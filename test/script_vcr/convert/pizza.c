#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int flag_pizza_trigger;
int pizza_moped, customer1, customer2, customer3, customer4, customer5;
int customer6, customer7, customer8, customer9, customer10, pizza_box11;
int pizza_box2, pizza_box3, pizza_box4, pizza_box5, pizza_box6;

int customer1_blip, customer2_blip, customer3_blip, customer4_blip;
int customer5_blip, customer6_blip, customer7_blip, customer8_blip;
int customer9_blip, customer10_blip, pizza_hut_blip, pizza_moped_blip;

int pizza_goals, customers_created, customer1_created, customer2_created;
int customer3_created, customer4_created, customer5_created, customer6_created;
int customer7_created, customer8_created, customer9_created, customer10_created;
int pizza_delivered, go_back_to_pizza_hut_flag, total_pizzas_thrown;
int pizza_has_been_thrown, pizza_box_var, where_is_player1, customer_complaint_time;
int customer_got_pizza, customer_var, mission_failed_flag, which_pizza_to_del;
int flag_player_not_in_pizza_moped, flag_pizza_moped_upsidedown, pizza_help_text_played;
int add_pizza_score, random_speech, pizza_speech_played;

float x_random, y_random, cust_coordx, cust_coordy, cust_coordz, ped_heading;
float sum_dif_xy, dif_plyr_cust_x, dif_plyr_cust_y, player1s_distance_from_customer;
float dif_cust_shop_x, dif_cust_shop_y, customers_distance_from_pizza_shop;
float random_customer_heading, pizza_shopx, pizza_shopy, pizza_shopz;
float player1_facing_this_direction, pizza_lobx, pizza_loby;
float pizzax, pizzay, pizzaz;
float player_x, player_y, player_z;
int fon, textur, blob_flag, char_near, pizza_help_text_played2;

void main(void);

void get_rnd_locations(void);

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

void draw_hud(int changetimer) {
	if (changetimer == 1) {
		if (TIMERC() >= 1000) {
			customer_complaint_time -= 1000;
			SETTIMERC(0);
		}
	}

	if (customer1_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer1))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer1, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer2_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer2))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer2, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer3_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer3))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer3, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer4_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer4))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer4, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer5_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer5))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer5, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer6_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer6))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer6, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer7_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer7))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer7, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer8_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer8))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer8, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer9_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer9))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer9, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if (customer10_created == 1)
	{
		if (IS_CHAR_IN_WATER(customer10))
		{
			get_rnd_locations();
			SET_CHAR_COORDINATES(customer10, cust_coordx, cust_coordy, cust_coordz);
		}
	}
	if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), pizza_shopx, pizza_shopy, pizza_shopz, 5.0, 5.0, 5.0, 1)) && (IS_CAR_STOPPED(pizza_moped)))
	{
		if ((total_pizzas_thrown < 6) && (go_back_to_pizza_hut_flag == 0))
		{
			total_pizzas_thrown = 6;
			customer_complaint_time += 30000;
		}
	}


	DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
	DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
	int timemin, timesec, timetemp;
	timesec = customer_complaint_time / 1000;
	timemin = timesec / 60;
	timetemp = timemin * 60;
	timesec -= timetemp;
	setup_draw_text();	
	//DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
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
	//DISPLAY_TEXT(0.78815097, 0.81091852, "PIZ1_12");
	//if (total_pizzas_thrown > 9) {
	//	setup_draw_value();
	//	DISPLAY_TEXT_WITH_NUMBER(0.92315097, 0.80191852, "HOTR_NB", total_pizzas_thrown);
	//} else {
	//	setup_draw_value();
	//	DISPLAY_TEXT_WITH_NUMBER(0.93015097, 0.80191852, "HOTR_NB", total_pizzas_thrown);
	//}
	DISPLAY_TEXT(0.78815097, 0.73564852, "PIZ1_12");
	if (total_pizzas_thrown > 9) {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", total_pizzas_thrown);
		} else {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_ZERO", total_pizzas_thrown);
		}

}

void mission_cleanup_pizza(void) {
	//G_ONMISSION = 0;
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("faggio"));
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("hellfury"));
	REMOVE_BLIP(customer1_blip);
	REMOVE_BLIP(customer2_blip);
	REMOVE_BLIP(customer3_blip);
	REMOVE_BLIP(customer4_blip);
	REMOVE_BLIP(customer5_blip);
	REMOVE_BLIP(customer6_blip);
	REMOVE_BLIP(customer7_blip);
	REMOVE_BLIP(customer8_blip);
	REMOVE_BLIP(customer9_blip);
	REMOVE_BLIP(customer10_blip);
	REMOVE_BLIP(pizza_hut_blip);
	REMOVE_BLIP(pizza_moped_blip);
	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), 1);
	flag_pizza_trigger = 1;
	TERMINATE_THIS_SCRIPT();
	//main();
}

void mission_passed_pizza(void) {
	CLEAR_PRINTS();
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	//PRINT_WITH_NUMBER_BIG("P_PASS", 5000, 5000, 1);
	while (true)
	{
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "P_PASS", 5000);//

		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	ADD_SCORE(GetPlayerIndex(), 5000);
	if (G_PIZZA == 0) {
		PRINT_HELP("PIZ1_WON");
		G_PIZZA = 1;
	}
	mission_cleanup_pizza();
}

void mission_failed_pizza(void) {
	//PRINT_BIG("P_FAIL", 5000, 1);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "MISSION_FAILED");// пишем "Миссия провалена"

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	mission_cleanup_pizza();
}

void plyr_quit_game(void) {
	if (flag_player_not_in_pizza_moped == 0) {
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
			CLEAR_PRINTS();
			mission_failed_flag = 3;
		}
	}
	return;
}

