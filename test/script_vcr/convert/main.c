/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

Pickup tweap_1, tweap_2;
uint lawyer_n, Ammo_nan;
uint Weap1, Weap1_2, get_Weap1, Ammo1_1, Ammo1_2;
uint Weap2, Weap2_2, get_Weap2, Ammo2_1, Ammo2_2;
uint Weap3, Weap3_2, get_Weap3, Ammo3_1, Ammo3_2;
uint Weap4, Weap4_2, get_Weap4, Ammo4_1, Ammo4_2;
uint Weap5, Weap5_2, get_Weap5, Ammo5_1, Ammo5_2;
uint Weap6, Weap6_2, get_Weap6, Ammo6_1, Ammo6_2;
uint Weap7, Weap7_2, get_Weap7, Ammo7_1, Ammo7_2;
uint Weap8, Weap8_2, get_Weap8, Ammo8_1, Ammo8_2;
uint Weap9, Weap9_2, get_Weap9, Ammo9_1, Ammo9_2;
uint Weap0, Weap0_2, get_Weap0, Ammo0_1, Ammo0_2;
float cop_X, cop_Y, cop_Z, cop_R;


void res_skin(void)
{
	CHANGE_PLAYER_MODEL(GetPlayerIndex(), 1862763509);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 2, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 3, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 4, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 5, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 6, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 8, 0, 0);
}
void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// поверка игрок мёртв/арестован
		{
			break;
		}
	}
}
void get_weap(int ID_scan)
{
	WAIT(0);
	//получить оружие
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 1, &get_Weap1, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 2, &get_Weap2, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 3, &get_Weap3, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 4, &get_Weap4, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 5, &get_Weap5, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &get_Weap6, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 7, &get_Weap7, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 8, &get_Weap8, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 9, &get_Weap9, &Ammo_nan, &Ammo_nan);
	GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 0, &get_Weap0, &Ammo_nan, &Ammo_nan);

	if (ID_scan == 1)
	{
		if (get_Weap1 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 1, &Weap1, &Ammo1_1, &Ammo_nan);
		}
		if (get_Weap2 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 2, &Weap2, &Ammo2_1, &Ammo_nan);
		}
		if (get_Weap3 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 3, &Weap3, &Ammo3_1, &Ammo_nan);
		}
		if (get_Weap4 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 4, &Weap4, &Ammo4_1, &Ammo_nan);
		}
		if (get_Weap5 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 5, &Weap5, &Ammo5_1, &Ammo_nan);
		}
		if (get_Weap6 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap6, &Ammo6_1, &Ammo_nan);
		}
		if (get_Weap7 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 7, &Weap7, &Ammo7_1, &Ammo_nan);
		}
		if (get_Weap8 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 8, &Weap8, &Ammo8_1, &Ammo_nan);
		}
		if (get_Weap9 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 9, &Weap9, &Ammo9_1, &Ammo_nan);
		}
		if (get_Weap0 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 0, &Weap0, &Ammo0_1, &Ammo_nan);
		}
		if (DOES_PICKUP_EXIST(tweap_1))
		{
			REMOVE_PICKUP(tweap_1);// выгружаем оружие
		}
		CREATE_PICKUP_ROTATE(vc_weap_basket, 3, 0, 527.01, 799.434, 16.5562, 0.0, 0.0, 0.0, &tweap_1);//
	}
	else if ((ID_scan == 2) || (ID_scan == 3)) 
	{
		if (get_Weap1 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 1, &Weap1_2, &Ammo1_2, &Ammo_nan);
		}
		if (get_Weap2 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 2, &Weap2_2, &Ammo2_2, &Ammo_nan);
		}
		if (get_Weap3 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 3, &Weap3_2, &Ammo3_2, &Ammo_nan);
		}
		if (get_Weap4 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 4, &Weap4_2, &Ammo4_2, &Ammo_nan);
		}
		if (get_Weap5 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 5, &Weap5_2, &Ammo5_2, &Ammo_nan);
		}
		if (get_Weap6 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap6_2, &Ammo6_2, &Ammo_nan);
		}
		if (get_Weap7 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 7, &Weap7_2, &Ammo7_2, &Ammo_nan);
		}
		if (get_Weap8 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 8, &Weap8_2, &Ammo8_2, &Ammo_nan);
		}
		if (get_Weap9 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 9, &Weap9_2, &Ammo9_2, &Ammo_nan);
		}
		if (get_Weap0 != 0)
		{
			GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 0, &Weap0_2, &Ammo0_2, &Ammo_nan);
		}

		if (DOES_PICKUP_EXIST(tweap_2))
		{
			REMOVE_PICKUP(tweap_2);// выгружаем оружие
		}
		if (ID_scan == 2)
		{
			CREATE_PICKUP_ROTATE(vc_weap_basket, 3, 0, -974.819, -294.504, 8.84402, 0.0, 0.0, -135.0, &tweap_2);//
		}
		else if (ID_scan == 3)
		{
			CREATE_PICKUP_ROTATE(vc_weap_basket, 3, 0, -1026.69, -298.557, 8.84074, 0.0, 0.0, -40.0, &tweap_2);//
		}

	}
	REMOVE_ALL_CHAR_WEAPONS(GetPlayerPed());
	WAIT(100);
	while (TRUE) 
	{
		WAIT(0);
		if ((!IS_CHAR_IN_AREA_2D( GetPlayerPed(), 532.444, 799.818, 522.444, 801.818, 0 )) && (!IS_CHAR_IN_AREA_2D( GetPlayerPed(), -969.68, -304.184, -977.749, -295.524, 0 )) && (!IS_CHAR_IN_AREA_2D( GetPlayerPed(), -1027.328, -303.785, -1035.396, -295.124, 0 )))
		{
			break;
		}
	}
}
void hospital(void)
{
	while (TRUE) 
	{
		WAIT(0);
		if (!IS_CHAR_DEAD(GetPlayerPed())) 
		{
			break;
		}
	}
	res_skin();

	WAIT(100);
	if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), 166.465, -2264.458, -2886.127, 552.054, 0 )) && (G_DIAZ >= 3)) // игрок в зоне Гаваны
	{
		SET_CHAR_COORDINATES(GetPlayerPed(), -440.243, 62.9246, 5.29422);// Госпиталь Гаваны
		SET_CHAR_HEADING(GetPlayerPed(), -95.0);
	}
	else if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), 166.465, 552.054, -2886.127, 3735.542, 0 )) && (G_DIAZ >= 3)) // игрок в зоне Даунтауна
	{
		SET_CHAR_COORDINATES(GetPlayerPed(), -389.428, 1691.1, 5.29302);//Дебаг: Госпиталь Даунтауна
		SET_CHAR_HEADING(GetPlayerPed(), 0.0);
	}
	else if (IS_CHAR_IN_AREA_2D( GetPlayerPed(), 3113.873, 552.054, 166.465, 3735.542, 0 )) // игрок в зоне Вице пойнт
	{
		SET_CHAR_COORDINATES(GetPlayerPed(), 925.961, 1235.05, 6.33435);//Госпиталь Вице пойнт
		SET_CHAR_HEADING(GetPlayerPed(), 80.0);
	}
	else
	{
		SET_CHAR_COORDINATES(GetPlayerPed(), 320.068, -433.964, 4.70675);//Дебаг: Вашинктон Драйв
		SET_CHAR_HEADING(GetPlayerPed(), -85.0);
	}
	//DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
}
void lawyer(void)
{
	while (TRUE) 
	{
		WAIT(0);
		if (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))
		{
			break;
		}
	}
	res_skin();
	SET_CHAR_COORDINATES(GetPlayerPed(), cop_X, cop_Y, cop_Z);//Дебаг: Вашинктон Драйв
	SET_CHAR_HEADING(GetPlayerPed(), cop_R);
	SetTime(2000);
	GENERATE_RANDOM_INT_IN_RANGE( 1, 15, &lawyer_n);// рендомное число
	if ((lawyer_n == 1) || (lawyer_n == 6) || (lawyer_n == 11))
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_CA", "", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
	}
	else if ((lawyer_n == 2) || (lawyer_n == 7) || (lawyer_n == 12))
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_DA", "", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
	}
	else if ((lawyer_n == 3) || (lawyer_n == 8) || (lawyer_n == 13))
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_EA", "", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
	}
	else if ((lawyer_n == 4) || (lawyer_n == 9) || (lawyer_n == 14))
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_ZA", "", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
	}
	else if ((lawyer_n == 5) || (lawyer_n == 10) || (lawyer_n == 15))
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_AA", "", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
	}
}
void Superman(void)
{
	uint pid = GET_PLAYER_ID();
	if (pid >= 0)
	{
		if (IS_PLAYER_PLAYING(pid))
		{
			if (PLAYER_HAS_CHAR(pid))
			{
				Ped ped;
				GET_PLAYER_CHAR(pid, &ped);
				if (ped > 0)
				{

					UpdateWeaponOfPed(ped, WEAPON_KNIFE);
					UpdateWeaponOfPed(ped, WEAPON_MOLOTOV);
					UpdateWeaponOfPed(ped, WEAPON_DEAGLE);
					UpdateWeaponOfPed(ped, WEAPON_SHOTGUN);
					UpdateWeaponOfPed(ped, WEAPON_MP5);
					UpdateWeaponOfPed(ped, WEAPON_AK47);	
				}
			}
		}
	}
}

