/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, blip_on, skip, help_1, help_2, text, play, stalking, in_car, del_car, wave, gogogo, textur, in_zon, hate, clear_ped, sutosave, super_ped;
float pedHUD_x, pedHUD_w, LanceH1, LanceH2, LanceH3, LanceHUD_y1, LanceHUD_y2, LanceHUD_y3, DiazH1, DiazH2, DiazH3, DiazHUD_y1, DiazHUD_y2, DiazHUD_y3, Speech;
float convoy_x, convoy_y, passenger, point, speed, speed2, speed3, speed4, terpenie, PedX2, PedY2, PedZ2, PedR2, convoy_x2, convoy_y2, car_blip, delta, hud_on, boom, garage, in_garage;

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
void cortez(void)
{
	blip_on = 0;
	sutosave = 0;
	Blip cortez_ico, vert_ico;
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
//============================== Treacherous Swine ======================================
		if ((G_ONMISSION == 0) && (G_CORTEZ == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				blip_on = 0;
				skip = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "COL_1", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("col_1");
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

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				ADD_BLIP_FOR_COORD(908.828, 563.354, 5.941, &cortez_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""
				PRINT_STRING_IN_STRING("string", "GEN1_05", 5000, 1);//~g~Go and kill Gonzalez!

				// ��� ���������
				SetTime(2000);
				UpdateWeaponOfPed(GetPlayerPed(), WEAPON_FTHROWER);

				Ped ped1, ped2, ped3;
				Cam camera;
				int money_plaer;
				help_1 = 0;
				help_2 = 0;
				play = 0;
				text = 0;

				uint PedM1 = MODEL_IG_ANTHONY;// ��������
				uint PedM2 = MODEL_M_Y_GMAF_HI_01;// ������

				// ������ ������
				REQUEST_MODEL(PedM1);// ��������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM2);// ������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ������� �����
				CREATE_CHAR (26, PedM1, 895.752, 571.529, 27.553, &ped1, TRUE);// ��������
				CREATE_CHAR (26, PedM2, 895.823, 572.708, 27.553, &ped2, TRUE);// ��������
				CREATE_CHAR (26, PedM2, 895.106, 576.637, 27.553, &ped3, TRUE);// ��������
				SET_CHAR_HEADING(ped1, -25.0);
				SET_CHAR_HEADING(ped2, -170.0);
				SET_CHAR_HEADING(ped3, -5.0);

				// ������ ��������
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				SetTime(2000);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_FTHROWER, TRUE);

				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( 908.828, 563.354, 5.941, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 908.828, 563.354, 5.941, &PlayR);//�������� "����� �� �����������"
					if ((( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )))
					{
						REMOVE_BLIP(cortez_ico);//������� ������ �� ������
						SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_FTHROWER, TRUE);

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
						SET_CHAR_COORDINATES(GetPlayerPed(), 887.29, 562.852, 29.284);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), -95.0);

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 886.461, 556.552, 29.904); // ���� ������� ������
						SET_CAM_POS			( camera, 900.625, 576.546, 28.014 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						SetTime(200);
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 892.86, 561.146, 29.284, 2, -2);// ����� ��� � �����
						// �������� ��������� �����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_b", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����

						SetTime(3000);
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 893.19, 562.085, 29.284, 2, -2);// ����� ��� � �����
						SetTime(1000);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//���������������� �������� �� ����

						// ������������� �����
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_AD", "GEN1_10", 0, 0);//I'm going to shut that big mouth of yours!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2000);
						SetSpeech();

						// ����� ������� ������
						POINT_CAM_AT_COORD	( camera, 895.755, 578.788, 28.006 ); // ���� ������� ������
						SET_CAM_POS			( camera, 895.242, 551.305, 32.388 );//������������ ������

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_AA", "GEN1_06", 0, 0);//Eh! He's got a blade!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 893.944, 563.112, 24.916, 3, -1, 1.5);// �������� ����� � ������
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_AB", "GEN1_11", 0, 0);//Stop running you fat slimeball!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//������� ������
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

						// ������ ��� �����.
						ADD_BLIP_FOR_CHAR(ped1, &cortez_ico);
						CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//�������� ������ �� ������
						CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ""
						CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������

						// ����� �����
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_SENSE_RANGE(ped2, 20.0);
						SET_SENSE_RANGE(ped3, 20.0);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
						SetTime(1000);
						PANIC_SCREAM(ped1);
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
					else if (IS_CHAR_DEAD(ped1))
					{
						break;
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 908.828, 563.354, 5.941, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
						DRAW_CHECKPOINT( 885.286, 563.279, 28.781, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
						DRAW_CHECKPOINT( 893.944, 563.112, 24.916, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ,  885.286, 563.279, 28.781, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.3 ) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							DO_SCREEN_FADE_OUT( 400 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 910.986, 563.28, 6.1);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							DO_SCREEN_FADE_IN( 400 );// ��������� ���������� ������
						}
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 893.944, 563.112, 24.916, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.3 ) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							DO_SCREEN_FADE_OUT( 400 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 910.986, 563.28, 6.1);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							DO_SCREEN_FADE_IN( 400 );// ��������� ���������� ������
						}
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 908.828, 563.354, 5.941, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							DO_SCREEN_FADE_OUT( 400 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 887.29, 562.852, 29.284);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							DO_SCREEN_FADE_IN( 400 );// ��������� ���������� ������
						}
						if ((IS_CHAR_DEAD(ped1)) && (help_2 == 0))
						{
							// ������ �� �����
							REMOVE_BLIP(cortez_ico);//������� ������ �� ������
							ADD_BLIP_FOR_COORD(885.286, 563.279, 28.781, &cortez_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN1_23", 5000, 1);//~g~Go back through the doors to return to the ground floor.
							help_2 = 1;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else
						{
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 893.944, 563.112, 24.916, &PedR);//�������� "����� �� �����������"
							if ( PedR < 2.0 )
							{
								PANIC_SCREAM(ped1);
								SET_CHAR_COORDINATES(ped1, 910.986, 563.28, 6.1);// ���������� ������
								SET_CHAR_HEADING(ped1, -95.0);
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 828.377, 59.035, 6.753, 3, -1, 1.5);// �������� ����� � �����

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN1_23", 5000, 1);//~g~Go back through the doors to return to the ground floor.
								text = 1;
								SETTIMERB( 0 );
							}
						}
						if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )) && (!IS_CHAR_IN_AREA_3D( ped1, 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )))
						{
							break;
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )) && (IS_CHAR_DEAD(ped1)))
						{
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped1))
						{
							REMOVE_BLIP(cortez_ico);//������� ������ �� ������
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							STORE_SCORE(GetPlayerIndex(), &money_plaer);// ���������� �������� ������ � ����������
							if ( money_plaer < 100 )
							{
								ADD_SCORE( GetPlayerIndex(), +100 );//��� ������ �����
							}
							// ������ �� �����������
							ADD_BLIP_FOR_COORD(754.079, 965.605, 5.128, &cortez_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "������� ������"

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NE_GEN1", 5000, 1);//The Vice City Police are on to you! Get to the Pay 'N' Spray in Vice Point.
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 828.377, 59.035, 6.753, &PedR);//�������� "����� �� �����������"
							if (( PlayR > 200.0) || ( PedR < 2.5 ))
							{
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 4);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN1_18", 5000, 1);//~r~Gonzalez has made it safely to the Police Station!
								skip = 1;// ���������� ��������
								break;
							}
							else
							{
								if (TIMERB() > 8000)
								{
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 828.377, 59.035, 6.753, 3, -1, 1.5);// �������� ����� � �����
									SETTIMERB( 0 );
									if (text == 1)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_DA", "GEN1_07", 0, 0);//Go away from me, you cheap bastard!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 2)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_AB", "GEN1_11", 0, 0);//Stop running you fat slimeball!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 3)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_EA", "GEN1_08", 0, 0);//Oh sweet Jesus, I've wasted my life and my looks!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 4)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_FA", "GEN1_12", 0, 0);//Stand still and I'll make it quick!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 5)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_GA", "GEN1_09", 0, 0);//I pay you double, Tommy, DOUBLE!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 6)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_GB", "GEN1_13", 0, 0);//Quit your squealing, no one cares, fatso!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else
									{
										PANIC_SCREAM(ped1);
									}
									text += 1;
								}
							}
						}
					}
				}


				if (skip == 0)
				{
					if (play == 1)
					{
						play = 0;
					}
					while(true)
					{
						WAIT(0);
						// ������ �� �����������
						DRAW_CHECKPOINT( 754.079, 965.605, 5.128, 2.1, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ,  754.079, 965.605, 5.128, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 2.0 )
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
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
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								SetTime(2000);
								DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
								skip = 2;// ���������� ��������
								break;
							}
							else
							{
								if (help_1 == 0)
								{
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "GEN1_20", 5000, 1);//~g~Get into a vehicle.
									help_1 = 1;
								}
							}
						}
						else
						{
							if (help_1 == 1)
							{
								help_1 = 0;
							}
						}
						if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							skip = 2;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				

				REMOVE_BLIP(cortez_ico);//������� ������ �� ������

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����

				// ��������� �� ������ �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������

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
					PRINT_HELP("CLOTH7"); //Casual outfit delivered to Gash in The North Point Mall.
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 250);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +250 );//��� ������ �����
					G_CORTEZ = 2;
					sutosave = 1;
				}

				G_ONMISSION = 0;
			}
		}