void plyr_off_moped(void) {
	if (!IS_CAR_DEAD(pizza_moped)) {
		if ((IS_CAR_UPSIDEDOWN(pizza_moped)) && (IS_CAR_STOPPED(pizza_moped))) {
			flag_pizza_moped_upsidedown = 1;
		}
		if ((!IS_CHAR_IN_CAR(GetPlayerPed(), pizza_moped)) && (flag_player_not_in_pizza_moped == 0) && (flag_pizza_moped_upsidedown == 0)) {
			PRINT_NOW("PIZ1_11", 5000, 1);
			ADD_BLIP_FOR_CAR(pizza_moped, &pizza_moped_blip);
			CHANGE_BLIP_SPRITE(pizza_moped_blip, BLIP_OBJECTIVE);
			CHANGE_BLIP_COLOUR(pizza_moped_blip, 19);
			CHANGE_BLIP_SCALE(pizza_moped_blip, 0.6);
			REMOVE_BLIP(customer1_blip);
			REMOVE_BLIP(customer2_blip);
			REMOVE_BLIP(customer3_blip);
			REMOVE_BLIP(customer4_blip);
			REMOVE_BLIP(customer5_blip);
			REMOVE_BLIP(customer6_blip);
			REMOVE_BLIP(customer7_blip);
			REMOVE_BLIP(customer8_blip);
			REMOVE_BLIP(customer9_blip);
			REMOVE_BLIP(customer10_blip);
			REMOVE_BLIP(pizza_hut_blip);
			flag_player_not_in_pizza_moped = 1;
		}
		if ((IS_CHAR_IN_CAR(GetPlayerPed(), pizza_moped)) && (flag_player_not_in_pizza_moped == 1)) {
			REMOVE_BLIP(pizza_moped_blip);
			if (go_back_to_pizza_hut_flag == 0) {
				if (customer1_created == 1) {
					if (!IS_CHAR_DEAD(customer1)) {
						ADD_BLIP_FOR_CHAR(customer1, &customer1_blip);
						CHANGE_BLIP_COLOUR(customer1_blip, 19);
						CHANGE_BLIP_SCALE(customer1_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer1_blip, "PIZ_BL");
					}
				}
				if (customer2_created == 1) {
					if (!IS_CHAR_DEAD(customer2)) {
						ADD_BLIP_FOR_CHAR(customer2, &customer2_blip);
						CHANGE_BLIP_COLOUR(customer2_blip, 19);
						CHANGE_BLIP_SCALE(customer2_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer2_blip, "PIZ_BL");
					}
				}
				if (customer3_created == 1) {
					if (!IS_CHAR_DEAD(customer3)) {
						ADD_BLIP_FOR_CHAR(customer3, &customer3_blip);
						CHANGE_BLIP_COLOUR(customer3_blip, 19);
						CHANGE_BLIP_SCALE(customer3_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer3_blip, "PIZ_BL");
					}
				}
				if (customer4_created == 1) {
					if (!IS_CHAR_DEAD(customer4)) {
						ADD_BLIP_FOR_CHAR(customer4, &customer4_blip);
						CHANGE_BLIP_COLOUR(customer4_blip, 19);
						CHANGE_BLIP_SCALE(customer4_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer4_blip, "PIZ_BL");
					}
				}
				if (customer5_created == 1) {
					if (!IS_CHAR_DEAD(customer5)) {
						ADD_BLIP_FOR_CHAR(customer5, &customer5_blip);
						CHANGE_BLIP_COLOUR(customer5_blip, 19);
						CHANGE_BLIP_SCALE(customer5_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer5_blip, "PIZ_BL");
					}
				}
				if (customer6_created == 1) {
					if (!IS_CHAR_DEAD(customer6)) {
						ADD_BLIP_FOR_CHAR(customer6, &customer6_blip);
						CHANGE_BLIP_COLOUR(customer6_blip, 19);
						CHANGE_BLIP_SCALE(customer6_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer6_blip, "PIZ_BL");
					}
				}
				if (customer7_created == 1) {
					if (!IS_CHAR_DEAD(customer7)) {
						ADD_BLIP_FOR_CHAR(customer7, &customer7_blip);
						CHANGE_BLIP_COLOUR(customer7_blip, 19);
						CHANGE_BLIP_SCALE(customer7_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer7_blip, "PIZ_BL");
					}
				}
				if (customer8_created == 1) {
					if (!IS_CHAR_DEAD(customer8)) {
						ADD_BLIP_FOR_CHAR(customer8, &customer8_blip);
						CHANGE_BLIP_COLOUR(customer8_blip, 19);
						CHANGE_BLIP_SCALE(customer8_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer8_blip, "PIZ_BL");
					}
				}
				if (customer9_created == 1) {
					if (!IS_CHAR_DEAD(customer9)) {
						ADD_BLIP_FOR_CHAR(customer9, &customer9_blip);
						CHANGE_BLIP_COLOUR(customer9_blip, 19);
						CHANGE_BLIP_SCALE(customer9_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer9_blip, "PIZ_BL");
					}
				}
				if (customer10_created == 1) {
					if (!IS_CHAR_DEAD(customer10)) {
						ADD_BLIP_FOR_CHAR(customer10, &customer10_blip);
						CHANGE_BLIP_COLOUR(customer10_blip, 19);
						CHANGE_BLIP_SCALE(customer10_blip, 0.77999990);
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer10_blip, "PIZ_BL");
					}
				}
			} else {
				REMOVE_BLIP(pizza_hut_blip);
				ADD_BLIP_FOR_COORD(pizza_shopx, pizza_shopy, -100.0, &pizza_hut_blip);
				CHANGE_BLIP_SPRITE(pizza_hut_blip, BLIP_OBJECTIVE);
				CHANGE_BLIP_COLOUR(pizza_hut_blip, 5);
				CHANGE_BLIP_SCALE(pizza_hut_blip, 0.6);
			}
			CLEAR_PRINTS();
			flag_player_not_in_pizza_moped = 0;
		}
	} else {
		mission_failed_flag = 2;
	}
	return;
}

void pizza_throw(void) {
	if (pizza_has_been_thrown == 0) {
		float px, py, pz;
		GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
		GET_CHAR_HEADING(GetPlayerPed(), &player1_facing_this_direction);
		player1_facing_this_direction -= 90.0;
		px += COS(player1_facing_this_direction) * 0.7;
		py += SIN(player1_facing_this_direction) * 0.7;
		GET_GROUND_Z_FOR_3D_COORD(px, py, pz, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("pizza_box_1"), px, py, pz, &pizza_box_var, 1);
		SET_OBJECT_PHYSICS_PARAMS(pizza_box_var, 7.27, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1082130432, -1082130432);
		SET_OBJECT_COLLISION(pizza_box_var, 1);
		SET_OBJECT_DYNAMIC(pizza_box_var, 1);
		total_pizzas_thrown--;
		pizza_has_been_thrown = 1;
	}
	return;
}

