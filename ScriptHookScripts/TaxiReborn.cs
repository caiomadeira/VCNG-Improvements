using System;
using System.Windows.Forms;
using GTA;

public class TaxiReborn : Script {

    enum eState {
         Off,
         WaitingForPlayer,
         Driving,
         ReachedTarget,
      }

      private float cost = 0.0f;
      float Speed = 70.0f;
      private readonly string[] allowedTaxiModels = { "TAXI", "TAXI2", "CABBY", "ROMANS_TAXI" };
      Vehicle SelectedCar = null;
      Ped SelectedDriver = null;
      eState state = eState.Off;
      Vector3 Destination;
      bool ChangedTimescale = false;
      Blip w = Game.GetWaypoint();

    public TaxiReborn() {
        Interval = 250;
        this.KeyDown += OnKeyDown;
        this.Tick += OnTick;
        Game.DisplayText("Task Reborn: Running", 3000);
    }
    private void OnTick(object sender, EventArgs e)
    {   
        // if (state == eState.Off || state == eState.ReachedTarget)
        // {
        //     Vehicle closestTaxi = World.GetClosestVehicle(Player.Character.Position, 10.0f);
        //     if (closestTaxi != null && IsTaxi(closestTaxi))
        //     {
        //          Game.DisplayText("Press 'E' to get a cab.", 3000);
        //     } else 
        //     { 
        //          Game.DisplayText("", 3000);
        //     }
        // }

        if (state == eState.WaitingForPlayer)
        {
            DisablePolice(true);
        }
        if (!Exists(Player.Character) || Player.Character.isDead)
        {
            TurnDriverToNormal();
            state = eState.Off;
            return;
        }
        if (state == eState.Driving && w != null)
        {
            DisablePolice(false);
            if (Exists(SelectedCar) && SelectedCar.Speed > 0.5f)
            {
                cost += 0.2f;
            }
            Game.DisplayText("Taxi Trip\nPress 'M' to accelerate time.\nPress 'SPACEBAR' to Skip with a Extra Cost.\nTrip in Progress.\nCost: $" + cost.ToString("0.0"));
        }
        if (state == eState.ReachedTarget)
        {
            DisablePolice(false);
        }

        if (state == 0) return;
         switch (state) {
            case eState.WaitingForPlayer:
               if (Player.Character.isSittingInVehicle(SelectedCar)) 
               { 
                    Player.Character.WillFlyThroughWindscreen = false;
                    Blip waypoint = Game.GetWaypoint();
                    if (waypoint == null)
                    {
                        Game.DisplayText("Waiting for player set destination....");
                        state = eState.WaitingForPlayer;
                    } else 
                    {
                        if (SetDestination())
                        {
                            SelectedDriver.Task.ClearAll();
                            SelectedDriver.Task.AlwaysKeepTask = true;
                            SelectedDriver.Task.DriveTo(SelectedCar, Destination, Speed, false);
                            state = eState.Driving;
                        } else {
                        state = eState.ReachedTarget;
                    }
                }

               } else if (Player.Character.Position.DistanceTo(SelectedCar.Position) > 8.0f) { // player got too far away
                  TurnDriverToNormal();
                  state = eState.Off;
               }
               break;

            case eState.Driving:
               //Game.DisplayText("Taxi Trip\nPress 'M' to accelerate time.\nPress 'SPACEBAR' to Skip with a Extra Cost.\n");
               if (Player.Character.isInVehicle(SelectedCar)) {
                  if (SelectedCar.Position.DistanceTo2D(Destination) < 10.0f) { // we are close to the destination

                     SelectedDriver.Task.ClearAll();
                     SelectedDriver.Task.AlwaysKeepTask = true;
                     if (ChangedTimescale) {
                        Game.TimeScale = 1.0F;
                        ChangedTimescale = false;
                     }

                     Game.DisplayText("Here we are!");

                     state = eState.ReachedTarget;

                  } else if (!SelectedDriver.isInVehicle(SelectedCar)) { // the driver left the vehicle
                     TurnDriverToNormal();
                     Game.DisplayText("Trip Finished. Cost: $" + cost.ToString("0.0"));
                     Player.Money = (int)(Player.Money - Math.Round(cost));
                     state = eState.Off;
                  }
               } else {
                  TurnDriverToNormal();
                  Game.DisplayText("Trip Finished. Cost: $" + cost.ToString("0.0"));
                  Player.Money = (int)(Player.Money - Math.Round(cost));
                  state = eState.Off;
               }
               break;

            case eState.ReachedTarget:
               if (!Player.Character.isInVehicle(SelectedCar)) { // wait for player to get out of the car
                  TurnDriverToNormal();
                  Game.DisplayText("Trip Finished. Cost: $" + cost.ToString("0.0"));
                  Player.Money = (int)(Player.Money - Math.Round(cost));
                  state = eState.Off;
               } 
            //    else 
            //    {
            //         SelectedDriver.Task.StandStill(-1);
            //         state = eState.ReachedTarget;
            //    }
               break;
         }
    }