void CreateScript(char * name)
{
	REQUEST_SCRIPT(name);
	while ( !HAS_SCRIPT_LOADED(name) ) WAIT(0);
	uint script = START_NEW_SCRIPT(name, 1024);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED(name);	
}

void InitThisScript(void)
{
	int randint;
	GENERATE_RANDOM_INT(&randint);
	SET_RANDOM_SEED(randint);

	THIS_SCRIPT_SHOULD_BE_SAVED();
	SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(TRUE);
}
void InitScriptLauncher(void)
{
	CreateScript("loader_script");
}

void HideLoadingScreen(int time)
{
	FORCE_LOADING_SCREEN(FALSE);
	DO_SCREEN_FADE_IN_UNHACKED(time);
}
void main(void)
{
	int intHash;
	uint startOffset;
	bool isPlaying, stop_aud, inInterior, isVolChanged;
	float vol = 0.0;
	float delta;

	inInterior = 0;
	isPlaying = 0;
	isVolChanged = 0;
	stop_aud = 0;

	InitThisScript();
	UNLOCK_LAZLOW_STATION();

	G_ONMISSION = 0;
	G_COLLECTOR = 0;
	G_SECOND_ISLAND = 0;
	G_SALE_NO = 0;
	G_MAIN_CALL = 0;
	G_LANCE_CALL = 0;
	G_MERSEDES_CALL = 0;
	G_AVERY_CALL = 0;

	G_LAWYER = 0;
	G_BIKE = 0;
	G_COKERUN = 0;
	G_COUNT = 0;
	G_CUBAN = 0;
	G_DIAZ = 0;
	G_HAITI = 0;
	G_ICECREAM = 0;
	G_CABS = 0;
	G_CLUB = 0;
	G_PHIL = 0;
	G_PRON = 0;
	G_PROTECT = 0;
	G_ROCK = 0;
	G_STRIP = 0;
	G_BUSINES_SA = 0;
	G_ASSASSIN = 0;
	G_AVERY = 0;
	G_CORTEZ = 0;

	G_SWANKO = 0;
	G_LINKS = 0;
	G_CONDO = 0;
	G_HEIGHS = 0;
	G_WS_1102 = 0;
	G_VP_3321 = 0;
	G_SHACK = 0;

	G_BLOODRING = 0;
	G_HOTRING = 0;
	G_DIRTRING = 0;
	G_TAXI = 0;
	G_PIZZA = 0;
	G_MEDIC = 0;
	G_FIRE = 0;
	G_COPCAR = 0;
	G_HELI1SC = 0;
	G_BMX_1 = 0;
	G_CARPRK = 0;
	G_PCJ = 0;
	G_RC_1 = 0;
	G_JUMP = 0;
	G_PACKET = 0;
	G_SA_RACE = 0;

	SET_PLAYER_CONTROL(GetPlayerIndex(), TRUE);
	SET_CHAR_COORDINATES(GetPlayerPed(), 556.13, -309.68, 5.41);
	SET_CHAR_RELATIONSHIP_GROUP(GetPlayerPed(), 0);
	FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
	FORWARD_TO_TIME_OF_DAY(06, 00);//устанавливаем время
	RELEASE_WEATHER();
	RELEASE_TIME_OF_DAY();
	FORCE_LOADING_SCREEN(TRUE);
	SET_CAR_DENSITY_MULTIPLIER(1.0);
	SET_MAX_WANTED_LEVEL(6);
	LOAD_SCENE(-694.657, -781.296, 11.2055);
	SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), 556.13, -309.68, 5.41);
	SET_CHAR_HEADING(GetPlayerPed(), 253.51);

	ADD_POLICE_RESTART(831.488, 63.0072, 5.98145, -45.0, 0); // полицейский учаток в Океандрайв

	InitScriptLauncher();
	SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PEDS(100); 
	SPECIFY_SCRIPT_POPULATION_ZONE_NUM_SCENARIO_PEDS(100);
	ACTIVATE_SCRIPT_POPULATION_ZONE();

	//WAIT(2000);
	//HideLoadingScreen(4000);
	//Superman();
	while (TRUE) 
	{
		WAIT(0);
		//------------------- Металлоискатель -------------------
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 532.444, 799.818, 14.841, 522.444, 801.818, 20.841, 0 )) //Гольф клуб
		{
			get_weap(1);
		}
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -969.68, -304.184, 8.415, -977.749, -295.524, 13.73, 0 )) //Аэропорт проход 1
		{
			get_weap(2);
		}
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1027.328, -303.785, 8.415, -1035.396, -295.124, 13.73, 0 )) //Аэропорт проход 2
		{
			get_weap(3);
		}

		if (HAS_PICKUP_BEEN_COLLECTED( tweap_1 ))
		{
			UpdateWeaponOfPed(GetPlayerPed(), Weap1);
			UpdateWeaponOfPed(GetPlayerPed(), Weap2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap3);
			UpdateWeaponOfPed(GetPlayerPed(), Weap4);
			UpdateWeaponOfPed(GetPlayerPed(), Weap5);
			UpdateWeaponOfPed(GetPlayerPed(), Weap6);
			UpdateWeaponOfPed(GetPlayerPed(), Weap7);
			UpdateWeaponOfPed(GetPlayerPed(), Weap8);
			UpdateWeaponOfPed(GetPlayerPed(), Weap9);
			UpdateWeaponOfPed(GetPlayerPed(), Weap0);
			SET_CHAR_AMMO(GetPlayerPed(), Weap1, Ammo1_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap2, Ammo2_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap3, Ammo3_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap4, Ammo4_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap5, Ammo5_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap6, Ammo6_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap7, Ammo7_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap8, Ammo8_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap9, Ammo9_1);
			SET_CHAR_AMMO(GetPlayerPed(), Weap0, Ammo0_1);
		}
		if (HAS_PICKUP_BEEN_COLLECTED( tweap_2 ))
		{
			UpdateWeaponOfPed(GetPlayerPed(), Weap1_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap2_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap3_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap4_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap5_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap6_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap7_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap8_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap9_2);
			UpdateWeaponOfPed(GetPlayerPed(), Weap0_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap1_2, Ammo1_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap2_2, Ammo2_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap3_2, Ammo3_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap4_2, Ammo4_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap5_2, Ammo5_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap6_2, Ammo6_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap7_2, Ammo7_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap8_2, Ammo8_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap9_2, Ammo9_2);
			SET_CHAR_AMMO(GetPlayerPed(), Weap0_2, Ammo0_2);
		}


		//------------------- фикс гоститаля -------------------
		if (IS_CHAR_DEAD(GetPlayerPed())) 
		{
			hospital();
		}
		//------------------- Адвакат -------------------
		if (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))
		{
			if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), 166.465, -2264.458, -2886.127, 552.054, 0 )) && (G_DIAZ >= 3)) // игрок в зоне Гаваны
			{
				cop_X = -438.639;
				cop_Y = -150.309;
				cop_Z = 5.42567;
				cop_R = -50.0;
			}
			else if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), 166.465, 552.054, -2886.127, 3735.542, 0 )) && (G_DIAZ >= 3)) // игрок в зоне Даунтауна
			{
				cop_X = -224.47;
				cop_Y = 1295.06;
				cop_Z = 5.851;
				cop_R = 135.0;
			}
			else if (IS_CHAR_IN_AREA_2D( GetPlayerPed(), 3113.873, 552.054, 166.465, 3735.542, 0 )) // игрок в зоне Вице пойнт
			{
				cop_X = 941.943;
				cop_Y = 1041.08;
				cop_Z = 5.54716;
				cop_R = 180.0;
			}
			else
			{
				cop_X = 831.488;
				cop_Y = 63.0072;
				cop_Z = 5.98145;
				cop_R = -45.0;
			}
			lawyer();
		}

		//------------------- музыка в интерьерах -------------------
		GET_INTERIOR_FROM_CHAR(GetPlayerPed(), &intHash);
		//DISPLAY_TEXT_WITH_2_NUMBERS(0.2, 0.2, "CAMTEST", intHash, ROUND(vol));
		if (intHash == 514)// MALIBU_CLUB
		{	
			if (isPlaying == 0)
			{
				GENERATE_RANDOM_INT_IN_RANGE(0, 550000, &startOffset);
				while (!(PRELOAD_STREAM_WITH_START_OFFSET("INTERIOR_STREAMS_MALIBU_CLUB", startOffset)))
				{
					WAIT(0);
				}
				PLAY_STREAM_FRONTEND();	
				SET_STREAM_PARAMS(0.0, 15000);
				isPlaying = 1;
				isVolChanged = 1;
			}
			inInterior = 1;
		}
		else if (intHash == 258) // MALL
		{	
			if (isPlaying == 0)
			{
				GENERATE_RANDOM_INT_IN_RANGE(0, 200000, &startOffset);
				while (!(PRELOAD_STREAM_WITH_START_OFFSET("INTERIOR_STREAMS_MALL_AMB", startOffset)))
				{
					WAIT(0);
				}
				PLAY_STREAM_FRONTEND();	
				SET_STREAM_PARAMS(0.0, 15000);
				isPlaying = 1;
				isVolChanged = 1;
			}
			inInterior = 1;
		}
		else if (intHash == 1026)// HOTEL
		{	
			if (isPlaying == 0)
			{
				GENERATE_RANDOM_INT_IN_RANGE(0, 450000, &startOffset);
				while (!(PRELOAD_STREAM_WITH_START_OFFSET("INTERIOR_STREAMS_HOTEL_MUSIC", startOffset)))
				{
					WAIT(0);
				}
				PLAY_STREAM_FRONTEND();	
				SET_STREAM_PARAMS(0.0, 15000);
				isPlaying = 1;
				isVolChanged = 1;
			}
			inInterior = 1;
		}
		else if (intHash == 1282)// STRIP
		{	
			if (isPlaying == 0)
			{
				GENERATE_RANDOM_INT_IN_RANGE(0, 650000, &startOffset);
				while (!(PRELOAD_STREAM_WITH_START_OFFSET("INTERIOR_STREAMS_STRIPCLUB", startOffset)))
				{
					WAIT(0);
				}
				PLAY_STREAM_FRONTEND();	
				SET_STREAM_PARAMS(0.0, 15000);
				isPlaying = 1;
				isVolChanged = 1;
			}
			inInterior = 1;
		}
		else
		{
			inInterior = 0;
			if (stop_aud == 1)
			{
				SET_STREAM_PARAMS(15.1, 15000);
				STOP_STREAM();
				isVolChanged = 0;
				isPlaying = 0;
				stop_aud = 0;
			}
		}

		GET_FRAME_TIME(&delta);
		if (inInterior == 1)
		{
			if (isVolChanged == 1)
			{
				vol += delta*1.5;
				SET_STREAM_PARAMS(vol, 15000);
				if (vol > 15.1)
				{
					vol = 15.1;
					isVolChanged = 0;
				}
			}
		}
		else
		{
			if (isPlaying == 1)
			{
				vol -= delta*3;
				SET_STREAM_PARAMS(vol, 15000);
				if (vol <= 0.0)
				{
					vol = 0.0;
					stop_aud = 1;
				}
			}
		}
	}
}
