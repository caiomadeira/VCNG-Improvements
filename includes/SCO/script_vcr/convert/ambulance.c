#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int ped_time_limit, players_ambulance, ped_time_limit_temp, ped_counter, number_of_injured_peds, brackets_var;
int ambulance_health_last, ambulance_health_now, time_drop, max_peds_in_car, peds_in_car, score_am, bonus_time_flag;
int saved_peds, hospital_blip, time_chunk, ambulance_level, time_chunk_in_secs, car_full_flag;
int drop_off_time_bonus, hospital_blip_flag, mission_end_button_ambulance, players_ambulance_health, saved_peds_this_go;
int injured_ped_1, injured_ped_1_blip, injured_ped_1_flag; 
int injured_ped_2, injured_ped_2_blip, injured_ped_2_flag;
int injured_ped_3, injured_ped_3_blip, injured_ped_3_flag;
int injured_ped_4, injured_ped_4_blip, injured_ped_4_flag;
int injured_ped_5, injured_ped_5_blip, injured_ped_5_flag;
int injured_ped_6, injured_ped_6_blip, injured_ped_6_flag;
int injured_ped_7, injured_ped_7_blip, injured_ped_7_flag;
int injured_ped_8, injured_ped_8_blip, injured_ped_8_flag;
int injured_ped_9, injured_ped_9_blip, injured_ped_9_flag;
int injured_ped_10, injured_ped_10_blip, injured_ped_10_flag;
int injured_ped_11, injured_ped_11_blip, injured_ped_11_flag;
int injured_ped_12, injured_ped_12_blip, injured_ped_12_flag;
int ped_var_for_gosub, ped_var_for_gosub_flag, ped_var_for_gosub_blip, player_failed_mission;
float random_x, random_y, hospital_x, hospital_y, hospital_z;
float player1_a_x, player1_a_y, player1_a_z, hospital_door_x, hospital_door_y;
float ped_coord_x, ped_coord_y, ped_coord_z, sound_x, sound_y, sound_z, ped_heading;
float difference_x_float_a, difference_y_float_a, sum_difference_a_xy;
float players_distance_from_ped, peds_distance_from_hospital, ped_time_limit_float, time_chunk_divider;
float random_ped_heading;
int fon, textur;

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

void ambulance_failed(void) {
	if (!(ambulance_level == 13)) {
		SETTIMERA(0); //сбрасываем таймер 
		while (true)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.4, "A_FAIL1");// пишем "Миссия завершина"

			SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_SAVES", saved_peds_this_go);//
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
	}
	hospital_blip_flag = 0;
	REMOVE_BLIP(hospital_blip);
	REMOVE_BLIP(injured_ped_1_blip);
	REMOVE_BLIP(injured_ped_2_blip);
	REMOVE_BLIP(injured_ped_3_blip);
	REMOVE_BLIP(injured_ped_4_blip);
	REMOVE_BLIP(injured_ped_5_blip);
	REMOVE_BLIP(injured_ped_6_blip);
	REMOVE_BLIP(injured_ped_7_blip);
	REMOVE_BLIP(injured_ped_8_blip);
	REMOVE_BLIP(injured_ped_9_blip);
	REMOVE_BLIP(injured_ped_10_blip);
	REMOVE_BLIP(injured_ped_11_blip);
	REMOVE_BLIP(injured_ped_12_blip);
	
	SET_WANTED_MULTIPLIER(1.0);
	TERMINATE_THIS_SCRIPT();
}

void generate_timelimit(void) {
	ped_time_limit_float = peds_distance_from_hospital / time_chunk_divider;
	ped_time_limit_float = ped_time_limit_float * 1000.0;
	ped_time_limit_temp = ROUND(ped_time_limit_float);
	ped_time_limit += ped_time_limit_temp;
	return;
}

