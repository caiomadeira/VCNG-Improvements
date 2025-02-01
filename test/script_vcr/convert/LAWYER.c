/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, dialog, textID, help, car1_des, car2_des, car2_des2, sutosave;
float PedX, PedY, PedZ, PedR, bike, in_car, in_cord, stelking, load_all, add_phone, locked;
float sound, soundID, riotID, riotON, skin, vorotaX;
float ped4_ID, ped5_ID, ped6_ID, ped7_ID, ped8_ID, ped9_ID, ped10_ID, ped11_ID, ped12_ID, ped13_ID;
float ped14_ID, ped15_ID, ped16_ID, ped17_ID, ped18_ID, ped19_ID, ped20_ID, ped21_ID, ped22_ID, ped23_ID, ped24_ID;
uint hour, minute, weather;


void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (TIMERA() > time)
		{
			break;
		}
	}
}
void SetSpeech(void)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (!IS_SCRIPTED_CONVERSATION_ONGOING())
		{
			break;
		}
		else if (TIMERA() > 10000)
		{
			break;
		}
	}
}

void LAWYER_1(void)
{
	blip_on = 0;
	sutosave = 0;
	Blip lawyer_ico, Party_ico, lance_car, jury_car1, jury_car2, Riot;
	WAIT(3000);
	while(true)
	{
		WAIT(0);
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
//============================== The Party ======================================
		if ((G_ONMISSION == 0) && (G_LAWYER == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(lawyer_ico, 0);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//������ �� ������ ��������� � ������� ����� "�������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				//--------------- ����� ������ ---------------
				skip = 0; // ���������� ��������
				load_all = 0;
				G_ONMISSION = 1;
				REMOVE_BLIP(lawyer_ico);//������� ������ �� ������
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				
				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				// ������������ ���
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);

				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//������������� �����
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_1A", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("law_1a");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//������������� ������
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//������������� �����

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				ADD_BLIP_FOR_COORD(527.259, -601.747, 4.341, &Party_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(Party_ico, BLIP_CLOTHES_SHOP);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(Party_ico, 0);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(Party_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_SHOP");//������ �� ������ ��������� � ������� ����� "Clothes shop"

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_VR", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "LAW1_1", 5500, 1);//~g~Go get some new threads from Rafael's clothes shop.
				SetTime(2000);

				// ������� ������
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(3250);

				Car car1, car2, car3, car4, car5, car6;
				Ped ped1, ped2;
				Cam camera, camera2, camera3;

				uint PedM1 = MODEL_M_Y_DORK_02;// ������
				uint PedM2 = MODEL_IG_ANNA;// ��������
				uint CarM1 = MODEL_BOBBER;
				uint CarM2 = MODEL_BANSHEE;
				uint CarM3 = MODEL_SUPERGT;
				uint CarM4 = MODEL_INFERNUS;
				uint CarM5 = MODEL_STRETCH;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(100);

				REQUEST_MODEL(CarM5);
				while (!HAS_MODEL_LOADED(CarM5)) WAIT(100);

				REQUEST_MODEL(PedM1);// ������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM2);// ��������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ���� � �������
				CREATE_CAR(CarM1, 286.576, -788.199, 5.801, &car1, TRUE);
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//������ ���� �� ���� ����������

				// ������ ��������� � ����
				CREATE_CAR(CarM2, 196.987, -842.386, 2.732, &car2, TRUE);
				SET_CAR_HEADING(car2, 102.336);
				CREATE_CAR(CarM3, 195.982, -837.659, 2.732, &car3, TRUE);
				SET_CAR_HEADING(car3, -77.664);
				CREATE_CAR(CarM4, 191.256, -818.101, 2.732, &car4, TRUE);
				SET_CAR_HEADING(car4, 102.336);
				CREATE_CAR(CarM5, 191.191, -813.617, 2.732, &car5, TRUE);
				SET_CAR_HEADING(car5, 102.336);

				// ������ ��������
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped2, TRUE);// ������ ����
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 0);

				// ������ ���� �������
				REQUEST_CAR_RECORDING( 2993 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2993 )) WAIT(0);

				//------------------ ������ ����� ������ ------------------
				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( 527.259, -601.747, 4.341, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 527.259, -601.747, 4.341, &PlayR);//�������� "����� �� �����������"
					if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(Party_ico);//������� ������ �� ������
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 530.273, -604.626, 4.197 ); // ���� ������� ������
						SET_CAM_POS			( camera, 522.552, -596.448, 16.414 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 529.623, -603.946, 4.766, 2, -2);// ����� ��� � �����
						SetTime(1000);

						DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						// ������������	
						SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 1, 0);

						FORWARD_TO_TIME_OF_DAY(19, 30);//������������� �����
						SET_CHAR_COORDINATES(GetPlayerPed(), 528.664, -602.916, 4.766);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), 52.9);
						SetTime(200);
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������

						// ���� ������
						CREATE_CAM( 3, &camera2 );
						CREATE_CAM( 14, &camera3 );
						POINT_CAM_AT_COORD	( camera, 528.442, -602.798, 4.56 ); // ���� ������� ������
						SET_CAM_POS			( camera, 527.141, -601.545, 5.08 );//������������ ������
						POINT_CAM_AT_COORD	( camera3, 528.442, -602.798, 5.839 ); // ���� ������� ������
						SET_CAM_POS			( camera3, 527.141, -601.545, 5.08 );//������������ ������
						SET_CAM_INTERP_STYLE_CORE( camera2, camera, camera3, 3500, 0 ); //����������� ������ �� ������ �� ����� ��������� � ����������� "SET_CAM_POS(camera, X, Y, Z)" 
						SET_CAM_ACTIVE( camera2, 1 );
						SET_CAM_PROPAGATE( camera2, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);

						SetTime(800);
						CLEAR_AREA(527.259, -601.747, 4.341, 80.5, 1);//������� ���� ��������
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2993, 0.0, 0.0, 0.0);// ������� ���������
						SetTime(3200);
						
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						DESTROY_CAM( camera2 );
						DESTROY_CAM( camera3 );

						// ����� ������� ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 529.848, -602.708, 5.331 ); // ���� ������� ������
						SET_CAM_POS			( camera, 507.329, -603.689, 5.273 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SetTime(1000);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BE", "LAW1_12", 0, 0);//Hmmmm...nice bike.
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2000);

						STOP_PLAYBACK_RECORDED_CAR(car1);
						TASK_LEAVE_CAR(ped1, car1);
						TASK_GO_STRAIGHT_TO_COORD(ped1, 508.057, -642.656, 12.069, 2, -2);
						SetTime(2500);

						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "LAW1_2", 5500, 1);//~g~Get to the Colonel's boat.

						ADD_BLIP_FOR_COORD(192.169, -827.01, 2.043, &Party_ico);//������� ������ �� ������
						CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""

						bike = 0;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
				}
				//------------------ ������ ����� ������ ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ((!IS_CHAR_DEAD(ped1)) && (!IS_CHAR_INJURED(ped1)))//���� ����� ���� ��� ����������
						{
							if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (bike == 0))
							{
								bike = 1;
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX1", "LAW1_13", 0, 0);//No! My Bike!
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB( 0 );

								// ��� ��������
								SET_CHAR_HEADING(ped1, -32.106);
								REQUEST_ANIMS( "amb@taxi_hail_m" );
								while (!HAVE_ANIMS_LOADED( "amb@taxi_hail_m" )) WAIT(0);
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "hail_left", "amb@taxi_hail_m", 1.0, 1, 0, 0, 0, 3000 );//���������������� �������� �� ����
							}
							if ((bike == 1) && (TIMERB() > 2000))
							{
								bike = 2;
								CLEAR_PRINTS();
								TASK_COMBAT(ped1, GetPlayerPed());
								PRINT_STRING_IN_STRING("string", "LAW1_2", 5500, 1);//~g~Get to the Colonel's boat.
							}
						}

						if ((load_all == 0) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 182.78, -847.079, 0.41, 210.881, -811.954, 17.658, 0 )))
						{
							load_all = 1;
							MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ������
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//��������� ������ ������
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//��������� ������ ������

							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
							MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
							REMOVE_CAR_RECORDING( 2993 ); // ��������� ���� ����������
						}

						DRAW_CHECKPOINT( 192.169, -827.01, 2.043, 1.8, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 192.169, -827.01, 2.043, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 1.3 )
						{
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// �������� ����� � ������
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car6);
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 189.069, -827.351, 2.732);// ���������� ������
								FIX_CAR(car6);
								SET_CAR_COORDINATES(car6, 194.114, -830.352, 2.732);
								SET_CAR_HEADING(car6, -77.664);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car6);
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 189.069, -827.351, 2.732);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -55.1);
							SET_CHAR_COORDINATES(ped2, 189.147, -825.867, 2.732);// ���������� ���� ��������
							SET_CHAR_HEADING(ped2, -175.0);

							FORCE_WEATHER_NOW(WEATHER_SUNNY);
							FORWARD_TO_TIME_OF_DAY(20, 30);//������������� �����

							//------------ �������� ----------------
							LOAD_ADDITIONAL_TEXT( "LAW_1B", 6 ); // ��������� �������� �� *.GTX
							START_CUTSCENE_NOW("law_1b");
							while (!HAS_CUTSCENE_LOADED())
							{
								WAIT(0);
							}

							DO_SCREEN_FADE_IN(0);
							while (!HAS_CUTSCENE_FINISHED())
							{
								WAIT(0);
							}

							if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
							{
								DO_SCREEN_FADE_IN(0);
							}

							FORWARD_TO_TIME_OF_DAY(04, 35);//������������� �����
							RELEASE_WEATHER();
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							ADD_BLIP_FOR_COORD(534.054, -946.33, 4.189, &Party_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""
							PRINT_STRING_IN_STRING("string", "LAW1_3", 5500, 1);//~g~Take the Colonel's daughter to the Pole Position club.
							in_car = 0;
							stelking = 0;
							dialog = 0;
							textID = 0;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				//------------------ ������ ����� ������ ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						// �������� ��������� �� �����
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car6);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car6, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped2, car6);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car6);
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car6, 0);
							}
							if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+5, PedY+5, PedZ+5, PedX-5, PedY-5, PedZ-5, 0 ))
								{
									TASK_GO_STRAIGHT_TO_COORD(ped2, PlayX, PlayY, PlayZ, 4, -2);
								}
							}
							if (stelking == 1)
							{
								stelking = 0;
							}
						}
						else
						{
							if (stelking == 0)
							{
								stelking = 1;
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX, PedY, PedZ, 4, -2);
								PRINT_STRING_IN_STRING("string", "NE_LEFT", 5500, 1);//~g~You left the colonels daughter, come back for her.
							}
						}
						// ������ � ����������
						if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (dialog == 0))
						{
							if (IS_CHAR_ON_ANY_BIKE(GetPlayerPed())) // � ���������
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX2", "NE_BIKE", 0, 0);//Wow, I like your motorcycle.
								START_SCRIPT_CONVERSATION(1, 1);
								dialog = 1;
								textID = 2;
							}
							else // � ������
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX3", "LAW1_5", 0, 0);//Will you be working for my father?
								START_SCRIPT_CONVERSATION(1, 1);
								dialog = 2;
								textID = 2;
							}
						}
						if (dialog == 1)
						{
							if (textID == 2)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX3", "LAW1_5", 0, 0);//Will you be working for my father?
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 3;
								}
							}
							else if (textID == 3)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF", "LAW1_6", 0, 0);//Maybe.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 4;
								}
							}
							else if (textID == 4)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF_XXX1", "LAW1_9", 0, 0);//It's so difficult having a rich and powerful father. Vamos.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 5;
								}
							}
							else if (textID == 5)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									CLEAR_PRINTS();
									textID = 6;
								}
							}
						}
						else if (dialog == 2)
						{
							if (textID == 2)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF", "LAW1_6", 0, 0);//Maybe.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 3;
								}
							}
							else if (textID == 3)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF_XXX2", "LAW1_7", 0, 0);//Do you mind me resting my hand in your lap?
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 4;
								}
							}
							else if (textID == 4)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF", "LAW1_8", 0, 0);//Maybe.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 5;
								}
							}
							else if (textID == 5)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF_XXX1", "LAW1_9", 0, 0);//It's so difficult having a rich and powerful father. Vamos.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 6;
								}
							}
							else if (textID == 6)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									CLEAR_PRINTS();
									textID = 7;
								}
							}
						}

						DRAW_CHECKPOINT( 534.054, -946.33, 4.189, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 534.054, -946.33, 4.189, &PlayR);//�������� "����� �� �����������"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 534.054, -946.33, 4.189, &PedR);//�������� "����� �� �����������"
						if (( PlayR < 1.5 ) && ( PedR < 1.5 ))
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							// ����������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// ��������� ��� � �����
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped2, 533.717, -943.083, 4.834);// ���������� ����
							}
							else
							{
								SET_CHAR_COORDINATES(ped2, 533.717, -943.083, 4.834);// ���������� ���� ��������
							}
							TASK_GO_STRAIGHT_TO_COORD(ped2, 524.137, -930.173, 4.834, 2, -2);

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 535.314, -937.212, 8.304); // ���� ������� ������
							SET_CAM_POS			( camera, 519.49, -951.657, 4.995 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SetTime(200);
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
							SetTime(500);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BG", "LAW1_10", 0, 0);//See you around, handsome!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// ����� ������� ������
							POINT_CAM_AT_COORD	( camera, 524.911, -931.449, 6.039 ); // ���� ������� ������
							SET_CAM_POS			( camera, 533.056, -941.08, 4.889 );//������������ ������

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BH", "LAW1_11", 0, 0);//I'm sure you will..
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							//������� ������
							SetTime(4000);
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							SET_CHAR_COORDINATES(ped2, 19.147, -5.867, 12.732);// ���������� ���� ��������
							skip = 2;// ���������� ��������
							CLEAR_PRINTS();
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//���� ����� ���� ��� ����������
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							EXPLODE_CHAR_HEAD(ped2);
							PRINT_STRING_IN_STRING("string", "LAW1_4", 5500, 1);//~r~You killed the Colonel's daughter!
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				// ������ ������ ���
				ABORT_SCRIPTED_CONVERSATION( 0 );
				REMOVE_BLIP(Party_ico);//������� ������ �� ������
				if (load_all == 0)
				{
					MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ������
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//��������� ������ ������
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//��������� ������ ������
					MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
					REMOVE_CAR_RECORDING( 2993 ); // ��������� ���� ����������
				}
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������

				if (car6 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//��������� ������ ������(� ����������� ������ ��������)
				}
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
				else if (skip == 2)
				{
					PRINT_HELP("NECLOTH1"); //Soiree outfit delivered to Ocean View Hotel on Ocean Beach.
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 100);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +100 );//��� ������ �����
					G_LAWYER = 2;
					sutosave = 1;
				}

				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