void dying_customers(void) {
	if (customer1_created == 1) {
		if (IS_CHAR_DEAD(customer1)) {
			mission_failed_flag = 1;
		}
	}
	if (customer2_created == 1) {
		if (IS_CHAR_DEAD(customer2)) {
			mission_failed_flag = 1;
		}
	}
	if (customer3_created == 1) {
		if (IS_CHAR_DEAD(customer3)) {
			mission_failed_flag = 1;
		}
	}
	if (customer4_created == 1) {
		if (IS_CHAR_DEAD(customer4)) {
			mission_failed_flag = 1;
		}
	}
	if (customer5_created == 1) {
		if (IS_CHAR_DEAD(customer5)) {
			mission_failed_flag = 1;
		}
	}
	if (customer6_created == 1) {
		if (IS_CHAR_DEAD(customer6)) {
			mission_failed_flag = 1;
		}
	}
	if (customer7_created == 1) {
		if (IS_CHAR_DEAD(customer7)) {
			mission_failed_flag = 1;
		}
	}
	if (customer8_created == 1) {
		if (IS_CHAR_DEAD(customer8)) {
			mission_failed_flag = 1;
		}
	}
	if (customer9_created == 1) {
		if (IS_CHAR_DEAD(customer9)) {
			mission_failed_flag = 1;
		}
	}
	if (customer10_created == 1) {
		if (IS_CHAR_DEAD(customer10)) {
			mission_failed_flag = 1;
		}
	}
	return;
}

void no_longer_needed_pizzas(void) {
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&pizza_box11);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&pizza_box2);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&pizza_box3);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&pizza_box4);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&pizza_box5);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&pizza_box6);
	GENERATE_RANDOM_INT_IN_RANGE(1, 20, &random_speech);
	if (pizza_speech_played == 0) {
		if (random_speech == 1) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CB", "PIZ1_13", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 2) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CF", "PIZ1_14", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 3) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CG", "PIZ1_15", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}	
		if (random_speech == 4) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CL", "PIZ1_16", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 5) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CO", "PIZ1_17", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 6) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CT", "PIZ1_18", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 7) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CV", "PIZ1_19", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 8) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_CW", "PIZ1_20", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 9) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DB", "PIZ1_21", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 10) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DE", "PIZ1_22", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 11) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DK", "PIZ1_23", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 12) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DL", "PIZ1_24", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 13) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DM", "PIZ1_25", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 14) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DQ", "PIZ1_26", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 15) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_DX", "PIZ1_27", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 16) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_FA", "PIZ1_28", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 17) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_FG", "PIZ1_29", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 18) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_FH", "PIZ1_30", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		if (random_speech == 19) {
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "B2_FL", "PIZ1_31", 0, 0);
			START_SCRIPT_CONVERSATION(1, 1);
		}
		pizza_speech_played = 1;
	}
	return;
}

void del_pizzas(void) {
	if (which_pizza_to_del == 1) {
		DELETE_OBJECT(&pizza_box11);
	}
	if (which_pizza_to_del == 2) {
		DELETE_OBJECT(&pizza_box2);
	}
	if (which_pizza_to_del == 3) {
		DELETE_OBJECT(&pizza_box3);
	}
	if (which_pizza_to_del == 4) {
		DELETE_OBJECT(&pizza_box4);
	}
	if (which_pizza_to_del == 5) {
		DELETE_OBJECT(&pizza_box5);
	}
	if (which_pizza_to_del == 6) {
		DELETE_OBJECT(&pizza_box6);
	}
	return;
}

