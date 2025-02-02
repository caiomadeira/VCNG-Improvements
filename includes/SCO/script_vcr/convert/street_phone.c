/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedX2, PedY2, PedZ2, PedR, blip_on, sound_load, volume, textur, Pizza_N, skip, Text, Text2, in_car, set_cam, kill, sutosave;
float carHUD_x, carHUD_w, carHUD_y1, carHUD_y2, carHUD_y3, carH1, carH2, carH3, touch_car, sound, time_m, time_s, time_ms, stage;

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
void SetTime2(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		if (TIMERA() > time)
		{
			break;
		}
		else if (IS_GAME_KEYBOARD_KEY_PRESSED(57))// ���� ������ "SPACE" ������������ �������� 
		{
			Text = 1;
			break;
		}
		else if (IS_GAME_KEYBOARD_KEY_PRESSED(28))// ���� ������ "ENTERC" ������������ ��������*/
		{
			Text = 1;
			break;
		}
		else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
		{
			Text = 1;
			break;
		}
		WAIT(0);
	}
}
void telephone(void)
{
	blip_on = 0;
	sutosave = 0;
	uint AudID;
	Blip phone, phone2;

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
//============================== Road Kill ======================================
		if ((G_ONMISSION == 0) && (G_ASSASSIN == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(470.635, -490.757, 5.01, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_UNKNOWN_CONTACT);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(phone, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "LG_25");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			//=============== ���� ������ =============== 
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 470.635+20, -490.757+20, 5.01-5, 470.635-20, -490.757-20, 5.01+10, 0 )) && (sound_load == 0))// �������� ����� � ���� �������� ����� �������� �������� � �� �� ������ � �������� ������ "��������� � �������� � ��������� ������".
			{
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/PHONERING" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_PHONERING_STREETR1", 470.635, -490.757, 5.01);
				CLEAR_AREA(470.635, -490.757, 5.01, 3.0, 1);//������� ���� ��������
				sound_load = 1;
			}
			else if (((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 470.635+20, -490.757+20, 5.01-5, 470.635-20, -490.757-20, 5.01+10, 0 )) && (sound_load == 1)))// ���� ����� �� � ���� ��������� ����
			{
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
			}
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 470.635, -490.757, 5.01, &PlayR);//�������� "����� �� �����������"
			DRAW_CHECKPOINT( 470.635, -490.757, 4.51, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(phone);//������� ������ �� ������
				blip_on = 0;

				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;

				Ped ped1;
				Car car1;
				Cam camera;
				Object PIZZA_1, trubka_1;
				Texture fon, pizz;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				pizz = GET_TEXTURE( textur, "pizza_hud" );

				// �������� ��������� �� ��������
				uint PedM1 = MODEL_M_Y_FF_WSPIZZA_R;// ��������� �����
				uint CarM1 = MODEL_HELLFURY;//���������� "Car2" = ������ ������
				uint ObjM1 = pizza_box_1; // ������� �����
				uint trubka = cj_handset_one;
				uint time_r;
				uint Ped_hp;

				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, 1.1, &trubka_1, TRUE);
				ATTACH_OBJECT_TO_PED( trubka_1, GetPlayerPed(), 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	

				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
					{
						break;
					}
					WAIT( 0 );
				}

				CLEAR_AREA(470.635, -490.757, 4.51, 2.0, 1);//������� ���� ��������
				SET_WIDESCREEN_BORDERS( 1 );
				SET_CHAR_COORDINATES(GetPlayerPed(), 470.635, -490.757, 5.422);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 0.1);
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 470.667, -490.582, 5.321 ); // ���� ������� ������
				SET_CAM_POS			( camera, 467.434, -493.182, 7.424);//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SetTime(800);

				REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
				SetTime(1000);

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TB", "ASM1_D", 0, 0);//Mr. Teal, your help in eradicating those out-of-towners was invaluable to business.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TC", "ASM1_C", 0, 0);//I have more work for you with a more 'hands-on' approach
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TD", "ASM1_B", 0, 0);//Your next job is taped under the phone.
				START_SCRIPT_CONVERSATION(1, 1);
				SetTime(2000);
				SetSpeech();

				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SetTime(1000);

				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "put_down_phone", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
				SetTime(1000);
				DETACH_OBJECT( trubka_1, 1 );
				DELETE_OBJECT( &trubka_1 );
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);
				SetTime(1000);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������
				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "ASM1_7", 5000, 1);//~g~Carl Pearson, Pizza Delivery Man. Kill him before he completes his deliveries.

				// ��������� ������ ����
				REQUEST_MODEL(PedM1);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ��������� ������ ����������
				REQUEST_MODEL(CarM1);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM1));//�������� "������ �����������" ���� ��� �� �������� � ������

				// ��������� ������ �����
				REQUEST_MODEL(ObjM1);
				while (!HAS_MODEL_LOADED(ObjM1)) WAIT(0);

				// ������ ��������� 
				CREATE_CAR(CarM1, 462.71, -942.87, 5.27, &car1, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car1, 267.0);//������ �������� ������
				CHANGE_CAR_COLOUR( car1, 28, 127 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 127, 127 );//���� ��������� ������
				//TURN_OFF_VEHICLE_EXTRA( car1, 9, 0 );//���������� ������� ��� "PIZZABOY"

				// ������ ���� � ����������
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//������ ���� �� ���� ����������
				TASK_CAR_DRIVE_WANDER(ped1, car1, 20.0, 2);// ��� ���� ����-��

				// ������ ������ �����
				CREATE_OBJECT_NO_OFFSET(ObjM1, PlayX+1, PlayY+1, PlayZ-5, &PIZZA_1, TRUE);
				SET_OBJECT_HEADING(PIZZA_1, 80);

				ADD_BLIP_FOR_CHAR(ped1, &phone);
				CHANGE_BLIP_SPRITE(phone, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
				CHANGE_BLIP_SCALE(phone, 0.77999990); // ������� ������ �� ������
				Pizza_N = 25;
				skip = 0;
				Text = 0;
				in_car = 0;
				time_r = 4500;

				while(true)
				{
					WAIT(0);
					GET_CHAR_HEALTH(ped1, &Ped_hp);

					// ���
					DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
					DRAW_SPRITE( pizz, 0.8555625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// ������ ������� ��������.

					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.156, 0.267);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					DISPLAY_TEXT(0.79909167, 0.80277778, "ASM1_6"); //DELIVERIES LEFT:

					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.26, 0.445);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					SET_TEXT_CENTRE(1);
					if ( Pizza_N >= 10 )
					{
						DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_NOZERO", Pizza_N);
					}
					else
					{
						DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_ZERO", Pizza_N);
					}

					if (IS_CHAR_SITTING_IN_ANY_CAR( ped1 ))
					{
						if (TIMERA() > time_r)
						{
							GET_CHAR_COORDINATES(ped1,  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
							GET_CHAR_HEADING(ped1, &PlayR); //�������� ���� �������� ������
							SET_OBJECT_COORDINATES(PIZZA_1, (1*COS((0-PlayR))+0*SIN((0-PlayR)))+PlayX, (0*COS((0-PlayR))-(1*SIN((0-PlayR))))+PlayY, PlayZ);
							SET_OBJECT_HEADING(PIZZA_1, PlayR);
							APPLY_FORCE_TO_OBJECT(PIZZA_1, 1, 5.5, 0, 1.0, 0, 0, 0, 1, 1, 1, 1);
							GENERATE_RANDOM_INT_IN_RANGE( 6500, 15000, &time_r);
							SETTIMERA(0);
							Pizza_N -= 1;
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
						}
					}
					else
					{
						if ((!IS_CAR_DEAD(car1)) && (in_car == 0))
						{
							in_car = 1;
							SETTIMERA(0);
							TASK_CAR_DRIVE_WANDER(ped1, car1, 20.0, 2);// ��� ���� ����-��
							SETTIMERB(0);
						}
						if ((in_car == 1) && (TIMERB() > 8000))
						{
							SETTIMERA(0);
							in_car = 0;
						}
					}

					// �������� ����� �����
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
					else if (IS_CHAR_DEAD(ped1))
					{
						skip = 2;// ���������� ��������
						break;
					}
					if (Pizza_N == 0) 
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "ASM1_5", 5000, 1);//~r~Your target completed his deliveries!
						skip = 1;// ���������� ��������
						break;
					}
					if ((Ped_hp < 120) && (Text == 0))
					{
						Text = 1;
						EXPLODE_CHAR_HEAD(ped1);
					}	
				}

				REMOVE_BLIP(phone);//������� ������ �� ������

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( pizz );
				REMOVE_TXD( textur );

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(ObjM1);//��������� ������

				// ��������� ����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)

				// ������� �����
				DELETE_OBJECT(&PIZZA_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&PIZZA_1);

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
					G_ASSASSIN = 2;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}