//============================== Mall Shootout ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				blip_on = 0;


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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "COL_2", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("col_2");
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
				FORCE_WEATHER_NOW(WEATHER_RAINING);
				RELEASE_WEATHER();
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				Car car1, car2;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7;
				Cam camera;
				Pickup bag;
				skip = 0;

				uint PedM1 = MODEL_IG_DMITRI;// �������
				uint PedM2 = MODEL_M_Y_NHELIPILOT;// SWAT
				uint CarM1 = MODEL_PCJ;// PCJ

				// ������ ������
				REQUEST_MODEL(PedM1);// ��������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM2);// ������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM1);// ������
				while (!HAS_MODEL_LOADED(CarM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ������� �����
				CREATE_CHAR (26, PedM1, 439.097, -403.801, 10.9, &ped1, TRUE);// �������
				CREATE_CHAR (26, PedM2, 286.386, -785.672, 5.06, &ped2, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 289.619, -785.672, 5.06, &ped3, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 292.961, -785.672, 5.06, &ped4, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 296.473, -785.672, 5.06, &ped5, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 299.976, -785.672, 5.06, &ped6, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 286.775, -783.209, 5.06, &ped7, TRUE);// SWAT

				SET_CHAR_HEADING(ped1, -95.0);
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);

				CREATE_CAR(CarM1, 286.232, -791.79, 5.445, &car1, TRUE);
				CREATE_CAR(CarM1, 289.629, -791.79, 5.445, &car2, TRUE);

				// ������ ��������
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				REQUEST_ANIMS( "gun@ak47" );
				while (!HAVE_ANIMS_LOADED( "gun@ak47" )) WAIT(0);

				ADD_BLIP_FOR_CHAR(ped1, &cortez_ico);
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "������� ������"
				PRINT_STRING_IN_STRING("string", "COL2_B1", 5000, 1);//~g~Meet the courier at the mall.
				SetTime(2000);

				while(true)
				{
					WAIT(0);
					if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 439.897, -407.509, 9.982, 435.397, -403.509, 13.982, 0 ))// ���� ����� � ����
					{

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

						REMOVE_BLIP(cortez_ico);//������� ������ �� ������
						ADD_BLIP_FOR_CHAR(ped1, &cortez_ico);
						CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//�������� ������ �� ������
						CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 433.081, -407.492, 10.705); // ���� ������� ������
						SET_CAM_POS			( camera, 442.991, -403.101, 12.374 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						
						SET_CHAR_COORDINATES(GetPlayerPed(), 436.942, -405.857, 10.2);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), -50.0);
						TASK_GO_STRAIGHT_TO_COORD(ped1, 437.601, -404.651, 10.5, 2, -1);// ������� ��� � �����
						SetTime(200);

						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
						SetTime(1500);

						SET_CHAR_HEADING(ped1, 150.0);
						SetTime(2000);

						// ������
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_GC", "COL2_1", 0, 0);//Ze rain, she is tres wet zis time of the year...
						START_SCRIPT_CONVERSATION(1, 1);

						// �������� �������
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 9000 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 9000 );//���������������� �������� �� ����
						SetTime(1000);

						// ���������� swat
						SET_CHAR_COORDINATES(ped2, 439.325, -417.789, 16.121);// ���������� ������
						SET_CHAR_COORDINATES(ped3, 435.535, -417.789, 16.121);// ���������� ������
						SET_CHAR_HEADING(ped2, 5.0);
						SET_CHAR_HEADING(ped3, 5.0);
						SET_CHAR_COORDINATES(ped4, 416.164, -404.718, 4.883);// ���������� ������
						SET_CHAR_COORDINATES(ped5, 416.164, -407.192, 4.883);// ���������� ������
						SET_CHAR_HEADING(ped4, -95.0);
						SET_CHAR_HEADING(ped5, -95.0);
						SET_CHAR_COORDINATES(ped6, 434.698, -405.802, 4.883);// ���������� ������
						SET_CHAR_COORDINATES(ped7, 438.483, -404.522, 4.883);// ���������� ������

						// ����������� ������
						SET_CAR_COORDINATES(car1, 472.664, -364.41, 4.861);// ���������� ������
						SET_CAR_COORDINATES(car2, 475.702, -364.41, 4.861);// ���������� ������
						SET_CAR_HEADING(car1, -45.0);
						SET_CAR_HEADING(car2, -45.0);
						SET_CAR_ENGINE_ON(car2, 1, 1);

						// ��������� swat
						UpdateWeaponOfPed(ped2, WEAPON_MP5);
						UpdateWeaponOfPed(ped3, WEAPON_MP5);
						UpdateWeaponOfPed(ped4, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped6, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
						SetTime(2340);
						SetSpeech();

						// swat ��� � �������
						TASK_GO_STRAIGHT_TO_COORD(ped2, 438.338, -414.568, 16.121, 2, -2);// swat ��� � �������
						TASK_GO_STRAIGHT_TO_COORD(ped3, 436.234, -414.568, 16.121, 2, -2);// swat ��� � �������

						// ����� ������� ������
						POINT_CAM_AT_COORD	( camera, 437.323, -407.423, 12.515 ); // ���� ������� ������
						SET_CAM_POS			( camera, 437.323, -394.819, 10.936 );//������������ ������

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_HA", "COL2_2", 0, 0);//What?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_EB_QQQ1", "COL2_3", 0, 0);//Ah, comment?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_EC", "COL2_4", 0, 0);//Look, Cortez sent me. Just give me the damn chips.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_ZA", "COL2_5", 0, 0);//Oh...d'accord.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// �������� ������������
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "holster_2_aim", "gun@ak47", 1.0, 0, 0, 0, 1, -1 );//���������������� �������� �� ����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "holster_2_aim", "gun@ak47", 1.0, 0, 0, 0, 1, -1 );//���������������� �������� �� ����

						// ����� ������� ������
						POINT_CAM_AT_COORD	( camera, 437.146, -405.239, 9.128 ); // ���� ������� ������
						SET_CAM_POS			( camera, 437.146, -418.711, 20.242 );//������������ ������
						SetTime(500);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_EA", "COL2_6A", 0, 0);//Freeze, imperialist American pig! Zat iz propertay of ze government Francais. 'And eet over!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_EB", "COL2_9", 0, 0);//You American idiot! They followed you here!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(1000);

						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 422.178, -400.601, 4.883, 3, -1, 1.5);// ������� ����� � ������
						SetTime(1800);

						// ������������ ���� � �����
						UpdateWeaponOfPed(ped2, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped3, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_PISTOL, TRUE);
						SET_CHAR_COORDINATES(ped2, 424.877, -397.139, 10.9);// ���������� ������
						SET_CHAR_COORDINATES(ped3, 424.877, -415.179, 10.9);// ���������� ������
						SET_CHAR_HEADING(ped2, 5.0);
						SET_CHAR_HEADING(ped3, 5.0);

						// ����� ������� ������
						POINT_CAM_AT_COORD	( camera, 437.387, -400.745, 8.703 ); // ���� ������� ������
						SET_CAM_POS			( camera, 414.856, -410.971, 4.811 );//������������ ������
						SetTime(3000);

						//������� ������
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL2_B2", 5000, 1);//~g~The courier is fleeing with the guidance chips! Don't let him get away!

						// ������������� ��������
						SET_CHAR_COORDINATES(ped1, 443.712, -372.927, 4.883);// ������������� ��������
						TASK_CAR_DRIVE_WANDER(ped1, car1, 55.0, 2);// ��� ���� ����-��

						// ����� swat
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_SENSE_RANGE(ped2, 20.0);
						SET_SENSE_RANGE(ped3, 20.0);
						SET_SENSE_RANGE(ped4, 20.0);
						SET_SENSE_RANGE(ped5, 20.0);
						SET_SENSE_RANGE(ped6, 20.0);
						SET_SENSE_RANGE(ped7, 20.0);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_COVER(ped7, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
						TASK_COMBAT(ped2, GetPlayerPed());
						TASK_COMBAT(ped3, GetPlayerPed());
						TASK_COMBAT(ped4, GetPlayerPed());
						TASK_COMBAT(ped5, GetPlayerPed());
						TASK_COMBAT(ped6, GetPlayerPed());
						TASK_COMBAT(ped7, GetPlayerPed());
						SET_CHAR_SHOOT_RATE(ped2, 25);
						SET_CHAR_SHOOT_RATE(ped3, 25);
						SET_CHAR_SHOOT_RATE(ped4, 25);
						SET_CHAR_SHOOT_RATE(ped5, 25);
						SET_CHAR_SHOOT_RATE(ped6, 25);
						SET_CHAR_SHOOT_RATE(ped7, 25);
						break;
					}

					else if (IS_CHAR_DEAD(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL2_F1", 5000, 1);//~r~You killed the contact!
						skip = 1;// ���������� ��������
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
					while(true)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped1))
						{
							// �� ���� �������� ����
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
							CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// �����

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_F2", 5000, 1);//~g~The courier is dead. Grab the guidance chips.

							REMOVE_BLIP(cortez_ico);//������� ������ �� ������
							ADD_BLIP_FOR_PICKUP(bag, &cortez_ico);
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ "�����"
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}

						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if ( PlayR > 250.5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_F4", 5000, 1);//~r~The courier has escaped! You failed to get the guidance chips.
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_IN_WATER(ped1))//���� ��� � ����
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_F3", 5000, 1);//~r~The guidance chips are at the bottom of the sea.
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( bag ))
						{
							REMOVE_BLIP(cortez_ico);//������� ������ �� ������

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_B3", 5000, 1);//~g~Take the guidance chips back to the Colonel.
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "���������� ������"
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
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
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							SET_CHAR_COORDINATES(GetPlayerPed(), 191.565, -827.564, 2.028);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), -85.0);
							SetTime(1000);
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							skip = 2;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				REMOVE_PICKUP(bag);// ��������� ������

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������

				// ��������� �� ������ �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//��������� ������ ����(� ����������� ��� ��������

				// ��������� �� ������ ���������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)

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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 500);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +500 );//��� ������ �����
					G_CORTEZ = 3;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Guardian Angels ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				blip_on = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "COL_3A", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("col_3a");
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

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				Car car1, car2, car3, car4, car5, car6, car7, car8, car9, car10, car11;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22;
				Cam camera;
				Object keis;
				Pickup sweap_1, bag;
				int pic_cord1, pic_cord2;
				Texture fon;
				skip = 0;
				stalking = 0;
				in_car = 0;
				del_car = 0;
				gogogo = 0;
				super_ped = 0;
				text = 0;
				clear_ped = 0;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );

				uint PedM1 = MODEL_IG_LILJACOB;// ����
				uint PedM2 = MODEL_IG_BLEDAR;// ����
				uint PedM3 = MODEL_M_Y_GMAF_HI_01;// �������� ����� 1
				uint PedM4 = MODEL_M_Y_GMAF_LO_01;// �������� ����� 2
				uint PedM5 = MODEL_M_Y_GLAT_HI_01;// ������� 1
				uint PedM6 = MODEL_M_Y_GLAT_HI_02;// ������� 2
				uint PedM7 = MODEL_M_M_GJAM_HI_01;// ��������

				uint CarM1 = MODEL_INFERNUS;// ��������
				uint CarM2 = MODEL_ADMIRAL;// �������
				uint CarM3 = MODEL_DUKES;// ����� ������
				uint CarM4 = MODEL_VOODOO;// ����
				uint CarM5 = MODEL_BURRITO;// �������
				uint CarM6 = MODEL_SANCHEZ;// ������

				uint keisM = mission_keis2;// ����
				uint Diaz_hp, Lance_hp;

				// ������ ������
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM3);// 
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM4);// 
				while (!HAS_MODEL_LOADED(PedM4));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM5);// 
				while (!HAS_MODEL_LOADED(PedM5));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM6);// 
				while (!HAS_MODEL_LOADED(PedM6));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM7);// 
				while (!HAS_MODEL_LOADED(PedM7));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(keisM);// �����
				while (!HAS_MODEL_LOADED(keisM)) WAIT(0);;

				REQUEST_MODEL(CarM1);// 
				while (!HAS_MODEL_LOADED(CarM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM2);// 
				while (!HAS_MODEL_LOADED(CarM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM3);// 
				while (!HAS_MODEL_LOADED(CarM3));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM4);// 
				while (!HAS_MODEL_LOADED(CarM4));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM5);// 
				while (!HAS_MODEL_LOADED(CarM5));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM6);// 
				while (!HAS_MODEL_LOADED(CarM6));////�������� "��� ����������" ���� ��� �� �������� � ������

				CREATE_OBJECT_NO_OFFSET(keisM, 0.8, 0.9, -2.4, &keis, TRUE);

				// ������ ���������
				CREATE_CAR(CarM1, 299.551, -779.725, 5.445, &car1, TRUE);// ��������
				CREATE_CAR(CarM2, 295.942, -779.725, 5.445, &car2, TRUE);// �������
				CREATE_CAR(CarM3, 292.585, -779.725, 5.445, &car3, TRUE);// ����� ������
				CREATE_CAR(CarM4, 289.167, -779.725, 5.445, &car4, TRUE);// ����
				CREATE_CAR(CarM4, 286.008, -779.725, 5.445, &car5, TRUE);// ����
				CREATE_CAR(CarM5, 299.551, -787.416, 5.445, &car6, TRUE);// �������
				CREATE_CAR(CarM5, 295.942, -787.416, 5.445, &car7, TRUE);// �������
				CREATE_CAR(CarM4, 292.585, -787.416, 5.445, &car8, TRUE);// ����
				CREATE_CAR(CarM6, 289.167, -787.416, 5.445, &car9, TRUE);// ������
				CREATE_CAR(CarM6, 286.008, -787.416, 5.445, &car10, TRUE);// ������
				LOCK_CAR_DOORS(car2, 3); // �������� ����������
				LOCK_CAR_DOORS(car10, 3); // �������� ����������

				CHANGE_CAR_COLOUR( car1, 112, 112 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car9, 89, 89 );//���� ������
				SET_EXTRA_CAR_COLOURS( car9, 27, 27 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car10, 89, 89 );//���� ������
				SET_EXTRA_CAR_COLOURS( car10, 27, 27 );//���� ��������� ������

				// ������ ����� �� ����
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// �������� �� ���� ����
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped2);// ������� �� ���� ����
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM5, &ped5);// ����� ������ �� ���� ������� 1
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM7, &ped7);// ���� �� ���� ��������
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM7, &ped9);// ���� �� ���� ��������
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM7, &ped11);// ������� �� ���� ��������
				CREATE_CHAR_INSIDE_CAR(car7, 1, PedM7, &ped15);// ������� �� ���� ��������
				CREATE_CHAR_INSIDE_CAR(car8, 1, PedM7, &ped19);// ���� �� ���� ��������
				CREATE_CHAR_INSIDE_CAR(car9, 1, PedM7, &ped21);// ������ �� ���� ��������
				CREATE_CHAR_INSIDE_CAR(car10, 1, PedM7, &ped22);// ������ �� ���� ��������

				// ������ ����� ����������
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 1, &ped3);// ������� �������� �������� ����� 1
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM4, 0, &ped4);// ������� �������� �������� ����� 2
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM6, 0, &ped6);// ����� ������ �������� ������� 2
				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM7, 0, &ped8);// ���� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car5, 1, PedM7, 0, &ped10);// ���� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM7, 0, &ped12);// ������� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM7, 1, &ped13);// ������� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM7, 2, &ped14);// ������� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM7, 0, &ped16);// ������� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM7, 1, &ped17);// ������� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM7, 2, &ped18);// ������� �������� ��������
				CREATE_CHAR_AS_PASSENGER(car8, 1, PedM7, 0, &ped20);// ���� �������� ��������

				// ������ ��������
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				// ������ ����
				REQUEST_CAR_RECORDING( 2999 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2999 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3000 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3000 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3001 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3001 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3002 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3002 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3003 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3003 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3004 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3004 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3005 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3005 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3006 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3006 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3007 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3007 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3008 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3008 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3009 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3009 )) WAIT(0);

				CREATE_PICKUP_ROTATE(w_ak47, 3, 120, 591.236, -657.675, 12.279, 92.468, -71.444, -1.476, &sweap_1);// ��� ��������
				ADD_BLIP_FOR_PICKUP(sweap_1, &cortez_ico);
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"
				GET_BLIP_COORDS(cortez_ico, &pic_cord1);// �����

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R14_WC", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "GEN3_20", 5000, 1);//~g~The Colonel has arranged some firepower for you at the multistory carpark.
				SetTime(1000);

				// ���������� ������
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
				SET_CHAR_RELATIONSHIP(ped4, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
				SET_CHAR_RELATIONSHIP(ped5, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 0);
				SET_CHAR_RELATIONSHIP(ped6, 5, 24);

				while(true)
				{
					GET_BLIP_COORDS(cortez_ico, &pic_cord2);// �����
					WAIT(0);
					if ((HAS_PLAYER_COLLECTED_PICKUP(GetPlayerIndex(), sweap_1)) || (pic_cord2 != pic_cord1))// �����
					{
						REMOVE_BLIP(cortez_ico);//������� ������ �� ������
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

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 568.505, -669.958, 10.557); // ���� ������� ������
						SET_CAM_POS			( camera, 589.701, -661.164, 13.531 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						CLEAR_AREA(565.183, -677.905, 9.607, 10.0, 1);//������� ���� ��������
						CLEAR_AREA(582.581, -663.427, 11.426, 15.0, 1);//������� ���� ��������
						SET_CHAR_COORDINATES(GetPlayerPed(), 589.384, -660.17, 12.036);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), 120.0);
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2999, 0.0, 0.0, 0.0);// ������� �����
						SetTime(7000);
					
						// ������ ������
						POINT_CAM_AT_COORD	( camera, 585.171, -661.506, 12.827); // ���� ������� ������
						SET_CAM_POS			( camera, 588.315, -668.298, 12.885 );//������������ ������

						STOP_PLAYBACK_RECORDED_CAR(car1);
						TASK_GO_STRAIGHT_TO_COORD(ped1, 585.034, -662.539, 12.33, 2, -1);// ����� ��� � �����
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 585.981, -661.875, 12.33, 2, -1);// ���� ��� � �����
						SetTime(1000);

						// ������������� ����
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_ED", "GEN3_1", 0, 0);//Hogging all the action, I see...
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_FA", "GEN3_2", 0, 0);//Look, you wanna do something other than just shadowing me everywhere? Why don't you come along and show me if you're any use.
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(5000);
						SetSpeech();

						// �������� ��������� �����
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//���������������� �������� �� ����
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_FB", "GEN3_3", 0, 0);//I might just do that. The name's Lance, by the way.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_GA", "GEN3_4", 0, 0);//Tommy Vercetti. Let's go...
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//������� ������
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

						del_car = 1;
						MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
						MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)

						ADD_BLIP_FOR_COORD(891.904, 26.789, 4.831, &cortez_ico);//������� ������ �� ������
						CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
						CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "������� ������"
						PRINT_STRING_IN_STRING("string", "GEN3_44", 5000, 1);//~g~Go with Lance to the drop off and watch over Diaz.
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
					while(true)
					{
						WAIT(0);
						// ���� ��������� �� �����
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car11);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car11, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car11);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car11);
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car11, 0);
							}
							if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+5, PedY+5, PedZ+5, PedX-5, PedY-5, PedZ-5, 0 ))
								{
									TASK_GO_STRAIGHT_TO_COORD(ped1, PlayX, PlayY, PlayZ, 4, -2);
								}
							}
							if (stalking == 1)
							{
								stalking = 0;
							}
						}
						else
						{
							if (stalking == 0)
							{
								stalking = 1;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~g~You've left Lance behind! Go and get him!
							}
						}


						DRAW_CHECKPOINT( 891.904, 26.789, 4.831, 2.0, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 891.904, 26.789, 4.831, &PedR);//�������� "����� �� �����������"
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 891.904, 26.789, 4.831, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 2.0) && ( PedR < 2.0))
						{
							REMOVE_BLIP(cortez_ico);//������� ������ �� ������

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

							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									TASK_LEAVE_CAR(ped1, car11);
								}
								TASK_LEAVE_CAR(GetPlayerPed(), car11);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car11);
							}

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 891.904, 26.789, 5.403); // ���� ������� ������
							SET_CAM_POS			( camera, 886.86, 3.537, 15.38 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							CLEAR_AREA(894.659, 54.979, 4.954, 15.0, 1);//������� ���� ��������
							DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3000, 0.0, 0.0, 0.0);// ������� �����
							SetTime(3000);
						
							// ������ ������
							POINT_CAM_AT_COORD	( camera, 894.318, 44.199, 5.192); // ���� ������� ������
							SET_CAM_POS			( camera, 893.822, 34.996, 6.659 );//������������ ������

							STOP_PLAYBACK_RECORDED_CAR(car2);
							TASK_GO_STRAIGHT_TO_COORD(ped2, 894.208, 38.563, 5.231, 2, -1);// ���� ��� � �����
							SetTime(500);
							TASK_GO_STRAIGHT_TO_COORD(ped3, 895.002, 39.167, 5.231, 2, -1);// ��������_1 ��� � �����
							SetTime(500);
							TASK_GO_STRAIGHT_TO_COORD(ped4, 893.113, 39.177, 5.231, 2, -1);// ��������_2 ��� � �����
							SetTime(5000);

							CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//������� ���� ��������
							SET_CHAR_COORDINATES(GetPlayerPed(), 893.265, 35.292, 5.276);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), 0.0);
							SET_CHAR_COORDINATES(ped1, 894.673, 35.153, 5.276);// ���������� �����
							SET_CHAR_HEADING(ped1, 5.0);
							SetTime(2000);

							// ������ ������
							POINT_CAM_AT_COORD	( camera, 896.823, 35.329, 4.878); // ���� ������� ������
							SET_CAM_POS			( camera, 888.071, 41.434, 7.708 );//������������ ������
							SetTime(3000);
							
							// ������������� ����
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GB", "GEN3_5", 0, 0);//You must be Cortez's new gun.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//���������������� �������� �� ����
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GC", "GEN3_6", 0, 0);//Until more gainful opportunities arise.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//���������������� �������� �� ����
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// ������ ������
							POINT_CAM_AT_COORD	( camera, 893.955, 34.872, 5.658); // ���� ������� ������
							SET_CAM_POS			( camera, 896.875, 40.563, 6.79 );//������������ ������

							SET_CHAR_HEADING(ped1, 65.0);
							SET_CHAR_HEADING(GetPlayerPed(), -90.0);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GD", "GEN3_7", 0, 0);//They'll be here any minute - we both better get a good vantage point...
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//���������������� �������� �� ����
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GE", "GEN3_8", 0, 0);// OK! I'll take the balcony, you get the roof across the yard.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//���������������� �������� �� ����
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							//������� ������
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

							// ��� ������
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 894.78, 14.377, 12.23, 3, -1, 1.5);// ���� ����� �� ������
							UpdateWeaponOfPed(ped1, WEAPON_AK47);
							UpdateWeaponOfPed(ped2, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped3, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped4, WEAPON_MICRO_UZI);
							SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MICRO_UZI, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MICRO_UZI, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MICRO_UZI, TRUE);
							SET_SENSE_RANGE(ped1, 80.0);

							ADD_BLIP_FOR_COORD(887.101, 28.852, 11.917, &cortez_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "������� ������"
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEGEN3_P", 5000, 1);//Take an observation point.
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 887.101, 28.852, 11.917, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 887.101, 28.852, 11.917, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 1.5)
						{
							REMOVE_BLIP(cortez_ico);//������� ������ �� ������
							SET_CHAR_HEALTH(ped1, 500);
							SET_CHAR_HEALTH(ped2, 500);
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);
							SET_MAX_WANTED_LEVEL(0);

							CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//������� ���� ��������
							CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//������� ���� ��������
							SET_CHAR_COORDINATES(ped1, 894.78, 14.377, 12.23);// ���������� �����
							SET_CHAR_HEADING(ped1, 60.0);
							FREEZE_CHAR_POSITION(ped1, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, TRUE);

							SET_CHAR_COORDINATES(ped2, 894.208, 38.563, 5.108);// ���������� �����
							SET_CHAR_HEADING(ped2, 180.0);

							// ������ ������
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_37", 5000, 1);//~g~Here come the Cubans. Watch over the deal making sure Diaz and Lance are safe.
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 893.401, 35.232, 9.185); // ���� ������� ������
							SET_CAM_POS			( camera, 893.585, 64.332, 15.034 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// ������ ������� ��������
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3001, 0.0, 0.0, 0.0);// ������� ��������
							SetTime(5000);

							STOP_PLAYBACK_RECORDED_CAR(car3);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, 893.226, 36.905, 5.967, 2, -1, 0.7);// �������_1 ��� � �����
							SetTime(500);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, 894.634, 36.767, 5.967, 2, -1, 0.7);// �������_2 ��� � �����
							SetTime(5000);	

							//������� ������
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							SET_CHAR_COORDINATES(ped5, 893.226, 36.905, 5.074);// ���������� �������_1
							SET_CHAR_HEADING(ped5, -30.0);

							UpdateWeaponOfPed(ped5, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped6, WEAPON_MICRO_UZI);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_MICRO_UZI, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MICRO_UZI, TRUE);
							SETTIMERB( 0 );
							wave = 0;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 916.686, 1.867, 3.615, 866.686, 51.867, 33.615, 0 ))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						// HUD �������� ����� � �����
						GET_CHAR_HEALTH(ped1, &Lance_hp);
						GET_CHAR_HEALTH(ped2, &Diaz_hp);
						pedHUD_x = 0.922156;
						pedHUD_w = 0.0739583;

						// -------------------------- Diaz HUD --------------------------
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
						DRAW_SPRITE( 0, 0.915054, 0.74213, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// ������ ������� ��������.
						if (Diaz_hp < 105)
						{
							DiazH1 = 0;
						}
						else
						{
							DiazH1 = Diaz_hp-100;
						}
						DiazH2 = pedHUD_w/500;
						DiazH3 = DiazH2*DiazH1;
						DiazHUD_y1 = pedHUD_w-DiazH3;
						DiazHUD_y2 = DiazHUD_y1/2;
						DiazHUD_y3 = pedHUD_x-DiazHUD_y2;
						DRAW_SPRITE( 0, DiazHUD_y3, 0.74213, DiazH3, 0.014, 0.0, 97, 194, 247, 255 );// ������ ������� ��������.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.73564852, "GEN3_22"); //DIAZ'S HEALTH:

						// -------------------------- Lance HUD --------------------------
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
						DRAW_SPRITE( 0, 0.915054, 0.7838, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// ������ ������� ��������.
						if (Lance_hp < 105)
						{
							LanceH1 = 0;
						}
						else
						{
							LanceH1 = Lance_hp-100;
						}
						LanceH2 = pedHUD_w/500;
						LanceH3 = LanceH2*LanceH1;
						LanceHUD_y1 = pedHUD_w-LanceH3;
						LanceHUD_y2 = LanceHUD_y1/2;
						LanceHUD_y3 = pedHUD_x-LanceHUD_y2;
						DRAW_SPRITE( 0, LanceHUD_y3, 0.7838, LanceH3, 0.014, 0.0, 97, 194, 247, 255 );// ������ ������� ��������.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.77731852, "GEN3_49"); //LANCE'S HEALTH:

						if (wave == 0)
						{
							if ((IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)))// �������� ���� ����� ������
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_33", 5000, 1);//~r~Check your fire!! You're supposed to be watching over Diaz and his men, not shooting them!
								skip = 1;// ���������� ��������
								break;
							}
							else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)))// �������� ������� ������
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_34", 5000, 1);//~r~There ain't gonna be a deal if you shoot the Cubans!
								skip = 1;// ���������� ��������
								break;
							}
						}
						
						if (TIMERB() > 10000)
						{
							if (wave == 0)
							{
								SET_OBJECT_COORDINATES(keis, 893.853, 37.61, 5.061);// ������ ����
								SETTIMERB( 0 );
								wave = 1;
							}
							else if (wave == 1)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped7, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//������� ���� ��������
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3002, 0.0, 0.0, 0.0);// ������� ����1
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "GEN3_19", 5000, 1);//~g~Haitians! They're busting the deal! Protect Diaz!
									gogogo = 1;
								}
								if (TIMERB() > 21000)
								{
									// �����
									UpdateWeaponOfPed(ped7, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped8, WEAPON_MICRO_UZI);
									SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_MICRO_UZI, TRUE);

									SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
									SET_CHAR_RELATIONSHIP(ped7, 5, 0);
									SET_CHAR_RELATIONSHIP(ped8, 5, 0);
									SET_SENSE_RANGE(ped7, 80.0);
									SET_SENSE_RANGE(ped8, 80.0);
									SET_CHAR_WILL_USE_COVER(ped7, 1);
									SET_CHAR_WILL_USE_COVER(ped8, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
									SET_CHAR_SHOOT_RATE(ped7, 45);
									SET_CHAR_SHOOT_RATE(ped8, 35);
									STOP_PLAYBACK_RECORDED_CAR(car4);
									REMOVE_BLIP(cortez_ico);//������� ������ �� ������

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 2;
								}
							}
							else if (wave == 2)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped9, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//������� ���� ��������
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car5, 3003, 0.0, 0.0, 0.0);// ������� ����2
									gogogo = 1;
								}
								if (TIMERB() > 20000)
								{
									// �����
									UpdateWeaponOfPed(ped9, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped10, WEAPON_MICRO_UZI);
									SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_MICRO_UZI, TRUE);

									SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
									SET_CHAR_RELATIONSHIP(ped9, 5, 0);
									SET_CHAR_RELATIONSHIP(ped10, 5, 0);
									SET_SENSE_RANGE(ped9, 80.0);
									SET_SENSE_RANGE(ped10, 80.0);
									SET_CHAR_WILL_USE_COVER(ped9, 1);
									SET_CHAR_WILL_USE_COVER(ped10, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
									SET_CHAR_SHOOT_RATE(ped9, 55);
									SET_CHAR_SHOOT_RATE(ped10, 35);
									STOP_PLAYBACK_RECORDED_CAR(car5);
									REMOVE_BLIP(cortez_ico);//������� ������ �� ������

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 3;
								}
							}
							else if (wave == 3)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped11, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//������� ���� ��������
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3004, 0.0, 0.0, 0.0);// ������� �������1
									gogogo = 1;
								}
								if (TIMERB() > 13000)
								{
									// �����
									UpdateWeaponOfPed(ped11, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped12, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped13, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped14, WEAPON_MICRO_UZI);
									SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_MICRO_UZI, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
									SET_CHAR_RELATIONSHIP(ped11, 5, 0);
									SET_CHAR_RELATIONSHIP(ped12, 5, 0);
									SET_CHAR_RELATIONSHIP(ped13, 5, 0);
									SET_CHAR_RELATIONSHIP(ped14, 5, 0);
									SET_SENSE_RANGE(ped11, 80.0);
									SET_SENSE_RANGE(ped12, 80.0);
									SET_SENSE_RANGE(ped13, 80.0);
									SET_SENSE_RANGE(ped14, 80.0);
									SET_CHAR_WILL_USE_COVER(ped11, 1);
									SET_CHAR_WILL_USE_COVER(ped12, 1);
									SET_CHAR_WILL_USE_COVER(ped13, 1);
									SET_CHAR_WILL_USE_COVER(ped14, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
									SET_CHAR_SHOOT_RATE(ped11, 25);
									SET_CHAR_SHOOT_RATE(ped12, 45);
									SET_CHAR_SHOOT_RATE(ped13, 35);
									SET_CHAR_SHOOT_RATE(ped14, 25);
									STOP_PLAYBACK_RECORDED_CAR(car6);
									REMOVE_BLIP(cortez_ico);//������� ������ �� ������

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 4;
								}
							}
							else if (wave == 4)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped15, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"

									CLEAR_AREA(894.659, 54.979, 4.831, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(897.339, 83.125, 3.854, 15.0, 1);//������� ���� ��������
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car7, 3006, 0.0, 0.0, 0.0);// ������� �������2
									gogogo = 1;
								}
								if (TIMERB() > 19000)
								{
									// �����
									UpdateWeaponOfPed(ped15, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped16, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped17, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped18, WEAPON_MICRO_UZI);
									SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_MICRO_UZI, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
									SET_CHAR_RELATIONSHIP(ped15, 5, 0);
									SET_CHAR_RELATIONSHIP(ped16, 5, 0);
									SET_CHAR_RELATIONSHIP(ped17, 5, 0);
									SET_CHAR_RELATIONSHIP(ped18, 5, 0);
									SET_SENSE_RANGE(ped15, 80.0);
									SET_SENSE_RANGE(ped16, 80.0);
									SET_SENSE_RANGE(ped17, 80.0);
									SET_SENSE_RANGE(ped18, 80.0);
									SET_CHAR_WILL_USE_COVER(ped15, 1);
									SET_CHAR_WILL_USE_COVER(ped16, 1);
									SET_CHAR_WILL_USE_COVER(ped17, 1);
									SET_CHAR_WILL_USE_COVER(ped18, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
									SET_CHAR_SHOOT_RATE(ped15, 35);
									SET_CHAR_SHOOT_RATE(ped16, 25);
									SET_CHAR_SHOOT_RATE(ped17, 65);
									SET_CHAR_SHOOT_RATE(ped18, 25);
									STOP_PLAYBACK_RECORDED_CAR(car7);
									REMOVE_BLIP(cortez_ico);//������� ������ �� ������

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 5;
								}
							}
							else if (wave == 5)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped19, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//������� ���� ��������
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car8, 3005, 0.0, 0.0, 0.0);// ������� ����3
									gogogo = 1;
								}
								if (TIMERB() > 17000)
								{
									// �����
									UpdateWeaponOfPed(ped19, WEAPON_MICRO_UZI);
									UpdateWeaponOfPed(ped20, WEAPON_MICRO_UZI);
									SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MICRO_UZI, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MICRO_UZI, TRUE);

									SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
									SET_CHAR_RELATIONSHIP(ped19, 5, 0);
									SET_CHAR_RELATIONSHIP(ped20, 5, 0);
									SET_SENSE_RANGE(ped19, 80.0);
									SET_SENSE_RANGE(ped20, 80.0);
									SET_CHAR_WILL_USE_COVER(ped19, 1);
									SET_CHAR_WILL_USE_COVER(ped20, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
									SET_CHAR_SHOOT_RATE(ped19, 45);
									SET_CHAR_SHOOT_RATE(ped20, 55);
									STOP_PLAYBACK_RECORDED_CAR(car8);
									REMOVE_BLIP(cortez_ico);//������� ������ �� ������

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 6;
								}
							}
							else if (wave == 6)
							{
								if (gogogo == 0)
								{
									// ������� ����
									SET_CHAR_COORDINATES_NO_OFFSET(ped2, 893.469, 43.037, 5.108);// ���������� 
									SET_CHAR_HEADING(ped2, -160.0);

									CLEAR_AREA(897.339, 83.125, 4.951, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(894.659, 54.979, 4.951, 15.0, 1);//������� ���� ��������
									CLEAR_AREA(884.946, 5.731, 3.854, 20.0, 1);//������� ���� ��������
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car9, 3008, 0.0, 0.0, 0.0);// ������� ������ 1
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car10, 3007, 0.0, 0.0, 0.0);// ������� ������ 2
									
									// ������ ������
									GET_CHAR_COORDINATES(ped21,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
									CREATE_CAM( 14, &camera );
									POINT_CAM_AT_COORD	( camera, PedX+0.617, PedY-2.174, PedZ+0.457); // ���� ������� ������
									SET_CAM_POS			( camera, PedX+0.617, PedY+3.544, PedZ+0.505 );//������������ ������
									SET_CAM_ACTIVE( camera, 1 );
									SET_CAM_PROPAGATE( camera, 1 );
									ACTIVATE_SCRIPTED_CAMS(1, 1);
									SET_CAM_FOV( camera, 45.0 );
									SET_WIDESCREEN_BORDERS( 1 );

									SET_CAR_COORDINATES(car2, 893.78, 46.3, 5.445);// ���������� ������
									SET_CAR_COORDINATES(car7, 295.942, -787.416, 5.445);// ���������� ������
									SET_CAR_COORDINATES(car8, 292.585, -787.416, 5.445);// ���������� ������
									SET_CAR_HEADING(car2, 176.41);
									SET_CAR_HEADING(car7, 0.0);
									SET_CAR_HEADING(car8, 0.0);
									SETTIMERB( 0 );
									text = 0;
									

									while(true)
									{
										WAIT(0);
										if (text == 0)
										{
											// ������ 1
											GET_CHAR_COORDINATES(ped21,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
											POINT_CAM_AT_COORD	( camera, PedX+0.617, PedY-2.174, PedZ+0.457); // ���� ������� ������
											SET_CAM_POS			( camera, PedX+0.617, PedY+3.544, PedZ+0.505 );//������������ ������
										}
										else
										{
											// ������ 2
											GET_CHAR_COORDINATES(ped22,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
											POINT_CAM_AT_COORD	( camera, PedX, PedY, PedZ); // ���� ������� ������
											SET_CAM_POS			( camera, 888.129, 27.327, 10.96 );//������������ ������
										}

										if (((IS_CHAR_IN_AREA_3D( ped22, 898.26, 32.856, 4.897, 888.26, 44.702, 14.897, 0 )) && (text == 0)) || ((TIMERB() > 20000) && (text == 0)))
										{
											SETTIMERB( 0 );
											text = 1;
										}
										if ((text == 1) && (TIMERB() > 500))
										{
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_GF", "GEN3_53", 0, 0);// MY MONEY!
											START_SCRIPT_CONVERSATION(1, 1);
											SET_OBJECT_COORDINATES(keis, 0.853, 0.61, -5.061);// ������ ����
											SETTIMERB( 0 );
											text = 2;
										}
										if ((text == 2) && (TIMERB() > 1600))
										{
											SetSpeech();
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_GG", "", 0, 0);// �������
											START_SCRIPT_CONVERSATION(1, 1);

											EXPLODE_CHAR_HEAD(ped21);
											STOP_PLAYBACK_RECORDED_CAR(car9);
											SetSpeech();
											break;
										}

									}
									SetTime(2000);	

									// ������� ������
									ACTIVATE_SCRIPTED_CAMS( 0, 0 );
									DESTROY_CAM( camera );
									SET_WIDESCREEN_BORDERS( 0 );
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R4_GH", "GEN3_54", 0, 0);//Don't just stand there, you pricks, chase that Haitian dickhead down!
									START_SCRIPT_CONVERSATION(1, 1);

									SET_CAR_COORDINATES(car9, 884.92, -11.548, 5.445);// ���������� ������
									SET_CAR_HEADING(car9, 160.00);

									ADD_BLIP_FOR_CHAR(ped22, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // ������� ������ �� ������
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"
									SetTime(2000);
									SetSpeech();

									STOP_PLAYBACK_RECORDED_CAR(car10);
									TASK_CAR_DRIVE_WANDER(ped22, car10, 20.0, 2);// ��� ���� ����-��
									SetTime(2000);
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "GEN3_36", 5000, 1);//~g~Grab the bike, chase him down and get Diaz's money back!

									SETTIMERB( 0 );
									SETTIMERC( 0 );
									super_ped = 1;
									gogogo = 0;
									wave = 7;
									break;
								}
							}
						}
						if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 916.686, 1.867, 3.615, 866.686, 51.867, 33.615, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_56", 5000, 1);//~r~Diaz was ambushed and died! Next time keep him in your sights!
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (Lance_hp < 100)
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (Diaz_hp < 100)
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (super_ped == 1)
						{
							SET_CHAR_INVINCIBLE(ped22, 1);
							if (TIMERC() > 25000)
							{
								SET_CHAR_INVINCIBLE(ped22, 0);
								super_ped = 0;
							}
						}
						if (IS_CHAR_DEAD(ped22))
						{
							REMOVE_BLIP(cortez_ico);//������� ������ �� ������
							GET_CHAR_COORDINATES(ped22,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);

							CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// �����
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_29", 5000, 1);//~g~Collect the briefcase and take it back to Diaz.

							ADD_BLIP_FOR_PICKUP(bag, &cortez_ico);
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ "�����"
							break;
						}

						if ((TIMERB() > 6000) && (gogogo == 0) && (!IS_CHAR_DEAD(ped22)))
						{
							TASK_CAR_DRIVE_WANDER(ped22, car10, 40.0, 2);// ��� ���� ����-��
							gogogo = 1;
						}

						GET_CHAR_COORDINATES(ped22,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if ( PlayR > 250.5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_30", 5000, 1);//~r~He got away with the money! Diaz will have your balls for this!
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( bag ))
						{
							FIX_CAR(car2);// ����� ������ �����
							FIX_CAR(car3);// ����� ������ 
							FIX_CAR(car4);// ����� ������ 
							SET_CHAR_HEALTH(ped1, 400);
							SET_CHAR_HEALTH(ped2, 400);
							WAIT(500);


							SET_CAR_COORDINATES(car2, 894.18, 42.15, 5.73);// ���������� ������
							SET_CAR_HEADING(car2, 175.0);
							TASK_ENTER_CAR_AS_DRIVER(ped2, car2, TRUE);// ����� ����� � ������
							WAIT(500);
						
							// ������ �����
							SET_CHAR_COORDINATES(ped1, 291.135, -767.684, 5.06);// ���������� 
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
							CLEAR_AREA(888.8, 11.1, 5.5, 75.5, 0);//������� ���� ��������
							clear_ped = 1;

							/*/ ������ �����
							SET_CHAR_COORDINATES(ped3, 292.135, -767.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped4, 293.135, -767.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped5, 294.135, -767.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped6, 295.135, -767.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped7, 291.135, -766.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped8, 292.135, -766.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped9, 293.135, -766.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped10, 294.135, -766.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped11, 295.135, -766.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped12, 291.135, -765.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped13, 292.135, -765.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped14, 293.135, -765.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped15, 294.135, -765.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped16, 295.135, -765.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped17, 291.135, -764.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped18, 292.135, -764.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped19, 293.135, -764.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped20, 294.135, -764.684, 5.06);// ���������� 
							SET_CHAR_COORDINATES(ped21, 295.135, -764.684, 5.06);// ���������� 
							WAIT(500);
							//*/

							// ������ ������ �����
							SET_CAR_COORDINATES(car3, 899.157, 37.433, 5.065);// ���������� ������
							SET_CAR_COORDINATES(car4, 896.312, 30.915, 5.065);// ���������� ������
							SET_CAR_COORDINATES(car5, 286.008, -779.725, 5.445);// ���������� ������
							SET_CAR_COORDINATES(car6, 299.551, -787.416, 5.445);// ���������� ������
							SET_CAR_COORDINATES(car7, 295.942, -787.416, 5.445);// ���������� ������
							SET_CAR_COORDINATES(car8, 292.585, -787.416, 5.445);// ���������� ������
							SET_CAR_HEADING(car3, -15.0);
							SET_CAR_HEADING(car4, -25.0);
							SET_CAR_HEADING(car5, 0.0);
							SET_CAR_HEADING(car6, 0.0);
							SET_CAR_HEADING(car7, 0.0);
							SET_CAR_HEADING(car8, 0.0);
							WAIT(500);

							REMOVE_BLIP(cortez_ico);//������� ������ �� ������
							ADD_BLIP_FOR_COORD(895.972, 42.967, 4.954, &cortez_ico);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""
							PRINT_STRING_IN_STRING("string", "GEN3_28", 5000, 1);//~g~Take the briefcase back to Diaz.
							WAIT(500);
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 895.972, 42.967, 4.954, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 895.972, 42.967, 4.954, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							FIX_CAR(car2);// ����� ������ 
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3009, 0.0, 0.0, 0.0);
							PAUSE_PLAYBACK_RECORDED_CAR(car2);
							SET_CHAR_COORDINATES(GetPlayerPed(), 895.662, 41.629, 5.156);// ���������� ������
							SET_CHAR_HEADING(GetPlayerPed(), 80.0);

							// ������ ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 895.585, 42.791, 5.664); // ���� ������� ������
							SET_CAM_POS			( camera, 891.361, 38.441, 6.598 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// ������������� �����.
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HA", "GEN3_9", 0, 0);//I live! Dickheads! And it's all down to you! What is your name?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();	

							// ����� �������
							POINT_CAM_AT_COORD	( camera, 892.826, 40.272, 5.193); // ���� ������� ������
							SET_CAM_POS			( camera, 897.216, 46.511, 6.773 );//������������ ������

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HB", "GEN3_10", 0, 0);//Tommy.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();


							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HC", "GEN3_11", 0, 0);//I see you soon, amigo, I think!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
							SetTime(3000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HD", "GEN3_12", 0, 0);//Shit. Where's that guy Lance?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// ������� ������
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

							SET_CAR_COORDINATES(car10, 289.167, -787.416, 5.445);// ���������� ������
							SET_CAR_HEADING(car10, 0.0);
							FIX_CAR(car9);// ����� ������ 
							SET_CAR_COORDINATES(car9, 895.007, 25.38, 5.445);// ���������� ������
							SET_CAR_HEADING(car9, -15.0);

							STOP_PLAYBACK_RECORDED_CAR(car2);
							SET_CAR_COORDINATES(car2, 295.942, -779.725, 5.445);// ���������� ������
							SET_CAR_HEADING(car2, 0.0);
							skip = 2;// ���������� ��������
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}

				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				REMOVE_PICKUP(sweap_1);// ��������� ������
				REMOVE_PICKUP(bag);// ��������� ����
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);
				SET_MAX_WANTED_LEVEL(6);

				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				STOP_PLAYBACK_RECORDED_CAR(car1);
				STOP_PLAYBACK_RECORDED_CAR(car2);
				STOP_PLAYBACK_RECORDED_CAR(car3);
				STOP_PLAYBACK_RECORDED_CAR(car4);
				STOP_PLAYBACK_RECORDED_CAR(car5);
				STOP_PLAYBACK_RECORDED_CAR(car6);
				STOP_PLAYBACK_RECORDED_CAR(car7);
				STOP_PLAYBACK_RECORDED_CAR(car8);
				STOP_PLAYBACK_RECORDED_CAR(car9);
				STOP_PLAYBACK_RECORDED_CAR(car10);

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM6);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(keisM);//��������� ������

				// ��������� �� ������ �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				if (clear_ped == 0)
				{
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
				}


				if (del_car == 0)
				{
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				}

				// ��������� �� ������ ���������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car8);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car9);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car10);//��������� ������ ������(� ����������� ������ ��������)

				// ��������� ���� ����������
				REMOVE_CAR_RECORDING( 2999 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3000 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3001 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3002 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3003 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3004 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3005 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3006 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3007 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3008 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3009 ); // ��������� ���� ����������

				DELETE_OBJECT(&keis);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&keis);
				if (car11 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car11);//��������� ������ ������(� ����������� ������ ��������)
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
					G_CORTEZ = 4;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Sir, Yes Sir! ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 5))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				blip_on = 0;
				skip = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "COL_4A", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("col_4a");
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

				Car car1, car2, car3, car4, car5;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22;
				Texture fon;

				uint PedM1 = MODEL_M_Y_GBIK_LO_02;// ������
				uint CarM1 = MODEL_PATRIOT;// �������
				uint CarM2 = MODEL_BIFF;// ��������
				uint CarM3 = MODEL_PSTOCKADE;// ����
				
				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );

				ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				in_zon = 0;
				hate = 0;
				help_1 = 0;
				help_2 = 0;
				play = 0;
				in_car = 0;
				del_car = 0;
				passenger = 0;
				point = 1;
				terpenie = 0;
				car_blip = 0;
				delta = 0;
				hud_on = 0;
				boom = 0;
				garage = 0;
				in_garage = 0;
				Speech = 0;
				pedHUD_x = 0.9088541;
				pedHUD_w = 0.0739583;

				// ������ ������
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM1);// 
				while (!HAS_MODEL_LOADED(CarM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM2);// 
				while (!HAS_MODEL_LOADED(CarM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM3);// 
				while (!HAS_MODEL_LOADED(CarM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ���������
				CREATE_CAR(CarM1, -423.002, 369.767, 5.417, &car1, TRUE);// �������
				CREATE_CAR(CarM2, -423.002, 378.171, 5.417, &car2, TRUE);// ��������
				CREATE_CAR(CarM3, -423.002, 386.576, 5.417, &car3, TRUE);// ����
				CREATE_CAR(CarM2, -423.002, 394.981, 5.417, &car4, TRUE);// ��������
				CREATE_CAR(CarM1, 286.008, -779.725, 5.445, &car5, TRUE);// ����
				SET_CAR_HEADING(car1, 180.0);
				SET_CAR_HEADING(car2, 180.0);
				SET_CAR_HEADING(car3, 180.0);
				SET_CAR_HEADING(car4, 180.0);

				LOCK_CAR_DOORS(car1, 3); // �������� ����������
				LOCK_CAR_DOORS(car2, 3); // �������� ����������
				LOCK_CAR_DOORS(car3, 3); // �������� ����������
				LOCK_CAR_DOORS(car4, 3); // �������� ����������
				TURN_OFF_VEHICLE_EXTRA( car2, 2, 1 );
				TURN_OFF_VEHICLE_EXTRA( car4, 2, 1 );

				CHANGE_CAR_COLOUR( car1, 96, 96 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car2, 112, 112 );//���� ������
				SET_EXTRA_CAR_COLOURS( car2, 112, 112 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car3, 112, 112 );//���� ������
				SET_EXTRA_CAR_COLOURS( car3, 112, 112 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car4, 112, 112 );//���� ������
				SET_EXTRA_CAR_COLOURS( car4, 112, 112 );//���� ��������� ������

				// ������ ����� �� ����
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// ������� �� ���� ������
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped2);// �������� �� ���� ������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);// ���� �� ���� ������
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM1, &ped4);// �������� �� ���� ������

				// ������ ����� ����������
				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM1, 0, &ped5);// ������� �������� ������
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM1, 0, &ped6);// �������� �������� ������
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM1, 0, &ped7);// ���� �������� ������
				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM1, 0, &ped8);// �������� �������� ������

				// ������ �����
				CREATE_CHAR (26, PedM1, -426.583, 377.662, 5.094, &ped9, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -419.908, 377.662, 5.094, &ped10, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -426.583, 379.739, 5.094, &ped11, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -419.908, 379.739, 5.094, &ped12, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -425.881, 393.487, 5.094, &ped13, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -419.781, 393.487, 5.094, &ped14, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -425.881, 395.564, 5.094, &ped15, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -419.781, 395.564, 5.094, &ped16, TRUE);// ������� 1

				CREATE_CHAR (26, PedM1, -426.002, 383.576, 5.094, &ped17, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -426.002, 386.576, 5.094, &ped18, TRUE);// ������� 2
				CREATE_CHAR (26, PedM1, -426.002, 389.576, 5.094, &ped19, TRUE);// ������� 3
				CREATE_CHAR (26, PedM1, -420.002, 383.576, 5.094, &ped20, TRUE);// ������� 1
				CREATE_CHAR (26, PedM1, -420.002, 386.576, 5.094, &ped21, TRUE);// ������� 2
				CREATE_CHAR (26, PedM1, -420.002, 389.576, 5.094, &ped22, TRUE);// ������� 3

				SET_CHAR_HEADING(ped17, 180.0);
				SET_CHAR_HEADING(ped18, 180.0);
				SET_CHAR_HEADING(ped19, 180.0);
				SET_CHAR_HEADING(ped20, 180.0);
				SET_CHAR_HEADING(ped21, 180.0);
				SET_CHAR_HEADING(ped22, 180.0);

				// ���������
				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				UpdateWeaponOfPed(ped2, WEAPON_AK47);
				UpdateWeaponOfPed(ped3, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped4, WEAPON_AK47);
				UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped6, WEAPON_AK47);
				UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped8, WEAPON_AK47);
				UpdateWeaponOfPed(ped9, WEAPON_AK47);
				UpdateWeaponOfPed(ped10, WEAPON_AK47);
				UpdateWeaponOfPed(ped11, WEAPON_AK47);
				UpdateWeaponOfPed(ped12, WEAPON_AK47);
				UpdateWeaponOfPed(ped13, WEAPON_AK47);
				UpdateWeaponOfPed(ped14, WEAPON_AK47);
				UpdateWeaponOfPed(ped15, WEAPON_AK47);
				UpdateWeaponOfPed(ped16, WEAPON_AK47);
				UpdateWeaponOfPed(ped17, WEAPON_AK47);
				UpdateWeaponOfPed(ped18, WEAPON_AK47);
				UpdateWeaponOfPed(ped19, WEAPON_AK47);
				UpdateWeaponOfPed(ped20, WEAPON_AK47);
				UpdateWeaponOfPed(ped21, WEAPON_AK47);
				UpdateWeaponOfPed(ped22, WEAPON_AK47);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_AK47, TRUE);

				SET_CHAR_HEALTH(ped1, 200);
				SET_CHAR_HEALTH(ped2, 200);
				SET_CHAR_HEALTH(ped3, 200);
				SET_CHAR_HEALTH(ped4, 200);
				SET_CHAR_HEALTH(ped5, 200);
				SET_CHAR_HEALTH(ped6, 200);
				SET_CHAR_HEALTH(ped7, 200);
				SET_CHAR_HEALTH(ped8, 200);
				SET_CHAR_HEALTH(ped9, 200);
				SET_CHAR_HEALTH(ped10, 200);
				SET_CHAR_HEALTH(ped11, 200);
				SET_CHAR_HEALTH(ped12, 200);
				SET_CHAR_HEALTH(ped13, 200);
				SET_CHAR_HEALTH(ped14, 200);
				SET_CHAR_HEALTH(ped15, 200);
				SET_CHAR_HEALTH(ped16, 200);
				SET_CHAR_HEALTH(ped17, 200);
				SET_CHAR_HEALTH(ped18, 200);
				SET_CHAR_HEALTH(ped19, 200);
				SET_CHAR_HEALTH(ped20, 200);
				SET_CHAR_HEALTH(ped21, 200);
				SET_CHAR_HEALTH(ped22, 200);

				//������ ����� � ������
				ATTACH_PED_TO_CAR( ped9, car2, 0, -0.75, -0.934, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped10, car2, 0, -0.75, -3.441, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped11, car2, 0, 0.646, -0.934, 1.864, 0.0, 0, 1, 0 );
				ATTACH_PED_TO_CAR( ped12, car2, 0, 0.646, -3.441, 1.864, 0.0, 270, 0, 1 );

				ATTACH_PED_TO_CAR( ped13, car4, 0, -0.75, -0.934, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped14, car4, 0, -0.75, -3.441, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped15, car4, 0, 0.646, -0.934, 1.864, 0.0, 0, 1, 1 );
				ATTACH_PED_TO_CAR( ped16, car4, 0, 0.646, -3.441, 1.864, 0.0, 270, 0, 0 );

				FREEZE_CHAR_POSITION(ped9, 1);
				FREEZE_CHAR_POSITION(ped10, 1);
				FREEZE_CHAR_POSITION(ped11, 1);
				FREEZE_CHAR_POSITION(ped12, 1);
				FREEZE_CHAR_POSITION(ped13, 1);
				FREEZE_CHAR_POSITION(ped14, 1);
				FREEZE_CHAR_POSITION(ped15, 1);
				FREEZE_CHAR_POSITION(ped16, 1);


				ADD_BLIP_FOR_CAR(car3, &cortez_ico);
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""

				PRINT_STRING_IN_STRING("string", "COL4_B1", 5000, 1);//~g~Go and acquire the piece of military hardware that is being taken through town.
				SetTime(8000);

				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)

				while(true)
				{
					WAIT(0);
					// �������� ���������� ������
					if (in_car == 0)
					{
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							if (IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car5))
							{
								in_car = 1;
							}
							else
							{
								if (!IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3))
								{
									MARK_CAR_AS_NO_LONGER_NEEDED(&car5);
									GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car5);
								}
							}
						}
					}
					else if (in_car == 1) 
					{
						if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							in_car = 0;
						}
					}

					// ������ �� �����
					GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
					if (( PlayR < 5.5) && (help_1 == 0))
					{
						help_1 = 1;
						SETTIMERC(0); //���������� ������ 
						if (play == 0)
						{
							// ������ �� �����!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HD_QQQ1", "COL4_7", 0, 0);//Civilian, move away from the tank!
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERA(0); //���������� ������ 
							play = 1;
						}
					}
					else if (help_1 == 1)
					{
						if ( TIMERC() > 3000 )
						{
							help_1 = 2;
						}
					}
					else if (help_1 == 2)
					{
						if ( TIMERC() > 8000 )
						{
							help_1 = 0;
						}
					}

					// ����� �������� ����������/����
					GET_CHAR_SPEED(ped1, &speed);
					GET_CHAR_SPEED(ped2, &speed2);
					GET_CHAR_SPEED(ped3, &speed3);
					GET_CHAR_SPEED(ped4, &speed4);

					if ((speed < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_HEADING(ped1, &PedR); //�������� ���� �������� ������
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					else if ((speed2 < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_HEADING(ped2, &PedR); //�������� ���� �������� ������
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					else if ((speed3 < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_HEADING(ped3, &PedR); //�������� ���� �������� ������
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					else if ((speed4 < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_CHAR_HEADING(ped4, &PedR); //�������� ���� �������� ������
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					if (del_car == 5)
					{
						del_car = 1;
						SETTIMERB(0); //���������� ������ 
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)

						if (IS_CAR_IN_AREA_3D(car5, convoy_x+3, convoy_y+5, PedZ-2, convoy_x-3, convoy_y-5, PedZ+2, 0))
						{
							if (play == 0)
							{
								//������� ��� ����������� ������ � ������ ����!
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_HE", "COL4_3", 0, 0);//CONVOY HALT!
								START_SCRIPT_CONVERSATION(1, 1);

								SETTIMERA(0); //���������� ������
								Speech = 1;
								play = 1;
							}
							terpenie += 1;
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped5, car5, PedX-12, PedY-12, PedZ, 4, 80.0, 2, 5, 10);// ��� ���� �� ������ ����������
							while (true)
							{
								WAIT( 0 );
								if ((!IS_CAR_IN_AREA_3D(car5, convoy_x+6, convoy_y+8, PedZ-2, convoy_x-6, convoy_y-8, PedZ+2, 0)) && (passenger == 0))
								{
									TASK_ENTER_CAR_AS_PASSENGER(ped5, car1, 10000, 3);
									SETTIMERC(0); //���������� ������ 
									passenger = 1;
								}
								GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//��������� ���������� ������ � ����������
								if ((IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3)) || (terpenie > 4) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX2+45, PedY2+45, PedX2-45, PedY2-45, 0)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_DEAD(ped7)) || (IS_CHAR_DEAD(ped8)) || (IS_CHAR_DEAD(ped9)) || (IS_CHAR_DEAD(ped10)) || (IS_CHAR_DEAD(ped11)) || (IS_CHAR_DEAD(ped12)) || (IS_CHAR_DEAD(ped13)) || (IS_CHAR_DEAD(ped14)) || (IS_CHAR_DEAD(ped15)) || (IS_CHAR_DEAD(ped16)) || (IS_CHAR_DEAD(ped17)) || (IS_CHAR_DEAD(ped18)) || (IS_CHAR_DEAD(ped19)) || (IS_CHAR_DEAD(ped20)) || (IS_CHAR_DEAD(ped21)) || (IS_CHAR_DEAD(ped22)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_INJURED(ped1)) || (IS_CHAR_INJURED(ped2)) || (IS_CHAR_INJURED(ped3)) || (IS_CHAR_INJURED(ped4)) || (IS_CHAR_INJURED(ped5)) || (IS_CHAR_INJURED(ped6)) || (IS_CHAR_INJURED(ped7)) || (IS_CHAR_INJURED(ped8)) || (IS_CHAR_INJURED(ped9)) || (IS_CHAR_INJURED(ped10)) || (IS_CHAR_INJURED(ped11)) || (IS_CHAR_INJURED(ped12)) || (IS_CHAR_INJURED(ped13)) || (IS_CHAR_INJURED(ped14)) || (IS_CHAR_INJURED(ped15)) || (IS_CHAR_INJURED(ped16)) || (IS_CHAR_INJURED(ped17)) || (IS_CHAR_INJURED(ped18)) || (IS_CHAR_INJURED(ped19)) || (IS_CHAR_INJURED(ped20)) || (IS_CHAR_INJURED(ped21)) || (IS_CHAR_INJURED(ped22)))
								{
									hate = 1;
									break;
								}
								if (passenger == 1)
								{
									if (IS_CHAR_SITTING_IN_CAR(ped5, car1))
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
										}
										else if (point == 3)
										{
											// ����
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����
										}
										passenger = 0;
										break;
									}
									else if ( TIMERC() > 15000 )
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
										}
										else if (point == 3)
										{
											// ����
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����
										}
										terpenie -= 1;
										WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car1, 0);
										passenger = 0;
										break;
									}
								}
								if (play == 1)
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										if (Speech == 1)
										{
											// ������� ��� ����������� ������ � ������ ����!
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_HF", "COL4_15", 0, 0);//Get that civilian vehicle out of our way! - Sir! Moving vehicle Sir!
											START_SCRIPT_CONVERSATION(1, 1);
											SETTIMERA(0); //���������� ������ 
											Speech = 0;
										}
									}
									if ( TIMERA() > 5000 )
									{
										play = 0;
									}
								}
							}
						}
						// ---- Tommi
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), convoy_x+3, convoy_y+5, PedZ-2, convoy_x-3, convoy_y-5, PedZ+2, 0 ))
						{
							if (play == 0)
							{
								//������� ����� ������������ � ������ ����!
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_HE", "COL4_3", 0, 0);//CONVOY HALT!
								START_SCRIPT_CONVERSATION(1, 1);

								SETTIMERA(0); //���������� ������ 
								Speech = 2;
								play = 1;
							}
							TASK_LEAVE_CAR(ped5, car1);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
							SET_CHAR_RELATIONSHIP(ped5, 3, 0);
							SET_SENSE_RANGE(ped5, 15.0);
							SET_CHAR_WILL_USE_COVER(ped5, 0);
							SET_CHAR_HEALTH(ped5, 200);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
							TASK_COMBAT(ped5, GetPlayerPed());
							terpenie += 1;
							while (true)
							{
								WAIT( 0 );
								if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), convoy_x+3, convoy_y+5, PedZ-2, convoy_x-3, convoy_y-5, PedZ+2, 0 )) && (passenger == 0))
								{
									SET_SENSE_RANGE(ped5, 0.01);
									TASK_ENTER_CAR_AS_PASSENGER(ped5, car1, 10000, 3);
									SETTIMERC(0); //���������� ������ 
									passenger = 1;
								}
								GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//��������� ���������� ������ � ����������
								if ((IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3)) || (terpenie > 4) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX2+45, PedY2+45, PedX2-45, PedY2-45, 0)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_DEAD(ped7)) || (IS_CHAR_DEAD(ped8)) || (IS_CHAR_DEAD(ped9)) || (IS_CHAR_DEAD(ped10)) || (IS_CHAR_DEAD(ped11)) || (IS_CHAR_DEAD(ped12)) || (IS_CHAR_DEAD(ped13)) || (IS_CHAR_DEAD(ped14)) || (IS_CHAR_DEAD(ped15)) || (IS_CHAR_DEAD(ped16)) || (IS_CHAR_DEAD(ped17)) || (IS_CHAR_DEAD(ped18)) || (IS_CHAR_DEAD(ped19)) || (IS_CHAR_DEAD(ped20)) || (IS_CHAR_DEAD(ped21)) || (IS_CHAR_DEAD(ped22)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_INJURED(ped1)) || (IS_CHAR_INJURED(ped2)) || (IS_CHAR_INJURED(ped3)) || (IS_CHAR_INJURED(ped4)) || (IS_CHAR_INJURED(ped5)) || (IS_CHAR_INJURED(ped6)) || (IS_CHAR_INJURED(ped7)) || (IS_CHAR_INJURED(ped8)) || (IS_CHAR_INJURED(ped9)) || (IS_CHAR_INJURED(ped10)) || (IS_CHAR_INJURED(ped11)) || (IS_CHAR_INJURED(ped12)) || (IS_CHAR_INJURED(ped13)) || (IS_CHAR_INJURED(ped14)) || (IS_CHAR_INJURED(ped15)) || (IS_CHAR_INJURED(ped16)) || (IS_CHAR_INJURED(ped17)) || (IS_CHAR_INJURED(ped18)) || (IS_CHAR_INJURED(ped19)) || (IS_CHAR_INJURED(ped20)) || (IS_CHAR_INJURED(ped21)) || (IS_CHAR_INJURED(ped22)))
								{
									hate = 1;
									break;
								}
								if (passenger == 1)
								{
									if (IS_CHAR_SITTING_IN_CAR(ped5, car1))
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
										}
										else
										{
											// ����
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����
										}
										passenger = 0;
										break;
									}
									else if ( TIMERC() > 15000 )
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
										}
										else if (point == 3)
										{
											// ����
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����
										}
										terpenie -= 1;
										SET_SENSE_RANGE(ped5, 0.1);
										WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car1, 0);
										passenger = 0;
										break;
									}
								}
								if (play == 1)
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										if (Speech == 2)
										{
											// ������� ����� ������������ � ������ ����!
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_HG", "COL4_11", 0, 0);//Get that civilian out of our way soldier! - Sir, Yes Sir!
											START_SCRIPT_CONVERSATION(1, 1);
											SETTIMERA(0); //���������� ������ 
											Speech = 0;
										}
									}
									if ( TIMERA() > 5000 )
									{
										play = 0;
									}
								}
							}
						}
						else
						{
							del_car = 0;
							if (point == 1)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
							}
							else if (point == 3)
							{
								// ����
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����
							}
						}
					}
					else if ((speed > 2) && (del_car == 1))
					{
						if (play == 0)
						{
							// ������, �����, ������������!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_JA", "COL4_17", 0, 0);//Ok, PLATOON MOVE IT OUT!
							START_SCRIPT_CONVERSATION(1, 1);

							SETTIMERA(0); //���������� ������ 
							play = 1;
						}
						del_car = 0;
					}
					else if ((speed < 1) && (del_car == 1))
					{
						if ( TIMERB() > 15000 )
						{
							del_car = 0;
						}
					}
					//DRAW_CHECKPOINT( convoy_x, convoy_y, PedZ, 4.0, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.66954074, "CP_TIME_NOZERO", del_car);// �������
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", speed*10);// �������
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.66954074, "CP_TIME_NOZERO", terpenie);// �������

					//----------------------------------------------

					// ����� ����
					if (play == 1)
					{
						if ((point == 1) || (point == 3))
						{
							if ( TIMERA() > 5000 )
							{
								play = 0;
							}
						}
						else if (point == 5)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								if (Speech == 3)
								{
									//��� ������� ��������, ������!
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R4_KA", "COL4_19", 0, 0);//Go get some doughnuts, soldier! - Sir, Yes Sir!
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERA(0); //���������� ������ 
									Speech = 0;
								}
							}
						
							if ( TIMERA() > 5000 )
							{
								SETTIMERA(0); //���������� ������ 
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped7, -419.942, -101.064, 5.762, 3, -2, 2.5);// ������ ����� � �������
								play = 0;
								point = 4;
							}
						}
					}
					//----------------------------------------------

					// ����� �������� ������ ���
					if (point == 4)
					{
						if ( TIMERA() > 9000 )
						{
							SETTIMERA(0); //���������� ������ 
							TASK_ENTER_CAR_AS_PASSENGER(ped7, car3, 10000, 3);
							point = 2;
						}
					}
					else if (point == 2)
					{
						if ( TIMERA() > 11000 )
						{
							// ������, �����, ������������!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_JA", "COL4_17", 0, 0);//Ok, PLATOON MOVE IT OUT!
							START_SCRIPT_CONVERSATION(1, 1);

							SETTIMERA(0); //���������� ������ 
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped7, car3, 0);
							play = 1;
							point = 3;
						}
					}

					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -398.104, -116.811, 5.48731, &PedR);//�������� "����� �� �����������"
					if (( PedR < 2.5 ) && (point == 1))
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						play = 0;

						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 3.5, 4, 2, 2);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)

						// ��� ������� ��������, ������!
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_HE", "COL4_3", 0, 0);//CONVOY HALT!
						START_SCRIPT_CONVERSATION(1, 1);

						SETTIMERA(0); //���������� ������ 
						play = 1;
						point = 5;
						Speech = 3;
						LOCK_CAR_DOORS(car3, 1); // �������� ����������
					}
					//----------------------------------------------

					// ���� �������
					GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//��������� ���������� ������ � ����������
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+65, PedY2+65, PedZ2-5, PedX2-65, PedY2-65, PedZ2+20, 0 )) && ( help_2 == 0))
					{
						GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//��������� ���������� ������ � ����������
						GET_CHAR_HEADING(ped3, &PedR2); //�������� ���� �������� ������

						convoy_x2 = (3*COS((0-PedR2))+(3.5*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped17, convoy_x2, convoy_y2, PedZ2);// ���������� ������

						convoy_x2 = (3*COS((0-PedR2))+(-1*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (-1*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped18, convoy_x2, convoy_y2, PedZ2);// ���������� ������

						convoy_x2 = (3*COS((0-PedR2))+(-3.5*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (-3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped19, convoy_x2, convoy_y2, PedZ2);// ���������� ������

						convoy_x2 = (-3*COS((0-PedR2))+(3*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped20, convoy_x2, convoy_y2, PedZ2);// ���������� ������

						convoy_x2 = (-3*COS((0-PedR2))+(0*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (0*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped21, convoy_x2, convoy_y2, PedZ2);// ���������� ������;

						convoy_x2 = (-3*COS((0-PedR2))+(-3*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (-3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped22, convoy_x2, convoy_y2, PedZ2);// ���������� ������
						help_2 = 1;
					}
					else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+65, PedY2+65, PedZ2-5, PedX2-65, PedY2-65, PedZ2+20, 0 )) && ( help_2 == 2))
					{
						help_2 = 0;
					}
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+20, PedY2+20, PedZ2-5, PedX2-20, PedY2-20, PedZ2+10, 0 )) && ( help_2 == 1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL4_B6", 5000, 1);//~g~Find a way to steal the tank!
						help_2 = 2;
					}
					//----------------------------------------------

					// ����� ����
					if ((IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3)) || (terpenie > 4) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX2+45, PedY2+45, PedX2-45, PedY2-45, 0)))
					{
						hate = 1;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_DEAD(ped7)) || (IS_CHAR_DEAD(ped8)) || (IS_CHAR_DEAD(ped9)) || (IS_CHAR_DEAD(ped10)) || (IS_CHAR_DEAD(ped11)) || (IS_CHAR_DEAD(ped12)) || (IS_CHAR_DEAD(ped13)) || (IS_CHAR_DEAD(ped14)) || (IS_CHAR_DEAD(ped15)) || (IS_CHAR_DEAD(ped16)) || (IS_CHAR_DEAD(ped17)) || (IS_CHAR_DEAD(ped18)) || (IS_CHAR_DEAD(ped19)) || (IS_CHAR_DEAD(ped20)) || (IS_CHAR_DEAD(ped21)) || (IS_CHAR_DEAD(ped22)))
					{
						hate = 1;
					}
					else if ((IS_CHAR_INJURED(ped1)) || (IS_CHAR_INJURED(ped2)) || (IS_CHAR_INJURED(ped3)) || (IS_CHAR_INJURED(ped4)) || (IS_CHAR_INJURED(ped5)) || (IS_CHAR_INJURED(ped6)) || (IS_CHAR_INJURED(ped7)) || (IS_CHAR_INJURED(ped8)) || (IS_CHAR_INJURED(ped9)) || (IS_CHAR_INJURED(ped10)) || (IS_CHAR_INJURED(ped11)) || (IS_CHAR_INJURED(ped12)) || (IS_CHAR_INJURED(ped13)) || (IS_CHAR_INJURED(ped14)) || (IS_CHAR_INJURED(ped15)) || (IS_CHAR_INJURED(ped16)) || (IS_CHAR_INJURED(ped17)) || (IS_CHAR_INJURED(ped18)) || (IS_CHAR_INJURED(ped19)) || (IS_CHAR_INJURED(ped20)) || (IS_CHAR_INJURED(ped21)) || (IS_CHAR_INJURED(ped22)))
					{
						hate = 1;
					}
					if (hate == 1)
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						WAIT(50);

						//�� ��������� �������� �����!
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_LA", "COL4_6", 0, 0);//WE'RE TAKING ENEMY FIRE!
						START_SCRIPT_CONVERSATION(1, 1);
						Speech = 4;
						play = 1;

						SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 4);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 4);
						SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped21, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped22, 5);

						SET_CHAR_RELATIONSHIP(ped1, 5, 0);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 4, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 4, 0);
						SET_CHAR_RELATIONSHIP(ped8, 5, 0);
						SET_CHAR_RELATIONSHIP(ped9, 5, 0);
						SET_CHAR_RELATIONSHIP(ped10, 5, 0);
						SET_CHAR_RELATIONSHIP(ped11, 5, 0);
						SET_CHAR_RELATIONSHIP(ped12, 5, 0);
						SET_CHAR_RELATIONSHIP(ped13, 5, 0);
						SET_CHAR_RELATIONSHIP(ped14, 5, 0);
						SET_CHAR_RELATIONSHIP(ped15, 5, 0);
						SET_CHAR_RELATIONSHIP(ped16, 5, 0);
						SET_CHAR_RELATIONSHIP(ped17, 5, 0);
						SET_CHAR_RELATIONSHIP(ped18, 5, 0);
						SET_CHAR_RELATIONSHIP(ped19, 5, 0);
						SET_CHAR_RELATIONSHIP(ped20, 5, 0);
						SET_CHAR_RELATIONSHIP(ped21, 5, 0);
						SET_CHAR_RELATIONSHIP(ped22, 5, 0);

						SET_SENSE_RANGE(ped1, 25.0);
						SET_SENSE_RANGE(ped2, 25.0);
						SET_SENSE_RANGE(ped3, 0.01);
						SET_SENSE_RANGE(ped4, 25.0);
						SET_SENSE_RANGE(ped5, 25.0);
						SET_SENSE_RANGE(ped6, 25.0);
						SET_SENSE_RANGE(ped7, 0.01);
						SET_SENSE_RANGE(ped8, 25.0);
						SET_SENSE_RANGE(ped9, 25.0);
						SET_SENSE_RANGE(ped10, 25.0);
						SET_SENSE_RANGE(ped11, 25.0);
						SET_SENSE_RANGE(ped12, 25.0);
						SET_SENSE_RANGE(ped13, 25.0);
						SET_SENSE_RANGE(ped14, 25.0);
						SET_SENSE_RANGE(ped15, 25.0);
						SET_SENSE_RANGE(ped16, 25.0);
						SET_SENSE_RANGE(ped17, 25.0);
						SET_SENSE_RANGE(ped18, 25.0);
						SET_SENSE_RANGE(ped19, 25.0);
						SET_SENSE_RANGE(ped20, 25.0);
						SET_SENSE_RANGE(ped21, 25.0);
						SET_SENSE_RANGE(ped22, 25.0);

						SET_CHAR_WILL_USE_COVER(ped1, 1);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_COVER(ped8, 1);
						SET_CHAR_WILL_USE_COVER(ped9, 1);
						SET_CHAR_WILL_USE_COVER(ped10, 1);
						SET_CHAR_WILL_USE_COVER(ped11, 1);
						SET_CHAR_WILL_USE_COVER(ped12, 1);
						SET_CHAR_WILL_USE_COVER(ped13, 1);
						SET_CHAR_WILL_USE_COVER(ped14, 1);
						SET_CHAR_WILL_USE_COVER(ped15, 1);
						SET_CHAR_WILL_USE_COVER(ped16, 1);
						SET_CHAR_WILL_USE_COVER(ped17, 1);
						SET_CHAR_WILL_USE_COVER(ped18, 1);
						SET_CHAR_WILL_USE_COVER(ped19, 1);
						SET_CHAR_WILL_USE_COVER(ped20, 1);
						SET_CHAR_WILL_USE_COVER(ped21, 1);
						SET_CHAR_WILL_USE_COVER(ped22, 1);

						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, 1);

						// ����������
						DETACH_PED(ped9, 1);
						DETACH_PED(ped10, 1);
						DETACH_PED(ped11, 1);
						DETACH_PED(ped12, 1);
						DETACH_PED(ped13, 1);
						DETACH_PED(ped14, 1);
						DETACH_PED(ped15, 1);
						DETACH_PED(ped16, 1);
						FREEZE_CHAR_POSITION(ped9, 0);
						FREEZE_CHAR_POSITION(ped10, 0);
						FREEZE_CHAR_POSITION(ped11, 0);
						FREEZE_CHAR_POSITION(ped12, 0);
						FREEZE_CHAR_POSITION(ped13, 0);
						FREEZE_CHAR_POSITION(ped14, 0);
						FREEZE_CHAR_POSITION(ped15, 0);
						FREEZE_CHAR_POSITION(ped16, 0);

						// ���� ����������� �� ��������� ���

						TASK_COMBAT(ped1, GetPlayerPed());
						TASK_COMBAT(ped2, GetPlayerPed());
						TASK_COMBAT(ped4, GetPlayerPed());
						TASK_COMBAT(ped5, GetPlayerPed());
						TASK_COMBAT(ped6, GetPlayerPed());
						TASK_COMBAT(ped8, GetPlayerPed());
						TASK_COMBAT(ped9, GetPlayerPed());
						TASK_COMBAT(ped10, GetPlayerPed());
						TASK_COMBAT(ped11, GetPlayerPed());
						TASK_COMBAT(ped12, GetPlayerPed());
						TASK_COMBAT(ped13, GetPlayerPed());
						TASK_COMBAT(ped14, GetPlayerPed());
						TASK_COMBAT(ped15, GetPlayerPed());
						TASK_COMBAT(ped16, GetPlayerPed());
						TASK_COMBAT(ped17, GetPlayerPed());
						TASK_COMBAT(ped18, GetPlayerPed());
						TASK_COMBAT(ped19, GetPlayerPed());
						TASK_COMBAT(ped20, GetPlayerPed());
						TASK_COMBAT(ped21, GetPlayerPed());
						TASK_COMBAT(ped22, GetPlayerPed());

						if (point > 1)
						{
							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							
							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);

							SET_SENSE_RANGE(ped3, 25.0);
							SET_SENSE_RANGE(ped7, 25.0);

							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 1);
						}
						WAIT(50);
						SETTIMERA(0); //���������� ������ 
						SETTIMERB(0); //���������� ������
						SET_CAR_DENSITY_MULTIPLIER(1);// �������� ����
						hate = 2;
						break;
					}
					//----------------------------------------------


					// ���� �����
					GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//��������� ���������� ������ � ����������
					GET_CHAR_HEADING(ped3, &PedR2); //�������� ���� �������� ������

					convoy_x2 = (3*COS((0-PedR2))+(3.5*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped17, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (3*COS((0-PedR2))+(-1*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (-1*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped18, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (3*COS((0-PedR2))+(-3.5*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (-3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped19, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (-3*COS((0-PedR2))+(3*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped20, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (-3*COS((0-PedR2))+(0*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (0*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped21, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (-3*COS((0-PedR2))+(-3*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (-3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped22, convoy_x2, convoy_y2, PedZ2, 3, -2);
					//----------------------------------------------

					// ��������� ������
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -288.417, -983.924, -10.0, -484.687, 516.076, 60.0, 0 )) && ( in_zon == 0))
					{
						in_zon = 1;
						SET_CAR_DENSITY_MULTIPLIER(0);// ��������� ����
					}
					else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -288.417, -983.924, -10.0, -484.687, 516.076, 60.0, 0 )) && ( in_zon == 1))
					{
						in_zon = 0;
						SET_CAR_DENSITY_MULTIPLIER(1);// �������� ����
					}
					//----------------------------------------------

					// ������ ������
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -384.239, -935.276, 5.978, &PedR);//�������� "����� �� �����������"
					if ( PedR < 2.5 )
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL4_B2", 5000, 1);//~r~The tank arrived at its destination safely!
						skip = 1;// ���������� ��������
						break;
					}
					else if (IS_CAR_DEAD(car3))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
						skip = 1;// ���������� ��������
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
					//----------------------------------------------
				}

				if ((skip == 0) && (point == 1))
				{
					while (true)
					{
						WAIT( 0 );
						if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped3)) || (!IS_CHAR_SITTING_IN_ANY_CAR(ped7)) || (TIMERA() > 10000))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOL4_T", 5000, 1);//~g~Get in the tank.
							LOCK_CAR_DOORS(car3, 1); // �������� ����������
							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							
							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);

							SET_SENSE_RANGE(ped3, 25.0);
							SET_SENSE_RANGE(ped7, 25.0);

							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 1);
							SETTIMERB(0); //���������� ������
							SETTIMERA(0); //���������� ������
							break;
						}

						// ����� ����
						if (play == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								if (Speech == 4)
								{
									//�������������� �������!"
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R4_MA", "COL4_9", 0, 0);//DEFENSIVE POSITIONS!
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERA(0); //���������� ������
									Speech = 0;
								}
							}
							if ( TIMERA() > 5000 )
							{
								play = 0;
							}
						}

						// ������ ������
						if (IS_CAR_DEAD(car3))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}

				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );

						// ����� ����
						if (play == 1)
						{
							if ( TIMERA() > 5000 )
							{
								WAIT(10);
								play = 0;
							}
						}

						if (IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3))
						{
							if (car_blip == 0)
							{
								REMOVE_BLIP(cortez_ico);//������� ������ �� ������
								ADD_BLIP_FOR_COORD(-613.883, 55.733, 4.186, &cortez_ico);//������� ������ �� ������
								CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
								CHANGE_BLIP_COLOUR(cortez_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""
								car_blip = 1;
							}
							if (car_blip == 1)
							{
								DRAW_CHECKPOINT( -613.883, 55.733, 4.186, 4.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
							}

							if ((delta == 0) && (play == 0))
							{
								WAIT(50);
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

								//�������� ����� ������ ������� ���-���-���
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_MB", "COL4_24", 0, 0);//Security protocol Delta India Echo triggered! Vehicle self destruct initiated!
								START_SCRIPT_CONVERSATION(1, 1);

								SETTIMERA(0); //���������� ������
								SETTIMERB(0); //���������� ������
								play = 1;
								delta = 1;
							}

							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -600.939, 30.766, 4.186, -645.592, 78.711, 15.632, 0 )) && (garage == 0))
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COL4_B7", 5000, 1);//~g~Drive the tank into the garage.
								OPEN_GARAGE("tank_g");
								garage = 1;
							}
							else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -600.939, 30.766, 4.186, -645.592, 78.711, 15.632, 0 )) && (garage == 1))
							{
								CLOSE_GARAGE("tank_g");
								garage = 0;
							}
						}
						else
						{
							if (car_blip == 1)
							{
								REMOVE_BLIP(cortez_ico);//������� ������ �� ������
								ADD_BLIP_FOR_CAR(car3, &cortez_ico);
								CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
								CHANGE_BLIP_COLOUR(cortez_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(cortez_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� ������"
								
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -603.975, 49.006, 4.186, -623.065, 62.218, 10.299, 0 ))
								{
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "NECOL4_T2", 5000, 1);//~g~Get back in the tank!
								}
								car_blip = 0;
							}
						}
						
						if (IS_CAR_IN_AREA_3D(car3, -603.975, 49.006, 4.186, -620.684, 62.218, 10.299, 0))
						{
							if ( in_garage == 0 )
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COL4_B8", 5000, 1);//~g~Get out of the tank and walk out of the garage.
								in_garage = 1;
							}
							if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -603.975, 49.006, 4.186, -623.065, 62.218, 10.299, 0 ))
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
								//SetTime(1000);
								CLOSE_GARAGE("tank_g");
								SetTime(2000);
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
								skip = 2;// ���������� ��������
								break;
							}
						}
						else if ((!IS_CAR_IN_AREA_3D(car3, -603.975, 49.006, 4.186, -620.684, 62.218, 10.299, 0)) && ( in_garage == 1))
						{
							in_garage = 0;
						}
						

						// �������� �����-������
						if (delta == 1)
						{
							if ((TIMERB() > 5000) && (hud_on == 0))
							{
								SETTIMERB(0); //���������� ������
								hud_on = 1;
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COL4_B3", 5000, 1);//~g~Drop the tank off in the Colonels lockup before it self destructs.
							}
							if (hud_on == 1)
							{
								if (TIMERB() > 100)
								{
									boom += 1;
									SETTIMERB(0); //���������� ������
								}
								// ----------------- HUD -----------------
								//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", boom);// �������

								SET_TEXT_COLOUR(95, 195, 247, 255);
								SET_TEXT_SCALE(0.156, 0.267);
								SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
								DISPLAY_TEXT(0.78815097, 0.80277778, "RBM3_6"); //DETONATION:

								DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
								DRAW_SPRITE( 0, 0.9088541, 0.80925926, 0.0739583, 0.014, 0.0, 27, 89, 130, 255 );// ������ ������� ��������.

								DiazH1 = boom;
								DiazH2 = pedHUD_w/1000;
								DiazH3 = DiazH2*DiazH1;
								DiazHUD_y1 = pedHUD_w-DiazH3;
								DiazHUD_y2 = DiazHUD_y1/2;
								DiazHUD_y3 = pedHUD_x-DiazHUD_y2;
								DRAW_SPRITE( 0, DiazHUD_y3, 0.80925926, DiazH3, 0.014, 0.0, 97, 194, 247, 255 );// ������ ������� ��������.

							}
						}

						// ������ ������
						if (boom > 1000)
						{
							EXPLODE_CAR(car3, 1, 1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CAR_DEAD(car3))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}

				ABORT_SCRIPTED_CONVERSATION( 0 );

				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				SET_CAR_DENSITY_MULTIPLIER(1);// �������� ����

				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������

				// ��������� �� ������ �����
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

				// ��������� �� ������ ���������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)

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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 2000);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +2000 );//��� ������ �����
					G_CORTEZ = 6;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== All Hands On Deck! ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 7))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				SET_MAX_WANTED_LEVEL(0);
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				blip_on = 0;
				skip = 0;

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

				Car car1, car2, car3, car4, car5, car6, car7, car8, car9, car10, car11, car12, car13;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22, ped23, ped24, ped25;
				Pickup sweap_1, aid_1;
				Cam camera;

				uint PedM1 = MODEL_IG_FAUSTIN;// ������
				uint PedM2 = MODEL_IG_FRENCH_TOM;// ������
				uint PedM3 = MODEL_M_M_LAWYER_02;// ������� � �������

				uint CarM1 = MODEL_TUGA;// ���� ������
				uint CarM2 = MODEL_WASHINGTON;// ������ (Washington)
				uint CarM3 = MODEL_DINGHY;// ����� (Speedre)
				uint CarM4 = MODEL_TROPIC;// ���� (Tripic)
				uint CarM5 = MODEL_MARQUIS;// ���� (Marquis)
				uint CarM6 = MODEL_REEFER;// ����� (Reefer)
				uint CarM7 = MODEL_MAVERICK;// ������� (Maverick)
				uint CarM8 = MODEL_ANNIHILATOR;// ������� (Hunter)
				uint Cortes_hp, car_hp1, car_hp2;
				speed = 0;
				speed2 = 0;
				speed3 = 0;
				speed4 = 0;
				play = 0;

				// ������ ������
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(PedM3);// 
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM1);// 
				while (!HAS_MODEL_LOADED(CarM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM2);// 
				while (!HAS_MODEL_LOADED(CarM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM3);// 
				while (!HAS_MODEL_LOADED(CarM3));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM4);// 
				while (!HAS_MODEL_LOADED(CarM4));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM5);// 
				while (!HAS_MODEL_LOADED(CarM5));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM6);// 
				while (!HAS_MODEL_LOADED(CarM6));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM7);// 
				while (!HAS_MODEL_LOADED(CarM7));////�������� "��� ����������" ���� ��� �� �������� � ������
				REQUEST_MODEL(CarM8);// 
				while (!HAS_MODEL_LOADED(CarM8));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ���� ���
				REQUEST_CAR_RECORDING( 3010 );// ������ (Washington)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3010 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3011 );// ������ (Washington)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3011 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3012 );// ���� ������
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3012 )) WAIT(0);

				REQUEST_CAR_RECORDING( 3014 );// ������� (Maverick)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3014 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3015 );// ������� (Maverick)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3015 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3016 );// ������� (Hunter)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3016 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3017 );// ������� (Hunter)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3017 )) WAIT(0);

				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(6, 0);//������������� �����

				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "COL_5A", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("col_5a");
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
				G_CORTEZ = 99;

				CREATE_CAR(CarM1, 54.0, -789.9, -3.0, &car1, TRUE);// ���� ������
				TURN_OFF_VEHICLE_EXTRA(car1, 1, 0);
				CREATE_CAR(CarM2, 247.149, -907.476, 3.468, &car2, TRUE);// ������ (Washington)
				CHANGE_CAR_COLOUR( car2, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car2, 0, 0 );//���� ��������� ������
				CREATE_CAR(CarM2, 251.749, -906.255, 4.103, &car3, TRUE);// ������ (Washington)
				CHANGE_CAR_COLOUR( car3, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car3, 0, 0 );//���� ��������� ������
				CREATE_CAR(CarM3, 100.991, -690.089, 1.587, &car4, TRUE);// ����� (Speedre)
				SET_CAR_HEADING(car4, 90.0);
				CREATE_CAR(CarM4, 101.697, -699.992, 1.587, &car5, TRUE);// ���� (Tripic)
				SET_CAR_HEADING(car5, 90.0);
				CREATE_CAR(CarM5, 104.164, -674.854, 1.587, &car6, TRUE);// ���� (Marquis)
				SET_CAR_HEADING(car6, 90.0);
				CREATE_CAR(CarM6, 120.866, -674.887, 1.587, &car7, TRUE);// ����� (Reefer)
				SET_CAR_HEADING(car7, 90.0);
				CREATE_CAR(CarM5, 624.929, 1483.241, 1.587, &car8, TRUE);// ���� (Marquis)
				SET_CAR_HEADING(car8, 75.0);
				CREATE_CAR(CarM4, 647.332, 1474.099, 1.587, &car9, TRUE);// ���� (Tripic)
				SET_CAR_HEADING(car9, 75.0);
				CREATE_CAR(CarM7, 742.157, 1642.026, 11.823, &car10, TRUE);// ������� (Maverick)
				SET_CAR_HEADING(car10, 90.0);
				CREATE_CAR(CarM7, 742.157, 1664.559, 12.523, &car11, TRUE);// ������� (Maverick)
				SET_CAR_HEADING(car11, 90.0);
				CREATE_CAR(CarM8, 757.386, 1653.161, 12.323, &car12, TRUE);// ������� (Hunter)
				SET_CAR_HEADING(car12, 90.0);
				CREATE_CAR(CarM3, 120.173, -733.062, 1.587, &car13, TRUE);// ����� (Speedre)
				SET_CAR_HEADING(car13, 180.0);
				CHANGE_CAR_COLOUR( car13, 30, 4 );//���� ������
				SET_EXTRA_CAR_COLOURS( car13, 0, 0 );//���� ��������� ������

				// ������ �����
				CREATE_CHAR (26, PedM1, 41.17, -821.214, 2.606, &ped1, TRUE);// ������
				CREATE_CHAR (26, PedM2, 41.17, -819.721, 2.606, &ped2, TRUE);// ������
				CREATE_CHAR (26, PedM2, 41.17, -818.226, 2.606, &ped3, TRUE);// ������
				CREATE_CHAR (26, PedM2, 41.17, -816.733, 2.606, &ped4, TRUE);// ������
				CREATE_CHAR (26, PedM2, 41.17, -815.239, 2.606, &ped5, TRUE);// ������

				CREATE_CHAR (26, PedM3, 281.581, -792.161, 5.423, &ped19, TRUE);// ������� � �������
				CREATE_CHAR (26, PedM3, 283.395, -792.161, 5.423, &ped20, TRUE);// ������� � �������
				CREATE_CHAR (26, PedM3, 285.208, -792.161, 5.423, &ped21, TRUE);// ������� � �������
				CREATE_CHAR (26, PedM3, 287.021, -792.161, 5.423, &ped22, TRUE);// ������� � �������
				CREATE_CHAR (26, PedM3, 281.581, -790.448, 5.423, &ped23, TRUE);// ������� � �������
				CREATE_CHAR (26, PedM3, 283.395, -790.448, 5.423, &ped24, TRUE);// ������� � �������
				CREATE_CHAR (26, PedM3, 285.208, -790.448, 5.423, &ped25, TRUE);// ������� � �������

				SET_CHAR_HEADING(ped19, 90.0);
				SET_CHAR_HEADING(ped20, 90.0);
				SET_CHAR_HEADING(ped21, 90.0);
				SET_CHAR_HEADING(ped22, 90.0);

				// ������ ����� �� ����
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM3, &ped6);// ������� � �������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped7);// ������� � �������
				CREATE_CHAR_INSIDE_CAR(car10, 1, PedM3, &ped14);// ������� � �������
				CREATE_CHAR_INSIDE_CAR(car11, 1, PedM3, &ped15);// ������� � �������
				CREATE_CHAR_INSIDE_CAR(car12, 1, PedM3, &ped16);// ������� � �������

				// ������ ����� ����������
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 0, &ped8);// ������� � �������
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 1, &ped9);// ������� � �������
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 2, &ped10);// ������� � �������

				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 0, &ped11);// ������� � �������
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 1, &ped12);// ������� � �������
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 2, &ped13);// ������� � �������
				CREATE_CHAR_AS_PASSENGER(car10, 1, PedM3, 2, &ped17);// ������� � �������
				CREATE_CHAR_AS_PASSENGER(car11, 1, PedM3, 1, &ped18);// ������� � �������

				//������ ����� � ������
				ATTACH_PED_TO_CAR( GetPlayerPed(), car1, 0, 0.141, -16.323, 8.131, 0.0, 0, 1, 1 );
				ATTACH_PED_TO_CAR( ped1, car1, 0, -2.948, -2.538, 8.131, 0.0, 0, 1, 1 );
				ATTACH_PED_TO_CAR( ped2, car1, 0, -4.221, -5.591, 8.131, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped3, car1, 0, 4.2311, -5.591, 8.131, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped4, car1, 0, -4.231, -13.185, 8.131, 0.0, 0, 1, 0 );
				ATTACH_PED_TO_CAR( ped5, car1, 0, 4.2311, -13.185, 8.131, 0.0, 270, 0, 1 );

				FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
				FREEZE_CHAR_POSITION(ped1, 1);
				FREEZE_CHAR_POSITION(ped2, 1);
				FREEZE_CHAR_POSITION(ped3, 1);
				FREEZE_CHAR_POSITION(ped4, 1);
				FREEZE_CHAR_POSITION(ped5, 1);

				SET_CAR_DENSITY_MULTIPLIER(0);// ��������� ����

				// ����� �����
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3012, 0.0, 0.0, 0.0);// ���� ������
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3010, 0.0, 0.0, 0.0);// ������ (Washington)
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3011, 0.0, 0.0, 0.0);// ������ (Washington)
				PAUSE_PLAYBACK_RECORDED_CAR(car2);
				PAUSE_PLAYBACK_RECORDED_CAR(car3);

				// ������ ������
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 53.217, -783.811, 9.597); // ���� ������� ������
				SET_CAM_POS			( camera, 33.126, -743.569, 4.93 );//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
				SetTime(5000);
				UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
				UNPAUSE_PLAYBACK_RECORDED_CAR(car3);

				// ������ ������
				POINT_CAM_AT_COORD	( camera, 53.588, -742.778, 7.715); // ���� ������� ������
				SET_CAM_POS			( camera, 42.605, -849.751, 8.827 );//������������ ������
				SetTime(5500);

				// ������ ������
				POINT_CAM_AT_COORD	( camera, 188.281, -748.055, 2.386); // ���� ������� ������
				SET_CAM_POS			( camera, 185.821, -658.835, 6.594 );//������������ ������
				SetTime(5500);

				STOP_PLAYBACK_RECORDED_CAR(car2);
				STOP_PLAYBACK_RECORDED_CAR(car3);
				REMOVE_CAR_RECORDING( 3010 ); // ��������� ���� ����������
				REMOVE_CAR_RECORDING( 3011 ); // ��������� ���� ����������

				// ������ ������
				POINT_CAM_AT_COORD	( camera, 176.847, -678.321, 4.518); // ���� ������� ������
				SET_CAM_POS			( camera, 198.709, -688.142, 4.591 );//������������ ������

				// ���� ����� � �����
				TASK_GO_STRAIGHT_TO_COORD(ped6, 103.184, -679.364, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped7, 120.505, -679.278, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped8, 109.659, -682.302, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped9, 109.659, -681.011, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped10, 103.184, -679.364, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped11, 120.505, -679.278, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped12, 109.659, -682.302, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped13, 109.659, -681.011, 2.606, 3, -2);
				SetTime(3000);
				
				// ������ ������
				POINT_CAM_AT_COORD	( camera, 90.848, -683.712, 7.504); // ���� ������� ������
				SET_CAM_POS			( camera, 158.721, -686.547, 3.787 );//������������ ������

				// ������������� ����� ���
				SET_CHAR_COORDINATES(ped6, 159.45, -679.962, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped7, 159.45, -681.38, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped8, 159.45, -682.799, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped9, 158.632, -680.674, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped10, 158.632, -682.194, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped11, 157.634, -679.833, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped12, 157.634, -681.337, 2.171);// ���������� ������
				SET_CHAR_COORDINATES(ped13, 157.634, -682.841, 2.171);// ���������� ������
				SetTime(3000);

				// ������ ������
				POINT_CAM_AT_COORD	( camera, 116.05, -681.641, 0.167); // ���� ������� ������
				SET_CAM_POS			( camera, 67.945, -716.863, 24.279 );//������������ ������
				SetTime(3500);

				DO_SCREEN_FADE_OUT( 500 );// ��������� �����
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}

				// ����������� ����� �� ������� ���
				WARP_CHAR_INTO_CAR(ped6, car4);
				WARP_CHAR_INTO_CAR(ped7, car5);
				WARP_CHAR_INTO_CAR(ped8, car6);
				WARP_CHAR_INTO_CAR(ped9, car7);
				
				SET_CHAR_COORDINATES(ped10, 103.184, -679.364, 2.606);// ���������� ������
				SET_CHAR_COORDINATES(ped11, 120.505, -679.278, 2.606);// ���������� ������
				SET_CHAR_COORDINATES(ped12, 109.659, -682.302, 2.606);// ���������� ������
				SET_CHAR_COORDINATES(ped13, 109.659, -681.011, 2.606);// ���������� ������
				SetTime(250);

				ATTACH_PED_TO_CAR( ped10, car4, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// ����� (Speedre)
				ATTACH_PED_TO_CAR( ped11, car5, 0, -0.245, 7.989, 2.339, 3.0, 90, 1, 1 );// ���� (Tripic)
				ATTACH_PED_TO_CAR( ped12, car6, 0, -0.184, 6.023, 1.815, 3.0, 90, 1, 0 );// ���� (Marquis)
				ATTACH_PED_TO_CAR( ped13, car7, 0, 1.0, 3.0, 1.816, 0.0, 270, 0, 1 );// ����� (Reefer)

				FREEZE_CHAR_POSITION(ped10, 1);
				FREEZE_CHAR_POSITION(ped11, 1);
				FREEZE_CHAR_POSITION(ped12, 1);
				FREEZE_CHAR_POSITION(ped13, 1);

				// ������-���� ������ ���
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car4, -39.386, -484.829, 1.1, 4, 16.0, 1, 5, 10 );// ����� (Speedre)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car5, -20.679, -477.399, 1.1, 4, 16.0, 1, 5, 10 );// ���� (Tripic)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped8, car6, -32.641, -510.701, 1.1, 4, 16.0, 1, 5, 10 );// ���� (Marquis)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped9, car7, -13.131, -504.776, 1.1, 4, 16.0, 1, 5, 10 );// ����� (Reefer)

				STOP_PLAYBACK_RECORDED_CAR(car1);
				REMOVE_CAR_RECORDING( 3012 ); // ���� ������

				SET_CAR_COORDINATES(car1, -26.928, -491.821, -3.5);
				SET_CAR_HEADING(car1, 15.0);
				FREEZE_CAR_POSITION(car1, 1);

				//������� ������
				SetTime(250);
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������

				//��������� ����� �� ������
				DETACH_PED(GetPlayerPed(), 1);
				DETACH_PED(ped1, 1);
				DETACH_PED(ped2, 1);
				DETACH_PED(ped3, 1);
				DETACH_PED(ped4, 1);
				DETACH_PED(ped5, 1);

				FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
				FREEZE_CHAR_POSITION(ped1, 1);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, TRUE);
				FREEZE_CHAR_POSITION(ped2, 0);
				FREEZE_CHAR_POSITION(ped3, 0);
				FREEZE_CHAR_POSITION(ped4, 0);
				FREEZE_CHAR_POSITION(ped5, 0);
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				// ��������� �����
				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped2, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped3, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped4, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped5, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped6, WEAPON_MP5);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MP5, TRUE);
				UpdateWeaponOfPed(ped7, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_M4, TRUE);
				UpdateWeaponOfPed(ped8, WEAPON_M4);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped9, WEAPON_MP5);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);
				UpdateWeaponOfPed(ped10, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped11, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped12, WEAPON_MP5);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_MP5, TRUE);
				UpdateWeaponOfPed(ped13, WEAPON_M4);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_M4, TRUE);

				// ���������� � ������
				SET_CHAR_HEALTH(ped1, 250);
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
				SET_CHAR_RELATIONSHIP(ped4, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
				SET_CHAR_RELATIONSHIP(ped5, 5, 24);
				SET_CHAR_SHOOT_RATE(ped1, 15);
				SET_CHAR_SHOOT_RATE(ped2, 15);
				SET_CHAR_SHOOT_RATE(ped3, 15);
				SET_CHAR_SHOOT_RATE(ped4, 15);
				SET_CHAR_SHOOT_RATE(ped5, 15);

				// ����� ���
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);

				SET_CHAR_RELATIONSHIP(ped10, 5, 0);
				SET_CHAR_RELATIONSHIP(ped11, 5, 0);
				SET_CHAR_RELATIONSHIP(ped12, 5, 0);
				SET_CHAR_RELATIONSHIP(ped13, 5, 0);

				SET_SENSE_RANGE(ped10, 30.0);
				SET_SENSE_RANGE(ped11, 30.0);
				SET_SENSE_RANGE(ped12, 30.0);
				SET_SENSE_RANGE(ped13, 30.0);

				SET_CHAR_WILL_USE_COVER(ped10, 1);
				SET_CHAR_WILL_USE_COVER(ped11, 1);
				SET_CHAR_WILL_USE_COVER(ped12, 1);
				SET_CHAR_WILL_USE_COVER(ped13, 1);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);

				SET_CHAR_SHOOT_RATE(ped10, 35);
				SET_CHAR_SHOOT_RATE(ped11, 35);
				SET_CHAR_SHOOT_RATE(ped12, 35);
				SET_CHAR_SHOOT_RATE(ped13, 35);

				PRINT_STRING_IN_STRING("string", "COL5_B1", 5000, 1);//~g~Defend the Colonel and his yacht at all costs.

				SETTIMERB( 0 );
				SETTIMERC( 0 );
				SET_CHAR_HEALTH(ped1, 500);
				CREATE_PICKUP_ROTATE(w_ak47, 3, 90, -27.256, -496.16, 9.268, -75.0, -80.0, 0.0, &sweap_1);// ��� ��������
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -27.148, -495.558, 9.268, 0.0, 0.0, 105.0, &aid_1);//������

				while(true)
				{
					WAIT(0);
					
					if (TIMERC() > 65000)
					{
						FIX_CAR(car1);//����� ������
						REMOVE_PICKUP(sweap_1);
						REMOVE_PICKUP(aid_1);
						CREATE_PICKUP_ROTATE(w_ak47, 3, 90, -27.256, -496.16, 9.268, -75.0, -80.0, 0.0, &sweap_1);// ��� ��������
						CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -27.148, -495.558, 9.268, 0.0, 0.0, 105.0, &aid_1);//������
						SETTIMERC( 0 );
					}
					if ((IS_CHAR_IN_AREA_3D( ped6, -35.386, -480.829, -1.1, -44.386, -488.829, 5.1, 0 )) && (speed == 0))// ���� ����� � ����
					{
						// ����� (Speedre)
						if (!IS_CHAR_DEAD(ped6))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped6, -34.576, -484.78, 3.604);// ���������� ������
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_SENSE_RANGE(ped6, 30.0);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
							SET_CHAR_SHOOT_RATE(ped6, 45);
						}
						if (!IS_CHAR_DEAD(ped10))
						{
							DETACH_PED(ped10, 1);
							FREEZE_CHAR_POSITION(ped10, 0);
							SET_CHAR_COORDINATES(ped10, -34.277, -485.926, 3.604);// ���������� ������
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( ped7, -16.679, -473.399, -1.1, -24.679, -481.399, 5.1, 0 )) && (speed2 == 0))// ���� ����� � ����
					{
						// ���� (Tripic)
						if (!IS_CHAR_DEAD(ped7))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped7, -25.713, -476.612, 3.604);// ���������� ������
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_SENSE_RANGE(ped7, 30.0);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
							SET_CHAR_SHOOT_RATE(ped7, 45);
						}
						if (!IS_CHAR_DEAD(ped11))
						{
							DETACH_PED(ped11, 1);
							FREEZE_CHAR_POSITION(ped11, 0);
							SET_CHAR_COORDINATES(ped11, -25.414, -477.758, 3.604);// ���������� ������
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed2 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( ped8, -28.641, -506.701, -1.1, -36.641, -514.701, 5.1, 0 )) && (speed3 == 0))// ���� ����� � ����
					{
						// ���� (Marquis)
						if (!IS_CHAR_DEAD(ped8))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped8, -29.969, -499.865, 3.604);// ���������� ������
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_SENSE_RANGE(ped8, 30.0);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
							SET_CHAR_SHOOT_RATE(ped8, 45);
						}
						if (!IS_CHAR_DEAD(ped12))
						{
							DETACH_PED(ped12, 1);
							FREEZE_CHAR_POSITION(ped12, 0);
							SET_CHAR_COORDINATES(ped12, -30.267, -498.719, 3.604);// ���������� ������
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed3 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( ped9, -9.131, -500.776, -1.1, -17.131, -508.776, 5.1, 0 )) && (speed4 == 0))// ���� ����� � ����
					{
						// ����� (Reefer)
						if (!IS_CHAR_DEAD(ped9))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped9, -19.498, -499.133, 3.604);// ���������� ������
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);
							SET_SENSE_RANGE(ped9, 30.0);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
							SET_CHAR_SHOOT_RATE(ped9, 45);
						}
						if (!IS_CHAR_DEAD(ped13))
						{
							DETACH_PED(ped13, 1);
							FREEZE_CHAR_POSITION(ped13, 0);
							SET_CHAR_COORDINATES(ped13, -19.797, -497.987, 3.604);// ���������� ������
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed4 = 1;
					}
			
					if (((IS_CHAR_DEAD(ped6)) || (IS_CHAR_INJURED(ped6))) && ((IS_CHAR_DEAD(ped7)) || (IS_CHAR_INJURED(ped7))) && ((IS_CHAR_DEAD(ped8)) || (IS_CHAR_INJURED(ped8))) && ((IS_CHAR_DEAD(ped9)) || (IS_CHAR_INJURED(ped9))) && ((IS_CHAR_DEAD(ped10)) || (IS_CHAR_INJURED(ped10))) && ((IS_CHAR_DEAD(ped11)) || (IS_CHAR_INJURED(ped11))) && ((IS_CHAR_DEAD(ped12)) || (IS_CHAR_INJURED(ped12))) && ((IS_CHAR_DEAD(ped13)) || (IS_CHAR_INJURED(ped13))))
					{
						break;
					}

					if (TIMERB() > 120000)
					{
						EXPLODE_CHAR_HEAD(ped6);
						EXPLODE_CHAR_HEAD(ped7);
						EXPLODE_CHAR_HEAD(ped8);
						EXPLODE_CHAR_HEAD(ped9);
						EXPLODE_CHAR_HEAD(ped10);
						EXPLODE_CHAR_HEAD(ped11);
						EXPLODE_CHAR_HEAD(ped12);
						EXPLODE_CHAR_HEAD(ped13);
					}

					GET_CHAR_HEALTH(ped1, &Cortes_hp);
					if (IS_CHAR_DEAD(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL5_B3", 5000, 1);//~r~The Colonel is dead!
						skip = 1;// ���������� ��������
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
					else if ((Cortes_hp < 50) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 3.072, -536.821, -5.0, -56.928, -446.821, 25.0, 0 )))// ���� ����� � ����
					{
						EXPLODE_CHAR_HEAD(ped1);
					}
				}

				// ������ ����� ������ 
				if (skip == 0)
				{
					// ���������� ������
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
					REMOVE_PICKUP(sweap_1);
					REMOVE_PICKUP(aid_1);
					FIX_CAR(car1);//����� ������

					// ��������� �� ������ �����
					DELETE_CHAR(&ped2);//������� ������ ����
					DELETE_CHAR(&ped3);//������� ������ ����
					DELETE_CHAR(&ped4);//������� ������ ����
					DELETE_CHAR(&ped5);//������� ������ ����
					DELETE_CHAR(&ped6);//������� ������ ����
					DELETE_CHAR(&ped7);//������� ������ ����
					DELETE_CHAR(&ped8);//������� ������ ����
					DELETE_CHAR(&ped9);//������� ������ ����
					DELETE_CHAR(&ped10);//������� ������ ����
					DELETE_CHAR(&ped11);//������� ������ ����
					DELETE_CHAR(&ped12);//������� ������ ����
					DELETE_CHAR(&ped13);//������� ������ ����
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped12);//��������� ������ ����(� ����������� ��� ��������
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped13);//��������� ������ ����(� ����������� ��� ��������

					// ��������� �� ������ ���������
					DELETE_CAR(&car2);//������� ������ ����
					DELETE_CAR(&car3);//������� ������ ����
					DELETE_CAR(&car4);//������� ������ ����
					DELETE_CAR(&car5);//������� ������ ����
					DELETE_CAR(&car6);//������� ������ ����
					DELETE_CAR(&car7);//������� ������ ����
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//��������� ������ ������(� ����������� ������ ��������)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//��������� ������ ������(� ����������� ������ ��������)

					// ������ ����� �����
					CREATE_CHAR (26, PedM2, 41.17, -819.721, 2.606, &ped2, TRUE);// ������
					CREATE_CHAR (26, PedM2, 41.17, -818.226, 2.606, &ped3, TRUE);// ������
					CREATE_CHAR (26, PedM2, 41.17, -816.733, 2.606, &ped4, TRUE);// ������
					CREATE_CHAR (26, PedM2, 41.17, -815.239, 2.606, &ped5, TRUE);// ������

					//������ ����� � ������
					ATTACH_PED_TO_CAR( GetPlayerPed(), car1, 0, 0.141, -16.323, 8.131, 0.0, 0, 1, 1 );
					ATTACH_PED_TO_CAR( ped1, car1, 0, -2.948, -2.538, 8.131, 0.0, 0, 1, 1 );
					ATTACH_PED_TO_CAR( ped2, car1, 0, -4.221, -5.591, 8.131, 3.0, 90, 1, 1 );
					ATTACH_PED_TO_CAR( ped3, car1, 0, 4.2311, -5.591, 8.131, 3.0, 90, 1, 1 );
					ATTACH_PED_TO_CAR( ped4, car1, 0, -4.231, -13.185, 8.131, 0.0, 0, 1, 0 );
					ATTACH_PED_TO_CAR( ped5, car1, 0, 4.2311, -13.185, 8.131, 0.0, 270, 0, 1 );

					FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
					FREEZE_CHAR_POSITION(ped1, 1);
					FREEZE_CHAR_POSITION(ped2, 1);
					FREEZE_CHAR_POSITION(ped3, 1);
					FREEZE_CHAR_POSITION(ped4, 1);
					FREEZE_CHAR_POSITION(ped5, 1);

					// ���������� � ������
					SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
					SET_CHAR_RELATIONSHIP(ped2, 5, 24);
					SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
					SET_CHAR_RELATIONSHIP(ped3, 5, 24);
					SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
					SET_CHAR_RELATIONSHIP(ped4, 5, 24);
					SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
					SET_CHAR_RELATIONSHIP(ped5, 5, 24);
					SET_CHAR_SHOOT_RATE(ped2, 15);
					SET_CHAR_SHOOT_RATE(ped3, 15);
					SET_CHAR_SHOOT_RATE(ped4, 15);
					SET_CHAR_SHOOT_RATE(ped5, 15);

					// ��������� ���� ���������
					REQUEST_CAR_RECORDING( 3013 );// ���� ������
					while (!HAS_CAR_RECORDING_BEEN_LOADED( 3013 )) WAIT(0);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3013, 0.0, 0.0, 0.0);// ���� ������

					// ������ ����� ��������� ���
					CREATE_CAR(CarM6, 606.748, 1489.45, 1.587, &car2, TRUE);// ����� (Reefer)
					SET_CAR_HEADING(car2, -105.0);
					CREATE_CAR(CarM6, 663.787, 1467.786, 1.587, &car3, TRUE);// ����� (Reefer)
					SET_CAR_HEADING(car3, 90.0);
					CREATE_CAR(CarM3, 591.783, 1491.737, 0.3, &car4, TRUE);// ����� (Speedre)
					SET_CAR_HEADING(car4, -140.0);
					CREATE_CAR(CarM3, 681.423, 1463.657, 0.3, &car5, TRUE);// ����� (Speedre)
					SET_CAR_HEADING(car5, 120.0);
					CREATE_CAR(CarM3, 486.127, 1336.15, 0.3, &car6, TRUE);// ����� (Speedre)
					SET_CAR_HEADING(car6, -55.0);
					CREATE_CAR(CarM3, 575.811, 1287.265, 0.3, &car7, TRUE);// ����� (Speedre)
					SET_CAR_HEADING(car7, -20.0);

					// ������ ����� �� �������
					CREATE_CHAR_INSIDE_CAR(car4, 1, PedM3, &ped6);// ������� � �������
					CREATE_CHAR_INSIDE_CAR(car5, 1, PedM3, &ped7);// ������� � �������
					CREATE_CHAR_INSIDE_CAR(car6, 1, PedM3, &ped8);// ������� � �������
					CREATE_CHAR_INSIDE_CAR(car7, 1, PedM3, &ped9);// ������� � �������

					// ������ ����� �����
					CREATE_CHAR (26, PedM3, 41.17, -819.721, 2.606, &ped10, TRUE);// ������� � �������
					CREATE_CHAR (26, PedM3, 41.17, -818.226, 2.606, &ped11, TRUE);// ������� � �������
					CREATE_CHAR (26, PedM3, 41.17, -816.733, 2.606, &ped12, TRUE);// ������� � �������
					CREATE_CHAR (26, PedM3, 41.17, -815.239, 2.606, &ped13, TRUE);// ������� � �������

					ATTACH_PED_TO_CAR( ped10, car4, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// ����� (Speedre)
					ATTACH_PED_TO_CAR( ped11, car5, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// ����� (Speedre)
					ATTACH_PED_TO_CAR( ped12, car6, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// ����� (Speedre)
					ATTACH_PED_TO_CAR( ped13, car7, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// ����� (Speedre)

					ATTACH_PED_TO_CAR( ped19, car8, 0, -0.184, 6.023, 1.815, 90.0, 90, 1, 1 );// ���� (Marquis)
					ATTACH_PED_TO_CAR( ped20, car8, 0, -1.719, -3.01, 1.613, 90.0, 90, 1, 1 );// ���� (Marquis)
					ATTACH_PED_TO_CAR( ped21, car9, 0, -1.879, 5.899, 2.097, 90.0, 90, 1, 1 );// ���� (Tripic)
					ATTACH_PED_TO_CAR( ped22, car9, 0, -2.41, -1.704, 1.961, 90.0, 90, 1, 1 );// ���� (Tripic)
					ATTACH_PED_TO_CAR( ped23, car3, 0, -1.221, 3.243, 1.816, 90.0, 90, 1, 1 );// ����� (Reefer)
					ATTACH_PED_TO_CAR( ped24, car8, 0, -1.719, 1.059, 1.613, 90.0, 90, 1, 1 );// ���� (Marquis)
					ATTACH_PED_TO_CAR( ped25, car12, 0, 0.015, 2.933, -1.039, 0.0, 0, 1, 1 );// ������� (Hunter)

					FREEZE_CHAR_POSITION(ped10, 1);
					FREEZE_CHAR_POSITION(ped11, 1);
					FREEZE_CHAR_POSITION(ped12, 1);
					FREEZE_CHAR_POSITION(ped13, 1);

					DETACH_PED(ped19, 1);
					DETACH_PED(ped20, 1);
					DETACH_PED(ped21, 1);
					DETACH_PED(ped22, 1);
					DETACH_PED(ped23, 1);
					DETACH_PED(ped24, 1);

					FREEZE_CHAR_POSITION(ped25, 1);
					SET_CHAR_COLLISION(ped25, 0);
					SET_CHAR_INVINCIBLE(ped25, 1);
					SET_CHAR_VISIBLE(ped25, 0);

					// ������ ������
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 605.018, 1379.022, 9.764); // ���� ������� ������
					SET_CAM_POS			( camera, 616.156, 1448.337, 5.113 );//������������ ������
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
					SetTime(4000);

					// ������ ������
					POINT_CAM_AT_COORD	( camera, 631.069, 1443.263, 6.032); // ���� ������� ������
					SET_CAM_POS			( camera, 581.424, 1377.638, 15.011 );//������������ ������
					SetTime(3000);

					DO_SCREEN_FADE_OUT( 500 );// ��������� �����
					while(true)
					{
						WAIT(0);
						if (IS_SCREEN_FADED_OUT())
						{
							break;
						}
					}
					
					// ��������� �������
					STOP_PLAYBACK_RECORDED_CAR(car1);
					REMOVE_CAR_RECORDING( 3013 ); // ��������� ���� ����������
					SET_CAR_COORDINATES(car1, 617.177, 1418.828, -3.5);
					SET_CAR_HEADING(car1, -20.0);
					FREEZE_CAR_POSITION(car1, 1);

					//������� ������
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					DESTROY_CAM( camera );
					SET_WIDESCREEN_BORDERS( 0 );
					
					//��������� ����� �� ������
					SetTime(250);
					DETACH_PED(GetPlayerPed(), 1);
					DETACH_PED(ped1, 1);
					DETACH_PED(ped2, 1);
					DETACH_PED(ped3, 1);
					DETACH_PED(ped4, 1);
					DETACH_PED(ped5, 1);

					FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
					FREEZE_CHAR_POSITION(ped1, 1);
					SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, TRUE);
					FREEZE_CHAR_POSITION(ped2, 0);
					FREEZE_CHAR_POSITION(ped3, 0);
					FREEZE_CHAR_POSITION(ped4, 0);
					FREEZE_CHAR_POSITION(ped5, 0);

					// ��������� �����
					UpdateWeaponOfPed(ped2, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped3, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped4, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped5, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped6, WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MP5, TRUE);
					UpdateWeaponOfPed(ped7, WEAPON_MICRO_UZI);
					SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MICRO_UZI, TRUE);
					UpdateWeaponOfPed(ped8, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped9, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped10, WEAPON_MICRO_UZI);
					SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_MICRO_UZI, TRUE);
					UpdateWeaponOfPed(ped11, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped12, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_MICRO_UZI, TRUE);
					UpdateWeaponOfPed(ped13, WEAPON_MICRO_UZI);
					SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_MICRO_UZI, TRUE);
					UpdateWeaponOfPed(ped17, WEAPON_M4);
					SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_M4, TRUE);
					UpdateWeaponOfPed(ped18, WEAPON_M4);
					SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_M4, TRUE);
					UpdateWeaponOfPed(ped19, WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_MP5, TRUE);
					UpdateWeaponOfPed(ped20, WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_MP5, TRUE);
					UpdateWeaponOfPed(ped21, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped22, WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_MP5, TRUE);
					UpdateWeaponOfPed(ped23, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped23, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped24, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped24, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped25, WEAPON_M4);
					SET_CURRENT_CHAR_WEAPON(ped25, WEAPON_M4, TRUE);

					CREATE_PICKUP_ROTATE(w_ak47, 3, 90, 614.419, 1415.461, 9.268, -75.0, -80.0, -35.0, &sweap_1);// ��� ��������
					CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 614.852, 1415.893, 9.268, 0.0, 0.0, 70.0, &aid_1);//������
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
					DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������

					// ����� ���
					SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped21, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped22, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped23, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped24, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped25, 5);

					SET_CHAR_RELATIONSHIP(ped10, 5, 0);
					SET_CHAR_RELATIONSHIP(ped11, 5, 0);
					SET_CHAR_RELATIONSHIP(ped12, 5, 0);
					SET_CHAR_RELATIONSHIP(ped13, 5, 0);
					SET_CHAR_RELATIONSHIP(ped14, 5, 0);
					SET_CHAR_RELATIONSHIP(ped15, 5, 0);
					SET_CHAR_RELATIONSHIP(ped17, 5, 0);
					SET_CHAR_RELATIONSHIP(ped18, 5, 0);
					SET_CHAR_RELATIONSHIP(ped19, 5, 0);
					SET_CHAR_RELATIONSHIP(ped20, 5, 0);
					SET_CHAR_RELATIONSHIP(ped21, 5, 0);
					SET_CHAR_RELATIONSHIP(ped22, 5, 0);
					SET_CHAR_RELATIONSHIP(ped23, 5, 0);
					SET_CHAR_RELATIONSHIP(ped24, 5, 0);
					SET_CHAR_RELATIONSHIP(ped25, 5, 0);

					SET_SENSE_RANGE(ped10, 30.0);
					SET_SENSE_RANGE(ped11, 30.0);
					SET_SENSE_RANGE(ped12, 30.0);
					SET_SENSE_RANGE(ped13, 30.0);
					SET_SENSE_RANGE(ped14, 30.0);
					SET_SENSE_RANGE(ped15, 30.0);
					SET_SENSE_RANGE(ped17, 30.0);
					SET_SENSE_RANGE(ped18, 30.0);
					SET_SENSE_RANGE(ped19, 90.0);
					SET_SENSE_RANGE(ped20, 90.0);
					SET_SENSE_RANGE(ped21, 90.0);
					SET_SENSE_RANGE(ped22, 90.0);
					SET_SENSE_RANGE(ped23, 90.0);
					SET_SENSE_RANGE(ped24, 90.0);
					SET_SENSE_RANGE(ped25, 95.0);

					SET_CHAR_WILL_USE_COVER(ped10, 1);
					SET_CHAR_WILL_USE_COVER(ped11, 1);
					SET_CHAR_WILL_USE_COVER(ped12, 1);
					SET_CHAR_WILL_USE_COVER(ped13, 1);
					SET_CHAR_WILL_USE_COVER(ped14, 1);
					SET_CHAR_WILL_USE_COVER(ped15, 1);
					SET_CHAR_WILL_USE_COVER(ped17, 1);
					SET_CHAR_WILL_USE_COVER(ped18, 1);
					SET_CHAR_WILL_USE_COVER(ped19, 1);
					SET_CHAR_WILL_USE_COVER(ped20, 1);
					SET_CHAR_WILL_USE_COVER(ped21, 1);
					SET_CHAR_WILL_USE_COVER(ped22, 1);
					SET_CHAR_WILL_USE_COVER(ped23, 1);
					SET_CHAR_WILL_USE_COVER(ped24, 1);

					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped23, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped24, FALSE);

					SET_CHAR_SHOOT_RATE(ped10, 35);
					SET_CHAR_SHOOT_RATE(ped11, 35);
					SET_CHAR_SHOOT_RATE(ped12, 35);
					SET_CHAR_SHOOT_RATE(ped13, 35);
					SET_CHAR_SHOOT_RATE(ped17, 35);
					SET_CHAR_SHOOT_RATE(ped18, 35);
					SET_CHAR_SHOOT_RATE(ped19, 35);
					SET_CHAR_SHOOT_RATE(ped20, 35);
					SET_CHAR_SHOOT_RATE(ped21, 35);
					SET_CHAR_SHOOT_RATE(ped22, 35);
					SET_CHAR_SHOOT_RATE(ped23, 35);
					SET_CHAR_SHOOT_RATE(ped24, 35);

					SET_CHAR_HEALTH(ped1, 1000);
					SET_CHAR_HEALTH(ped14, 1000);
					SET_CHAR_HEALTH(ped15, 1000);
					SET_CHAR_HEALTH(ped16, 1500);
					SET_CHAR_HEALTH(ped17, 1500);
					SET_CHAR_HEALTH(ped18, 1500);

					SETTIMERB( 0 );
					SETTIMERC( 0 );
					gogogo = 0;
					speed = 0;
					speed2 = 0;
					speed3 = 0;
					speed4 = 0;
					in_zon = 0;
					in_car = 0;
					LanceH1 = 0;
					LanceH2 = 0;
					LanceH3 = 0;
					play = 0;	

					while(true)
					{
						WAIT(5);
						if (TIMERC() > 65000)
						{
							FIX_CAR(car1);//����� ������
							REMOVE_PICKUP(sweap_1);
							REMOVE_PICKUP(aid_1);
							CREATE_PICKUP_ROTATE(w_ak47, 3, 60, 614.419, 1415.461, 9.268, -75.0, -80.0, -35.0, &sweap_1);// ��� ��������
							CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 614.852, 1415.893, 9.268, 0.0, 0.0, 70.0, &aid_1);//������
							SETTIMERC( 0 );
						}

						if ((TIMERB() > 2000) && (gogogo == 0))
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_PA", "COL5_3", 0, 0);//The bridge up ahead!
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERA( 1500 );
							play = 1;

							// ������-���� ������ ���
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car4, 610.982, 1431.7, 1.1, 4, 16.0, 1, 5, 10 );// ����� (Speedre)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car5, 630.567, 1427.057, 1.1, 4, 16.0, 1, 5, 10 );// ����� (Speedre)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped8, car6, 601.667, 1406.639, 1.1, 4, 16.0, 1, 5, 10 );// ����� (Speedre)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped9, car7, 621.048, 1400.301, 1.1, 4, 16.0, 1, 5, 10 );// ����� (Speedre)
							gogogo = 1;
							SETTIMERB( 0 );
						}

						// �������� ���
						if ((TIMERB() > 35000) && (gogogo == 1))
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_TA", "COL5_17", 0, 0);//Oh my god they've got a helicopter!
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERA( 0 );
							play = 1;

							// �������� ���� �������� 1
							ADD_BLIP_FOR_CAR(car10, &vert_ico);
							CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(vert_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(vert_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""
						
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car10, 3014, 0.0, 0.0, 0.0);// ������� 1
							WAIT(500);
							in_zon = 0;
							gogogo = 2;
							in_car = 1;
							SETTIMERB( 0 );
						}
						if ((TIMERB() > 5000) && (gogogo == 2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B5", 5000, 1);//~g~Shoot down the helicopters, do not endanger the yacht.
							gogogo = 3;
						}

						if (in_car == 1)
						{
							if ((IS_CHAR_IN_AREA_3D( ped14,  769.5, 1509.5, 1.5,  724.5, 1554.5, 21.5, 0 )) && (in_zon == 1))// ���� ����� � ����
							{
								// �������� ���� ��������
								STOP_PLAYBACK_RECORDED_CAR(car10);
								REMOVE_CAR_RECORDING( 3014 ); // ��������� ���� ����������
								REQUEST_CAR_RECORDING( 3014 );// ������� (Maverick)
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3014 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car10, 3014, 0.0, 0.0, 0.0);// ������� 1

								// ��������� ���������
								//DELETE_CAR(&ped17);//������� ������ ����
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped17);//��������� ������ ����(� ����������� ��� ��������
								CREATE_CHAR_AS_PASSENGER(car10, 1, PedM3, 2, &ped17);// ������� � ������� ������� 1
								UpdateWeaponOfPed(ped17, WEAPON_M4);
								SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_M4, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
								SET_CHAR_RELATIONSHIP(ped17, 5, 0);
								SET_SENSE_RANGE(ped17, 30.0);
								SET_CHAR_WILL_USE_COVER(ped17, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
								SET_CHAR_SHOOT_RATE(ped17, 35);
								SET_CHAR_HEALTH(ped17, 1500);
								in_zon = 0;
							}
							else if ((!IS_CHAR_IN_AREA_3D( ped14,  769.5, 1509.5, 1.5,  724.5, 1554.5, 21.5, 0 )) && (in_zon == 0))// ���� ����� � ����
							{
								in_zon = 1;
							}
						}
						else if (in_car == 2)
						{
							if ((IS_CHAR_IN_AREA_3D( ped15,  872.5, 1409.5, 1.2,  827.5, 1454.5, 21.2, 0 )) && (in_zon == 1))// ���� ����� � ����
							{
								// �������� ���� ��������
								STOP_PLAYBACK_RECORDED_CAR(car11);
								REMOVE_CAR_RECORDING( 3015 ); // ��������� ���� ����������
								REQUEST_CAR_RECORDING( 3015 );// ������� (Maverick)
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3015 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car11, 3015, 0.0, 0.0, 0.0);// ������� 2

								// ��������� ���������
								//DELETE_CAR(&ped18);//������� ������ ����
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped18);//��������� ������ ����(� ����������� ��� ��������
								CREATE_CHAR_AS_PASSENGER(car11, 1, PedM3, 1, &ped18);// ������� � ������� ������� 2
								UpdateWeaponOfPed(ped18, WEAPON_M4);
								SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_M4, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
								SET_CHAR_RELATIONSHIP(ped18, 5, 0);
								SET_SENSE_RANGE(ped18, 30.0);
								SET_CHAR_WILL_USE_COVER(ped18, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
								SET_CHAR_SHOOT_RATE(ped18, 35);
								SET_CHAR_HEALTH(ped18, 1500);
								in_zon = 0;
							}
							else if ((!IS_CHAR_IN_AREA_3D( ped15,  872.5, 1409.5, 1.2,  827.5, 1454.5, 21.2, 0 )) && (in_zon == 0))// ���� ����� � ����
							{
								in_zon = 1;
							}
						}
						else if (in_car == 3)
						{
							if ((IS_CHAR_IN_AREA_3D( ped16,  382.5, 1537.5, 2.0, 337.5, 1582.5, 22.0, 0 )) && (in_zon == 1))// ���� ����� � ����
							{
								// �������� ���� ��������
								STOP_PLAYBACK_RECORDED_CAR(car12);
								REMOVE_CAR_RECORDING( 3016 ); // ��������� ���� ����������
								REQUEST_CAR_RECORDING( 3016 );// ������� (Maverick)
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3016 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car12, 3016, 0.0, 0.0, 0.0);// ������� 3
								in_zon = 0;

								if (play == 0)
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_SA", "COL5_20", 0, 0);//He's coming again! Blow that chopper!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									SETTIMERA( 0 );
									play = 1;
								}	
							}
							else if ((!IS_CHAR_IN_AREA_3D( ped16,  382.5, 1537.5, 2.0, 337.5, 1582.5, 22.0, 0 )) && (in_zon == 0))// ���� ����� � ����
							{
								in_zon = 1;
							}
						}

						if ( ((IS_CHAR_DEAD(ped14)) && (in_car == 1)) || ((IS_CAR_DEAD(car10)) && (in_car == 1)))
						{
							// �������� ���� �������� 2
							REMOVE_BLIP(vert_ico);//������� ������ �� ������
							ADD_BLIP_FOR_CAR(car11, &vert_ico);
							CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(vert_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(vert_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""

							STOP_PLAYBACK_RECORDED_CAR(car10);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car11, 3015, 0.0, 0.0, 0.0);// ������� 2
							WAIT(500);
							in_zon = 0;
							in_car = 2;
						}
						if ( ((IS_CHAR_DEAD(ped15)) && (in_car == 2)) || ((IS_CAR_DEAD(car11)) && (in_car == 2)))
						{
							// �������� ���� �������� 3
							REMOVE_BLIP(vert_ico);//������� ������ �� ������
							ADD_BLIP_FOR_CAR(car12, &vert_ico);
							CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(vert_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_SCALE(vert_ico, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""
							STOP_PLAYBACK_RECORDED_CAR(car11);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car12, 3017, 0.0, 0.0, 0.0);// ������� 3

							// ������ �� �������
							ABORT_SCRIPTED_CONVERSATION( 0 );
							DO_SCREEN_FADE_OUT( 500 );// ��������� �����
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

							// ������ ������
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 456.011, 1262.081, 18.311); // ���� ������� ������
							SET_CAM_POS			( camera, 619.327, 1413.817, 14.956 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������
							SetTime(4500);

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
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B4", 5000, 1);//~g~Shoot the attacking helicopter out of the sky.
							WAIT(500);
							in_zon = 0;
							in_car = 3;

						}
						if ((IS_CAR_DEAD(car12)) && (in_car == 3))
						{
							REMOVE_BLIP(vert_ico);//������� ������ �� ������
							STOP_PLAYBACK_RECORDED_CAR(car12);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B2", 5000, 1);//~g~Get up front and clear the route for the Colonel's yacht.
							in_car = 4;
							WAIT( 25 );
						}

						// �������
						if ((IS_CHAR_IN_AREA_3D( ped6,  614.982, 1435.7, -1.1,  606.982, 1427.7, 5.1, 0 )) && (speed == 0))// ���� ����� � ����
						{
							// ����� (car4)
							if (!IS_CHAR_DEAD(ped6))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped6, 614.951, 1428.982, 3.604);// ���������� ������
								SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
								SET_CHAR_RELATIONSHIP(ped6, 5, 0);
								SET_SENSE_RANGE(ped6, 30.0);
								SET_CHAR_WILL_USE_COVER(ped6, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
								SET_CHAR_SHOOT_RATE(ped6, 45);
							}
							if (!IS_CHAR_DEAD(ped10))
							{
								DETACH_PED(ped10, 1);
								FREEZE_CHAR_POSITION(ped10, 0);
								SET_CHAR_COORDINATES(ped10, 614.538, 1427.872, 3.604);// ���������� ������
							}

							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
								START_SCRIPT_CONVERSATION(1, 1);
							}		
							speed = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( ped7, 634.567, 1431.057, -1.1, 626.567, 1423.057, 5.1, 0 )) && (speed2 == 0))// ���� ����� � ����
						{
							// ���� (car5)
							if (!IS_CHAR_DEAD(ped7))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped7, 626.895, 1430.59, 3.604);// ���������� ������
								SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
								SET_CHAR_RELATIONSHIP(ped7, 5, 0);
								SET_SENSE_RANGE(ped7, 30.0);
								SET_CHAR_WILL_USE_COVER(ped7, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
								SET_CHAR_SHOOT_RATE(ped7, 45);
							}
							if (!IS_CHAR_DEAD(ped11))
							{
								DETACH_PED(ped11, 1);
								FREEZE_CHAR_POSITION(ped11, 0);
								SET_CHAR_COORDINATES(ped11, 626.483, 1429.479, 3.604);// ���������� ������
							}
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
								START_SCRIPT_CONVERSATION(1, 1);
							}		
							speed2 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( ped8, 605.667, 1410.639, -1.1, 597.667, 1402.639, 5.1, 0 )) && (speed3 == 0))// ���� ����� � ����
						{
							// ���� (car6)
							if (!IS_CHAR_DEAD(ped8))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped8, 610.485, 1415.093, 3.604);// ���������� ������
								SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
								SET_CHAR_RELATIONSHIP(ped8, 5, 0);
								SET_SENSE_RANGE(ped8, 30.0);
								SET_CHAR_WILL_USE_COVER(ped8, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
								SET_CHAR_SHOOT_RATE(ped8, 45);
							}
							if (!IS_CHAR_DEAD(ped12))
							{
								DETACH_PED(ped12, 1);
								FREEZE_CHAR_POSITION(ped12, 0);
								SET_CHAR_COORDINATES(ped12, 610.072, 1413.983, 3.604);// ���������� ������
							}
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
								START_SCRIPT_CONVERSATION(1, 1);
							}			
							speed3 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( ped9, 625.048, 1404.301, -1.1, 617.048, 1396.301, 6.1, 0 )) && (speed4 == 0))// ���� ����� � ����
						{
							// ����� (car7)
							if (!IS_CHAR_DEAD(ped9))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped9, 619.481, 1409.687, 3.604);// ���������� ������
								SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
								SET_CHAR_RELATIONSHIP(ped9, 5, 0);
								SET_SENSE_RANGE(ped9, 30.0);
								SET_CHAR_WILL_USE_COVER(ped9, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
								SET_CHAR_SHOOT_RATE(ped9, 45);
							}
							if (!IS_CHAR_DEAD(ped13))
							{
								DETACH_PED(ped13, 1);
								FREEZE_CHAR_POSITION(ped13, 0);
								SET_CHAR_COORDINATES(ped13, 619.069, 1408.577, 3.604);// ���������� ������
							}
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
								START_SCRIPT_CONVERSATION(1, 1);
							}	
							speed4 = 1;
						}

						// ���� �����
						if ((TIMERA() > 3500) && (play == 1))
						{
							play = 0;
						}

						// ����������� ������
						if ((IS_CAR_DEAD(car8)) && (IS_CAR_DEAD(car9)) && (IS_CAR_DEAD(car12)))
						{
							skip = 2;// ���������� ��������
							break;
						}

						GET_CAR_HEALTH(car8, &car_hp1);
						GET_CAR_HEALTH(car9, &car_hp2);

						if ((car_hp1 < 100) && (LanceH1 == 0))
						{
							EXPLODE_CAR(car8, 1, 1);
							LanceH1 = 1;
							WAIT( 250 );
						}
						if ((car_hp2 < 100) && (LanceH2 == 0))
						{
							EXPLODE_CAR(car9, 1, 1);
							LanceH2 = 1;
							WAIT( 250 );
						}
						if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped16)) && (LanceH3 == 0))
						{
							EXPLODE_CHAR_HEAD(ped16);
							EXPLODE_CAR(car12, 1, 1);
							LanceH3 = 1;
							WAIT( 50 );
						}

						GET_CHAR_HEALTH(ped1, &Cortes_hp);
						if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B3", 5000, 1);//~r~The Colonel is dead!					
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if ((Cortes_hp < 50) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 657.177, 1373.828, -5.0, 577.177, 1463.828, 25.0, 0 )))// ���� ����� � ����
						{
							EXPLODE_CHAR_HEAD(ped1);
							WAIT( 25 );
						}
					}
				}

				// ���������� ������
				REMOVE_BLIP(vert_ico);//������� ������ �� ������
				REMOVE_PICKUP(sweap_1);
				REMOVE_PICKUP(aid_1);
				G_CORTEZ = 5;

				if (skip == 1)
				{
					if (IS_CHAR_DEAD(GetPlayerPed()))
					{
						while (true)
						{
							WAIT( 0 );
							if (!IS_CHAR_DEAD(GetPlayerPed()))
							{
								break;
							}
						}
					}
					else
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
						SET_CHAR_COORDINATES(GetPlayerPed(), 193.919, -827.131, 2.028);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), -85.0);
						WAIT( 500 );
						DO_SCREEN_FADE_IN( 500 );// ��������� ���������� ������
					}
				}
				else if (skip == 2)
				{
					// ������ ������� ���
					SetTime(2500);
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
					SET_CHAR_COORDINATES(ped1, 41.0, -818.0, 2.604);// ���������� ������

					// ��������� ���� ���������
					REQUEST_CAR_RECORDING( 3013 );// ���� ������
					while (!HAS_CAR_RECORDING_BEEN_LOADED( 3013 )) WAIT(0);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3013, -10.0, 70.0, 0.0);// ���� ������

					SET_CAR_COORDINATES(car13, 587.045, 1686.647, 1.587);// ���������� �����
					SET_CAR_HEADING(car13, 130.0);
					WARP_CHAR_INTO_CAR(GetPlayerPed(), car13);// ����� ������ � �����

					// ������ ������
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 634.947, 1475.841, 2.741); // ���� ������� ������
					SET_CAM_POS			( camera, 629.109, 1583.829, 5.083 );//������������ ������
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
					SetTime(4000);

					// ������ ������
					POINT_CAM_AT_COORD	( camera, 628.874, 1506.061, 10.863); // ���� ������� ������
					SET_CAM_POS			( camera, 634.541, 1342.408, 13.411 );//������������ ������
					SetTime(4000);

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
					DESTROY_CAM( camera );
					SET_WIDESCREEN_BORDERS( 0 );

					STOP_PLAYBACK_RECORDED_CAR(car1);
					REMOVE_CAR_RECORDING( 3013 ); // ��������� ���� ����������

					SET_CAR_COORDINATES(car1, 606.133, 1486.415, -3.9454);// ���������� ����
					SET_CAR_HEADING(car1, 360.0);
					TURN_OFF_VEHICLE_EXTRA(car1, 1, 0);
					FREEZE_CAR_POSITION(car1, 1); 
					SET_CAR_IN_CUTSCENE(car1, 1);

					FORCE_WEATHER_NOW(WEATHER_SUNNY);
					RELEASE_WEATHER();

					//------------ �������� ----------------
					LOAD_ADDITIONAL_TEXT( "COL_5B", 6 ); // ��������� �������� �� *.GTX
					START_CUTSCENE_NOW("col_5b");
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

					SET_CAR_COORDINATES(car1, -26.928, -491.821, 1.587);// ���������� ����
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				}
				
				SET_MAX_WANTED_LEVEL(6);
				SET_CAR_DENSITY_MULTIPLIER(1);// �������� ����

				STOP_PLAYBACK_RECORDED_CAR(car10); // ������� (Maverick)
				STOP_PLAYBACK_RECORDED_CAR(car11); // ������� (Maverick)
				STOP_PLAYBACK_RECORDED_CAR(car12); // ������� (Hunter)
				REMOVE_CAR_RECORDING( 3014 ); // ������� (Maverick)
				REMOVE_CAR_RECORDING( 3015 ); // ������� (Maverick)
				REMOVE_CAR_RECORDING( 3016 ); // ������� (Hunter)

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ����

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM6);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM7);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM8);//��������� ������ ������

				// ��������� �� ������ �����
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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped25);//��������� ������ ����(� ����������� ��� ��������

				// ��������� �� ������ ���������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car8);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car9);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car10);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car11);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car12);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car13);//��������� ������ ������(� ����������� ������ ��������)

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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 5000);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +5000 );//��� ������ �����
					G_CORTEZ = 8;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 8))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(cortez_ico);//������� ������ �� ������
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_CORTEZ < 8)
	{
		cortez();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