    private void OnKeyDown(object sender, GTA.KeyEventArgs e)
    {
        switch (e.Key) {

            case Keys.E:
            //TODO: Criar um array com animações para chamar o taxi.
            AnimationFlags animflags = AnimationFlags.Unknown12 | AnimationFlags.Unknown11 | AnimationFlags.Unknown09;
            Player.Character.Task.PlayAnimation(new AnimationSet("taxi_hail"), "hail_taxi", 8.0f, animflags);
                if (Player.WantedLevel == 0)
                    DisablePolice(true);
                else { return; }
               switch (state) {
                  case eState.Off:
                  cost = 0.0f;
                     SelectedCar = World.GetClosestVehicle(Player.Character.Position, 10.0F);
                     if (!Exists(SelectedCar) || !IsTaxi(SelectedCar)) return;
                     SelectedDriver = SelectedCar.GetPedOnSeat(VehicleSeat.Driver);
                     if (!Exists(SelectedDriver)) { return; } 
                     else if (SelectedDriver == Player) {
                        SelectedCar = null;
                        SelectedDriver = null;
                        return;
                     }
                    // Force police to ignore player when entering the taxi
                     DisablePolice(true);
                     // force the game to load all path nodes, or he wouldn't be able to find the way to distant locations
                     Game.LoadAllPathNodes = true;

                     SelectedCar.DoorLock = 0;
                     SelectedCar.MakeProofTo(false, false, false, true, false); // make the car collision proof, or it will blow up pretty fast

                     // make sure that the driver won't die from his miserable driving skills
                     SelectedDriver.Invincible = true;
                     SelectedDriver.WillFlyThroughWindscreen = false;
                     SelectedDriver.CanBeKnockedOffBike = false;

                     // make sure that he will focus on his task
                     SelectedDriver.BlockPermanentEvents = true;
                     SelectedDriver.ChangeRelationship(RelationshipGroup.Player, Relationship.Respect);

                     SelectedDriver.Task.ClearAll();
                     SelectedDriver.Task.AlwaysKeepTask = true;
                     SelectedDriver.Task.Wait(-1); // wait until we clear the tasks again

                     if (Player.Group.MemberCount > 0)
                        // Group.EnterVehicle will make sure that only members closeby try to enter the vehicle
                        Player.Group.EnterVehicle(SelectedCar, true, true);
                     else
                        Player.Character.Task.EnterVehicle(SelectedCar, SelectedCar.GetFreePassengerSeat());

                     state = eState.WaitingForPlayer;
                     break;

                  case eState.WaitingForPlayer:

                     TurnDriverToNormal();
                     state = eState.Off;
                     break;

                  case eState.Driving: // Change Route

                        break;
                  case eState.ReachedTarget:
                     if (SetDestination()) {
                        // give the new task to the driver
                        SelectedDriver.BlockPermanentEvents = true;
                        SelectedDriver.Task.ClearAll();
                        SelectedDriver.Task.AlwaysKeepTask = true;
                        SelectedDriver.Task.DriveTo(SelectedCar, Destination, Speed, false);

                        state = eState.Driving;
                     }
                     break;
               }
               break;

            case Keys.M:
               if (state == eState.Driving) { // Accelerate time when M is pressed while driving
                  ChangedTimescale = !ChangedTimescale;
                  if (ChangedTimescale)
                     Game.TimeScale = 4.0F;
                  else
                     Game.TimeScale = 1.0F;
               }
               break;
            
            // case spacebar to skip
            case Keys.Space:
                if (state == eState.Driving)
                {
                    if (Destination != null)
                    {
                        Game.FadeScreenOut(1000);
                        Wait(1200);

                        cost += 10.0f;

                        Player.Character.Position = Destination;
                        SelectedCar.Position = Destination;

                        SelectedDriver.Task.ClearAll();
                        state = eState.ReachedTarget;
                        Game.FadeScreenIn(1000);
                    }
                }
                break;
         }
    }

    private void DisablePolice(bool NoPolice)
    {
        if (NoPolice == true) 
        {
            Player.WantedLevel = 0;
            Game.WantedMultiplier = 0.0F;
            // Game.DisplayText("Police will ignore you!", 300);
        } 
        else 
        {
            Game.WantedMultiplier = 1.0F;
            // Game.DisplayText("Police will NOT ignore you!", 300);
        }
    }
    private bool SetDestination() {
        w = Game.GetWaypoint();
         if (w == null) {
            Game.DisplayText("You have to select a waypoint first!");
            return false;
         }
         Destination = World.GetNextPositionOnStreet(w.Position);
        Game.DisplayText("Driving to " + World.GetStreetName(Destination) + "...", 3000);
         return true;
      }

      // revert any settings we have done during the script
      private void TurnDriverToNormal() {
         Player.Character.CanBeKnockedOffBike = true;
         Player.Character.WillFlyThroughWindscreen = true;
         Player.Character.MakeProofTo(false, false, false, false, false);
         Game.LoadAllPathNodes = false;
         if (ChangedTimescale) {
            Game.TimeScale = 1.0F;
            ChangedTimescale = false;
         }
         state = eState.Off;
         bool gotcar = Exists(SelectedCar);
         if (gotcar) {
            SelectedCar.PassengersLeaveVehicle(true);
            SelectedCar.MakeProofTo(false, false, false, false, false);
         }
         if (Exists(SelectedDriver)) {
            SelectedDriver.Invincible = false;
            SelectedDriver.WillFlyThroughWindscreen = true;
            SelectedDriver.CanBeKnockedOffBike = true;
            SelectedDriver.BlockPermanentEvents = false;
            SelectedDriver.ChangeRelationship(RelationshipGroup.Player, Relationship.Like);
            if (gotcar) {
               SelectedDriver.Task.ClearAll();
               SelectedDriver.Task.AlwaysKeepTask = true;
               SelectedDriver.Task.CruiseWithVehicle(SelectedCar, 12.0f, true);
            }
         }
      }

      private bool IsTaxi(Vehicle vehicle)
      {
        foreach(string model in allowedTaxiModels)
        {
            if (vehicle.Name == model)
                return true;
        }
        return false;
      }

}