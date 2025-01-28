/***********************************************************************
					Fully stripped main script
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
float playX, playY, playZ, playR, jump_ok, all_jump, speed;
float jump_1, jump_2, jump_3, jump_4, jump_5, jump_6, jump_7, jump_8, jump_9, jump_10;
float jump_11, jump_12, jump_13, jump_14, jump_15, jump_16, jump_17, jump_18, jump_19, jump_20;
float jump_21, jump_22, jump_23, jump_24, jump_25, jump_26, jump_27, jump_28, jump_29, jump_30;
float jump_31, jump_32, jump_33, jump_34, jump_35, jump_36;

Cam camera;
Car car1;

void text_jump(void)
{
	all_jump += 1;
	ADD_SCORE( GetPlayerIndex(), (all_jump*100) );//даЄм игроку денег
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);
		SET_TEXT_COLOUR(0, 180, 130, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 250);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT(0.5, 0.4, "JUMPING_T1");// пишем "¬ыполнен уникальный прижок"
		SET_TEXT_COLOUR(55, 95, 125, 255);
		SET_TEXT_SCALE(0.45, 0.65);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 250);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "JUMPING_T2", (all_jump*100));// текст "награда $~1~"
		if ((TIMERA() > 5000) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
		{
			break;
		}
	}
}
void look_jump(float cam_x, float cam_y, float cam_z)
{
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, playX, playY, playZ ); // куда смотрит камера
	SET_CAM_POS			( camera, cam_x, cam_y, cam_z );//расположение камеры
	SET_CAM_FOV( camera, 60.20001000 );
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_WIDESCREEN_BORDERS( 1 );
	SETTIMERA(0); //сбрасываем таймер 
	SET_TIME_SCALE( 0.35 );
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &car1);

	if (IS_CAR_IN_AIR_PROPER(car1))
	{
		while (true) 
		{
			WAIT(0);
			GET_CHAR_COORDINATES(GetPlayerPed(),  &playX, &playY, &playZ);//вписываем координаты игрока в переменную
			POINT_CAM_AT_COORD	( camera, playX, playY, playZ ); // куда смотрит камера
			DISABLE_PAUSE_MENU(1);// отключаем главное меню
			if  ((!IS_CAR_IN_AIR_PROPER(car1)) && (TIMERA() > 150) || (TIMERA() > 3000))
			{
				if (TIMERA() < 1000)
				{
					jump_ok = 0;
				}
				else
				{
					jump_ok = 1;
				}
				break;
			}
		}
	}

	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	DESTROY_CAM( camera );
	SET_WIDESCREEN_BORDERS( 0 ); //возвращаем инетрфейс;
	SET_TIME_SCALE( 1.0 );
	if (jump_ok == 1)
	{
		text_jump();
	}
}
void jump(void)
{
	jump_ok = 0;
	while (true)
	{
		WAIT(0);
		GET_CHAR_COORDINATES(GetPlayerPed(),  &playX, &playY, &playZ);//вписываем координаты игрока в переменную
		GET_CHAR_SPEED(GetPlayerPed(), &speed);
		//DISPLAY_TEXT_WITH_NUMBER(0.9083334, 0.72787074, "CP_TIME_NOZERO", speed);// 

		//===================== jump_1 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -1054.781, -511.546, 12.707, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_1 == 0))
		{
			look_jump(-1088.964, -506.8505, 18.1338);
			if (jump_ok == 1)
			{
				jump_1 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_2 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -919.695, -222.212, 22.673, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_2 == 0))
		{
			look_jump(-927.8242, -248.5606, 31.2329);
			if (jump_ok == 1)
			{
				jump_2 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_3 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -783.49, -378.833, 13, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_3 == 0))
		{
			look_jump(-767.2437, -361.1972, 20.7296);
			if (jump_ok == 1)
			{
				jump_3 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_4 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -819.139, -521.685, 16.016, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_4 == 0))
		{
			look_jump(-761.279, -494.8624, 16.979);
			if (jump_ok == 1)
			{
				jump_4 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_5 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -1118.685, -542.674, 13.121, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_5 == 0))
		{
			look_jump(-1087.165, -540.3603, 18.1604);
			if (jump_ok == 1)
			{
				jump_5 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_6 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -1162.712, -739.881, 13.068, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_6 == 0))
		{
			look_jump(-1131.454, -738.5879, 15.5915);
			if (jump_ok == 1)
			{
				jump_6 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_7 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -1120.337, -697.952, 11.194, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_7 == 0))
		{
			look_jump(-1157.58, -714.3733, 20.3087);
			if (jump_ok == 1)
			{
				jump_7 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_8 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -907.022, -465.257, 13.115, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_8 == 0))
		{
			look_jump(-922.2749, -464.9999, 18.0731);
			if (jump_ok == 1)
			{
				jump_8 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_9 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 457.721, 1430.801, 19.103, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_9 == 0))
		{
			look_jump(433.1404, 1411.404, 14.2009);
			if (jump_ok == 1)
			{
				jump_9 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_10 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 111.972, -846.4981, 4.929, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_10 == 0))
		{
			look_jump(121.9503, -866.5061, 3.6779);
			if (jump_ok == 1)
			{
				jump_10 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_11 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 111.972, -743.589, 4.929, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_11 == 0))
		{
			look_jump(118.4064, -767.2807, 3.4204);
			if (jump_ok == 1)
			{
				jump_11 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_12 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -241.345, 1695.422, 23.916, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_12 == 0))
		{
			look_jump(-257.7014, 1732.213, 19.0565);
			if (jump_ok == 1)
			{
				jump_12 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_13 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -96.84003, 1363.062, 92.71701, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_13 == 0))
		{
			look_jump(-110.2, 1376.4, 93.2);
			if (jump_ok == 1)
			{
				jump_13 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_14 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -406.022, 1686.526, 25.94, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 18) && (jump_14 == 0))
		{
			look_jump(-420.7, 1705.3, 18.4);
			if (jump_ok == 1)
			{
				jump_14 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_15 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 120.553, 1642.196, 41.741, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_15 == 0))
		{
			look_jump(140.5, 1635.7, 34);
			if (jump_ok == 1)
			{
				jump_15 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_16 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -578.583, 502.902, 9.181, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_16 == 0))
		{
			look_jump(-571.154, 470.0057, 9.957);
			if (jump_ok == 1)
			{
				jump_16 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_17 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -509.702, 418.494, 9.181, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_17 == 0))
		{
			look_jump(-497.7841, 407.5568, 6.218799);
			if (jump_ok == 1)
			{
				jump_17 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_18 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -467.789, 793.804, 9.915, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_18 == 0))
		{
			look_jump(-473.6896, 771.6933, 10.5044);
			if (jump_ok == 1)
			{
				jump_18 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_19 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, -608.895, -36.323, 15.855, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 14) && (jump_19 == 0))
		{
			look_jump(-622.6156, -55.86133, 12.1929);
			if (jump_ok == 1)
			{
				jump_19 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_20 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 641.993, -430.672, 13.967, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_20 == 0))
		{
			look_jump(666.5752, -427.8961, 15.5283);
			if (jump_ok == 1)
			{
				jump_20 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_21 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 479.115, -431.415, 19.883, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_21 == 0))
		{
			look_jump(496.3356, -434.6796, 22.5317);
			if (jump_ok == 1)
			{
				jump_21 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_22 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 543.481, -697.6, 29.67, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_22 == 0))
		{
			look_jump(517.5247, -725.3891, 25.4335);
			if (jump_ok == 1)
			{
				jump_22 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_23 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 440.435, -712.895, 11.752, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_23 == 0))
		{
			look_jump(437.1501, -741.4602, 13.7525);
			if (jump_ok == 1)
			{
				jump_23 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_24 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 442.103, -793.505, 14.361, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 16) && (jump_24 == 0))
		{
			look_jump(426.5163, -822.1759, 14.045);
			if (jump_ok == 1)
			{
				jump_24 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_25 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 651.05, -619, 6.84, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_25 == 0))
		{
			look_jump(661.2427, -607.774, 8.4116);
			if (jump_ok == 1)
			{
				jump_25 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_26 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 692.0561, -412.833, 6.84, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_26 == 0))
		{
			look_jump(692.0202, -430.3474, 5.296);
			if (jump_ok == 1)
			{
				jump_26 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_27 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 717.4732, 38.88571, 10, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_27 == 0))
		{
			look_jump(701.9545, 63.37839, 9.2438);
			if (jump_ok == 1)
			{
				jump_27 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_28 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 803.7901, -176.863, 13.895, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_28 == 0))
		{
			look_jump(794.3011, -202.6794, 17.4501);
			if (jump_ok == 1)
			{
				jump_28 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_29 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 894.589, 10.77002, 12.931, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_29 == 0))
		{
			look_jump(859.6391, 8.953125, 6.3656);
			if (jump_ok == 1)
			{
				jump_29 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_30 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 887.1049, 28.26401, 12.931, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_30 == 0))
		{
			look_jump(889.6417, 0.9078979, 13.3283);
			if (jump_ok == 1)
			{
				jump_30 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_31 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 893.91, 149.638, 8.222, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_31 == 0))
		{
			look_jump(895.6723, 133.1857, 12.049);
			if (jump_ok == 1)
			{
				jump_31 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_32 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 692.041, 52.392, 8.688, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_32 == 0))
		{
			look_jump(715.5344, 53.15881, 4.4141);
			if (jump_ok == 1)
			{
				jump_32 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_33 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 750.2051, 309.7988, 36.3731, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 17) && (jump_33 == 0))
		{
			look_jump(734.9448, 317.0932, 28.4501);
			if (jump_ok == 1)
			{
				jump_33 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_34 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 877.5, 414.6, 10, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_34 == 0))
		{
			look_jump(849.4033, 407.3275, 7.7649);
			if (jump_ok == 1)
			{
				jump_34 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_35 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 868.8542, 198.6788, 9.897701, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 19) && (jump_35 == 0))
		{
			look_jump(853.6179, 165.4967, 8.1343);
			if (jump_ok == 1)
			{
				jump_35 = 1;
				jump_ok = 0;
			}
		}
		//===================== jump_36 =====================
		GET_DISTANCE_BETWEEN_COORDS_3D( playX, playY, playZ, 86.18201, 242.259, 6.926, &playR); //
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (playR < 3.6) && (speed > 13) && (jump_36 == 0))
		{
			look_jump(115.9934, 234.211, 9.3976);
			if (jump_ok == 1)
			{
				jump_36 = 1;
				jump_ok = 0;
			}
		}

		if (all_jump == 36)
		{
			G_JUMP = 1;
			break;
		}
	}
}

void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	jump();

	while (TRUE) 
	{
		WAIT(0);
	}
}