void catch_da_pizza(void) {
	if (DOES_OBJECT_EXIST(pizza_box11)) {
		if (!IS_CHAR_DEAD(customer_var)) {
			if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box11, 10.0, 10.0, 0)) {
				which_pizza_to_del = 1;
				WAIT(20);
				SETTIMERB(0);
				while (true) {
					WAIT(0);
					draw_hud(0);
					if (TIMERB() > 3000) {
						break;
					}
					if (!IS_CHAR_DEAD(customer_var)) {
						if (DOES_OBJECT_EXIST(pizza_box11)) {
							GET_OBJECT_COORDINATES(pizza_box11, &pizzax, &pizzay, &pizzaz);
							TASK_GO_STRAIGHT_TO_COORD(customer_var, pizzax, pizzay, pizzaz, 4, -1);
							if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box11, 1.0, 1.0, 0)) {
								break;
							}
						}
					} else {
						mission_failed_flag = 1;
					}
					plyr_off_moped();
					plyr_quit_game();
				}
				customer_got_pizza = 1;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (DOES_OBJECT_EXIST(pizza_box2)) {
		if (!IS_CHAR_DEAD(customer_var)) {
			if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box2, 10.0, 10.0, 0)) {
				which_pizza_to_del = 2;
				WAIT(20);
				SETTIMERB(0);
				while (true) {
					WAIT(0);
					draw_hud(0);
					if (TIMERB() > 3000) {
						break;
					}
					if (!IS_CHAR_DEAD(customer_var)) {
						if (DOES_OBJECT_EXIST(pizza_box2)) {
							GET_OBJECT_COORDINATES(pizza_box2, &pizzax, &pizzay, &pizzaz);
							TASK_GO_STRAIGHT_TO_COORD(customer_var, pizzax, pizzay, 5.0, 4, -1);
							if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box2, 1.0, 1.0, 0)) {
								break;
							}
						}
					} else {
						mission_failed_flag = 1;
					}
					plyr_off_moped();
					plyr_quit_game();
				}
				customer_got_pizza = 1;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (DOES_OBJECT_EXIST(pizza_box3)) {
		if (!IS_CHAR_DEAD(customer_var)) {
			if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box3, 10.0, 10.0, 0)) {
				which_pizza_to_del = 3;
				WAIT(20);
				SETTIMERB(0);
				while (true) {
					WAIT(0);
					draw_hud(0);
					if (TIMERB() > 3000) {
						break;
					}
					if (!IS_CHAR_DEAD(customer_var)) {
						if (DOES_OBJECT_EXIST(pizza_box3)) {
							GET_OBJECT_COORDINATES(pizza_box3, &pizzax, &pizzay, &pizzaz);
							TASK_GO_STRAIGHT_TO_COORD(customer_var, pizzax, pizzay, 5.0, 4, -1);
							if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box3, 1.0, 1.0, 0)) {
								break;
							}
						}
					} else {
						mission_failed_flag = 1;
					}
					plyr_off_moped();
					plyr_quit_game();
				}
				customer_got_pizza = 1;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (DOES_OBJECT_EXIST(pizza_box4)) {
		if (!IS_CHAR_DEAD(customer_var)) {
			if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box4, 10.0, 10.0, 0)) {
				which_pizza_to_del = 4;
				WAIT(20);
				SETTIMERB(0);
				while (true) {
					WAIT(0);
					draw_hud(0);
					if (TIMERB() > 3000) {
						break;
					}
					if (!IS_CHAR_DEAD(customer_var)) {
						if (DOES_OBJECT_EXIST(pizza_box4)) {
							GET_OBJECT_COORDINATES(pizza_box4, &pizzax, &pizzay, &pizzaz);
							TASK_GO_STRAIGHT_TO_COORD(customer_var, pizzax, pizzay, 5.0, 4, -1);
							if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box4, 1.0, 1.0, 0)) {
								break;
							}
						}
					} else {
						mission_failed_flag = 1;
					}
					plyr_off_moped();
					plyr_quit_game();
				}
				customer_got_pizza = 1;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (DOES_OBJECT_EXIST(pizza_box5)) {
		if (!IS_CHAR_DEAD(customer_var)) {
			if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box5, 10.0, 10.0, 0)) {
				which_pizza_to_del = 4;
				WAIT(20);
				SETTIMERB(0);
				while (true) {
					WAIT(0);
					draw_hud(0);
					if (TIMERB() > 3000) {
						break;
					}
					if (!IS_CHAR_DEAD(customer_var)) {
						if (DOES_OBJECT_EXIST(pizza_box5)) {
							GET_OBJECT_COORDINATES(pizza_box5, &pizzax, &pizzay, &pizzaz);
							TASK_GO_STRAIGHT_TO_COORD(customer_var, pizzax, pizzay, 5.0, 4, -1);
							if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box5, 1.0, 1.0, 0)) {
								break;
							}
						}
					} else {
						mission_failed_flag = 1;
					}
					plyr_off_moped();
					plyr_quit_game();
				}
				customer_got_pizza = 1;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (DOES_OBJECT_EXIST(pizza_box6)) {
		if (!IS_CHAR_DEAD(customer_var)) {
			if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box6, 10.0, 10.0, 0)) {
				which_pizza_to_del = 4;
				WAIT(20);
				SETTIMERB(0);
				while (true) {
					WAIT(0);
					draw_hud(0);
					if (TIMERB() > 3000) {
						break;
					}
					if (!IS_CHAR_DEAD(customer_var)) {
						if (DOES_OBJECT_EXIST(pizza_box6)) {
							GET_OBJECT_COORDINATES(pizza_box6, &pizzax, &pizzay, &pizzaz);
							TASK_FOLLOW_NAV_MESH_TO_COORD(customer_var, pizzax, pizzay, 5.0, 4, -2, -1);
							if (LOCATE_CHAR_ON_FOOT_OBJECT_2D(customer_var, pizza_box6, 1.0, 1.0, 0)) {
								break;
							}
						}
					} else {
						mission_failed_flag = 1;
					}
					plyr_off_moped();
					plyr_quit_game();
				}
				customer_got_pizza = 1;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	return;
}

void delivering_pizzas(void) {
	char_near = 0;
	if (customer1_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer1, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer2_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer2, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer3_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer3, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer4_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer4, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer5_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer5, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer6_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer6, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer7_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer7, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer8_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer8, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer9_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer9, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	if (customer10_created == 1) {
		if (LOCATE_CHAR_ON_FOOT_CAR_3D(customer10, pizza_moped, 3.0, 3.0, 3.0, 0)) {
			char_near = 1;
		}
	}
	
	if (!IS_CAR_DEAD(pizza_moped)) {
		if (IS_CHAR_IN_CAR(GetPlayerPed(), pizza_moped)) {
			if (char_near == 1) {
				if (IS_CONTROL_PRESSED(2, 4)) {
					if (total_pizzas_thrown == 6) {
						pizza_throw();
						pizza_box11 = pizza_box_var;
					}
					if (total_pizzas_thrown == 5) {
						pizza_throw();
						pizza_box2 = pizza_box_var;
					}
					if (total_pizzas_thrown == 4) {
						pizza_throw();
						pizza_box3 = pizza_box_var;
					}
					if (total_pizzas_thrown == 3) {
						pizza_throw();
						pizza_box4 = pizza_box_var;
					}
					if (total_pizzas_thrown == 2) {
						pizza_throw();
						pizza_box5 = pizza_box_var;
					}
					if (total_pizzas_thrown == 1) {
						pizza_throw();
						pizza_box6 = pizza_box_var;
					}
				} else {
					pizza_has_been_thrown = 0;
				}
			}
		}
	}
	if (customer1_created == 1) {
		if (!IS_CHAR_DEAD(customer1)) {
			customer_var = customer1;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer1)) {
					TASK_STAND_STILL(customer1, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer1);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer1_blip);
				customer1_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer2_created == 1) {
		if (!IS_CHAR_DEAD(customer2)) {
			customer_var = customer2;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer2)) {
					TASK_STAND_STILL(customer2, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer2);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer2_blip);
				customer2_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer3_created == 1) {
		if (!IS_CHAR_DEAD(customer3)) {
			customer_var = customer3;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer3)) {
					TASK_STAND_STILL(customer3, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer3);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer3_blip);
				customer3_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer4_created == 1) {
		if (!IS_CHAR_DEAD(customer4)) {
			customer_var = customer4;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer4)) {
					TASK_STAND_STILL(customer4, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer4);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer4_blip);
				customer4_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer5_created == 1) {
		if (!IS_CHAR_DEAD(customer5)) {
			customer_var = customer5;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer5)) {
					TASK_STAND_STILL(customer5, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer5);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer5_blip);
				customer5_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer6_created == 1) {
		if (!IS_CHAR_DEAD(customer6)) {
			customer_var = customer6;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer6)) {
					TASK_STAND_STILL(customer6, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer6);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer6_blip);
				customer6_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer7_created == 1) {
		if (!IS_CHAR_DEAD(customer7)) {
			customer_var = customer7;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer7)) {
					TASK_STAND_STILL(customer7, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer7);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer7_blip);
				customer7_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer8_created == 1) {
		if (!IS_CHAR_DEAD(customer8)) {
			customer_var = customer8;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer8)) {
					TASK_STAND_STILL(customer8, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer8);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer8_blip);
				customer8_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer9_created == 1) {
		if (!IS_CHAR_DEAD(customer9)) {
			customer_var = customer9;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer9)) {
					TASK_STAND_STILL(customer9, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer9);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer9_blip);
				customer9_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	if (customer10_created == 1) {
		if (!IS_CHAR_DEAD(customer10)) {
			customer_var = customer10;
			catch_da_pizza();
			if (customer_got_pizza == 1) {
				if (!IS_CHAR_DEAD(customer10)) {
					TASK_STAND_STILL(customer10, 500);
				} else {
					mission_failed_flag = 1;	
				}
				WAIT(500);
				del_pizzas();
				MARK_CHAR_AS_NO_LONGER_NEEDED(&customer10);
				PRINT_NOW("PIZ1_34", 5000, 1);
				ADD_SCORE(GetPlayerIndex(), 10);
				REMOVE_BLIP(customer10_blip);
				customer10_created = 0;
				pizza_delivered++;
				add_pizza_score++;
				customer_got_pizza = 0;
			}
		} else {
			mission_failed_flag = 1;
		}
	}
	plyr_off_moped();
	return;
}

