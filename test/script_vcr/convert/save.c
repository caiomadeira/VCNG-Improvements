/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

#include "globals.h"
float saving, text_on, X, Y, Z, R;


void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	text_on = 0;
	while (TRUE)
	{
		//=========================== Printworks ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -643.221, 244.286, 5.832, -646.473, 246.34, 9.572, 0 )) && (G_ONMISSION == 0) && (G_COUNT > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 1;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = -645.084;
				Y = 246.738;
				Z = 6.27582;
				R = -5.0;
				saving = 1;
				G_SAVE_SAVED = 1;
			}
		}
		else
		{
			if (text_on == 1)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Sunshine Autos ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -595.019, -317.531, 6.782, -598.862, -313.54, 10.782, 0 )) && (G_ONMISSION == 0) && (G_BUSINES_SA > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 2;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X =-595.363;
				Y = -318.285;
				Z = 7.53234;
				R = -150.0;
				saving = 1;
				G_SAVE_SAVED = 2;
			}
		}
		else
		{
			if (text_on == 2)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Interglobal Films ===========================
		// кровать
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 349.382, 1463.778, 4.527, 346.333, 1467.335, 8.02, 0 )) && (G_ONMISSION == 0) && (G_PRON > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 3;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 346.101;
				Y = 1464.79;
				Z = 5.03874;
				R = 125.0;
				saving = 1;
				G_SAVE_SAVED = 3;
			}
		}
		//диван
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 344.294, 1471.025, 4.527, 342.19, 1473.941, 8.02, 0 )) && (G_ONMISSION == 0) && (G_PRON > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 3;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 341.992;
				Y = 1471.62;
				Z = 5.03874;
				R = 125.0;
				saving = 1;
				G_SAVE_SAVED = 3;
			}
		}
		else
		{
			if (text_on == 3)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Cherry Popper Icecreams ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -445.067, -47.23, 4.972, -447.067, -4.102, 8.562, 0 )) && (G_ONMISSION == 0) && (G_ICECREAM > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 4;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = -444.516;
				Y = -45.5149;
				Z = 5.47654;
				R = -80.0;
				saving = 1;
				G_SAVE_SAVED = 4;
			}
		}
		else
		{
			if (text_on == 4)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Kaufman Cabs ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -564.786, 719.034, 5.225, -566.732, 722.27, 9.459, 0 )) && (G_ONMISSION == 0) && (G_CABS > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 5;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = -567.321;
				Y = 720.751;
				Z = 5.67434;
				R = 60.0;
				saving = 1;
				G_SAVE_SAVED = 5;
			}
		}
		else
		{
			if (text_on == 5)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Malibu Club ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 897.958, 479.305, 9.559, 893.964, 483.173, 12.29, 0 )) && (G_ONMISSION == 0) && (G_CLUB > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 6;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 896.001;
				Y = 479.025;
				Z = 9.93599;
				R = -175.0;
				saving = 1;
				G_SAVE_SAVED = 6;
			}
		}
		else
		{
			if (text_on == 6)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== The Boatyard ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -234.66, -952.034, 7.566, -236.961, -949.769, 11.824, 0 )) && (G_ONMISSION == 0) && (G_COKERUN > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 7;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = -235.225;
				Y = -949.423;
				Z = 8.07865;
				R = -25.0;
				saving = 1;
				G_SAVE_SAVED = 7;
			}
		}
		else
		{
			if (text_on == 7)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Pole Position Club ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 508.048, -917.682, 4.345, 505.62, -915.054, 7.33, 0 )) && (G_ONMISSION == 0) && (G_STRIP > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 8;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 507.606;
				Y = -917.858;
				Z = 4.84248;
				R = -175.0;
				saving = 1;
				G_SAVE_SAVED = 8;
			}
		}
		else
		{
			if (text_on == 8)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== El Swanko Casa ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 863.972, 1132.26, 6.177, 858.972, 1137.26, 11.177, 0 )) && (G_ONMISSION == 0) && (G_SWANKO > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = 861.53;
			Y = 1139.81;
			Z = 6.99313;
			R = 0.0;
			saving = 1;
			G_SAVE_SAVED = 9;
		}
		//=========================== Links View Apartment ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 736.09, 906.963, 6.693, 731.09, 911.963, 11.693, 0 )) && (G_ONMISSION == 0) && (G_LINKS > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = 737.991;
			Y = 909.371;
			Z = 7.45291;
			R = -85.0;
			saving = 1;
			G_SAVE_SAVED = 10;
		}
		//=========================== Hyman Condo ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -400.854, 1841.342, 5.229, -404.119, 1845.572, 10.229, 0 )) && (G_ONMISSION == 0) && (G_CONDO > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = -401.593;
			Y = 1839.58;
			Z = 5.7949;
			R = -165.0;
			saving = 1;
			G_SAVE_SAVED = 11;
		}
		//=========================== Ocean Heighs Aprt ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 453.212, -972.369, 6.965, 447.555, -969.353, 10.267, 0 )) && (G_ONMISSION == 0) && (G_HEIGHS > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = 451.255;
			Y = -967.217;
			Z = 7.52892;
			R = -5.0;
			saving = 1;
			G_SAVE_SAVED = 12;
		}
		//=========================== 1102 Washington Street ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 521.188, -272.005, 5.308, 518.527, -269.363, 10.308, 0 )) && (G_ONMISSION == 0) && (G_WS_1102 > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = 522.489;
			Y = -272.164;
			Z = 6.00446;
			R = -120.0;
			saving = 1;
			G_SAVE_SAVED = 13;
		}
		//=========================== 3321 Vice Point ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 967.985, 1806.919, 11.92, 964.985, 1809.919, 16.438, 0 )) && (G_ONMISSION == 0) && (G_VP_3321 > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = 963.529;
			Y = 1805.22;
			Z = 12.0903;
			R = 130.0;
			saving = 1;
			G_SAVE_SAVED = 14;
		}

		//=========================== Skumole Shack ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -125.348, 1231.967, 14.033, -129.233, 1235.396, 17.309, 0 )) && (G_ONMISSION == 0) && (G_SHACK > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			X = -127.19;
			Y = 1236.19;
			Z = 14.8111;
			R = 0.0;
			saving = 1;
			G_SAVE_SAVED = 15;
		}
		//=========================== Ocean View Hotel ===========================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 662.561, -731.554, 13.874, 659.649, -728.9, 17.472, 0 )) && (G_ONMISSION == 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 16;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 661.254;
				Y = -731.808;
				Z = 14.4212;
				R = -175.0;
				saving = 1;
				G_SAVE_SAVED = 16;
			}
		}
		else
		{
			if (text_on == 16)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}
		//=========================== Vercetti Mansion ===========================
		//диван 1 этаж 1
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 29.714, -26.031, 12.711, 26.559, -24.301, 15.638, 0 )) && (G_ONMISSION == 0) && (G_PROTECT > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 17;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 28.115;
				Y = -26.2823;
				Z =13.2436;
				R = -175.0;
				saving = 1;
				G_SAVE_SAVED = 17;
			}
		}
		//диван 2 этаж 1
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 29.714, -30.213, 12.711, 26.559, -28.483, 15.638, 0 )) && (G_ONMISSION == 0) && (G_PROTECT > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 17;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 28.0589;
				Y = -28.1805;
				Z =13.2436;
				R = -10.0;
				saving = 1;
				G_SAVE_SAVED = 17;
			}
		}
		//диван 3 этаж 2
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 62.09, -60.884, 19.687, 59.834, -58.636, 24.098, 0 )) && (G_ONMISSION == 0) && (G_PROTECT > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 17;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 60.0189;
				Y = -58.3347;
				Z = 20.0673;
				R = 40.0;
				saving = 1;
				G_SAVE_SAVED = 17;
			}
		}
		//диван 4 этаж 2
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 48.989, -62.33, 19.687, 46.732, -59.231, 24.098, 0 )) && (G_ONMISSION == 0) && (G_PROTECT > 0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
		{
			if (text_on == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
				text_on = 17;
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				X = 49.0995;
				Y = -59.0782;
				Z =20.0673;
				R = -45.0;
				saving = 1;
				G_SAVE_SAVED = 17;
			}
		}
		else
		{
			if (text_on == 17)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text_on = 0;
			}
		}



		if (saving == 1)
		{
			CLEAR_HELP(); // удаляем текст подсказки
			saving = 0;
			text_on = 0;
			DO_SCREEN_FADE_OUT(1500);
			WAIT(500);
			G_SAVE_OCCURED = TRUE;
			ACTIVATE_SAVE_MENU();
			WAIT(0);
			SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), X, Y, Z);
			SET_CHAR_HEADING(GetPlayerPed(), R);
			if (DID_SAVE_COMPLETE_SUCCESSFULLY())
			{
				DO_SCREEN_FADE_OUT_UNHACKED(0);
				uint h, m;
				GET_TIME_OF_DAY(&h, &m);
				FORWARD_TO_TIME_OF_DAY(h + 6, m);
				G_SAVE_OCCURED = FALSE;
				WAIT(1000);
			}
			DO_SCREEN_FADE_IN_UNHACKED(2000);
			WAIT(3000);
		}
		WAIT(0);
	}
	return;
}
