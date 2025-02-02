#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

Pickup tatem;

int pick_1, pick_2, pick_3, pick_4, pick_5, pick_6, pick_7, pick_8, pick_9, pick_10, pick_11, pick_12, pick_13, pick_14, pick_15, pick_16, pick_17, pick_18, pick_19, pick_20, pick_21, pick_22, pick_23, pick_24, pick_25;
int pick_26, pick_27, pick_28, pick_29, pick_30, pick_31, pick_32, pick_33, pick_34, pick_35, pick_36, pick_37, pick_38, pick_39, pick_40, pick_41, pick_42, pick_43, pick_44, pick_45, pick_46, pick_47, pick_48, pick_49, pick_50;
int pick_51, pick_52, pick_53, pick_54, pick_55, pick_56, pick_57, pick_58, pick_59, pick_60, pick_61, pick_62, pick_63, pick_64, pick_65, pick_66, pick_67, pick_68, pick_69, pick_70, pick_71, pick_72, pick_73, pick_74, pick_75;
int pick_76, pick_77, pick_78, pick_79, pick_80, pick_81, pick_82, pick_83, pick_84, pick_85, pick_86, pick_87, pick_88, pick_89, pick_90, pick_91, pick_92, pick_93, pick_94, pick_95, pick_96, pick_97, pick_98, pick_99, pick_100;
int all_pick, part_pick, spawn;