void create_random_injured_ped(void) {
	if ((number_of_injured_peds > 0) && (injured_ped_1_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_1);
		injured_ped_1_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_1, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_1, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_1, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_1, &injured_ped_1_blip);
		CHANGE_BLIP_SPRITE(injured_ped_1_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_1_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_1_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_1_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 1) && (injured_ped_2_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_2);
		injured_ped_2_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_2, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_2, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_2, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_2, &injured_ped_2_blip);
		CHANGE_BLIP_SPRITE(injured_ped_2_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_2_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_2_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_2_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 2) && (injured_ped_3_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_3);
		injured_ped_3_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_3, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_3, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_3, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_3, &injured_ped_3_blip);
		CHANGE_BLIP_SPRITE(injured_ped_3_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_3_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_3_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_3_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 3) && (injured_ped_4_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_4);
		injured_ped_4_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_4, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_4, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_4, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_4, &injured_ped_4_blip);
		CHANGE_BLIP_SPRITE(injured_ped_4_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_4_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_4_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_4_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 4) && (injured_ped_5_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_5);
		injured_ped_5_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_5, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_5, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_5, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_5, &injured_ped_5_blip);
		CHANGE_BLIP_SPRITE(injured_ped_5_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_5_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_5_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_5_blip, "BL_VTAR");
		return;
	}	
	if ((number_of_injured_peds > 5) && (injured_ped_6_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_6);
		injured_ped_6_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_6, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_6, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_6, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_6, &injured_ped_6_blip);
		CHANGE_BLIP_SPRITE(injured_ped_6_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_6_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_6_blip, 0.6); // масштаб иконки на радаре 
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_6_blip, "BL_VTAR");
		return;
	}	
	if ((number_of_injured_peds > 6) && (injured_ped_7_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_7);
		injured_ped_7_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_7, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_7, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_7, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_7, &injured_ped_7_blip);
		CHANGE_BLIP_SPRITE(injured_ped_7_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_7_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_7_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_7_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 7) && (injured_ped_8_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_8);
		injured_ped_8_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_8, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_8, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_8, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_8, &injured_ped_8_blip);
		CHANGE_BLIP_SPRITE(injured_ped_8_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_8_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_8_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_8_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 8) && (injured_ped_9_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_9);
		injured_ped_9_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_9, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_9, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_9, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_9, &injured_ped_9_blip);
		CHANGE_BLIP_SPRITE(injured_ped_9_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_9_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_9_blip, 0.6); // масштаб иконки на радаре 
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_9_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 9) && (injured_ped_10_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_10);
		injured_ped_10_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_10, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_10, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_10, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_10, &injured_ped_10_blip);
		CHANGE_BLIP_SPRITE(injured_ped_10_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_10_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_10_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_10_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 10) && (injured_ped_11_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_11);
		injured_ped_11_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_11, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_11, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_11, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_11, &injured_ped_11_blip);
		CHANGE_BLIP_SPRITE(injured_ped_11_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_11_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_11_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_11_blip, "BL_VTAR");
		return;
	}
	if ((number_of_injured_peds > 11) && (injured_ped_12_flag == 0)) {
		CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, &injured_ped_12);
		injured_ped_12_flag = 1;
		SET_CHAR_BLEEDING(injured_ped_12, 1);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(injured_ped_12, 1);
		GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
		SET_CHAR_HEADING(injured_ped_12, random_ped_heading);
		ADD_BLIP_FOR_CHAR(injured_ped_12, &injured_ped_12_blip);
		CHANGE_BLIP_SPRITE(injured_ped_12_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(injured_ped_12_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(injured_ped_12_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(injured_ped_12_blip, "BL_VTAR");
		return;
	}
	return;
}

void injured_ped_checks(void) {
	if (IS_CHAR_DEAD(ped_var_for_gosub)) {
		PRINT_NOW("A_FAIL3", 3000, 1);
		player_failed_mission = 1;
		return;
	}
	if (ped_time_limit == 0) {
		EXPLODE_CHAR_HEAD(ped_var_for_gosub);
		REMOVE_CHAR_ELEGANTLY(ped_var_for_gosub);
		PRINT_NOW("A_FAIL2", 3000, 1);
		player_failed_mission = 1;
		return;
	}
	if (ped_var_for_gosub_flag == 3) {
		GET_CHAR_COORDINATES(ped_var_for_gosub, &sound_x, &sound_y, &sound_z);
		GET_CAR_HEALTH(players_ambulance, &ambulance_health_now);
		if (ambulance_health_now < ambulance_health_last) {
			time_drop = ambulance_health_last - ambulance_health_now;
			time_drop = time_drop * 50;
			ped_time_limit = ped_time_limit - time_drop;		
			if (ped_time_limit < 0) {
				ped_time_limit = 0;
			}
			ambulance_health_last = ambulance_health_now;
		}
	}
	if (ped_var_for_gosub_flag == 1) {
		if (LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), ped_var_for_gosub, 10.0, 10.0, 2.0, 0)) {
			GET_NUMBER_OF_PASSENGERS(players_ambulance, &peds_in_car);
			GET_MAXIMUM_NUMBER_OF_PASSENGERS(players_ambulance, &max_peds_in_car);
			if (peds_in_car == max_peds_in_car) {
				PRINT_NOW("A_FULL", 5000, 1);
				car_full_flag = 1;
			} else {
				car_full_flag = 0;
			}
			GET_CAR_HEALTH(players_ambulance, &ambulance_health_last);
			if (car_full_flag == 0) {
				int getseat;
				while (true) {
					GENERATE_RANDOM_INT_IN_RANGE(0, max_peds_in_car, &getseat);
					if (IS_CAR_PASSENGER_SEAT_FREE(players_ambulance, getseat)) {
						break;
					}			
				}
				int seq1;
				OPEN_SEQUENCE_TASK(&seq1);
				TASK_ENTER_CAR_AS_PASSENGER(0, players_ambulance, -1, getseat);
				CLOSE_SEQUENCE_TASK(seq1);
				TASK_PERFORM_SEQUENCE(ped_var_for_gosub, seq1);
				CLEAR_SEQUENCE_TASK(seq1);
				int seqpr = 0;
				while (!(seqpr == -1)) {
					WAIT(0);
					GET_SEQUENCE_PROGRESS(ped_var_for_gosub, &seqpr);
				}
				ped_var_for_gosub_flag = 2;
			}
		}
	}
	if (ped_var_for_gosub_flag == 2) {
		if (!LOCATE_CHAR_IN_CAR_CHAR_2D(GetPlayerPed(), ped_var_for_gosub, 20.0, 20.0, 0)) {
			ped_var_for_gosub_flag = 1;
		}
		if (DOES_CHAR_EXIST(ped_var_for_gosub)) {
			if (!IS_CHAR_IN_ANY_CAR(ped_var_for_gosub)) {
				ped_var_for_gosub_flag = 1;
			}
		}
	}
	
	if (ped_var_for_gosub_flag == 2) {
		if (IS_CHAR_IN_ANY_CAR(ped_var_for_gosub)) {
			REMOVE_BLIP(ped_var_for_gosub_blip);
			if (hospital_blip_flag == 0) {
				ADD_BLIP_FOR_COORD(hospital_x, hospital_y, hospital_z, &hospital_blip);
				CHANGE_BLIP_SPRITE(hospital_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(hospital_blip, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(hospital_blip, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(hospital_blip, "BL_HTAR");
				hospital_blip_flag = 1;
			}
			time_chunk_in_secs = time_chunk / 1000;
			//PRINT_WITH_NUMBER_BIG("A_TIME", time_chunk_in_secs, 6000, 6);
			SETTIMERA(0); //сбрасываем таймер 
			while (true)
			{
				SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
				SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
				SET_TEXT_EDGE(1, 0, 0, 0, 255); //
				SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
				SET_TEXT_CENTRE(1); // задаём центр текста
				DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_TIME", time_chunk_in_secs);//

				WAIT( 0 );
				if ( TIMERA() > 3000 )
				{
					break;
				}
			}
			ped_time_limit += time_chunk;
			ped_var_for_gosub_flag = 3;
		}
	}
	
	if (ped_var_for_gosub_flag == 3) {
		if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), hospital_x, hospital_y, hospital_z, 6.0, 6.0, 2.0, 1)) && (IS_CAR_STOPPED(players_ambulance))) {
			TASK_FOLLOW_NAV_MESH_TO_COORD(ped_var_for_gosub, hospital_door_x, hospital_door_y, 5.0, 2, -2, 2.0);
			ped_var_for_gosub_flag = 4;
		}
	}
	
	if (ped_var_for_gosub_flag == 4) {
		TASK_FOLLOW_NAV_MESH_TO_COORD(ped_var_for_gosub, hospital_door_x, hospital_door_y, 5.0, 4, -2, 2.0);
		if (!IS_CHAR_IN_ANY_CAR(ped_var_for_gosub)) {
			TASK_FOLLOW_NAV_MESH_TO_COORD(ped_var_for_gosub, hospital_door_x, hospital_door_y, 5.0, 4, -2, 2.0);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_var_for_gosub);
			//PRINT_BIG("A_PASS", 3000, 5);
			if (bonus_time_flag == 1) {
				time_chunk_in_secs = time_chunk / 1000;
				//PRINT_WITH_NUMBER_BIG("A_TIME", time_chunk_in_secs, 6000, 6);
				STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_ambulance);
				GET_CAR_HEALTH(players_ambulance, &players_ambulance_health);
				players_ambulance_health += 110;
				SET_CAR_HEALTH(players_ambulance, players_ambulance_health);
				SET_ENGINE_HEALTH(players_ambulance, players_ambulance_health);
				ped_time_limit += time_chunk;
				bonus_time_flag++;
			}
			if ( TIMERA() > 10000 )
			{
				SETTIMERA(0); //сбрасываем таймер 
				while (true)
				{
					SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
					SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
					SET_TEXT_EDGE(1, 0, 0, 0, 255); //
					SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
					SET_TEXT_CENTRE(1); // задаём центр текста
					DISPLAY_TEXT(0.5, 0.4, "A_PASS");//

					if (bonus_time_flag == 1)
					{
						SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_TIME", time_chunk_in_secs);//
					}

					WAIT( 0 );
					if ( TIMERA() > 3000 )
					{
						break;
					}
				}
			}
			
			saved_peds++;
			ped_var_for_gosub_flag = 0;
		}
	}
	return;
}