void create_random_customer(void) {
	if ((pizza_goals > 0) && (customer1_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer1, random_customer_heading);
		TASK_STAND_STILL(customer1, -1);
		ADD_BLIP_FOR_CHAR(customer1, &customer1_blip);
		CHANGE_BLIP_COLOUR(customer1_blip, 19);
		CHANGE_BLIP_SCALE(customer1_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer1_blip, "PIZ_BL");
		customer1_created = 1;
		return;
	}
	if ((pizza_goals > 1) && (customer2_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer2);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer2, random_customer_heading);
		TASK_STAND_STILL(customer2, -1);
		ADD_BLIP_FOR_CHAR(customer2, &customer2_blip);
		CHANGE_BLIP_COLOUR(customer2_blip, 19);
		CHANGE_BLIP_SCALE(customer2_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer2_blip, "PIZ_BL");
		customer2_created = 1;
		return;
	}
	if ((pizza_goals > 2) && (customer3_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer3);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer3, random_customer_heading);
		TASK_STAND_STILL(customer3, -1);
		ADD_BLIP_FOR_CHAR(customer3, &customer3_blip);
		CHANGE_BLIP_COLOUR(customer3_blip, 19);
		CHANGE_BLIP_SCALE(customer3_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer3_blip, "PIZ_BL");
		customer3_created = 1;
		return;
	}
	if ((pizza_goals > 3) && (customer4_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer4);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer4, random_customer_heading);
		TASK_STAND_STILL(customer4, -1);
		ADD_BLIP_FOR_CHAR(customer4, &customer4_blip);
		CHANGE_BLIP_COLOUR(customer4_blip, 19);
		CHANGE_BLIP_SCALE(customer4_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer4_blip, "PIZ_BL");
		customer4_created = 1;
		return;
	}
	if ((pizza_goals > 4) && (customer5_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer5);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer5, random_customer_heading);
		TASK_STAND_STILL(customer5, -1);
		ADD_BLIP_FOR_CHAR(customer5, &customer5_blip);
		CHANGE_BLIP_COLOUR(customer5_blip, 19);
		CHANGE_BLIP_SCALE(customer5_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer5_blip, "PIZ_BL");
		customer5_created = 1;
		return;
	}
	if ((pizza_goals > 5) && (customer6_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer6);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer6, random_customer_heading);
		TASK_STAND_STILL(customer6, -1);
		ADD_BLIP_FOR_CHAR(customer6, &customer6_blip);
		CHANGE_BLIP_COLOUR(customer6_blip, 19);
		CHANGE_BLIP_SCALE(customer6_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer6_blip, "PIZ_BL");
		customer6_created = 1;
		return;
	}
	if ((pizza_goals > 6) && (customer7_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer7);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer7, random_customer_heading);
		TASK_STAND_STILL(customer7, -1);
		ADD_BLIP_FOR_CHAR(customer7, &customer7_blip);
		CHANGE_BLIP_COLOUR(customer7_blip, 19);
		CHANGE_BLIP_SCALE(customer7_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer7_blip, "PIZ_BL");
		customer7_created = 1;
		return;
	}
	if ((pizza_goals > 7) && (customer8_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer8);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer8, random_customer_heading);
		TASK_STAND_STILL(customer8, -1);
		ADD_BLIP_FOR_CHAR(customer8, &customer8_blip);
		CHANGE_BLIP_COLOUR(customer8_blip, 19);
		CHANGE_BLIP_SCALE(customer8_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer8_blip, "PIZ_BL");
		customer8_created = 1;
		return;
	}
	if ((pizza_goals > 8) && (customer9_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer9);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer9, random_customer_heading);
		TASK_STAND_STILL(customer9, -1);
		ADD_BLIP_FOR_CHAR(customer9, &customer9_blip);
		CHANGE_BLIP_COLOUR(customer9_blip, 19);
		CHANGE_BLIP_SCALE(customer9_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer9_blip, "PIZ_BL");
		customer9_created = 1;
		return;
	}
	if ((pizza_goals > 9) && (customer10_created == 0)) {
		CREATE_RANDOM_CHAR(cust_coordx, cust_coordy, cust_coordz, &customer10);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_customer_heading);
		SET_CHAR_HEADING(customer10, random_customer_heading);
		TASK_STAND_STILL(customer10, -1);
		ADD_BLIP_FOR_CHAR(customer10, &customer10_blip);
		CHANGE_BLIP_COLOUR(customer10_blip, 19);
		CHANGE_BLIP_SCALE(customer10_blip, 0.77999990);
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer10_blip, "PIZ_BL");
		customer10_created = 1;
		return;
	}
	return;
}

