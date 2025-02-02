using System;
using System.Text;
using System.Windows.Forms;
using System.Collections.Generic;
using GTA;
using GTA.Native;

namespace SimpleScript {

    public class SimpleScript : Script {
		
		private string version = "1.0.1";

        private void Message(string message) {
            Game.DisplayText("[SimpleScript] " + message);
        }
		
		public SimpleScript() {
			this.KeyDown += new GTA.KeyEventHandler(KeyManager);

			Message("Successfully Started ! (v" + version + ")");
		}

        private void KeyManager(object sender, GTA.KeyEventArgs e) {

            if (e.Key == Settings.GetValueKey("RESTORE_PLAYER_HEALTH_AND_ARMOR", "KEYS", Keys.D1)) {
                Player.Character.Health = 1000;
                Player.Character.Armor = 1000;

                Message(
                    Settings.GetValueString(
                        "RESTORE_PLAYER_HEALTH_AND_ARMOR",
                        "MESSAGES",
                        "Your health and your armor have been restored !"
                    )
                );
            }
			
			if (e.Key == Settings.GetValueKey("SPAWN_VEHICLE", "KEYS", Keys.D2)) {
                if (Player.Character.CurrentVehicle == null) {
					Vector3 vehiclePosition = World.GetNextPositionOnStreet(Player.Character.Position.Around(5.0f));
					Vehicle vehicle = World.CreateVehicle(new Model("COMET"), vehiclePosition);
					Player.Character.Task.EnterVehicle(vehicle, VehicleSeat.Driver);
					vehicle.NoLongerNeeded();

					Message(
						Settings.GetValueString(
							"SPAWN_VEHICLE",
							"MESSAGES",
							"A vehicle has appeared near you !"
						)
					);
				} else {
					Message(
						Settings.GetValueString(
							"SPAWN_VEHICLE_ERROR",
							"MESSAGES",
							"You already have a vehicle !"
						)
					);
				}
            }
			
			if (e.Key == Settings.GetValueKey("REPAIR_VEHICLE", "KEYS", Keys.D3)) {
                if (Player.Character.CurrentVehicle != null) {
					Player.Character.CurrentVehicle.Repair();

					Message(
						Settings.GetValueString(
							"REPAIR_VEHICLE",
							"MESSAGES",
							"Your vehicle has been repaired !"
						)
					);
				} else {
					Message(
						Settings.GetValueString(
							"REPAIR_VEHICLE_ERROR",
							"MESSAGES",
							"You must be in a vehicle !"
						)
					);
				}
            }
			
			if (e.Key == Settings.GetValueKey("ADD_WANTED_LEVEL", "KEYS", Keys.D4)) {
                if (Player.WantedLevel < 6) {
					Player.WantedLevel += 1;
					
					Message(
                    Settings.GetValueString(
                        "ADD_WANTED_LEVEL",
                        "MESSAGES",
                        "Your wanted level as been increased by one !"
						)
					);
				} else {
					Message(
                    Settings.GetValueString(
                        "ADD_WANTED_LEVEL_ERROR",
                        "MESSAGES",
                        "You have reached the maximum wanted level !"
						)
					);
				}
            }
			
			if (e.Key == Settings.GetValueKey("REMOVE_WANTED_LEVEL", "KEYS", Keys.D5)) {
                if (Player.WantedLevel > 0) {
					Player.WantedLevel -= 6;
					
					Message(
                    Settings.GetValueString(
                        "REMOVE_WANTED_LEVEL",
                        "MESSAGES",
                        "Your wanted level as been deleted !"
						)
					);
				} else {
					Message(
                    Settings.GetValueString(
                        "REMOVE_WANTED_LEVEL_ERROR",
                        "MESSAGES",
                        "You are not wanted by the police !"
						)
					);
				}
            }
			
			if (e.Key == Settings.GetValueKey("ADD_MONEY", "KEYS", Keys.D6)) {
                Player.Money += 1000;
				
				Message(
                    Settings.GetValueString(
                        "ADD_MONEY",
                        "MESSAGES",
                        "1000$ have been added to your account !"
					)
				);
            }
			
			if (e.Key == Settings.GetValueKey("REMOVE_MONEY", "KEYS", Keys.D7)) {
                Player.Money -= 1000;
				
				Message(
                    Settings.GetValueString(
                        "REMOVE_MONEY",
                        "MESSAGES",
                        "1000$ has been withdrawn from your account !"
					)
				);
            }

			if (e.Key == Settings.GetValueKey("DROP_WEAPON", "KEYS", Keys.D8)) {
				if (Player.Character.Weapons.Current != null) {
					Player.Character.DropCurrentWeapon();

					Message(
						Settings.GetValueString(
							"DROP_WEAPON",
							"MESSAGES",
							"You throw your weapon !"
						)
					);
				} else {
					Message(
						Settings.GetValueString(
							"DROP_WEAPON_ERROR",
							"MESSAGES",
							"You have to hold a weapon to throw it !"
						)
					);
				}
			}

        }

    }

}