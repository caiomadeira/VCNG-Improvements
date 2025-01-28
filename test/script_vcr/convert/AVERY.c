/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, blip_on, skip, car_on, car_n, time_m, time_s, time_ms, timer_on, sound, textur1, skip_cam, help_1, help_2, help_3, help_4, sutosave;
float attach_1, attach_2, attach_3, attach_4, point_1, point_2, point_3, point_4, attach_on, tnt1_on, tnt2_on, tnt3_on, tnt4_on, bomb_add, fail, zone, grob_x, grob_y, grob_r, open_d;


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
void SetTime2(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
		{
			break;
		}
		if ((IS_GAME_KEYBOARD_KEY_PRESSED(GAME_KEY_ESC)) || (TIMERA() > time) || (IS_GAME_KEYBOARD_KEY_PRESSED(57)) || (IS_GAME_KEYBOARD_KEY_PRESSED(42)) || (IS_GAME_KEYBOARD_KEY_PRESSED(54)) ||(IS_GAME_KEYBOARD_KEY_PRESSED(28)))
		{
			skip_cam = 1;
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
void boyarsky(void)
{
	blip_on = 0;
	sutosave = 0;
	Blip avery_ico;
	WAIT(2000);
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
//============================== Four Iron ======================================
		if ((G_ONMISSION == 0) && (G_AVERY == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(691.139, 300.702, 4.845, &avery_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(avery_ico, BLIP_FAUSTIN);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(avery_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "LG_02");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 691.139, 300.702, 4.845, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 691.139, 300.702, 4.845, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(avery_ico);//������� ������ �� ������
				skip = 0; // ���������� ��������
				
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 691.139, 300.702, 4.845);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 65.0);
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 55);//������������� �����
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "TEX_1", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("tex_1");
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

				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(6, 0);//������������� �����
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				ADD_BLIP_FOR_COORD(758.381, 736.977, 5.287, &avery_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(avery_ico, BLIP_CLOTHES_SHOP);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(avery_ico, 0);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(avery_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "NE_SHOP");//������ �� ������ ��������� � ������� ����� "������� ������"

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_VW", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "TEX1_1", 5500, 1);//~g~Go and pick up some golfing clothes from Jocksports.
				SetTime(2000);

				Car car1, car2, car3, car4, car5, car6, car7;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7;
				Cam camera, camera2, camera3;
				Pickup sweap_1;
				int dm, cdm;

				uint PedM1 = MODEL_M_Y_GRUS_LO_01;// ��������
				uint PedM2 = MODEL_M_M_BUSINESS_02;// ������
				uint PedM3 = MODEL_M_M_BUSINESS_03;// ������2
				uint CarM1 = MODEL_HUNTLEY;// ��������
				uint CarM2 = MODEL_PRIMO;// ������ �����������
				car_on = 0;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(PedM1);// ��������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM2);// ������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM3);// ������2
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ������ ���������
				CREATE_CAR(CarM1, 286.232, -791.79, 5.445, &car1, TRUE);
				CREATE_CAR(CarM1, 289.629, -791.79, 5.445, &car2, TRUE);
				CREATE_CAR(CarM1, 293.025, -791.79, 5.445, &car3, TRUE);
				CREATE_CAR(CarM1, 296.422, -791.79, 5.445, &car4, TRUE);
				CREATE_CAR(CarM1, 299.905, -791.79, 5.445, &car5, TRUE);
				CREATE_CAR(CarM2, 299.905, -784.59, 5.445, &car6, TRUE);
				CREATE_CAR(CarM1, 303.181, -791.79, 5.445, &car7, TRUE);
				

				// ������ ������� �����
				CREATE_CHAR (26, PedM1, 291.032, -785.32, 5.06, &ped7, TRUE);// ��������
				CREATE_CHAR (26, PedM2, 286.386, -796.318, 5.06, &ped1, TRUE);// ��������
				CREATE_CHAR (26, PedM3, 289.619, -796.318, 5.06, &ped2, TRUE);// ��������
				CREATE_CHAR (26, PedM2, 292.961, -796.318, 5.06, &ped3, TRUE);// ��������
				CREATE_CHAR (26, PedM3, 296.473, -796.318, 5.06, &ped4, TRUE);// ��������

				// ������ ��������� � ������
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM2, &ped5);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM3, &ped6);//������ ���� �� ���� ����������

				// ������ ������ ��� ������
				CREATE_PICKUP_ROTATE(w_cue, 3, 1, 528.36, 812.989, 15.741, -87.532, -108.556, 8.524, &sweap_1);// ������ �����-������

				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( 758.381, 736.977, 5.287, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 758.381, 736.977, 5.287, &PlayR);//�������� "����� �� �����������"
					if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(avery_ico);//������� ������ �� ������
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 761.797, 738.767, 5.123 ); // ���� ������� ������
						SET_CAM_POS			( camera, 751.643, 733.932, 17.341 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 760.891, 738.67, 6.342, 2, -2);// ����� ��� � �����
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
						SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 3, 0);
						SET_CHAR_COORDINATES(GetPlayerPed(), 759.676, 737.762, 6.342);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), 125.0);
						SetTime(200);
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������

						// ���� ������
						CREATE_CAM( 3, &camera2 );
						CREATE_CAM( 14, &camera3 );
						POINT_CAM_AT_COORD	( camera, 759.495, 737.587, 5.486 ); // ���� ������� ������
						SET_CAM_POS			( camera, 757.903, 736.734, 6.006 );//������������ ������
						POINT_CAM_AT_COORD	( camera3, 759.495, 737.587, 6.765 ); // ���� ������� ������
						SET_CAM_POS			( camera3, 757.903, 736.734, 6.006 );//������������ ������
						SET_CAM_INTERP_STYLE_CORE( camera2, camera, camera3, 3500, 0 ); //����������� ������ �� ������ �� ����� ��������� � ����������� "SET_CAM_POS(camera, X, Y, Z)" 
						SET_CAM_ACTIVE( camera2, 1 );
						SET_CAM_PROPAGATE( camera2, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SetTime(3000);

						// �������
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BT", "TEX1_7", 0, 0);//Is this me?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BU", "TEX1_6", 0, 0);//Nice ass baby!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();


						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						DESTROY_CAM( camera2 );
						DESTROY_CAM( camera3 );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

						PRINT_STRING_IN_STRING("string", "TEX1_2", 5500, 1);//~g~Now head to the Leaf Links Golf Club.
						ADD_BLIP_FOR_COORD(534.333, 784.791, 15.724, &avery_ico);//������� ������ �� ������
						CHANGE_BLIP_SPRITE(avery_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(avery_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_SCALE(avery_ico, 0.6); // ������� ������ �� ������
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "NE_POINT");//������ �� ������ ��������� � ������� ����� "���������"

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
					while (TRUE)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 534.333, 784.791, 15.724, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 534.333, 784.791, 15.724, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							REMOVE_BLIP(avery_ico);//������� ������ �� ������
							// ����������� �����
							SET_CHAR_COORDINATES(ped1, 521.729, 1100.947, 13.319);// ���������� ����
							SET_CHAR_HEADING(ped1, -55.0);
							SET_CHAR_COORDINATES(ped2, 513.547, 1112.779, 13.319);// ���������� ����
							SET_CHAR_HEADING(ped2, -60.0);
							SET_CHAR_COORDINATES(ped3, 511.877, 1115.711, 13.319);// ���������� ����
							SET_CHAR_HEADING(ped3, -60.0);
							SET_CHAR_COORDINATES(ped4, 507.382, 1132.946, 13.319);// ���������� ����
							SET_CHAR_HEADING(ped4, -80.0);
							SET_CHAR_COORDINATES(ped7, 511.148, 1112.84, 13.319);// ���������� ����
							SET_CHAR_HEADING(ped7, 30.0);

							// ���������� ���������
							SET_CAR_COORDINATES(car1, 526.702, 825.113, 13.947);
							SET_CAR_HEADING(car1, -30.0);
							SET_CAR_COORDINATES(car2, 528.348, 1094.122, 8.964);
							SET_CAR_HEADING(car2, -60.0);
							SET_CAR_COORDINATES(car3, 526.523, 1096.905, 8.964);
							SET_CAR_HEADING(car3, -50.0);
							SET_CAR_COORDINATES(car4, 523.366, 1111.12, 8.964);
							SET_CAR_HEADING(car4, -135.0);
							SET_CAR_COORDINATES(car5, 515.357, 1127.517, 8.964);
							SET_CAR_HEADING(car5, -165.0);
							SET_CAR_COORDINATES(car7, 530.975, 1090.137, 8.964);
							SET_CAR_HEADING(car7, -45.0);
							//

							// ��������� �����
							UpdateWeaponOfPed(ped1, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_POOLCUE, TRUE);
							UpdateWeaponOfPed(ped2, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_POOLCUE, TRUE);
							UpdateWeaponOfPed(ped3, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_POOLCUE, TRUE);
							UpdateWeaponOfPed(ped4, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_POOLCUE, TRUE);
							UpdateWeaponOfPed(ped5, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_POOLCUE, TRUE);
							UpdateWeaponOfPed(ped6, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_POOLCUE, TRUE);
							UpdateWeaponOfPed(ped7, WEAPON_POOLCUE);
							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_POOLCUE, TRUE);

							// �������� ����� �������
							REQUEST_ANIMS( "ne_mini_golf" );
							while (!HAVE_ANIMS_LOADED( "ne_mini_golf" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "golf_drive", "ne_mini_golf", 8.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����

							// ������ ������������ ����
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							SET_MAX_WANTED_LEVEL(0);
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
							POINT_CAM_AT_COORD	( camera, 525.445, 1102.359, 10.592); // ���� ������� ������
							SET_CAM_POS			( camera, 541.071, 1092.879, 11.918 );//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SetTime(200);
							DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
							PRINT_STRING_IN_STRING("string", "TEX1_0", 5500, 1);//~g~The target is at the driving range enjoying a game of golf. Make sure it's his last.
							SetTime(3500);

							// ����� ������� ������
							POINT_CAM_AT_COORD	( camera, 507.615, 1111.145, 13.089 ); // ���� ������� ������
							SET_CAM_POS			( camera, 516.266, 1116.456, 13.982 );//������������ ������
							SetTime(3500);

							//������� ������
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

							// ������ ��� �����.
							ADD_BLIP_FOR_CHAR(ped7, &avery_ico);
							CHANGE_BLIP_SPRITE(avery_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
							CHANGE_BLIP_COLOUR(avery_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "MO_TARGET");//������ �� ������ "�������"
							CHANGE_BLIP_SCALE(avery_ico, 0.6); // ������� ������ �� ������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped7))// �������� ����� ���� ����
						{
							skip = 2;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), 532.459, 1092.475, 495.611, 1138.786, 0)) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 526.469, 1092.668, 12.326, 513.484, 1106.479, 18.411, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 517.291, 1093.854, 12.326, 500.091, 1133.854, 18.411, 0 )))
						{
							SET_SENSE_RANGE(ped1, 50.0);
							SET_CHAR_DECISION_MAKER(ped1, dm);
							SET_COMBAT_DECISION_MAKER(ped1, cdm);
							SET_CHAR_HEALTH(ped1, 200);
							SET_CHAR_KEEP_TASK(ped1, 1);
							TASK_COMBAT(ped1, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 0);

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

							SET_SENSE_RANGE(ped5, 50.0);
							SET_CHAR_DECISION_MAKER(ped5, dm);
							SET_COMBAT_DECISION_MAKER(ped5, cdm);
							SET_CHAR_HEALTH(ped5, 200);
							SET_CHAR_KEEP_TASK(ped5, 1);
							TASK_COMBAT(ped5, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 1);

							// ���� ���� ����������
							if (IS_CAR_IN_AREA_3D(car4, 534.316, 1089.333, 4.899, 495.611, 1138.786, 16.034, 0))//(!IS_CAR_DEAD(car4))
							{
								TASK_ENTER_CAR_AS_DRIVER(ped7, car4, -1);
								car_n = 4;
								car_on = 1;
							}
							else if (IS_CAR_IN_AREA_3D(car3, 534.316, 1089.333, 4.899, 495.611, 1138.786, 16.034, 0))//(!IS_CAR_DEAD(car3))
							{
								TASK_ENTER_CAR_AS_DRIVER(ped7, car4, -1);
								car_n = 3;
								car_on = 1;
							}
							else if (IS_CAR_IN_AREA_3D(car5, 534.316, 1089.333, 4.899, 495.611, 1138.786, 16.034, 0))//(!IS_CAR_DEAD(car5))
							{
								TASK_ENTER_CAR_AS_DRIVER(ped7, car5, -1);
								car_n = 5;
								car_on = 1;
							}
							else if (IS_CAR_IN_AREA_3D(car2, 534.316, 1089.333, 4.899, 495.611, 1138.786, 16.034, 0))//(!IS_CAR_DEAD(car2))
							{
								TASK_ENTER_CAR_AS_DRIVER(ped7, car2, -1);
								car_n = 2;
								car_on = 1;
							}
							else if (IS_CAR_IN_AREA_3D(car1, 534.316, 1089.333, 4.899, 495.611, 1138.786, 16.034, 0))//(!IS_CAR_DEAD(car1))
							{
								TASK_ENTER_CAR_AS_DRIVER(ped7, car1, -1);
								car_n = 1;
								car_on = 1;
							}
							else if (!IS_CAR_DEAD(car6))
							{
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped7, 520.177, 819.444, 13.947, 3, -1, 2.5);
								//TASK_ENTER_CAR_AS_PASSENGER(ped7, car6, -1, 0);
								//car_n = 6;
								car_on = 3;
							}

							// ��������� ��������� �����������
							SET_CAR_COORDINATES(car6, 535.379, 782.147, 16.408);
							SET_CAR_HEADING(car6, -70.0);

							// ������� ����
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BU_XXX1", "TEX1_3", 0, 0);//Who's this guy? Boys, deal with him.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BU_XXX2", "TEX1_9", 0, 0);//Get him!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if (car_on == 1)
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped7))
							{
								// ��� ����  �� ���������� ������
								if (car_n == 1)
								{
									TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car1, 520.177, 819.444, 13.947, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������
								}
								else if (car_n == 2)
								{
									TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car2, 520.177, 819.444, 13.947, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������
								}
								else if (car_n == 3)
								{
									TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car3, 520.177, 819.444, 13.947, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������
								}
								else if (car_n == 4)
								{
									TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car4, 520.177, 819.444, 13.947, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������
								}
								else if (car_n == 5)
								{
									TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car5, 520.177, 819.444, 13.947, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������
								}
								car_on = 3;
							}
						}

						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 520.177, 819.444, 13.947, &PedR);//�������� "����� �� �����������"
						if ((PedR < 4.5) && (car_on == 3))
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped7))
							{
								if (car_n == 1)
								{
									TASK_LEAVE_CAR(ped7, car1);
								}
								else if (car_n == 2)
								{
									TASK_LEAVE_CAR(ped7, car2);
								}
								else if (car_n == 3)
								{
									TASK_LEAVE_CAR(ped7, car3);
								}
								else if (car_n == 4)
								{
									TASK_LEAVE_CAR(ped7, car4);
								}
								else if (car_n == 5)
								{
									TASK_LEAVE_CAR(ped7, car5);
								}
							}
							TASK_ENTER_CAR_AS_PASSENGER(ped7, car6, -1, 0);
							car_on = 2;
						}
						if (car_on == 2)
						{
							if (!IS_CHAR_SITTING_IN_ANY_CAR(ped7))
							{
								car_on = 4;
							}
						}
						// ���� �������� ��������
						if (car_on == 4)
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped7))
							{
								TASK_CAR_DRIVE_WANDER(ped6, car6, 40.0, 2);
								car_on = 5;
							}
						}

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if (IS_CHAR_DEAD(ped7))// �������� ����� ���� ����
						{
							skip = 2;// ���������� ��������
							break;
						}
						else if (PlayR > 200.3)
						{
							PRINT_STRING_IN_STRING("string", "TEX1_5", 5500, 1);//~r~He got away!
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
				WAIT( 100 );
				REMOVE_BLIP(avery_ico);//������� ������ �� ������
				SET_MAX_WANTED_LEVEL(6);

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������

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
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//��������� ������ ������(� ����������� ������ ��������)

				REMOVE_PICKUP(sweap_1);// ��������� ����

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
					PRINT_HELP("CLOTH4"); //Country Club outfit delivered to The Golf Club in Leaf Links.
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
					G_AVERY = 2;
					sutosave = 1;
				}

				blip_on = 0;
				G_ONMISSION = 0;
			}
		}

