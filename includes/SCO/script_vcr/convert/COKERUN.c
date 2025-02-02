/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, blip_on, tovarX, tovarY, tovarZ, help_text1, all_tovar, go, sound, time_m, time_s, textur, skip, sutosave;
int income, load_mashin, help, message;

void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
		{
			break;
		}
	}
}
void boat_race(void)
{
	blip_on = 0;
	sutosave = 0;
	Blip boat_ico;
	help_text1 = 0;
	message = 0;

	load_mashin = 0;
	help = 0;
	uint rId9;

	WAIT(3000);
	while(true)
	{
		WAIT(0);
		if ((G_DIAZ >= 3) && (message < 3))
		{
			if (message == 0)
			{
				SetTime(2000);
				PRINT_HELP("BRID_OP"); //Storm warning over, all bridges to the mainland are now open.
				message = 1;
			}
			if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
			{
				DISABLE_FRONTEND_RADIO();
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_VS", " ", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SETTIMERA( 0 );
				while(true)
				{
					WAIT(0);
					if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						break;
					}
					else if ((TIMERA() > 14000) || (!IS_SCRIPTED_CONVERSATION_ONGOING()))
					{
						break;
					}
				}
				ENABLE_FRONTEND_RADIO();
				message = 5;
			}
		}
		if (sutosave == 1)
		{
			sutosave = 0;
			G_SAVE_SAVED = 16; // ����� ����� 
			G_SAVE_OCCURED = TRUE;
			DO_AUTO_SAVE();
			WAIT(500);
			if (DID_SAVE_COMPLETE_SUCCESSFULLY())
			{
				G_SAVE_OCCURED = FALSE;
			}
		}
//============================== Checkpoint Charlie ======================================
		if ((G_ONMISSION == 0) && (G_COKERUN > 0))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-224.504, -946.921, 7.458, &boat_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(boat_ico, BLIP_BOAT_TOUR);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(boat_ico, 1.1); // ������� ������ �� ������
				SET_BLIP_AS_SHORT_RANGE(boat_ico, 1); // ������ ��������� ���� �� � ���� ����������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(boat_ico, "LG_09");//������ �� ������ ��������� � ������� ����� ""
				blip_on = 1;
			}
			if ((IS_CHAR_IN_ANY_BOAT(GetPlayerPed())) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -151.874, -972.239, -0.789, -141.374, -966.239, 1.711, 0 ) && (!IS_CHAR_DEAD(GetPlayerPed())) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) || (IS_CHAR_IN_ANY_BOAT(GetPlayerPed())) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -156.289, -983.831, -0.789, -145.789, -977.831, 1.711, 0 )) && (!IS_CHAR_DEAD(GetPlayerPed())) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
			{
				if (help_text1 == 0)
				{
					CLEAR_HELP(); // ������� ����� ���������
					PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
					help_text1 = 1;
				}
				if (((IS_CONTROL_PRESSED( 2, 23 )) && (! IS_USING_CONTROLLER()) && (G_COKERUN > 0) && (G_ONMISSION == 0)) || ((IS_BUTTON_PRESSED( 0, 4 )) && (IS_USING_CONTROLLER()) && (G_COKERUN > 0) && (G_ONMISSION == 0)))
				{
					CLEAR_HELP(); // ������� ����� ���������
					REMOVE_BLIP(boat_ico);//������� ������ �� ������
					blip_on = 0;
					G_ONMISSION = 1;
					Cam camera;
					Object tovar, rampa_1, rampa_2, rampa_3;
					Texture fon, timer;
					uint gruz = ne_goods;
					uint ramp = waterjumpx2;

					all_tovar = 1;
					go = 0;
					sound = 0;
					time_m = 4;
					time_s = 30;
					skip = 0;

					textur = LOAD_TXD( "sunshine_race" );
					fon = GET_TEXTURE( textur, "fon_hud" );
					timer = GET_TEXTURE( textur, "timer_hud" );

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

					//������ ����
					REQUEST_MODEL(gruz);
					while (!HAS_MODEL_LOADED(gruz)) WAIT(0);
					CREATE_OBJECT_NO_OFFSET(gruz, -107.1, -993.9, 1.095, &tovar, TRUE);
					ADD_BLIP_FOR_OBJECT(tovar, &boat_ico);
					CHANGE_BLIP_SPRITE(boat_ico, BLIP_OBJECTIVE);//������ �� ������
					CHANGE_BLIP_COLOUR(boat_ico, 5);   //���� �����b �� ������
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(boat_ico, "MO_TARGET");//������ �� ������ ��������� � ������� �����
					CHANGE_BLIP_SCALE(boat_ico, 0.6); // ������� ������ �� ������

					//������ �����
					REQUEST_MODEL(ramp);
					while (!HAS_MODEL_LOADED(ramp)) WAIT(0);
					CREATE_OBJECT_NO_OFFSET(ramp, 159.7, -930.1, 0.5, &rampa_1, TRUE);
					CREATE_OBJECT_NO_OFFSET(ramp, 157.6, -839.8, 0.5, &rampa_2, TRUE);
					CREATE_OBJECT_NO_OFFSET(ramp, 127.4, -692.3, 0.5, &rampa_3, TRUE);
					SET_OBJECT_DYNAMIC(rampa_1, 0);
					SET_OBJECT_DYNAMIC(rampa_2, 0);
					SET_OBJECT_DYNAMIC(rampa_3, 0);
					SET_OBJECT_INVINCIBLE(rampa_1, 1);
					SET_OBJECT_INVINCIBLE(rampa_2, 1);
					SET_OBJECT_INVINCIBLE(rampa_3, 1);
					FREEZE_OBJECT_POSITION(rampa_1, 1);
					FREEZE_OBJECT_POSITION(rampa_2, 1);
					FREEZE_OBJECT_POSITION(rampa_3, 1);

					//������ �� ����
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -103.378, -989.718, 1.207 ); // ���� ������� ������
					SET_CAM_POS			( camera, -143.117, -977.164, 3.736);//������������ ������
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					PRINT_STRING_IN_STRING("string", "NE_BOATYARD1", 3000, 1);//Smugglers got rid of their goods during a police chase,
					SetTime(3000);

					PRINT_STRING_IN_STRING("string", "NE_BOATYARD2", 3000, 1);//Pick up the goods in the allowed time before the cops have returned.
					SetTime(3000);

					//������� ������
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );

					PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					SETTIMERA(0);
					while (true)
					{
						SET_TEXT_FONT(4);
						SET_TEXT_COLOUR(235, 115, 18, 255);
						SET_TEXT_SCALE(0.5, 0.7);
						SET_TEXT_EDGE(2, 0, 0, 0, 255);
						SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 3);// 3
						if (TIMERA() > 900)
						{
							break;
						}
						WAIT(0);
					}
					PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					SETTIMERA(0);
					while (true)
					{
						SET_TEXT_FONT(4);
						SET_TEXT_COLOUR(235, 115, 18, 255);
						SET_TEXT_SCALE(0.5, 0.7);
						SET_TEXT_EDGE(2, 0, 0, 0, 255);
						SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 2);// 2
						if (TIMERA() > 900)
						{
							break;
						}
						WAIT(0);
					}
					PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					SETTIMERA(0);
					while (true)
					{
						SET_TEXT_FONT(4);
						SET_TEXT_COLOUR(235, 115, 18, 255);
						SET_TEXT_SCALE(0.5, 0.7);
						SET_TEXT_EDGE(2, 0, 0, 0, 255);
						SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 1);// 1
						if (TIMERA() > 900)
						{
							break;
						}
						WAIT(0);
					}
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
					SETTIMERA(0);
					SETTIMERB(0);

					while (TRUE)
					{
						WAIT(0);
						if ((go == 0) || (go == 1))
						{
							if (go == 0)
							{
								PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
								go = 1;
							}

							SET_TEXT_FONT(4);
							SET_TEXT_COLOUR(235, 115, 18, 255);
							SET_TEXT_SCALE(0.5, 0.7);
							SET_TEXT_EDGE(2, 0, 0, 0, 255);
							SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "GO", 1);// 1
							if (TIMERB() > 900)
							{
								go = 2;
							}
						}
						//============================ HUD ============================
						// ������ ���
						if (TIMERA() > 999)
						{
							time_s -= 1;
							SETTIMERA( 0 );
						}
						if (time_s < 0)
						{
							time_m -= 1;
							time_s = 59;
						}

						// ������
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
						//DRAW_SPRITE( timer, 0.8765625, 0.7838, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// ������ ������� ��������.
						if ((time_m == 0) && (time_s < 16))
						{
							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.156, 0.267);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); // �����:

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// ������

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							SET_TEXT_CENTRE(1);
							if ( time_s > 9 )
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", time_s);// �������
							}
							else
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", time_s);// �������
							}
						}
						else
						{
							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.156, 0.267);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); // �����:

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// ������

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							SET_TEXT_CENTRE(1);
							if ( time_s > 9 )
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", time_s);// �������
							}
							else
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", time_s);// �������
							}
						}

						if ((sound == 0) && (time_s == 15) && (time_m == 0))
						{
							DISABLE_FRONTEND_RADIO();
							while (!(PRELOAD_STREAM("MP_COUNTDOWN")));
							PRELOAD_STREAM("MP_COUNTDOWN");  // ��� ������� �� sounds.dat15, ����� ����� ��������� ������ �� �����
							PLAY_STREAM_FRONTEND();
							sound = 1;
						}

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_OBJECT_COORDINATES(tovar, &tovarX, &tovarY, &tovarZ);
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, tovarX, tovarY, tovarZ, &PlayR);//�������� "����� �� �����������"

						if ((IS_CHAR_IN_ANY_BOAT(GetPlayerPed())) && ( PlayR < 6.5 ))
						{
							all_tovar += 1;
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							if (all_tovar == 2)
							{
								SET_OBJECT_COORDINATES(tovar, -25.20001, -1042.2, 1.095);
							}
							else if (all_tovar == 3)
							{
								SET_OBJECT_COORDINATES(tovar, 71.79999, -1066.6, 1.095);
							}
							else if (all_tovar == 4)
							{
								SET_OBJECT_COORDINATES(tovar, 100, -1145.1, 1.095);
							}
							else if (all_tovar == 5)
							{
								SET_OBJECT_COORDINATES(tovar, 31.70001, -1197.7, 1.095);
							}
							else if (all_tovar == 6)
							{
								SET_OBJECT_COORDINATES(tovar, 120.7, -1182.6, 1.095);
							}
							else if (all_tovar == 7)
							{
								SET_OBJECT_COORDINATES(tovar, 159.7, -1023.2, 1.095);
							}
							else if (all_tovar == 8)
							{
								SET_OBJECT_COORDINATES(tovar, 160.6, -888.534, 1.095);
							}
							else if (all_tovar == 9)
							{
								SET_OBJECT_COORDINATES(tovar, 157.6, -799.034, 1.095);
							}
							else if (all_tovar == 10)
							{
								SET_OBJECT_COORDINATES(tovar, 127.4, -653.234, 1.095);
							}
							else if (all_tovar == 11)
							{
								SET_OBJECT_COORDINATES(tovar, 134.4, -541.4, 1.095);
							}
							else if (all_tovar == 12)
							{
								SET_OBJECT_COORDINATES(tovar, 181, -406.9, 1.095);
							}
							else if (all_tovar == 13)
							{
								SET_OBJECT_COORDINATES(tovar, 348, -233, 1.095);
							}
							else if (all_tovar == 14)
							{
								SET_OBJECT_COORDINATES(tovar, 591, -101, 1.095);
							}
							else if (all_tovar == 15)
							{
								SET_OBJECT_COORDINATES(tovar, 712.0001, 58, 1.095);
							}
							else if (all_tovar == 16)
							{
								SET_OBJECT_COORDINATES(tovar, 843, 264, 1.095);
							}
							else if (all_tovar == 17)
							{
								SET_OBJECT_COORDINATES(tovar, 825.0001, 553, 1.095);
							}
							else if (all_tovar == 18)
							{
								SET_OBJECT_COORDINATES(tovar, 682, 633, 1.095);
							}
							else if (all_tovar == 19)
							{
								SET_OBJECT_COORDINATES(tovar, 627, 363, 1.095);
							}
							else if (all_tovar == 20)
							{
								SET_OBJECT_COORDINATES(tovar, 482, 383, 1.095);
							}
							else if (all_tovar == 21)
							{
								SET_OBJECT_COORDINATES(tovar, 369, 377, 1.095);
							}
							else if (all_tovar == 22)
							{
								SET_OBJECT_COORDINATES(tovar, 340, 600, 1.095);
							}
							else if (all_tovar == 23)
							{
								SET_OBJECT_COORDINATES(tovar, 363, 827, 1.095);
							}
							else if (all_tovar == 24)
							{
								SET_OBJECT_COORDINATES(tovar, 458, 927, 1.095);
							}
							else if (all_tovar == 25)
							{
								SET_OBJECT_COORDINATES(tovar, 629, 936, 1.095);
							}
							else if (all_tovar == 26)
							{
								SET_OBJECT_COORDINATES(tovar, 737.4, 1073.6, 1.095);
							}
						}
						if (all_tovar > 26)
						{
							REMOVE_BLIP(boat_ico);//������� ������ �� ������
							SET_OBJECT_COORDINATES(tovar, -0.36, -0.402, 0.095);
							skip = 2;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							PRINT_STRING_IN_STRING("string", "NETAXI2", 5000, 1);//~r~You're out of time!
							skip = 1;// ���������� ��������
							break;
						}
					}
					// ������ ������ ���
					WAIT(100);
					REMOVE_BLIP(boat_ico);//������� ������ �� ������

					if (sound == 1)
					{
						STOP_STREAM();
						ENABLE_FRONTEND_RADIO();
					}

					RELEASE_TEXTURE( fon );
					RELEASE_TEXTURE( timer );
					REMOVE_TXD( textur );

					MARK_MODEL_AS_NO_LONGER_NEEDED(gruz);//��������� ������
					MARK_MODEL_AS_NO_LONGER_NEEDED(ramp);//��������� ������

					DELETE_OBJECT(&tovar);
					DELETE_OBJECT(&rampa_1);
					DELETE_OBJECT(&rampa_2);
					DELETE_OBJECT(&rampa_3);
					MARK_OBJECT_AS_NO_LONGER_NEEDED(&tovar);
					MARK_OBJECT_AS_NO_LONGER_NEEDED(&rampa_1);
					MARK_OBJECT_AS_NO_LONGER_NEEDED(&rampa_2);
					MARK_OBJECT_AS_NO_LONGER_NEEDED(&rampa_3);

					if (skip == 1)
					{
						SETTIMERA(0); //���������� ������ 
						while (true)
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // ����� ���� ������
							SET_TEXT_SCALE(0.5, 0.6); // ������� ������
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
							SET_TEXT_CENTRE(1); // ����� ����� ������
							DISPLAY_TEXT(0.5, 0.45, "MISSION_FAILED");// ����� "������ ���������"

							WAIT( 0 );
							if ( TIMERA() > 3000 )
							{
								break;
							}
						}
					}
					if (skip == 2)
					{
						if (G_COKERUN == 1)
						{
							DO_SCREEN_FADE_OUT( 500 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -132.401, -966.641, 14.598 ); // ���� ������� ������
							SET_CAM_POS			( camera, -117.879, -968.923, 16.259 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������

							SETTIMERA(0); //���������� ������ 
							while (true)
							{
								SET_TEXT_COLOUR(93, 200, 252, 255); // ����� ���� ������
								SET_TEXT_SCALE(0.5, 0.7); // ������� ������
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
								SET_TEXT_CENTRE(1); // ����� ����� ������
								DISPLAY_TEXT(0.5, 0.45, "BOAT_A2");//BOATYARD ASSET COMPLETED
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}
							// ������ ������
							POINT_CAM_AT_COORD	( camera, -231.592, -952.518, 9.05262 ); // ���� ������� ������
							SET_CAM_POS			( camera, -227.057, -949.979, 11.9171 ); // ������������ ������

							PRINT_STRING_IN_STRING("string", "BOAT_AS", 5000, 1);//~g~The Boatyard will now generate revenue up to a maximum of $2000. Make sure you collect it regularly.
							//������� �ר��� �����
							SETTIMERA(0); //���������� ������ 
							SETTIMERB(0); //���������� ������
							
							uint rId9;
							int temp = 0;
							GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);

							while(true)
							{
								WAIT(0);
								SET_TEXT_RENDER_ID(rId9);
								DRAW_SPRITE( 0, 0.5000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 0, 0, 0, 255 );

								SET_TEXT_SCALE(4.0, 14.5);
								SET_TEXT_DROPSHADOW(45, 45, 45, 255, 0);
								SET_TEXT_COLOUR(51, 184, 18, 255);
								SET_TEXT_FONT(1);
								DISPLAY_TEXT_WITH_NUMBER(0.005, 0.005, "CASH", temp);//����� ����� �� ����������
							
								if ( TIMERA() > 500)
								{
									temp +=3;
									SETTIMERA(0); //���������� ������ 
								}
								if ( TIMERB() > 6000)
								{
									break;
								}
							}
							WAIT( 100 );
							SET_TEXT_RENDER_ID(rId9);
							DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);

							DO_SCREEN_FADE_OUT( 500 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}

							//������� ������
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������
							G_COKERUN = 2;
						}
						SETTIMERA(0); //���������� ������ 
						TRIGGER_MISSION_COMPLETE_AUDIO(1);//����������� ������ �������� "(1)" ������������� ���� �� "...\EFLC\pc\audio\Sfx\gps.rpf\GPS\MISSION_COMPLETE_1" (����� "6" = "SMC6" � ���-�� ������)
						while (true)
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // ����� ���� ������
							SET_TEXT_SCALE(0.5, 0.7); // ������� ������
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
							SET_TEXT_CENTRE(1); // ����� ����� ������
							DISPLAY_TEXT(0.5, 0.45, "MISSION_PASSED");// ����� "������ ���������"

							SET_TEXT_COLOUR(255, 159, 255, 255); // ����� ���� ������
							SET_TEXT_SCALE(0.5, 0.7); // ������� ������
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
							SET_TEXT_CENTRE(1); // ����� ����� ������
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 5000);// +5000$
							
							WAIT( 0 );
							if ( TIMERA() > 4000 )
							{
								break;
							}
						}
						ADD_SCORE( GetPlayerIndex(), +5000 );//��� ������ �����
						sutosave = 1;
					}
					G_ONMISSION = 0;
				}
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(boat_ico);//������� ������ �� ������
				blip_on = 0;
			}
		}
		if (G_COKERUN == 2)
		{
			if ( TIMERC() > 1440)// ����� �����
			{
				if (income < 2000)// ������������ �����
				{
					income +=1;
				}
				SETTIMERC(0); //���������� ������ 
			}
			if (G_COLLECTOR == 7)// ID �������
			{
				income = 0;
				G_COLLECTOR = 0;
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -224.353, -955.881, 6.956, -234.353, -947.881, 13.739, 0 ))
			{
				if (load_mashin == 0)
				{
					GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);
					load_mashin = 1;
				}
				SET_TEXT_RENDER_ID(rId9);
				DRAW_SPRITE( 0, 0.5000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 0, 0, 0, 255 );
				SET_TEXT_SCALE(4.0, 14.5);
				SET_TEXT_DROPSHADOW(45, 45, 45, 255, 0);
				SET_TEXT_COLOUR(51, 184, 18, 255);
				SET_TEXT_FONT(1);
				DISPLAY_TEXT_WITH_NUMBER(0.005, 0.005, "CASH", income);//����� ����� �� ����������
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -229.615, -953.785, -232.615, -950.785, 0))
				{
					if (help == 0)
					{
						PRINT_HELP_FOREVER("NEGETMONEY"); // Press the ~INPUT_PHONE_ACCEPT~ button to cash out.
						help = 1;
					}
					if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//�������� ������-�� ������� "��� �������".
					{
						ADD_SCORE( GetPlayerIndex(), +income );// �������� � ������ �����
						income = 0;
					}
				}
			}
			else
			{
				if (load_mashin == 1) 
				{
					CLEAR_HELP(); // ������� ����� ���������
					WAIT( 100 );
					SET_TEXT_RENDER_ID(rId9);
					DRAW_RECT(0.5, 0.5, 1.0, 1.0, 35, 35, 35, 255);
					load_mashin = 0;
					help = 0;
				}
			}
		}
	}
}
void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	boat_race();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