//============================== Back Alley Brawl ======================================
		else if ((G_ONMISSION == 0) && (G_LAWYER == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//������ �� ������ ��������� � ������� ����� "�������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				//--------------- ����� ������ ---------------
				G_ONMISSION = 1;
				skip = 0;// ���������� ��������
				add_phone = 0;
				in_cord = 0;
				textID = 0;
				in_car = 0;
				help = 0;
				locked = 1;
				REMOVE_BLIP(lawyer_ico);//������� ������ �� ������
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				
				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 1, 0);

				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//������������� �����
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_2A", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("law_2a");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//������������� ������
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//������������� �����
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				ADD_BLIP_FOR_COORD(925.599, 453.827, 5.389, &Party_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "���������� ������"
				PRINT_STRING_IN_STRING("string", "LAW2_6", 5500, 1);//~g~Go to the Malibu Club and find Kent Paul.

				Car car1;
				Pickup mob_phone;
				Ped ped1, ped2, ped3, ped4, ped5;
				Cam camera, camera2, camera3;
				Object trubka_1;
				int dm, cdm;

				uint PedM1 = MODEL_M_M_KOREACOOK_01;// ����� - ���� 
				uint PedM2 = MODEL_M_M_SHORTORDER;// ����� m_m_koreacook_01 
				uint PedM3 = MODEL_IG_LILJACOB;// ����
				uint CarM1 = MODEL_INFERNUS;
				uint trubka = vc_mob_phone;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				REQUEST_MODEL(PedM1);// ����� - ����
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM2);// �����
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM3);// ����
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ �����
				CREATE_CHAR (26, PedM1, 281.145, -791.79, 5.445, &ped1, TRUE);// ������ ������ �����
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped2, TRUE);// ������ ������ 1
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped3, TRUE);// ������ ������ 2
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped4, TRUE);// ������ ������ 3
				CREATE_CHAR (26, PedM3, 281.145, -791.79, 5.445, &ped5, TRUE);// // ������ �����

				//������ ������ �����
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				CREATE_CAR(CarM1, 196.987, -842.386, 2.732, &car1, TRUE);
				SET_CAR_HEADING(car1, 102.336);
				LOCK_CAR_DOORS(car1, 3); //��������� ����� ���������� ��� ������
				CHANGE_CAR_COLOUR( car1, 112, 112 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//���� ��������� ������

				// ������ ����
				REQUEST_CAR_RECORDING( 2994 );// ������ ���� ����� �������
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2994 )) WAIT(0);
				REQUEST_CAR_RECORDING( 2995 );// ������ ���� ����� ����
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2995 )) WAIT(0);

				// ������ �������
				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, -1.1, &trubka_1, TRUE);

				//------------------ ������ ����� ������ ------------------
				while (TRUE)
				{
					// ���� ������
					WAIT(0);
					DRAW_CHECKPOINT( 925.599, 453.827, 5.389, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 925.599, 453.827, 5.389, &PlayR);//�������� "����� �� �����������"
					if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 923.279, 454.929, 6.108); // ���� ������� ������
						SET_CAM_POS			( camera, 936.918, 437.017, 6.893 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 921.141, 457.901, 5.688, 2, -2);//����� ��� � ����

						// ����������
						REMOVE_BLIP(Party_ico);//������� ������ �� ������
						DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						SetTime(200);
						SET_CHAR_COORDINATES(GetPlayerPed(), 925.06, 453.041, 5.763);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), -128.321);

						//������� ������
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );

						//------------ �������� ��� ----------------
						LOAD_ADDITIONAL_TEXT( "LAW_2B", 6 ); // ��������� �������� �� *.GTX
						START_CUTSCENE_NOW("law_2b");
						while (!HAS_CUTSCENE_LOADED())
						{
							WAIT(0);
						}

						DO_SCREEN_FADE_IN(0);
						while (!HAS_CUTSCENE_FINISHED())
						{
							WAIT(0);
						}

						if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
						{
							DO_SCREEN_FADE_IN(0);
						}

						ADD_BLIP_FOR_COORD(869.546, -37.984, 5.566, &Party_ico);//������� ������ �� ������
						CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
						CHANGE_BLIP_COLOUR(Party_ico, 19);  //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "���������� ������"
						PRINT_STRING_IN_STRING("string", "LAW2_7", 5500, 1);//~g~Go and find the chef on Ocean Drive.

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
						SET_CHAR_COORDINATES(ped1, 869.546, -37.984, 4.853);// ���������� ������-�����
						SET_CHAR_HEADING(ped1, 56.323);

						// �������� ��������� �� ��������
						ATTACH_OBJECT_TO_PED( trubka_1, ped1, 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );
						REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
						while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
				}
				if (skip == 0)
				{
				//------------------ ������ ����� ������ ------------------
					while (TRUE)
					{
						// ����� � ��������
						WAIT(0);
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 869.546, -37.984, 5.566, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 15.3)
						{
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 868.909, -38.109, 5.991); // ���� ������� ������
							SET_CAM_POS			( camera, 871.836, -37.408, 6.237 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 879.131, -26.629, 5.39);// ���������� ������
								SET_CHAR_HEADING(GetPlayerPed(), 156.233);
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 872.062, -31.654, 4.918);// ���������� ������
							}
							else
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 872.062, -31.654, 4.918);// ���������� ������
								SET_CHAR_HEADING(GetPlayerPed(), 154.994);
							}

							SetTime(800);
							SET_CHAR_HEADING(ped1, -15.994);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "cellphone_out", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
							SetTime(1000);
							DETACH_OBJECT( trubka_1, 1 );
							SET_OBJECT_COORDINATES(trubka_1, 1.1, 1.1, -1.1);

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 870.175, -36.652, 4.918, 2, -2);//����� ��� � ������ - �����
							SetTime(200);

							// ������ ������
							POINT_CAM_AT_COORD	( camera, 870.603, -38.014, 4.678); // ���� ������� ������
							SET_CAM_POS			( camera, 867.869, -25.671, 8.817 );//������������ ������

							// ������ ���
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BH_XXX2", "LAW2_1", 0, 0);//Hey, whatchoo lookin' at?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

// �������� ��������� ���

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI", "LAW2_2", 0, 0);//You better start talking..
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

