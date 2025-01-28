#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int onfire_car_fire, onfire_car_1_fire, onfire_car_2_fire, onfire_car_3_fire;
int onfire_ped_fire, onfire_ped_1_fire, onfire_ped_2_fire, onfire_ped_3_fire, onfire_ped_4_fire;
int onfire_ped_5_fire, onfire_ped_6_fire, onfire_ped_7_fire, onfire_ped_8_fire, onfire_ped_9_fire;

int onfire_car_blip, onfire_car_1_blip, onfire_car_2_blip, onfire_car_3_blip;
int onfire_ped_blip, onfire_ped_1_blip, onfire_ped_2_blip, onfire_ped_3_blip, onfire_ped_4_blip;
int onfire_ped_5_blip, onfire_ped_6_blip, onfire_ped_7_blip, onfire_ped_8_blip, onfire_ped_9_blip;
int onfire_car, onfire_car_1, onfire_car_2, onfire_car_3;
int onfire_ped, onfire_ped_1, onfire_ped_2, onfire_ped_3, onfire_ped_4;
int onfire_ped_5, onfire_ped_6, onfire_ped_7, onfire_ped_8, onfire_ped_9;
int fire_time_limit, fail_firetruck_mission, intermediate_int, score_ft;
int displayed_timer, displayed_counter, fires_extinguished, firetruck_level, mission_end_button_ft;
int total_score, players_car_health, firetruck_level_minus_4, fires_extinguished_this_round;
int onfire_car_health, fires_needing_extinguishing, car_health_test_timer;
int onfire_car_flag, onfire_car_1_flag, onfire_car_2_flag, onfire_car_3_flag;
int onfire_ped_flag, onfire_ped_1_flag, onfire_ped_2_flag, onfire_ped_3_flag, onfire_ped_4_flag;
int onfire_ped_5_flag, onfire_ped_6_flag, onfire_ped_7_flag, onfire_ped_8_flag, onfire_ped_9_flag;
int fire_flag, fire1_flag, fire2_flag, fire3_flag, fire4_flag, fire5_flag;
int game_timer;

float time_divider;
float players_distance_from_fire, fire_time_limit_float, random_car_heading;
float fire1_x, fire1_y, fire2_x, fire2_y, fire3_x, fire3_y, fire4_x, fire4_y, fire5_x, fire5_y;
float player_x, player_y, player_z;
int random_int, random_car_model, players_car;
float car1_x, car1_y, car1_z, car2_x, car2_y, car2_z, car3_x, car3_y, car3_z;
float dx, dy, temp_x, temp_y, temp_xy, sum_x_y_temp;
float x, y, z;
float objx, objy, objz;
int objtemp, fon, textur, inftk;

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

void main(void);

void fire_generation_start(void);

void failed(void) {
	//PRINT_BIG("F_FAIL1", 5000, 5);
	//PRINT_WITH_NUMBER_BIG("TSCORE", total_score, 6000, 6);

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.4, "F_FAIL1");// пишем "Миссия завершина"

		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "TSCORE", total_score);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	SET_WANTED_MULTIPLIER(1.0);
	REMOVE_BLIP(onfire_car_blip);
	REMOVE_BLIP(onfire_car_1_blip);
	REMOVE_BLIP(onfire_car_2_blip);
	REMOVE_BLIP(onfire_car_3_blip);
	REMOVE_BLIP(onfire_ped_blip);
	REMOVE_BLIP(onfire_ped_1_blip);
	REMOVE_BLIP(onfire_ped_2_blip);
	REMOVE_BLIP(onfire_ped_3_blip);
	REMOVE_BLIP(onfire_ped_4_blip);
	REMOVE_BLIP(onfire_ped_5_blip);
	REMOVE_BLIP(onfire_ped_6_blip);
	REMOVE_BLIP(onfire_ped_7_blip);
	REMOVE_BLIP(onfire_ped_8_blip);
	REMOVE_BLIP(onfire_ped_9_blip);
	if (!IS_CHAR_DEAD(onfire_ped_1)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_1, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_1);
	}
	if (!IS_CHAR_DEAD(onfire_ped_2)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_2, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_2);
	}
	if (!IS_CHAR_DEAD(onfire_ped_3)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_3, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_3);
	}
	if (!IS_CHAR_DEAD(onfire_ped_4)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_4, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_4);
	}
	if (!IS_CHAR_DEAD(onfire_ped_5)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_5, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_5);
	}
	if (!IS_CHAR_DEAD(onfire_ped_6)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_6, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_6);
	}
	if (!IS_CHAR_DEAD(onfire_ped_7)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_7, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_7);
	}
	if (!IS_CHAR_DEAD(onfire_ped_8)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_8, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_8);
	}
	if (!IS_CHAR_DEAD(onfire_ped_9)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_9, 0);
		EXPLODE_CHAR_HEAD(onfire_ped_9);
	}
	if (!IS_CAR_DEAD(onfire_car_1)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car_1, 0);
		EXPLODE_CAR(onfire_car_1, 1, 0);
	}
	if (!IS_CAR_DEAD(onfire_car_2)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car_2, 0);
		EXPLODE_CAR(onfire_car_2, 1, 0);
	}
	if (!IS_CAR_DEAD(onfire_car_3)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car_3, 0);
		EXPLODE_CAR(onfire_car_3, 1, 0);
	}
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	TERMINATE_THIS_SCRIPT();
	//main();
}