void generate_random_coord(void) {
	int a = 0;
	while (a == 0) {
		WAIT(0);
		GET_CHAR_COORDINATES(GetPlayerPed(), &player1_a_x, &player1_a_y, &player1_a_z);
		SET_RANDOM_SEED(ROUND(player1_a_x * player1_a_y * player1_a_z));
		if (hospital_x == 300.0288) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(45.702, 1544.298, &random_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1275.797, 425.797, &random_y);
		}
		if (hospital_x == 912.1241) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(258.766, 1757.234, &random_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(425.797, 1924.203, &random_y);
		}
		if (hospital_x == -438.6317) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1455.702, 45.702, &random_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1269.039, 531.039, &random_y);
		}
		if (hospital_x == -390.1110) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1442.766, 258.766, &random_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(531.039, 2230.961, &random_y);
		}
		
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
			mission_end_button_ambulance = 1;
		}		
		if (mission_end_button_ambulance == 1) {
			if (!((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || !((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
				PRINT_NOW("A_CANC", 3000, 1);
				player_failed_mission = 1;
				return;
			}
		}	
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("ambulance"))) {
			PRINT_NOW("A_CANC", 3000, 1);
			player_failed_mission = 1;
			return;
		}		
		GET_CLOSEST_CAR_NODE_WITH_HEADING(random_x, random_y, player1_a_z, &ped_coord_x, &ped_coord_y, &ped_coord_z, &ped_heading);		
		//if (flag_baron_mission2_passed == 0) {  // пройдена ли миссия, после которой дают доступ ко второму острову
			if ((ped_coord_x > -1894.212) && (ped_coord_x < 172.402) && (ped_coord_y > -1494.821) && (ped_coord_y < 2427.426)) {
				continue;
			}
			
			if ((ped_coord_x > 168.018) && (ped_coord_x < 603.188) && (ped_coord_y > 258.942) && (ped_coord_y < 2222.059)) {
				continue;
			}
			
			if ((ped_coord_x > 168.657) && (ped_coord_x < 469.828) && (ped_coord_y > -196.217) && (ped_coord_y < 258.488)) {
				continue;
			}
			
			if ((ped_coord_x > 597.191) && (ped_coord_x < 692.713) && (ped_coord_y > 346.926) && (ped_coord_y < 1164.97)) {
				continue;
			}
		//}
		if ((ped_coord_x > 766.358) && (ped_coord_x < 868.544) && (ped_coord_y > -24.26) && (ped_coord_y < 99.821)) {
			continue;
		}

		if ((ped_coord_x > 368.566) && (ped_coord_x < 514.544) && (ped_coord_y > -462.197) && (ped_coord_y < -363.661)) {
			continue;
		}

		if ((ped_coord_x > 879.49) && (ped_coord_x < 1032.769) && (ped_coord_y > 440.436) && (ped_coord_y < 586.414)) {
			continue;
		}

		if ((ped_coord_x > 240.639) && (ped_coord_x < 667.820) && (ped_coord_y > 260.393) && (ped_coord_y < 939.193)) {
			continue;
		}

		if ((ped_coord_x > 142.298) && (ped_coord_x < 715.265) && (ped_coord_y > 931.713) && (ped_coord_y < 1194.476)) {
			continue;
		}

		if ((ped_coord_x > -295.192) && (ped_coord_x < 365.360) && (ped_coord_y > 512.133) && (ped_coord_y < 632.565)) {
			continue;
		}

		if ((ped_coord_x > -83.969) && (ped_coord_x < 244.48) && (ped_coord_y > -134.969) && (ped_coord_y < 25.606)) {
			continue;
		}

		if ((ped_coord_x > -277.393) && (ped_coord_x < -146.012) && (ped_coord_y > -883.112) && (ped_coord_y < -678.741)) {
			continue;
		}

		if ((ped_coord_x > 766.358) && (ped_coord_x < 926.933) && (ped_coord_y > 1524.328) && (ped_coord_y < 1794.389)) {
			continue;
		}

		if ((ped_coord_x > -357.682) && (ped_coord_x < -193.455) && (ped_coord_y > 1729.907) && (ped_coord_y < 1839.391)) {
			continue;
		}

		if ((ped_coord_x > -740.876) && (ped_coord_x < -594.897) && (ped_coord_y > 770.098) && (ped_coord_y < 948.921)) {
			continue;
		}

		if ((ped_coord_x > -956.194) && (ped_coord_x < -766.421) && (ped_coord_y > 485.438) && (ped_coord_y < 762.799)) {
			continue;
		}

		if ((ped_coord_x > -1138.666) && (ped_coord_x < -857.657) && (ped_coord_y > -474.370) && (ped_coord_y < -251.752)) {
			continue;
		}

		if ((ped_coord_x > -324.335) && (ped_coord_x < 213.686) && (ped_coord_y > -446.567) && (ped_coord_y < -345.689)) {
			continue;
		}

		if ((ped_coord_x > 252.119) && (ped_coord_x < 497.111) && (ped_coord_y > 33.816) && (ped_coord_y < 115.480)) {
			continue;
		}

		if ((ped_coord_x > 944.111) && (ped_coord_x < 1071.213) && (ped_coord_y > -1282.644) && (ped_coord_y < -1146.04)) {
			continue;
		}

		if ((ped_coord_x > -258.672) && (ped_coord_x < -148.672) && (ped_coord_y > -986.748) && (ped_coord_y < -916.748)) {
			continue;
		}

		if ((ped_coord_x > -743.037) && (ped_coord_x < -579.796) && (ped_coord_y > 266.101) && (ped_coord_y < 374.739)) {
			continue;
		}

		if ((ped_coord_x > -598.494) && (ped_coord_x < -516.479) && (ped_coord_y > -369.312) && (ped_coord_y < -288.591)) {
			continue;
		}

		if ((ped_coord_x > -463.098) && (ped_coord_x < -422.090) && (ped_coord_y > -60.101) && (ped_coord_y < -15.640)) {
			continue;
		}

		if ((ped_coord_x > -579.059) && (ped_coord_x < -549.059) && (ped_coord_y > 714.561) && (ped_coord_y < 749.561)) {
			continue;
		}

		if ((ped_coord_x > 320.505) && (ped_coord_x < 442.704) && (ped_coord_y > 1453.348) && (ped_coord_y < 1558.693)) {
			continue;
		}

		if ((ped_coord_x > 966.890) && (ped_coord_x < 1106.890) && (ped_coord_y > 189.884) && (ped_coord_y < 349.884)) {
			continue;
		}

		if ((ped_coord_x > -1350.221) && (ped_coord_x < -1153.598) && (ped_coord_y > 225.490) && (ped_coord_y < 448.689)) {
			continue;
		}

		if ((ped_coord_x > -470.697) && (ped_coord_x < -449.794) && (ped_coord_y > 1324.781) && (ped_coord_y < 1341.322)) {
			continue;
		}

		if ((ped_coord_x > -626.234) && (ped_coord_x < -607.148) && (ped_coord_y > 606.364) && (ped_coord_y < 622.749)) {
			continue;
		}

		if ((ped_coord_x > -802.791) && (ped_coord_x < -677.931) && (ped_coord_y > 565.121) && (ped_coord_y < 659.134)) {
			continue;
		}

		if (ped_coord_z < 1.0) {
			continue;
		}
		difference_x_float_a = player1_a_x - ped_coord_x;
		difference_y_float_a = player1_a_y - ped_coord_y;
		difference_x_float_a = difference_x_float_a * difference_x_float_a;
		difference_y_float_a = difference_y_float_a * difference_y_float_a;
		sum_difference_a_xy = difference_x_float_a + difference_y_float_a;
		players_distance_from_ped = SQRT(sum_difference_a_xy);
		
		if (players_distance_from_ped < 120.0) {
			continue;
		}
		
		difference_x_float_a = hospital_x - ped_coord_x;
		difference_y_float_a = hospital_y - ped_coord_y;
		difference_x_float_a = difference_x_float_a * difference_x_float_a;
		difference_y_float_a = difference_y_float_a * difference_y_float_a;
		sum_difference_a_xy = difference_x_float_a + difference_y_float_a;
		peds_distance_from_hospital = SQRT(sum_difference_a_xy);
		
		if (peds_distance_from_hospital < 100.0) {
			continue;
		}
			
		if (injured_ped_1_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_1)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_1, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_2_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_2)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_2, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_3_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_3)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_3, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_4_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_4)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_4, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_5_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_5)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_5, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_6_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_6)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_6, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_7_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_7)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_7, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_8_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_8)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_8, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_9_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_9)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_9, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_10_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_10)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_10, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}
		
		if (injured_ped_11_flag > 0) {
			if (!IS_CHAR_DEAD(injured_ped_11)) {
				if (LOCATE_CHAR_ANY_MEANS_2D(injured_ped_11, ped_coord_x, ped_coord_y, 25.0, 25.0, 0)) {
					continue;
				}
			}
		}	
		ped_coord_x += COS(ped_heading) * 4.0;
		ped_coord_y += SIN(ped_heading) * 4.0;
		a = 1;
	}
	return;
}

