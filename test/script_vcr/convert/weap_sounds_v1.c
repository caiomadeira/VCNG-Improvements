#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

int sID, sIDTime, sState, sSwitched, sCount;
int plWeap, sound_timer1, sound_timer2;

void main(void) {
	while (!REQUEST_AMBIENT_AUDIO_BANK("SCRIPT_MISSION/CHSAW")) {
		WAIT(0);
	}
	sState = 0;
	sCount = 0;
	while (true) {
		WAIT(0);
		GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &plWeap);
		if (sState == 0) {
			if (plWeap == WEAPON_FTHROWER) {
				WAIT(1000);
				sID = GET_SOUND_ID();
				sState = 1;
			}
		} else if (sState == 1) {
			PLAY_SOUND_FROM_PED(sID, "SCRIPT_MISSION_CHSAW_START", GetPlayerPed());
			SETTIMERC(0);
			while (TIMERC() < 1416) {
				WAIT(0);
				if (plWeap != WEAPON_FTHROWER) {
					sState = 99;
				}
			}
			sState = 2;
			sSwitched = 0;
		} else if (sState == 2) {
			if (sSwitched == 0) {
				PLAY_SOUND_FROM_PED(sID, "SCRIPT_MISSION_CHSAW_LOW", GetPlayerPed());
				sSwitched = 1;
			}
			if (HAS_SOUND_FINISHED(sID)) {
				sSwitched = 0;
				sCount++;
			}
			if (plWeap != WEAPON_FTHROWER) {
				sState = 99;
			}
			if (IS_CONTROL_PRESSED(2, 4)) {
				sState = 3;
			}
		} else if (sState == 3) {
			PLAY_SOUND_FROM_PED(sID, "SCRIPT_MISSION_CHSAW_TOHIGH", GetPlayerPed());
			SETTIMERC(0);
			while (TIMERC() < 344) {
				WAIT(0);
				if (plWeap != WEAPON_FTHROWER) {
					sState = 99;
				}
			}
			sState = 4;
			sSwitched = 0;
		} else if (sState == 4) {
			if (sSwitched == 0) {
				PLAY_SOUND_FROM_PED(sID, "SCRIPT_MISSION_CHSAW_HIGH", GetPlayerPed());
				sSwitched = 1;
			}
			if (HAS_SOUND_FINISHED(sID)) {
				sSwitched = 0;
				sCount++;
			}
			if (plWeap != WEAPON_FTHROWER) {
				sState = 99;
			}
			if (!IS_CONTROL_PRESSED(2, 4)) {
				sState = 5;
			}
		} else if (sState == 5) {
			PLAY_SOUND_FROM_PED(sID, "SCRIPT_MISSION_CHSAW_TOLOW", GetPlayerPed());
			SET_CHAR_AMMO(GetPlayerPed(), WEAPON_FTHROWER, AMMO_MAX);
			SETTIMERC(0);
			while (TIMERC() < 231) {
				WAIT(0);
				if (plWeap != WEAPON_FTHROWER) {
					sState = 99;
				}
			}
			sState = 2;
			sSwitched = 0;		
		} else if (sState == 99) {
			PLAY_SOUND_FROM_PED(sID, "SCRIPT_MISSION_CHSAW_OFF", GetPlayerPed());
			SETTIMERC(0);
			while (TIMERC() < 769) {
				WAIT(0);
			}
			STOP_SOUND(sID);
			RELEASE_SOUND_ID(sID);
			sState = 0;
		}
		if (sCount > 30) {
			sCount = 0;
			STOP_SOUND(sID);
			RELEASE_SOUND_ID(sID);
			sID = GET_SOUND_ID();
		}
	}
}