void get_rnd_locations(void) {
	WAIT(0);
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
	if (where_is_player1 == 1) {
		GENERATE_RANDOM_FLOAT_IN_RANGE(-614.4, 273.9, &x_random);
		GENERATE_RANDOM_FLOAT_IN_RANGE(373.0, 2133.7, &y_random);
		pizza_shopx = -475.0; 
		pizza_shopy = 1342.3;
		pizza_shopz = 5.5;	
	}
	if (where_is_player1 == 2) {
		GENERATE_RANDOM_FLOAT_IN_RANGE(-767.4, -267.9, &x_random);
		GENERATE_RANDOM_FLOAT_IN_RANGE(-227.0, 833.7, &y_random);
		pizza_shopx = -595.9; 
		pizza_shopy = 615.7;
		pizza_shopz = 5.7;
	}
	if (where_is_player1 == 3) {
		GENERATE_RANDOM_FLOAT_IN_RANGE(333.9, 1336.4, &x_random);
		GENERATE_RANDOM_FLOAT_IN_RANGE(133.7, 1333.5, &y_random);
		pizza_shopx = 844.6;
		pizza_shopy = 630.8;
		pizza_shopz = 5.4;
	}
	
	GET_CLOSEST_CAR_NODE_WITH_HEADING(x_random, y_random, player_z, &cust_coordx, &cust_coordy, &cust_coordz, &ped_heading);
	if ((cust_coordz < 3.0) || (cust_coordz > 7.0)) {
		get_rnd_locations();
	}
	
	if ((cust_coordx > 766.358) && (cust_coordx < 868.544) && (cust_coordy > -24.261) && (cust_coordy < 100.179)) {
		get_rnd_locations();
	}
	if ((cust_coordx > 369.434) && (cust_coordx < 514.544) && (cust_coordy > -462.198) && (cust_coordy < -363.662)) {
		get_rnd_locations();
	}
	if ((cust_coordx > 879.491) && (cust_coordx < 1032.769) && (cust_coordy > 441.564) && (cust_coordy < 586.415)) {
		get_rnd_locations();
	}
	if ((cust_coordx > 351.682) && (cust_coordx < 667.821) && (cust_coordy > 261.607) && (cust_coordy < 939.194)) {
		get_rnd_locations();
	}
	if ((cust_coordx > 143.702) && (cust_coordx < 715.265) && (cust_coordy > 931.714) && (cust_coordy < 1194.476)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -295.193) && (cust_coordx < 366.639) && (cust_coordy > 513.866) && (cust_coordy < 632.566)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -83.97) && (cust_coordx < 245.518) && (cust_coordy > -134.97) && (cust_coordy < 26.393)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -277.393) && (cust_coordx < -146.012) && (cust_coordy > -883.112) && (cust_coordy < -678.742)) {
		get_rnd_locations();
	}
	if ((cust_coordx > 766.358) && (cust_coordx < 926.934) && (cust_coordy > 1524.328) && (cust_coordy < 1794.389)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -357.682) && (cust_coordx < -193.456) && (cust_coordy > 1729.908) && (cust_coordy < 1839.392)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -740.877) && (cust_coordx < -594.898) && (cust_coordy > 770.098) && (cust_coordy < 948.922)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -956.195) && (cust_coordx < -766.422) && (cust_coordy > 486.561) && (cust_coordy < 762.799)) {
		get_rnd_locations();
	}
	if ((cust_coordx > -1138.667) && (cust_coordx < -857.658) && (cust_coordy > -474.371) && (cust_coordy < -251.753)) {
		get_rnd_locations();
	}
	dif_plyr_cust_x = player_x - cust_coordx;
	dif_plyr_cust_y = player_y - cust_coordy;
	dif_plyr_cust_x = dif_plyr_cust_x * dif_plyr_cust_x;
	dif_plyr_cust_y = dif_plyr_cust_y * dif_plyr_cust_y;
	sum_dif_xy = dif_plyr_cust_x + dif_plyr_cust_y;
	player1s_distance_from_customer = SQRT(sum_dif_xy);
	if (player1s_distance_from_customer < 120.0) {
		get_rnd_locations();
	}
	dif_cust_shop_x = pizza_shopx - cust_coordx;
	dif_cust_shop_y = pizza_shopy - cust_coordy;
	dif_cust_shop_x = dif_cust_shop_x * dif_cust_shop_x;
	dif_cust_shop_y = dif_cust_shop_y * dif_cust_shop_y;
	sum_dif_xy = dif_cust_shop_x + dif_cust_shop_y;
	customers_distance_from_pizza_shop = SQRT(sum_dif_xy);
	if (customers_distance_from_pizza_shop < 100.0) {
		get_rnd_locations();
	}
	
	if (customer1_created == 1) {
		if (!IS_CHAR_DEAD(customer1)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer1, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer2_created == 1) {
		if (!IS_CHAR_DEAD(customer2)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer2, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer3_created == 1) {
		if (!IS_CHAR_DEAD(customer3)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer3, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer4_created == 1) {
		if (!IS_CHAR_DEAD(customer4)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer4, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer5_created == 1) {
		if (!IS_CHAR_DEAD(customer5)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer5, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer6_created == 1) {
		if (!IS_CHAR_DEAD(customer6)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer6, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer7_created == 1) {
		if (!IS_CHAR_DEAD(customer7)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer7, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer8_created == 1) {
		if (!IS_CHAR_DEAD(customer8)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer8, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer9_created == 1) {
		if (!IS_CHAR_DEAD(customer9)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer9, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	if (customer10_created == 1) {
		if (!IS_CHAR_DEAD(customer10)) {
			if (LOCATE_CHAR_ANY_MEANS_2D(customer10, cust_coordx, cust_coordy, 25.0, 25.0, 0)) {
				get_rnd_locations();
			}
		}
	}
	cust_coordx += COS(ped_heading) * 8.0;
	cust_coordy += SIN(ped_heading) * 8.0;
	return;
}

void start_pizza_mission(void) {
	while (true) {
		WAIT(0);
		draw_hud(1);
		if (pizza_goals == 1) {
			if (pizza_help_text_played == 0) {
				if (TIMERA() > 13999) {
					PRINT_HELP("PIZ1_06");
					pizza_help_text_played = 1;
				}
			}
			if (pizza_help_text_played2 == 0) {
				if (TIMERA() > 19999) {
					PRINT_HELP("PIZ1_96");
					pizza_help_text_played2 = 1;
				}
			}
		}
		if (!IS_CAR_DEAD(pizza_moped)) {
			if (IS_CHAR_IN_CAR(GetPlayerPed(), pizza_moped)) {
				if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), pizza_shopx, pizza_shopy, pizza_shopz, 3.0, 3.0, 3.0, 0)) && (IS_CAR_STOPPED(pizza_moped))) {
					if (TIMERA() > 14000) {
						if (total_pizzas_thrown > 0) {
							CLEAR_PRINTS();
							total_pizzas_thrown = 6;
							no_longer_needed_pizzas();
							blob_flag = 0;
							SETTIMERA(0);
						}
					}
				}
			}
		}
		if (customer_complaint_time == 0) {
			PRINT_NOW("PIZ1_08", 5000, 1);
			mission_failed_pizza();
		}
		while (customers_created < pizza_goals) {
			WAIT(0);
			draw_hud(1);
			get_rnd_locations();
			create_random_customer();
			customers_created++;
			if (mission_failed_flag == 1) {
				PRINT_NOW("PIZ1_07", 5000, 1);
			}
			if (mission_failed_flag == 2) {
				PRINT_NOW("PIZ1_09", 5000, 1);
			}
			if (mission_failed_flag == 3) {
				PRINT_NOW("PIZ1_32", 5000, 1);
			}
			if ((mission_failed_flag == 1) || (mission_failed_flag == 2) || (mission_failed_flag == 3)) {
				mission_failed_pizza();
			}
			plyr_off_moped();
			plyr_quit_game();
			dying_customers();
		}
		if (mission_failed_flag == 1) {
			PRINT_NOW("PIZ1_07", 5000, 1);
		}
		if (mission_failed_flag == 2) {
			PRINT_NOW("PIZ1_09", 5000, 1);
		}
		if (mission_failed_flag == 3) {
			PRINT_NOW("PIZ1_32", 5000, 1);
		}
		if ((mission_failed_flag == 1) || (mission_failed_flag == 2) || (mission_failed_flag == 3)) {
			mission_failed_pizza();
		}
		plyr_off_moped();
		plyr_quit_game();
		dying_customers();
		
		if (go_back_to_pizza_hut_flag == 0) {
			if (pizza_delivered == pizza_goals) {
				if (flag_player_not_in_pizza_moped == 0) {
					PRINT_NOW("PIZ1_33", 7000, 1);
					REMOVE_BLIP(pizza_hut_blip);
					ADD_BLIP_FOR_COORD(pizza_shopx, pizza_shopy, -100.0, &pizza_hut_blip);
					CHANGE_BLIP_SPRITE(pizza_hut_blip, BLIP_OBJECTIVE);
					CHANGE_BLIP_COLOUR(pizza_hut_blip, 5);
					CHANGE_BLIP_SCALE(pizza_hut_blip, 0.6);
					go_back_to_pizza_hut_flag = 1;
				}
			} else {
				if (total_pizzas_thrown > 0) {
					delivering_pizzas();
				} else {
					delivering_pizzas();
					if (blob_flag == 0) {
						PRINT_NOW("PIZ1_02", 5000, 1);
						blob_flag = 1;
					}
					REMOVE_BLIP(customer1_blip);
					REMOVE_BLIP(customer2_blip);
					REMOVE_BLIP(customer3_blip);
					REMOVE_BLIP(customer4_blip);
					REMOVE_BLIP(customer5_blip);
					REMOVE_BLIP(customer6_blip);
					REMOVE_BLIP(customer7_blip);
					REMOVE_BLIP(customer8_blip);
					REMOVE_BLIP(customer9_blip);
					REMOVE_BLIP(customer10_blip);
					REMOVE_BLIP(pizza_hut_blip);
					if (flag_player_not_in_pizza_moped == 0) {
						REMOVE_BLIP(pizza_hut_blip);
						ADD_BLIP_FOR_COORD(pizza_shopx, pizza_shopy, pizza_shopz, &pizza_hut_blip);
						CHANGE_BLIP_SPRITE(pizza_hut_blip, BLIP_OBJECTIVE);
						CHANGE_BLIP_COLOUR(pizza_hut_blip, 5);
						CHANGE_BLIP_SCALE(pizza_hut_blip, 0.6);
						if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), pizza_shopx, pizza_shopy, pizza_shopz, 5.0, 5.0, 5.0, 1)) && (IS_CAR_STOPPED(pizza_moped))) {
							if (!IS_CHAR_DEAD(customer1)) {
								ADD_BLIP_FOR_CHAR(customer1, &customer1_blip);
								CHANGE_BLIP_COLOUR(customer1_blip, 19);
								CHANGE_BLIP_SCALE(customer1_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer1_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer2)) {
								ADD_BLIP_FOR_CHAR(customer2, &customer2_blip);
								CHANGE_BLIP_COLOUR(customer2_blip, 19);
								CHANGE_BLIP_SCALE(customer2_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer2_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer3)) {
								ADD_BLIP_FOR_CHAR(customer3, &customer3_blip);
								CHANGE_BLIP_COLOUR(customer3_blip, 19);
								CHANGE_BLIP_SCALE(customer3_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer3_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer4)) {
								ADD_BLIP_FOR_CHAR(customer4, &customer4_blip);
								CHANGE_BLIP_COLOUR(customer4_blip, 19);
								CHANGE_BLIP_SCALE(customer4_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer4_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer5)) {
								ADD_BLIP_FOR_CHAR(customer5, &customer5_blip);
								CHANGE_BLIP_COLOUR(customer5_blip, 19);
								CHANGE_BLIP_SCALE(customer5_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer5_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer6)) {
								ADD_BLIP_FOR_CHAR(customer6, &customer6_blip);
								CHANGE_BLIP_COLOUR(customer6_blip, 19);
								CHANGE_BLIP_SCALE(customer6_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer6_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer7)) {
								ADD_BLIP_FOR_CHAR(customer7, &customer7_blip);
								CHANGE_BLIP_COLOUR(customer7_blip, 19);
								CHANGE_BLIP_SCALE(customer7_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer7_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer8)) {
								ADD_BLIP_FOR_CHAR(customer8, &customer8_blip);
								CHANGE_BLIP_COLOUR(customer8_blip, 19);
								CHANGE_BLIP_SCALE(customer8_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer8_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer9)) {
								ADD_BLIP_FOR_CHAR(customer9, &customer9_blip);
								CHANGE_BLIP_COLOUR(customer9_blip, 19);
								CHANGE_BLIP_SCALE(customer9_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer9_blip, "PIZ_BL");
							}
							if (!IS_CHAR_DEAD(customer10)) {
								ADD_BLIP_FOR_CHAR(customer10, &customer10_blip);
								CHANGE_BLIP_COLOUR(customer10_blip, 19);
								CHANGE_BLIP_SCALE(customer10_blip, 0.77999990);
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(customer10_blip, "PIZ_BL");
							}
							REMOVE_BLIP(pizza_hut_blip);
							pizza_speech_played = 0;
							total_pizzas_thrown = 6;
							no_longer_needed_pizzas();
							blob_flag = 0;
						}
					}
				}
			}
		} else {
			DRAW_CHECKPOINT( pizza_shopx, pizza_shopy, pizza_shopz, 4.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), pizza_shopx, pizza_shopy, pizza_shopz, 5.0, 5.0, 5.0, 1)) && (IS_CAR_STOPPED(pizza_moped))) {
				if (pizza_goals == 10) {
					if (G_PIZZA == 0) {
						mission_passed_pizza();
					} else {
						pizza_goals = 9;
					}
				} else {
					REMOVE_BLIP(pizza_hut_blip);
					customer_complaint_time = 301000;
					pizza_speech_played = 0;
					total_pizzas_thrown = 6;
					no_longer_needed_pizzas();
					blob_flag = 0;
					customers_created = 0;
					pizza_goals++;
					pizza_delivered = 0;
					go_back_to_pizza_hut_flag = 0;
				}
			} else {
				if (total_pizzas_thrown > 0) {
					delivering_pizzas();
				}
			}
		}
	}
}

