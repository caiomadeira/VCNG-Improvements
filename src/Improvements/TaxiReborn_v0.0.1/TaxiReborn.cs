/*
   Taxi Reborn By Caio Madeira
   https://github.com/caiomadeira/VCNG-Improvements
   Is a WIP Project and part of ViceCity Next Gen Improvements
   Give the credits.
   Code inspired by Alexander Blade's samples for Scripthook.
*/

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

      private float NoMoneyCounter = 0;
      private float cost = 0.0f;
      private float baseCost = 0.1f;
      private float costPerMeter = 0.5f;
      float Speed = 70.0f;
      private readonly string[] allowedTaxiModels = { "TAXI", "TAXI2", "CABBY", "ROMANS_TAXI" };
      Vehicle SelectedCar = null;
      Ped SelectedDriver = null;
      eState state = eState.Off;
      Vector3 Destination;
      bool ChangedTimescale = false;
      Blip w = Game.GetWaypoint();
      float playerDistToTaxi = 10.0f;
    public TaxiReborn() {
        Interval = 500;
        this.KeyDown += OnKeyDown;
        this.Tick += OnTick;
        Game.DisplayText("TaxiRebornVCNG\nBy caiomadeira\nv0.0.1\ngithub.com/caiomadeira", 3000);
    }
    private void OnTick(object sender, EventArgs e)
    {   
        CheckAllTimeForTaxis();

        if (state == eState.WaitingForPlayer)
        {
            DisablePolice(true);
        }
        if (!Exists(Player.Character) || Player.Character.isDead )
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
                UpdateCostChange(1);
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
               if (Player.Character.isInVehicle(SelectedCar)) {
                  if (SelectedCar.Position.DistanceTo2D(Destination) < 10.0f) { // we are close to the destination

                     if (ChangedTimescale) {
                        Game.TimeScale = 1.0F;
                        ChangedTimescale = false;
                     }

                     Game.DisplayText("Here we are!");
                     state = eState.ReachedTarget;

                  } else if (!SelectedDriver.isInVehicle(SelectedCar)) { // the driver left the vehicle
                     FinishTrip();
                  }
               } else {
                  FinishTrip();
               }
               break;

            case eState.ReachedTarget:
               if (!Player.Character.isInVehicle(SelectedCar)) 
               { // wait for player to get out of the car
                  FinishTrip();
               } 
               break;
         }
    }

    private void OnKeyDown(object sender, GTA.KeyEventArgs e)
    {
        switch (e.Key) {

            case Keys.E:
                if (Player.WantedLevel == 0)
                    DisablePolice(true);
                else { return; }
               switch (state) {
                  case eState.Off:
                     cost = 0.0f;
                     SelectedCar = World.GetClosestVehicle(Player.Character.Position, playerDistToTaxi);
                     if (!Exists(SelectedCar) || !IsTaxi(SelectedCar)) return;
                     SelectedDriver = SelectedCar.GetPedOnSeat(VehicleSeat.Driver);
                     if (!Exists(SelectedDriver)) 
                     {
                       // SelectedDriver = SelectedCar.CreatePedOnSeat(VehicleSeat.Driver);
                        //if (!Exists(SelectedDriver)) 
                        //{
                           //SelectedCar = null;
                           return;
                        //}
                     } else if (SelectedDriver == Player) {
                        SelectedCar = null;
                        SelectedDriver = null;
                        return;
                     }
                     // Call the taxi Animation
                     HailTaxi();
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
                     if (SetDestination()) 
                     {
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
                        Vector3 nearbyPosition = Destination + new Vector3(RandFloat(-12f, 12f), RandFloat(-12f, 12f), 0f);

                        Game.FadeScreenOut(1000);
                        Wait(1200);

                        cost += 10.0f;

                        Player.Character.Position = nearbyPosition;
                        SelectedCar.Position = nearbyPosition;

                        SelectedDriver.Task.ClearAll();
                        state = eState.ReachedTarget;
                        Game.FadeScreenIn(1000);
                        Player.Character.Task.LeaveVehicle();
                    }
                }
                break;
         }
    }
   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      UpdateCostChange (WIP): 
      Increase the cost of trip per distance. 
      TODO: Fix the calculo to avoid high costs.
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private void UpdateCostChange(int taxType)
   {
      if (taxType == 0)
      {
         if (SelectedCar != null && Destination != null)
         {
            float distance = SelectedCar.Position.DistanceTo(Destination);
            cost = baseCost + (distance * costPerMeter);

            if (cost > 1000.0f)
         {
               cost = 1000.0f;
         }
         }
      } else 
      {
         // For while, i put this because the calculus has problems
         cost += baseCost;
      }
   }
   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      DisablePolice: 
      Disable police while enter in vehicle.
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
    private void DisablePolice(bool NoPolice)
    {
        if (NoPolice == true) 
        {
            Player.WantedLevel = 0;
            Game.WantedMultiplier = 0.0F;
        } 
        else 
        {
            Game.WantedMultiplier = 1.0F;
        }
    }
   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      CheckAllTimeForTaxis: 
      Search for taxis nearst player
      TODO: The functions need to avoid show the message if the taxi has no Ped Driver
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private void CheckAllTimeForTaxis()
   {
      if (state == eState.Off && !Player.Character.isInVehicle())
      {
         Vehicle closestTaxi = World.GetClosestVehicle(Player.Character.Position, playerDistToTaxi);
         if (closestTaxi != null && IsTaxi(closestTaxi))
         {
            Game.DisplayText("Press 'E' to call the taxi", 3000);
         }
      }
   }
   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      FinishTrip: 
      FinishTrip decreasing Players Money or set the consequences.
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private void FinishTrip()
    {
      Player.Character.Task.LeaveVehicle();
      TurnDriverToNormal();
      if (Player.Money >= cost)
      {
         string msg = "Trip Finished. Total Cost: $" + cost.ToString("0.0");
         GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING", "STRING", msg, 3000);
         Player.Money = (int)(Player.Money - Math.Round(cost));
         if (NoMoneyCounter > 0) { NoMoneyCounter--; }
         else { NoMoneyCounter = 0; }
      } 
      else 
      {
         string msg = "Trip Finished. Total Cost: $" + cost.ToString("0.0") + " but, you don't have money.";
         GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING", "STRING", msg, 3000);

         NoMoneyCounter++;
         if (Exists(SelectedDriver) && Exists(SelectedCar))
         {
            if (NoMoneyCounter >= 0 && NoMoneyCounter <= 2)
            {
               SelectedDriver.Task.LeaveVehicle();
               SelectedDriver.Task.FightAgainst(Player.Character);
            }
            else if (NoMoneyCounter > 2)
            {
               SelectedDriver.Task.LeaveVehicle();
               SelectedDriver.Task.FightAgainst(Player.Character);

               Player.WantedLevel = 1;
            }
         }
      }
      state = eState.Off;
    }
   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      HailTaxi: 
      Make HAIL TAXI animation
      //TODO: Create Array of animations of 'hail taxi'
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private void HailTaxi()
   {
   if (Player.Character.Weapons.Current != Weapon.Unarmed)
      Player.Character.Weapons.Select(Weapon.Unarmed);

   AnimationFlags animflags = AnimationFlags.Unknown12 | AnimationFlags.Unknown11 | AnimationFlags.Unknown09;
   Player.Character.Task.PlayAnimation(new AnimationSet("taxi_hail"), "hail_taxi", 8.0f, animflags);
   }

   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      SetDestination: 
      Set Destination of Trip
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private bool SetDestination() 
   {
      w = Game.GetWaypoint();
      if (w == null) {
         GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING", "STRING", "You have to select a waypoint first!");
         return false;
      }
      Destination = World.GetNextPositionOnStreet(w.Position);
      Game.DisplayText("Driving to " + World.GetStreetName(Destination) + "...", 3000);
      return true;
   }

   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      TurnDriverToNormal: 
      Revert any settings we have done during the script
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private void TurnDriverToNormal() 
   {
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
   /* 
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
      IsTaxi: 
      Check if Vehicle Is a Taxi
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   */
   private bool IsTaxi(Vehicle vehicle)
   {
      foreach(string model in allowedTaxiModels)
      {
         if (vehicle.Name == model)
               return true;
      }
      return false;
   }

   private float RandFloat(float minValue, float maxValue)
   {
      Random rand = new Random();
      return (float)(rand.NextDouble() * (maxValue - minValue) + minValue);
   }
}