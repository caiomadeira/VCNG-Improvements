#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

int i, isActivated;
int c[30];
int cur;
float timeScale = 1.0;

void ChangeLetterPos(void) {
	isActivated = false;
	for (i = 1; i < 30; i++) {
		c[i-1] = c[i];
	}
	c[29] = cur;
	return;
}

void UpdateKeys(void) {
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(16)) {
		cur = 16;
		ChangeLetterPos();
	} else
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(17)) {
		cur = 17;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(18)) {
		cur = 18;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(19)) {
		cur = 19;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(20)) {
		cur = 20;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(21)) {
		cur = 21;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(22)) {
		cur = 22;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(23)) {
		cur = 23;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(24)) {
		cur = 24;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(25)) {
		cur = 25;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(30)) {
		cur = 30;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(31)) {
		cur = 31;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(32)) {
		cur = 32;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(33)) {
		cur = 33;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(34)) {
		cur = 34;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(35)) {
		cur = 35;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(36)) {
		cur = 36;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(37)) {
		cur = 37;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(38)) {
		cur = 38;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(44)) {
		cur = 44;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(45)) {
		cur = 45;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(46)) {
		cur = 46;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(47)) {
		cur = 47;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(48)) {
		cur = 48;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(49)) {
		cur = 49;
		ChangeLetterPos();
	}
	if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(50)) {
		cur = 50;
		ChangeLetterPos();
	}
	if ((IS_GAME_KEYBOARD_KEY_JUST_PRESSED(57)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(26)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(27)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(39)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(40)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(51)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(52)) || (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(53))) {
		cur = 0;
		ChangeLetterPos();
	}
	return;
}

void CreateCar(char* name) {
	int ccar;
	float x, y, z, h, px, py;
	REQUEST_MODEL(GET_HASH_KEY(name));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY(name))) {
		WAIT(0);
	}
	GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);
	GET_CHAR_HEADING(GetPlayerPed(), &h);
	h += 90.0;
	px = x + COS(h) * 6.0;
	py = y + SIN(h) * 6.0;
	h -= 180.0;
	CREATE_CAR(GET_HASH_KEY(name), px, py, z, &ccar, 1);
	SET_CAR_HEADING(ccar, h);
	MARK_CAR_AS_NO_LONGER_NEEDED(&ccar);
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY(name));
	PRINT_HELP("CHEAT1");
	isActivated = true;
	return;
}