void mission_start_pizza(void) {
	//G_ONMISSION = 1;
	WAIT(0);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "PIZ1_A");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	LOAD_ADDITIONAL_TEXT("PIZZA", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	pizza_goals = 1;
	customers_created = 0;
	customer1_created = 0;
	customer2_created = 0;
	customer3_created = 0;
	customer4_created = 0;
	customer5_created = 0;
	customer6_created = 0;
	customer7_created = 0;
	customer8_created = 0;
	customer9_created = 0;
	customer10_created = 0;
	pizza_delivered = 0;
	go_back_to_pizza_hut_flag = 0;
	total_pizzas_thrown = 6;
	pizza_has_been_thrown = 0;
	pizza_box_var = 0;
	where_is_player1 = 0;
	customer_complaint_time = 301000;
	customer_got_pizza = 0;
	customer_var = 0;
	mission_failed_flag = 0;
	which_pizza_to_del = 0;
	flag_player_not_in_pizza_moped = 0;
	flag_pizza_moped_upsidedown = 0;
	blob_flag = 0;
	pizza_help_text_played = 0;
	pizza_help_text_played2 = 0;
	random_speech = 0;
	pizza_speech_played = 0;

	x_random = 0.0;
	y_random = 0.0;
	cust_coordx = 0.0;
	cust_coordy = 0.0; 
	cust_coordz = 0.0;
	sum_dif_xy = 0.0;
	dif_plyr_cust_x = 0.0;
	dif_plyr_cust_y = 0.0;
	player1s_distance_from_customer = 0.0;
	dif_cust_shop_x = 0.0;
	dif_cust_shop_y = 0.0;
	customers_distance_from_pizza_shop = 0.0;
	random_customer_heading = 0.0;
	pizza_shopx = 0.0;
	pizza_shopy = 0.0;
	player1_facing_this_direction = 0.0;
	pizza_lobx = 0.0;
	pizza_loby = 0.0;
	pizzax = 0.0; 
	pizzay = 0.0; 
	pizzaz = 0.0;
	player_x = 0.0;
	player_y = 0.0;
	player_z = 0.0;
	add_pizza_score = 0;
	
	REQUEST_MODEL(GET_HASH_KEY("pizza_box_1"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("pizza_box_1"))) WAIT(0);
	REQUEST_MODEL(GET_HASH_KEY("hellfury"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("hellfury"))) WAIT(0);
	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), 0);
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &pizza_moped);
	} else {
		PRINT_NOW("PIZ1_32", 5000, 1);
		mission_failed_pizza();
	}
	if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) {
		where_is_player1 = 1;
	}
	if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI")) {
		where_is_player1 = 2;
	}
	if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ")) {
		where_is_player1 = 3;
	}
	PRINT("PIZ1_01", 7000, 1);
	PRINT("PIZ1_05", 7000, 1);
	SETTIMERA(0);
	start_pizza_mission();
}

void main(void) {

	mission_start_pizza();
	mission_failed_pizza();
	//mission_cleanup_pizza();

	//while (true) {
	//	WAIT(0);
	//	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
	//		if (G_ONMISSION == 0) {
	//			if (G_flag_pizza_mission_passed == 0) {  // глобальный флаг, пройдена ли пицца-миссия вообще
	//				if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("hellfury"))) && (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), -461.1, 1331.7, -4.0, -481.1, 1351.7, 16.0, 0)) && (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), -585.7, 611.6, -4.2, -605.7, 631.6, 16.2, 0)) && (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), 836.8, 620.7, -4.9, 856.8, 640.7, 15.9, 0))) {
	//					flag_pizza_trigger = 1;
	//				}
	//				if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("hellfury"))) && (flag_pizza_trigger == 0)) {
	//					PRINT_BIG("PIZ1_A", 14000, 5);
	//					WAIT(0);
	//					mission_start_pizza();
	//					if (HAS_DEATHARREST_EXECUTED()) {
	//						mission_failed_pizza();
	//					}
	//					mission_cleanup_pizza();
	//				}
	//				if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
	//					if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
	//						flag_pizza_trigger = 0;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}