// �������� ��������� ���

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI_XXX1", "LAW2_3", 0, 0);//Hey, make me, you prick!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							//������� ������
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

							// ��� ������� ���������� �������
							ADD_BLIP_FOR_CHAR(ped1, &Party_ico);
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(Party_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "MO_TARGET");//������ �� ������ "�������"
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������

							// ����� ������� ������
							SetTime(200);
							CLEAR_PRINTS();
							SET_SENSE_RANGE(ped1, 50.0);
							SET_CHAR_DECISION_MAKER(ped1, dm);
							SET_COMBAT_DECISION_MAKER(ped1, cdm);
							SET_CHAR_HEALTH(ped1, 200);
							SET_CHAR_KEEP_TASK(ped1, 1);
							TASK_COMBAT(ped1, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 0);
							SetTime(3000);

							while (TRUE)
							{
								WAIT(0);
								if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)))//���� ��� ���� ��� �����
								{
									EXPLODE_CHAR_HEAD(ped1);
									REMOVE_BLIP(Party_ico);//������� ������ �� ������

									// �� ���� �������� �������
									PRINT_STRING_IN_STRING("string", "LAW2_11", 5500, 1);//~g~Pick up his cell phone.
									GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
									GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
									CREATE_PICKUP( vc_phone_pick_up, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &mob_phone, 0 );// �������

									ADD_BLIP_FOR_PICKUP(mob_phone, &Party_ico);
									CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
									CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "���������� ������"
									add_phone = 1;
									break;
								}
								GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+20, PedY+20, PedZ+20, PedX-20, PedY-20, PedZ-20, 0 ))// ���� ����� ������ �� ������
								{
									PRINT_STRING_IN_STRING("string", "NE_FIGHT", 5500, 1);//~r~Are you afraid of a fight?
									skip = 1;// ���������� ��������
									break;
								}
								else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
								{
									skip = 1;// ���������� ��������
									break;
								}
							}
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)))//���� ����� ���� ��� ����������
						{
							EXPLODE_CHAR_HEAD(ped1);
							DETACH_OBJECT( trubka_1, 1 );
							SET_OBJECT_COORDINATES(trubka_1, 1.1, 1.1, -1.1);

							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							if (add_phone == 0)
							{
								// �� ���� �������� �������
								PRINT_STRING_IN_STRING("string", "LAW2_11", 5500, 1);//~g~Pick up his cell phone.
								GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
								GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
								CREATE_PICKUP( vc_phone_pick_up, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &mob_phone, 0 );// �������

								ADD_BLIP_FOR_PICKUP(mob_phone, &Party_ico);
								CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
								CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "���������� ������"
								add_phone = 1;
							}
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				//------------------ ������ ����� ������ ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// ������� �������
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( mob_phone ))
						{
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							PRINT_HELP_FOREVER("LAW2_12"); //Cell phone acquired! You can now receive phone calls.
							SetTime(1000);

							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							CLEAR_HELP(); // ������� ����� ���������

							// ������ ������
							GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_PISTOL, 14, FALSE);
							SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_PISTOL, TRUE);

							UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_3);
							UpdateWeaponOfPed(ped3, WEAPON_KNIFE);
							UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_3);
							UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_3, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_KNIFE, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_3, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);

							// ������������� ������
							SET_CHAR_COORDINATES(GetPlayerPed(), 867.67, -38.887, 4.918);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -21.819);

							// ������������� �����
							SET_CHAR_COORDINATES(ped5, 867.607, -41.114, 4.918);// ���������� �����
							SET_CHAR_HEADING(ped5, 154.994);

							// ������������� ���������� �����
							SET_CAR_COORDINATES(car1, 867.521, -116.042, 5.519);// ���������� ���������� �����
							SET_CAR_HEADING(car1, 156.233);
							FREEZE_CAR_POSITION(car1, 1);

							// ������������� �������
							SET_CHAR_COORDINATES(ped2, 871.851, -33.606, 4.918);// ���������� ������1
							SET_CHAR_HEADING(ped2, 154.994);

							SET_CHAR_COORDINATES(ped3, 870.694, -32.833, 4.918);// ���������� ������2
							SET_CHAR_HEADING(ped3, 154.994);

							SET_CHAR_COORDINATES(ped4, 869.312, -32.151, 4.918);// ���������� ������3
							SET_CHAR_HEADING(ped4, 154.994);
							SetTime(500);

							ADD_BLIP_FOR_CHAR(ped5, &Party_ico);
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(Party_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_LANCE");//������ �� ������ "�������"
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������

							ADD_BLIP_FOR_CAR(car1, &lance_car);
							CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(lance_car, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "NE_CAR");//������ �� ������ "�������"
							CHANGE_BLIP_SCALE(lance_car, 0.6); // ������� ������ �� ������

							//------------ �������� ��� ----------------
							LOAD_ADDITIONAL_TEXT( "LAW_2C", 6 ); // ��������� �������� �� *.GTX
							START_CUTSCENE_NOW("law_2c");
							while (!HAS_CUTSCENE_LOADED())
							{
								WAIT(0);
							}

							DO_SCREEN_FADE_IN(0);
							while (!HAS_CUTSCENE_FINISHED())
							{
								WAIT(0);
							}

							if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
							{
								DO_SCREEN_FADE_IN(0);
							}

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 870.993, -32.916, 5.651 ); // ���� ������� ������
							SET_CAM_POS			( camera, 864.445, -44.067, 6.119 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SetTime(2000);

							// ����� �������
							POINT_CAM_AT_COORD	( camera, 864.085, -44.291, 5.505 ); // ���� ������� ������
							SET_CAM_POS			( camera, 869.913, -35.165, 5.837 );//������������ ������

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI_XXX2", "LAW2_4", 0, 0);//This way!
							START_SCRIPT_CONVERSATION(1, 1);
							TASK_GO_STRAIGHT_TO_COORD(ped5, 838.004, -103.263, 4.918, 4, -2);//���� ����� � ������ �����
							SetSpeech();

							//������� ������
							SetTime(500);
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

							SET_SENSE_RANGE(ped2, 50.0);
							SET_CHAR_DECISION_MAKER(ped2, dm);
							SET_COMBAT_DECISION_MAKER(ped2, cdm);
							SET_CHAR_HEALTH(ped2, 200);
							SET_CHAR_KEEP_TASK(ped2, 1);
							TASK_COMBAT(ped2, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 0);

							SET_SENSE_RANGE(ped3, 50.0);
							SET_CHAR_DECISION_MAKER(ped3, dm);
							SET_COMBAT_DECISION_MAKER(ped3, cdm);
							SET_CHAR_HEALTH(ped3, 200);
							SET_CHAR_KEEP_TASK(ped3, 1);
							TASK_COMBAT(ped3, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 0);

							SET_SENSE_RANGE(ped4, 50.0);
							SET_CHAR_DECISION_MAKER(ped4, dm);
							SET_COMBAT_DECISION_MAKER(ped4, cdm);
							SET_CHAR_HEALTH(ped4, 200);
							SET_CHAR_KEEP_TASK(ped4, 1);
							TASK_COMBAT(ped4, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 0);
							CLEAR_PRINTS();
							SetTime(6000);
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				//------------------ �������� ����� ������ ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// ����� � ������
						WAIT(0);
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//��������� ���������� ���� � ����������
						if (in_cord == 0)
						{
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 838.004, -103.263, 4.918, &PedR);//�������� "��� �� �����������"
							if ( PedR < 1.3)
							{
								TASK_GO_STRAIGHT_TO_COORD(ped5, 867.269, -115.923, 5.519, 4, -2);//���� ����� �� ������ �����
								in_cord = 1;
							}
						}
						else if (in_cord == 1)
						{
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 867.269, -115.923, 5.519, &PedR);//�������� "��� �� �����������"
							if ( PedR < 5.3)
							{
								TASK_ENTER_CAR_AS_PASSENGER(ped5, car1, -1, 0);
								in_cord = 2;
								SETTIMERB(0); //���������� ������ 
							}
						}

						if (locked == 1)
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 868.855, -116.292, 5.08047, &PlayR);//�������� "����� �� �����������"
							if ( PlayR < 1.5)
							{
								FREEZE_CAR_POSITION(car1, 0);
								LOCK_CAR_DOORS(car1, 1); //������������ ����� ���������� ��� ������
								locked = 0;
							}
						}

						if ((IS_CHAR_SITTING_IN_ANY_CAR(ped5)) && (in_cord == 2))
						{
							PRINT_STRING_IN_STRING("string", "NE_IN_CAR", 5500, 1);//~g~Get in the car.
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							in_cord = 3;
						}
						else if (( TIMERB() > 10000 ) && (in_cord == 2) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped5)))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car1, 0);
						}

						if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped5)))
						{
							REMOVE_BLIP(lance_car);//������� ������ �� ������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_INJURED(ped5)))//���� ���� ����
						{
							skip = 1;// ���������� ��������
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							break;
						}
					}
				}
				//------------------ ������ ����� ������ ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// ��������� �������
						WAIT(0);
						if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 0))
						{
							// ������ ���
							SetTime(2000);
							CLOSE_ALL_CAR_DOORS(car1);
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI_XXX3", "LAW2_16", 0, 0);//One thing you gotta realize about this town. You gotta pack some heat.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BJ", "LAW2_17", 0, 0);//C'mon, the local gun shop's a couple of blocks away.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// ������ ���� ��������
							SetTime(1000);
							ADD_BLIP_FOR_COORD(379.082, -948.858, 4.217, &Party_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_WEAPONS);//�������� ������ �� ������
							CHANGE_BLIP_SCALE(Party_ico, 1.1); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "Ammu-Nation"
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "LAW2_15", 5500, 1);//~g~Go to Ammu-Nation.
							textID = 1;
						}

						if ((!IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 0))
						{
							in_car = 1;
							// ������� � ������
							PRINT_STRING_IN_STRING("string", "IN_VEH", 5500, 1);//~g~Hey! Get back in the vehicle!
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							ADD_BLIP_FOR_CAR(car1, &lance_car);
							CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(lance_car, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "NE_CAR");//������ �� ������ "�������"
							CHANGE_BLIP_SCALE(lance_car, 0.6); // ������� ������ �� ������
						}
						else if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 1))
						{
							in_car = 0;
							// ����� � ��������� �������
							PRINT_STRING_IN_STRING("string", "LAW2_15", 5500, 1);//~g~Go to Ammu-Nation.
							REMOVE_BLIP(lance_car);//������� ������ �� ������
							ADD_BLIP_FOR_COORD(379.082, -948.858, 4.217, &Party_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_WEAPONS);//�������� ������ �� ������
							CHANGE_BLIP_SCALE(Party_ico, 1.1); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "Ammu-Nation"
						}

						if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
						{
							DRAW_CHECKPOINT( 379.082, -948.858, 4.217, 2.5, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 379.082, -948.858, 4.217, &PlayR);//�������� "����� �� �����������"
							if (( PlayR < 2.1) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
							{
								ABORT_SCRIPTED_CONVERSATION( 0 );
								//��������� Ammu-Nation
								REMOVE_BLIP(Party_ico);//������� ������ �� ������
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

								DO_SCREEN_FADE_OUT( 500 );// ��������� �����
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())
									{
										break;
									}
								}
								// ������ ������
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, 369.507, -948.653, 5.431); // ���� ������� ������
								SET_CAM_POS			( camera, 379.696, -946.602, 6.501 );//������������ ������
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������
								SETTIMERA( 0 );
								help = 0;
								// ������ ��������� 1
								PRINT_HELP_FOREVER("LAW3_11"); //Stand in the ~q~pink marker~w~ to view the weapons on offer.

								while(true)
								{
									WAIT(0);
									if ((IS_GAME_KEYBOARD_KEY_PRESSED(GAME_KEY_ESC)) || (help == 69) || (IS_GAME_KEYBOARD_KEY_PRESSED(57)) || (IS_GAME_KEYBOARD_KEY_PRESSED(42)) || (IS_GAME_KEYBOARD_KEY_PRESSED(54)) ||(IS_GAME_KEYBOARD_KEY_PRESSED(28)))
									{

										help = 99;
										break;
									}
									if ((TIMERA() > 3500) && (help == 0))
									{
										// ������ ��������� 2
										PRINT_HELP_FOREVER("LAW3_12"); //You can select weapons by pressing ~h~left~w~ or ~h~right~w~ on the ~h~directional button.
										POINT_CAM_AT_COORD	( camera, 369.387, -955.835, 7.097); // ���� ������� ������
										SET_CAM_POS			( camera, 370.659, -945.036, 7.113 );//������������ ������
										SETTIMERA( 0 );
										help = 1;
									}
									else if ((TIMERA() > 3500) && (help == 1))
									{
										// ������ ��������� 3
										PRINT_HELP_FOREVER("LAW3_13"); //If you have enough cash you can buy weapons by pressing the ~h~~k~~PED_SPRINT~ ~w~button.
										POINT_CAM_AT_COORD	( camera, 367.628, -956.467, 7.645); // ���� ������� ������
										SET_CAM_POS			( camera, 372.485, -945.471, 6.522 );//������������ ������
										SETTIMERA( 0 );
										help = 2;
									}
									else if ((TIMERA() > 3500) && (help == 2))
									{
										// ������ ��������� 4
										PRINT_HELP_FOREVER("LAW3_14"); //You can exit the shop by pressing the ~h~~k~~VEHICLE_ENTER_EXIT~ ~w~button.
										POINT_CAM_AT_COORD	( camera, 372.263, -950.477, 4.784); // ���� ������� ������
										SET_CAM_POS			( camera, 366.303, -942.803, 7.469 );//������������ ������
										SETTIMERA( 0 );
										help = 3;
									}
									else if ((TIMERA() > 3500) && (help == 3))
									{
										// ������ ��������� 5
										PRINT_HELP_FOREVER("HELP46"); //There are eight different types of weapon.
										POINT_CAM_AT_COORD	( camera, 369.387, -955.835, 7.097); // ���� ������� ������
										SET_CAM_POS			( camera, 370.659, -945.036, 7.113 );//������������ ������
										SETTIMERA( 0 );
										help = 4;
									}
									else if ((TIMERA() > 3500) && (help == 4))
									{
										// ������ ��������� 6
										PRINT_HELP_FOREVER("HELP47"); //You can carry one of each type of weapon at a time - one type of pistol, one type of shotgun.
										POINT_CAM_AT_COORD	( camera, 367.628, -956.467, 7.645); // ���� ������� ������
										SET_CAM_POS			( camera, 372.485, -945.471, 6.522 );//������������ ������
										SETTIMERA( 0 );
										help = 5;
									}
									else if ((TIMERA() > 3500) && (help == 5))
									{
										help = 69;
									}
								}
								//������� ������
								DO_SCREEN_FADE_OUT( 500 );// ��������� �����
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())
									{
										break;
									}
								}
								CLEAR_HELP(); // ������� ����� ���������
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								DESTROY_CAM( camera );
								SET_WIDESCREEN_BORDERS( 0 );
								DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

								PRINT_STRING_IN_STRING("string", "LAW2_10", 5500, 1);//~g~Drive back to the hotel.
								REMOVE_BLIP(lance_car);//������� ������ �� ������
								ADD_BLIP_FOR_COORD(671.379, -747.318, 4.727, &Party_ico);//������� ������ �� ������
								CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
								CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "hotel"

								in_car = 0;
								break;
							}
						}

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped5))//���� ���� ����� �� ������ �� ������� ���
						{
							skip = 1;// ���������� ��������
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							break;
						}
						else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_INJURED(ped5)))//���� ���� ����
						{
							skip = 1;// ���������� ��������
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							break;
						}
					}
				}
				//------------------ ������ ����� ������ ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// �����
						WAIT(0);
						if ((!IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 0))
						{
							in_car = 1;
							// ������� � ������
							PRINT_STRING_IN_STRING("string", "IN_VEH", 5500, 1);//~g~Hey! Get back in the vehicle!
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							ADD_BLIP_FOR_CAR(car1, &lance_car);
							CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(lance_car, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "NE_CAR");//������ �� ������ "�������"
							CHANGE_BLIP_SCALE(lance_car, 0.6); // ������� ������ �� ������
						}
						else if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 1))
						{
							in_car = 0;
							// ����� � ��������� �������
							PRINT_STRING_IN_STRING("string", "LAW2_10", 5500, 1);//~g~Drive back to the hotel.
							REMOVE_BLIP(lance_car);//������� ������ �� ������
							ADD_BLIP_FOR_COORD(671.379, -747.318, 4.727, &Party_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(Party_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "hotel"
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 653.863, -795.02, 1.962, 703.863, -695.02, 26.962, 0 )) && (IS_CHAR_IN_CAR(GetPlayerPed(), car1)))
						{
							// ����������
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							SET_CAR_DENSITY_MULTIPLIER(0);// ��������� ����
							CLEAR_AREA_OF_CARS( 680.758, -755.964, 1.154, 100.0 );

							// ��������� ���� �������
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2994, 0.0, 0.008, -0.128);// ��������� ���� �������

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 674.017, -740.841, 6.473); // ���� ������� ������
							SET_CAM_POS			( camera, 670.527, -752.394, 5.354 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
							CLEAR_AREA(674.2433, -750.8853, 4.501233, 6.5, 0);//������� ���� ��������


							SetTime(3000);
							TASK_LEAVE_CAR(GetPlayerPed(), car1);// ���������� �����
							SetTime(3000);

							// ����� ������� ������
							POINT_CAM_AT_COORD	( camera, 675.293, -747.194, 5.183 ); // ���� ������� ������
							SET_CAM_POS			( camera, 673.211, -737.637, 8.129 );//������������ ������

							// �������� ��������� �����
							REQUEST_ANIMS( "veh@low" );//��������� ���� � ���������
							while (!HAVE_ANIMS_LOADED( "veh@low" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "shuffle_seat_ps", "veh@low", 1.0, 0, 0, 0, 1, -1 );//���������������� �������� �� ����
							SetTime(1500);

							// ����������� ������
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BK", "LAW2_5", 0, 0);//I'm going to go see what I can dig up. I'll be watching you, Tommy.
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(4200);

							// ����� ������� ������
							CLEAR_PRINTS();
							POINT_CAM_AT_COORD	( camera, 676.609, -746.077, 4.005 ); // ���� ������� ������
							SET_CAM_POS			( camera, 674.922, -722.211, 7.108 );//������������ ������

							// ��������� ���� �����
							STOP_PLAYBACK_RECORDED_CAR(car1);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2995, 0.0, 0.008, -0.128);// ��������� ���� �����
							SetTime(5800);
							STOP_PLAYBACK_RECORDED_CAR(car1);
							SET_CHAR_COORDINATES(ped5, 19.147, -5.867, 12.732);// ���������� ����

							//������� ������
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							SET_CAR_DENSITY_MULTIPLIER(1);// ���������� ����

							skip = 2;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							break;
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped5))//���� ���� ����� �� ������ �� ������� ���
						{
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_INJURED(ped5)))//���� ���� ����
						{
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							skip = 1;
							break;
						}
					}
				}


				ABORT_SCRIPTED_CONVERSATION( 0 );
				REMOVE_BLIP(Party_ico);//������� ������ �� ������
				REMOVE_BLIP(lance_car);//������� ������ �� ������

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);

				// ��������� �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);

				// ��������� ����������
				REMOVE_CAR_RECORDING( 2994 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 2995 ); // ��������� ���� ����������

				//������� ��������� ������� ���
				REMOVE_PICKUP(mob_phone);
				DELETE_OBJECT( &trubka_1 );

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
				else if (skip == 2)
				{
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 200);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +200 );//��� ������ �����
					G_LAWYER = 3;
					G_MAIN_CALL = 1;
					sutosave = 1;
				}
				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