void passed(void) {
	//PRINT_BIG("F_PASS1", 5000, 5);
	score_ft = firetruck_level * firetruck_level;
	score_ft *= 50;
	total_score += score_ft;
	//PRINT_WITH_NUMBER_BIG("F_REWD", score_ft, 6000, 6);
	ADD_SCORE(GetPlayerIndex(), score_ft);

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.4, "F_PASS1");// пишем "Миссия завершина"

		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "F_REWD", score_ft);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	if (firetruck_level > 11) {
		if (G_FIRE == 0) {		// если пройдешь все уровни в первый раз, то покажет сообщение
			//MAKE_PLAYER_FIRE_PROOF(GetPlayerIndex(), 1);
			PRINT_HELP("FIREPRO");
			G_FIRE = 1;
		}
	}
	firetruck_level++;
	REMOVE_BLIP(onfire_car_blip);
	REMOVE_BLIP(onfire_car_1_blip);
	REMOVE_BLIP(onfire_car_2_blip);
	REMOVE_BLIP(onfire_car_3_blip);
	REMOVE_BLIP(onfire_ped_blip);
	REMOVE_BLIP(onfire_ped_1_blip);
	REMOVE_BLIP(onfire_ped_2_blip);
	REMOVE_BLIP(onfire_ped_3_blip);
	REMOVE_BLIP(onfire_ped_4_blip);
	REMOVE_BLIP(onfire_ped_5_blip);
	REMOVE_BLIP(onfire_ped_6_blip);
	REMOVE_BLIP(onfire_ped_7_blip);
	REMOVE_BLIP(onfire_ped_8_blip);
	REMOVE_BLIP(onfire_ped_9_blip);
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_car);
		GET_CAR_HEALTH(players_car, &players_car_health);
		players_car_health += 150;
		SET_CAR_HEALTH(players_car, players_car_health);
	}
	MARK_CAR_AS_NO_LONGER_NEEDED(&onfire_car_1);
	if (!IS_CAR_DEAD(onfire_car_1)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car_1, 0);
	}
	MARK_CAR_AS_NO_LONGER_NEEDED(&onfire_car_2);
	if (!IS_CAR_DEAD(onfire_car_2)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car_2, 0);
	}
	MARK_CAR_AS_NO_LONGER_NEEDED(&onfire_car_3);
	if (!IS_CAR_DEAD(onfire_car_3)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car_3, 0);
	}
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_3);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_4);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_5);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_6);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_7);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_8);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&onfire_ped_9);
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	fire_generation_start();
}

