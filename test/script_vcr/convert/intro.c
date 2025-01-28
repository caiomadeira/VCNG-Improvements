/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float PlayX, PlayY, PlayZ, PlayR, help_1, set_txd, language, textur, alpha, set_in;


void SetCut(uint time)
{
	SETTIMERA( 0 );
	DO_SCREEN_FADE_IN( 1 );// ��������� ���������� ������
	while(true)
	{
		WAIT(0);
		DRAW_MOVIE( 0.50000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 255, 255, 255, 255 );
		if ((IS_GAME_KEYBOARD_KEY_PRESSED(GAME_KEY_ESC)) || (TIMERA() > time) || (IS_GAME_KEYBOARD_KEY_PRESSED(57)) || (IS_GAME_KEYBOARD_KEY_PRESSED(42)) || (IS_GAME_KEYBOARD_KEY_PRESSED(54)) ||(IS_GAME_KEYBOARD_KEY_PRESSED(28)))
		{
			DO_SCREEN_FADE_OUT( 50 );// ��������� �����
			while(true)
			{
				WAIT(0);
				DRAW_MOVIE( 0.50000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 0, 0, 0, 255 );
				if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������, ���� ����� ����������
				{
					break;
				}
			}
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

void INTRO(void)
{
	WAIT(500);

	//============================== Intro ======================================
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
	SET_CAR_DENSITY_MULTIPLIER(0);// ��������� ����
	uint CarM1 = MODEL_ADMIRAL;
	uint CarM2 = MODEL_CABBY;
	uint CarM3 = MODEL_SENTINEL;
	uint CarM4 = MODEL_COQUETTE;
	uint CarM5 = MODEL_TAXI;
	uint PedM1 = MODEL_IG_ROMAN;// ���������
	uint AudID;
	Car car1, car2, car3, car4, car5, car6;
	Ped ped1, ped2, ped3, ped4, ped5, ped6;
	Cam camera;
	Blip hotel;
	Texture intro_1, intro_2, intro_3, intro_4;
	help_1 = 0;
	set_txd = 1;
	G_ONMISSION = 1;

	language = GET_CURRENT_LANGUAGE();
	if (language == 0)
	{
		textur = LOAD_TXD( "intro_en" );
	}
	else if (language == 5)
	{
		textur = LOAD_TXD( "intro_ru" );
	}
	else
	{
		textur = LOAD_TXD( "intro_user" );
	}
	intro_1 = GET_TEXTURE( textur, "Intro_1" );
	intro_2 = GET_TEXTURE( textur, "Intro_2" );
	intro_3 = GET_TEXTURE( textur, "Intro_3" );
	intro_4 = GET_TEXTURE( textur, "Intro_4" );

//------------ �������� ���������� ----------------
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

    //CREATE_CAR(CarM1, 555.13, -304.68, 5.41, &car1, TRUE);
	//SET_CAR_HEADING(car1, 15.31);
	CREATE_CAR(CarM1, -1154.64,-13.088,9.37876, &car1, TRUE);
	CHANGE_CAR_COLOUR( car1, 112, 112 );//���� ������
	SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//���� ��������� ������

	SET_CHAR_COORDINATES(GetPlayerPed(), -253.936, -1031.04, 6.83345);// ���������� ������
	CREATE_CAR(CarM2, -1095.01,-40.467,8.37876, &car2, TRUE);
	CREATE_CAR(CarM3, -1213.33,-18.8215,8.37876, &car3, TRUE);
	CREATE_CAR(CarM4, -1094.52,-53.372,8.37876, &car4, TRUE);
	CREATE_CAR(CarM5, -1230.08,-18.8337,8.37876, &car5, TRUE);
	CREATE_CAR(CarM2, -1178.44,-18.8215,8.37876, &car6, TRUE);
	SET_CAR_HEADING(car1, 90.633);
	SET_CAR_HEADING(car2, 0.633);
	SET_CAR_HEADING(car3, -90.0);
	SET_CAR_HEADING(car4, 0.633);
	SET_CAR_HEADING(car5, -90.0);
	SET_CAR_HEADING(car6, -90.0);

//------------ �������� �������� ----------------
	REQUEST_MODEL(PedM1);//
	while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
	CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//������ ���� �� ���� ����������
	CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped2);//������ ���� �� ���� ����������
	CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);//������ ���� �� ���� ����������
	CREATE_CHAR_INSIDE_CAR(car4, 1, PedM1, &ped4);//������ ���� �� ���� ����������
	CREATE_CHAR_INSIDE_CAR(car5, 1, PedM1, &ped5);//������ ���� �� ���� ����������
	CREATE_CHAR_INSIDE_CAR(car6, 1, PedM1, &ped6);//������ ���� �� ���� ����������
	CHANGE_CAR_COLOUR( car1, 112, 66 );//���� ������
	SET_EXTRA_CAR_COLOURS( car1, 0, 0 );//���� ������

//------------ �������� ����� ----------------
	REQUEST_CAR_RECORDING( 2992 );
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 2992 )) WAIT(0);
	FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);