//============================== Jury Fury ======================================
		else if ((G_ONMISSION == 0) && (G_LAWYER == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//������ �� ������ ��������� � ������� ����� "�������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				skip = 0; // ���������� ��������
				help = 0;
				car1_des = 0;
				car2_des = 0;
				car2_des2 = 0;
				G_ONMISSION = 1;
				REMOVE_BLIP(lawyer_ico);//������� ������ �� ������
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				
				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 2, 0); // Modifiquei aqui
				
				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6;
				Pickup sweap_1, sweap_2;
				uint car1_HP, car2_HP, ped2_HP, ped3_HP;
				uint dialogID;
				Cam camera;

				uint PedM1 = MODEL_M_M_GTRI_HI_01;// ��������� 1
				uint PedM2 = MODEL_M_M_BUSINESS_03;// ��������� 2
				uint PedM3 = MODEL_F_M_PJERSEY_01;// ���������� ����������� 2
				uint PedM4 = MODEL_M_M_SWEEPER;// ������ ��������
				uint PedM5 = MODEL_M_M_GRU2_HI_02;// �������� ����������
				uint PedM6 = MODEL_IG_TUNA;// �������� ���������

				uint CarM1 = MODEL_SENTINEL;// ���������
				uint CarM2 = MODEL_ADMIRAL;// �������
				uint CarM3 = MODEL_MARBELLA;// ���������
				uint CarM4 = MODEL_FXT;// ��������

				// ������ ������
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(100);

				REQUEST_MODEL(PedM1);// ��������� 1
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM2);// ��������� 2
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM3);// ���������� ����������� 2
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM4);// ������ ��������
				while (!HAS_MODEL_LOADED(PedM4));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM5);// �������� ����������
				while (!HAS_MODEL_LOADED(PedM5));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM6);// �������� ���������
				while (!HAS_MODEL_LOADED(PedM6));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ����
				CREATE_CAR(CarM1, 968.689, 749.632, 9.099, &car1, TRUE);// ���������
				CREATE_CAR(CarM2, 618.481, -500.791, 5.058, &car2, TRUE);// �������
				CREATE_CAR(CarM3, 297.061, -779.882, 5.019, &car3, TRUE);// ���������
				CREATE_CAR(CarM4, 283.846, -780.803, 5.019, &car4, TRUE);// ��������
				SET_CAR_HEADING(car1, -91.702);
				SET_CAR_HEADING(car2, 261.36);

				// ��������� ������ ��� ������
				LOCK_CAR_DOORS(car1, 3); //��������� ����� ���������� ��� ������
				LOCK_CAR_DOORS(car2, 3); //��������� ����� ���������� ��� ������
				LOCK_CAR_DOORS(car4, 3); //��������� ����� ���������� ��� ������

				// ������ �����
				CREATE_CHAR (26, PedM1, 290.473, -785.685, 5.19, &ped1, TRUE);// ��������� 1
				CREATE_CHAR (26, PedM2, 623.574, -493.928, 5.386, &ped2, TRUE);// ��������� 2
				CREATE_CHAR (26, PedM3, 623.574, -493.021, 5.386, &ped3, TRUE);// C��������� ����������� 2
				CREATE_CHAR (26, PedM4, 549.677, -288.081, 4.686, &ped4, TRUE);// ������ ��������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM5, &ped5);// �������� ����������
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM6, &ped6);// �������� ���������
				SET_CHAR_HEADING(ped3, 172.928);
				SET_CHAR_HEADING(ped4, 43.279);
				SET_CHAR_HEALTH(ped2, 1000);
				SET_CHAR_HEALTH(ped3, 1000);

				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped4, 1);

				// ������ ���� ����������
				REQUEST_CAR_RECORDING( 2996 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2996 )) WAIT(0);

				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//������������� �����

				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_3", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("law_3");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//������������� ������
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//������������� �����

				// ������ �� ������ ���������
				CLEAR_AREA(549.677, -288.081, 4.686, 80.5, 1);//������� ���� ��������
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 550.738, -288.656, 5.308); // ���� ������� ������
				SET_CAM_POS			( camera, 540.301, -286.913, 7.878 );//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_XF", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				// ����������� ����
				SetTime(1000);
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 2996, 0.0, 0.0, 0.0);
				SetTime(1000);
				SETTIMERA( 0 );

				// ������ ������� ����
				while (TRUE)
				{
					WAIT(0);
					if ((TIMERA() > 3000) || (IS_CHAR_TOUCHING_VEHICLE(ped4, car3))) //��� ���� ������ ������ ����
					{
						EXPLODE_CHAR_HEAD(ped4);
						STOP_PLAYBACK_RECORDED_CAR(car3);
						break;
					}
				}
				// �������� ���������� ����
				GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
				GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
				CREATE_PICKUP_ROTATE(w_hammer, 3, 1, PedX, PedY, PedZ, -87.532, -108.556, 8.524, &sweap_1);// ������ ���� 
				CREATE_PICKUP_ROTATE(w_bat, 3, 1, 625.035, -491.01, 5.062, 169.82, -14.625, 4.35, &sweap_2);// ������ ���� 

				SetTime(2000);
				// ������ ������ �� ����
				POINT_CAM_AT_COORD	( camera, 551.371, -288.083, 4.596); // ���� ������� ������
				SET_CAM_POS			( camera, 543.173, -296.107, 6.183 );//������������ ������
				PRINT_STRING_IN_STRING("string", "LAW3_24", 5500, 1);//~g~That hammer would be useful.
				SetTime(4000);

				//������� ������
				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				TASK_LEAVE_CAR(ped5, car3);// ��� ������� �� ����������

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//��������� ������ ������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������

				// ��������� ���� ����������
				REMOVE_CAR_RECORDING( 2996 ); // ��������� ���� ����������

				// ������ ������� ��� �������
				ADD_BLIP_FOR_CAR(car1, &jury_car1);
				CHANGE_BLIP_SPRITE(jury_car1, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(jury_car1, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car1, "NE_CAR");//������ �� ������ "�������"
				CHANGE_BLIP_SCALE(jury_car1, 0.6); // ������� ������ �� ������

				// ������ ������� ��� �����
				ADD_BLIP_FOR_CHAR(ped2, &jury_car2);
				CHANGE_BLIP_SPRITE(jury_car2, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(jury_car2, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car2, "NE_CAR");//������ �� ������ "�������"
				CHANGE_BLIP_SCALE(jury_car2, 0.6); // ������� ������ �� ������

				// ����������� �������
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_BL", "LAW3_7", 0, 0);//~g~Go and intimidate the two jurors, but DON'T kill them!
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();
				//SET_CURRENT_MOVIE( "audio/law3_24" );


				// ������� ������
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(1250);

				//------------------ ������ ����� ������ ------------------
				while (TRUE)
				{
					WAIT(0);
					GET_CAR_HEALTH(car1, &car1_HP);
					GET_CAR_HEALTH(car2, &car2_HP);
					GET_CHAR_HEALTH(ped2, &ped2_HP);
					GET_CHAR_HEALTH(ped3, &ped3_HP);

					// ���� ����� �� ����������� ����� "�������� ������"
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 951.636, 711.794, 6.106, 986.436, 771.794, 21.106, 0 )) && (help == 0))
					{
						PRINT_STRING_IN_STRING("string", "LAW3_20", 5500, 1);//~g~Smash up the Juror's car!
						help = 1;
					}

					// ���� ������ 1 �������
					if ((car1_HP < 5) && (car1_des == 0))
					{

						DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
						REMOVE_BLIP(jury_car1);//������� ������ �� ������
						SET_CHAR_COORDINATES(ped1, 984.8, 727.5, 8.539);// ���������� ����
						SET_CHAR_HEADING(ped1, 46.4);

						// ������ ���
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 984.691, 727.433, 10.274); // ���� ������� ������
						SET_CAM_POS			( camera, 986.126, 723.922, 10.789 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						// �������� ����� � ������
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 958.737, 745.489, 9.099);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -15.013);
							WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 975.0, 740.8, 8.539);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -148.514);
						}
						else
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 975.0, 740.8, 8.539);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -148.514);
						}

						// ����� ��� � ����
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 978.492, 736.038, 9.391, 2, -2);//����� ��� � �����
						SetTime(250);

						// ������������� ������
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BM", "LAW3_21", 0, 0);//I can't believe this is happening!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						GENERATE_RANDOM_INT_IN_RANGE( 1, 12, &dialogID);
						if ((dialogID == 1) || (dialogID == 7))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX1", "LAW3_1", 0, 0);//Giorgio sends his regards.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 2) || (dialogID == 8))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX2", "LAW3_2", 0, 0);//Remember, guilty is a dirty word.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 3) || (dialogID == 9))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 4) || (dialogID == 10))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX1", "LAW3_4", 0, 0);//You know he's not guilty.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 5) || (dialogID == 11))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX2", "LAW3_5", 0, 0);//You remember Giorgio? You remember he's innocent.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 6) || (dialogID == 12))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BO", "LAW3_6", 0, 0);//Not guilty, understand? Good.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}

						// ������ ������
						POINT_CAM_AT_COORD	( camera, 980.528, 733.934, 10.859); // ���� ������� ������
						SET_CAM_POS			( camera, 981.683, 736.051, 10.808 );//������������ ������

						// ��� �������
						TASK_GO_STRAIGHT_TO_COORD(ped1, 968.7, 710.3, 9.391, 4, -2);//��������� �����
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BP", " ", 0, 0);//������
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						//SetTime(2500);

						//������� ������
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

						// ������� ����
						SET_CHAR_COORDINATES(ped1, 290.473, -785.685, 5.19);// ���������� ����
						TASK_GO_STRAIGHT_TO_COORD(ped1, 290.473, -785.685, 5.19, 4, -2);//��������� �����
						car1_des = 1;
					}

					// ���� ������ 2 �������
					if ((car2_HP < 5) && (car2_des == 0))
					{
						DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
						REMOVE_BLIP(jury_car2);//������� ������ �� ������
						SET_CHAR_COORDINATES(ped2, 634.284, -489.079, 4.451);// ���������� ����
						SET_CHAR_HEADING(ped2, 155.144);

						// ������ ���
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 631.786, -494.704, 5.021); // ���� ������� ������
						SET_CAM_POS			( camera, 636.534, -487.072, 6.687 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						// �������� ����� � ������
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), 105.498);
							WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 631.758, -496.799, 4.451);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -7.47);
						}
						else
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 631.758, -496.799, 4.451);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -7.47);
						}

						// ����� ��� � ����
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 632.752, -493.506, 5.386, 2, -2);//����� ��� � �����
						SetTime(250);

						// ��������� ������
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R1_BQ", "NE_LAW3_1", 0, 0);//Man. my car!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// ������ ������
						POINT_CAM_AT_COORD	( camera, 632.427, -490.956, 5.862); // ���� ������� ������
						SET_CAM_POS			( camera, 632.131, -491.902, 5.988 );//������������ ������

						// ��� �������
						TASK_GO_STRAIGHT_TO_COORD(ped2, 638.477, -471.28, 5.386, 4, -2);//��������� �����
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX1", " ", 0, 0);//������
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						//SetTime(3000);

						//������� ������
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

						// ������� ����
						SET_CHAR_COORDINATES(ped2, 292.473, -783.685, 5.19);// ���������� ����
						TASK_GO_STRAIGHT_TO_COORD(ped2, 292.473, -783.685, 5.19, 4, -2);//��������� �����
						car2_des = 1;
					}

					// ���� ��� 1 ��� ��� 2 ���������� 
					if (((ped2_HP < 990) && (car2_des == 0)) || ((ped3_HP < 990) && (car2_des == 0)))
					{
						if (IS_CAR_IN_AREA_3D(car2, 615.574, -502.26, 3.946, 621.074, -499.26, 6.946, 0))
						{
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							SET_CHAR_COORDINATES(ped2, 620.943, -497.315, 4.451);// ���������� ����
							SET_CHAR_HEADING(ped2, 166.505);
							SET_CAR_HEALTH(car2, 1000);
							SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), 105.498);

							SET_CAR_COORDINATES(car2, 618.48, -500.79, 5.058);// ���������� ������
							SET_CAR_HEADING(car2, 261.36);

							// ������ ����
							REQUEST_CAR_RECORDING( 2997 );// ������ ���� ��������
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 2997 )) WAIT(0);
							REQUEST_CAR_RECORDING( 2998 );// ������ ���� ���������
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 2998 )) WAIT(0);

							REQUEST_ANIMS( "ped" );//��������� ���� � ���������
							while (!HAVE_ANIMS_LOADED( "ped" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "duck_cower", "ped", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
							PANIC_SCREAM(ped3);
							TASK_ENTER_CAR_AS_DRIVER(ped2, car2, -1);// ��� ������� � ������

							// ������ ���
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 618.985, -503.321, 5.338); // ���� ������� ������
							SET_CAM_POS			( camera, 625.491, -496.804, 7.461 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������

							// ��� ����� � ������
							SETTIMERA( 0 );
							while(true)
							{
								WAIT(0);
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
								{
									SetTime(1000);
									break;
								}
								else if (TIMERA() > 3000)
								{
									WARP_CHAR_INTO_CAR(ped2, car2);// ������������� ���� �� ����
									break;
								}
							}
							// ������� ����
							CLEAR_AREA(640.931, -483.029, 4.07, 5.5, 1);//������� ���� ��������
							CLEAR_AREA(639.585, -489.304, 4.07, 5.5, 1);//������� ���� ��������
							CLEAR_AREA(638.272, -495.001, 4.07, 5.5, 1);//������� ���� ��������
							CLEAR_AREA(636.958, -500.699, 4.07, 5.5, 1);//������� ���� ��������
							CLEAR_AREA(635.644, -506.396, 4.07, 5.5, 1);//������� ���� ��������
							CLEAR_AREA(634.367, -512.435, 4.07, 5.5, 1);//������� ���� ��������

							// ��������� ����
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 2997, 0.0, 0.374, -0.164);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 2998, 0.0, 0.142, -0.693);

							// ������ ������
							POINT_CAM_AT_COORD	( camera, 626.665, -503.788, 4.24); // ���� ������� ������
							SET_CAM_POS			( camera, 611.616, -498.071, 6.533 );//������������ ������
							CLOSE_ALL_CAR_DOORS(car2);// ��������� �����
							SetTime(4000);

							// ������ ������
							POINT_CAM_AT_COORD	( camera, 633.956, -505.002, 5.19); // ���� ������� ������
							SET_CAM_POS			( camera, 633.633, -496.148, 8.663 );//������������ ������
							SetTime(4000);

							// ������� ������
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							PRINT_STRING_IN_STRING("string", "LAW3_9", 5500, 1);//~g~Smash up the Juror's car to get him out!

							//������������� ����
							STOP_PLAYBACK_RECORDED_CAR(car2);
							STOP_PLAYBACK_RECORDED_CAR(car4);
							REMOVE_CAR_RECORDING( 2997 ); // ��������� ���� ����������
							REMOVE_CAR_RECORDING( 2998 ); // ��������� ���� ����������
							EXTINGUISH_CAR_FIRE(car2);
							EXTINGUISH_CAR_FIRE(car4);
							SET_CAR_HEALTH(car2, 1000);

							// ��������� ���� �������� ������
							while(true)
							{
								WAIT(0);
								GET_CAR_HEALTH(car2, &car2_HP);
								//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.9, "CP_TIME_NOZERO", car2_HP);
								if ((car2_HP < 900) && (car2_des2 == 0))
								{
									// ����������� ������� ����
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX2", "NE_LAW3_2", 0, 0);//Hey man, my car! Leave my damn car alone, man!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 900);
									car2_des2 = 1;
								}
								else if ((car2_HP < 700) && (car2_des2 == 1))
								{
									// ����������� ������� ����
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R1_BR", "NE_LAW3_3", 0, 0);//Oh, please God! Someone help me!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 700);
									car2_des2 = 2;
								}
								else if ((car2_HP < 500) && (car2_des2 == 2))
								{
									// ����������� ������� ����
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BS", "NE_LAW3_4", 0, 0);//Yo man, I still got payment to make on this!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 500);
									car2_des2 = 3;
								}
								else if ((car2_HP < 100) && (car2_des2 == 3))
								{
									// ����������� ������� ����
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BS_XXX1", "NE_LAW3_5", 0, 0);//Okay, okay, man! I get the message!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 1);
									car2_des2 = 4;
								}
								else if (((car2_HP < 5) && (car2_des2 == 4)) || (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)))
								{
									if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
									{
										TASK_LEAVE_CAR(ped2, car2);// ��� ������� �� ������
									}

									DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
									while(true)
									{
										WAIT(0);
										if (IS_SCREEN_FADED_OUT())
										{
											break;
										}
									}
									SetTime(1000);
									if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
									{
										WARP_CHAR_FROM_CAR_TO_COORD(ped2, 633.551, -503.916, 4.451);// ���������� ����
										SET_CHAR_HEADING(ped2, -168.322);
									}
									else
									{
										SET_CHAR_COORDINATES(ped2, 633.551, -503.916, 4.451);// ���������� ����
										SET_CHAR_HEADING(ped2, -168.322);
									}
									SET_CAR_COORDINATES(car2, 632.11, -505.21, 5.058);// ���������� ������
									SET_CAR_HEADING(car2, 209.23);

									// �������� ����� � ������
									if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
									{
										SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// ���������� ������
										SET_CHAR_HEADING(GetPlayerPed(), 105.498);
										WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 633.158, -507.921, 4.304);// ���������� ������
										SET_CHAR_HEADING(GetPlayerPed(), -11.288);
									}
									else
									{
										SET_CHAR_COORDINATES(GetPlayerPed(), 633.158, -507.921, 4.304);// ���������� ������
										SET_CHAR_HEADING(GetPlayerPed(), -11.288);
									}

									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
									REMOVE_BLIP(jury_car2);//������� ������ �� ������

									// ������ ������
									CREATE_CAM( 14, &camera );
									POINT_CAM_AT_COORD	( camera, 631.877, -506.294, 4.671); // ���� ������� ������
									SET_CAM_POS			( camera, 634.686, -497.097, 6.668 );//������������ ������
									SET_CAM_ACTIVE( camera, 1 );
									SET_CAM_PROPAGATE( camera, 1 );
									ACTIVATE_SCRIPTED_CAMS(1, 1);
									SET_CAM_FOV( camera, 45.0 );
									SET_WIDESCREEN_BORDERS( 1 );
									DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
									SetTime(250);

									// ������������� ������
									REMOVE_BLIP(jury_car2);//������� ������ �� ������
									GENERATE_RANDOM_INT_IN_RANGE( 1, 12, &dialogID);
									if ((dialogID == 1) || (dialogID == 7))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX1", "LAW3_1", 0, 0);//Giorgio sends his regards.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 2) || (dialogID == 8))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX2", "LAW3_2", 0, 0);//Remember, guilty is a dirty word.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 3) || (dialogID == 9))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 4) || (dialogID == 10))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX1", "LAW3_4", 0, 0);//You know he's not guilty.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 5) || (dialogID == 11))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX2", "LAW3_5", 0, 0);//You remember Giorgio? You remember he's innocent.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 6) || (dialogID == 12))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BO", "LAW3_6", 0, 0);//Not guilty, understand? Good.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}

									// ������ ������
									POINT_CAM_AT_COORD	( camera, 632.427, -490.956, 5.862); // ���� ������� ������
									SET_CAM_POS			( camera, 632.131, -491.902, 5.988 );//������������ ������
									SET_CHAR_COORDINATES(ped2, 634.284, -489.079, 4.451);// ���������� ����
									SET_CHAR_HEADING(ped2, -28.13);

									// ��� �������
									TASK_GO_STRAIGHT_TO_COORD(ped2, 638.477, -471.28, 5.386, 4, -2);//��������� �����
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX1", " ", 0, 0);//������
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									//SetTime(2500);

									//������� ������
									SET_CAM_BEHIND_PED( GetPlayerPed() );
									ACTIVATE_SCRIPTED_CAMS( 0, 0 );
									DESTROY_CAM( camera );
									SET_WIDESCREEN_BORDERS( 0 );
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

									// ������� ����
									SET_CHAR_COORDINATES(ped2, 292.473, -783.685, 5.19);// ���������� ����
									TASK_GO_STRAIGHT_TO_COORD(ped2, 292.473, -783.685, 5.19, 4, -2);//��������� �����
									car2_des2 = 5;
									car2_des = 1;
									break;
								}
								else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//���� ��������� ����
								{
									EXPLODE_CHAR_HEAD(ped1);
									EXPLODE_CHAR_HEAD(ped2);
									break;
								}
								else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 581.95, -543.68, 1.652, 671.95, -453.68, 25.1, 0 ))// ���� ����� ������� �����
								{
									skip = 1;
									break;
								}
							}
							SetTime(2500);
						}
						else
						{
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							REMOVE_BLIP(jury_car2);//������� ������ �� ������
							SET_CHAR_COORDINATES(ped2, 624.583, -494.482, 4.451);// ���������� ����
							SET_CHAR_HEADING(ped2, -111.38);

							REQUEST_ANIMS( "ped" );//��������� ���� � ���������
							while (!HAVE_ANIMS_LOADED( "ped" )) WAIT(0);

							// ������ ���
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 630.144, -495.907, 4.983); // ���� ������� ������
							SET_CAM_POS			( camera, 622.264, -492.284, 6.136 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// �������� ����� � ������
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// ���������� ������
								SET_CHAR_HEADING(GetPlayerPed(), 105.498);
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 628.82, -495.402, 4.451);// ���������� ������
								SET_CHAR_HEADING(GetPlayerPed(), 68.201);
							}
							else
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 628.82, -495.402, 4.451);// ���������� ������
								SET_CHAR_HEADING(GetPlayerPed(), 68.201);
							}

							// ����� ��� � ����
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "duck_cower", "ped", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
							PANIC_SCREAM(ped3);
							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 626.697, -494.893, 5.386, 2, -2);//����� ��� � �����
							SetTime(250);

							// ��������� ������
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BS_XXX1", "NE_LAW3_5", 0, 0);//Okay, okay, man! I get the message!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// ������ ������
							POINT_CAM_AT_COORD	( camera, 632.427, -490.956, 5.862); // ���� ������� ������
							SET_CAM_POS			( camera, 632.131, -491.902, 5.988 );//������������ ������
							SET_CHAR_COORDINATES(ped2, 634.284, -489.079, 4.451);// ���������� ����
							SET_CHAR_HEADING(ped2, -15.774);

							// ��� �������
							TASK_GO_STRAIGHT_TO_COORD(ped2, 638.477, -471.28, 5.386, 4, -2);//��������� �����
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX1", " ", 0, 0);//������
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							//SetTime(3000);

							//������� ������
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

							// ������� ����
							SET_CHAR_COORDINATES(ped2, 292.473, -783.685, 5.19);// ���������� ����
							TASK_GO_STRAIGHT_TO_COORD(ped2, 292.473, -783.685, 5.19, 4, -2);//��������� �����
						}
						car2_des = 1;
					}

					if ((car1_des == 1) && (car2_des == 1))// ���� ������ 1 � 2 �������
					{
						skip = 2;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//���� ��������� ����
					{
						skip = 1;
						PRINT_STRING_IN_STRING("string", "LAW3_8", 5500, 1);//~r~You killed a Juror!
						EXPLODE_CHAR_HEAD(ped1);
						EXPLODE_CHAR_HEAD(ped2);
						break;
					}
					else if (skip == 1)
					{
						PRINT_STRING_IN_STRING("string", "NE_LAW3_6", 5500, 1);//~r~The Juror called the police!
						break;
					}
				}

				ABORT_SCRIPTED_CONVERSATION( 0 );
				REMOVE_BLIP(jury_car1);//������� ������ �� ������
				REMOVE_BLIP(jury_car2);//������� ������ �� ������
				REMOVE_PICKUP(sweap_1);// ��������� ����
				REMOVE_PICKUP(sweap_2);// ��������� ����

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//��������� ������ ������

				// ��������� �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)

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
				else if (skip == 2)
				{
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 400);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +400 );//��� ������ �����
					G_LAWYER = 4;
					sutosave = 1;
				}

				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
