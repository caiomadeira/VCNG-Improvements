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
						(GetPlayerPed(), 1, 4, 0); // ����������� ������
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