void do_fire_on_ped_bit(void) {
	if (onfire_ped_flag < 2) {
		if (!IS_CHAR_DEAD(onfire_ped)) {
			if (onfire_ped_flag == 0) {
				if (!IS_CHAR_IN_ANY_CAR(onfire_ped)) {
					onfire_ped_fire = START_CHAR_FIRE(onfire_ped);
					ADD_BLIP_FOR_CHAR(onfire_ped, &onfire_ped_blip);
					CHANGE_BLIP_DISPLAY(onfire_ped_blip, 2);
					onfire_ped_flag = 1;
				}
			}
			if (onfire_ped_flag == 1) {
				if (IS_SCRIPT_FIRE_EXTINGUISHED(onfire_ped_fire)) {
					REMOVE_BLIP(onfire_ped_blip);
					if (displayed_counter == 0) {
						displayed_counter = 1;
					}
					fires_extinguished++;
					fires_extinguished_this_round++;
					onfire_ped_flag = 2;
				}
			}
		} else {
			if (IS_CHAR_IN_WATER(onfire_ped)) {
				if (onfire_ped_flag == 1) {
					REMOVE_SCRIPT_FIRE(onfire_ped_fire);
					REMOVE_BLIP(onfire_ped_blip);
					if (displayed_counter == 0) {
						displayed_counter = 1;
					}
					fires_extinguished++;
					fires_extinguished_this_round++;
					onfire_ped_flag = 2;
				} else {
					PRINT_NOW("F_FAIL2", 5000, 1);
					fail_firetruck_mission = 1;
					return;
				}
			} else {
				PRINT_NOW("F_FAIL2", 5000, 1);
				fail_firetruck_mission = 1;
				return;
			}
		}
	}
	return;
}

void do_fire_on_car_bit(void) {
	if (!(onfire_car_flag == 10)) {
		if (!IS_CAR_DEAD(onfire_car)) {
			if (!IS_SCRIPT_FIRE_EXTINGUISHED(onfire_car_fire)) {
				GET_CAR_HEALTH(onfire_car, &onfire_car_health);
				if (car_health_test_timer < game_timer) {
					if (onfire_car_health < 700) {
						EXPLODE_CAR(onfire_car, 1, 0);
						PRINT_NOW("F_FAIL2", 5000, 1);
						fail_firetruck_mission = 1;
						return;
					}
				} else {
					SET_CAR_HEALTH(onfire_car, 1000);
				}
				if (onfire_car_flag == 0) {
					if (fires_extinguished_this_round == firetruck_level_minus_4) {
						SET_CAR_ONLY_DAMAGED_BY_PLAYER(onfire_car, 1);
						onfire_car_flag = 1;
					}
				}
			} else {
				if (!(onfire_car_flag == 10)) {
					REMOVE_BLIP(onfire_car_blip);
					SET_CAR_PROOFS(onfire_car, 0, 0, 0, 0, 0);
					FREEZE_CAR_POSITION(onfire_car, 0);
					TASK_EVERYONE_LEAVE_CAR(onfire_car);
					if (displayed_counter == 0) {
						displayed_counter = 1;
					}
					onfire_car_flag = 10;
					fires_extinguished++;
					fires_extinguished_this_round++;
				}
			}
		} else {
			if (IS_CAR_IN_WATER(onfire_car)) {
				if (!(onfire_car_flag == 10)) {
					REMOVE_BLIP(onfire_car_blip);
					SET_CAR_PROOFS(onfire_car, 0, 0, 0, 0, 0);
					FREEZE_CAR_POSITION(onfire_car, 0);
					TASK_EVERYONE_LEAVE_CAR(onfire_car);
					if (displayed_counter == 0) {
						displayed_counter = 1;
					}
					onfire_car_flag = 10;
					fires_extinguished++;
					fires_extinguished_this_round++;
				}
			} else {
				PRINT_NOW("F_FAIL2", 5000, 1);
				fail_firetruck_mission = 1;
				return;
			}
		}
	}
	return;
}

void do_cancelled_checks(void) {
	if (displayed_timer == 1) {
		if (fire_time_limit < 1) {
			PRINT_NOW("F_FAIL2", 5000, 1);
			fail_firetruck_mission = 1;
			return;
		}
	}
	if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("firetruk"))) {
		PRINT_NOW("F_CANC", 3000, 1);
		fail_firetruck_mission = 1;
		return;
	}
	mission_end_button_ft = 0;
	if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, 4)) && (IS_USING_CONTROLLER()))) {
		mission_end_button_ft = 1;
	}
	if (mission_end_button_ft == 1) {
		PRINT_NOW("F_CANC", 3000, 1);
		fail_firetruck_mission = 1;
		WAIT(1000);
		return;
	}
	return;
}