void text(void)
{
	ADD_SCORE( GetPlayerIndex(), +100 );//даём игроку денег
	SETTIMERA(0);
	while (true)
	{
		WAIT(0);
		SET_TEXT_COLOUR(0, 180, 130, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 250);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_2_NUMBERS(0.5, 0.35, "PAKEGES_T1", all_pick, 100);// текст "поднято пакетов ~1~ из ~1~ "  
		if ((TIMERA() > 5000) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
		{
			break;
		}
	}
}
void packages(void)
{
	all_pick = 0;
	part_pick = 1;
	spawn = 0;

	WAIT(3000);
	while (TRUE)
	{
		WAIT(0);
		if (pick_1 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 924.0994, -1196.418, 4.736586, 902.0994, -1174.418, 29.736586, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 913.0994, -1185.418, 9.736586, &tatem, 0 );
					spawn = 1;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_1 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 1)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_2 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1152.4, 23.79999, 1.45, 1130.4, 45.79999, 26.45, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 1141.4, 34.79999, 6.45, &tatem, 0 );
					spawn = 2;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_2 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 2)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_3 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 231, -1125.1, 2.25, 209, -1103.1, 27.25, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 220, -1114.1, 7.25, &tatem, 0 );
					spawn = 3;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_3 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 3)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_4 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 75.60001, -1211.2, 0.711996, 53.60001, -1189.2, 25.711996, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 64.60001, -1200.2, 5.711996, &tatem, 0 );
					spawn = 4;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_4 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 4)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_5 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 340.1829, -1078.684, -0.630203, 318.1829, -1056.684, 24.369797, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 329.1829, -1067.684, 4.369797, &tatem, 0 );
					spawn = 5;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_5 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 5)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_6 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 209.3, -560.6, 2.721842, 187.3, -538.6, 27.721842, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 198.3, -549.6, 7.721842, &tatem, 0 );
					spawn = 6;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_6 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 6)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_7 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 532, -469.7, 8.24603, 510, -447.7, 33.24603, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 521, -458.7, 13.24603, &tatem, 0 );
					spawn = 7;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_7 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 7)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_8 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 649.4, -366.9, 1.273831, 627.4, -344.9, 26.273831, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 638.4, -355.9, 6.273831, &tatem, 0 );
					spawn = 8;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_8 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 8)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_9 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 627.1, -130.9, -0.361522, 605.1, -108.9, 24.638478, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 616.1, -119.9, 4.638478, &tatem, 0 );
					spawn = 9;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_9 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 9)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_10 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 814.9, 52.5, 2.95, 792.9, 74.5, 27.95, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 803.9, 63.5, 7.95, &tatem, 0 );
					ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(tatem, "cop_int");
					spawn = 10;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_10 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 10)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_11 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 742.8, 243.5, 1.038167, 720.8, 265.5, 26.038167, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 731.8, 254.5, 6.038167, &tatem, 0 );
					spawn = 11;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_11 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 11)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_12 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 765.8, -252.3, 11.95351, 743.8, -230.3, 36.95351, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 754.8, -241.3, 16.95351, &tatem, 0 );
					spawn = 12;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_12 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 12)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_13 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 935.8, 476.7, -0.863174, 913.8, 498.7, 24.136826, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 924.8, 487.7, 4.136826, &tatem, 0 );
					spawn = 13;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_13 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 13)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_14 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 914.6589, 635.4711, 0.319037, 892.6589, 657.4711, 25.319037, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 903.6589, 646.4711, 5.319037, &tatem, 0 );
					spawn = 14;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_14 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 14)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_15 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 824.2898, 733.5702, 0.467783, 802.2898, 755.5702, 25.467783, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 813.2898, 744.5702, 5.467783, &tatem, 0 );
					spawn = 15;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_15 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 15)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_16 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 734.1, 817.4, 2.652855, 712.1, 839.4, 27.652855, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 723.1, 828.4, 7.652855, &tatem, 0 );
					spawn = 16;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_16 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 16)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_17 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 914.9001, 1645.6, 13.65, 892.9001, 1667.6, 38.65, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 903.9001, 1656.6, 18.65, &tatem, 0 );
					ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(tatem, "mall_int");
					spawn = 17;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_17 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 17)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_18 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 851.6, 1540.2, 14.45, 829.6, 1562.2, 39.45, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 840.6, 1551.2, 19.45, &tatem, 0 );
					ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(tatem, "mall_int");
					spawn = 18;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_18 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 18)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_19 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1005.6, 1679.1, 8.05297, 983.6, 1701.1, 33.05297, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 994.6, 1690.1, 13.05297, &tatem, 0 );
					spawn = 19;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_19 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 19)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_20 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1335.8, 1395.8, 5.46477, 1313.8, 1417.8, 30.46477, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 1324.8, 1406.8, 10.46477, &tatem, 0 );
					spawn = 20;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_20 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 20)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_21 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 797.7, -42.29999, 45.54806, 775.7, -20.29999, 70.54806, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 786.7, -31.29999, 50.54806, &tatem, 0 );
					spawn = 21;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_21 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 21)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_22 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 750.9, 1699.5, 6.52917, 728.9, 1721.5, 31.52917, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 739.9, 1710.5, 11.52917, &tatem, 0 );
					spawn = 22;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_22 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 22)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_23 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 715.3, 1454.9, -1.047812, 693.3, 1476.9, 23.952188, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 704.3, 1465.9, 3.952188, &tatem, 0 );
					spawn = 23;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_23 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 23)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_24 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 772.7, 1239.2, 11.98205, 750.7, 1261.2, 36.98205, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 761.7, 1250.2, 16.98205, &tatem, 0 );
					spawn = 24;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_24 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 24)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_25 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 917.6468, 539.4587, 22.14715, 895.6468, 561.4587, 47.14715, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 906.6468, 550.4587, 27.14715, &tatem, 0 );
					spawn = 25;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_25 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 25)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_26 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 796.9095, 806.0086, 8.7679, 774.9095, 828.0086, 33.7679, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 785.9095, 817.0086, 13.7679, &tatem, 0 );
					spawn = 26;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_26 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 26)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_27 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 514.1, 42.39999, 2.766345, 492.1, 64.39999, 27.766345, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 503.1, 53.39999, 7.766345, &tatem, 0 );
					spawn = 27;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_27 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 27)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_28 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 497.6, 75.5, -2.477641, 475.6, 97.5, 22.522359, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 486.6, 86.5, 2.522359, &tatem, 0 );
					spawn = 28;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_28 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 28)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_29 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 710.3, 272.1, 25.23756, 688.3, 294.1, 50.23756, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 699.3, 283.1, 30.23756, &tatem, 0 );
					spawn = 29;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_29 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 29)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_30 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 857.9, 1739.4, 7.52021, 835.9, 1761.4, 32.52021, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 846.9, 1750.4, 12.52021, &tatem, 0 );
					spawn = 30;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_30 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 30)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_31 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 271.6, -819.3001, -6.946664, 249.6, -797.3001, 18.053336, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 260.6, -808.3001, -1.946664, &tatem, 0 );
					spawn = 31;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_31 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 31)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_32 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 210.9, -409.2, -1.057209, 188.9, -387.2, 23.942791, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 199.9, -398.2, 3.942791, &tatem, 0 );
					spawn = 32;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_32 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 32)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_33 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 507.077, -276.703, 0.805548, 487.278, -251.08, 25.805548, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 506.2901, -262.5063, 5.805548, &tatem, 0 );
					spawn = 33;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_33 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 33)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_34 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 551.5, -29.90002, 3.809023, 529.5, -7.90002, 28.809023, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 540.5, -18.90002, 8.809023, &tatem, 0 );
					spawn = 34;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_34 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 34)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_35 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 677.9001, 389.8, -2.826186, 655.9001, 411.8, 22.173814, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 666.9001, 400.8, 2.173814, &tatem, 0 );
					spawn = 35;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_35 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 35)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_36 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 868.6684, 609.7336, 0.348907, 846.6684, 631.7336, 25.348907, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 857.6684, 620.7336, 5.348907, &tatem, 0 );
					spawn = 36;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_36 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 36)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_37 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 845.6, 953.1, 0.519434, 823.6, 975.1, 25.519434, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 834.6, 964.1, 5.519434, &tatem, 0 );
					spawn = 37;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_37 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 37)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_38 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 637.9, 1200.8, 2.05504, 615.9, 1222.8, 27.05504, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 626.9, 1211.8, 7.05504, &tatem, 0 );
					spawn = 38;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_38 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 38)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_39 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1033.4, 558, 5.84004, 1011.4, 580, 30.84004, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 1022.4, 569, 10.84004, &tatem, 0 );
					spawn = 39;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_39 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 39)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_40 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 965.3518, 388.0195, 23.68931, 943.3518, 410.0195, 48.68931, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 954.3518, 399.0195, 28.68931, &tatem, 0 );
					spawn = 40;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_40 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 40)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_41 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 402.2, 1444.4, 8.50255, 380.2, 1466.4, 33.50255, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 391.2, 1455.4, 13.50255, &tatem, 0 );
					spawn = 41;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_41 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 41)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_42 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 427.9, 1513.7, -0.020416, 405.9, 1535.7, 24.979584, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 416.9, 1524.7, 4.979584, &tatem, 0 );
					spawn = 42;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_42 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 42)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_43 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 504.7, 1438.5, -0.105523, 482.7, 1460.5, 24.894477, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 493.7, 1449.5, 4.894477, &tatem, 0 );
					spawn = 43;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_43 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 43)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_44 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 376.0553, 1646, 6.15717, 354.0553, 1668, 31.15717, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 365.0553, 1657, 11.15717, &tatem, 0 );
					spawn = 44;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_44 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 44)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_45 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 526.7, 1635.8, 7.84051, 504.7, 1657.8, 32.84051, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 515.7, 1646.8, 12.84051, &tatem, 0 );
					spawn = 45;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_45 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 45)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_46 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 514.5, 1121.3, 3.654015, 492.5, 1143.3, 28.654015, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 503.5, 1132.3, 8.654015, &tatem, 0 );
					spawn = 46;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_46 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 46)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_47 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 619.7708, 773.417, 1.062229, 597.7708, 795.417, 26.062229, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 608.7708, 784.417, 6.062229, &tatem, 0 );
					spawn = 47;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_47 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 47)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_48 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 489.4369, 370.8303, 1.561998, 467.4369, 392.8303, 26.561998, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 478.4369, 381.8303, 6.561998, &tatem, 0 );
					spawn = 48;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_48 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 48)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_49 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 397.4, 779.7, 13.66698, 375.4, 801.7, 38.66698, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 386.4, 790.7, 18.66698, &tatem, 0 );
					spawn = 49;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_49 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 49)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_50 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 487.4, 507, 6.47937, 465.4, 529, 31.47937, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 476.4, 518, 11.47937, &tatem, 0 );
					spawn = 50;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_50 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 50)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_51 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 207.1, -66.09997, -0.558567, 185.1, -44.09997, 24.441433, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 196.1, -55.09997, 4.441433, &tatem, 0 );
					spawn = 51;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_51 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 51)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_52 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -74.29633, -77.29999, -0.538085, -96.29633, -55.29999, 24.461915, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -85.29633, -66.29999, 4.461915, &tatem, 0 );
					spawn = 52;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_52 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 52)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_53 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -133.5201, 98.6854, 8.92293, -155.5201, 120.6854, 33.92293, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -144.5201, 109.6854, 13.92293, &tatem, 0 );
					spawn = 53;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_53 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 53)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_54 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 135.0885, 106.9701, -0.802952, 113.0885, 128.9701, 24.197048, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 124.0885, 117.9701, 4.197048, &tatem, 0 );
					spawn = 54;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_54 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 54)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_55 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 199.9354, 198.1507, -0.614758, 177.9354, 220.1507, 24.385242, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 188.9354, 209.1507, 4.385242, &tatem, 0 );
					spawn = 55;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_55 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 55)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_56 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 197.1, 1741.5, 0.029903, 175.1, 1763.5, 25.029903, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, 186.1, 1752.5, 5.029903, &tatem, 0 );
					spawn = 56;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_56 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 56)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_57 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -7, 1808.6, 1.764299, -29, 1830.6, 26.764299, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -18, 1819.6, 6.764299, &tatem, 0 );
					spawn = 57;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_57 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 57)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_58 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -317.48, 1785.41, 0.648621, -339.48, 1807.41, 25.648621, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -328.48, 1796.41, 5.648621, &tatem, 0 );
					spawn = 58;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_58 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 58)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_59 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1106.1, 1925.1, -2.184933, -1128.1, 1947.1, 22.815067, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1117.1, 1936.1, 2.815067, &tatem, 0 );
					spawn = 59;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_59 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 59)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_60 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -346.8, 1641.4, -1.054897, -368.8, 1663.4, 23.945103, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -357.8, 1652.4, 3.945103, &tatem, 0 );
					spawn = 60;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_60 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 60)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_61 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -7.5, 1641.7, 50.23894, -29.5, 1663.7, 75.23894, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -18.5, 1652.7, 55.23894, &tatem, 0 );
					spawn = 61;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_61 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 61)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_62 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -124.6018, 1299.199, 11.96159, -146.6018, 1321.199, 36.96159, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -135.6018, 1310.199, 16.96159, &tatem, 0 );
					spawn = 62;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_62 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 62)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_63 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -454.7, 952.4, 0.060403, -476.7, 974.4, 25.060403, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -465.7, 963.4, 5.060403, &tatem, 0 );
					spawn = 63;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_63 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 63)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_64 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -535.0205, 786.9848, -1.705204, -557.0205, 808.9848, 23.294796, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -546.0205, 797.9848, 3.294796, &tatem, 0 );
					spawn = 64;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_64 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 64)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_65 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -411.8667, 750.1909, 2.085114, -433.8667, 772.1909, 27.085114, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -422.8667, 761.1909, 7.085114, &tatem, 0 );
					spawn = 65;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_65 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 65)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_66 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -628.5, 873.7, 0.350351, -650.5, 895.7, 25.350351, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -639.5, 884.7, 5.350351, &tatem, 0 );
					spawn = 66;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_66 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 66)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_67 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -717.6, 953.1, 0.174026, -739.6, 975.1, 25.174026, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -728.6, 964.1, 5.174026, &tatem, 0 );
					spawn = 67;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_67 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 67)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_68 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -531.1, 713.9, 1.731517, -553.1, 735.9, 26.731517, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -542.1, 724.9, 6.731517, &tatem, 0 );
					spawn = 68;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_68 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 68)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_69 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -589.1119, 566.1001, 0.428432, -611.1119, 588.1001, 25.428432, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -600.1119, 577.1001, 5.428432, &tatem, 0 );
					spawn = 69;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_69 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 69)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_70 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -550, 271.7, -0.176608, -572, 293.7, 24.823392, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -561, 282.7, 4.823392, &tatem, 0 );
					spawn = 70;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_70 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 70)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_71 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -660.9, 401.1, 9.23516, -682.9, 423.1, 34.23516, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -671.9, 412.1, 14.23516, &tatem, 0 );
					spawn = 71;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_71 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 71)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_72 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -689.3439, 165.0698, 4.114492, -711.3439, 187.0698, 29.114492, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -700.3439, 176.0698, 9.114492, &tatem, 0 );
					spawn = 72;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_72 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 72)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_73 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -751.1999, 204.3, 0.026275, -773.1999, 226.3, 25.026275, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -762.1999, 215.3, 5.026275, &tatem, 0 );
					spawn = 73;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_73 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 73)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_74 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -649.7, -78.09998, 15.15, -671.7, -56.09998, 40.15, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -660.7, -67.09998, 20.15, &tatem, 0 );
					spawn = 74;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_74 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 74)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_75 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -735.9, -54.29999, 1.849563, -757.9, -32.29999, 26.849563, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -746.9, -43.29999, 6.849563, &tatem, 0 );
					spawn = 75;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_75 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 75)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_76 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -576.9405, -351.6171, 7.04838, -598.9405, -329.6171, 32.04838, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -587.9405, -340.6171, 12.04838, &tatem, 0 );
					spawn = 76;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_76 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 76)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_77 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -409.2476, -108.11122, 1.367052, -431.2476, -86.11122, 26.367052, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -420.2476, -97.11122, 6.367052, &tatem, 0 );
					spawn = 77;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_77 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 77)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_78 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -735.1999, -196.8, 11.95944, -757.1999, -174.8, 36.95944, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -746.1999, -185.8, 16.95944, &tatem, 0 );
					spawn = 78;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_78 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 78)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_79 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -358.9, -662.6, 0.189179, -380.9, -640.6, 25.189179, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -369.9, -651.6, 5.189179, &tatem, 0 );
					spawn = 79;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_79 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 79)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_80 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -178.7, -853.4, 10.85281, -200.7, -831.4, 35.85281, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -189.7, -842.4, 15.85281, &tatem, 0 );
					spawn = 80;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_80 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 80)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_81 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -574, -971.8001, 8.49348, -596, -949.8001, 33.49348, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -585, -960.8001, 13.49348, &tatem, 0 );
					spawn = 81;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_81 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 81)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_82 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -646.2, -677.1999, 0.283512, -668.2, -655.1999, 25.283512, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -657.2, -666.1999, 5.283512, &tatem, 0 );
					spawn = 82;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_82 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 82)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_83 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -385.2, -939, 1.702013, -407.2, -917, 26.702013, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -396.2, -928, 6.702013, &tatem, 0 );
					spawn = 83;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_83 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 83)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_84 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -716.6, -811.8, 4.01815, -738.6, -789.8, 29.01815, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -727.6, -800.8, 9.01815, &tatem, 0 );
					spawn = 84;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_84 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 84)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_85 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -925.3001, -733.6999, 7.24, -947.3001, -711.6999, 32.24, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -936.3001, -722.6999, 12.24, &tatem, 0 );
					spawn = 85;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_85 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 85)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_86 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -836.9, -624.5, 11.33602, -858.9, -602.5, 36.33602, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -847.9, -613.5, 16.33602, &tatem, 0 );
					spawn = 86;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_86 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 86)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_87 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1329.8, -531.1999, 3.95146, -1351.8, -509.1999, 28.95146, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1340.8, -520.1999, 8.95146, &tatem, 0 );
					spawn = 87;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_87 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 87)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_88 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -743.3, -519.4, 3.951916, -765.3, -497.4, 28.951916, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -754.3, -508.4, 8.951916, &tatem, 0 );
					spawn = 88;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_88 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 88)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_89 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1025.48, -359.29, 23.0069, -1047.48, -337.29, 48.0069, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1036.48, -348.29, 28.0069, &tatem, 0 );
					spawn = 89;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_89 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 89)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_90 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1117.8, -537.5, 7.571, -1139.8, -515.5, 13.898, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1128.8, -526.5, 8.940001, &tatem, 0 );
					spawn = 90;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_90 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 90)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_91 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -905.1, -568.4, 13.68271, -927.1, -546.4, 38.68271, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -916.1, -557.4, 18.68271, &tatem, 0 );
					spawn = 91;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_91 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 91)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_92 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1123.3, -533.5, 15.03, -1145.3, -511.5, 35.44, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1134.3, -522.5, 15.44, &tatem, 0 );
					spawn = 92;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_92 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 92)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_93 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -922.4, -406, 9.97058, -944.4, -384, 34.97058, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -933.4, -395, 14.97058, &tatem, 0 );
					spawn = 93;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_93 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 93)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_94 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1079.5, -297.1, 3.958352, -1101.5, -275.1, 28.958352, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1090.5, -286.1, 8.958352, &tatem, 0 );
					spawn = 94;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_94 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 94)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_95 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1385.1, -365.6, 3.942764, -1407.1, -343.6, 28.942764, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1396.1, -354.6, 8.942764, &tatem, 0 );
					spawn = 95;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_95 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 95)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_96 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1282.5, 102.8, 3.950307, -1304.5, 124.8, 28.950307, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1293.5, 113.8, 8.950307, &tatem, 0 );
					spawn = 96;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_96 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 96)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_97 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1293.2, 222.8, 3.948702, -1315.2, 244.8, 28.948702, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -1304.2, 233.8, 8.948702, &tatem, 0 );
					spawn = 97;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_97 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 97)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_98 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -884, -15.099975, 3.003187, -906, 6.900025, 28.003187, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -895, -4.099975, 8.003187, &tatem, 0 );
					spawn = 98;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_98 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 98)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_99 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -619.5, -443.5, 3.949265, -641.5, -421.5, 28.949265, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -630.5, -432.5, 8.949265, &tatem, 0 );
					spawn = 99;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_99 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 99)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}
		if (pick_100 == 0)
		{
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -821.8001, -824.9, 18.78222, -843.8001, -802.9, 43.78222, 0 ))
			{
				if (spawn == 0)
				{
					CREATE_PICKUP( vc_packages, 22, -832.8001, -813.9, 23.78222, &tatem, 0 );
					spawn = 100;
				}
				if (HAS_PICKUP_BEEN_COLLECTED( tatem ))
				{
					REMOVE_PICKUP(tatem);// выгружаем
					pick_100 = 1;
					all_pick += 1;
					spawn = 0;
					text();
				}
			}
			else
			{
				if (spawn == 100)
				{
					REMOVE_PICKUP(tatem);// выгружаем
					spawn = 0;
					WAIT(1000);
				}
			}
		}

		// --------------- Назначение бонусов ---------------
		if ((all_pick == 10) && (part_pick == 1))
		{
			PRINT_HELP("PICK1"); //Body Armor delivered to Ocean View Hotel!
			G_PACKET = 1;
			part_pick = 2;
		}
		if ((all_pick == 20) && (part_pick == 2))
		{
			PRINT_HELP("PICK2"); //357 delivered to Ocean View Hotel!
			G_PACKET = 2;
			part_pick = 3;
		}
		if ((all_pick == 30) && (part_pick == 3))
		{
			PRINT_HELP("PICK3"); //Chainsaw delivered to Ocean View Hotel!
			G_PACKET = 3;
			part_pick = 4;
		}
		if ((all_pick == 40) && (part_pick == 4))
		{
			PRINT_HELP("PICK4"); //MP5 delivered to Ocean View Hotel!
			G_PACKET = 4;
			part_pick = 5;
		}
		if ((all_pick == 50) && (part_pick == 5))
		{
			PRINT_HELP("PICK5"); //.308 Sniper delivered to Ocean View Hotel!
			G_PACKET = 5;
			part_pick = 6;
		}
		if ((all_pick == 60) && (part_pick == 6))
		{
			PRINT_HELP("PICK6"); //M60 delivered to Ocean View Hotel!
			G_PACKET = 6;
			part_pick = 7;
		}
		if ((all_pick == 70) && (part_pick == 7))
		{
			PRINT_HELP("PICK7"); //Rocket Launcher delivered to Ocean View Hotel!
			G_PACKET = 7;
			part_pick = 8;
		}
		if ((all_pick == 80) && (part_pick == 8))
		{
			PRINT_HELP("PICK8"); //Sparrow now available from the Mansion on Starfish Island!
			G_PACKET = 8;
			part_pick = 9;
		}
		if ((all_pick == 90) && (part_pick == 9))
		{
			PRINT_HELP("PICK9"); //Tank now available from the Army Barracks!
			G_PACKET = 9;
			part_pick = 10;
		}
		if ((all_pick == 100) && (part_pick == 10))
		{
			PRINT_HELP("PICK10"); //Hunter now available from the Army Barracks!
			G_PACKET = 10;
			part_pick = 11;
			break;
		}
	}
}
void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	packages();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