//============================== Riot ======================================
		else if ((G_ONMISSION == 0) && (G_LAWYER == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//������ �� ������ ��������� � ������� ����� "�������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				skip = 0; // ���������� ��������
				G_ONMISSION = 1;
				REMOVE_BLIP(lawyer_ico);//������� ������ �� ������
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				
				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 1, 0);
				SET_MAX_WANTED_LEVEL(0);

				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//������������� �����
				
				//------------ �������� ��� ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_4", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("law_4");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//������������� ������
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//������������� �����

				// ������ �����
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				ADD_BLIP_FOR_COORD(731.166, 210.147, 6.354, &Riot);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(Riot, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(Riot, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(Riot, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Riot, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""

				// ������ �������� ������
				ADD_BLIP_FOR_COORD(527.259, -601.747, 4.341, &Party_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(Party_ico, BLIP_CLOTHES_SHOP);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(Party_ico, 0);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(Party_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_SHOP");//������ �� ������ ��������� � ������� ����� ""

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_WB", "", 0, 0);//mono_8
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "LAW1_1", 5500, 1);//~g~Go get some new threads from Rafael's clothes shop.
				SetTime(1000);

				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22, ped23, ped24;
				Object barrel_1, barrel_2, barrel_3, vorota;
				Cam camera, camera2, camera3;

				// ����������� ������ ����������
				uint PedM1 = MODEL_M_M_SECURITYMAN;// ��������
				uint PedM2 = MODEL_IG_TUNA;// ������� 1
				uint PedM3 = MODEL_IG_VINNY_SPAZ;// ������� 2
				uint CarM1 = MODEL_FXT;// ��������
				uint barrel = barrel4;// �����
				uint vorotaM = vc_electricgate; //������
				uint ped4_HP, ped5_HP, ped6_HP, ped7_HP, ped8_HP, ped9_HP, ped10_HP, ped11_HP, ped12_HP, ped13_HP;
				uint ped14_HP, ped15_HP, ped16_HP, ped17_HP, ped18_HP, ped19_HP, ped20_HP, ped21_HP, ped22_HP, ped23_HP, ped24_HP;
				uint AudID;

				// ��������� ������
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(PedM1);// ��������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM2);// ������� 1
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM3);// ������� 2
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(barrel);// �����
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);
				
				REQUEST_MODEL(vorotaM);// ������
				while (!HAS_MODEL_LOADED(vorotaM)) WAIT(0);

				// ������ ������
				CREATE_OBJECT_NO_OFFSET(vorotaM, 731.196, 219.32, 6.078, &vorota, TRUE);
				SET_OBJECT_DYNAMIC(vorota, 0);
				SET_OBJECT_INVINCIBLE(vorota, 1);
				FREEZE_OBJECT_POSITION(vorota, 1);

				// ������ �����
				CREATE_OBJECT_NO_OFFSET(barrel, 716.957, 222.311, 6.386, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 747.284, 231.978, 6.386, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 744.208, 221.089, 6.386, &barrel_3, TRUE);

				// ������ ������
				CREATE_CAR(CarM1, 744.774, 223.702, 6.354, &car1, TRUE);
				SET_CAR_HEADING(car1, 89.421);
				CREATE_CAR(CarM1, 744.774, 229.793, 6.354, &car2, TRUE);
				SET_CAR_HEADING(car2, 89.421);
				CREATE_CAR(CarM1, 719.85, 230.833, 6.354, &car3, TRUE);
				SET_CAR_HEADING(car3, -90.579);

				// ������ ����������
				CREATE_CHAR (26, PedM1, 737.717, 234.072, 6.354, &ped1, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 731.529, 221.274, 6.354, &ped2, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 735.911, 221.376, 6.354, &ped3, TRUE);// ������ ����

				// ������ ������� 1
				CREATE_CHAR (26, PedM2, 726.113, 216.401, 6.354, &ped4, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 737.019, 211.426, 6.354, &ped5, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 740.795, 216.692, 6.354, &ped6, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 731.361, 214.974, 6.354, &ped7, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 726.873, 210.934, 6.354, &ped8, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 735.413, 214.706, 6.354, &ped9, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 741.986, 213.132, 6.354, &ped10, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 739.796, 209.501, 6.354, &ped11, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 730.041, 212.085, 6.354, &ped12, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 736.509, 217.536, 6.354, &ped13, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 731.682, 209.003, 6.354, &ped14, TRUE);// ������ ����

				// ������ ������� 2
				CREATE_CHAR (26, PedM3, 723.234, 212.966, 6.354, &ped15, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 728.926, 208.093, 6.354, &ped16, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 726.826, 213.711, 6.354, &ped17, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 729.155, 216.309, 6.354, &ped18, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 732.908, 217.047, 6.354, &ped19, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 733.013, 212.894, 6.354, &ped20, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 734.284, 210.596, 6.354, &ped21, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 736.751, 207.754, 6.354, &ped22, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 738.673, 215.755, 6.354, &ped23, TRUE);// ������ ����
				CREATE_CHAR (26, PedM3, 741.959, 210.859, 6.354, &ped24, TRUE);// ������ ����

				// ������������ �����
				SET_CHAR_HEADING(ped1, -175.01);
				SET_CHAR_HEADING(ped2, -170.01);
				SET_CHAR_HEADING(ped3, 175.01);

				SET_CHAR_HEADING(ped4, -40.0);
				SET_CHAR_HEADING(ped5, -10.0);
				SET_CHAR_HEADING(ped6, 0.01);
				SET_CHAR_HEADING(ped7, 0.01);
				SET_CHAR_HEADING(ped8, 0.01);
				SET_CHAR_HEADING(ped9, 15.0);
				SET_CHAR_HEADING(ped10, 15.0);
				SET_CHAR_HEADING(ped11, 15.0);
				SET_CHAR_HEADING(ped12, -20.0);
				SET_CHAR_HEADING(ped13, 10.0);
				SET_CHAR_HEADING(ped14, -30.0);

				SET_CHAR_HEADING(ped15, -20.0);
				SET_CHAR_HEADING(ped16, -15.0);
				SET_CHAR_HEADING(ped17, -30.0);
				SET_CHAR_HEADING(ped18, -20.0);
				SET_CHAR_HEADING(ped19, -15.0);
				SET_CHAR_HEADING(ped20, 0.01);
				SET_CHAR_HEADING(ped21, 0.01);
				SET_CHAR_HEADING(ped22, 0.01);
				SET_CHAR_HEADING(ped23, 0.01);
				SET_CHAR_HEADING(ped24, 0.01);

				// ��������� "����-�����" ���
				int dm, cdm;
				LOAD_CHAR_DECISION_MAKER(2, &dm); // 4
				LOAD_COMBAT_DECISION_MAKER(3, &cdm); // 3 10
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				SET_SENSE_RANGE(ped1, 0.01);
				SET_SENSE_RANGE(ped2, 0.01);
				SET_SENSE_RANGE(ped3, 0.01);
				SET_SENSE_RANGE(ped4, 0.01);
				SET_SENSE_RANGE(ped5, 0.01);
				SET_SENSE_RANGE(ped6, 0.01);
				SET_SENSE_RANGE(ped7, 0.01);
				SET_SENSE_RANGE(ped8, 0.01);
				SET_SENSE_RANGE(ped9, 0.01);
				SET_SENSE_RANGE(ped10, 0.01);
				SET_SENSE_RANGE(ped11, 0.01);
				SET_SENSE_RANGE(ped12, 0.01);
				SET_SENSE_RANGE(ped13, 0.01);
				SET_SENSE_RANGE(ped14, 0.01);
				SET_SENSE_RANGE(ped15, 0.01);
				SET_SENSE_RANGE(ped16, 0.01);
				SET_SENSE_RANGE(ped17, 0.01);
				SET_SENSE_RANGE(ped18, 0.01);
				SET_SENSE_RANGE(ped19, 0.01);
				SET_SENSE_RANGE(ped20, 0.01);
				SET_SENSE_RANGE(ped21, 0.01);
				SET_SENSE_RANGE(ped22, 0.01);
				SET_SENSE_RANGE(ped23, 0.01);
				SET_SENSE_RANGE(ped24, 0.01);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped14, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped21, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped22, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped23, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped24, 7);

				SET_CHAR_DECISION_MAKER(ped1, dm);
				SET_CHAR_DECISION_MAKER(ped2, dm);
				SET_CHAR_DECISION_MAKER(ped3, dm);
				SET_CHAR_DECISION_MAKER(ped4, dm);
				SET_CHAR_DECISION_MAKER(ped5, dm);
				SET_CHAR_DECISION_MAKER(ped6, dm);
				SET_CHAR_DECISION_MAKER(ped7, dm);
				SET_CHAR_DECISION_MAKER(ped8, dm);
				SET_CHAR_DECISION_MAKER(ped9, dm);
				SET_CHAR_DECISION_MAKER(ped10, dm);
				SET_CHAR_DECISION_MAKER(ped11, dm);
				SET_CHAR_DECISION_MAKER(ped12, dm);
				SET_CHAR_DECISION_MAKER(ped13, dm);
				SET_CHAR_DECISION_MAKER(ped14, dm);
				SET_CHAR_DECISION_MAKER(ped15, dm);
				SET_CHAR_DECISION_MAKER(ped16, dm);
				SET_CHAR_DECISION_MAKER(ped17, dm);
				SET_CHAR_DECISION_MAKER(ped18, dm);
				SET_CHAR_DECISION_MAKER(ped19, dm);
				SET_CHAR_DECISION_MAKER(ped20, dm);
				SET_CHAR_DECISION_MAKER(ped21, dm);
				SET_CHAR_DECISION_MAKER(ped22, dm);
				SET_CHAR_DECISION_MAKER(ped23, dm);
				SET_CHAR_DECISION_MAKER(ped24, dm);

				SET_COMBAT_DECISION_MAKER(ped1, cdm);
				SET_COMBAT_DECISION_MAKER(ped2, cdm);
				SET_COMBAT_DECISION_MAKER(ped3, cdm);
				SET_COMBAT_DECISION_MAKER(ped4, cdm);
				SET_COMBAT_DECISION_MAKER(ped5, cdm);
				SET_COMBAT_DECISION_MAKER(ped6, cdm);
				SET_COMBAT_DECISION_MAKER(ped7, cdm);
				SET_COMBAT_DECISION_MAKER(ped8, cdm);
				SET_COMBAT_DECISION_MAKER(ped9, cdm);
				SET_COMBAT_DECISION_MAKER(ped10, cdm);
				SET_COMBAT_DECISION_MAKER(ped11, cdm);
				SET_COMBAT_DECISION_MAKER(ped12, cdm);
				SET_COMBAT_DECISION_MAKER(ped13, cdm);
				SET_COMBAT_DECISION_MAKER(ped14, cdm);
				SET_COMBAT_DECISION_MAKER(ped15, cdm);
				SET_COMBAT_DECISION_MAKER(ped16, cdm);
				SET_COMBAT_DECISION_MAKER(ped17, cdm);
				SET_COMBAT_DECISION_MAKER(ped18, cdm);
				SET_COMBAT_DECISION_MAKER(ped19, cdm);
				SET_COMBAT_DECISION_MAKER(ped20, cdm);
				SET_COMBAT_DECISION_MAKER(ped21, cdm);
				SET_COMBAT_DECISION_MAKER(ped22, cdm);
				SET_COMBAT_DECISION_MAKER(ped23, cdm);
				SET_COMBAT_DECISION_MAKER(ped24, cdm);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped23, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped24, 0);

				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped1, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped2, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped3, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped4, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped5, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped6, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped7, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped8, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped9, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped10, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped11, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped12, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped13, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped14, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped15, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped16, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped17, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped18, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped19, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped20, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped21, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped22, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped23, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped24, 1);

				SET_PED_DONT_DO_EVASIVE_DIVES(ped1, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped2, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped3, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped4, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped5, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped6, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped7, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped8, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped9, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped10, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped11, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped12, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped13, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped14, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped15, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped16, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped17, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped18, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped19, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped20, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped21, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped22, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped23, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped24, 1);

				SET_CHAR_WILL_USE_COVER(ped1, 0);
				SET_CHAR_WILL_USE_COVER(ped2, 0);
				SET_CHAR_WILL_USE_COVER(ped3, 0);
				SET_CHAR_WILL_USE_COVER(ped4, 0);
				SET_CHAR_WILL_USE_COVER(ped5, 0);
				SET_CHAR_WILL_USE_COVER(ped6, 0);
				SET_CHAR_WILL_USE_COVER(ped7, 0);
				SET_CHAR_WILL_USE_COVER(ped8, 0);
				SET_CHAR_WILL_USE_COVER(ped9, 0);
				SET_CHAR_WILL_USE_COVER(ped10, 0);
				SET_CHAR_WILL_USE_COVER(ped11, 0);
				SET_CHAR_WILL_USE_COVER(ped12, 0);
				SET_CHAR_WILL_USE_COVER(ped13, 0);
				SET_CHAR_WILL_USE_COVER(ped14, 0);
				SET_CHAR_WILL_USE_COVER(ped15, 0);
				SET_CHAR_WILL_USE_COVER(ped16, 0);
				SET_CHAR_WILL_USE_COVER(ped17, 0);
				SET_CHAR_WILL_USE_COVER(ped18, 0);
				SET_CHAR_WILL_USE_COVER(ped19, 0);
				SET_CHAR_WILL_USE_COVER(ped20, 0);
				SET_CHAR_WILL_USE_COVER(ped21, 0);
				SET_CHAR_WILL_USE_COVER(ped22, 0);
				SET_CHAR_WILL_USE_COVER(ped23, 0);
				SET_CHAR_WILL_USE_COVER(ped24, 0);

				UpdateWeaponOfPed(ped1, WEAPON_PISTOL);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_PISTOL, TRUE);
				UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_24);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_24, TRUE);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_24);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_24, TRUE);

				// ��������� ��������
				REQUEST_ANIMS( "amb@bum_a" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@bum_a" ));//���� ���� � ��������� �� �������� �������� � ������
				REQUEST_ANIMS( "amb@nightclub_ext" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@nightclub_ext" ));//���� ���� � ��������� �� �������� �������� � ������
				REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@payphone" ));//���� ���� � ��������� �� �������� �������� � ������
				REQUEST_ANIMS( "ped" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "ped" ));//���� ���� � ��������� �� �������� �������� � ������

				// ������������� ��������
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped17, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped21, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped23, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped18, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped24, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped22, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped16, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped19, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����

				sound = 0;
				soundID = 1;
				help = 0;
				riotID = 0;
				ped4_ID = 0;
				ped5_ID = 0;
				ped6_ID = 0;
				ped7_ID = 0;
				ped8_ID = 0;
				ped9_ID = 0;
				ped10_ID = 0;
				ped11_ID = 0;
				ped12_ID = 0;
				ped13_ID = 0;
				ped14_ID = 0;
				ped15_ID = 0;
				ped16_ID = 0;
				ped17_ID = 0;
				ped18_ID = 0;
				ped19_ID = 0;
				ped20_ID = 0;
				ped21_ID = 0;
				ped22_ID = 0;
				ped23_ID = 0;
				ped24_ID = 0;
				riotON = 0;
				skin = 0;
				textID = 0;
				car1_des = 0;
				car2_des = 0;
				car2_des2 = 0;
				vorotaX = 731.196;

				// ������������� ����
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/LAWRIOT" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_LAWRIOT_LAW4RIOT", 731.166, 210.147, 6.354);

				while (TRUE)
				{
					WAIT(0);

					// �������� ����� ������
					if (skin == 0)
					{
						DRAW_CHECKPOINT( 527.259, -601.747, 4.341, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 527.259, -601.747, 4.341, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							skin = 1;
							REMOVE_BLIP(Party_ico);//������� ������ �� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 530.273, -604.626, 4.197 ); // ���� ������� ������
							SET_CAM_POS			( camera, 522.552, -596.448, 16.414 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 529.623, -603.946, 4.766, 2, -2);// ����� ��� � �����
							SetTime(1000);

							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// ������������	
							SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 2, 0);// ������

							SET_CHAR_COORDINATES(GetPlayerPed(), 528.664, -602.916, 4.766);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), 52.9);
							SetTime(200);
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������

							// ���� ������
							CREATE_CAM( 3, &camera2 );
							CREATE_CAM( 14, &camera3 );
							POINT_CAM_AT_COORD	( camera, 528.442, -602.798, 4.56 ); // ���� ������� ������
							SET_CAM_POS			( camera, 527.141, -601.545, 5.08 );//������������ ������
							POINT_CAM_AT_COORD	( camera3, 528.442, -602.798, 5.839 ); // ���� ������� ������
							SET_CAM_POS			( camera3, 527.141, -601.545, 5.08 );//������������ ������
							SET_CAM_INTERP_STYLE_CORE( camera2, camera, camera3, 3500, 0 ); //����������� ������ �� ������ �� ����� ��������� � ����������� "SET_CAM_POS(camera, X, Y, Z)" 
							SET_CAM_ACTIVE( camera2, 1 );
							SET_CAM_PROPAGATE( camera2, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_WIDESCREEN_BORDERS( 1 ); //��������� ���������
							SetTime(5000);

							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							DESTROY_CAM( camera2 );
							DESTROY_CAM( camera3 );
							SET_WIDESCREEN_BORDERS( 0 ); //���������� ���������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							PRINT_STRING_IN_STRING("string", "NE_LAW4_1", 5500, 1);//~g~Drive to the site of the workers' strike.
						}
					}

					GET_CHAR_HEALTH(ped4, &ped4_HP);
					GET_CHAR_HEALTH(ped5, &ped5_HP);
					GET_CHAR_HEALTH(ped6, &ped6_HP);
					GET_CHAR_HEALTH(ped7, &ped7_HP);
					GET_CHAR_HEALTH(ped8, &ped8_HP);
					GET_CHAR_HEALTH(ped9, &ped9_HP);
					GET_CHAR_HEALTH(ped10, &ped10_HP);
					GET_CHAR_HEALTH(ped11, &ped11_HP);
					GET_CHAR_HEALTH(ped12, &ped12_HP);
					GET_CHAR_HEALTH(ped13, &ped13_HP);
					GET_CHAR_HEALTH(ped14, &ped14_HP);
					GET_CHAR_HEALTH(ped15, &ped15_HP);
					GET_CHAR_HEALTH(ped16, &ped16_HP);
					GET_CHAR_HEALTH(ped17, &ped17_HP);
					GET_CHAR_HEALTH(ped18, &ped18_HP);
					GET_CHAR_HEALTH(ped19, &ped19_HP);
					GET_CHAR_HEALTH(ped20, &ped20_HP);
					GET_CHAR_HEALTH(ped21, &ped21_HP);
					GET_CHAR_HEALTH(ped22, &ped22_HP);
					GET_CHAR_HEALTH(ped23, &ped23_HP);
					GET_CHAR_HEALTH(ped24, &ped24_HP);

					// �������� �����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 731.166, 210.147, 6.354, &PlayR);//�������� "����� �� �����������"
					if (( PlayR < 40.0) && (sound == 0))
					{
						SETTIMERB( 0 );
						sound = 1;
					}
					else if (( PlayR > 40.0) && (sound == 1))
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						sound = 0;
					}
					if (sound == 1)
					{
						if (soundID == 1)
						{
							if (TIMERB() > 7000)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_DA", " ", 0, 0);//
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB( 0 );
								soundID = 2;
							}
						}
						else if (soundID == 2)
						{
							if (TIMERB() > 7000)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_EA", " ", 0, 0);//
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB( 0 );
								soundID = 1;
							}
						}
					}
					if (( PlayR < 25.0) && (textID == 0))
					{
						// ������� ����� � ����������� ��������
						PRINT_STRING_IN_STRING("string", "LAW4_13", 5500, 1);//~g~Start fighting with at least 4 workers to get a riot started.
						textID = 1;
					}

					if ((ped4_HP < 195) && (ped4_ID == 0)) ped4_ID = 1, riotID += 1;
					else if ((ped5_HP < 195) && (ped5_ID == 0)) ped5_ID = 1, riotID += 1;
					else if ((ped6_HP < 195) && (ped6_ID == 0)) ped6_ID = 1, riotID += 1;
					else if ((ped7_HP < 195) && (ped7_ID == 0)) ped7_ID = 1, riotID += 1;
					else if ((ped8_HP < 195) && (ped8_ID == 0)) ped8_ID = 1, riotID += 1;
					else if ((ped9_HP < 195) && (ped9_ID == 0)) ped9_ID = 1, riotID += 1;
					else if ((ped10_HP < 195) && (ped10_ID == 0)) ped10_ID = 1, riotID += 1;
					else if ((ped11_HP < 195) && (ped11_ID == 0)) ped11_ID = 1, riotID += 1;
					else if ((ped12_HP < 195) && (ped12_ID == 0)) ped12_ID = 1, riotID += 1;
					else if ((ped13_HP < 195) && (ped13_ID == 0)) ped13_ID = 1, riotID += 1;
					else if ((ped14_HP < 195) && (ped14_ID == 0)) ped14_ID = 1, riotID += 1;
					else if ((ped15_HP < 195) && (ped15_ID == 0)) ped15_ID = 1, riotID += 1;
					else if ((ped16_HP < 195) && (ped16_ID == 0)) ped16_ID = 1, riotID += 1;
					else if ((ped17_HP < 195) && (ped17_ID == 0)) ped17_ID = 1, riotID += 1;
					else if ((ped18_HP < 195) && (ped18_ID == 0)) ped18_ID = 1, riotID += 1;
					else if ((ped19_HP < 195) && (ped19_ID == 0)) ped19_ID = 1, riotID += 1;
					else if ((ped20_HP < 195) && (ped20_ID == 0)) ped20_ID = 1, riotID += 1;
					else if ((ped21_HP < 195) && (ped21_ID == 0)) ped21_ID = 1, riotID += 1;
					else if ((ped22_HP < 195) && (ped22_ID == 0)) ped22_ID = 1, riotID += 1;
					else if ((ped23_HP < 195) && (ped23_ID == 0)) ped23_ID = 1, riotID += 1;
					else if ((ped24_HP < 195) && (ped24_ID == 0)) ped24_ID = 1, riotID += 1;

					if (((riotID > 3) && (riotON == 0)) || ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 716.176, 219.828, 5.218, 748.176, 235.758, 15.218, 0 )) && (riotON == 0)))
					{
						riotON = 1;
						REMOVE_BLIP(Party_ico);//������� ������ �� ������
						REMOVE_BLIP(Riot);//������� ������ �� ������

						if (riotID > 3)
						{
							// ������ �� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 733.589, 220.041, 6.696 ); // ���� ������� ������
							SET_CAM_POS			( camera, 728.927, 224.124, 7.243);//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);

							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BS_XXX2", "LAW4_5", 0, 0);//Sticks out, boys! Let's crack some commie skulls!
							START_SCRIPT_CONVERSATION(1, 1);
							soundID = 3;

							// ��������� ������
							while (true)
							{
								WAIT( 0 );
								vorotaX += 0.06;
								SET_OBJECT_COORDINATES(vorota, vorotaX, 219.32, 6.078);
								if (vorotaX > 737.4)
								{
									break;
								}
							}
							SetSpeech();

							TASK_GO_STRAIGHT_TO_COORD(ped2, 732.049, 218.421, 6.354, 2, -2);// ��� ��� � �����
							TASK_GO_STRAIGHT_TO_COORD(ped3, 736.048, 218.378, 6.354, 2, -2);// ��� ��� � �����
							SetTime(2000);

							// ������� ������
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
						}

						SET_OBJECT_COORDINATES(vorota, 737.8, 219.32, 6.078);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped16, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped17, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped18, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped19, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped21, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped22, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped23, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped24, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����

						// ���� ���
						SET_SENSE_RANGE(ped1, 15.01);
						SET_SENSE_RANGE(ped2, 10.01);
						SET_SENSE_RANGE(ped3, 10.01);
						SET_SENSE_RANGE(ped4, 6.01);
						SET_SENSE_RANGE(ped5, 6.01);
						SET_SENSE_RANGE(ped6, 6.01);
						SET_SENSE_RANGE(ped7, 6.01);
						SET_SENSE_RANGE(ped8, 6.01);
						SET_SENSE_RANGE(ped9, 6.01);
						SET_SENSE_RANGE(ped10, 6.01);
						SET_SENSE_RANGE(ped11, 6.01);
						SET_SENSE_RANGE(ped12, 6.01);
						SET_SENSE_RANGE(ped13, 6.01);
						SET_SENSE_RANGE(ped14, 6.01);
						SET_SENSE_RANGE(ped15, 6.01);
						SET_SENSE_RANGE(ped16, 6.01);
						SET_SENSE_RANGE(ped17, 6.01);
						SET_SENSE_RANGE(ped18, 6.01);
						SET_SENSE_RANGE(ped19, 6.01);
						SET_SENSE_RANGE(ped20, 6.01);
						SET_SENSE_RANGE(ped21, 6.01);
						SET_SENSE_RANGE(ped22, 6.01);
						SET_SENSE_RANGE(ped23, 6.01);
						SET_SENSE_RANGE(ped24, 6.01);

						if (skin == 1)
						{
							SET_CHAR_RELATIONSHIP_GROUP(ped15, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped16, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped17, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped18, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped19, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped20, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped21, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped22, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped23, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped24, 0);
						}
						TASK_COMBAT(ped2, ped7);
						TASK_COMBAT(ped3, ped19);
						TASK_COMBAT(ped4, ped15);
						TASK_COMBAT(ped5, ped16);
						TASK_COMBAT(ped6, ped17);
						TASK_COMBAT(ped7, ped18);
						TASK_COMBAT(ped15, ped4);
						TASK_COMBAT(ped16, ped5);
						TASK_COMBAT(ped17, ped6);
						TASK_COMBAT(ped18, ped7);
						TASK_COMBAT(ped1, GetPlayerPed());
						TASK_COMBAT(ped2, ped7);
						TASK_COMBAT(ped3, ped19);
						PRINT_STRING_IN_STRING("string", "LAW4_14", 5500, 1);//~g~Destroy the vans in the compound!

						ADD_BLIP_FOR_CAR(car1, &lance_car);
						CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//�������� ������ �� ������
						CHANGE_BLIP_COLOUR(lance_car, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "MO_TARGET");//������ �� ������ "�������"
						CHANGE_BLIP_SCALE(lance_car, 0.6); // ������� ������ �� ������

						ADD_BLIP_FOR_CAR(car2, &jury_car1);
						CHANGE_BLIP_SPRITE(jury_car1, BLIP_OBJECTIVE);//�������� ������ �� ������jury_car1
						CHANGE_BLIP_COLOUR(jury_car1, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car1, "MO_TARGET");//������ �� ������ "�������"
						CHANGE_BLIP_SCALE(jury_car1, 0.6); // ������� ������ �� ������

						ADD_BLIP_FOR_CAR(car3, &jury_car2);
						CHANGE_BLIP_SPRITE(jury_car2, BLIP_OBJECTIVE);//�������� ������ �� ������jury_car1
						CHANGE_BLIP_COLOUR(jury_car2, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car2, "MO_TARGET");//������ �� ������ "�������"
						CHANGE_BLIP_SCALE(jury_car2, 0.6); // ������� ������ �� ������
						skin = 1;
					}

					if ((riotON == 1) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 716.176, 219.828, 5.218, 748.176, 235.758, 15.218, 0 )))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 737.311, 233.431, 6.871 ); // ���� ������� ������
						SET_CAM_POS			( camera, 730.188, 225.704, 9.987 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SetTime(4000);

						// ������ ������
						POINT_CAM_AT_COORD	( camera, 748.657, 232.445, 5.295 ); // ���� ������� ������
						SET_CAM_POS			( camera, 732.313, 232.226, 8.498 );//������������ ������
						SetTime(4000);

						// ������� ������
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

						TASK_COMBAT(ped1, GetPlayerPed());
						TASK_COMBAT(ped2, ped7);
						TASK_COMBAT(ped3, ped19);
						TASK_COMBAT(ped4, ped15);
						TASK_COMBAT(ped5, ped16);
						TASK_COMBAT(ped6, ped17);
						TASK_COMBAT(ped7, ped18);
						TASK_COMBAT(ped15, ped4);
						TASK_COMBAT(ped16, ped5);
						TASK_COMBAT(ped17, ped6);
						TASK_COMBAT(ped18, ped7);
						riotON = 2;
					}
					
					if ((IS_CAR_DEAD(car1)) && (car1_des == 0))
					{
						REMOVE_BLIP(lance_car);//������� ������ �� ������
						car1_des = 1;
					}
					if ((IS_CAR_DEAD(car2)) && (car2_des == 0))
					{
						REMOVE_BLIP(jury_car1);//������� ������ �� ������
						car2_des = 1;
					}
					if ((IS_CAR_DEAD(car3)) && (car2_des2 == 0))
					{
						REMOVE_BLIP(jury_car2);//������� ������ �� ������
						car2_des2 = 1;
					}

					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;
						break;
					}
					else if ((car1_des == 1) && (car2_des == 1) && (car2_des2 == 1))
					{
						WAIT( 500 );
						if ((!IS_CHAR_DEAD(GetPlayerPed())) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 2;
							break;
						}
						else
						{
							skip = 1;
							break;
						}
					}
				}

				// ������� ����
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				SET_MAX_WANTED_LEVEL(6);

				REMOVE_BLIP(Party_ico);//������� ������ �� ������
				REMOVE_BLIP(Riot);//������� ������ �� ������
				REMOVE_BLIP(lance_car);//������� ������ �� ������
				REMOVE_BLIP(jury_car1);//������� ������ �� ������
				REMOVE_BLIP(jury_car2);//������� ������ �� ������

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(vorotaM);//��������� ������

				// ��������� �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped12);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped13);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped14);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped15);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped16);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped17);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped18);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped19);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped20);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped21);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped22);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped23);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped24);//��������� ������ ����(� ����������� ��� ��������

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)

				// ������� �������
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);
				DELETE_OBJECT(&barrel_3);
				DELETE_OBJECT(&vorota);

				// ��������� ����� � ������
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&vorota);

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
				else if (skip == 2)
				{
					PRINT_HELP("CLOTH3"); //Coveralls outfit delivered to Tooled Up in The North Point Mall.
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 1000);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +1000 );//��� ������ �����
					G_LAWYER = 5;
					G_AVERY = 1;
					sutosave = 1;
				}

				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_LAWYER == 5))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(lawyer_ico);//������� ������ �� ������
				blip_on = 0;
			}
		}
	}					
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_LAWYER < 5)
	{
		LAWYER_1();
	}
	WAIT(200);
	while (TRUE)
	{
		WAIT(10);
	}
	return;
}
