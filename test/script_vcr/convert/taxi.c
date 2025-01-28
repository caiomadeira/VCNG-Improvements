#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int blip1_ct1, blip2_ct1, spray_blip_onscreen;
int taxi_car1, taxi_countdown_already_started;
int taxi_ped1, taxi_passed_this_shot, taxi_fucked_flag;
int taxi_countdown, taxi_score, WMOCAistance_int, WMOCAistance_int_old;
int taxi_finish_time, taxi_start_time, total_taxi_time_taken; 
int score_for_this_fare, speedbonus, in_a_row_cash, in_a_row_number;

float WMOCAestx1, WMOCAesty1, WMOCAestz1;
float taxi_blipx, taxi_blipy, taxi_blipz;
float taxi_ped_x, taxi_ped_y, taxi_ped_z;
float x_diff, y_diff, x_diff_sq, y_diff_sq, WMOCAistance_sq, WMOCAistance; 
int fon, textur, max_peds_in_car, spray_taxi, been_in_taxi1_before, intaxi, animpld;
int first_pas;
int dm, cdm, wl;

void main(void);

void Start_taxi_mission(void);

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

void mission_cleanup_taxi1(void) {
	REMOVE_BLIP(blip1_ct1);
	REMOVE_BLIP(blip2_ct1);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&taxi_car1);
	//PRINT_BIG("TAXI6", 5000, 5);
	//PRINT_WITH_NUMBER_BIG("TSCORE", taxi_score, 6000, 6);

	if ((taxi_passed_this_shot >= 100) && (G_TAXI == 0))
	{
		G_TAXI = 1;
	}

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.5, "TAXI6");// пишем "Миссия завершина"

		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.4, "TSCORE", taxi_score);//

		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}

	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	CLEAR_HELP();
	TERMINATE_THIS_SCRIPT();
	//main();
}

void taxi_ped_leave2(void) {
	WAIT(0);
	if (!IS_CHAR_DEAD(taxi_ped1)) {
		if (!IS_CAR_DEAD(taxi_car1)) {
			if (!IS_CHAR_IN_CAR(taxi_ped1, taxi_car1)) {
				TASK_WANDER_STANDARD(taxi_ped1);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
			}
		}
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	return;
}

void mission_taxi1_failed(void) {
	if (!IS_CHAR_DEAD(taxi_ped1)) {
		if (!IS_CAR_DEAD(taxi_car1)) {
			TASK_LEAVE_CAR(taxi_ped1, taxi_car1);
			if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
				SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
			}
		}
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	mission_cleanup_taxi1();
}

void mission_taxi1_passed(void) {
	REMOVE_BLIP(blip1_ct1);
	REMOVE_BLIP(blip2_ct1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
	WAIT(0);
	PRINT("TAXI1", 1500, 1);
	Start_taxi_mission();
	return;
}

void taxi_fail_button_pressed(void) {
	while (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
		WAIT(0);
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
		}
	}
	mission_taxi1_failed();
}

void taxi_fucked(void) {
	WAIT(0);
	PRINT_NOW("TAXI3", 5000, 1);
	if (!IS_CHAR_DEAD(taxi_ped1)) {
		TASK_FLEE_CHAR_ANY_MEANS(taxi_ped1, taxi_car1, 250.0, -1, 0, 0, 0, 25.0);
	}
	taxi_fucked_flag = 1;
	mission_taxi1_failed();
}

void taxi_out_of_time(void) {
	PRINT_NOW("TAXI2A", 5000, 1);
	mission_taxi1_failed();
}

void score(void) {
	//if (TIMERB() > speedbonus) {
	//	score_for_this_fare = WMOCAistance_int_old / 10;
	//	PRINT_BIG("TAXI4", 5000, 5);
	//} else {
	//	score_for_this_fare = WMOCAistance_int_old / 8;
	//	PRINT_BIG("TAXI5", 5000, 5);
	//}
	
	ADD_SCORE(GetPlayerIndex(), score_for_this_fare);
	//PRINT_WITH_NUMBER_BIG("TSCORE2", score_for_this_fare, 6000, 6);

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "TSCORE2", score_for_this_fare);//


		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста

		if (TIMERB() > speedbonus) {
		score_for_this_fare = WMOCAistance_int_old / 10;
		//PRINT_BIG("TAXI4", 5000, 5);
		DISPLAY_TEXT(0.5, 0.4, "TAXI4");// пишем "Миссия завершина"
		} else {
			score_for_this_fare = WMOCAistance_int_old / 8;
			//PRINT_BIG("TAXI5", 5000, 5);
			DISPLAY_TEXT(0.5, 0.4, "TAXI5");// пишем "Миссия завершина"
		}
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}

	taxi_score = taxi_score + score_for_this_fare;
	taxi_passed_this_shot++;
	taxi_countdown = taxi_countdown + 10000;
	if (!IS_CHAR_DEAD(taxi_ped1)) {
		if (!IS_CAR_DEAD(taxi_car1)) {
			TASK_LEAVE_CAR(taxi_ped1, taxi_car1);
			if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
				SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
			}
			while (IS_CHAR_IN_CAR(taxi_ped1, taxi_car1)) {
				WAIT(0);
				if ((IS_CHAR_DEAD(taxi_ped1)) || (IS_CAR_DEAD(taxi_car1))) {
					taxi_ped_leave2();
				}
				if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
					taxi_ped_leave2();
				}
				if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
					taxi_ped_leave2();
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
					taxi_ped_leave2();
				}
			}
		}
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	//PRINT_WITH_2_NUMBERS_BIG("IN_ROW", taxi_passed_this_shot, in_a_row_cash, 5000, 6);
	if (taxi_passed_this_shot == in_a_row_number) {
		SETTIMERA(0); //сбрасываем таймер 
		while (true)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_2_NUMBERS(0.5, 0.4, "IN_ROW", taxi_passed_this_shot, in_a_row_cash);
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
		ADD_SCORE(GetPlayerIndex(), in_a_row_cash);
		taxi_score = taxi_score + in_a_row_cash;
		in_a_row_number = in_a_row_number + 5;
		in_a_row_cash = in_a_row_cash + 500;
	}
	first_pas = 1;
	mission_taxi1_passed();
}