void firetruck_mission_loop(void) {
	while (true) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			fire_time_limit -= 1000;
			SETTIMERC(0);
		}
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = fire_time_limit / 1000;
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
		if (fail_firetruck_mission == 1) {
			failed();
		}
		GET_GAME_TIMER(&game_timer);
		do_cancelled_checks();
		if (fail_firetruck_mission == 1) {
			failed();
		}

		//if ((timemin == 0) && (timesec < 1))
		//{
		//	PRINT_NOW("F_FAIL2", 5000, 1);
		//	failed();
		//}
		
		onfire_car = onfire_car_1;
		onfire_car_fire = onfire_car_1_fire;
		onfire_car_flag = onfire_car_1_flag;
		onfire_car_blip = onfire_car_1_blip;
		do_fire_on_car_bit();
		onfire_car_1_fire = onfire_car_fire;
		onfire_car_1_flag = onfire_car_flag;
		onfire_car_1_blip = onfire_car_blip;
		if (firetruck_level > 1) {
			onfire_ped = onfire_ped_1;  
			onfire_ped_flag = onfire_ped_1_flag; 
			onfire_ped_fire = onfire_ped_1_fire;
			onfire_ped_blip = onfire_ped_1_blip; 
			do_fire_on_ped_bit();
			onfire_ped_1_flag = onfire_ped_flag; 
			onfire_ped_1_fire = onfire_ped_fire; 
			onfire_ped_1_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 2) {
			onfire_ped = onfire_ped_2;
			onfire_ped_flag = onfire_ped_2_flag; 
			onfire_ped_fire = onfire_ped_2_fire; 
			onfire_ped_blip = onfire_ped_2_blip; 
			do_fire_on_ped_bit();
			onfire_ped_2_flag = onfire_ped_flag; 
			onfire_ped_2_fire = onfire_ped_fire; 
			onfire_ped_2_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 3) {
			onfire_ped = onfire_ped_3;	  
			onfire_ped_flag = onfire_ped_3_flag; 
			onfire_ped_fire = onfire_ped_3_fire; 
			onfire_ped_blip = onfire_ped_3_blip; 
			do_fire_on_ped_bit();
			onfire_ped_3_flag = onfire_ped_flag; 
			onfire_ped_3_fire = onfire_ped_fire; 
			onfire_ped_3_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 4) {
			onfire_car = onfire_car_2;
			onfire_car_fire = onfire_car_2_fire;
			onfire_car_flag = onfire_car_2_flag;
			onfire_car_blip = onfire_car_2_blip;
			do_fire_on_car_bit();
			onfire_car_2_fire = onfire_car_fire;
			onfire_car_2_flag = onfire_car_flag;
			onfire_car_2_blip = onfire_car_blip;
		}
		if (firetruck_level > 5) {
			onfire_ped = onfire_ped_4;	  
			onfire_ped_flag = onfire_ped_4_flag; 
			onfire_ped_fire = onfire_ped_4_fire; 
			onfire_ped_blip = onfire_ped_4_blip; 
			do_fire_on_ped_bit();
			onfire_ped_4_flag = onfire_ped_flag; 
			onfire_ped_4_fire = onfire_ped_fire; 
			onfire_ped_4_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 6) {
			onfire_ped = onfire_ped_5;	  
			onfire_ped_flag = onfire_ped_5_flag; 
			onfire_ped_fire = onfire_ped_5_fire; 
			onfire_ped_blip = onfire_ped_5_blip; 
			do_fire_on_ped_bit();
			onfire_ped_5_flag = onfire_ped_flag; 
			onfire_ped_5_fire = onfire_ped_fire; 
			onfire_ped_5_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 7) {
			onfire_ped = onfire_ped_6;	  
			onfire_ped_flag = onfire_ped_6_flag;
			onfire_ped_fire = onfire_ped_6_fire; 
			onfire_ped_blip = onfire_ped_6_blip; 
			do_fire_on_ped_bit();
			onfire_ped_6_flag = onfire_ped_flag; 
			onfire_ped_6_fire = onfire_ped_fire; 
			onfire_ped_6_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 8) {
			onfire_car = onfire_car_3;
			onfire_car_fire = onfire_car_3_fire;
			onfire_car_flag = onfire_car_3_flag;
			onfire_car_blip = onfire_car_3_blip;
			do_fire_on_car_bit();
			onfire_car_3_fire = onfire_car_fire;
			onfire_car_3_flag = onfire_car_flag;
			onfire_car_3_blip = onfire_car_blip;
		}
		if (firetruck_level > 9) {
			onfire_ped = onfire_ped_7;	  
			onfire_ped_flag = onfire_ped_7_flag; 
			onfire_ped_fire = onfire_ped_7_fire; 
			onfire_ped_blip = onfire_ped_7_blip; 
			do_fire_on_ped_bit();
			onfire_ped_7_flag = onfire_ped_flag; 
			onfire_ped_7_fire = onfire_ped_fire; 
			onfire_ped_7_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 10) {
			onfire_ped = onfire_ped_8;	  
			onfire_ped_flag = onfire_ped_8_flag; 
			onfire_ped_fire = onfire_ped_8_fire; 
			onfire_ped_blip = onfire_ped_8_blip; 
			do_fire_on_ped_bit();
			onfire_ped_8_flag = onfire_ped_flag;
			onfire_ped_8_fire = onfire_ped_fire; 
			onfire_ped_8_blip = onfire_ped_blip; 
		}
		if (firetruck_level > 11) {
			onfire_ped = onfire_ped_9;	  
			onfire_ped_flag = onfire_ped_9_flag; 
			onfire_ped_fire = onfire_ped_9_fire; 
			onfire_ped_blip = onfire_ped_9_blip; 
			do_fire_on_ped_bit();
			onfire_ped_9_flag = onfire_ped_flag; 
			onfire_ped_9_fire = onfire_ped_fire; 
			onfire_ped_9_blip = onfire_ped_blip; 
		}
		if (fires_extinguished_this_round == fires_needing_extinguishing) {
			passed();
		}
	}
}