//============================== Waste the Wife ======================================
		else if ((G_ONMISSION == 0) && (G_ASSASSIN == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(915.516, 777.734, 5.019, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_UNKNOWN_CONTACT);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(phone, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "LG_25");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			//=============== ���� ������ =============== 
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 915.516+20, 777.734+20, 5.019-5, 915.516-20, 777.734-20, 5.019+10, 0 )) && (sound_load == 0))// �������� ����� � ���� �������� ����� �������� �������� � �� �� ������ � �������� ������ "��������� � �������� � ��������� ������".
			{
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/PHONERING" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_PHONERING_STREETR1", 915.516, 777.734, 5.019);
				
				CLEAR_AREA(915.516, 777.734, 5.019, 3.0, 1);//������� ���� ��������
				sound_load = 1;
			}
			else if (((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 915.516+20, 777.734+20, 5.019-5, 915.516-20, 777.734-20, 5.019+10, 0 )) && (sound_load == 1)))// ���� ����� �� � ���� ��������� ����
			{
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
			}
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 915.516, 777.734, 5.019, &PlayR);//�������� "����� �� �����������"
			DRAW_CHECKPOINT( 915.516, 777.734, 5.019, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(phone);//������� ������ �� ������
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
				blip_on = 0;
				skip = 0;
				set_cam = 0;
				Text = 0;
				touch_car = 0;

				Ped ped1;
				Car car1;
				Cam camera;
				Object trubka_1;
				Texture fon, car;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				car = GET_TEXTURE( textur, "car_hud" );

				// �������� ��������� �� ��������
				uint PedM1 = MODEL_F_Y_PVILLBO_02;// ���
				uint CarM1 = MODEL_COMET;//���������� "Car2" = ������ ������
				uint trubka = cj_handset_one;
				uint car_HP, cry_ped, PTFX, PTFX2;

				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, 1.1, &trubka_1, TRUE);
				ATTACH_OBJECT_TO_PED( trubka_1, GetPlayerPed(), 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	

				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
					{
						break;
					}
					WAIT( 0 );
				}

				CLEAR_AREA(915.516, 777.734, 5.019, 2.0, 1);//������� ���� ��������
				SET_WIDESCREEN_BORDERS( 1 );
				SET_CHAR_COORDINATES(GetPlayerPed(), 915.516, 777.734, 6.05);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 0.1);
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 915.481, 778.163, 6.069 ); // ���� ������� ������
				SET_CAM_POS			( camera, 916.806, 776.096, 7.036);//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SetTime(800);

				REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
				SetTime(1000);

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_TE", "ASM2_A", 0, 0);//My compliments on a job well done Mr. Teal. My client was very pleased.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TC", "ASM1_C", 0, 0);//I have more work for you with a more 'hands-on' approach
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TD", "ASM1_B", 0, 0);//Your next job is taped under the phone.
				START_SCRIPT_CONVERSATION(1, 1);
				SetTime(2000);
				SetSpeech();

				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SetTime(1000);

				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "put_down_phone", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
				SetTime(1000);
				DETACH_OBJECT( trubka_1, 1 );
				DELETE_OBJECT( &trubka_1 );
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);
				SetTime(1000);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "ASM2_1", 5000, 1);//~g~Mrs. Dawson will be leaving the Jewelry shop in Vice Point soon. Kill her. It must look like a car accident.

				// ��������� ������ ����
				REQUEST_MODEL(PedM1);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				// ��������� ������ ����������
				REQUEST_MODEL(CarM1);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM1));//�������� "������ �����������" ���� ��� �� �������� � ������

				// ������ ��������� 
				CREATE_CAR(CarM1, 299.905, -791.79, 5.445, &car1, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				CHANGE_CAR_COLOUR( car1, 132, 132 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 29, 29 );//���� ��������� ������

				// ������ ����
				CREATE_CHAR (26, PedM1, 299.976, -785.672, 5.06, &ped1, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������

				ADD_BLIP_FOR_COORD(836.844, 756.51, 4.62, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "NE_POINT");//������ �� ������ ��������� � ������� ����� "������ ������"

				while(true)
				{
					WAIT(0);
					DRAW_CHECKPOINT(836.844, 756.51, 4.62, 3.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 836.844, 756.51, 4.62, &PlayR);//�������� "����� �� �����������"
					if (PlayR < 3.3)
					{
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							REMOVE_BLIP(phone);//������� ������ �� ������

							// ���������� ���������
							SET_CAR_COORDINATES(car1, 826.905, 735.995, 5.582);
							SET_CAR_HEADING(car1, 180.0);//������ �������� ������

							// ���������� ����
							SET_CHAR_COORDINATES(ped1, 820.497, 735.714, 6.039);// ���������� ������
							SET_CHAR_HEADING(ped1, -95.0);
							
							// ������ ������
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	
							SET_WIDESCREEN_BORDERS( 1 );
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 836.844, 756.511, 5.244 ); // ���� ������� ������
							SET_CAM_POS			( camera, 830.751, 748.454, 9.852);//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV(camera, 45.0);

							SetTime(1500);
							TASK_GO_STRAIGHT_TO_COORD(ped1, 825.357, 735.97, 5.004, 2, -2);// ��� ��� � ������

							//��� ������ 2
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM2_8", 5000, 1);//~g~You must make Mrs. Dawson's death look like an accident. Do not use any weapons.

							POINT_CAM_AT_COORD	( camera, 820.785, 735.709, 6.24 ); // ���� ������� ������
							SET_CAM_POS			( camera, 812.698, 736.287, 5.794);//������������ ������
							SETTIMERA(0);
							
							while (TRUE)
							{
								WAIT(0);
								GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
								GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 825.357, 735.97, 5.004, &PedR);//�������� "����� �� �����������"
								if ( PedR < 1.3)
								{
									TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, 10000, 3);
									break;
								}
								if ((TIMERA() > 2500) && (set_cam == 0))
								{
									//��� ������ 3
									set_cam = 1;
									POINT_CAM_AT_COORD	( camera, 824.363, 733.846, 5.657 ); // ���� ������� ������
									SET_CAM_POS			( camera, 825.713, 743.068, 7.798);//������������ ������
								}
								else if ((TIMERA() > 7000) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
								{
									WARP_CHAR_INTO_CAR(ped1, car1);
									break;
								}
							}

							SetTime(3500);
							WARP_CHAR_INTO_CAR(ped1, car1);// ��������� ���� �� ����
							TASK_CAR_DRIVE_WANDER(ped1, car1, 20.0, 2);// ��� ���� ����-��
							LOCK_CAR_DOORS(car1, 3); //��������� ����� ���������� ��� ������

							//��� ������ 4
							POINT_CAM_AT_COORD	( camera, 826.621, 732.738, 6.511 ); // ���� ������� ������
							SET_CAM_POS			( camera, 828.651, 749.299, 7.186);//������������ ������

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM2_10", 5000, 1);//~g~When her car bursts into flames make your self scarce!

							SetTime(3500);
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������

							ADD_BLIP_FOR_CHAR(ped1, &phone);
							CHANGE_BLIP_SPRITE(phone, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 19);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
							CHANGE_BLIP_SCALE(phone, 0.77999990); // ������� ������ �� ������
							Text = 0;
							break;
						}
						else
						{
							if (Text == 0)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "ASM2_9", 5000, 1);//~g~You need some wheels for this job!
								Text = 1;
							}

						}
					}
					else
					{
						if (Text == 1)
						{
							Text = 0;
						}
					}
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
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
						// ------------------- HUD -------------------
						GET_CAR_HEALTH(car1, &car_HP);
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
						DRAW_SPRITE( car, 0.8765625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// ������ ������� ��������.
						DRAW_SPRITE( 0, 0.8421875, 0.80925926, 0.0739583, 0.014, 0.0, 27, 89, 130, 255 );// ������ ������� ��������.
						carHUD_x = 0.8421875;
						carHUD_w = 0.0739583;

						if (car_HP < 5)
						{
							carH1 = 0;
						}
						else
						{
							carH1 = car_HP;
						}
						carH2 = carHUD_w/1000;
						carH3 = carH2*carH1;
						carHUD_y1 = carHUD_w-carH3;
						carHUD_y2 = carHUD_y1/2;
						carHUD_y3 = carHUD_x-carHUD_y2;
						DRAW_SPRITE( 0, carHUD_y3, 0.80925926, carH3, 0.014, 0.0, 97, 194, 247, 255 );// ������ ������� ��������.

						// ------------------------- ������� --------------------------------
						if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car1))) // ���� ����� ��������� ������ ���������
						{
							if (touch_car == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_WA", "ASM2_13", 0, 0);//Oh my god!
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB(0);
								touch_car = 1;
								TASK_CAR_DRIVE_WANDER(ped1, car1, 60.0, 2);// ��� ���� ����-��
								GET_CAR_HEALTH(car1, &car_HP);
								car_HP -=50;
								SET_CAR_HEALTH(car1, car_HP);
								Text = 1;
							}
							else if (touch_car == 1)
							{
								if (TIMERB() > 8000)
								{
									SETTIMERB(0);
									GENERATE_RANDOM_INT_IN_RANGE( 1, 10, &cry_ped);
									if ((cry_ped == 1) || (cry_ped == 6))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_TF", "ASM2_11", 0, 0);//Help me!
										START_SCRIPT_CONVERSATION(1, 1);
										GET_CAR_HEALTH(car1, &car_HP);
										car_HP -=20;
										SET_CAR_HEALTH(car1, car_HP);
										Text = 1;
									}
									else if ((cry_ped == 2) || (cry_ped == 7))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R4_WA", "ASM2_13", 0, 0);//Oh my god!
										START_SCRIPT_CONVERSATION(1, 1);
										GET_CAR_HEALTH(car1, &car_HP);
										car_HP -=50;
										SET_CAR_HEALTH(car1, car_HP);
										Text = 1;
									}
									else if ((cry_ped == 3) || (cry_ped == 8))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R4_TG", "ASM2_12", 0, 0);// Somebody help me!
										START_SCRIPT_CONVERSATION(1, 1);
										GET_CAR_HEALTH(car1, &car_HP);
										car_HP -=80;
										SET_CAR_HEALTH(car1, car_HP);
										Text = 1;
									}
									else if ((cry_ped == 4) || (cry_ped == 9))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R4_WA", "ASM2_13", 0, 0);//Oh my god!
										START_SCRIPT_CONVERSATION(1, 1);
										GET_CAR_HEALTH(car1, &car_HP);
										car_HP -=100;
										SET_CAR_HEALTH(car1, car_HP);
										Text = 1;
									}
									else if ((cry_ped == 5) || (cry_ped == 10))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R4_WA", "ASM2_13", 0, 0);//Oh my god!
										START_SCRIPT_CONVERSATION(1, 1);
										GET_CAR_HEALTH(car1, &car_HP);
										car_HP -=100;
										SET_CAR_HEALTH(car1, car_HP);
										Text = 1;
									}
								}
							}
						}
						if ((TIMERB() > 2500) && (Text == 1))
						{
							Text = 0;
						}

						// ------------------------- ������ ������ -------------------------
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ���� � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if (PlayR > 200)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM2_5", 5000, 1);//~r~She got away!
							skip = 1;// ���������� ��������
							break;
						}
						else if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX-50, PedY-50, PedX+50, PedY+50, 0))//�������� ����� ����� ������ �� ������
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM2_7", 5000, 1);//~r~It's supposed to look like an accident! Try ramming her off the road instead!
							skip = 1;// ���������� ��������
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
						{
							skip = 1;// ���������� ��������
							break;
						}

						// ------------------------- ���������� ������-------------------------
						if (car_HP < 5)
						{
							//��������� ����������
							SETTIMERB(0);
							PTFX = START_PTFX_ON_VEH("fire_chopper_tail", car1, -1.035, -1.33, -0.35, 1, 1, 90, 0.36);
							PTFX2 = START_PTFX_ON_VEH("fire_chopper_tail", car1, 1.035, -1.33, -0.05, 1, 1, -90, 0.36);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM2_3", 5000, 1);//~g~She's gonna blow! Get out of there!
							break;
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped1))//����� � ������� �� ������
						{
							EXPLODE_CHAR_HEAD(ped1);
							skip = 2;// ���������� ��������
							WAIT(100);
							break;
						}
						else if (IS_CAR_IN_WATER(car1))//���� � ����
						{
							EXPLODE_CHAR_HEAD(ped1);
							skip = 2;// ���������� ��������
							WAIT(100);
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CAR_DEAD(car1)))//���� ��� ����
						{
							EXPLODE_CHAR_HEAD(ped1);
							skip = 2;// ���������� ��������
							WAIT(100);
							break;
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						ABORT_SCRIPTED_CONVERSATION( 0 );
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ���� � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if (PlayR > 80)
						{
							EXPLODE_CAR(car1, 1, 1);
							skip = 2;// ���������� ��������
							break;
						}
						else if (TIMERB() > 15000)
						{
							EXPLODE_CAR(car1, 1, 1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM2_6", 5000, 1);//~r~You were too near the scene of the 'accident'!
							skip = 1;// ���������� ��������
							break;
						}
					}
				}
				WAIT(10);
				REMOVE_BLIP(phone);//������� ������ �� ������
				ABORT_SCRIPTED_CONVERSATION( 0 );

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( car );
				REMOVE_TXD( textur );
				STOP_PTFX(PTFX);
				REMOVE_PTFX(PTFX);
				STOP_PTFX(PTFX2);
				REMOVE_PTFX(PTFX2);

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������

				// ��������� ����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)

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
					G_ASSASSIN = 4;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Autocide ======================================
		else if ((G_ONMISSION == 0) && (G_ASSASSIN == 5))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(470.635, -490.757, 5.01, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_UNKNOWN_CONTACT);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(phone, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "LG_25");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			//=============== ���� ������ =============== 
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 470.635+20, -490.757+20, 5.01-5, 470.635-20, -490.757-20, 5.01+10, 0 )) && (sound_load == 0))// �������� ����� � ���� �������� ����� �������� �������� � �� �� ������ � �������� ������ "��������� � �������� � ��������� ������".
			{
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/PHONERING" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_PHONERING_STREETR1", 470.635, -490.757, 5.01);
				CLEAR_AREA(470.635, -490.757, 5.01, 3.0, 1);//������� ���� ��������
				sound_load = 1;

			}
			else if (((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 470.635+20, -490.757+20, 5.01-5, 470.635-20, -490.757-20, 5.01+10, 0 )) && (sound_load == 1)))// ���� ����� �� � ���� ��������� ����
			{
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
			}
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 470.635, -490.757, 5.01, &PlayR);//�������� "����� �� �����������"
			DRAW_CHECKPOINT( 470.635, -490.757, 4.51, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(phone);//������� ������ �� ������
				SET_MOVIE_VOLUME(0);
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
				blip_on = 0;

				Cam camera;
				Object trubka_1;

				// �������� ��������� �� ��������
				uint trubka = cj_handset_one;
				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, 1.1, &trubka_1, TRUE);
				ATTACH_OBJECT_TO_PED( trubka_1, GetPlayerPed(), 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	

				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
					{
						break;
					}
					WAIT( 0 );
				}

				CLEAR_AREA(470.635, -490.757, 4.51, 2.0, 1);//������� ���� ��������
				SET_WIDESCREEN_BORDERS( 1 );
				SET_CHAR_COORDINATES(GetPlayerPed(), 470.635, -490.757, 5.422);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 0.1);
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 470.667, -490.582, 5.321 ); // ���� ������� ������
				SET_CAM_POS			( camera, 467.434, -493.182, 7.424);//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SetTime(800);

				REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
				SetTime(1000);


				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TH", "ASM3_C", 0, 0);//A European gang plans to hit a bank in Vice City. My employers would rather this didn't happen.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_TI", "ASM3_D", 0, 0);//Each member of the gang has a cover while they are here in Vice City. Some have menial jobs, others are on vacation.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_TJ", "ASM3_E", 0, 0);// Each target and their likely whereabouts are taped under the phone.
				START_SCRIPT_CONVERSATION(1, 1);
				SetTime(2000);
				SetSpeech();

				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SetTime(1000);


				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "put_down_phone", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
				SetTime(1000);
				DETACH_OBJECT( trubka_1, 1 );
				DELETE_OBJECT( &trubka_1 );
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);
				SetTime(1000);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "ASM3_12", 5000, 1);//~g~A selection of weapons have been left for you nearby if you require them. You have ~h~9 MINUTES ~g~to kill all members of the gang.

				Ped ped1, ped2, ped3, ped4, ped5, ped6;
				Car car1, car2, car3, car4, car5;
				Pickup sweap_1, sweap_2;
				Texture fon, timer;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint PedM1 = MODEL_M_M_PLATIN_02;// ��� � ������� 2
				uint PedM2 = MODEL_M_M_ARMOURED;// ��� � ������� 2
				uint PedM3 = MODEL_M_M_SWEEPER;// ��� � ������� 2
				uint PedM4 = MODEL_M_M_CHINATOWN_01;// ��� � ������� 2
				uint PedM5 = MODEL_IG_DARKO;// ��� � ������� 2

				uint CarM1 = MODEL_PCJ;//���������� "Car2" = ������ ������
				uint CarM2 = MODEL_STOCKADE;//���������� "Car2" = ������ ������
				uint CarM3 = MODEL_BOBCAT;//���������� "Car2" = ������ ������
				uint CarM4 = MODEL_TROPIC;//���������� "Car2" = ������ ������

				//��������� ������ �����
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

				// ��������� ������ �����
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);
				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(100);

				// ������ ���������
				CREATE_CAR(CarM1, 390.58, -506.241, 4.95, &car1, TRUE);// PCJ (�����) ��� ������
				CREATE_CAR(CarM2, 286.232, -791.79, 6.01, &car2, TRUE);// �������� ������
				CREATE_CAR(CarM3, 289.629, -791.79, 6.01, &car3, TRUE);// ������ (������ � �������� �������)
				CREATE_CAR(CarM4, -975.79, -1079.69, 1.445, &car4, TRUE);// ���� ������
				CREATE_CAR(CarM1, 293.025, -791.79, 6.01, &car5, TRUE);// PCJ �����
				SET_CAR_HEADING(car1, 90.0);


				WAIT(100);

				// ������ ���������
				CHANGE_CAR_COLOUR( car1, 133, 133 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 133, 133 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car3, 0, 29 );//���� ������
				SET_EXTRA_CAR_COLOURS( car3, 133, 133 );//���� ��������� ������

				// ������ ������� �����
				CREATE_CHAR (26, PedM1, 286.386, -785.672, 5.56, &ped1, TRUE);// ���������
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped2);// ��������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped3);// �������� �� ����
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 0, &ped4);// �������� �������� (������ - ��������)
				CREATE_CHAR (26, PedM4, 289.619, -785.672, 5.56, &ped5, TRUE);// ��� � ������������
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM5, &ped6);// // ��� "�����" (���� "��")

				// ������ ������
				CREATE_PICKUP_ROTATE(w_psg1, 3, 10, 390.897, -523.874, 4.869, 90.0, -75.0, -90.0, &sweap_1);// ���������
				CREATE_PICKUP_ROTATE(w_uzi, 3, 300, 390.041, -523.375, 4.736, 90.0, 0.0, -40.0, &sweap_2);// UZI

				// ������ ��� �������
				ADD_BLIP_FOR_COORD(390.616, -521.159, 5.01, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(phone, 3);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
				CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ ��������� � ������� ����� ""

				SETTIMERB( 0 );
				SETTIMERA( 0 );
				time_m = 9;
				time_s = 0;
				sound = 0;
				stage = 0;
				Text = 0;
				Text2 = 0;
				blip_on = 0;

				SetTime(5000);
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "You have 9 MINUTES to kill all members of the gang.", 8000, 4);// ����� "� ��� ���� 9 �����, ����� ����� ���� ������ �����."

				while(true)
				{
					WAIT(0);
					// �������������
					if (((TIMERA() > 10000) && (stage == 0)) || ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 402.893, -530.858, 3.591, 377.893, -505.858, 18.591, 0 )) && (stage == 0)))
					{
						REMOVE_BLIP(phone);//������� ������ �� ������
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "ASM3_13", 5000, 1);//~g~Mike Griffin is working on an advertising board in Washington.
						
						// ��������� ����
						SET_CHAR_COORDINATES(ped1, 380.96, -352.06, 21.45);// ���������� ����
						SET_CHAR_HEADING(ped1, 278.5);

						//�������� �� ����
						REQUEST_ANIMS( "amb@default" );
						while (!HAVE_ANIMS_LOADED( "amb@default" )) WAIT(0);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "preacher_default", "amb@default", 8.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����

						ADD_BLIP_FOR_CHAR(ped1, &phone);
						CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
						CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
						stage = 1;
					}

					// ����� 1 (������� �� ��������� ������)
					if (stage == 1)
					{
						if (IS_CHAR_DEAD(ped1))// �������� ����� ���� ����
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_14", 5000, 1);//~g~Dick Tanner is working for DBP Security in Ocean Drive.
							SET_CAR_COORDINATES_NO_OFFSET(car2, 788.357, -193.28, 5.24);// ���������� ��������
							SET_CAR_HEADING(car2, -23.71);

							REMOVE_BLIP(phone);//������� ������ �� ������
							ADD_BLIP_FOR_CHAR(ped2, &phone);
							CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
							CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							stage = 2;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
					}

					// ����� 2 (�������� ��������)
					if (stage == 2)
					{
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 40.0 )
						{
							if ((Text == 0) && (Text2 == 0))
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "ASM3_18", 5000, 1);//~g~Don't get too close to the target or he may spot you!
								Text = 1;
							}
						}
						else
						{
							if ((Text == 1) && (Text2 == 0))
							{
								Text = 0;
							}
						}

						if (( PlayR < 20.0) && (Text2 == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_19", 5000, 1);//~g~He's seen you! Waste him!
							TASK_CAR_DRIVE_WANDER(ped2, car2, 40.0, 2);// ��� ���� ����-��
							Text2 = 1;
						}

						if (IS_CHAR_DEAD(ped2))// �������� ����� ���� ����
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_15", 5000, 1);//~g~Marcus Hammond and Franco Carter are located near the Jewelry shop in Vice Point.
							SET_CAR_COORDINATES(car3, 839.6844, 743.52, 4.79);// ���������� bobcat
							SET_CAR_HEADING(car3, 52.8);

							REMOVE_BLIP(phone);//������� ������ �� ������
							ADD_BLIP_FOR_CHAR(ped3, &phone);
							CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
							CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������

							ADD_BLIP_FOR_CHAR(ped4, &phone2);
							CHANGE_BLIP_SPRITE(phone2, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone2, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone2, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
							CHANGE_BLIP_SCALE(phone2, 0.6); // ������� ������ �� ������
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							Text = 0;
							Text2 = 0;
							stage = 3;
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}

					// ����� 3 ( ����� � ���������� ��������)
					if (stage == 3)
					{
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 40.0 )
						{
							if ((Text == 0) && (Text2 == 0))
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "ASM3_18", 5000, 1);//~g~Don't get too close to the target or he may spot you!
								Text = 1;
							}
						}
						else
						{
							if ((Text == 1) && (Text2 == 0))
							{
								Text = 0;
							}
						}

						if (( PlayR < 20.0) && (Text2 == 0))
						{
							TASK_CAR_DRIVE_WANDER(ped3, car3, 40.0, 2);// ��� ���� ����-��
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_20", 5000, 1);//~g~They have seen you! Make sure you waste them both!
							// ��������� ����
							TASK_LEAVE_CAR(ped4, car3);
							UpdateWeaponOfPed(ped4, WEAPON_SHOTGUN);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_SHOTGUN, TRUE);
							SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_SENSE_RANGE(ped4, 80.0);
							SET_CHAR_WILL_USE_COVER(ped4, 1);

							Text2 = 1;
						}

						if ((IS_CHAR_DEAD(ped3)) && (IS_CHAR_DEAD(ped4)))// �������� ����� ���� ����
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_16", 5000, 1);//~g~Nick Kong is cruising off Washington Beach.

							SET_CAR_COORDINATES(car4, 469.2, -135.4, 0.79);// ���������� ����
							SET_CAR_HEADING(car4, 131.2);
							// ������ � ���� ����
							ATTACH_PED_TO_CAR( ped5, car4, 0, 0, -3.7, 2.0, 3.0, 90, 1, 1 );
							//ATTACH_PED_TO_CAR(ped5, car4, 0, 0, -3.7, 2.0, 0, 0);
							FREEZE_CHAR_POSITION(ped5, 1);

							REMOVE_BLIP(phone);//������� ������ �� ������
							REMOVE_BLIP(phone2);//������� ������ �� ������
							ADD_BLIP_FOR_CHAR(ped5, &phone);
							CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
							CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							Text = 0;
							Text2 = 0;
							stage = 4;
						}
						else if (IS_CHAR_INJURED(ped3))
						{
							EXPLODE_CHAR_HEAD(ped3);
						}
						else if (IS_CHAR_INJURED(ped4))
						{
							EXPLODE_CHAR_HEAD(ped4);
						}
						if ((blip_on == 0) && IS_CHAR_DEAD(ped3))
						{
							REMOVE_BLIP(phone);//������� ������ �� ������
							blip_on = 1;
						}
						else if ((blip_on == 0) && IS_CHAR_DEAD(ped4)) 
						{
							REMOVE_BLIP(phone2);//������� ������ �� ������
							blip_on = 1;
						}
					}

					// ����� 4 ( ��� �� ����)
					if (stage == 4)
					{
						if (IS_CHAR_DEAD(ped5))// �������� ����� ���� ����
						{
							FREEZE_CHAR_POSITION(ped5, 0);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_17", 5000, 1);//~g~Charlie Dilson is riding in Washington.

							SET_CAR_COORDINATES(car5, 464.4084, -855.646, 4.2868);// ���������� �����
							SET_CAR_HEADING(car5, 152.6697);
							TASK_CAR_DRIVE_WANDER(ped6, car5, 20.0, 2);// ��� ���� ����-��

							REMOVE_BLIP(phone);//������� ������ �� ������
							ADD_BLIP_FOR_CHAR(ped6, &phone);
							CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "Blip01" ��������� � ������� �����
							CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							Text = 0;
							Text2 = 0;
							stage = 5;
						}
						else if (IS_CHAR_INJURED(ped5))
						{
							EXPLODE_CHAR_HEAD(ped5);
						}
					}
					// ����� 5 ( ��� ���������)
					if (stage == 5)
					{
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 40.0 )
						{
							if ((Text == 0) && (Text2 == 0))
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "ASM3_18", 5000, 1);//~g~Don't get too close to the target or he may spot you!
								Text = 1;
							}
						}
						else
						{
							if ((Text == 1) && (Text2 == 0))
							{
								Text = 0;
							}
						}
						if (( PlayR < 20.0) && (Text2 == 0))
						{
							TASK_CAR_DRIVE_WANDER(ped6, car5, 40.0, 2);// ��� ���� ����-��
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM3_19", 5000, 1);//~g~He's seen you! Waste him!
							Text2 = 1;
						}

						if (IS_CHAR_DEAD(ped6))// �������� ����� ���� ����
						{
							REMOVE_BLIP(phone);//������� ������ �� ������
							skip = 2;// ���������� ��������
							break;
						}
						else if (IS_CHAR_INJURED(ped6))
						{
							EXPLODE_CHAR_HEAD(ped6);
						}
					}
					//============================ HUD ============================
					// ������ ���
					if (TIMERB() > 999)
					{
						time_s -= 1;
						SETTIMERB( 0 );
					}
					if (time_s < 0)
					{
						time_m -= 1;
						time_s = 59;
					}
					time_ms = TIMERB();

					// ������
					DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
					//DRAW_SPRITE( timer, 0.8765625, 0.7838, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// ������ ������� ��������.
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
					if ((time_m == 0) && (time_s == 0))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "ASM3_21", 5000, 1);//~r~You did not kill all the gang members in time!
						skip = 1;// ���������� ��������
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
					{
						skip = 1;// ���������� ��������
						break;
					}
				}

				REMOVE_BLIP(phone);//������� ������ �� ������
				REMOVE_BLIP(phone2);//������� ������ �� ������
				blip_on = 0;

				// ��������� ��������
				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}
				REMOVE_PICKUP(sweap_1);// ��������� ������
				REMOVE_PICKUP(sweap_2);// ��������� ������

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//��������� ������ ����

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//��������� ������ ������

				// ��������� �� ������ �����
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������

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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 4000);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +4000 );//��� ������ �����
					G_ASSASSIN = 6;
					sutosave = 1;
				}

				G_ONMISSION = 0;
			}
		}