void passenger_destination(void) {
	WAIT(0);
	if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
		mission_taxi1_failed();
	}
	GENERATE_RANDOM_INT_IN_RANGE(1, 16, &been_in_taxi1_before);
	if ((IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "FRANI")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "CASGC")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "PORTU")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI"))) {
		if (been_in_taxi1_before == 1) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
				passenger_destination();
			}
			PRINT_NOW("MFARE1", 5000, 1);
			WMOCAestx1 = -246.1;	   
			WMOCAesty1 = 1726.5;
			WMOCAestz1 = 4.4;
		}
		if (been_in_taxi1_before == 2) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "FRANI")) {
				passenger_destination();
			}
			PRINT_NOW("MFARE2", 5000, 1);
			WMOCAestx1 = -1024.7;   
			WMOCAesty1 = -292.1;
			WMOCAestz1 = 8.1;
		}
		if (been_in_taxi1_before == 3) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE3", 5000, 1);
			WMOCAestx1 = -576.0;  
			WMOCAesty1 = -347.9;
			WMOCAestz1 = 6.9;
		}
		if (been_in_taxi1_before == 4) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE4", 5000, 1);
			WMOCAestx1 = -585.4;   
			WMOCAesty1 = 728.9; 
			WMOCAestz1 = 5.1;
		}
		if (been_in_taxi1_before == 5) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE5", 5000, 1);
			WMOCAestx1 = -538.2;   
			WMOCAesty1 = -144.2; 
			WMOCAestz1 = 5.4;
		}
		if (been_in_taxi1_before == 6) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE6", 5000, 1);
			WMOCAestx1 = -167.6;   
			WMOCAesty1 = 1200.3; 
			WMOCAestz1 = 4.9;
		}
		if (been_in_taxi1_before == 7) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE7", 5000, 1);
			WMOCAestx1 = -432.6;  
			WMOCAesty1 = -144.0; 
			WMOCAestz1 = 5.0;
		}
		if (been_in_taxi1_before == 8) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE8", 5000, 1);
			WMOCAestx1 = -228.7;   
			WMOCAesty1 = 1288.7; 
			WMOCAestz1 = 4.8;
		}
		if (been_in_taxi1_before == 9) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE9", 5000, 1);
			WMOCAestx1 = -367.4;   
			WMOCAesty1 = 1700.8; 
			WMOCAestz1 = 4.6;
		}
		if (been_in_taxi1_before == 10) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE10", 5000, 1);
			WMOCAestx1 = -438.9;   
			WMOCAesty1 = 66.2; 
			WMOCAestz1 = 4.8;
		}
		if (been_in_taxi1_before == 11) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE11", 5000, 1);
			WMOCAestx1 = -591.6;  
			WMOCAesty1 = 1865.8; 
			WMOCAestz1 = 2.4;
		}
		if (been_in_taxi1_before == 12) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE12", 5000, 1);
			WMOCAestx1 = -631.6;
			WMOCAesty1 = 617.0;
			WMOCAestz1 = 5.2;
		}
		if (been_in_taxi1_before == 13) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE13", 5000, 1);
			WMOCAestx1 = -445.6;
			WMOCAesty1 = 1328.7;
			WMOCAestz1 = 5.0;
		}
		if (been_in_taxi1_before == 14) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "PORTU")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE14", 5000, 1);
			WMOCAestx1 = -312.0;
			WMOCAesty1 = -731.0;
			WMOCAestz1 = 5.1;
		}
		if (been_in_taxi1_before == 15) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI")) {
				passenger_destination();
			}
			PRINT_NOW("WFARE15", 5000, 1);
			WMOCAestx1 = -417.6;
			WMOCAesty1 = 441.4;
			WMOCAestz1 = 5.1;
		}
	} else {
		if (been_in_taxi1_before == 1) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "MIDPA")) {
				passenger_destination();
			}
			PRINT_NOW("FARE1", 5000, 1);
			WMOCAestx1 = 533.7;
			WMOCAesty1 = -943.8;
			WMOCAestz1 = 4.4;
		}
		if (been_in_taxi1_before == 2) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE2", 5000, 1);
			WMOCAestx1 = 938.8;
			WMOCAesty1 = 440.9;
			WMOCAestz1 = 4.4;
		}
		if (been_in_taxi1_before == 3) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "MIDPA")) {
				passenger_destination();
			}
			PRINT_NOW("FARE3", 5000, 1);
			WMOCAestx1 = 189.7;
			WMOCAesty1 = -768.8;
			WMOCAestz1 = 1.9;
		}
		if (been_in_taxi1_before == 4) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "MIDPA")) {
				passenger_destination();
			}
			PRINT_NOW("FARE4", 5000, 1);
			WMOCAestx1 = 380.5;
			WMOCAesty1 = -948.7;
			WMOCAestz1 = 3.1;
		}
		if (been_in_taxi1_before == 5) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "THTRI")) {
				passenger_destination();
			}
			PRINT_NOW("FARE5", 5000, 1);
			WMOCAestx1 = 634.6;
			WMOCAesty1 = 42.7;
			WMOCAestz1 = 5.3;
		}
		if (been_in_taxi1_before == 6) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE6", 5000, 1);
			WMOCAestx1 = 916.3;
			WMOCAesty1 = 1657.3;
			WMOCAestz1 = 10.4;
		}
		if (been_in_taxi1_before == 7) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE7", 5000, 1);
			WMOCAestx1 = 827.8;
			WMOCAesty1 = 736.8;
			WMOCAestz1 = 4.9;
		}
		if (been_in_taxi1_before == 8) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "MIDPA")) {
				passenger_destination();
			}
			PRINT_NOW("FARE8", 5000, 1);
			WMOCAestx1 = 915.3;
			WMOCAesty1 = -685.7;
			WMOCAestz1 = 4.7;
		}
		if (been_in_taxi1_before == 9) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "THTRI")) {
				passenger_destination();
			}
			PRINT_NOW("FARE9", 5000, 1);
			WMOCAestx1 = 1033.0;
			WMOCAesty1 = -85.2;
			WMOCAestz1 = 6.2;
		}
		if (been_in_taxi1_before == 10) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE10", 5000, 1);
			WMOCAestx1 = 1169.2;
			WMOCAesty1 = 1026.1;
			WMOCAestz1 = 5.9;
		}
		if (been_in_taxi1_before == 11) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "MIDPA")) {
				passenger_destination();
			}
			PRINT_NOW("FARE11", 5000, 1);
			WMOCAestx1 = 334.7;
			WMOCAesty1 = -442.7;
			WMOCAestz1 = 4.4;
		}
		if (been_in_taxi1_before == 12) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE12", 5000, 1);
			WMOCAestx1 = 864.1;
			WMOCAesty1 = 1238.3;
			WMOCAestz1 = 5.4;
		}
		if (been_in_taxi1_before == 13) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "THTRI")) {
				passenger_destination();
			}
			PRINT_NOW("FARE13", 5000, 1);
			WMOCAestx1 = 836.9;
			WMOCAesty1 = 66.5;
			WMOCAestz1 = 4.1;
		}
		if (been_in_taxi1_before == 14) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE14", 5000, 1);
			WMOCAestx1 = 953.7;
			WMOCAesty1 = 1040.5;
			WMOCAestz1 = 5.1;
		}
		if (been_in_taxi1_before == 15) {
			if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
				passenger_destination();
			}
			PRINT_NOW("FARE15", 5000, 1);
			WMOCAestx1 = 866.0;
			WMOCAesty1 = 601.1;
			WMOCAestz1 = 5.0;
		}
	}
	ADD_BLIP_FOR_COORD(WMOCAestx1, WMOCAesty1, WMOCAestz1, &blip2_ct1);
	CHANGE_BLIP_SPRITE(blip2_ct1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(blip2_ct1, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_SCALE(blip2_ct1, 0.6); // масштаб иконки на радаре
	CHANGE_BLIP_DISPLAY(blip2_ct1, 2);
	
	if (IS_CAR_DEAD(taxi_car1)) {
		mission_taxi1_failed();
	}
	x_diff = taxi_ped_x - taxi_blipx;
	y_diff = taxi_ped_y - taxi_blipy;

	x_diff_sq = x_diff * x_diff;
	y_diff_sq = y_diff * y_diff;

	WMOCAistance_sq = x_diff_sq + y_diff_sq;
	WMOCAistance = SQRT(WMOCAistance_sq);
	WMOCAistance_int = WMOCAistance;
	WMOCAistance_int_old = WMOCAistance_int; 
	
	if ((IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "FRANI")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "CASGC")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "PORTU")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI"))) {
		if (taxi_passed_this_shot == 0) {
			WMOCAistance_int = WMOCAistance_int * 80;
		}
		if (taxi_passed_this_shot == 1) {
			WMOCAistance_int = WMOCAistance_int * 75;
		}
		if (taxi_passed_this_shot == 2) {
			WMOCAistance_int = WMOCAistance_int * 70;
		}
		if (taxi_passed_this_shot == 3) {
			WMOCAistance_int = WMOCAistance_int * 69;
		}
		if (taxi_passed_this_shot == 4) {
			WMOCAistance_int = WMOCAistance_int * 68;
		}
		if (taxi_passed_this_shot == 5) {
			WMOCAistance_int = WMOCAistance_int * 66;
		}
		if ((taxi_passed_this_shot > 5) && (taxi_passed_this_shot <= 10)) {
			WMOCAistance_int = WMOCAistance_int * 65;
		}
		if ((taxi_passed_this_shot > 11) && (taxi_passed_this_shot <= 20)) {
			WMOCAistance_int = WMOCAistance_int * 60;
		}
		if ((taxi_passed_this_shot > 20) && (taxi_passed_this_shot <= 50)) {
			WMOCAistance_int = WMOCAistance_int * 55;
		}
		if (taxi_passed_this_shot > 50) {
			WMOCAistance_int = WMOCAistance_int * 50;
		}
	} else {
		if (taxi_passed_this_shot == 0) {
			WMOCAistance_int = WMOCAistance_int * 90;
		}
		if (taxi_passed_this_shot == 1) {
			WMOCAistance_int = WMOCAistance_int * 85;
		}
		if (taxi_passed_this_shot == 2) {
			WMOCAistance_int = WMOCAistance_int * 80;
		}
		if (taxi_passed_this_shot == 3) {
			WMOCAistance_int = WMOCAistance_int * 79;
		}
		if (taxi_passed_this_shot == 4) {
			WMOCAistance_int = WMOCAistance_int * 78;
		}
		if (taxi_passed_this_shot == 5) {
			WMOCAistance_int = WMOCAistance_int * 76;
		}
		if ((taxi_passed_this_shot > 5) && (taxi_passed_this_shot <= 10)) {
			WMOCAistance_int = WMOCAistance_int * 75;
		}
		if ((taxi_passed_this_shot > 11) && (taxi_passed_this_shot <= 20)) {
			WMOCAistance_int = WMOCAistance_int * 70;
		}
		if ((taxi_passed_this_shot > 20) && (taxi_passed_this_shot <= 50)) {
			WMOCAistance_int = WMOCAistance_int * 65;
		}
		if (taxi_passed_this_shot > 50) {
			WMOCAistance_int = WMOCAistance_int * 60;
		}
	}
	
	if (first_pas == 0) {
		taxi_countdown = taxi_countdown + WMOCAistance_int * 2;
	} else {
		taxi_countdown = taxi_countdown + WMOCAistance_int;
	}
	speedbonus = WMOCAistance_int;
	speedbonus = speedbonus / 100;
	speedbonus = speedbonus * 65;
	
	SETTIMERB(0);
	if (taxi_countdown_already_started == 0) {
		taxi_countdown_already_started = 1;
	}
	if (taxi_passed_this_shot == 0) {
		taxi_countdown = taxi_countdown + 5000;
	}
	
	while (true) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			taxi_countdown -= 1000;
			SETTIMERC(0);
		}
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		int timemin, timesec, timetemp;
		timesec = taxi_countdown / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;


		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		//if ((timesec > 9) && (timemin > 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T1", timemin, timesec);
		//} else if ((timesec <= 9) && (timemin <= 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T3", timemin, timesec);
		//} else if ((timesec > 9) && (timemin <= 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T2", timemin, timesec);
		//} else if ((timesec <= 9) && (timemin > 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T0", timemin, timesec);
		//}

		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if (timemin > 9)
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", timemin);// минуты
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", timemin);// минуты
		}
		setup_draw_value();
		DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if ( timesec > 9 )
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", timesec);// секунды
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", timesec);// секунды
		}


		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "FARES");
		//if (taxi_passed_this_shot > 9) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_NUMBER(0.92315097, 0.80191852, "HOTR_NB", taxi_passed_this_shot);
		//} else {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_NUMBER(0.93015097, 0.80191852, "HOTR_NB", taxi_passed_this_shot);
		//}
		if (taxi_passed_this_shot > 9) {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", taxi_passed_this_shot);
		} else {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_ZERO", taxi_passed_this_shot);
		}

		DRAW_CHECKPOINT( WMOCAestx1, WMOCAesty1, WMOCAestz1, 5.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
		if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), WMOCAestx1, WMOCAesty1, WMOCAestz1, 4.0, 4.0, 4.0, 1)) && (IS_CAR_STOPPED(taxi_car1))) {
			break;
		}
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
		}
		if (IS_CAR_DEAD(taxi_car1)) {
			mission_taxi1_failed();
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
			mission_taxi1_failed();
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
			taxi_fail_button_pressed();
		}
		if (taxi_countdown <= 0) {
			taxi_out_of_time();
		}
		if ((IS_CAR_UPSIDEDOWN(taxi_car1)) && (IS_CAR_STOPPED(taxi_car1))) {
			taxi_fucked();
		}
	}
	score();
}