void next_fire(void) {
	do_cancelled_checks();
	if (fail_firetruck_mission == 1) {
		failed();
	}
	
	//IF flag_baron_mission2_passed = 0
		GENERATE_RANDOM_FLOAT_IN_RANGE(186.43, 1116.41, &car1_x);
		GENERATE_RANDOM_FLOAT_IN_RANGE(-1280.62, 1841.102, &car1_y);
	//ELSE
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1369.615, -985.473, 163.134, 2124.896, 0)) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1369.615, 163.134, &car1_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-985.473, 2124.896, &car1_y);
		} else {
			GENERATE_RANDOM_FLOAT_IN_RANGE(186.43, 1116.41, &car1_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1280.62, 1841.102, &car1_y);
		}
		
	if (firetruck_level < 5) {
		GET_CLOSEST_CAR_NODE(car1_x, car1_y, 5.0, &car1_x, &car1_y, &car1_z);
	} else {
		if (firetruck_level < 9) {
			Vector3 car1_vec, car2_vec;
			int temp1, temp2;
			float temp3;
			GET_CLOSEST_ROAD(car1_x, car1_y, 5.0, 12.0, 1, &car1_vec, &car2_vec, &temp1, &temp2, &temp3);
			car1_x = car1_vec.x;
			car1_y = car1_vec.y;
			car1_z = car1_vec.z;
			car2_x = car2_vec.x;
			car2_y = car2_vec.y;
			car2_z = car2_vec.z;
			if ((car1_x == 0.0) && (car1_y == 0.0) && (car2_x == 0.0) && (car2_y == 0.0)) {
				WAIT(0);
				next_fire();
			}
			dx = car2_x - car1_x;
			dy = car2_y - car1_y;
			temp_x = dx * dx;
			temp_y = dy * dy;
			temp_xy = temp_x + temp_y;
			temp_xy = SQRT(temp_xy);
			sum_x_y_temp = 12.0 / temp_xy;
			temp_x = dx * sum_x_y_temp;
			car2_x = car1_x + temp_x;
			temp_y = dy * sum_x_y_temp;
			car2_y = car1_y + temp_y;
			
			car1_z += 0.5;
			car2_z += 0.5;
		} else {
			Vector3 car2_vec, car3_vec;
			int temp1, temp2;
			float temp3;
			GET_CLOSEST_ROAD(car1_x, car1_y, 5.0, 18.0, 1, &car2_vec, &car3_vec, &temp1, &temp2, &temp3);
			car2_x = car2_vec.x;
			car2_y = car2_vec.y;
			car2_z = car2_vec.z;
			car3_x = car3_vec.x;
			car3_y = car3_vec.y;
			car3_z = car3_vec.z;
			if ((car2_x == 0.0) && (car2_y == 0.0) && (car3_x == 0.0) && (car3_y == 0.0)) {
				WAIT(0);
				next_fire();
			}
			dx = car3_x - car2_x;
			dy = car3_y - car2_y;
			temp_x = dx * dx;
			temp_y = dy * dy;
			temp_xy = temp_x + temp_y;
			temp_xy = SQRT(temp_xy);
			sum_x_y_temp = 18.0 / temp_xy;
			temp_x = dx * sum_x_y_temp;
			car3_x = car2_x + temp_x;
			temp_y = dy * sum_x_y_temp;
			car3_y = car2_y + temp_y;
			
			car1_x = car2_x	- car3_x;
			car1_x = car1_x / 2.0;
			car1_x = car1_x	+ car3_x;
			
			car1_y = car2_y	- car3_y;
			car1_y = car1_y / 2.0;
			car1_y = car1_y	+ car3_y;
			
			car1_z = car2_z	- car3_z;
			car1_z = car1_z / 2.0;
			car1_z = car1_z	+ car3_z;
			
			car2_z += 0.5;
			car1_z += 0.5;
			car3_z += 0.5;
		}
	}
	
	if (car1_z < 2.0) {
		WAIT(0);
		next_fire();
	}
	
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
	GET_DISTANCE_BETWEEN_COORDS_2D(player_x, player_y, car1_x, car1_y, &players_distance_from_fire);
	
	if ((players_distance_from_fire < 150.0) || (players_distance_from_fire > 600.0)) {
		WAIT(0);
		next_fire();
	}
	
	if ((car1_x > -1475.785) && (car1_x < -672.785) && (car1_y > 1278.678) && (car1_y < 2306.513)) {
		WAIT(0);
		next_fire();
	}
	if ((car1_x > 168.018) && (car1_x < 603.188) && (car1_y > 258.942) && (car1_y < 2222.059)) {
		WAIT(0);
		next_fire();
	}
	if ((car1_x > 597.191) && (car1_x < 692.713) && (car1_y > 346.926) && (car1_y < 1164.97)) {
		WAIT(0);
		next_fire();
	}
	if ((car1_x > -298.729) && (car1_x < 170.334) && (car1_y > 529.399) && (car1_y < 595.853)) {
		WAIT(0);
		next_fire();
	}
	if ((car1_x > 253.88) && (car1_x < 497.112) && (car1_y > 34.183) && (car1_y < 116.519)) {
		WAIT(0);
		next_fire();
	}
	if ((car1_x > -329.855) && (car1_x < 261.566) && (car1_y > -134.099) && (car1_y < 309.382)) {
		WAIT(0);
		next_fire();
	}
	// флаг миссии, после которой открывается второй остров
	/*if (flag_baron_mission2_passed == 0)
		if ((car1_x > -1894.212) && (car1_x < 172.402) && (car1_y > -1494.821) && (car1_y < 2427.426)) {
			WAIT(0);
			next_fire();
		}
		if ((car1_x > 168.018) && (car1_x < 603.188) && (car1_y > 258.942) && (car1_y < 2222.059)) {
			WAIT(0);
			next_fire();
		}
		if ((car1_x > 168.657) && (car1_x < 469.828) && (car1_y > -196.217) && (car1_y < 258.488)) {
			WAIT(0);
			next_fire();
		}
		if ((car1_x > 597.191) && (car1_x < 692.713) && (car1_y > 346.926) && (car1_y < 1164.97)) {
			WAIT(0);
			next_fire();
		}	
	}*/
	
	fire_time_limit_float = players_distance_from_fire / time_divider;
	fire_time_limit_float = fire_time_limit_float * 1000.0;
	intermediate_int = fire_time_limit_float;
	fire_time_limit += intermediate_int;
	if (fires_extinguished == 0) {
		if (fire_time_limit < 50000) {
			fire_time_limit = 50000;
		}
	}
	while (!HAS_MODEL_LOADED(random_car_model)) {
		WAIT(0);
		do_cancelled_checks();
		if (fail_firetruck_mission == 1) {
			failed();
		}
	}
	
	CREATE_CAR(random_car_model, car1_x, car1_y, car1_z, &onfire_car_1, 1);
	GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_car_heading);
	SET_CAR_HEADING(onfire_car_1, random_car_heading);
	SET_CAR_ON_GROUND_PROPERLY(onfire_car_1);
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(onfire_car_1, 0.0, 2.0, 0.3, &objx, &objy, &objz);
	onfire_car_1_fire = START_SCRIPT_FIRE(objx, objy, objz, 5, 3);
	SET_CAR_PROOFS(onfire_car_1, 1, 1, 1, 1, 1);
	FREEZE_CAR_POSITION(onfire_car_1, 1);
	ADD_BLIP_FOR_CAR(onfire_car_1, &onfire_car_1_blip);
	CHANGE_BLIP_DISPLAY(onfire_car_1_blip, 2);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(onfire_car_1, 1);
	fires_needing_extinguishing++;
	
	CREATE_RANDOM_CHAR_AS_DRIVER(onfire_car_1, &onfire_ped_1);
	SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_1, 1);
	fires_needing_extinguishing++;
	
	if (firetruck_level > 2) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(onfire_car_1, 0, &onfire_ped_2);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_2, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 3) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(onfire_car_1, 1, &onfire_ped_3);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_3, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 4) {
		temp_x = car2_x - 5.0;
		x = temp_x + 10.0;
		GENERATE_RANDOM_FLOAT_IN_RANGE(temp_x, x, &car2_x);
		temp_y = car2_y - 5.0;
		y = temp_y + 10.0;
		GENERATE_RANDOM_FLOAT_IN_RANGE(temp_y, y, &car2_y);
		CREATE_CAR(random_car_model, car2_x, car2_y, car2_z, &onfire_car_2, 1);
		TURN_CAR_TO_FACE_COORD(onfire_car_2, car1_x, car1_y);
		SET_CAR_ON_GROUND_PROPERLY(onfire_car_2);
		GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(onfire_car_2, 0.0, 2.0, 0.3, &objx, &objy, &objz);
		onfire_car_2_fire = START_SCRIPT_FIRE(objx, objy, objz, 5, 3);
		SET_CAR_PROOFS(onfire_car_2, 1, 1, 1, 1, 1);
		ADD_BLIP_FOR_CAR(onfire_car_2, &onfire_car_2_blip);
		CHANGE_BLIP_DISPLAY(onfire_car_2_blip, 2);
		SET_UPSIDEDOWN_CAR_NOT_DAMAGED(onfire_car_2, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 5) {
		CREATE_RANDOM_CHAR_AS_DRIVER(onfire_car_2, &onfire_ped_4);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_4, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 6) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(onfire_car_2, 0, &onfire_ped_5);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_5, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 7) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(onfire_car_2, 1, &onfire_ped_6);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_6, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 8) {
		temp_x = car3_x - 5.0;
		x = temp_x + 10.0;
		GENERATE_RANDOM_FLOAT_IN_RANGE(temp_x, x, &car3_x);
		temp_y = car3_y - 5.0;
		y = temp_y + 10.0;
		GENERATE_RANDOM_FLOAT_IN_RANGE(temp_y, y, &car3_y);
		CREATE_CAR(random_car_model, car3_x, car3_y, car3_z, &onfire_car_3, 1);
		TURN_CAR_TO_FACE_COORD(onfire_car_3, car1_x, car1_y);
		SET_CAR_ON_GROUND_PROPERLY(onfire_car_3);
		GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(onfire_car_3, 0.0, 2.0, 0.3, &objx, &objy, &objz);
		onfire_car_3_fire = START_SCRIPT_FIRE(objx, objy, objz, 5, 3);
		SET_CAR_PROOFS(onfire_car_3, 1, 1, 1, 1, 1);
		ADD_BLIP_FOR_CAR(onfire_car_3, &onfire_car_3_blip);
		CHANGE_BLIP_DISPLAY(onfire_car_3_blip, 2);
		SET_UPSIDEDOWN_CAR_NOT_DAMAGED(onfire_car_3, 1);
		fires_needing_extinguishing++;
	}
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	if (firetruck_level > 9) {
		CREATE_RANDOM_CHAR_AS_DRIVER(onfire_car_3, &onfire_ped_7);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_7, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 10) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(onfire_car_3, 0, &onfire_ped_8);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_8, 1);
		fires_needing_extinguishing++;
	}
	if (firetruck_level > 11) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(onfire_car_3, 1, &onfire_ped_9);
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(onfire_ped_9, 1);
		fires_needing_extinguishing++;
	}

	if (!IS_CHAR_DEAD(onfire_ped_1)) {
		char* zonName = GET_NAME_OF_ZONE(car1_x, car1_y, car1_z);	
		if (firetruck_level < 5) {
			PRINT_STRING_IN_STRING_NOW("F_START", zonName, 5000, 1);
		} else {
			PRINT_STRING_IN_STRING_NOW("F_STAR1", zonName, 5000, 1);
		}
	}
	if (firetruck_level == 1) {
		fires_needing_extinguishing--;
		DELETE_CHAR(&onfire_ped_1);
	}
	if (displayed_timer == 0) {
		displayed_timer = 1;
	}
	firetruck_level_minus_4 = firetruck_level - 4;
	GET_GAME_TIMER(&game_timer);
	car_health_test_timer = game_timer + 3000;
	firetruck_mission_loop();
}