//============================== Check Out at the Check In ======================================
		else if ((G_ONMISSION == 0) && (G_ASSASSIN == 7))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-1050.36, -291.03, 8.83, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_UNKNOWN_CONTACT);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(phone, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "LG_25");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			//=============== ���� ������ =============== 
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1050.36+20, -291.03+20, 8.83-5, -1050.36-20, -291.03-20, 8.83+10, 0 )) && (sound_load == 0))// �������� ����� � ���� �������� ����� �������� �������� � �� �� ������ � �������� ������ "��������� � �������� � ��������� ������".
			{
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/PHONERING" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_PHONERING_STREETR1", -1050.36, -291.03, 8.83);
				CLEAR_AREA(-1050.36, -291.03, 8.83, 3.0, 1);//������� ���� ��������
				sound_load = 1;
			}
			else if (((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1050.36+20, -291.03+20, 8.83-5, -1050.36-20, -291.03-20, 8.83+10, 0 )) && (sound_load == 1)))// ���� ����� �� � ���� ��������� ����
			{
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
			}
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -1050.36, -291.03, 8.83, &PlayR);//�������� "����� �� �����������"
			DRAW_CHECKPOINT( -1050.36, -291.03, 8.83, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(phone);//������� ������ �� ������
				SET_MOVIE_VOLUME(0);
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
				blip_on = 0;

				Object trubka_1;
				uint trubka = cj_handset_one;
				uint random;
				Cam camera;
				Pickup sweap_1, bag;
				Texture fon;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17;
				Car car1, car2, car3, car4;
				skip = 0;
				Text = 0;
				kill = 0;

				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, 1.1, &trubka_1, TRUE);
				ATTACH_OBJECT_TO_PED( trubka_1, GetPlayerPed(), 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	

				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
					{
						break;
					}
					WAIT( 0 );
				}
				CLEAR_AREA(-1050.36, -291.03, 8.83, 2.0, 1);//������� ���� ��������
				SET_WIDESCREEN_BORDERS( 1 );
				SET_CHAR_COORDINATES(GetPlayerPed(), -1050.36, -291.03, 9.374);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), 175.0);
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -1051.469, -292.323, 10.164 ); // ���� ������� ������
				SET_CAM_POS			( camera, -1051.447, -289.012, 11.326);//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SetTime(800);

				REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
				SetTime(800);
				WAIT(0);

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TK", "ASM4_A", 0, 0);//Time to fry bigger fish, Mr. Teal. There's a rifle in the foliage to your right.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				POINT_CAM_AT_COORD	( camera, -1064.856, -280.408, 9.474 ); // ���� ������� ������
				SET_CAM_POS			( camera, -1045.159, -293.486, 10.223);//������������ ������

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_TL", "ASM4_B", 0, 0);//Watch the woman standing on the balcony above the check-in desks. She will walk through the crowd and ask someone the time.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				POINT_CAM_AT_COORD	( camera, -1051.48, -290.806, 9.85 ); // ���� ������� ������
				SET_CAM_POS			( camera, -1051.455, -294.347, 11.756);//������������ ������

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_UA", "ASM4_C", 0, 0);//You must kill that person, retrieve his case and take it to the location taped under the phone.
				START_SCRIPT_CONVERSATION(1, 1);
				SetTime(2000);
				SetSpeech();

				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "put_down_phone", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
				SetTime(1000);
				DETACH_OBJECT( trubka_1, 1 );
				DELETE_OBJECT( &trubka_1 );
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);

				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������

				// ������ ���
				CREATE_PICKUP_ROTATE(w_psg1, 3, 10, -1064.828, -276.173, 9.398, 90.0, -85.0, -90.0, &sweap_1);// ��� ��������

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "ASM4_15", 5000, 1);//~g~Get the sniper rifle to your right.
				ADD_BLIP_FOR_PICKUP(sweap_1, &phone);
				CHANGE_BLIP_SPRITE(phone, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(phone, 19);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "��������"

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

				uint PedM1 = MODEL_F_Y_PMANHAT_02;// �������
				uint PedM2 = MODEL_M_M_PMANHAT_02;// ��� � ������� 1
				uint PedM3 = MODEL_M_M_BUSINESS_02;// �������������
				uint PedM4 = MODEL_M_M_BUSINESS_03;// ��� � ������� 2

				uint CarM1 = MODEL_ADMIRAL;//���������� "Car2" = ������ ������
				uint CarM2 = MODEL_WASHINGTON;//���������� "Car2" = ������ ������

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );

				REQUEST_MODEL(PedM1);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM2);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM3);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(PedM4);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM4));////�������� "��� ����������" ���� ��� �� �������� � ������

				CREATE_CHAR (26, PedM1, 290.008, -783.209, 5.06, &ped1, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, 286.386, -785.672, 5.06, &ped2, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, 289.619, -785.672, 5.06, &ped3, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM4, 292.961, -785.672, 5.06, &ped14, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, 296.473, -785.672, 5.06, &ped15, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, 299.976, -785.672, 5.06, &ped16, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM4, 286.386, -783.209, 5.06, &ped17, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������

				REQUEST_MODEL(CarM1);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM1));//�������� "������ �����������" ���� ��� �� �������� � ������

				REQUEST_MODEL(CarM2);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM2));//�������� "������ �����������" ���� ��� �� �������� � ������

				CREATE_CAR(CarM1, 286.232, -791.79, 5.445, &car1, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				CREATE_CAR(CarM1, 289.629, -791.79, 5.445, &car2, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				CREATE_CAR(CarM1, 293.025, -791.79, 5.445, &car3, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				CREATE_CAR(CarM2, 296.422, -791.79, 5.445, &car4, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������

				// ���� �����
				CHANGE_CAR_COLOUR( car1, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 133, 133 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car2, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car2, 133, 133 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car3, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car3, 133, 133 );//���� ��������� ������
				CHANGE_CAR_COLOUR( car4, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car4, 133, 133 );//���� ��������� ������

				REQUEST_ANIMS( "amb@hang_str_f_idls" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_f_idls" )) WAIT(0);
				REQUEST_ANIMS( "amb@book" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@book" )) WAIT(0);

				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM3, &ped4);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM4, &ped5);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM4, &ped6);//������ ���� �� ���� ����������
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM3, &ped13);//������ ���� �� ���� ����������

				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM4, 0, &ped7);
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 0, &ped8);
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM4, 0, &ped9);
				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM4, 1, &ped10);
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 1, &ped11);
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 1, &ped12);

				SET_CHAR_RELATIONSHIP_GROUP(ped3, 3);
				SET_CHAR_RELATIONSHIP(ped3, 5, 0);
				SET_SENSE_RANGE(ped3, 49.0);
				UpdateWeaponOfPed(ped3, WEAPON_MICRO_UZI);

				// ����� 1
				while(true)
				{
					WAIT(0);
					if (HAS_PICKUP_BEEN_COLLECTED( sweap_1 ))
					{
						GENERATE_RANDOM_INT_IN_RANGE( 1, 6, &random);
						REMOVE_BLIP(phone);//������� ������ �� ������
						SET_CHAR_COORDINATES(ped1, -987.341, -341.461, 15.845);// ���������� ������
						SET_CHAR_HEADING(ped1, -85.0);

						if ((random == 1) || (random == 4))
						{
							SET_CHAR_COORDINATES(ped2, -956.108, -333.376, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped3, -955.775, -333.934, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped2, 45.0);
							SET_CHAR_HEADING(ped3, 45.0);
							SET_CHAR_COORDINATES(ped14, -957.632, -334.431, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped15, -956.893, -334.733, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped14, 65.0);
							SET_CHAR_HEADING(ped15, 65.0);
							SET_CHAR_COORDINATES(ped16, -958.563, -335.394, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped17, -958.111, -335.871, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped16, 15.0);
							SET_CHAR_HEADING(ped17, 15.0);
						}
						
						else if ((random == 2) || (random == 5))
						{

							SET_CHAR_COORDINATES(ped14, -956.108, -333.376, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped15, -955.775, -333.934, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped14, 65.0);
							SET_CHAR_HEADING(ped15, 65.0);
							SET_CHAR_COORDINATES(ped2, -957.632, -334.431, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped3, -956.893, -334.733, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped2, 45.0);
							SET_CHAR_HEADING(ped3, 45.0);
							SET_CHAR_COORDINATES(ped16, -958.563, -335.394, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped17, -958.111, -335.871, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped16, 15.0);
							SET_CHAR_HEADING(ped17, 15.0);
						}
						else if ((random == 3) || (random == 6))
						{
							SET_CHAR_COORDINATES(ped14, -956.108, -333.376, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped15, -955.775, -333.934, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped14, 65.0);
							SET_CHAR_HEADING(ped15, 65.0);
							SET_CHAR_COORDINATES(ped16, -957.632, -334.431, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped17, -956.893, -334.733, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped16, 15.0);
							SET_CHAR_HEADING(ped17, 15.0);
							SET_CHAR_COORDINATES(ped2, -958.563, -335.394, 9.845);// ���������� ������
							SET_CHAR_COORDINATES(ped3, -958.111, -335.871, 9.845);// ���������� ������
							SET_CHAR_HEADING(ped2, 45.0);
							SET_CHAR_HEADING(ped3, 45.0);
						}

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
						SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������

						SET_WIDESCREEN_BORDERS( 1 );
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -987.341, -341.461, 15.845 ); // ���� ������� ������
						SET_CAM_POS			( camera, -1053.5, -289.078, 11.48);//������������ ������
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "ASM4_16", 5000, 1);//~g~Watch the woman on the balcony, she will walk down the escalators and ask someone the time.
						SetTime2(6000);

						if (Text == 0)
						{
							POINT_CAM_AT_COORD	( camera, -987.341, -341.461, 16.187 ); // ���� ������� ������
							SET_CAM_POS			( camera, -984.484, -340.774, 16.786);//������������ ������
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_17", 5000, 1);//~g~Once the conversation has finished kill the person she spoke to, but do not kill her.
							SetTime2(6000);
						}
						if (Text == 0)
						{
							POINT_CAM_AT_COORD	( camera, -987.341, -341.461, 16.084 ); // ���� ������� ������
							SET_CAM_POS			( camera, -959.011, -295.461, 10.037);//������������ ������
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_18", 5000, 1);//~g~Once the target is dead retrieve his briefcase and take it to Ammu-Nation in Downtown.
							SetTime2(6000);
						}
						if (Text == 0)
						{
							POINT_CAM_AT_COORD	( camera, -987.341, -341.461, 15.845 ); // ���� ������� ������
							SET_CAM_POS			( camera, -1018.073, -318.076, 15.348);// ������������ ������
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_19", 5000, 1);//~g~Keep your distance from the target! Use the distance bar in the upper right corner of the screen.
							SetTime2(6000);
						}
						if (Text == 0)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_20", 5000, 1);//~g~If it gets full he will see you.
							SetTime2(6000);
						}

						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
						SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������

						ADD_BLIP_FOR_CHAR(ped1, &phone);
						CHANGE_BLIP_SPRITE(phone, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(phone, 19);   //���� ������ �� ������ (0=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "�������"
						CHANGE_BLIP_SCALE(phone, 0.77999990); // ������� ������ �� ������
						SETTIMERB( 0 );
						Text = 0;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
					{
						skip = 1;
						break;
					}
				}

				// ����� 2 
				if ( skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if ((TIMERB() > 10000) && (Text == 0))
						{
							GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 2, -2);
							Text = 1;
						}

						// HUD ���
						GET_CHAR_COORDINATES(ped2,  &PedX2, &PedY2, &PedZ2);//��������� ���������� ������ � ����������
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX2, PedY2, PedZ2, &PlayR);//�������� "����� �� �����������"

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.80277778, "ASM4_12"); //DISTANCE:

						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
						DRAW_SPRITE( 0, 0.9088541, 0.80925926, 0.0739583, 0.014, 0.0, 27, 89, 130, 255 );// ������ ������� ��������.

						carHUD_x = 0.9088541;
						carHUD_w = 0.0739583;

						if (PlayR < 50)
						{
							carH1 = 0;
						}
						else if (PlayR > 99)
						{
							carH1 = 50;
						}
						else
						{
							carH1 = PlayR-50;
						}
						carH2 = carHUD_w/50;
						carH3 = carH2*carH1;
						carHUD_y1 = carHUD_w-carH3;
						carHUD_y2 = carHUD_y1/2;
						carHUD_y3 = carHUD_x-carHUD_y2;
						DRAW_SPRITE( 0, carHUD_y3, 0.80925926, carH3, 0.014, 0.0, 97, 194, 247, 255 );// ������ ������� ��������.

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
						{
							skip = 1;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_25", 5000, 1);//~r~You killed the woman you fool!
							skip = 1;
							break;
						}
						else if (PlayR < 50)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_27", 5000, 1);//~r~The target has seen you! You should have kept your distance!
							skip = 1;
							break;
						}
						else if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -883.542, -434.103, -1114.664, -241.825, 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_28", 5000, 1);//~r~The target heard you firing your weapon!
							skip = 1;
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -883.542, -434.103, 5.0, -1114.664, -241.825, 50.0, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_26", 5000, 1);//~r~The target has boarded his flight!
							skip = 1;
							break;
						}
						
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, PedX2, PedY2, PedZ2, &PedR);//�������� "����� �� �����������"
						if ((PedR < 0.95) && (kill == 0))
						{
							SETTIMERB( 0 );
							SET_CHAR_HEADING(ped1, -145.0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a4", "amb@hang_str_f_idls", 2.5, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
							kill = 1;
						}
						else if ((kill == 1) && (TIMERB() > 3600))
						{
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "walk_read", "amb@book", 5.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
							kill = 2;
							SETTIMERB( 0 );
						}
						else if ((kill == 2) && (TIMERB() > 9600))
						{
							REMOVE_BLIP(phone);//������� ������ �� ������
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -1051.469, -292.922, 8.811, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -925.87, -400.47, 15.0, 2, -2, 2.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, -925.87, -400.47, 15.0, 2, -2, 2.5);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped14, -1079.939, -393.444, 15.842, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped15, -1036.512, -318.776, 9.846, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped16, -1058.969, -289.701, 9.845, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped17, -1048.746, -272.925, 9.845, 2, -2, 3.5);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEASM4_K", 5000, 1);//~g~Nail him and get the briefcase!
							break;
						}
					}
				}

				// ����� 3
				if ( skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped2))
						{
							// �� ���� �������� ����
							GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);

							CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// �����
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_21", 5000, 1);//~g~Get the briefcase!

							ADD_BLIP_FOR_PICKUP(bag, &phone);
							CHANGE_BLIP_SPRITE(phone, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 19);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "�����"

							if (!IS_CHAR_DEAD(ped3))
							{
								SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MICRO_UZI, TRUE);
								TASK_COMBAT(ped3, GetPlayerPed());// ����� ��������
							}
							break;
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}

						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -925.87, -400.47, 15.0, &PedR);//�������� "����� �� �����������"
						if ((PedR < 2.0) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -883.542, -434.103, 5.0, -1114.664, -241.825, 50.0, 0 )))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_26", 5000, 1);//~r~The target has boarded his flight!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
						{
							skip = 1;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_25", 5000, 1);//~r~You killed the woman you fool!
							skip = 1;
							break;
						}
					}
				}

				// ����� 4
				if ( skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( bag ))
						{
							REMOVE_BLIP(phone);//������� ������ �� ������
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_22", 5000, 1);//~g~Take the briefcase to Ammu-Nation in Downtown.
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							ADD_BLIP_FOR_COORD(-234.027, 1728.927, 4.98, &phone);//������� ������ �� ������
							CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
							CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "NE_POINT");//������ �� ������ ��������� � ������� ����� "���������� ������"
							
							// ������ ������ ������
							SET_CAR_COORDINATES(car1, -749.967, -403.764, 9.373);// ���������� ������
							SET_CAR_HEADING(car1, 90.0);
							SET_CAR_COORDINATES(car2, -749.808, -412.417, 9.373);// ���������� ������
							SET_CAR_HEADING(car2, 90.0);
							SET_CAR_COORDINATES(car3, -705.431, -561.59, 9.222);// ���������� ������
							SET_CAR_HEADING(car3, -55.0);
							SET_CAR_COORDINATES(car4, -232.818, 1726.323, 5.41);// ���������� ������
							SET_CAR_HEADING(car4, -90.0);

							// ����� �����
							SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped10, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped11, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped12, 3);

							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_CHAR_RELATIONSHIP(ped5, 5, 0);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);
							SET_CHAR_RELATIONSHIP(ped10, 5, 0);
							SET_CHAR_RELATIONSHIP(ped11, 5, 0);
							SET_CHAR_RELATIONSHIP(ped12, 5, 0);

							SET_SENSE_RANGE(ped4, 50.0);
							SET_SENSE_RANGE(ped5, 50.0);
							SET_SENSE_RANGE(ped6, 50.0);
							SET_SENSE_RANGE(ped7, 50.0);
							SET_SENSE_RANGE(ped8, 50.0);
							SET_SENSE_RANGE(ped9, 50.0);
							SET_SENSE_RANGE(ped10, 50.0);
							SET_SENSE_RANGE(ped11, 50.0);
							SET_SENSE_RANGE(ped12, 50.0);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 1);

							UpdateWeaponOfPed(ped4, WEAPON_MP5);
							UpdateWeaponOfPed(ped5, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped6, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped7, WEAPON_MP5);
							UpdateWeaponOfPed(ped8, WEAPON_MP5);
							UpdateWeaponOfPed(ped9, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped10, WEAPON_MICRO_UZI);
							UpdateWeaponOfPed(ped11, WEAPON_MP5);
							UpdateWeaponOfPed(ped12, WEAPON_MP5);
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
						{
							skip = 1;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_25", 5000, 1);//~r~You killed the woman you fool!
							skip = 1;
							break;
						}
					}
				}

				// ����� 5
				if ( skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( -234.027, 1728.927, 4.98, 1.3, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -234.027, 1728.927, 4.98, &PlayR);//�������� "����� �� �����������"
						if ( PlayR < 1.3 )
						{
							REMOVE_BLIP(phone);//������� ������ �� ������

							
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped13, car4, 247.653, 1521.736, 5.41, 4, 90.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while (true)
							{
								if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
								{
									break;
								}
								WAIT( 0 );
							}

							SetTime(800);
							GET_CHAR_COORDINATES(ped13,  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
							SET_WIDESCREEN_BORDERS( 1 );
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // ���� ������� ������
							SET_CAM_POS			( camera, -248.134, 1729.556, 6.535);//������������ ������
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
							SETTIMERA(0); //���������� ������ 

							while (true)
							{
								GET_CHAR_COORDINATES(ped13,  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
								POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // ���� ������� ������
								WAIT( 0 );
								if ( TIMERA() > 4000 )
								{
									break;
								}
							}
							DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
							while (true)
							{
								GET_CHAR_COORDINATES(ped13,  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
								POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // ���� ������� ������
								if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
								{
									break;
								}
								WAIT( 0 );
							}
							SET_CHAR_COORDINATES(ped13, -1.48, -2.974, 5.374);// ���������� ������
							SetTime(800);
							DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������
							skip = 2;
							break;
						}
						else if (IS_CHAR_DEAD(ped13))// �������� ��� ����
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEASM4_K2", 5000, 1);//~r~You had to give courier the bag, not to kill him.
							skip = 1;
							break;
						}

						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
						{
							skip = 1;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASM4_25", 5000, 1);//~r~You killed the woman you fool!
							skip = 1;
							break;
						}
					}
				}
				

				REMOVE_BLIP(phone);//������� ������ �� ������
				blip_on = 0;

				// ��������� ��������
				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				REMOVE_PICKUP(sweap_1);// ��������� ������
				REMOVE_PICKUP(bag);// ��������� ������

				// ��������� �� ������ ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ����
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//��������� ������ ����
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

				// ��������� �� ������ ���������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 8000);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +8000 );//��� ������ �����
					G_ASSASSIN = 8;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Loose Ends ======================================
		else if ((G_ONMISSION == 0) && (G_ASSASSIN == 9))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-544.91, 2.23, 4.81, &phone);//������� ������ �� ������
				CHANGE_BLIP_SPRITE(phone, BLIP_UNKNOWN_CONTACT);//�������� ������ �� ������
				CHANGE_BLIP_SCALE(phone, 1.1); // ������� ������ �� ������
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "LG_25");//������ �� ������ ��������� � ������� ����� "��������"
				blip_on = 1;
			}
			//=============== ���� ������ =============== 
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -544.91+20, 2.23+20, 4.81-5, -544.91-20, 2.23-20, 4.81+10, 0 )) && (sound_load == 0))// �������� ����� � ���� �������� ����� �������� �������� � �� �� ������ � �������� ������ "��������� � �������� � ��������� ������".
			{
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/PHONERING" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_PHONERING_STREETR1", -544.91, 2.23, 4.81);
				
				CLEAR_AREA(-544.91, 2.23, 4.81, 3.0, 1);//������� ���� ��������
				sound_load = 1;
			}
			else if (((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -544.91+20, 2.23+20, 4.81-5, -544.91-20, 2.23-20, 4.81+10, 0 )) && (sound_load == 1)))// ���� ����� �� � ���� ��������� ����
			{
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
			}
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -544.91, 2.23, 4.81, &PlayR);//�������� "����� �� �����������"
			DRAW_CHECKPOINT( -544.91, 2.23, 4.81, 1.5, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				REMOVE_BLIP(phone);//������� ������ �� ������
				SET_MOVIE_VOLUME(0);
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
				blip_on = 0;
				SET_MAX_WANTED_LEVEL(3);

				Pickup sweap_1, bag, aid_1;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22, ped23, ped24, ped25, ped26, ped27, ped28, ped29, ped30;
				Car car1, car2, car3, car4, car5, car6;
				Object barrel_1, barrel_2, barrel_3, barrel_4, trubka_1;
				uint trubka = cj_handset_one;
				Cam camera;
				skip = 0;

				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, 1.1, &trubka_1, TRUE);
				ATTACH_OBJECT_TO_PED( trubka_1, GetPlayerPed(), 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������	

				DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
					{
						break;
					}
					WAIT( 0 );
				}
				CLEAR_AREA(-544.91, 2.23, 4.81, 2.0, 1);//������� ���� ��������
				SET_WIDESCREEN_BORDERS( 1 );
				SET_CHAR_COORDINATES(GetPlayerPed(), -544.91, 2.23, 4.81);// ���������� ������
				SET_CHAR_HEADING(GetPlayerPed(), -81.5);
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -543.903, 2.267, 6.001 ); // ���� ������� ������
				SET_CAM_POS			( camera, -547.687, 1.584, 7.848);//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SetTime(800);

				REQUEST_ANIMS( "amb@payphone" );//��������� ���� � ���������
				while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
				DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
				SetTime(800);
				WAIT(0);

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R4_UB", "ASM5_A", 0, 0);//There is a valuable exchange taking place on the roof of the Cherry Popper Ice Cream Company.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_UC", "ASM5_B", 0, 0);//Kill everyone involved, steal the merchandise and take it to the helipad at the airport.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_UD", "ASM5_C", 0, 0);//There is a gate to your left that leads to the back of the factory.
				START_SCRIPT_CONVERSATION(1, 1);
				
				CREATE_PICKUP_ROTATE(w_m4, 3, 60, -538.907, 13.311, 5.333, 92.468, -71.444, -81.476, &sweap_1);// ��� ��������
				CREATE_PICKUP( mission_keis, 22, -457.989, 15.962, 23.214, &bag, 0 );// �����
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -488.812, -83.308, 7.516, 0.0, 0.0, 7.2, &aid_1);//������

				uint CarM1 = MODEL_ADMIRAL;//���������� "Car2" = ������ ������
				uint CarM2 = MODEL_PONY;//���������� "Car2" = ������ ������
				uint CarM3 = MODEL_MAVERICK;//���������� "Car2" = ������ ������
				uint barrel = barrel4;

				uint PedM1 = MODEL_M_M_BUSINESS_02;// ��� � ������� 1
				uint PedM2 = MODEL_M_M_BUSINESS_03;// ��� � ������� 2
				uint PedM3 = MODEL_M_M_PHARBRON_01;// ��� � ������� 3
				uint PedM4 = MODEL_M_Y_GIRI_LO_01;// ���� ����� ����

				REQUEST_MODEL(CarM1);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM1));//�������� "������ �����������" ���� ��� �� �������� � ������
				CREATE_CAR(CarM1, -505.284, 20.37, 5.356, &car1, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car1, 5.0);//������ �������� ������
				CHANGE_CAR_COLOUR( car1, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car1, 133, 133 );//���� ��������� ������

				REQUEST_MODEL(CarM2);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM2));//�������� "������ �����������" ���� ��� �� �������� � ������
				CREATE_CAR(CarM2, -492.686, 5.85, 6.267, &car2, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car2, 95.0);//������ �������� ������

				REQUEST_MODEL(CarM3);//�������� ������ ������ �� ����������
				while (!HAS_MODEL_LOADED(CarM3));//�������� "������ �����������" ���� ��� �� �������� � ������
				CREATE_CAR(CarM3, -439.053, 18.085, 23.481, &car3, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car3, 5.0);//������ �������� ������

				CREATE_CAR(CarM1, -937.7, -756.65, 9.53, &car4, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car4, 76.0);//������ �������� ������
				CHANGE_CAR_COLOUR( car4, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car4, 133, 133 );//���� ��������� ������

				CREATE_CAR(CarM1, -492.283, 0.701, 6.266, &car5, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car5, 95.0);//������ �������� ������
				CHANGE_CAR_COLOUR( car5, 0, 0 );//���� ������
				SET_EXTRA_CAR_COLOURS( car5, 133, 133 );//���� ��������� ������

				CREATE_CAR(CarM3, -935.69, -723.65, 13.03, &car6, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
				SET_CAR_HEADING(car6, 302.0);//������ �������� ������
				LOCK_CAR_DOORS(car6, 3); //��������� ����� ���������� ��� ������

				REQUEST_MODEL(barrel);
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(barrel, -495.276, 7.944, 6.124, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, -491.595, -23.04, 5.161, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, -474.276, -28.857, 5.088, &barrel_3, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, -491.316, -39.302, 5.09, &barrel_4, TRUE);

				REQUEST_MODEL(PedM1);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
				CREATE_CHAR (26, PedM1, -504.208, 22.287, 5.197, &ped1, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				SET_CHAR_HEADING(ped1, 98.5);

				REQUEST_MODEL(PedM2);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������
				CREATE_CHAR (26, PedM2, -503.577, 18.338, 5.161, &ped2, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				SET_CHAR_HEADING(ped2, 98.5);

				REQUEST_MODEL(PedM3);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������
				CREATE_CHAR (26, PedM3, -455.159, 14.935, 23.907, &ped3, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				SET_CHAR_HEADING(ped3, 68.5);

				REQUEST_MODEL(PedM4);//�������� ������ ������ ���� �� ����������
				while (!HAS_MODEL_LOADED(PedM4));////�������� "��� ����������" ���� ��� �� �������� � ������
				CREATE_CHAR (26, PedM4, -461.066, 14.043, 23.907, &ped4, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				SET_CHAR_HEADING(ped4, -106.5);

				CREATE_CHAR (26, PedM1, -492.001, -1.29, 6.108, &ped5, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -492.665, 4.217, 6.186, &ped6, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, -476.242, -17.131, 6.267, &ped7, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM1, -487.712, -11.489, 6.262, &ped8, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -493.399, -23.607, 5.496, &ped9, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, -495.069, -43.556, 5.243, &ped10, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM1, -491.706, -51.346, 5.481, &ped11, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -502.987, -58.548, 4.928, &ped12, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, -499.182, -71.402, 6.993, &ped13, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM1, -494.798, -71.694, 6.981, &ped14, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -489.305, -94.309, 10.624, &ped15, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, -476.489, -91.927, 11.093, &ped16, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM1, -444.421, -95.484, 10.468, &ped17, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -441.473, -72.128, 10.377, &ped18, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, -449.371, -58.777, 14.305, &ped19, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM1, -445.028, -37.545, 14.305, &ped20, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -451.341, -15.893, 23.867, &ped21, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM3, -446.177, -10.209, 23.867, &ped22, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM1, -458.958, -19.921, 19.459, &ped23, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -465.429, -16.929, 17.32, &ped24, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ ����������� !!!!!!!!!
				CREATE_CHAR (26, PedM3, -472.366, 20.89, 12.764, &ped25, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ ����������� !!!!!!!!!
				CREATE_CHAR (26, PedM1, -483.657, -28.911, 7.022, &ped26, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -473.936, -31.972, 5.475, &ped27, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM3, &ped28);//������ ���� �� ���� ����������
				CREATE_CHAR (26, PedM4, -461.393, 15.693, 23.907, &ped29, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
				CREATE_CHAR (26, PedM2, -455.371, 16.719, 23.907, &ped30, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������

				SET_CHAR_HEADING(ped5, -1.5);
				SET_CHAR_HEADING(ped6, -1.5);
				SET_CHAR_HEADING(ped7, -11.5);
				SET_CHAR_HEADING(ped8, -11.5);
				SET_CHAR_HEADING(ped9, -86.5);
				SET_CHAR_HEADING(ped10, -86.5);
				SET_CHAR_HEADING(ped11, -1.5);
				SET_CHAR_HEADING(ped12, -21.5);
				SET_CHAR_HEADING(ped13, -106.5);
				SET_CHAR_HEADING(ped14, 103.5);
				SET_CHAR_HEADING(ped15, -96.5);
				SET_CHAR_HEADING(ped16, -96.5);
				SET_CHAR_HEADING(ped17, 73.5);
				SET_CHAR_HEADING(ped18, 73.5);
				SET_CHAR_HEADING(ped19, -106.5);
				SET_CHAR_HEADING(ped20, 106.5);
				SET_CHAR_HEADING(ped21, -106.5);
				SET_CHAR_HEADING(ped22, 148.5);
				SET_CHAR_HEADING(ped23, 173.5);
				SET_CHAR_HEADING(ped24, 98.5);
				SET_CHAR_HEADING(ped25, 98.5);
				SET_CHAR_HEADING(ped26, 83.5);
				SET_CHAR_HEADING(ped27, -106.5);
				SET_CHAR_HEADING(ped29, -106.5);
				SET_CHAR_HEADING(ped30, 68.5);
				SetTime(200);

				// ������ ������������ �����
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -539.988, 18.069, 5.86 ); // ���� ������� ������
				SET_CAM_POS			( camera, -555.857, 5.303, 10.604 );//������������ ������
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SetTime(3550);
				SetSpeech();

				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SetTime(1000);

				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "put_down_phone", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
				SetTime(1000);

				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);
				DETACH_OBJECT( trubka_1, 1 );
				DELETE_OBJECT( &trubka_1 );
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);
				SetTime(1000);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ �� ���������� ����
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� ��������

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "ASM5_1", 5000, 1);//~g~Enter the compound behind the Cherry Popper Ice Cream Company The deal is taking place on the roof.

				UpdateWeaponOfPed(ped1, WEAPON_MP5);
				UpdateWeaponOfPed(ped2, WEAPON_MP5);
				UpdateWeaponOfPed(ped3, WEAPON_MP5);
				UpdateWeaponOfPed(ped4, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped5, WEAPON_MP5);
				UpdateWeaponOfPed(ped6, WEAPON_MP5);
				UpdateWeaponOfPed(ped7, WEAPON_MP5);
				UpdateWeaponOfPed(ped8, WEAPON_MP5);
				UpdateWeaponOfPed(ped9, WEAPON_MP5);
				UpdateWeaponOfPed(ped10, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped11, WEAPON_MP5);
				UpdateWeaponOfPed(ped12, WEAPON_MP5);
				UpdateWeaponOfPed(ped13, WEAPON_MP5);
				UpdateWeaponOfPed(ped14, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped15, WEAPON_MP5);
				UpdateWeaponOfPed(ped16, WEAPON_MP5);
				UpdateWeaponOfPed(ped17, WEAPON_MP5);
				UpdateWeaponOfPed(ped18, WEAPON_MP5);
				UpdateWeaponOfPed(ped19, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped20, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped21, WEAPON_MP5);
				UpdateWeaponOfPed(ped22, WEAPON_MP5);
				UpdateWeaponOfPed(ped23, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped24, WEAPON_M4);
				UpdateWeaponOfPed(ped25, WEAPON_AK47);
				UpdateWeaponOfPed(ped26, WEAPON_MP5);
				UpdateWeaponOfPed(ped27, WEAPON_MICRO_UZI);
				UpdateWeaponOfPed(ped29, WEAPON_MP5);
				UpdateWeaponOfPed(ped30, WEAPON_MP5);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped23, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped24, WEAPON_M4, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped25, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped26, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped27, WEAPON_MICRO_UZI, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped29, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped30, WEAPON_MP5, TRUE);

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
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped21, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped22, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped23, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped24, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped25, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped26, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped27, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped29, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped30, 5);

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
				SET_CHAR_RELATIONSHIP(ped17, 5, 0);
				SET_CHAR_RELATIONSHIP(ped18, 5, 0);
				SET_CHAR_RELATIONSHIP(ped19, 5, 0);
				SET_CHAR_RELATIONSHIP(ped20, 5, 0);
				SET_CHAR_RELATIONSHIP(ped21, 5, 0);
				SET_CHAR_RELATIONSHIP(ped22, 5, 0);
				SET_CHAR_RELATIONSHIP(ped23, 5, 0);
				SET_CHAR_RELATIONSHIP(ped24, 5, 0);
				SET_CHAR_RELATIONSHIP(ped25, 5, 0);
				SET_CHAR_RELATIONSHIP(ped26, 5, 0);
				SET_CHAR_RELATIONSHIP(ped27, 5, 0);
				SET_CHAR_RELATIONSHIP(ped29, 5, 0);
				SET_CHAR_RELATIONSHIP(ped30, 5, 0);

				SET_SENSE_RANGE(ped1, 10.0);
				SET_SENSE_RANGE(ped2, 20.0);
				SET_SENSE_RANGE(ped3, 10.0);
				SET_SENSE_RANGE(ped4, 10.0);
				SET_SENSE_RANGE(ped5, 20.0);
				SET_SENSE_RANGE(ped6, 20.0);
				SET_SENSE_RANGE(ped7, 10.0);
				SET_SENSE_RANGE(ped8, 10.0);
				SET_SENSE_RANGE(ped9, 20.0);
				SET_SENSE_RANGE(ped10, 10.0);
				SET_SENSE_RANGE(ped11, 10.0);
				SET_SENSE_RANGE(ped12, 20.0);
				SET_SENSE_RANGE(ped13, 10.0);
				SET_SENSE_RANGE(ped14, 20.0);
				SET_SENSE_RANGE(ped15, 20.0);
				SET_SENSE_RANGE(ped16, 10.0);
				SET_SENSE_RANGE(ped17, 20.0);
				SET_SENSE_RANGE(ped18, 10.0);
				SET_SENSE_RANGE(ped19, 20.0);
				SET_SENSE_RANGE(ped20, 10.0);
				SET_SENSE_RANGE(ped21, 10.0);
				SET_SENSE_RANGE(ped22, 10.0);
				SET_SENSE_RANGE(ped23, 10.0);
				SET_SENSE_RANGE(ped24, 35.0);
				SET_SENSE_RANGE(ped25, 35.0);
				SET_SENSE_RANGE(ped26, 10.0);
				SET_SENSE_RANGE(ped27, 20.0);
				SET_SENSE_RANGE(ped29, 10.0);
				SET_SENSE_RANGE(ped30, 10.0);

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
				SET_CHAR_WILL_USE_COVER(ped17, 1);
				SET_CHAR_WILL_USE_COVER(ped18, 1);
				SET_CHAR_WILL_USE_COVER(ped19, 1);
				SET_CHAR_WILL_USE_COVER(ped20, 1);
				SET_CHAR_WILL_USE_COVER(ped21, 1);
				SET_CHAR_WILL_USE_COVER(ped22, 1);
				SET_CHAR_WILL_USE_COVER(ped23, 1);
				SET_CHAR_WILL_USE_COVER(ped24, 1);
				SET_CHAR_WILL_USE_COVER(ped25, 1);
				SET_CHAR_WILL_USE_COVER(ped26, 1);
				SET_CHAR_WILL_USE_COVER(ped27, 1);
				SET_CHAR_WILL_USE_COVER(ped29, 1);
				SET_CHAR_WILL_USE_COVER(ped30, 1);

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
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped23, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped24, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped25, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped26, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped27, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped29, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped30, FALSE);

				ADD_BLIP_FOR_PICKUP(bag, &phone);
				CHANGE_BLIP_SPRITE(phone, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(phone, 19);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "MO_TARGET");//������ �� ������ "�����"

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

				FREEZE_CAR_POSITION(car6, 1);
				SET_CAR_PROOFS(car6, 1, 1, 1, 1, 1);//������ ������ ����������

				while(true)
				{
					WAIT(0);
					if (HAS_PICKUP_BEEN_COLLECTED( bag ))
					{
						REMOVE_BLIP(phone);//������� ������ �� ������
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "ASM5_3", 5000, 1);//~g~Take the merchandise to the helipad at the airport!

						ADD_BLIP_FOR_COORD(-932.99, -726.01, 10.01, &phone);//������� ������ �� ������
						CHANGE_BLIP_SPRITE(phone, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(phone, 5);   //���� ������ �� ������ (0=�����)
						CHANGE_BLIP_SCALE(phone, 0.6); // ������� ������ �� ������
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(phone, "NE_POINT");//������ �� ������ ��������� � ������� ����� "���������� ������"

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
						break;
					}
					else if (IS_CHAR_DEAD(ped28))// �������� ��� ����
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEASM4_K2", 5000, 1);//~r~You had to give courier the bag, not to kill him.
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
					{
						skip = 1;
						break;
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);

						DRAW_CHECKPOINT( -932.99, -726.01, 12.093, 2.0, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -932.99, -726.01, 12.093, &PlayR);//�������� "����� �� �����������"
						if (( PlayR < 2.0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
								REMOVE_BLIP(phone);//������� ������ �� ������
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

								DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
								while (true)
								{
									if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
									{
										break;
									}
									WAIT( 0 );
								}
								SET_CAR_COORDINATES(car3, 5.48, 6.974, 5.374);// ���������� ������
								WAIT( 20 );
								CLEAR_AREA(-935.69, -723.65, 13.03, 8.0, 1);//������� ���� ��������
								FREEZE_CAR_POSITION(car6, 0);
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped28, car6, 12.6, 15.7, 88.4, 4, 90.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
								SetTime(800);
								SET_WIDESCREEN_BORDERS( 1 );
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -935.69, -723.65, 13.03 ); // ���� ������� ������
								SET_CAM_POS			( camera, -942.569, -746.697, 13.687);//������������ ������
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);

								DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
								SETTIMERA(0); //���������� ������ 

								while (true)
								{
									GET_CHAR_COORDINATES(ped28,  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
									POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // ���� ������� ������
									WAIT( 0 );
									if ( TIMERA() > 4000 )
									{
										break;
									}
								}
								DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
								while (true)
								{
									GET_CHAR_COORDINATES(ped28,  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
									POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // ���� ������� ������
									if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //���� ����� ����������
									{
										break;
									}
									WAIT( 0 );
								}
								// ������������� ������/�����/�������
								SET_CHAR_COORDINATES(ped28, -1.48, -2.974, 5.374);// ���������� ������
								SetTime(500);
								DO_SCREEN_FADE_IN( 1500 );// ��������� ���������� ������
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								DESTROY_CAM( camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
								skip = 2;
								break;
						}
						else if (IS_CHAR_DEAD(ped28))// �������� ��� ����
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEASM4_K2", 5000, 1);//~r~You had to give courier the bag, not to kill him.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
						{
							skip = 1;
							break;
						}

						
					}
				}
				REMOVE_BLIP(phone);//������� ������ �� ������
				SET_MAX_WANTED_LEVEL(6);

				REMOVE_PICKUP(sweap_1);
				REMOVE_PICKUP(bag);
				REMOVE_PICKUP(aid_1);

				// ��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//��������� ������

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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped25);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped26);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped27);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped28);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped29);//��������� ������ ����(� ����������� ��� ��������
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped30);//��������� ������ ����(� ����������� ��� ��������

				// ��������� ������
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//��������� ������ ������(� ����������� ������ ��������)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//��������� ������ ������(� ����������� ������ ��������)

				// ������� �������
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);
				DELETE_OBJECT(&barrel_3);
				DELETE_OBJECT(&barrel_4);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_4);

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
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 16000);// +5000$
						
						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}
					ADD_SCORE( GetPlayerIndex(), +16000 );//��� ������ �����
					G_ASSASSIN = 10;
					sutosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(phone);//������� ������ �� ������
				blip_on = 0;
			}
			if (sound_load == 1)
			{
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				sound_load = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_ASSASSIN < 10)
	{
		telephone();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