void main(void) {
	WAIT(5000);
	isActivated = false;
	for (i = 0; i < 30; i++) {
		c[i] = 0;
	}
	while (true) {
		WAIT(0);
		int a[30];
		if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
			UpdateKeys();
			if (!isActivated) {
				// GETTHEREFAST - спавн Sabre
				if ((c[18] == 34) && (c[19] == 18) && (c[20] == 20) && (c[21] == 20) && (c[22] == 35) && (c[23] == 18) && (c[24] == 19) && (c[25] == 18) && (c[26] == 33) && (c[27] == 30) && (c[28] == 31) && (c[29] == 20)) {
					CreateCar("sabregt");
				// RUBBISHCAR - спавн мусоровоза
				} else if ((c[20] == 19) && (c[21] == 22) && (c[22] == 48) && (c[23] == 48) && (c[24] == 23) && (c[25] == 31) && (c[26] == 35) && (c[27] == 46) && (c[28] == 30) && (c[29] == 19)) {
					CreateCar("trash");
				// BETTERTHANWALKING - спавн гольфкара	
				} else if ((c[13] == 48) && (c[14] == 18) && (c[15] == 20) && (c[16] == 20) && (c[17] == 18) && (c[18] == 19) && (c[19] == 20) && (c[20] == 35) && (c[21] == 30) && (c[22] == 49) && (c[23] == 17) && (c[24] == 30) && (c[25] == 38) && (c[26] == 37) && (c[27] == 23) && (c[28] == 49) && (c[29] == 34)) {
					CreateCar("huntley");
				// GETTHEREVERYFASTINDEED - спавн Hotring A	
				} else if ((c[8] == 34) && (c[9] == 18) && (c[10] == 20) && (c[11] == 20) && (c[12] == 35) && (c[13] == 18) && (c[14] == 19) && (c[15] == 18) && (c[16] == 47) && (c[17] == 18) && (c[18] == 19) && (c[19] == 21) && (c[20] == 33) && (c[21] == 30) && (c[22] == 31) && (c[23] == 20) && (c[24] == 23) && (c[25] == 49) && (c[26] == 32) && (c[27] == 18) && (c[28] == 18) && (c[29] == 32)) {
					CreateCar("chavos");
				// GETTHEREAMAZINGLYFAST - спавн Hotring B
				} else if ((c[9] == 34) && (c[10] == 18) && (c[11] == 20) && (c[12] == 20) && (c[13] == 35) && (c[14] == 18) && (c[15] == 19) && (c[16] == 18) && (c[17] == 30) && (c[18] == 50) && (c[19] == 30) && (c[20] == 44) && (c[21] == 23) && (c[22] == 49) && (c[23] == 34) && (c[24] == 38) && (c[25] == 21) && (c[26] == 33) && (c[27] == 30) && (c[28] == 31) && (c[29] == 20)) {
					CreateCar("feroci");
				// ROCKANDROLLCAR - спавн лимузина	
				} else if ((c[16] == 19) && (c[17] == 24) && (c[18] == 46) && (c[19] == 37) && (c[20] == 30) && (c[21] == 49) && (c[22] == 32) && (c[23] == 19) && (c[24] == 24) && (c[25] == 38) && (c[26] == 38) && (c[27] == 46) && (c[28] == 30) && (c[29] == 19)) {
					CreateCar("stretch");
				// THELASTRIDE - спавн катафалка	
				} else if ((c[19] == 20) && (c[20] == 35) && (c[21] == 18) && (c[22] == 38) && (c[23] == 30) && (c[24] == 31) && (c[25] == 20) && (c[26] == 19) && (c[27] == 23) && (c[28] == 32) && (c[29] == 18)) {
					CreateCar("romero");
				// GETTHEREQUICKLY - спавн первой тачки из Bloodring
				} else if ((c[15] == 34) && (c[16] == 18) && (c[17] == 20) && (c[18] == 20) && (c[19] == 35) && (c[20] == 18) && (c[21] == 19) && (c[22] == 18) && (c[23] == 16) && (c[24] == 22) && (c[25] == 23) && (c[26] == 46) && (c[27] == 37) && (c[28] == 38) && (c[29] == 21)) {
					CreateCar("willard");
				// TRAVELINSTYLE - спавн второй тачки из Bloodring
				} else if ((c[17] == 20) && (c[18] == 19) && (c[19] == 30) && (c[20] == 47) && (c[21] == 18) && (c[22] == 38) && (c[23] == 23) && (c[24] == 49) && (c[25] == 31) && (c[26] == 20) && (c[27] == 21) && (c[28] == 38) && (c[29] == 18)) {
					CreateCar("peyote");
				// PANZER - спавн танка	
				} else if ((c[24] == 25) && (c[25] == 30) && (c[26] == 49) && (c[27] == 44) && (c[28] == 18) && (c[29] == 19)) {
					CreateCar("pstockade");
				// ASPIRINE - восстановление жизни	
				} else if ((c[22] == 30) && (c[23] == 31) && (c[24] == 25) && (c[25] == 23) && (c[26] == 19) && (c[27] == 23) && (c[28] == 49) && (c[29] == 18)) {
					SET_CHAR_HEALTH(GetPlayerPed(), 1000);
					if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
						int hcar;
						STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &hcar);
						SET_ENGINE_HEALTH(hcar, 1500);
						MARK_CAR_AS_NO_LONGER_NEEDED(&hcar);
					}
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// PRECIOUSPROTECTION - броня
				} else if ((c[12] == 25) && (c[13] == 19) && (c[14] == 18) && (c[15] == 46) && (c[16] == 23) && (c[17] == 24) && (c[18] == 22) && (c[19] == 31) && (c[20] == 25) && (c[21] == 19) && (c[22] == 24) && (c[23] == 20) && (c[24] == 18) && (c[25] == 46) && (c[26] == 20) && (c[27] == 23) && (c[28] == 24) && (c[29] == 49)) {
					ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// THUGSTOOLS - первый пак с оружием
				} else if ((c[20] == 20) && (c[21] == 35) && (c[22] == 22) && (c[23] == 34) && (c[24] == 31) && (c[25] == 20) && (c[26] == 24) && (c[27] == 24) && (c[28] == 38) && (c[29] == 31)) {
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_PISTOL);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_SHOTGUN);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_MICRO_UZI);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_BASEBALLBAT);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_MOLOTOV);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// PROFESSIONALTOOLS - второй пак с оружием
				} else if ((c[13] == 25) && (c[14] == 19) && (c[15] == 24) && (c[16] == 33) && (c[17] == 18) && (c[18] == 31) && (c[19] == 31) && (c[20] == 23) && (c[21] == 24) && (c[22] == 49) && (c[23] == 30) && (c[24] == 38) && (c[25] == 20) && (c[26] == 24) && (c[27] == 24) && (c[28] == 38) && (c[29] == 31)) {
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_DEAGLE);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_SHOTGUN);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_MP5);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_KNIFE);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_GRENADE);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// NUTTERTOOLS - третий пак с оружием
				} else if ((c[19] == 49) && (c[20] == 22) && (c[21] == 20) && (c[22] == 20) && (c[23] == 18) && (c[24] == 19) && (c[25] == 20) && (c[26] == 24) && (c[27] == 24) && (c[28] == 38) && (c[29] == 31)) {
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_DEAGLE);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_SNIPERRIFLE);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M4);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_FTHROWER);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_RLAUNCHER);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// LEAVEMEALONE - убрать звезды розыска
				} else if ((c[18] == 38) && (c[19] == 18) && (c[20] == 30) && (c[21] == 47) && (c[22] == 18) && (c[23] == 50) && (c[24] == 18) && (c[25] == 30) && (c[26] == 38) && (c[27] == 24) && (c[28] == 49) && (c[29] == 18)) {
					CLEAR_WANTED_LEVEL(GetPlayerIndex());
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// YOUWONTTAKEMEALIVE - добавить две звезды
				} else if ((c[12] == 21) && (c[13] == 24) && (c[14] == 22) && (c[15] == 17) && (c[16] == 24) && (c[17] == 49) && (c[18] == 20) && (c[19] == 20) && (c[20] == 30) && (c[21] == 37) && (c[22] == 18) && (c[23] == 50) && (c[24] == 18) && (c[25] == 30) && (c[26] == 38) && (c[27] == 23) && (c[28] == 47) && (c[29] == 18)) {
					int wl;
					STORE_WANTED_LEVEL(GetPlayerIndex(), &wl);					
					wl += 2;
					if (wl > 6) {
						wl = 6;
					}
					ALTER_WANTED_LEVEL(GetPlayerIndex(), wl);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// ICANTTAKEITANYMORE - игрок умирает
				} else if ((c[12] == 23) && (c[13] == 46) && (c[14] == 30) && (c[15] == 49) && (c[16] == 20) && (c[17] == 20) && (c[18] == 30) && (c[19] == 37) && (c[20] == 18) && (c[21] == 23) && (c[22] == 20) && (c[23] == 30) && (c[24] == 49) && (c[25] == 21) && (c[26] == 50) && (c[27] == 24) && (c[28] == 19) && (c[29] == 18)) {
					EXPLODE_CHAR_HEAD(GetPlayerPed());
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// ABITDRIEG - облачная погода
				} else if ((c[21] == 30) && (c[22] == 48) && (c[23] == 23) && (c[24] == 20) && (c[25] == 32) && (c[26] == 19) && (c[27] == 23) && (c[28] == 18) && (c[29] == 34)) {
					FORCE_WEATHER_NOW(WEATHER_CLOUDY);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// APLEASANTDAY - хорошая погода
				} else if ((c[18] == 30) && (c[19] == 25) && (c[20] == 38) && (c[21] == 18) && (c[22] == 30) && (c[23] == 31) && (c[24] == 30) && (c[25] == 49) && (c[26] == 20) && (c[27] == 32) && (c[28] == 30) && (c[29] == 21)) {
					FORCE_WEATHER_NOW(WEATHER_SUNNY);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// ALOVELYDAY - ясная погода
				} else if ((c[20] == 30) && (c[21] == 38) && (c[22] == 24) && (c[23] == 47) && (c[24] == 18) && (c[25] == 38) && (c[26] == 21) && (c[27] == 32) && (c[28] == 30) && (c[29] == 21)) {
					FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// CATSANDDOGS - дождливая погода
				} else if ((c[19] == 46) && (c[20] == 30) && (c[21] == 20) && (c[22] == 31) && (c[23] == 30) && (c[24] == 49) && (c[25] == 32) && (c[26] == 32) && (c[27] == 24) && (c[28] == 34) && (c[29] == 31)) {
					FORCE_WEATHER_NOW(WEATHER_RAINING);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// CANTSEEATHING - туманная погода
				} else if ((c[17] == 46) && (c[18] == 30) && (c[19] == 49) && (c[20] == 20) && (c[21] == 31) && (c[22] == 18) && (c[23] == 18) && (c[24] == 30) && (c[25] == 20) && (c[26] == 35) && (c[27] == 23) && (c[28] == 49) && (c[29] == 34)) {
					FORCE_WEATHER_NOW(WEATHER_FOGGY);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// BIGBANG - взорвать все машины
				} else if ((c[23] == 48) && (c[24] == 23) && (c[25] == 34) && (c[26] == 48) && (c[27] == 30) && (c[28] == 49) && (c[29] == 34)) {
					int j, k, bcar;
					float px, py, pz;
					GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
					for (j = 0; j < 20; j++) {
						for (k = 0; k < 20; k++) {
							bcar = GET_CLOSEST_CAR(px+(j*10-100), py+(k*10-100), pz, 300.0, 0, 69);
							if (DOES_VEHICLE_EXIST(bcar)) {
								EXPLODE_CAR(bcar, 1, 0);
								MARK_CAR_AS_NO_LONGER_NEEDED(&bcar);
							}
						}
					}
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// ONSPEED - ускорить время игры
				} else if ((c[23] == 24) && (c[24] == 49) && (c[25] == 31) && (c[26] == 25) && (c[27] == 18) && (c[28] == 18) && (c[29] == 32)) {
					timeScale += 0.2;
					if (timeScale > 2.4) {
						timeScale = 2.4;
					}
					SET_TIME_SCALE(timeScale);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				// BOOOOOORING - замедлить время игры
				} else if ((c[19] == 48) && (c[20] == 24) && (c[21] == 24) && (c[22] == 24) && (c[23] == 24) && (c[24] == 24) && (c[25] == 24) && (c[26] == 19) && (c[27] == 23) && (c[28] == 49) && (c[29] == 34)) {
					timeScale -= 0.2;
					if (timeScale <= 0.0) {
						timeScale = 0.2;
					}
					SET_TIME_SCALE(timeScale);
					PRINT_HELP("CHEAT1");
					isActivated = true;
				}
			}
		}
	}
}