void mission_root(void);

void ambulance_loop(void) {
	SETTIMERC(0);
	while (true) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			ped_time_limit -= 1000;
			SETTIMERC(0);
		}
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = ped_time_limit / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		if ((timesec > 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T1", timemin, timesec);
		} else if ((timesec <= 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T3", timemin, timesec);
		} else if ((timesec > 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T2", timemin, timesec);
		} else if ((timesec <= 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T0", timemin, timesec);
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
			mission_end_button_ambulance = 1;
		}		
		if (mission_end_button_ambulance == 1) {
			if (!((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || !((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
				PRINT_NOW("A_CANC", 3000, 1);
				ambulance_failed();
			}
		}		
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("ambulance"))) {
			PRINT_NOW("A_CANC", 3000, 1);
			ambulance_failed();
		}
		if ((timemin == 0) && (timesec < 1)){
			PRINT_NOW("A_FAIL2", 3000, 1);
			ambulance_failed();
		}
		if ((number_of_injured_peds > 6) && (bonus_time_flag == 2) && (drop_off_time_bonus == 0)) {
			bonus_time_flag = 1;
			drop_off_time_bonus++;
		}
		if ((number_of_injured_peds > 9) && (bonus_time_flag == 2) && (drop_off_time_bonus == 1)) {
			bonus_time_flag = 1;
			drop_off_time_bonus++;
		}
		if ((number_of_injured_peds > 12) && (bonus_time_flag == 2) && (drop_off_time_bonus == 2)) {
			bonus_time_flag = 1;
			drop_off_time_bonus++;
		}
		
		if (injured_ped_1_flag > 0) {
			ped_var_for_gosub = injured_ped_1;
			ped_var_for_gosub_flag = injured_ped_1_flag;
			ped_var_for_gosub_blip = injured_ped_1_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_1_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_2_flag > 0) {
			ped_var_for_gosub = injured_ped_2;
			ped_var_for_gosub_flag = injured_ped_2_flag;
			ped_var_for_gosub_blip = injured_ped_2_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_2_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_3_flag > 0) {
			ped_var_for_gosub = injured_ped_3;
			ped_var_for_gosub_flag = injured_ped_3_flag;
			ped_var_for_gosub_blip = injured_ped_3_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_3_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_4_flag > 0) {
			ped_var_for_gosub = injured_ped_4;
			ped_var_for_gosub_flag = injured_ped_4_flag;
			ped_var_for_gosub_blip = injured_ped_4_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_4_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_5_flag > 0) {
			ped_var_for_gosub = injured_ped_5;
			ped_var_for_gosub_flag = injured_ped_5_flag;
			ped_var_for_gosub_blip = injured_ped_5_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_5_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_6_flag > 0) {
			ped_var_for_gosub = injured_ped_6;
			ped_var_for_gosub_flag = injured_ped_6_flag;
			ped_var_for_gosub_blip = injured_ped_6_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_6_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_7_flag > 0) {
			ped_var_for_gosub = injured_ped_7;
			ped_var_for_gosub_flag = injured_ped_7_flag;
			ped_var_for_gosub_blip = injured_ped_7_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_7_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_8_flag > 0) {
			ped_var_for_gosub = injured_ped_8;
			ped_var_for_gosub_flag = injured_ped_8_flag;
			ped_var_for_gosub_blip = injured_ped_8_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_8_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_9_flag > 0) {
			ped_var_for_gosub = injured_ped_9;
			ped_var_for_gosub_flag = injured_ped_9_flag;
			ped_var_for_gosub_blip = injured_ped_9_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_9_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_10_flag > 0) {
			ped_var_for_gosub = injured_ped_10;
			ped_var_for_gosub_flag = injured_ped_10_flag;
			ped_var_for_gosub_blip = injured_ped_10_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_10_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_11_flag > 0) {
			ped_var_for_gosub = injured_ped_11;
			ped_var_for_gosub_flag = injured_ped_11_flag;
			ped_var_for_gosub_blip = injured_ped_11_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_11_flag = ped_var_for_gosub_flag;
		}
		
		if (injured_ped_12_flag > 0) {
			ped_var_for_gosub = injured_ped_12;
			ped_var_for_gosub_flag = injured_ped_12_flag;
			ped_var_for_gosub_blip = injured_ped_12_blip;
			injured_ped_checks();
			if (player_failed_mission == 1) {
				ambulance_failed();
			}
			injured_ped_12_flag = ped_var_for_gosub_flag;
		}
		
		if (saved_peds == number_of_injured_peds) {
			score_am = ambulance_level * ambulance_level;
			score_am *= 50;
			//PRINT_WITH_NUMBER_BIG("A_REW", score_am, 6000, 6);
			SETTIMERA(0); //сбрасываем таймер 
			while (true)
			{
				SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
				SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
				SET_TEXT_EDGE(1, 0, 0, 0, 255); //
				SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
				SET_TEXT_CENTRE(1); // задаём центр текста
				DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_REW", score_am);//

				WAIT( 0 );
				if ( TIMERA() > 3000 )
				{
					break;
				}
			}
			//total_saved_peds += saved_peds;
			saved_peds_this_go += saved_peds;
			number_of_injured_peds++;
			saved_peds = 0;
			ped_counter = 0;
			ADD_SCORE(GetPlayerIndex(), score_am);
			hospital_blip_flag = 0;
			REMOVE_BLIP(hospital_blip);
			REMOVE_BLIP(injured_ped_1_blip);
			REMOVE_BLIP(injured_ped_2_blip);
			REMOVE_BLIP(injured_ped_3_blip);
			REMOVE_BLIP(injured_ped_4_blip);
			REMOVE_BLIP(injured_ped_5_blip);
			REMOVE_BLIP(injured_ped_6_blip);
			REMOVE_BLIP(injured_ped_7_blip);
			REMOVE_BLIP(injured_ped_8_blip);
			REMOVE_BLIP(injured_ped_9_blip);
			REMOVE_BLIP(injured_ped_10_blip);
			REMOVE_BLIP(injured_ped_11_blip);
			REMOVE_BLIP(injured_ped_12_blip);
			ambulance_level++;
			if (ambulance_level == 13) {
				//PRINT_WITH_NUMBER_BIG("A_COMP1", 15000, 5000, 5);
				SETTIMERA(0); //сбрасываем таймер 
				while (true)
				{
					SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
					SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
					SET_TEXT_EDGE(1, 0, 0, 0, 255); //
					SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
					SET_TEXT_CENTRE(1); // задаём центр текста
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_COMP1", 15000);//
					
					WAIT( 0 );
					if ( TIMERA() > 4000 )
					{
						break;
					}
				}
				ADD_SCORE(GetPlayerIndex(), 15000);
				PRINT_HELP("A_COMP2");// Paramedic missions complete! You will never get tired when running!
				G_MEDIC = 1;
			}
			mission_root();
		}	
	}
}

void mission_root(void) {
	PRINT_WITH_NUMBER("ALEVEL", ambulance_level, 5000, 4);
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_ambulance);
	SWITCH_CAR_SIREN(players_ambulance, 1);
	ped_time_limit = 0;
	if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), 794.298, -425.797, 1183.0, 1383.0, 0)) {
		hospital_x = 300.0288; 
		hospital_y = -448.1411; 
		hospital_z = 4.4084;
		hospital_door_x	= 299.3;
		hospital_door_y = -449.6;
	} else {
		if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), 1007.234, 1174.203, 1183.0, 1283.0, 0)) {
			hospital_x = 912.1241; 
			hospital_y = 1243.7480; 
			hospital_z = 5.3577;
			hospital_door_x	= 929.5145;
			hospital_door_y = 1241.1912;
		} else {
			if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), -705.702, -369.039, 1183.0, 1433.0, 0)) {
				hospital_x = -438.6317;
				hospital_y = 56.0081;
				hospital_z = 5.0683;
				hospital_door_x	= -454.1110;
				hospital_door_y = 63.5340;
			} else {
				if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), -592.766, 1380.961, 1283.0, 1383.0, 0)) {
					hospital_x = -390.1110;
					hospital_y = 1700.6761;
					hospital_z = 4.8744; 
					hospital_door_x	= -390.2640;
					hospital_door_y = 1673.0605;
				}
			}
		}
	}
	WAIT(3000);
	while (number_of_injured_peds > ped_counter) {
		generate_random_coord();
		if (player_failed_mission == 1) {
			ambulance_failed();
		}
		create_random_injured_ped();
		generate_timelimit();
		ped_counter++;
	}
	
	if (number_of_injured_peds > 3) {
		bonus_time_flag = 1;
	} else {
		bonus_time_flag = 0;
	}
	
	time_chunk = ped_time_limit / number_of_injured_peds;
	time_chunk /= 2;
	brackets_var = number_of_injured_peds + 1;
	time_chunk *= brackets_var;
	ped_time_limit += time_chunk;
	ped_time_limit = ped_time_limit / number_of_injured_peds;
	time_chunk = ped_time_limit;
	time_chunk /= 2;
	
	if (G_ONMISSION == 0) {
		ADD_BLIP_FOR_COORD(hospital_x, hospital_y, hospital_z, &hospital_blip);
		CHANGE_BLIP_SPRITE(hospital_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(hospital_blip, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(hospital_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(hospital_blip, "BL_HTAR");
	}
	ambulance_loop();
}

void mission_start_ambulance(void) {
	LOAD_ADDITIONAL_TEXT("AMBULAE", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	ped_time_limit = 0;
	players_ambulance = 0;
	ambulance_health_last = 0;
	ambulance_health_now = 0;
	time_drop = 0;
	max_peds_in_car = 0;
	peds_in_car = 0;
	number_of_injured_peds = 1;
	ped_counter = 0;
	injured_ped_1_flag = 0;
	injured_ped_2_flag = 0;
	injured_ped_3_flag = 0;
	injured_ped_4_flag = 0;
	injured_ped_5_flag = 0;
	injured_ped_6_flag = 0;
	injured_ped_7_flag = 0;
	injured_ped_8_flag = 0;
	injured_ped_9_flag = 0;
	injured_ped_10_flag = 0;
	injured_ped_11_flag = 0;
	injured_ped_12_flag = 0;
	saved_peds = 0;
	time_chunk_divider = 10.0;
	ambulance_level = 1;
	time_chunk = 0;
	time_chunk_in_secs = 0;
	score_am = 0;
	bonus_time_flag = 0;
	drop_off_time_bonus = 0;
	hospital_blip_flag = 0;
	mission_end_button_ambulance = 0;
	car_full_flag = 0;
	saved_peds_this_go = 0;
	player_failed_mission = 0;
	ped_coord_x = 0.0;
	ped_coord_y = 0.0;
	ped_coord_z = 0.0;
	
	PRINT_NOW("ATUTOR2", 3000, 1);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "AMBUL_M");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	SET_WANTED_MULTIPLIER(0.5);
	mission_root();
}

void main(void)
{
	mission_start_ambulance();
	ambulance_failed();
}