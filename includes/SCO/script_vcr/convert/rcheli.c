/***********************************************************************
					Fully stripped main script
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/
// IS PLAYER FREE AIMING AT CHAR //��������� ������ �� ��������
#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, checkX, checkY, checkZ, checkX2, checkY2, checkZ2, check_cord, textur;
float time_m, time_s, skip, zone;

Texture fon;

void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
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
void rc_raider(void)
{
	Car car0, car1, goblin;
	uint checkpoint;
	Blip Blip_r, Blip_r2;
	Cam camera;

	skip = 0;
	zone = 1;
	textur = LOAD_TXD( "sunshine_race" );
	fon = GET_TEXTURE( textur, "fon_hud" );

	DO_SCREEN_FADE_OUT( 250 );// ��������� �����
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}
	SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// ������ ���������� ����
	SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// ����� �����������
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
	GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car0);//�������� ����������
	SET_ENGINE_HEALTH(car0, 900);
	SET_CAR_COORDINATES_NO_OFFSET(car0, -800.605, -700.893, 9.668);
	SET_CAR_HEADING(car0, -18.916);

	//������ �������
	check_cord = 1;
	uint CarM1 = MODEL_TOURMAV;
	REQUEST_MODEL(CarM1);
	while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
	CREATE_CAR(CarM1, -803.77, -700.257, 9.22, &goblin, TRUE);
	SET_CAR_HEADING(goblin, -18.916);
	SET_CAR_LIVERY(goblin, 1);
	FREEZE_CAR_POSITION(goblin, 1);

	//���������� ������
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, -802.531, -700.031, 9.468 ); // ���� ������� ������
	SET_CAM_POS			( camera, -798.093, -694.052, 12.573 );//������������ ������
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CAM_FOV( camera, 45.0 );
	SET_WIDESCREEN_BORDERS( 1 );
	DO_SCREEN_FADE_IN( 250 );// ��������� ���������� ������

	//������������� �������� ����� � ������ ���� �������
	REQUEST_ANIMS( "ne_topfun" );//��������� ���� � ���������
	while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
	SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_out", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
	MARK_CAR_AS_NO_LONGER_NEEDED(&car0);//��������� �� ������ ������
	
	//��������� ������� � ���� ������ �����
	PRINT_STRING_IN_STRING_NOW("string", "RCH1_6", 5000, 1);//~g~Use the RC Helicopter to collect checkpoints scattered throughout the airport.
	SetTime(2000);

	SET_CHAR_VISIBLE(GetPlayerPed(), 0); //���������� �����
	TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), goblin, TRUE);//����� ������ � �������
	SetTime(3000);

	uint CarM2 = MODEL_SPEEDO;
	REQUEST_MODEL(CarM2);
	while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
	CLEAR_AREA( -800.605, -700.893, 9.468, 6.0, 1);//������� ���� ��������
	CREATE_CAR(CarM2, -800.605, -700.893, 9.468, &car1, TRUE);
	SET_CAR_HEADING(car1, -18.916);
	SET_CAR_LIVERY(car1, 1);
	SET_CAR_PROOFS(car1, 1, 1, 1, 1, 1);
	FREEZE_CAR_POSITION(car1, 1);
	
	checkX = -858.4858;
	checkY =-720.3286;
	checkZ = 16.91778;
	checkX2 = -974.7137;
	checkY2 =-743.5944;
	checkZ2 = 18.04353;
	checkpoint = CREATE_CHECKPOINT( 4, checkX, checkY, checkZ, checkX2, checkY2, checkZ2, 0.20000000 );
	ADD_BLIP_FOR_COORD(checkX, checkY, checkZ, &Blip_r);//������� ������ �� ������ � ���������� "Blip01"
	CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_r, 5);   //���� ������ �� ������ (0=�����)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//������ �� ������ "Blip01" ��������� � ������� �����
	CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // ������� ������ �� ������

	ADD_BLIP_FOR_COORD(checkX2, checkY2, checkZ2, &Blip_r2);//������� ������ �� ������ � ���������� "Blip01"
	CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_r2, 5);   //���� ������ �� ������ (0=�����)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//������ �� ������ "Blip01" ��������� � ������� �����
	CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // ������� ������ �� ������
	CHANGE_BLIP_ALPHA(Blip_r2, 125);

	SETTIMERB( 0 );
	time_m = 0;
	time_s = 0;

	POINT_CAM_AT_COORD	( camera, -858.486, -720.329, 16.918 ); // ���� ������� ������
	SET_CAM_POS			( camera, -862.129, -708.642, 19.483 );//������������ ������
	PRINT_STRING_IN_STRING_NOW("string", "RCH1_7", 5000, 1);//~g~There are 20 checkpoints in total.
	SetTime(5000);

	//���������� ������ �� �������
	POINT_CAM_AT_COORD	( camera, -803.77, -700.257, 9.22 ); // ���� ������� ������
	SET_CAM_POS			( camera, -806.224, -695.017, 11.192 );//������������ ������
	PRINT_STRING_IN_STRING_NOW("string", "RCH1_8", 5000, 1);//~g~If you wish to quit this mission press the ~h~~k~~PAD_LB~ ~g~button to detonate your RC Helicopter.
	SetTime(5000);

	//������� ������
	SET_CAM_BEHIND_PED( GetPlayerPed() );
	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	END_CAM_COMMANDS( &camera );
	SET_WIDESCREEN_BORDERS( 0 );
	SET_FOLLOW_VEHICLE_CAM_SUBMODE(2);
	SetTime(1000);
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������ ������
	FREEZE_CAR_POSITION(goblin, 0);
	//


	while (TRUE)
	{
		WAIT(0);
		SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);

		//������ ���
		if (TIMERB() > 999)
		{
			time_s += 1;
			SETTIMERB( 0 );
		}
		if (time_s > 59)
		{
			time_m += 1;
			time_s = 0;
		}


		//============================ HUD ============================
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.

		//�����
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if (time_m > 9)
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", time_m);// ������
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// ������
		}
		setup_draw_value();
		DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if ( time_s > 9 )
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", time_s);// �������
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", time_s);// �������
		}

		//���������
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "RCH1_4");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if (check_cord < 11)
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_ZERO", check_cord-1);// 
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_NOZERO", check_cord-1);// 
		}
		setup_draw_value();
		DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "OUTOF_NUM", 20);// 

		if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) || (GET_ENGINE_HEALTH(goblin) < 200) || (IS_CAR_IN_WATER(goblin)))//���� ����� ������� ��� ��������� �������, ����� ������ ������
		{
			PRINT_STRING_IN_STRING_NOW("string", "WRECKED", 7000, 1);//~r~The vehicle is wrecked!
			EXPLODE_CAR(goblin, 1, 1);
			SetTime(1000);
			skip = 1;
			break;
		}
		else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1651.942, -1142.788, -15.613, -451.942, 57.212, 364.387, 0 ))
		{
			PRINT_STRING_IN_STRING_NOW("string", "RCH1_13", 7000, 1);//~r~The RC helicopter went out of range!
			EXPLODE_CAR(goblin, 1, 1);
			SetTime(1000);
			skip = 1;
			break;
		}

		if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1461.723, -952.569, -15.613, -642.161, -133.007, 265.737, 0 )) && (zone == 1))
		{
			PRINT_HELP_FOREVER("RCH1_12"); //~g~The RC helicopter is getting too far out of range!
			zone = 0;
		}
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1461.723, -952.569, -15.613, -642.161, -133.007, 265.737, 0 )) && (zone == 0))
		{
			CLEAR_HELP(); // ������� ����� ���������
			zone = 1;
		}

		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, checkX, checkY, checkZ, &PlayR);//�������� "����� �� �����������"
		//��������� ���:
		if (PlayR < 3.1)
		{
			check_cord +=1;
			PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
			if (check_cord == 2)
			{
				checkX = -974.7137;
				checkY =-743.5944;
				checkZ = 18.04353;
				checkX2 = -1041.338;
				checkY2 =-714.527;
				checkZ2 = 10.83702;
			}
			else if (check_cord == 3)
			{
				checkX = -1041.338;
				checkY =-714.527;
				checkZ = 10.83702;
				checkX2 = -1140.803;
				checkY2 =-706.6136;
				checkZ2 = 16.81559;

			}
			else if (check_cord == 4)
			{

				checkX = -1140.803;
				checkY =-706.6136;
				checkZ = 16.81559;
				checkX2 = -1255.231;
				checkY2 =-746.2191;
				checkZ2 = 31.20518;

			}
			else if (check_cord == 5)
			{
				checkX = -1255.231;
				checkY =-746.2191;
				checkZ = 31.20518;
				checkX2 = -1352.514;
				checkY2 =-810.9379;
				checkZ2 = 10.78206;

			}
			else if (check_cord == 6)
			{

				checkX = -1352.514;
				checkY =-810.9379;
				checkZ = 10.78206;
				checkX2 = -1364.708;
				checkY2 =-531.7391;
				checkZ2 = 10.78206;

			}
			else if (check_cord == 7)
			{
				checkX = -1364.708;
				checkY =-531.7391;
				checkZ = 10.78206;
				checkX2 = -1366.11;
				checkY2 =-375.3282;
				checkZ2 = 10.78206;

			}
			else if (check_cord == 8)
			{
				checkX = -1366.11;
				checkY =-375.3282;
				checkZ = 10.78206;
				checkX2 = -1354.401;
				checkY2 =-347.5585;
				checkZ2 = 51.24453;
			}
			else if (check_cord == 9)
			{
				checkX = -1354.401;
				checkY =-347.5585;
				checkZ = 51.24453;
				checkX2 = -1252.155;
				checkY2 =-390.4126;
				checkZ2 = 47.34144;
			}
			else if (check_cord == 10)
			{
				checkX = -1252.155;
				checkY =-390.4126;
				checkZ = 47.34144;
				checkX2 = -1251.412;
				checkY2 =-569.964;
				checkZ2 = 14.44249;
			}
			else if (check_cord == 11)
			{
				checkX = -1251.412;
				checkY =-569.964;
				checkZ = 14.44249;
				checkX2 = -1161.167;
				checkY2 =-439.1681;
				checkZ2 = 30.12179;
			}
			else if (check_cord == 12)
			{
				checkX = -1161.167;
				checkY =-439.1681;
				checkZ = 30.12179;
				checkX2 = -1056.566;
				checkY2 =-361.9299;
				checkZ2 = 21.99353;
			}
			else if (check_cord == 13)
			{
				checkX = -1056.566;
				checkY =-361.9299;
				checkZ = 21.99353;
				checkX2 = -919.8584;
				checkY2 =-223.728;
				checkZ2 = 20.10391;
			}
			else if (check_cord == 14)
			{
				checkX = -919.8584;
				checkY =-223.728;
				checkZ = 20.10391;
				checkX2 = -804.5237;
				checkY2 =-306.9036;
				checkZ2 = 18.80973;
			}
			else if (check_cord == 15)
			{
				checkX = -804.5237;
				checkY =-306.9036;
				checkZ = 18.80973;
				checkX2 = -879.7384;
				checkY2 =-427.131;
				checkZ2 = 10.78464;
			}
			else if (check_cord == 16)
			{
				checkX = -879.7384;
				checkY =-427.131;
				checkZ = 10.78464;
				checkX2 = -919.3431;
				checkY2 =-505.1696;
				checkZ2 = 19.31271; 
			}
			else if (check_cord == 17)
			{
				checkX = -919.3431;
				checkY =-505.1696;
				checkZ = 19.31271;
				checkX2 = -997.6587;
				checkY2 =-564.0671;
				checkZ2 = 30.15611;
			}
			else if (check_cord == 18)
			{
				checkX = -997.6587;
				checkY =-564.0671;
				checkZ = 30.15611;
				checkX2 = -855.8775;
				checkY2 =-644.0732;
				checkZ2 = 10.8591;
			}
			else if (check_cord == 19)
			{
				checkX = -855.8775;
				checkY =-644.0732;
				checkZ = 10.8591;
				checkX2 = -835.2156;
				checkY2 =-747.3368;
				checkZ2 = 10.77548;
			}
			else if (check_cord == 20)
			{
				checkX = -835.2156;
				checkY =-747.3368;
				checkZ = 10.77548;
				checkX2 = -835.2156;
				checkY2 =-747.3368;
				checkZ2 = 15.77548;
			}
			else if (check_cord == 21)
			{
				TRIGGER_MISSION_COMPLETE_AUDIO(1);//����������� ������ �������� "(1)" ������������� ���� �� "...\EFLC\pc\audio\Sfx\gps.rpf\GPS\MISSION_COMPLETE_1" (����� "6" = "SMC6" � ���-�� ������) 
				skip = 2;
				break;
			}
			
			if (check_cord == 20)
			{
				REMOVE_BLIP(Blip_r);//������� ������ �� ������
				REMOVE_BLIP(Blip_r2);//������� ������ �� ������
				DELETE_CHECKPOINT(checkpoint);
				checkpoint = CREATE_CHECKPOINT( 5, checkX, checkY, checkZ, checkX2, checkY2, checkZ2, 0.20000000 );
				ADD_BLIP_FOR_COORD(checkX, checkY, checkZ, &Blip_r);//������� ������ �� ������ � ���������� "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r, 5);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//������ �� ������ "Blip01" ��������� � ������� �����
				CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // ������� ������ �� ������
			}
			else
			{
				REMOVE_BLIP(Blip_r);//������� ������ �� ������
				REMOVE_BLIP(Blip_r2);//������� ������ �� ������
				DELETE_CHECKPOINT(checkpoint);
				checkpoint = CREATE_CHECKPOINT( 4, checkX, checkY, checkZ, checkX2, checkY2, checkZ2, 0.20000000 );
				ADD_BLIP_FOR_COORD(checkX, checkY, checkZ, &Blip_r);//������� ������ �� ������ � ���������� "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r, 5);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//������ �� ������ "Blip01" ��������� � ������� �����
				CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // ������� ������ �� ������

				ADD_BLIP_FOR_COORD(checkX2, checkY2, checkZ2, &Blip_r2);//������� ������ �� ������ � ���������� "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r2, 5);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//������ �� ������ "Blip01" ��������� � ������� �����
				CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // ������� ������ �� ������
				CHANGE_BLIP_ALPHA(Blip_r2, 125);
			}
		}
	}
	CLEAR_HELP(); // ������� ����� ���������
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������

	REMOVE_BLIP(Blip_r);//������� ������ �� ������
	REMOVE_BLIP(Blip_r2);//������� ������ �� ������
	DELETE_CHECKPOINT(checkpoint);
	
	//���������� ������ �� ������
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, -800.605, -700.893, 8.468 ); // ���� ������� ������
	SET_CAM_POS			( camera, -800.398, -688.654, 12.657 );//������������ ������
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CAM_FOV( camera, 45.0 );
	SET_WIDESCREEN_BORDERS( 1 );
	WARP_CHAR_INTO_CAR(GetPlayerPed(), car1);
	SetTime(1500);

	//������������� �������� ������ �� ������ ���� �������
	REQUEST_ANIMS( "ne_topfun" );//��������� ���� � ���������
	while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_in", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//���������������� �������� �� ����
	SetTime(500);
	TURN_OFF_VEHICLE_EXTRA( car1, 9, 1 );//��������� �����
	SET_CHAR_VISIBLE(GetPlayerPed(), 1); //���������� �����
	SetTime(1000);

	SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// ������ ���������� ����
	SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// ����� �����������
	SET_CAR_COORDINATES_NO_OFFSET(goblin, 0.9, 0.9, 0.9);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
	MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
	MARK_CAR_AS_NO_LONGER_NEEDED(&goblin);//��������� ������ ������(� ����������� ������ ��������)
	SetTime(1000);

	SET_CAM_BEHIND_PED( GetPlayerPed() );
	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	END_CAM_COMMANDS( &camera );
	SET_WIDESCREEN_BORDERS( 0 );
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������ ������
}

void main(void)
{
	CLEAR_HELP(); // ������� ����� ���������
	LOAD_ADDITIONAL_TEXT("RCHELI1", 6);
	rc_raider();

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
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 100);// +5000$
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
		G_RC_1 += 1;
		if (time_s >= 10) {
			PRINT_WITH_2_NUMBERS_NOW("RCH1_9", time_m, time_s, 7000, 1);
		} else {
			PRINT_WITH_2_NUMBERS_NOW("RCH1_10", time_m, time_s, 7000, 1);
		}
		ADD_SCORE( GetPlayerIndex(), +100 );//��� ������ �����
	}
	TERMINATE_THIS_SCRIPT();
}