void fire_generation_start(void) {
	fires_needing_extinguishing = 0;
	fires_extinguished_this_round = 0;

	onfire_car_1_flag = 0;
	onfire_car_2_flag = 0;
	onfire_car_3_flag = 0;
	onfire_ped_1_flag = 0;
	onfire_ped_2_flag = 0;
	onfire_ped_3_flag = 0;
	onfire_ped_4_flag = 0;
	onfire_ped_5_flag = 0;
	onfire_ped_6_flag = 0;
	onfire_ped_7_flag = 0;
	onfire_ped_8_flag = 0;
	onfire_ped_9_flag = 0;
	PRINT_WITH_NUMBER("FIRELVL", firetruck_level, 3000, 1);
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_car);
	SWITCH_CAR_SIREN(players_car, 1);
	WAIT(1500);
	GENERATE_RANDOM_INT_IN_RANGE(25, 44, &random_int);
	if (random_int == 25) {
		random_car_model = GET_HASH_KEY("sentinel");
	}
	if (random_int == 26) {
		random_car_model = GET_HASH_KEY("moonbeam");
	}
	if (random_int == 27) {
		random_car_model = GET_HASH_KEY("washington");
	}
	if (random_int == 28) {
		random_car_model = GET_HASH_KEY("landstalker");
	}
	if (random_int == 29) {
		random_car_model = GET_HASH_KEY("perennial");
	}
	if (random_int == 30) {
		random_car_model = GET_HASH_KEY("admiral");
	}
	if (random_int == 31) {
		random_car_model = GET_HASH_KEY("marbella");
	}
	if (random_int == 32) {
		random_car_model = GET_HASH_KEY("pmp600");
	}
	if (random_int == 33) {
		random_car_model = GET_HASH_KEY("ingot");
	}
	if (random_int == 34) {
		random_car_model = GET_HASH_KEY("pony");
	}
	if (random_int == 35) {
		random_car_model = GET_HASH_KEY("taxi");
	}
	if (random_int == 36) {
		random_car_model = GET_HASH_KEY("taxi");
	}
	if (random_int == 37) {
		random_car_model = GET_HASH_KEY("steed");
	}
	if (random_int == 38) {
		random_car_model = GET_HASH_KEY("burrito2");
	}
	if (random_int == 39) {
		random_car_model = GET_HASH_KEY("patriot");
	}
	if (random_int == 40) {
		random_car_model = GET_HASH_KEY("burrito");
	}
	if (random_int == 41) {
		random_car_model = GET_HASH_KEY("cabby");
	}
	if (random_int == 42) {
		random_car_model = GET_HASH_KEY("pinnacle");
	}
	if (random_int == 43) {
		random_car_model = GET_HASH_KEY("sultanrs");
	}
	REQUEST_MODEL(random_car_model);
	next_fire();
}

void mission_start_fire(void) {
	WAIT(0);
	LOAD_ADDITIONAL_TEXT("FIRETRK", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	fire_time_limit = 0;
	score_ft = 0;
	displayed_timer = 0;
	fires_extinguished = 0;
	displayed_counter = 0;
	total_score = 0;
	mission_end_button_ft = 0;
	time_divider = 5.5;
	firetruck_level = 1;
	fail_firetruck_mission = 0;
	random_car_model = 0;
	intermediate_int = 0;
	players_car_health = 0;
	onfire_car_1 = -1;
	onfire_car_1 = -1;
	onfire_car_1 = -1;
	car_health_test_timer = 0;
	
	onfire_ped_1_fire = 0;
	onfire_ped_2_fire = 0;
	onfire_ped_3_fire = 0;
	onfire_ped_4_fire = 0;
	onfire_ped_5_fire = 0;
	onfire_ped_6_fire = 0;
	onfire_ped_7_fire = 0;
	onfire_ped_8_fire = 0;
	onfire_ped_9_fire = 0;
	
	SET_WANTED_MULTIPLIER(0.5);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "FIRE_M");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	fire_generation_start();
}

void main(void) {

	mission_start_fire();
	failed();
}