void ped_get_in_taxi(void) {
	animpld = 0;
	TASK_STAND_STILL(taxi_ped1, -2);
	while ((!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 7.0, 7.0, 2.0, 0)) || (!IS_CAR_STOPPED(taxi_car1))) {
		WAIT(0);
		if (first_pas == 1) {
			if (TIMERC() >= 1000) {
				taxi_countdown -= 1000;
				SETTIMERC(0);
			}
		}

		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		int timemin, timesec, timetemp;
		timesec = taxi_countdown / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		if (first_pas == 1) {
			//if ((timesec > 9) && (timemin > 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T1", timemin, timesec);
			//} else if ((timesec <= 9) && (timemin <= 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T3", timemin, timesec);
			//} else if ((timesec > 9) && (timemin <= 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T2", timemin, timesec);
			//} else if ((timesec <= 9) && (timemin > 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T0", timemin, timesec);
			//}
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if (timemin > 9)
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", timemin);// минуты
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", timemin);// минуты
			}
			setup_draw_value();
			DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if ( timesec > 9 )
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", timesec);// секунды
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", timesec);// секунды
			}
		} else {
			setup_draw_value();
			//DISPLAY_TEXT(0.9018542, 0.76831852, "TAXNULL");
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT(0.9203125, 0.76954074, "TAXNULL");
		}
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "FARES");
		//if (taxi_passed_this_shot > 9) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_NUMBER(0.92315097, 0.80191852, "HOTR_NB", taxi_passed_this_shot);
		//} else {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_NUMBER(0.93015097, 0.80191852, "HOTR_NB", taxi_passed_this_shot);
		//}
		if (taxi_passed_this_shot > 9) {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", taxi_passed_this_shot);
		} else {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_ZERO", taxi_passed_this_shot);
		}
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
		}
		if (IS_CAR_DEAD(taxi_car1)) {
			mission_taxi1_failed();
		}
		if (IS_CHAR_DEAD(taxi_ped1)) {
			mission_taxi1_passed();
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
			mission_taxi1_failed();
		}
		if (!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 90.0, 90.0, 20.0, 0)) {
			mission_taxi1_passed();
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
			taxi_fail_button_pressed();
		}
		if ((taxi_countdown_already_started == 1) && (taxi_countdown <= 0)) {
			mission_taxi1_failed();
		}
		if (!IS_CHAR_DEAD(taxi_ped1)) {
			if (TIMERA() > 1000) {
				TASK_TURN_CHAR_TO_FACE_CHAR(taxi_ped1, GetPlayerPed());	
				SETTIMERA(0);
			}
		}
	}
	animpld = 0;
	GET_MAXIMUM_NUMBER_OF_PASSENGERS(taxi_car1, &max_peds_in_car);
	int getseat;
	while (true) {
		GENERATE_RANDOM_INT_IN_RANGE(0, max_peds_in_car, &getseat);
		if (IS_CAR_PASSENGER_SEAT_FREE(taxi_car1, getseat)) {
			break;
		}			
	}
	MODIFY_CHAR_MOVE_STATE(taxi_ped1, 3);
	TASK_ENTER_CAR_AS_PASSENGER(taxi_ped1, taxi_car1, -1, getseat);
	while (!IS_CHAR_IN_CAR(taxi_ped1, taxi_car1)) {
		WAIT(0);

		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		int timemin, timesec, timetemp;
		timesec = taxi_countdown / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		if (first_pas == 1) {
			//if ((timesec > 9) && (timemin > 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T1", timemin, timesec);
			//} else if ((timesec <= 9) && (timemin <= 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T3", timemin, timesec);
			//} else if ((timesec > 9) && (timemin <= 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T2", timemin, timesec);
			//} else if ((timesec <= 9) && (timemin > 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T0", timemin, timesec);
			//}
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if (timemin > 9)
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", timemin);// минуты
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", timemin);// минуты
			}
			setup_draw_value();
			DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if ( timesec > 9 )
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", timesec);// секунды
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", timesec);// секунды
			}
		} else {
			setup_draw_value();
			//DISPLAY_TEXT(0.9018542, 0.76831852, "TAXNULL");
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT(0.9203125, 0.76954074, "TAXNULL");
		}
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "FARES");
		//if (taxi_passed_this_shot > 9) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_NUMBER(0.92315097, 0.80191852, "HOTR_NB", taxi_passed_this_shot);
		//} else {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_NUMBER(0.93015097, 0.80191852, "HOTR_NB", taxi_passed_this_shot);
		//}
		if (taxi_passed_this_shot > 9) {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", taxi_passed_this_shot);
		} else {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_ZERO", taxi_passed_this_shot);
		}
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
		}
		if (IS_CAR_DEAD(taxi_car1)) {
			mission_taxi1_failed();
		}
		if (IS_CHAR_DEAD(taxi_ped1)) {
			mission_taxi1_passed();
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
			mission_taxi1_failed();
		}
		if (!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 90.0, 90.0, 20.0, 0)) {
			mission_taxi1_passed();
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
			taxi_fail_button_pressed();
		}
		if ((taxi_countdown_already_started == 1) && (taxi_countdown <= 0)) {
			mission_taxi1_failed();
		}
		if (!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 7.0, 7.0, 2.0, 0)) {
			ped_get_in_taxi();
		}
	}
	GET_CHAR_COORDINATES(taxi_ped1, &taxi_ped_x, &taxi_ped_y, &taxi_ped_z);
	REMOVE_BLIP(blip1_ct1);
	passenger_destination();
}