//------------ �������� ��� ----------------
	LOAD_ADDITIONAL_TEXT( "INT_A", 6 ); // ��������� �������� �� *.GTX
	FORWARD_TO_TIME_OF_DAY(20, 0);//������������� �����
	START_CUTSCENE_NOW("int_a");
	while (!HAS_CUTSCENE_LOADED())
	{
		WAIT(0);
	}
	FORCE_LOADING_SCREEN(FALSE);
	DO_SCREEN_FADE_IN_UNHACKED(4000);
	DO_SCREEN_FADE_IN(0);
	SETTIMERB( 0 );
	SETTIMERC( 0 );
	alpha = 0;
	set_in = 1;
	while (!HAS_CUTSCENE_FINISHED())
	{
		WAIT(0);
		if (TIMERB() < 9000)
		{
			if ((set_in == 1) && (TIMERB() > 1500))
			{
				if (TIMERC() > 1)
				{
					if (alpha < 253)
					{
						alpha += 2;
					}
					else
					{
						alpha = 254;
						set_in = 0;
					}
					SETTIMERC( 0 );
				}
			}
			if (TIMERB() > 6000)
			{
				if (TIMERC() > 1)
				{
					if (alpha > 1) alpha -= 2;
					SETTIMERC( 0 );
				}
			}
			DRAW_SPRITE( intro_1, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, alpha );// ������ ������� ��������.
		}
	}
	LOAD_ADDITIONAL_TEXT( "INT_M", 6 ); // ��������� �������� �� *.GTX
	FORWARD_TO_TIME_OF_DAY(6, 0);//������������� �����
	START_CUTSCENE_NOW("int_m");
	while (!HAS_CUTSCENE_LOADED())
	{
		WAIT(0);
	}

	SET_CAR_IN_CUTSCENE(car2, 1);
	SET_CAR_IN_CUTSCENE(car3, 1);
	SET_CAR_IN_CUTSCENE(car4, 1);
	SET_CAR_IN_CUTSCENE(car5, 1);
	SET_CAR_IN_CUTSCENE(car6, 1);
	TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -1230.64,-13.5635,8.37876, 4, 5.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
	TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -1094.69,-133.733,8.37876, 4, 5.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
	TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -1222.18,-13.5635,8.37876, 4, 5.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
	TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped5, car5, -1095.01,-127.779,8.37876, 4, 5.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
	TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car6, -1094.69,-141.077,8.37876, 4, 5.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)

	DO_SCREEN_FADE_IN(0);
	SETTIMERB( 0 );
	SETTIMERC( 0 );
	alpha = 0;
	set_in = 1;
	while (!HAS_CUTSCENE_FINISHED())
	{
		WAIT(0);
		if (TIMERB() < 9000)
		{
			if ((set_in == 1) && (TIMERB() > 1500))
			{
				if (TIMERC() > 1)
				{
					if (alpha < 253)
					{
						alpha += 2;
					}
					else
					{
						alpha = 254;
						set_in = 0;
					}
					SETTIMERC( 0 );
				}
			}
			if (TIMERB() > 6000)
			{
				if (TIMERC() > 1)
				{
					if (alpha > 1) alpha -= 2;
					SETTIMERC( 0 );
				}
			}
			DRAW_SPRITE( intro_2, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, alpha );// ������ ������� ��������.
		}
	}
	LOAD_ADDITIONAL_TEXT( "INT_D", 6 ); // ��������� �������� �� *.GTX
	FORWARD_TO_TIME_OF_DAY(6, 30);//������������� �����
	START_CUTSCENE_NOW("int_d");

	while (!HAS_CUTSCENE_LOADED())
	{
		WAIT(0);
	}

	DO_SCREEN_FADE_IN(0);
	SETTIMERB( 0 );
	SETTIMERC( 0 );
	alpha = 0;
	set_in = 1;
	while (!HAS_CUTSCENE_FINISHED())
	{
		WAIT(0);
		if (TIMERB() < 9000)
		{
			if ((set_in == 1) && (TIMERB() > 1500))
			{
				if (TIMERC() > 1)
				{
					if (alpha < 253)
					{
						alpha += 2;
					}
					else
					{
						alpha = 254;
						set_in = 0;
					}
					SETTIMERC( 0 );
				}
			}
			if (TIMERB() > 6000)
			{
				if (TIMERC() > 1)
				{
					if (alpha > 1) alpha -= 2;
					SETTIMERC( 0 );
				}
			}
			DRAW_SPRITE( intro_3, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, alpha );// ������ ������� ��������.
		}
	}
	
	if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
	{
		DO_SCREEN_FADE_IN(0);
	}
	// ����� �����
	SET_CAR_COORDINATES(car1, 555.13, -304.68, 5.41);// ���������� ������
	TASK_ENTER_CAR_AS_PASSENGER(GetPlayerPed(), car1, 1, 1);
	MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
	SET_CURRENT_MOVIE( "GTAtitles" );
	PLAY_MOVIE();
	SetCut (79000);
	RETUNE_RADIO_TO_STATION_NAME( "BOBBY_KONDERS" );
	MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
	STOP_STREAM();//������������� ��������
	RELEASE_MOVIE();//������������� �� �����
	//*/
	DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������

//------------------------------------------
	RELEASE_WEATHER();
	FORWARD_TO_TIME_OF_DAY(19, 45);//������������� �����
	CLEAR_AREA(555.13, -304.68, 5.41, 80.5, 1);//������� ���� ��������
	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2992, 0.0, 0.0, 0.0);
	SET_PLAYBACK_SPEED(car1, 1.15);

	NEW_SCRIPTED_CONVERSATION();
	ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
	ADD_LINE_TO_CONVERSATION(0, "R1_AA", "INTRO1", 0, 0);//I poke my head out of the gutter for one freakin' second and fate shovels shit in my face!
	START_SCRIPT_CONVERSATION(1, 1);

//------------ ������ 1 ----------------
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, 116.573+433, -797.821+533, 11.414-6 ); // ���� ������� ������
	SET_CAM_POS			( camera, 116.583+433, -796.821+533, 11.423-6 );//������������ ������
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CAM_FOV( camera, 45.0 );
	SET_WIDESCREEN_BORDERS( 1 );

	SETTIMERA( 0 );
	SETTIMERB( 0 );
	SETTIMERC( 0 );
	alpha = 254;

	while(true)
	{
		WAIT(0);
		if ((TIMERA() > 2000) && (set_txd == 1))
		{
			//------------ ������ 2 ----------------
			POINT_CAM_AT_COORD	( camera, 105.771+433, -808.888+533, 12.091-6 ); // ���� ������� ������
			SET_CAM_POS			( camera, 104.88+433, -808.433+533, 12.108-6 );//������������ ������
			SETTIMERA( 0 );
			set_txd = 2;
		}
		else if ((TIMERA() > 3000) && (set_txd == 2))
		{
			break;
		}

		if (TIMERB() < 5000)
		{
			if (TIMERB() > 2000)
			{
				if (TIMERC() > 3)
				{
					if (alpha > 1) alpha -= 2;
					SETTIMERC( 0 );
				}
			}
			DRAW_SPRITE( intro_4, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, alpha );// ������ ������� ��������.
		}
	}
	SetSpeech();