//============================== Demolition Man ======================================
		else if ((G_ONMISSION == 0) && (G_AVERY == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(691.139, 300.702, 4.845, &avery_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(avery_ico, BLIP_FAUSTIN);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(avery_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "LG_02");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 691.139, 300.702, 4.845, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 691.139, 300.702, 4.845, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(avery_ico);//������� ������ �� ������
				skip = 0; // ���������� ��������

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 691.139, 300.702, 4.845);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 65.0);
				
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 55);//������������� �����
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "TEX_3", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("tex_3");
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

				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(6, 35);//������������� �����
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18;
				Object barrel_1, barrel_2, barrel_3, barrel_4, tnt_1, tnt_2, tnt_3, tnt_4;
				Blip tnt1_ico, tnt2_ico, tnt3_ico, tnt4_ico;
				Texture fon, tnt;
				Cam camera;

				textur1 = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur1, "fon_hud" );
				tnt = GET_TEXTURE( textur1, "tnt_hud" );

				uint PedM1 = MODEL_M_M_PLATIN_02;// �������
				uint PedM2 = MODEL_M_M_ARMOURED;// ��������
				uint PedM3 = MODEL_M_Y_FIREMAN;// ��������
				uint CarM1 = MODEL_SPEEDO;// ������
				uint CarM2 = MODEL_TOURMAV;// �������
				uint CarM3 = MODEL_FIRETRUK;// �������� ������
				uint barrel = barrel1;// �����
				uint dynamite_1 = dynamite;// �������

				attach_1 = 0;
				attach_2 = 0;
				attach_3 = 0;
				attach_4 = 0;
				point_1 = 0;
				point_2 = 0;
				point_3 = 0;
				point_4 = 0;
				attach_on = 0;
				tnt1_on = 0;
				tnt2_on = 0;
				tnt3_on = 0;
				tnt4_on = 0;
				bomb_add = 0;
				time_m = 7;
				time_s = 0;
				time_ms = 0;
				sound = 0;
				timer_on = 0;
				skip_cam = 0;
				zone = 1;
				help_1 = 0;
				help_2 = 0;
				help_3 = 0;
				help_4 = 0;

				// ��������� ����������
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				// ��������� ���������
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				// ��������� �������� ������
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

				// ��������� ����������
				REQUEST_MODEL(PedM1);// �������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ��������� ���������
				REQUEST_MODEL(PedM2);// ��������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ��������� ���������
				REQUEST_MODEL(PedM3);// ��������
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ��������� �����
				REQUEST_MODEL(barrel);// �����
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);

				// ��������� �������
				REQUEST_MODEL(dynamite_1);// �����
				while (!HAS_MODEL_LOADED(dynamite_1)) WAIT(0);

				// ������ ������
				CREATE_CAR(CarM1, 659.915, 180.789, 5.409, &car1, TRUE);
				SET_CAR_HEADING(car1, 79.984);

				// ������ �������
				CREATE_CAR(CarM2, 284.8115, -787.1965, 5.445457, &car2, TRUE);

				// ������ �������� ����������
				CREATE_CAR(CarM3, 276.052, -792.49, 5.445457, &car3, TRUE);

				// ������ �����
				CREATE_OBJECT_NO_OFFSET(barrel, 290.424, -798.9435, 5.445457, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 291.765, -798.9435, 5.445457, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 287.742, -798.9435, 5.445457, &barrel_3, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 289.083, -798.9435, 5.445457, &barrel_4, TRUE);

				// ������ �������
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 294.8487, -798.9435, 5.445457, &tnt_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 295.5919, -798.9435, 5.445457, &tnt_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 293.3623, -798.9435, 5.445457, &tnt_3, TRUE);
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 294.1054, -798.9435, 5.445457, &tnt_4, TRUE);				
				
				// ������ �������
				CREATE_CHAR (26, PedM1, 290.8138, -794.7287, 5.059736, &ped1, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 295.2588, -794.7287, 5.059736, &ped2, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 289.3321, -794.7287, 5.059736, &ped3, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 298.2222, -794.7287, 5.059736, &ped4, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 299.7038, -794.7287, 5.059736, &ped5, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 301.1854, -794.7287, 5.059736, &ped6, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 293.7771, -794.7287, 5.059736, &ped7, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 292.2955, -794.7287, 5.059736, &ped8, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 287.8505, -794.7287, 5.059736, &ped9, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 286.3689, -794.7287, 5.059736, &ped10, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 296.7405, -794.7287, 5.059736, &ped11, TRUE);// ������ ����
				CREATE_CHAR (26, PedM1, 284.8872, -794.7287, 5.059736, &ped12, TRUE);// ������ ����

				// ������ ����������
				CREATE_CHAR (26, PedM2, 287.8299, -792.8582, 5.059736, &ped13, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 289.3012, -792.8582, 5.059736, &ped14, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 284.8872, -792.8582, 5.059736, &ped15, TRUE);// ������ ����
				CREATE_CHAR (26, PedM2, 286.3585, -792.8582, 5.059736, &ped16, TRUE);// ������ ����

				// ������ ��������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped17);//������ ���� �� ���� ����������
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 0, &ped18);//������ ���� ��� ��������� ����������

				// ������ �� ����������
				ADD_BLIP_FOR_CAR(car1, &avery_ico);
				CHANGE_BLIP_SPRITE(avery_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(avery_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(avery_ico, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "NE_CAR");//������ �� ������ ��������� � ������� ����� "������ ������"
				PRINT_STRING_IN_STRING("string", "TEX3_16", 5500, 1);//~g~Get to the ~w~TOPFUN ~g~van near the building site to be demolished.
				SetTime(2000);
				while (true)
				{
					WAIT( 0 );
					if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
					{
						break;
					}
					if (IS_CAR_DEAD(car1))
					{
						PRINT_STRING_IN_STRING("string", "TEX3_31", 5500, 1);//~r~You destroyed the TOPFUN van that contained the bombs and RC helicopter!
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
					REMOVE_BLIP(avery_ico);//������� ������ �� ������
					SetTime(1000);
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

					//������������� �������� ����� � ������ ���� �������
					REQUEST_ANIMS( "ne_topfun" );//��������� ���� � ���������
					while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
					SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_out", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
					SetTime(2000);

					// ��������� �����
					SET_OBJECT_COORDINATES(barrel_1, 530.574, 151.342, 3.2461);
					SET_OBJECT_COORDINATES(barrel_2, 589.549, 184.972, 12.361);
					SET_OBJECT_COORDINATES(barrel_3, 521.147, 171.132, 21.556);
					SET_OBJECT_COORDINATES(barrel_4, 573.008, 149.875, 30.817);

					FREEZE_OBJECT_POSITION(barrel_1, 1);
					FREEZE_OBJECT_POSITION(barrel_2, 1);
					FREEZE_OBJECT_POSITION(barrel_3, 1);
					FREEZE_OBJECT_POSITION(barrel_4, 1);

					// ��������� �������
					SET_OBJECT_COORDINATES(tnt_1, 662.852, 185.889, 5.294);
					SET_OBJECT_COORDINATES(tnt_2, 662.852, 188.972, 5.406);
					SET_OBJECT_COORDINATES(tnt_3, 662.852, 191.889, 5.509);
					SET_OBJECT_COORDINATES(tnt_4, 662.852, 194.889, 5.618);

					// ��������� �������
					SET_CAR_COORDINATES(car2, 659.192, 190.431, 5.595);
					SET_CAR_HEADING(car2, 87.868);
					SET_CAR_LIVERY(car2, 2);

					// ��������� ����������
					SET_CHAR_COORDINATES(ped1, 554.419, 161.447, 3.21);// ���������� ������
					SET_CHAR_HEADING(ped1, -170.092);
					SET_CHAR_COORDINATES(ped2, 593.074, 157.246, 3.166);// ���������� ������
					SET_CHAR_HEADING(ped2, -91.136);
					SET_CHAR_COORDINATES(ped3, 549.199, 184.821, 12.387);// ���������� ������
					SET_CHAR_HEADING(ped3, -71.317);
					SET_CHAR_COORDINATES(ped4, 550.529, 184.875, 12.387);// ���������� ������
					SET_CHAR_HEADING(ped4, 110.958);
					SET_CHAR_COORDINATES(ped5, 593.101, 176.68, 12.387);// ���������� ������
					SET_CHAR_HEADING(ped5, -82.133);
					SET_CHAR_COORDINATES(ped6, 593.313, 157.207, 12.387);// ���������� ������
					SET_CHAR_HEADING(ped6, -98.326);
					SET_CHAR_COORDINATES(ped7, 514.414, 176.56, 21.6);// ���������� ������
					SET_CHAR_HEADING(ped7, 87.306);
					SET_CHAR_COORDINATES(ped8, 514.561, 178.06, 21.6);// ���������� ������
					SET_CHAR_HEADING(ped8, 176.813);
					SET_CHAR_COORDINATES(ped9, 545.241, 176.698, 30.89);// ���������� ������
					SET_CHAR_HEADING(ped9, -81.427);
					SET_CHAR_COORDINATES(ped10, 531.297, 156.989, 30.89);// ���������� ������
					SET_CHAR_HEADING(ped10, 76.446);
					SET_CHAR_COORDINATES(ped11, 593.518, 176.651, 30.89);// ���������� ������
					SET_CHAR_HEADING(ped11, -81.427);
					SET_CHAR_COORDINATES(ped12, 562.347, 166.747, 30.89);// ���������� ������
					SET_CHAR_HEADING(ped12, 84.469);

					// ��������� ����������
					UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_23, TRUE);
					UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_23);
					SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_23, TRUE);

					// ��������� ������
					SET_CHAR_COORDINATES(ped13, 554.036, 153.891, 21.6);// ���������� ������
					SET_CHAR_HEADING(ped13, 0.0);
					SET_CHAR_COORDINATES(ped14, 537.143, 186.822, 21.6);// ���������� ������
					SET_CHAR_HEADING(ped14, -174.134);
					SET_CHAR_COORDINATES(ped15, 556.366, 152.773, 30.89);// ���������� ������
					SET_CHAR_HEADING(ped15, -1.083);
					SET_CHAR_COORDINATES(ped16, 553.106, 186.969, 30.89);// ���������� ������
					SET_CHAR_HEADING(ped16, -174.134);

					SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);

					SET_CHAR_RELATIONSHIP(ped1, 5, 0);
					SET_CHAR_RELATIONSHIP(ped2, 5, 0);
					SET_CHAR_RELATIONSHIP(ped3, 5, 0);
					SET_CHAR_RELATIONSHIP(ped4, 5, 0);
					SET_CHAR_RELATIONSHIP(ped5, 5, 0);
					SET_CHAR_RELATIONSHIP(ped6, 5, 0);
					SET_CHAR_RELATIONSHIP(ped7, 5, 0);
					SET_CHAR_RELATIONSHIP(ped8, 5, 0);
					SET_CHAR_RELATIONSHIP(ped9, 5, 0);
					SET_CHAR_RELATIONSHIP(ped10, 5, 0);
					SET_CHAR_RELATIONSHIP(ped11, 5, 0);
					SET_CHAR_RELATIONSHIP(ped12, 5, 0);
					SET_CHAR_RELATIONSHIP(ped13, 5, 0);
					SET_CHAR_RELATIONSHIP(ped14, 5, 0);
					SET_CHAR_RELATIONSHIP(ped15, 5, 0);
					SET_CHAR_RELATIONSHIP(ped16, 5, 0);

					SET_SENSE_RANGE(ped1, 20.0);
					SET_SENSE_RANGE(ped2, 20.0);
					SET_SENSE_RANGE(ped3, 20.0);
					SET_SENSE_RANGE(ped4, 20.0);
					SET_SENSE_RANGE(ped5, 20.0);
					SET_SENSE_RANGE(ped6, 20.0);
					SET_SENSE_RANGE(ped7, 20.0);
					SET_SENSE_RANGE(ped8, 20.0);
					SET_SENSE_RANGE(ped9, 20.0);
					SET_SENSE_RANGE(ped10, 20.0);
					SET_SENSE_RANGE(ped11, 20.0);
					SET_SENSE_RANGE(ped12, 20.0);
					SET_SENSE_RANGE(ped13, 20.0);
					SET_SENSE_RANGE(ped14, 20.0);
					SET_SENSE_RANGE(ped15, 20.0);
					SET_SENSE_RANGE(ped16, 20.0);

					SET_CHAR_WILL_USE_COVER(ped1, 1);
					SET_CHAR_WILL_USE_COVER(ped2, 1);
					SET_CHAR_WILL_USE_COVER(ped3, 1);
					SET_CHAR_WILL_USE_COVER(ped4, 1);
					SET_CHAR_WILL_USE_COVER(ped5, 1);
					SET_CHAR_WILL_USE_COVER(ped6, 1);
					SET_CHAR_WILL_USE_COVER(ped7, 1);
					SET_CHAR_WILL_USE_COVER(ped8, 1);
					SET_CHAR_WILL_USE_COVER(ped9, 1);
					SET_CHAR_WILL_USE_COVER(ped10, 1);
					SET_CHAR_WILL_USE_COVER(ped11, 1);
					SET_CHAR_WILL_USE_COVER(ped12, 1);
					SET_CHAR_WILL_USE_COVER(ped13, 1);
					SET_CHAR_WILL_USE_COVER(ped14, 1);
					SET_CHAR_WILL_USE_COVER(ped15, 1);
					SET_CHAR_WILL_USE_COVER(ped16, 1);

					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);

					// ��������� ������
					UpdateWeaponOfPed(ped13, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped14, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped15, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped16, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_PISTOL, TRUE);

					SET_CHAR_VISIBLE(GetPlayerPed(), 0); //���������� �����
					TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), car2, TRUE);//����� ������ � �������

					//������������� �������� �������
					REQUEST_ANIMS( "missgunlockup" );//��������� ���� � ���������
					while (!HAVE_ANIMS_LOADED( "missgunlockup" )) WAIT(0);
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "rpg_loop", "missgunlockup", 1.0, 0, 0, 0, 0, 30000 );//���������������� �������� �� ����
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "rpg_loop", "missgunlockup", 1.0, 0, 0, 0, 0, 30000 );//���������������� �������� �� ����
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "rpg_loop", "missgunlockup", 1.0, 0, 0, 0, 0, 30000 );//���������������� �������� �� ����
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "rpg_loop", "missgunlockup", 1.0, 0, 0, 0, 0, 30000 );//���������������� �������� �� ����

					// -------------------- �������� --------------------

					//���������� ������
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 585.464, 174.283, 19.035 ); // ���� ������� ������
					SET_CAM_POS			( camera, 695.566, 233.794, 20.612 );//������������ ������
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					PRINT_STRING_IN_STRING("string", "TEX3_1", 5000, 1);//~g~Use the RC helicopter to transport bombs to four demolition points on the building site.
					SetTime2(5000);

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� �������
						POINT_CAM_AT_COORD	( camera, 659.192, 190.431, 5.595 ); // ���� ������� ������
						SET_CAM_POS			( camera, 644.897, 185.911, 12.477 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_2", 5000, 1);//~g~You must place one bomb at each target. You can place bombs in any order.
						SetTime2(5000);
					}

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� �����
						POINT_CAM_AT_COORD	( camera, 662.852, 187.512, 5.294 ); // ���� ������� ������
						SET_CAM_POS			( camera, 662.892, 182.669, 6.227 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_30", 5000, 1);//~g~To pick up a bomb, simply maneuver the RC helicopter next to it. The RC Helicopter can carry one bomb at a time.
						SetTime2(5000);
					}

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� �����
						POINT_CAM_AT_COORD	( camera, 531.365, 151.43, 3.246 ); // ���� ������� ������
						SET_CAM_POS			( camera, 524.539, 150.81, 3.486 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_39", 5000, 1);//~g~To drop a bomb press the ~h~~k~~VEHICLE_HANDBRAKE~ ~g~button.
						SetTime2(5000);
					}

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� ����� � ������
						POINT_CAM_AT_COORD	( camera, 589.549, 184.972, 12.36 ); // ���� ������� ������
						SET_CAM_POS			( camera, 589.249, 162.844, 12.595 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_5", 5000, 1);//~g~If you place a bomb unsuccessfully you can pick it up and try again.
						SetTime2(5000);
					}

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� ����� � ������ 2
						POINT_CAM_AT_COORD	( camera, 521.147, 171.881, 21.556 ); // ���� ������� ������
						SET_CAM_POS			( camera, 533.574, 171.913, 22.048 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_6", 5000, 1);//~g~Once you have picked up a bomb for the first time, the detonation timer will start.
						SetTime2(5000);
					}

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� ����� � ������ 3
						POINT_CAM_AT_COORD	( camera, 573.008, 149.181, 30.817 ); // ���� ������� ������
						SET_CAM_POS			( camera, 552.781, 155.149, 31.316 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_7", 5000, 1);//~g~You must then place the remaining bombs in 7 minutes!
						SetTime2(5000);
					}

					if (skip_cam == 0)
					{
						// ����� ������� ������ �� ��������
						POINT_CAM_AT_COORD	( camera, 550.765, 170.625, 6.145 ); // ���� ������� ������
						SET_CAM_POS			( camera, 550.561, 127.476, 6.171 );//������������ ������
						PRINT_STRING_IN_STRING("string", "TEX3_27", 5000, 1);//~g~A central stairway allows access to all the floors in the building.
						SetTime2(5000);
					}
					// -------------------- �������� --------------------

					//������� ������
					SET_CAM_BEHIND_PED( GetPlayerPed() );
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );
					LOCK_CAR_DOORS(car2, 2); // �������� ����������
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
					SET_FOLLOW_VEHICLE_CAM_SUBMODE(2);

					ADD_BLIP_FOR_OBJECT(tnt_1, &tnt1_ico);
					CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(tnt1_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
					CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // ������� ������ �� ������
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 1"

					ADD_BLIP_FOR_OBJECT(tnt_2, &tnt2_ico);
					CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(tnt2_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
					CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // ������� ������ �� ������
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 2"

					ADD_BLIP_FOR_OBJECT(tnt_3, &tnt3_ico);
					CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(tnt3_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
					CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // ������� ������ �� ������
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 3"

					ADD_BLIP_FOR_OBJECT(tnt_4, &tnt4_ico);
					CHANGE_BLIP_SPRITE(tnt4_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(tnt4_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
					CHANGE_BLIP_SCALE(tnt4_ico, 0.6); // ������� ������ �� ������
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt4_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 4"

					// ���
					if (fail > 2)
					{
						SET_CAR_PROOFS( car2, 0, 1, 1, 1, 1 );
						SET_CAR_STRONG(car2, 0);
						SET_CAR_CAN_BE_VISIBLY_DAMAGED(car2, 0);
					}

					while (true)
					{
						WAIT( 0 );
						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������



// ------------------------------------------------ ����� ���� ------------------------------------------------
						// ��������� ���!!!!!!!!!!!!!!!!!!!!!!!
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 530.574+1.5, 151.342+1.5, 3.2461-0.5, 530.574-1.5, 151.342-1.5, 3.2461+5.0, 0 )) && (help_1 == 0) && (point_1 == 0))
						{
							help_1 = 1;
							PRINT_HELP_FOREVER("TEX3_40"); //To drop a bomb press the ~INPUT_PHONE_ACCEPT~ button.
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 530.574+1.5, 151.342+1.5, 3.2461-0.5, 530.574-1.5, 151.342-1.5, 3.2461+5.0, 0 )) && (help_1 == 1))
						{
							CLEAR_HELP(); // ������� ����� ���������
							help_1 = 0;
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 589.549+1.5, 184.972+1.5, 12.361-0.5, 589.549-1.5, 184.972-1.5, 12.361+5.0, 0 )) && (help_2 == 0) && (point_2 == 0))
						{
							help_2 = 1;
							PRINT_HELP_FOREVER("TEX3_40"); //To drop a bomb press the ~INPUT_PHONE_ACCEPT~ button.
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 589.549+1.5, 184.972+1.5, 12.361-0.5, 589.549-1.5, 184.972-1.5, 12.361+5.0, 0 )) && (help_2 == 1))
						{
							CLEAR_HELP(); // ������� ����� ���������
							help_2 = 0;
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 521.147+1.5, 171.132+1.5, 21.556-0.5, 521.147-1.5, 171.132-1.5, 21.556+5.0, 0 )) && (help_3 == 0) && (point_3 == 0))
						{
							help_3 = 1;
							PRINT_HELP_FOREVER("TEX3_40"); //To drop a bomb press the ~INPUT_PHONE_ACCEPT~ button.
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 521.147+1.5, 171.132+1.5, 21.556-0.5, 521.147-1.5, 171.132-1.5, 21.556+5.0, 0 )) && (help_3 == 1))
						{
							CLEAR_HELP(); // ������� ����� ���������
							help_3 = 0;
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 573.008+1.5, 149.875+1.5, 30.817-0.5, 573.008-1.5, 149.875-1.5, 30.817+5.0, 0 )) && (help_4 == 0) && (point_4 == 0))
						{
							help_4 = 1;
							PRINT_HELP_FOREVER("TEX3_40"); //To drop a bomb press the ~INPUT_PHONE_ACCEPT~ button.
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 573.008+1.5, 149.875+1.5, 30.817-0.5, 573.008-1.5, 149.875-1.5, 30.817+5.0, 0 )) && (help_4 == 1))
						{
							CLEAR_HELP(); // ������� ����� ���������
							help_4 = 0;
						}

						if ((IS_BUTTON_PRESSED( 0, 16 )) || ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()))) //���������� ENTER
						{
							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 530.574+1.5, 151.342+1.5, 3.2461-0.5, 530.574-1.5, 151.342-1.5, 3.2461+5.0, 0 )) && (attach_on == 1) && (point_1 == 0))
							{
								if (attach_1 == 1)
								{
									attach_on = 0;
									tnt1_on = 1;
									attach_1 = 0;
									point_1 = 1;
									DETACH_OBJECT(tnt_1, 1);
									SET_OBJECT_COORDINATES(tnt_1, 530.574, 151.342, 3.2461+0.782);
									SET_OBJECT_HEADING(tnt_1, 0.5);
									FREEZE_OBJECT_POSITION(tnt_1, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_2 == 1)
								{
									attach_on = 0;
									tnt2_on = 1;
									attach_2 = 0;
									point_1 = 1;
									DETACH_OBJECT(tnt_2, 1);
									SET_OBJECT_COORDINATES(tnt_2, 530.574, 151.342, 3.2461+0.782);
									SET_OBJECT_HEADING(tnt_2, 0.5);
									FREEZE_OBJECT_POSITION(tnt_2, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_3 == 1)
								{
									attach_on = 0;
									tnt3_on = 1;
									attach_3 = 0;
									point_1 = 1;
									DETACH_OBJECT(tnt_3, 1);
									SET_OBJECT_COORDINATES(tnt_3, 530.574, 151.342, 3.2461+0.782);
									SET_OBJECT_HEADING(tnt_3, 0.5);
									FREEZE_OBJECT_POSITION(tnt_3, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_4 == 1)
								{
									attach_on = 0;
									tnt4_on = 1;
									attach_4 = 0;
									point_1 = 1;
									DETACH_OBJECT(tnt_4, 1);
									SET_OBJECT_COORDINATES(tnt_4, 530.574, 151.342, 3.2461+0.782);
									SET_OBJECT_HEADING(tnt_4, 0.5);
									FREEZE_OBJECT_POSITION(tnt_4, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
							}
							else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 589.549+1.5, 184.972+1.5, 12.361-0.5, 589.549-1.5, 184.972-1.5, 12.361+5.0, 0 )) && (attach_on == 1) && (point_2 == 0))
							{
								if (attach_1 == 1)
								{
									attach_on = 0;
									tnt1_on = 1;
									attach_1 = 0;
									point_2 = 1;
									DETACH_OBJECT(tnt_1, 1);
									SET_OBJECT_COORDINATES(tnt_1, 589.549, 184.972, 12.361+0.782);
									SET_OBJECT_HEADING(tnt_1, 0.5);
									FREEZE_OBJECT_POSITION(tnt_1, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_2 == 1)
								{
									attach_on = 0;
									tnt2_on = 1;
									attach_2 = 0;
									point_2 = 1;
									DETACH_OBJECT(tnt_2, 1);
									SET_OBJECT_COORDINATES(tnt_2, 589.549, 184.972, 12.361+0.782);
									SET_OBJECT_HEADING(tnt_2, 0.5);
									FREEZE_OBJECT_POSITION(tnt_2, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_3 == 1)
								{
									attach_on = 0;
									tnt3_on = 1;
									attach_3 = 0;
									point_2 = 1;
									DETACH_OBJECT(tnt_3, 1);
									SET_OBJECT_COORDINATES(tnt_3, 589.549, 184.972, 12.361+0.782);
									SET_OBJECT_HEADING(tnt_3, 0.5);
									FREEZE_OBJECT_POSITION(tnt_3, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_4 == 1)
								{
									attach_on = 0;
									tnt4_on = 1;
									attach_4 = 0;
									point_2 = 1;
									DETACH_OBJECT(tnt_4, 1);
									SET_OBJECT_COORDINATES(tnt_4, 589.549, 184.972, 12.361+0.782);
									SET_OBJECT_HEADING(tnt_4, 0.5);
									FREEZE_OBJECT_POSITION(tnt_4, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
							}
							else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 521.147+1.5, 171.132+1.5, 21.556-0.5, 521.147-1.5, 171.132-1.5, 21.556+5.0, 0 )) && (attach_on == 1) && (point_3 == 0))
							{
								if (attach_1 == 1)
								{
									attach_on = 0;
									tnt1_on = 1;
									attach_1 = 0;
									point_3 = 1;
									DETACH_OBJECT(tnt_1, 1);
									SET_OBJECT_COORDINATES(tnt_1, 521.147, 171.132, 21.556+0.782);
									SET_OBJECT_HEADING(tnt_1, 0.5);
									FREEZE_OBJECT_POSITION(tnt_1, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_2 == 1)
								{
									attach_on = 0;
									tnt2_on = 1;
									attach_2 = 0;
									point_3 = 1;
									DETACH_OBJECT(tnt_2, 1);
									SET_OBJECT_COORDINATES(tnt_2, 521.147, 171.132, 21.556+0.782);
									SET_OBJECT_HEADING(tnt_2, 0.5);
									FREEZE_OBJECT_POSITION(tnt_2, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_3 == 1)
								{
									attach_on = 0;
									tnt3_on = 1;
									attach_3 = 0;
									point_3 = 1;
									DETACH_OBJECT(tnt_3, 1);
									SET_OBJECT_COORDINATES(tnt_3, 521.147, 171.132, 21.556+0.782);
									SET_OBJECT_HEADING(tnt_3, 0.5);
									FREEZE_OBJECT_POSITION(tnt_3, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_4 == 1)
								{
									attach_on = 0;
									tnt4_on = 1;
									attach_4 = 0;
									point_3 = 1;
									DETACH_OBJECT(tnt_4, 1);
									SET_OBJECT_COORDINATES(tnt_4, 521.147, 171.132, 21.556+0.782);
									SET_OBJECT_HEADING(tnt_4, 0.5);
									FREEZE_OBJECT_POSITION(tnt_4, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
							}
							else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 573.008+1.5, 149.875+1.5, 30.817-0.5, 573.008-1.5, 149.875-1.5, 30.817+5.0, 0 )) && (attach_on == 1) && (point_4 == 0))
							{
								if (attach_1 == 1)
								{
									attach_on = 0;
									tnt1_on = 1;
									attach_1 = 0;
									point_4 = 1;
									DETACH_OBJECT(tnt_1, 1);
									SET_OBJECT_COORDINATES(tnt_1, 573.008, 149.875, 30.817+0.782);
									SET_OBJECT_HEADING(tnt_1, 0.5);
									FREEZE_OBJECT_POSITION(tnt_1, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_2 == 1)
								{
									attach_on = 0;
									tnt2_on = 1;
									attach_2 = 0;
									point_4 = 1;
									DETACH_OBJECT(tnt_2, 1);
									SET_OBJECT_COORDINATES(tnt_2, 573.008, 149.875, 30.817+0.782);
									SET_OBJECT_HEADING(tnt_2, 0.5);
									FREEZE_OBJECT_POSITION(tnt_2, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_3 == 1)
								{
									attach_on = 0;
									tnt3_on = 1;
									attach_3 = 0;
									point_4 = 1;
									DETACH_OBJECT(tnt_3, 1);
									SET_OBJECT_COORDINATES(tnt_3, 573.008, 149.875, 30.817+0.782);
									SET_OBJECT_HEADING(tnt_3, 0.5);
									FREEZE_OBJECT_POSITION(tnt_3, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
								else if (attach_4 == 1)
								{
									attach_on = 0;
									tnt4_on = 1;
									attach_4 = 0;
									point_4 = 1;
									DETACH_OBJECT(tnt_4, 1);
									SET_OBJECT_COORDINATES(tnt_4, 573.008, 149.875, 30.817+0.782);
									SET_OBJECT_HEADING(tnt_4, 0.5);
									FREEZE_OBJECT_POSITION(tnt_4, 1);
									PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
									bomb_add += 1;
								}
							}
							else
							{
								if (attach_1 == 1) DETACH_OBJECT(tnt_1, 1);
								else if (attach_2 == 1) DETACH_OBJECT(tnt_2, 1);
								else if (attach_3 == 1) DETACH_OBJECT(tnt_3, 1);
								else if (attach_4 == 1) DETACH_OBJECT(tnt_4, 1);
								attach_on = 0;
								attach_1 = 0;
								attach_2 = 0;
								attach_3 = 0;
								attach_4 = 0;
							}

							REMOVE_BLIP(tnt1_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt2_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt3_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt4_ico);//������� ������ �� ������

							if (tnt1_on == 0)
							{
								ADD_BLIP_FOR_OBJECT(tnt_1, &tnt1_ico);
								CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt1_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 1"
							}
							if (tnt2_on == 0)
							{
								ADD_BLIP_FOR_OBJECT(tnt_2, &tnt2_ico);
								CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt2_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 2"
							}
							if (tnt3_on == 0)
							{
								ADD_BLIP_FOR_OBJECT(tnt_3, &tnt3_ico);
								CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt3_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 3"
							}
							if (tnt4_on == 0)
							{
								ADD_BLIP_FOR_OBJECT(tnt_4, &tnt4_ico);
								CHANGE_BLIP_SPRITE(tnt4_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt4_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt4_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt4_ico, "NE_TNT_1");//������ �� ������ ��������� � ������� ����� "������� 4"
							}
						}
//------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------ �������� ���� ------------------------

						if ((IS_VEHICLE_TOUCHING_OBJECT(car2, tnt_1)) && (attach_on == 0) && (tnt1_on == 0))
						{
							timer_on = 1;
							attach_1 = 1;
							attach_on = 1;
							ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.6, 0, 0, 0);
							REMOVE_BLIP(tnt1_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt2_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt3_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt4_ico);//������� ������ �� ������

							if (point_1 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_1, &tnt1_ico);
								CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt1_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 1"
							}
							if (point_2 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_2, &tnt2_ico);
								CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt2_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 2"
							}
							if (point_3 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_3, &tnt3_ico);
								CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt3_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 3"
							}
							if (point_4 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_4, &tnt4_ico);
								CHANGE_BLIP_SPRITE(tnt4_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt4_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt4_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt4_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 4"
							}
						}
						else if ((IS_VEHICLE_TOUCHING_OBJECT(car2, tnt_2)) && (attach_on == 0) && (tnt2_on == 0))
						{
							timer_on = 1;
							attach_2 = 1;
							attach_on = 1;
							ATTACH_OBJECT_TO_CAR(tnt_2, car2, 0, 0, 0, -0.6, 0, 0, 0);
							REMOVE_BLIP(tnt1_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt2_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt3_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt4_ico);//������� ������ �� ������

							if (point_1 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_1, &tnt1_ico);
								CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt1_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 1"
							}
							if (point_2 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_2, &tnt2_ico);
								CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt2_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 2"
							}
							if (point_3 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_3, &tnt3_ico);
								CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt3_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 3"
							}
							if (point_4 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_4, &tnt4_ico);
								CHANGE_BLIP_SPRITE(tnt4_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt4_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt4_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt4_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 4"
							}
						}
						else if ((IS_VEHICLE_TOUCHING_OBJECT(car2, tnt_3)) && (attach_on == 0) && (tnt3_on == 0))
						{
							timer_on = 1;
							attach_3 = 1;
							attach_on = 1;
							ATTACH_OBJECT_TO_CAR(tnt_3, car2, 0, 0, 0, -0.6, 0, 0, 0);
							REMOVE_BLIP(tnt1_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt2_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt3_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt4_ico);//������� ������ �� ������

							if (point_1 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_1, &tnt1_ico);
								CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt1_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 1"
							}
							if (point_2 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_2, &tnt2_ico);
								CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt2_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 2"
							}
							if (point_3 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_3, &tnt3_ico);
								CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt3_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 3"
							}
							if (point_4 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_4, &tnt4_ico);
								CHANGE_BLIP_SPRITE(tnt4_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt4_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt4_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt4_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 4"
							}
						}
						else if ((IS_VEHICLE_TOUCHING_OBJECT(car2, tnt_4)) && (attach_on == 0) && (tnt4_on == 0))
						{
							timer_on = 1;
							attach_4 = 1;
							attach_on = 1;
							ATTACH_OBJECT_TO_CAR(tnt_4, car2, 0, 0, 0, -0.6, 0, 0, 0);
							REMOVE_BLIP(tnt1_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt2_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt3_ico);//������� ������ �� ������
							REMOVE_BLIP(tnt4_ico);//������� ������ �� ������

							if (point_1 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_1, &tnt1_ico);
								CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt1_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 1"
							}
							if (point_2 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_2, &tnt2_ico);
								CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt2_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 2"
							}
							if (point_3 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_3, &tnt3_ico);
								CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt3_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 3"
							}
							if (point_4 == 0)
							{
								ADD_BLIP_FOR_OBJECT(barrel_4, &tnt4_ico);
								CHANGE_BLIP_SPRITE(tnt4_ico, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tnt4_ico, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
								CHANGE_BLIP_SCALE(tnt4_ico, 0.6); // ������� ������ �� ������
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt4_ico, "MO_TARGET");//������ �� ������ ��������� � ������� ����� "������� 4"
							}
						}

						if (attach_on == 1)
						{
							if (point_1 == 0)
							{
								DRAW_CHECKPOINT( 530.574, 151.342, 3.2461-0.5, 2.2, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
							}
							if (point_2 == 0)
							{
								DRAW_CHECKPOINT( 589.549, 184.972, 12.361-0.5, 2.2, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
							}
							if (point_3 == 0)
							{
								DRAW_CHECKPOINT( 521.147, 171.132, 21.556-0.5, 2.2, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
							}
							if (point_4 == 0)
							{
								DRAW_CHECKPOINT( 573.008, 149.875, 30.817-0.5, 2.2, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
							}
						}

						//============================ HUD ============================
						if (timer_on == 1)
						{
							// ������ ���
							if (fail > 2)
							{
								if (TIMERB() > 1249)
								{
									time_s -= 1;
									SETTIMERB( 0 );
								}
							}
							else
							{
								if (TIMERB() > 999)
								{
									time_s -= 1;
									SETTIMERB( 0 );
								}
							}
							if (time_s < 0)
							{
								time_m -= 1;
								time_s = 59;
							}
							time_ms = TIMERB();

							// ������
							DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
							if ((time_m == 0) && (time_s < 16))
							{
								SET_TEXT_COLOUR(235, 25, 35, 255);
								SET_TEXT_SCALE(0.156, 0.267);
								SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
								DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

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
								DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

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
						}
						// ������� ���� 
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
						DRAW_SPRITE( tnt, 0.8420625, 0.74213, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// ������ ������� ��������.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.73564852, "TEX3_11"); //TARGETS LEFT:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "CP_TIME_NOZERO", bomb_add);// 

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72787074, "OUTOF_NUM", 4);// 

						if (bomb_add == 4)
						{
							// ����� ������
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
							G_AVERY = 99; // ��������� ��� ������ ������� � WORLD.sco

							//------------ �������� ----------------
							START_CUTSCENE_NOW("destr1");
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

							// ��������� ��������
							SET_CAR_COORDINATES(car3, 615.205, 196.6671, 2.603);
							SET_CAR_HEADING(car3, 52.868);
							SWITCH_CAR_SIREN(car3, 1);// �������� ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
							skip = 2;// ���������� ��������
							G_AVERY = 3;
							break;
						}

						// ��������� ���� �������� ����
						if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 878.152, -143.968, -21.971, 313.598, 420.586, 258.029, 0 )) && (zone == 1))
						{
							//����� ���������:
							PRINT_HELP_FOREVER("NEHELP2"); //The RC helicopter is getting too far out of range!
							zone = 0;
						}
						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 878.152, -143.968, -21.971, 313.598, 420.586, 258.029, 0 )) && (zone == 0))
						{
							CLEAR_HELP(); // ������� ����� ���������
							zone = 1;
						}

						if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) || (GET_ENGINE_HEALTH(car2) < 200) || (IS_CAR_IN_WATER(car2)))//���� ����� ������� ��� ��������� �������, ����� ������ ������
						{
							PRINT_STRING_IN_STRING("string", "TEX3_18", 5500, 1);//~r~Your RC Helicopter has been destroyed!
							EXPLODE_CAR(car2, 1, 1);
							skip = 1;// ���������� ��������
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1031.739, -296.829, -21.971, 160.737, 573.447, 386.287, 0 ))
						{
							PRINT_STRING_IN_STRING("string", "TEX3_21", 5500, 1);//~r~The RC Helicopter went out of range!
							EXPLODE_CAR(car2, 1, 1);
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
						{
							skip = 1;// ���������� ��������
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							PRINT_STRING_IN_STRING("string", "TEX3_17", 5500, 1);//~r~You ran out of time!
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							PRINT_STRING_IN_STRING("string", "TEX3_31", 5500, 1);//~r~You destroyed the TOPFUN van that contained the bombs and RC helicopter!
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);
							skip = 1;// ���������� ��������
							EXPLODE_CHAR_HEAD(GetPlayerPed());
							break;
						}
						else if(IS_CAR_DEAD(car2))
						{
							PRINT_STRING_IN_STRING("string", "TEX3_18", 5500, 1);//~r~Your RC Helicopter has been destroyed!
							skip = 1;// ���������� ��������
							break;
						}
					}
				}

				CLEAR_HELP(); // ������� ����� ���������
				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( tnt );
				REMOVE_TXD( textur1 );
				fail += 1;

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}
				if (skip == 1)
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
				}
				WARP_CHAR_INTO_CAR(GetPlayerPed(), car1);
				DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
				WAIT(100);
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0); // ��������
				SET_CHAR_VISIBLE(GetPlayerPed(), 1); // ������� �����

				if ((!IS_CHAR_DEAD(GetPlayerPed())) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
				{
					// �������� ������ ������ ���
					REQUEST_ANIMS( "ne_topfun" );//��������� ���� � ���������
					while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
					SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_in", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
					SetTime(1500);
				}
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

				REMOVE_BLIP(avery_ico);//������� ������ �� ������
				REMOVE_BLIP(tnt1_ico);//������� ������ �� ������
				REMOVE_BLIP(tnt2_ico);//������� ������ �� ������
				REMOVE_BLIP(tnt3_ico);//������� ������ �� ������
				REMOVE_BLIP(tnt4_ico);//������� ������ �� ������

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������
				
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������

				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(dynamite_1);//��������� ������

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
				
				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)

				// ������� �������
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);
				DELETE_OBJECT(&barrel_3);
				DELETE_OBJECT(&barrel_4);

				DELETE_OBJECT(&tnt_1);
				DELETE_OBJECT(&tnt_2);
				DELETE_OBJECT(&tnt_3);
				DELETE_OBJECT(&tnt_4);

				// ��������� �����
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_4);

				// ��������� �������
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_4);

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
					G_AVERY = 3;
					sutosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== Two Bit Hit ======================================
		else if ((G_ONMISSION == 0) && (G_AVERY == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(691.139, 300.702, 4.845, &avery_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(avery_ico, BLIP_FAUSTIN);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(avery_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "LG_02");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 691.139, 300.702, 4.845, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 691.139, 300.702, 4.845, &PlayR);//�������� "����� �� �����������"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(avery_ico);//������� ������ �� ������
				skip = 0; // ���������� ��������

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 691.139, 300.702, 4.845);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 65.0);
				
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 55);//������������� �����
				SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				
				//------------ �������� ----------------
				LOAD_ADDITIONAL_TEXT( "TEX_2", 6 ); // ��������� �������� �� *.GTX
				START_CUTSCENE_NOW("tex_2");
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

				RELEASE_WEATHER();
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
				ADD_BLIP_FOR_COORD(-588.894, 104.258, 4.781, &avery_ico);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(avery_ico, BLIP_CLOTHES_SHOP);//�������� ������ �� ������
				CHANGE_BLIP_COLOUR(avery_ico, 0);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(avery_ico, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "NE_SHOP");//������ �� ������ ��������� � ������� ����� "������� ������"
				PRINT_STRING_IN_STRING("string", "TEX_2C", 5000, 1);//~g~Go get yourself some Cuban gang colors in Little Havana!

				Car car1, car2, car3, car4, car5;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15;
				Object grob;
				Cam camera, camera2, camera3;
				car_on = 0;
				bomb_add = 0;
				open_d = 0;

				uint PedM1 = MODEL_M_Y_GJAM_LO_01;// ��������1
				uint PedM2 = MODEL_M_Y_GJAM_LO_02;// ��������2
				uint CarM1 = MODEL_ROMERO;// ��������
				uint CarM2 = MODEL_VOODOO;// ����
				uint ObjM1 = jw_coffin;// ����

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(PedM1);// ��������1
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM2);// ��������2
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(ObjM1);// ����
				while (!HAS_MODEL_LOADED(ObjM1)) WAIT(0);

				// ������ ���������
				CREATE_CAR(CarM1, 286.232, -791.79, 4.445, &car1, TRUE);
				CREATE_CAR(CarM1, 289.629, -791.79, 4.445, &car2, TRUE);
				CREATE_CAR(CarM2, 293.025, -791.79, 4.445, &car3, TRUE);
				CREATE_CAR(CarM2, 296.422, -791.79, 4.445, &car4, TRUE);
				CREATE_CAR(CarM2, 299.905, -791.79, 4.445, &car5, TRUE);

				// ������ ���������
				CHANGE_CAR_COLOUR( car1, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 133, 133 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car2, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car2, 133, 133 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car3, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car3, 133, 133 );//���� ��������� ������
				TURN_OFF_VEHICLE_EXTRA(car1, 1, 0);
				TURN_OFF_VEHICLE_EXTRA(car1, 2, 1);
				TURN_OFF_VEHICLE_EXTRA(car1, 3, 1);

				// ������ ������� �����
				CREATE_CHAR (26, PedM1, 286.386, -785.672, 5.06, &ped1, TRUE);// Boss
				CREATE_CHAR (26, PedM2, 289.619, -785.672, 5.06, &ped2, TRUE);// ��������
				CREATE_CHAR (26, PedM1, 292.961, -785.672, 5.06, &ped3, TRUE);// ��������
				CREATE_CHAR (26, PedM2, 296.473, -785.672, 5.06, &ped4, TRUE);// ��������
				CREATE_CHAR (26, PedM1, 299.976, -785.672, 5.06, &ped5, TRUE);// ��������
				CREATE_CHAR (26, PedM2, 286.386, -783.209, 5.06, &ped6, TRUE);// ��������
				CREATE_CHAR (26, PedM1, 289.619, -783.209, 5.06, &ped7, TRUE);// ��������
				CREATE_CHAR (26, PedM1, 292.961, -783.209, 5.06, &ped8, TRUE);// ��������
				CREATE_CHAR (26, PedM1, 296.473, -783.209, 5.06, &ped9, TRUE);// ��������
				CREATE_CHAR (26, PedM1, 299.976, -783.209, 5.06, &ped10, TRUE);// ��������

				// ������ ����� � �������
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM2, &ped11);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped12);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM2, &ped13);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM1, &ped14);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM2, &ped15);//������ ���� �� ���� ����������

				// ������ ����
				CREATE_OBJECT_NO_OFFSET(ObjM1, 290.424, -798.9435, 5.445457, &grob, TRUE);

				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -588.894, 104.258, 4.781, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -588.894, 104.258, 4.781, &PlayR);//�������� "����� �� �����������"
					if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						WAIT(0);
						REMOVE_BLIP(avery_ico);//������� ������ �� ������
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

						// ������ ������
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -590.879, 104.026, 4.616 ); // ���� ������� ������
						SET_CAM_POS			( camera, -577.948, 106.167, 15.366 );//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -591.203, 103.965, 5.835, 2, -2);// ����� ��� � �����
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
						SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 4, 0); // ����������� ������
						SET_CHAR_COORDINATES(GetPlayerPed(), -589.702, 104.208, 5.52);// ���������� ������
						SET_CHAR_HEADING(GetPlayerPed(), -80.0);
						SetTime(200);
						DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������

						// ���� ������
						CREATE_CAM( 3, &camera2 );
						CREATE_CAM( 14, &camera3 );
						POINT_CAM_AT_COORD	( camera, -589.481, 104.356, 4.981 ); // ���� ������� ������
						SET_CAM_POS			( camera, -587.677, 104.457, 5.501 );//������������ ������
						POINT_CAM_AT_COORD	( camera3, -589.481, 104.356, 6.258 ); // ���� ������� ������
						SET_CAM_POS			( camera3, -587.677, 104.457, 5.501 );//������������ ������
						SET_CAM_INTERP_STYLE_CORE( camera2, camera, camera3, 3500, 0 ); //����������� ������ �� ������ �� ����� ��������� � ����������� "SET_CAM_POS(camera, X, Y, Z)" 
						SET_CAM_ACTIVE( camera2, 1 );
						SET_CAM_PROPAGATE( camera2, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SetTime(3000);

						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						DESTROY_CAM( camera2 );
						DESTROY_CAM( camera3 );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
						PRINT_STRING_IN_STRING("string", "TEX_2D", 5000, 1);//~g~Take out the Haitian Gang Lord at Romero's Funeral Parlor!

						// ������ ��� �����.
						ADD_BLIP_FOR_CHAR(ped1, &avery_ico);
						CHANGE_BLIP_SPRITE(avery_ico, BLIP_OBJECTIVE);//�������� ������ �� ������
						CHANGE_BLIP_COLOUR(avery_ico, 19);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(avery_ico, "MO_TARGET");//������ �� ������ "�������"
						CHANGE_BLIP_SCALE(avery_ico, 0.6); // ������� ������ �� ������

						// ����������� �����
						SET_CHAR_COORDINATES(ped1, -613.901, 604.96, 5.56);// ���������� ����
						SET_CHAR_HEADING(ped1, 135.0);
						SET_CHAR_COORDINATES(ped2, -615.041, 604.266, 5.56);// ���������� ����
						SET_CHAR_HEADING(ped2, -95.0);
						SET_CHAR_COORDINATES(ped3, -613.901, 603.896, 5.56);// ���������� ����
						SET_CHAR_HEADING(ped3, 30.0);
						SET_CHAR_COORDINATES(ped4, -604.7, 603.0, 5.56);// ���������� ����
						SET_CHAR_HEADING(ped4, 70.0);
						SET_CHAR_COORDINATES(ped5, -631.556, 588.759, 5.56);// ���������� ����
						SET_CHAR_HEADING(ped5, 95.0);
						SET_CHAR_COORDINATES(ped6, -631.504, 573.032, 5.56);// ���������� ����
						SET_CHAR_HEADING(ped6, 95.0);
						SET_CHAR_COORDINATES(ped7, -623.0, 585.0, 6.219);// ���������� ����
						SET_CHAR_HEADING(ped7, 95.0);
						SET_CHAR_COORDINATES(ped8, -622.0, 559.0, 6.219);// ���������� ����
						SET_CHAR_HEADING(ped8, 95.0);
						SET_CHAR_COORDINATES(ped9, -609.44, 597.96, 10.823);// ���������� ����
						SET_CHAR_HEADING(ped9, 70.0);
						SET_CHAR_COORDINATES(ped10, -614.8, 587.8, 8.829);// ���������� ����
						SET_CHAR_HEADING(ped10, 105.0);

						// ���������� ���������
						SET_CAR_COORDINATES(car1, -626.0, 602.64, 5.785);
						SET_CAR_HEADING(car1, 90.0);
						SET_CAR_COORDINATES(car2, -630.0, 588.0, 5.785);
						SET_CAR_HEADING(car2, 180.0);
						SET_CAR_COORDINATES(car3, -630.0, 573.0, 5.785);
						SET_CAR_HEADING(car3, 180.0);
						SET_CAR_COORDINATES(car4, -637.0, 608.4, 5.785);
						SET_CAR_HEADING(car4, -90.0);
						SET_CAR_COORDINATES(car5, -637.0, 551.6, 5.785);
						SET_CAR_HEADING(car5, -90.0);

						// ��������� �����
						UpdateWeaponOfPed(ped2, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_PISTOL, TRUE);
						UpdateWeaponOfPed(ped3, WEAPON_MICRO_UZI);
						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MICRO_UZI, TRUE);
						UpdateWeaponOfPed(ped4, WEAPON_MICRO_UZI);
						SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MICRO_UZI, TRUE);
						UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);
						UpdateWeaponOfPed(ped6, WEAPON_MICRO_UZI);
						SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MICRO_UZI, TRUE);
						UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
						UpdateWeaponOfPed(ped8, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_PISTOL, TRUE);
						UpdateWeaponOfPed(ped9, WEAPON_AK47);
						SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_AK47, TRUE);
						UpdateWeaponOfPed(ped10, WEAPON_AK47);
						SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_AK47, TRUE);

						UpdateWeaponOfPed(ped12, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped13, WEAPON_MICRO_UZI);
						UpdateWeaponOfPed(ped14, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped15, WEAPON_MICRO_UZI);

						// ����� �����
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);

						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_CHAR_RELATIONSHIP(ped8, 5, 0);
						SET_CHAR_RELATIONSHIP(ped9, 5, 0);
						SET_CHAR_RELATIONSHIP(ped10, 5, 0);
						SET_CHAR_RELATIONSHIP(ped12, 5, 0);
						SET_CHAR_RELATIONSHIP(ped13, 5, 0);
						SET_CHAR_RELATIONSHIP(ped14, 5, 0);
						SET_CHAR_RELATIONSHIP(ped15, 5, 0);

						SET_SENSE_RANGE(ped2, 30.0);
						SET_SENSE_RANGE(ped3, 30.0);
						SET_SENSE_RANGE(ped4, 25.0);
						SET_SENSE_RANGE(ped5, 25.0);
						SET_SENSE_RANGE(ped6, 25.0);
						SET_SENSE_RANGE(ped7, 25.0);
						SET_SENSE_RANGE(ped8, 25.0);
						SET_SENSE_RANGE(ped9, 25.0);
						SET_SENSE_RANGE(ped10, 25.0);
						SET_SENSE_RANGE(ped12, 25.0);
						SET_SENSE_RANGE(ped13, 25.0);
						SET_SENSE_RANGE(ped14, 35.0);
						SET_SENSE_RANGE(ped15, 35.0);

						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_COVER(ped7, 1);
						SET_CHAR_WILL_USE_COVER(ped8, 1);
						SET_CHAR_WILL_USE_COVER(ped9, 1);
						SET_CHAR_WILL_USE_COVER(ped10, 1);
						SET_CHAR_WILL_USE_COVER(ped12, 1);
						SET_CHAR_WILL_USE_COVER(ped13, 1);
						SET_CHAR_WILL_USE_COVER(ped14, 1);
						SET_CHAR_WILL_USE_COVER(ped15, 1);

						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);
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
					while (TRUE)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped1))//���� ��� ����
						{
							skip = 1;// ���������� ��������
							PRINT_STRING_IN_STRING("string", "TEX_2B", 5000, 1);//~r~Fool! People have to WITNESS a Cuban doing the hit!
							break;
						}
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -590.0, 532.0, 2.0, -657.0, 628.0, 30.0, 0 ))
						{
							PRINT_STRING_IN_STRING("string", "TEX_2A", 5000, 1);//~g~Excellent! They've spotted you!
							SetTime(500);
							if ((!IS_CHAR_DEAD(ped11)) && (!IS_CAR_DEAD(car1)))
							{
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);// ���� ������� � ��������
								car_on = 0;
							}
							else
							{
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -609.938, 615.959, 5.56, 3, -1, 2.5);
								car_on = 2;
								UpdateWeaponOfPed(ped1, WEAPON_M4);
								SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_M4, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
								SET_CHAR_RELATIONSHIP(ped1, 5, 0);
								SET_SENSE_RANGE(ped1, 10.0);
								SET_CHAR_WILL_USE_COVER(ped1, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 0);
							}
							break;
						}
					}
				}
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ((IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (car_on == 0))
						{
							CLEAR_AREA(-630.226,603.881,5.18665, 45.0, 1);//������� ���� ��������
							WAIT(100);
							TASK_CAR_DRIVE_WANDER(ped11, car1, 40.0, 2);
							APPLY_FORCE_TO_OBJECT(grob, 1, 0.0, -8.5, 1.0, 0, 0, 0, 1, 1, 1, 1);
							car_on = 1;
						}

						if ((car_on == 1) && (!IS_CHAR_DEAD(ped1)) && (!IS_CAR_DEAD(car1)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped1)))
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							GET_CHAR_HEADING(ped1, &PedR); //�������� ���� �������� ������
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
							if (PlayR > 200.3)
							{
								PRINT_STRING_IN_STRING("string", "TEX1_5", 5000, 1);//~r~He got away!
								skip = 1;// ���������� ��������
								break;
							}

							grob_x = (0*COS((0-PedR))+(-20*SIN((0-PedR))))+PedX;
							grob_y = (-20*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
							//DRAW_CHECKPOINT( grob_x, grob_y, PedZ, 4.0, 160, 116, 209);//�������� �������� �� ����������� � ��� ����

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, grob_x, grob_y, PedZ, &grob_r);//�������� "����� �� �����������"
							if (grob_r < 4)
							{
								if (open_d == 0)
								{
									OPEN_CAR_DOOR(car1, 5);// ��������� ��������
									open_d = 1;
									SETTIMERB(4500);
								}
								// ����������� ����
								if (TIMERB() > 5000)
								{
									bomb_add = 0;
									SET_OBJECT_COORDINATES(grob, (0*COS((0-PedR))+(-3*SIN((0-PedR))))+PedX, (-3*COS((0-PedR))-(0*SIN((0-PedR))))+PedY, PedZ-20);
									WAIT(1);
									SET_OBJECT_COORDINATES(grob, (0*COS((0-PedR))+(-3*SIN((0-PedR))))+PedX, (-3*COS((0-PedR))-(0*SIN((0-PedR))))+PedY, PedZ+1);
									SET_OBJECT_HEADING(grob, PedR);
									APPLY_FORCE_TO_OBJECT(grob, 1, 0.0, -8.5, 1.0, 0, 0, 0, 1, 1, 1, 1);
									SETTIMERB(0);
								}
							}

							if ((IS_CHAR_TOUCHING_OBJECT(GetPlayerPed(), grob)) && (bomb_add == 0))
							{
								bomb_add = 1;
								GET_OBJECT_COORDINATES(grob, &PedX, &PedY, &PedZ);
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 0.025, 1, 0, 1.00000000 );
							}
						}
						if (IS_CHAR_DEAD(ped1))// �������� ����� ���� ����
						{
							REMOVE_BLIP(avery_ico);//������� ������ �� ������
							if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -209.925, 216.375, -35.491, -917.502, 952.896, 150.0, 0 ))
							{
								PRINT_STRING_IN_STRING("string", "TEXEXIT", 5000, 1);//~g~Now get out of Little Haiti!
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
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -209.925, 216.375, -35.491, -917.502, 952.896, 150.0, 0 ))
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


				REMOVE_BLIP(avery_ico);//������� ������ �� ������

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(ObjM1);//��������� ������

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

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)

				// ������� �������
				DELETE_OBJECT(&grob);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&grob);

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
					PRINT_HELP("CLOTH5"); //Havana outfit delivered to Little Havana Streetwear in Little Havana.
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 2500);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +2500 );//��� ������ �����
					G_AVERY = 5;
					sutosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_AVERY == 5))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(avery_ico);//������� ������ �� ������
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_AVERY < 5)
	{
		boyarsky();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
