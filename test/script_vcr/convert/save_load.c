/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

#include "globals.h"
float X, Y, Z, R;

void main(void)
{
	if (G_SAVE_OCCURED)
	{
		uint Torso;
		WAIT(500);
		if (G_SAVE_SAVED == 1) // Printworks
		{
			X = -645.084;
			Y = 246.738;
			Z = 6.27582;
			R = -5.0;
		}
		else if (G_SAVE_SAVED == 2) // Sunshine Autos
		{
			X =-595.363;
			Y = -318.285;
			Z = 7.53234;
			R = -150.0;
		}
		else if (G_SAVE_SAVED == 3) // Interglobal Films
		{
			X =349.932;
			Y = 1461.77;
			Z = 5.1074;
			R = -105.0;
		}
		else if (G_SAVE_SAVED == 4) // Cherry Popper Icecreams
		{
			X = -444.516;
			Y = -45.5149;
			Z = 5.47654;
			R = -80.0;
		}
		else if (G_SAVE_SAVED == 5) // Kaufman Cabs
		{
			X = -567.321;
			Y = 720.751;
			Z = 5.67434;
			R = 60.0;
		}
		else if (G_SAVE_SAVED == 6) // Malibu Club
		{
			X = 924.395;
			Y = 454.833;
			Z = 5.73708;
			R = -130.0;
		}
		else if (G_SAVE_SAVED == 7) // The Boatyard
		{
			X = -235.225;
			Y = -949.423;
			Z = 8.07865;
			R = -25.0;
		}
		else if (G_SAVE_SAVED == 8) // Pole Position Club
		{
			X = 529.641;
			Y = -937.62;
			Z = 4.65521;
			R = -150.0;
		}
		else if (G_SAVE_SAVED == 9) // El Swanko Casa
		{
			X = 861.53;
			Y = 1139.81;
			Z = 6.99313;
			R = 0.0;
		}
		else if (G_SAVE_SAVED == 10) // Links View Apartment
		{
			X = 737.991;
			Y = 909.371;
			Z = 7.45291;
			R = -85.0;
		}
		else if (G_SAVE_SAVED == 11) // Hyman Condo
		{
			X = -401.593;
			Y = 1839.58;
			Z = 5.7949;
			R = -165.0;
		}
		else if (G_SAVE_SAVED == 12) // Ocean Heighs Aprt
		{
			X = 451.255;
			Y = -967.217;
			Z = 7.52892;
			R = -5.0;
		}
		else if (G_SAVE_SAVED == 13) // 1102 Washington Street
		{
			X = 522.489;
			Y = -272.164;
			Z = 6.00446;
			R = -120.0;
		}
		else if (G_SAVE_SAVED == 14) // 3321 Vice Point
		{
			X = 963.529;
			Y = 1805.22;
			Z = 12.0903;
			R = 130.0;
		}
		else if (G_SAVE_SAVED == 15) // Skumole Shack
		{
			X = -127.19;
			Y = 1236.19;
			Z = 14.8111;
			R = 0.0;
		}
		else if (G_SAVE_SAVED == 16) // Ocean View Hotel
		{
			X = 664.601;
			Y = -746.511;
			Z = 7.041;
			R = 250.0;
		}
		else if (G_SAVE_SAVED == 17) // Vercetti Mansion
		{
			X = 54.5077;
			Y = -19.8106;
			Z =13.8069;
			R = 0.0;
		}
		else
		{
			X = 664.601;
			Y = -746.511;
			Z = 7.041;
			R = 250.0;
		}

		LOAD_SCENE(X, Y, Z);
		SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), X, Y, Z);
		SET_CHAR_HEADING(GetPlayerPed(), R);

		WAIT(500);
		//получить скин
		Torso = GET_CHAR_DRAWABLE_VARIATION(GetPlayerPed(), 1);

		//получить оружие
		uint Weap1, Ammo1_1, Ammo1_2;
		uint Weap2, Ammo2_1, Ammo2_2;
		uint Weap3, Ammo3_1, Ammo3_2;
		uint Weap4, Ammo4_1, Ammo4_2;
		uint Weap5, Ammo5_1, Ammo5_2;
		uint Weap6, Ammo6_1, Ammo6_2;
		uint Weap7, Ammo7_1, Ammo7_2;
		uint Weap8, Ammo8_1, Ammo8_2;
		uint Weap9, Ammo9_1, Ammo9_2;
		uint Weap0, Ammo0_1, Ammo0_2;
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 1, &Weap1, &Ammo1_1, &Ammo1_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 2, &Weap2, &Ammo2_1, &Ammo2_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 3, &Weap3, &Ammo3_1, &Ammo3_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 4, &Weap4, &Ammo4_1, &Ammo4_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 5, &Weap5, &Ammo5_1, &Ammo5_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap6, &Ammo6_1, &Ammo6_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 7, &Weap7, &Ammo7_1, &Ammo7_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 8, &Weap8, &Ammo8_1, &Ammo8_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 9, &Weap9, &Ammo9_1, &Ammo9_2);
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 0, &Weap0, &Ammo0_1, &Ammo0_2);
   
		CHANGE_PLAYER_MODEL(GetPlayerIndex(), 1862763509);
		WAIT(100);
		//задать оружие
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
		SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);

		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, Torso, 0);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 2, 0, 0);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 3, 0, 0);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 4, 0, 0);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 5, 0, 0);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 6, 0, 0);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 8, 0, 0);

		uint h, m;
		GET_TIME_OF_DAY(&h, &m);
		FORWARD_TO_TIME_OF_DAY(h + 6, m);
		DO_SCREEN_FADE_OUT_UNHACKED(0);
		SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), X, Y, Z);
		SET_CHAR_HEADING(GetPlayerPed(), R);

		WAIT(2000);
		FORCE_LOADING_SCREEN(FALSE);
		DO_SCREEN_FADE_IN_UNHACKED(3000);
	}

	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