//------------ ������ 3 ----------------

	NEW_SCRIPTED_CONVERSATION();
	ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
	ADD_LINE_TO_CONVERSATION(0, "R1_BA", "INTRO2", 0, 0);//Go get some sleep.
	START_SCRIPT_CONVERSATION(1, 1);
	SetSpeech();

	NEW_SCRIPTED_CONVERSATION();
	ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
	ADD_LINE_TO_CONVERSATION(0, "R1_BB", "INTRO3", 0, 0);//What are you gonna do?
	START_SCRIPT_CONVERSATION(1, 1);
	SetSpeech();

	NEW_SCRIPTED_CONVERSATION();
	ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
	ADD_LINE_TO_CONVERSATION(0, "R1_BC", "INTRO4", 0, 0);//I'll drop by your office tomorrow and we can start sorting this mess out.
	START_SCRIPT_CONVERSATION(1, 1);
	SetSpeech();

	CLEAR_PRINTS();
	TASK_LEAVE_CAR(ped1, car1);
	TASK_GO_STRAIGHT_TO_COORD(ped1, 551.715, -291.361, 5.398, 4, -2);
	SetTime(3000);

	WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 568.261, -284.221, 5.156);//������������� �� ������
	SET_CHAR_HEADING(GetPlayerPed(), 210.0);

	POINT_CAM_AT_COORD	( camera, 114.307+433, -816.57+533, 11.083-6 ); // ���� ������� ������
	SET_CAM_POS			( camera, 113.655+433, -815.814+533, 11.029-6 );//������������ ������
	STOP_PLAYBACK_RECORDED_CAR(car1);
	SET_CHAR_COORDINATES(ped1, 562.961, -278.867, 4.567);// ���������� ����
	SET_CHAR_HEADING(ped1, 133.0);
	TASK_GO_STRAIGHT_TO_COORD(ped1, 548.288, -290.367, 5.398, 4, -2);
	CLOSE_ALL_CAR_DOORS(car1);

	SetTime(2000);
	SET_CAR_DENSITY_MULTIPLIER(1);// ���������� ����
	SET_CAM_BEHIND_PED( GetPlayerPed() );
	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	DESTROY_CAM( camera );
	SET_WIDESCREEN_BORDERS( 0 );
	REMOVE_CAR_RECORDING( 2992 );

	SET_CHAR_COORDINATES(ped1, 5.13, -3.68, 10.41);// ���������� ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����

	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������)
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);
	MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&car2);
	MARK_CAR_AS_NO_LONGER_NEEDED(&car3);
	MARK_CAR_AS_NO_LONGER_NEEDED(&car4);
	MARK_CAR_AS_NO_LONGER_NEEDED(&car5);
	MARK_CAR_AS_NO_LONGER_NEEDED(&car6);
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

	//------------------ ��������� ��� -------------
	SetTime(3000);
	PRINT_HELP_FOREVER("HELP42"); // Follow the ~p~pink blip~w~ to find the hotel.

	ADD_BLIP_FOR_COORD(671.029, -747.042, 4.934, &hotel);//������� ������ �� ������
	CHANGE_BLIP_SPRITE(hotel, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(hotel, 5);   //���� ������ �� ������ (0=�����)
	CHANGE_BLIP_SCALE(hotel, 0.6); // ������� ������ �� ������
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(hotel, "NE_POINT");//������ �� ������ ��������� � ������� ����� "����"

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
	CLEAR_HELP(); // ������� ����� ���������

	
	//��������� �������������� ���
	SetTime(5000);
	PRINT_HELP_FOREVER("BRID_CL"); // Storm warning: All bridges to the mainland are closed.
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if ((TIMERA() > 3000) && (help_1 == 0))
		{
			CLEAR_HELP(); // ������� ����� ���������
			SETTIMERA( 0 );
			help_1 = 1;
		}
		else if ((TIMERA() > 10000) && (help_1 == 1))
		{
			help_1 = 0;
			break;
		}

		if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
		{
			DISABLE_FRONTEND_RADIO();
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
			ADD_LINE_TO_CONVERSATION(0, "R1_BD", " ", 0, 0);//
			START_SCRIPT_CONVERSATION(1, 1);
			help_1 = 1;

			SETTIMERA( 0 );
			while(true)
			{
				WAIT(0);
				if ((TIMERA() > 3000) && (help_1 == 1))
				{
					CLEAR_HELP(); // ������� ����� ���������
					help_1 = 0;
				}
				if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
				{
					ABORT_SCRIPTED_CONVERSATION( 0 );
					break;
				}
				else if (!IS_SCRIPTED_CONVERSATION_ONGOING())
				{
					break;
				}
			}
			ENABLE_FRONTEND_RADIO();
			CLEAR_HELP(); // ������� ����� ���������
			help_1 = 0;
			break;
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 659.314, -785.552, 1.332, 705.314, -709.552, 30.135, 0 ))
		{
			CLEAR_HELP(); // ������� ����� ���������
			help_1 = 0;
			break;
		}
	}

	//------------------ ������ ������ -------------

	while (TRUE)
	{
		WAIT(0);
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 657.314, -787.552, 3.332, 707.314, -707.552, 28.135, 0 )) && (help_1 == 0))
		{
			help_1 = 1;
			PRINT_HELP("HELP44"); // Stop in the ~p~pink marker.
			SETTIMERA( 0 );
		}
		if (help_1 == 1)
		{
			if (TIMERA() > 3000)
			{
				CLEAR_HELP(); // ������� ����� ���������
				help_1 = 2;
			}
		}

		DRAW_CHECKPOINT( 671.029, -747.042, 4.934, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 671.029, -747.042, 4.934, &PlayR);//�������� "����� �� �����������"
		if ( PlayR < 1.3 )
		{
			// ������ ���
			REMOVE_BLIP(hotel);//������� ������ �� ������
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
			CREATE_CAM( 14, &camera );
			POINT_CAM_AT_COORD	( camera, 263.577+433, -1310.574+533, 10.589-5  ); // ���� ������� ������
			SET_CAM_POS			( camera, 264.334+433, -1311.161+533, 10.297-5 );//������������ ������
			SET_CAM_ACTIVE( camera, 1 );
			SET_CAM_PROPAGATE( camera, 1 );
			ACTIVATE_SCRIPTED_CAMS(1, 1);
			SET_CAM_FOV( camera, 45.0 );
			SET_WIDESCREEN_BORDERS( 1 );
			
			PRINT_HELP_FOREVER("HELP16"); // Walk through the front door of the ~m~Ocean View~w~ Hotel to enter the building.
			SetTime(4000);
			CLEAR_HELP(); // ������� ����� ���������

			SET_CAM_BEHIND_PED( GetPlayerPed() );
			ACTIVATE_SCRIPTED_CAMS( 0, 0 );
			DESTROY_CAM( camera );
			SET_WIDESCREEN_BORDERS( 0 );
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������

			ADD_BLIP_FOR_COORD(642.789, -755.855, 5.974, &hotel);//������� ������ �� ������
			CHANGE_BLIP_SPRITE(hotel, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
			CHANGE_BLIP_COLOUR(hotel, 5);   //���� ������ �� ������ (0=�����)
			CHANGE_BLIP_SCALE(hotel, 0.6); // ������� ������ �� ������
			CHANGE_BLIP_NAME_FROM_TEXT_FILE(hotel, "NE_POINT");//������ �� ������ ��������� � ������� ����� "����"
			break;
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 656.296, -748.324, 4.946, 660.846, -740.824, 11.446, 0 ))
		{
			// ������ � �����
			REMOVE_BLIP(hotel);//������� ������ �� ������
			ADD_BLIP_FOR_COORD(642.789, -755.855, 5.974, &hotel);//������� ������ �� ������
			CHANGE_BLIP_SPRITE(hotel, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
			CHANGE_BLIP_COLOUR(hotel, 5);   //���� ������ �� ������ (0=�����)
			CHANGE_BLIP_SCALE(hotel, 0.6); // ������� ������ �� ������
			CHANGE_BLIP_NAME_FROM_TEXT_FILE(hotel, "NE_POINT");//������ �� ������ ��������� � ������� ����� "����"
			break;
		}
	}
	while (TRUE)
	{
		WAIT(0);
		DRAW_CHECKPOINT( 642.789, -755.855, 5.974, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 656.296, -748.324, 4.946, 660.846, -740.824, 11.446, 0 ))
		{
			// ������ ���
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
			CREATE_CAM( 14, &camera );
			POINT_CAM_AT_COORD	( camera, 642.625, -755.805, 6.653  ); // ���� ������� ������
			SET_CAM_POS			( camera, 657.751, -739.661, 8.751 );//������������ ������
			SET_CAM_ACTIVE( camera, 1 );
			SET_CAM_PROPAGATE( camera, 1 );
			ACTIVATE_SCRIPTED_CAMS(1, 1);
			SET_CAM_FOV( camera, 45.0 );
			SET_WIDESCREEN_BORDERS( 1 );
			
			PRINT_HELP_FOREVER("HELP19");  // Walk into the ~p~pink marker ~w~to continue.
			SETTIMERA( 0 );
			while(true)
			{
				WAIT(0);
				DRAW_CHECKPOINT( 642.789, -755.855, 5.974, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
				if (TIMERA() > 3000)
				{
					break;
				}
			}
			CLEAR_HELP(); // ������� ����� ���������
			SET_CAM_BEHIND_PED( GetPlayerPed() );
			ACTIVATE_SCRIPTED_CAMS( 0, 0 );
			DESTROY_CAM( camera );
			SET_WIDESCREEN_BORDERS( 0 );
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
			break;
		}
	}
	//----------------------------------------------

	//============================== An Old Friend ======================================
	while (TRUE)
	{
		WAIT(0);
		DRAW_CHECKPOINT( 642.789, -755.855, 5.974, 1.3, 246, 151, 255);//�������� �������� �� ����������� � ��� ����
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 642.789, -755.855, 5.974, &PlayR);//�������� "����� �� �����������"
		if ( PlayR < 1.8 )
		{
			REMOVE_BLIP(hotel);//������� ������ �� ������
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
			ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
			APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
			// ������ ���
			CREATE_CAM( 14, &camera );
			POINT_CAM_AT_COORD	( camera, 641.511, -756.154, 6.713  ); // ���� ������� ������
			SET_CAM_POS			( camera, 647.924, -752.37, 6.9967 );//������������ ������
			SET_CAM_ACTIVE( camera, 1 );
			SET_CAM_PROPAGATE( camera, 1 );
			ACTIVATE_SCRIPTED_CAMS(1, 1);
			SET_CAM_FOV( camera, 45.0 );
			SET_WIDESCREEN_BORDERS( 1 );

			// ����� ����������� �� ��������
			TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 637.021, -754.877, 8.832, 2, -2);
			SetTime(500);

			// ����������
			DO_SCREEN_FADE_OUT( 1000 );// ��������� �����
			while(true)
			{
				WAIT(0);
				if (IS_SCREEN_FADED_OUT())
				{
					break;
				}
			}
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
			SET_CHAR_COORDINATES(GetPlayerPed(), 660.337, -733.43, 14.48);// ���������� ������
			SET_CHAR_HEADING(GetPlayerPed(), 0.1);

			//------------ �������� ----------------
			LOAD_ADDITIONAL_TEXT( "INT_B", 6 ); // ��������� �������� �� *.GTX
			FORWARD_TO_TIME_OF_DAY(19, 0);//������������� �����
			FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
			START_CUTSCENE_NOW("int_b");
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

			FORWARD_TO_TIME_OF_DAY(7, 30);//������������� �����
			RELEASE_WEATHER();
			DO_SCREEN_FADE_IN( 1000 );// ��������� ���������� ������
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );

			POINT_CAM_AT_COORD	( camera, 660.537, -729.304, 14.183  ); // ���� ������� ������
			SET_CAM_POS			( camera, 663.181, -734.941, 16.065 );//������������ ������
			PRINT_HELP_FOREVER("NEHELP1");  // Sleeping on the bed will save the game and advance time by six hours.
			SetTime(5000);
			CLEAR_HELP(); // ������� ����� ���������

			SET_CAM_BEHIND_PED( GetPlayerPed() );
			ACTIVATE_SCRIPTED_CAMS( 0, 0 );
			DESTROY_CAM( camera );
			SET_WIDESCREEN_BORDERS( 0 );
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
			G_LAWYER = 1;
			G_ONMISSION = 0;
			break;
		}
	}

	while (TRUE)
	{
		WAIT(0);
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 662.581, -750.27, 5.496, 667.581, -740.27, 10.496, 0 ))
		{
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
			CREATE_CAM( 14, &camera );
			POINT_CAM_AT_COORD	( camera, 679.021, -723.314, 5.507  ); // ���� ������� ������
			SET_CAM_POS			( camera, 690.751, -711.325, 9.127 );//������������ ������
			SET_CAM_ACTIVE( camera, 1 );
			SET_CAM_PROPAGATE( camera, 1 );
			ACTIVATE_SCRIPTED_CAMS(1, 1);
			SET_CAM_FOV( camera, 45.0 );
			SET_WIDESCREEN_BORDERS( 1 );
			
			PRINT_HELP_FOREVER("CARSAVE");  // You can save any vehicle in the parking spot outside your safehouse. Park your car there and exit it. The car will remain there for you to use.
			SetTime(5000);
			CLEAR_HELP(); // ������� ����� ���������

			SET_CAM_BEHIND_PED( GetPlayerPed() );
			ACTIVATE_SCRIPTED_CAMS( 0, 0 );
			DESTROY_CAM( camera );
			SET_WIDESCREEN_BORDERS( 0 );
			SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//������������� ������
			break;
		}
		else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 627.417, -777.408, 3.332, 677.166, -710.844, 40.07, 0 ))
		{
			break;
		}
	}
	SetTime(1000);
	PRINT_HELP("CLOTH2"); //Street outfit delivered to Safehouses.
	SetTime(3000);
	CLEAR_HELP(); // ������� ����� ���������
	PRINT_HELP("HELP14"); // To find the Lawyer's office, follow the ~h~L blip~w~ on the radar
	SetTime(5000);
	if (G_ONMISSION == 0)
	{
		G_SAVE_SAVED = 16; // ����� ����� 
		G_SAVE_OCCURED = TRUE;
		DO_AUTO_SAVE();
		WAIT(500);
		if (DID_SAVE_COMPLETE_SUCCESSFULLY())
		{
			G_SAVE_OCCURED = FALSE;
		}
	}
}
void load_screen(void)
{
	FORCE_LOADING_SCREEN(FALSE);
	DO_SCREEN_FADE_IN_UNHACKED(4000);
	DO_SCREEN_FADE_IN(0);
}
void main(void)
{
	WAIT(2000);
	//G_LAWYER = 1; // ��������� �����	
	//load_screen(); // ��������� �����
	REGISTER_MISSION_PASSED( "NESAVE_GM" );
	if (G_LAWYER == 0)
	{
		INTRO();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
