#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

int sID, sIDTime, sState;
int plWeap, sound_timer1, sound_timer2;

void main(void) {
	sState = 0;
	while (true) {
		WAIT(0);
		GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &plWeap);
		if (sState == 0)
		{
			if (plWeap == WEAPON_FTHROWER)
			{
				WAIT(1000);
				sState = 1;
			}
		}
		else if (sState == 1)
		{
			SET_MOVIE_VOLUME( -8 );
			SET_CURRENT_MOVIE( "audio/START" );
			PLAY_MOVIE();
			SETTIMERC(0);
			while (TIMERC() < 1416)
			{
				WAIT(0);
				if (plWeap != WEAPON_FTHROWER)
				{
					sState = 99;
				}
			}
			sState = 2;
			SET_CURRENT_MOVIE( "audio/LOW" );
			PLAY_MOVIE();
			SETTIMERA(0);
		}
		else if (sState == 2)
		{
			if (plWeap != WEAPON_FTHROWER) {
				sState = 99;
			}
			if (TIMERA() > 15000)
			{
				SET_CURRENT_MOVIE( "audio/LOW" );
				PLAY_MOVIE();
				SETTIMERA(0);
			}
			if (IS_CONTROL_PRESSED(2, 4))
			{
				sState = 3;
				SET_CURRENT_MOVIE( "audio/TOHIGH" );
				PLAY_MOVIE();
			}
		}
		else if (sState == 3)
		{
			SETTIMERC(0);
			while (TIMERC() < 344)
			{
				WAIT(0);
				if (plWeap != WEAPON_FTHROWER)
				{
					sState = 99;
				}
			}
			sState = 4;
			SET_CURRENT_MOVIE( "audio/HIGH" );
			PLAY_MOVIE();
			SETTIMERA(0);
		}
		else if (sState == 4)
		{
			if (plWeap != WEAPON_FTHROWER)
			{
				sState = 99;
			}
			if (TIMERA() > 15000)
			{
				SET_CURRENT_MOVIE( "audio/HIGH" );
				PLAY_MOVIE();
				SETTIMERA(0);
			}
			if (!IS_CONTROL_PRESSED(2, 4))
			{
				sState = 5;
				SET_CURRENT_MOVIE( "audio/TOLOW" );
				PLAY_MOVIE();
			}
		}
		else if (sState == 5)
		{
			SET_CHAR_AMMO(GetPlayerPed(), WEAPON_FTHROWER, AMMO_MAX);
			SETTIMERC(0);
			while (TIMERC() < 231)
			{
				WAIT(0);
				if (plWeap != WEAPON_FTHROWER)
				{
					sState = 99;
				}
			}
			SET_CURRENT_MOVIE( "audio/LOW" );
			PLAY_MOVIE();
			sState = 2;	
		}
		else if (sState == 99)
		{
			SET_CURRENT_MOVIE( "audio/OFF" );
			PLAY_MOVIE();
			SETTIMERC(0);
			while (TIMERC() < 769) {
				WAIT(0);
			}
			STOP_STREAM();
			RELEASE_MOVIE();
			sState = 0;
		}
	}
}