void Start_taxi_mission(void) {
	//if (G_done_taxi_help == 0) {
		PRINT_HELP("TAXIH1");
	//}
	score_for_this_fare = 0;
	if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
		mission_taxi1_failed();
	}
	if (IS_CAR_DEAD(taxi_car1)) {
		mission_taxi1_failed();
	}
	if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
		mission_taxi1_failed();
	}
	if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
		taxi_fail_button_pressed();
	}
	if ((taxi_countdown_already_started == 1) && (taxi_countdown <= 0)) {
		mission_taxi1_failed();
	}
	taxi_ped1 = -1;
	while (taxi_ped1 == -1) {
		WAIT(0);
		float px, py, pz;
		GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
		GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(px, py, pz, 200.0, 200.0, 250.0, &taxi_ped1);
		if (taxi_ped1 != -1) {
			float pedx, pedy, pedz;
			int pint;
			GET_CHAR_COORDINATES(taxi_ped1, &pedx, &pedy, &pedz);
			GET_INTERIOR_AT_COORDS(pedx, pedy, pedz, &pint);
			if (pint == 0) {
				break;
			} else {
				MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
				taxi_ped1 = -1;
			}
		}
	}
	ADD_BLIP_FOR_CHAR(taxi_ped1, &blip1_ct1);
	CHANGE_BLIP_COLOUR(blip1_ct1, 5);
	CHANGE_BLIP_SCALE(blip1_ct1, 0.77999990); // масштаб иконки на радаре
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(blip1_ct1, "TAXPSG");
	LOAD_CHAR_DECISION_MAKER(2, &dm);
	LOAD_COMBAT_DECISION_MAKER(3, &cdm);
	SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
	SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);
	SET_CHAR_DECISION_MAKER(taxi_ped1, dm);
	SET_COMBAT_DECISION_MAKER(taxi_ped1, cdm);
	SET_CHAR_STAY_IN_CAR_WHEN_JACKED(taxi_ped1, 1);
	SET_CHAR_RELATIONSHIP_GROUP(taxi_ped1, 23);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(taxi_ped1, 0);
	SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(taxi_ped1, 0);
	SETTIMERC(0);
	ped_get_in_taxi();
}

void mission_start_taxi1(void) {
	taxi_countdown_already_started = 0;
	taxi_countdown = 0;
	taxi_passed_this_shot = 0;
	taxi_score = 0;
	taxi_ped1 = -1;
	taxi_fucked_flag = 0;
	in_a_row_number = 5;
	in_a_row_cash = 500;
	first_pas = 0;
	LOAD_ADDITIONAL_TEXT("TAXI1", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
		mission_taxi1_failed();
	}
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &taxi_car1);
	} else {
		mission_taxi1_failed();
	}
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "TAXI_M");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	PRINT_NOW("TAXI1", 1500, 1);
	WAIT(600);
	Start_taxi_mission();
}

void main(void) {
	mission_start_taxi1();
	mission_cleanup_taxi1();
	//while (true) {
	//	WAIT(0);
	//	STORE_WANTED_LEVEL(GetPlayerIndex(), &wl);
	//	if ((IS_CHAR_IN_TAXI(GetPlayerPed())) && (wl == 0)) {
	//		if (G_ONMISSION == 0) {
	//			if (intaxi == 0) {
	//				PRINT_HELP("TTUTOR");
	//				intaxi = 1;
	//			}
	//			if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
	//				G_ONMISSION = 1;
	//				PRINT_BIG("TAXI_M", 6000, 5);
	//				mission_start_taxi1();
	//				mission_cleanup_taxi1();
	//				G_ONMISSION = 0;
	//				WAIT(1000);
	//			}
	//		}
	//	} else {
	//		CLEAR_HELP();
	//		intaxi = 0;
	//	}
	//}
}