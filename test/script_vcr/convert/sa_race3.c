/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
Car car1, car2, car3;
Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11;
Texture fon, timer;
Blip Blip_r, Blip_r2, Blip_c1, Blip_c2, Blip_c3;
uint checkpoint;
float help_text;
float textur, skip, start_race, poziteon, time_m, time_s, zone;
float Blip_x, Blip_y, Blip_z, Blip_x2, Blip_y2, Blip_z2;
float PlayX, PlayY, PlayZ, PlayR, PlayH, play_cord, startX, startY, startZ, startH;
float Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, Ped1R, ped1_cord, SetSped1;
float Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, Ped2R, ped2_cord, SetSped2;
float Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, Ped3R, ped3_cord, SetSped3;
float water1X, water1Y, water1Z, water1R, water2X, water2Y, water2Z, water2R, water3X, water3Y, water3Z, water3R;
float sped_wall1, sped_wall2, sped_wall3, time_wall;

void position(void)
{
	//***************** ������� *****************
	GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//��������� ���������� ��������� � ����������
	GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//�������� "����� �� �����������"
	GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//��������� ���������� ��������� � ����������
	GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//�������� "����� �� �����������"
	GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//��������� ���������� ��������� � ����������
	GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//�������� "����� �� �����������"
	GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
	GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//�������� "����� �� �����������"

	if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped2R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 1;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 2;
				}
			}
			else if (PlayR > Ped2R)//0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
		}
		else if (PlayR > Ped1R)//0
		{
			if (PlayR < Ped2R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
			else if (PlayR > Ped2R)//0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 3;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 4;
				}
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped2R)//0
			{
				poziteon = 2;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped2R)//0
			{
				poziteon = 3;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 2;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 2;
			}
		}
		else if (PlayR > Ped2R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			poziteon = 1;
		}
		else if (PlayR > Ped1R) //0
		{
			poziteon = 2;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 1;
		}
		else if (PlayR > Ped2R) //0
		{
			poziteon = 2;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 1;
		}
		else if (PlayR > Ped3R) //0
		{
			poziteon = 2;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
	{
		poziteon = 1;
	}
	else if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped2R)//0
			{
				poziteon = 3;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped2R)//0
			{
			poziteon = 4;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 4;
			}
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
		else if (PlayR > Ped2R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 4;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			poziteon = 3;
		}
		else if (PlayR > Ped1R) //0
		{
			poziteon = 4;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 3;
		}
		else if (PlayR > Ped2R) //0
		{
			poziteon = 4;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 3;
		}
		else if (PlayR > Ped3R) //0
		{
			poziteon = 4;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 4;
	}
	//======
	else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}

	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 3;
	}
	else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 2;
	}
	else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord > ped3_cord))
	{
		poziteon = 2;
	}

	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
	{
		poziteon = 2;
	}
	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 3;
	}
	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 3;
	}
	return;
}
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
void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// ������� ����� ����/���������
		{
			break;
		}
	}
}
void sa_race(void)
{
	uint Ped_hp4, Ped_hp5, Ped_hp6, Ped_hp7, Ped_hp8, Ped_hp9, Ped_hp10, Ped_hp11;
	
	help_text = 0;
	skip = 0;
	zone = 1;
	start_race = 0;
	time_m = 0;
	time_s = 0;

	startX = 634.489;
	startY = 187.797;
	startZ = 4.52925;
	startH = 165.0;

	Blip_x = 620.464;
	Blip_y = 116.854;
	Blip_z = 4.8329;
	Blip_x2 = 613.55;
	Blip_y2 = 33.5422;
	Blip_z2 = 5.0699;
	play_cord = 1;

	ped1B_x = 620.464;
	ped1B_y = 116.854;
	ped1B_z = 4.8329;
	SetSped1 = 0;
	ped1_cord = 1;

	ped2B_x = 620.464;
	ped2B_y = 116.854;
	ped2B_z = 4.8329;
	SetSped2 = 0;
	ped2_cord = 1;

	ped3B_x = 620.464;
	ped3B_y = 116.854;
	ped3B_z = 4.8329;
	SetSped3 = 0;
	ped3_cord = 1;

	SWITCH_ROADS_OFF( 715.988, 109.372, -1.286, 602.218, 333.631, 80.0 );// ��������� ���� �������
	//SET_CAR_DENSITY_MULTIPLIER(0.4);// ��������� ����

	ADD_BLIP_FOR_COORD(startX, startY, startZ, &Blip_r);//������� ������ �� ������
	CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//�������� ������ �� ������ "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_r, 5);   //���� ������ �� ������ (0=����� 5=������� 19=�����)
	CHANGE_BLIP_SCALE(Blip_r, 0.6); // ������� ������ �� ������
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_POINT");//������ �� ������ ��������� � ������� ����� ""

	textur = LOAD_TXD( "sunshine_race" );
	fon = GET_TEXTURE( textur, "fon_hud" );
	timer = GET_TEXTURE( textur, "timer_hud" );

	uint CarM1 = MODEL_INFERNUS;//���������� "Car2" = ������ ������
	uint CarM2 = MODEL_BANSHEE;//���������� "Car2" = ������ ������
	uint CarM3 = MODEL_SUPERGT;//���������� "Car2" = ������ ������
	uint PedM1 = MODEL_F_Y_CDRESS_01;////���������� "Ped1" = ������ ������� ����
	uint PedM2 = MODEL_M_Y_BOHO_01;////���������� "Ped1" = ������ ������� ����
	uint PedM3 = MODEL_M_Y_GIRI_LO_01;////���������� "Ped1" = ������ ������� ����

	uint PedM4 = MODEL_F_Y_PMANHAT_02;////���������� "Ped1" = ������ ������� ����
	uint PedM5 = MODEL_F_Y_PVILLBO_02;////���������� "Ped1" = ������ ������� ����
	uint PedM6 = MODEL_M_Y_MODO;////���������� "Ped1" = ������ ������� ����
	uint PedM7 = MODEL_M_Y_PCOOL_02;////���������� "Ped1" = ������ ������� ����

	// ��������� ��������
	REQUEST_ANIMS( "vcNE_race_funs" );//��������� ���� � ���������
	while (!HAVE_ANIMS_LOADED( "vcNE_race_funs" )) WAIT(0);

	REQUEST_MODEL(CarM1);//�������� ������ ������ �� ����������
	while (!HAS_MODEL_LOADED(CarM1));//�������� "������ �����������" ���� ��� �� �������� � ������
	CREATE_CAR(CarM1, (-4*COS((1-startH))+0*SIN((1-startH)))+startX, (0*COS((1-startH))-(-4*SIN((1-startH))))+startY, startZ, &car1, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
	SET_CAR_HEADING(car1, startH);//������ �������� ������

	REQUEST_MODEL(CarM2);//�������� ������ ������ �� ����������
	while (!HAS_MODEL_LOADED(CarM2));//�������� "������ �����������" ���� ��� �� �������� � ������
	CREATE_CAR(CarM2, (-4*COS((1-startH))+6*SIN((1-startH)))+startX, (6*COS((1-startH))-(-4*SIN((1-startH))))+startY, startZ, &car2, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
	SET_CAR_HEADING(car2, startH);//������ �������� ������

	REQUEST_MODEL(CarM3);//�������� ������ ������ �� ����������
	while (!HAS_MODEL_LOADED(CarM3));//�������� "������ �����������" ���� ��� �� �������� � ������
	CREATE_CAR(CarM3, (0*COS((1-startH))+6*SIN((1-startH)))+startX, (6*COS((1-startH))-(0*SIN((1-startH))))+startY, startZ, &car3, TRUE);// ������ ������,(������ � ����������"Car2"),("&a2"���������� � ������� ������� �������� ������) �� ������ �����������
	SET_CAR_HEADING(car3, startH);//������ �������� ������

	REQUEST_MODEL(PedM1);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM1));////�������� "��� ����������" ���� ��� �� �������� � ������
	CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//������ ���� �� ���� ����������

	REQUEST_MODEL(PedM2);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM2));////�������� "��� ����������" ���� ��� �� �������� � ������
	CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped2);//������ ���� �� ���� ����������

	REQUEST_MODEL(PedM3);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM3));////�������� "��� ����������" ���� ��� �� �������� � ������
	CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped3);//������ ���� �� ���� ����������

	REQUEST_MODEL(PedM4);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM4));////�������� "��� ����������" ���� ��� �� �������� � ������

	REQUEST_MODEL(PedM5);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM5));////�������� "��� ����������" ���� ��� �� �������� � ������

	REQUEST_MODEL(PedM6);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM6));////�������� "��� ����������" ���� ��� �� �������� � ������

	REQUEST_MODEL(PedM7);//�������� ������ ������ ���� �� ����������
	while (!HAS_MODEL_LOADED(PedM7));////�������� "��� ����������" ���� ��� �� �������� � ������

	CREATE_CHAR (26, PedM1, (3.5*COS((1-startH))+5.1*SIN((1-startH)))+startX, (5.1*COS((1-startH))-(3.5*SIN((1-startH))))+startY, startZ, &ped4, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM2, (3.7*COS((1-startH))+3.7*SIN((1-startH)))+startX, (3.7*COS((1-startH))-(3.7*SIN((1-startH))))+startY, startZ, &ped5, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM3, (3.4*COS((1-startH))+2.0*SIN((1-startH)))+startX, (2.0*COS((1-startH))-(3.4*SIN((1-startH))))+startY, startZ, &ped6, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM4, (-7.8*COS((1-startH))+5.8*SIN((1-startH)))+startX, (5.8*COS((1-startH))-(-7.8*SIN((1-startH))))+startY, startZ, &ped7, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM5, (-8.9*COS((1-startH))+3.8*SIN((1-startH)))+startX, (3.8*COS((1-startH))-(-8.9*SIN((1-startH))))+startY, startZ, &ped8, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM6, (-7.6*COS((1-startH))+3.4*SIN((1-startH)))+startX, (3.4*COS((1-startH))-(-7.6*SIN((1-startH))))+startY, startZ, &ped9, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM7, (-8.3*COS((1-startH))+1.8*SIN((1-startH)))+startX, (1.8*COS((1-startH))-(-8.3*SIN((1-startH))))+startY, startZ, &ped10, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������
	CREATE_CHAR (26, PedM1, (-7.7*COS((1-startH))+0.2*SIN((1-startH)))+startX, (0.2*COS((1-startH))-(-7.7*SIN((1-startH))))+startY, startZ, &ped11, TRUE);// ������ ����,(������ � ����������"Ped1"),("&p1"���������� � ������� ������� �������� ����) �� ������ �����������

	SET_CHAR_PROOFS(ped1, TRUE, TRUE, TRUE, TRUE, TRUE);//������ ���� ����������
	SET_CHAR_PROOFS(ped2, TRUE, TRUE, TRUE, TRUE, TRUE);//������ ���� ����������
	SET_CHAR_PROOFS(ped3, TRUE, TRUE, TRUE, TRUE, TRUE);//������ ���� ����������
	SET_CAR_PROOFS(car1, TRUE, TRUE, TRUE, TRUE, TRUE);//������ ������ ����������
	SET_CAR_PROOFS(car2, TRUE, TRUE, TRUE, TRUE, TRUE);//������ ������ ����������
	SET_CAR_PROOFS(car3, TRUE, TRUE, TRUE, TRUE, TRUE);//������ ������ ����������
	SET_CAN_BURST_CAR_TYRES(car1, 0); // ���� ���������� ������ ���������
	SET_CAN_BURST_CAR_TYRES(car2, 0); // ���� ���������� ������ ���������
	SET_CAN_BURST_CAR_TYRES(car3, 0); // ���� ���������� ������ ���������
	LOCK_CAR_DOORS(car1, 3); //��������� ����� ���������� ��� ������
	LOCK_CAR_DOORS(car2, 3); //��������� ����� ���������� ��� ������
	LOCK_CAR_DOORS(car3, 3); //��������� ����� ���������� ��� ������

	SET_CHAR_HEADING(ped4, 75.0+startH);
	SET_CHAR_HEADING(ped5, 95.0+startH);
	SET_CHAR_HEADING(ped6, 85.0+startH);
	SET_CHAR_HEADING(ped7, -95.0+startH);
	SET_CHAR_HEADING(ped8, -95.0+startH);
	SET_CHAR_HEADING(ped9, -80.0+startH);
	SET_CHAR_HEADING(ped10, -110.0+startH);
	SET_CHAR_HEADING(ped11, -90.0+startH);

	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "crowd_excited_a", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "crowd_excited_b", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "crowd_negative", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "stactic_celeb_a", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "crowd_positive", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "crowd_negative", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "crowd_excited_b", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "crowd_excited_a", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//���������������� �������� �� ����

	CLEAR_AREA( startX, startY, startZ, 65.0, 1);//������� ���� ��������
	GET_CAR_HEADING(car1, &startH); //�������� ���� �������� ������
	while(true)
	{
		WAIT(0);
		DRAW_CHECKPOINT( startX, startY, startZ, 2, 160, 116, 209);//�������� �������� �� ����������� � ��� ����
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, startX, startY, startZ, &PlayR);//�������� "����� �� �����������"
		if ( PlayR < 2.0)
		{
			if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) //��������� "����� � ������"
			{
				GET_CHAR_HEADING(GetPlayerPed(), &PlayH); //�������� ���� �������� ������
				if ((PlayH > (startH-20)) && (PlayH < (startH+20))) //��������� "���� ������ � ���������� ����������"
				{
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//������������ ������
					break;
				}
				else
				{
					if (help_text == 0)
					{
						PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT6", 350, 1);//������� �� ����� ��������� "���������� ������"
						help_text = 1;
					}
				}
			}
			else
			{
				if (help_text == 0)
				{
					PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT7", 350, 1);//������� �� ����� ��������� "������� ���������� ������"
					help_text = 1;
				}
			}
		}
		else
		{
			if (help_text == 1)
			{
				help_text = 0;
			}
		}
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car1))) // ���� ����� ��������� ������ ���������
		{
			start_race = 1; //���������� � ��������� ��������� ������
			break;
		}
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car2))) // ���� ����� ��������� ������ ���������
		{
			start_race = 1; //���������� � ��������� ��������� ������
			break;
		}
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car3))) // ���� ����� ��������� ������ ���������
		{
			start_race = 1; //���������� � ��������� ��������� ������
			break;
		}
		
		//�������� �������� ���������
		GET_CHAR_HEALTH(ped4, &Ped_hp4);
		GET_CHAR_HEALTH(ped5, &Ped_hp5);
		GET_CHAR_HEALTH(ped6, &Ped_hp6);
		GET_CHAR_HEALTH(ped7, &Ped_hp7);
		GET_CHAR_HEALTH(ped8, &Ped_hp8);
		GET_CHAR_HEALTH(ped9, &Ped_hp9);
		GET_CHAR_HEALTH(ped10, &Ped_hp10);
		GET_CHAR_HEALTH(ped11, &Ped_hp11);
		if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), startX-25, startY-25, startX+25, startY+25, 0))//�������� ����� ����� ������ �� ������
		{
			PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT8", 3500, 1);//������� �� ����� ��������� "���-�� ������ ��������,����� ��������"
			skip = 1;
			PANIC_SCREAM(ped4);
			PANIC_SCREAM(ped5);
			PANIC_SCREAM(ped6);
			PANIC_SCREAM(ped7);
			PANIC_SCREAM(ped8);
			PANIC_SCREAM(ped9);
			PANIC_SCREAM(ped10);
			PANIC_SCREAM(ped11);
			break;
		}
		else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
		{
			skip = 1;
			break;
		}
		else if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), startX-30, startY-30, startX+30, startY+30, 0 )) && (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)))
		{
			PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT12", 3500, 1);//������� �� ����� ��������� "�� �������� �� ����� �����, ��� ��������� ���� ����������."
			skip = 1;
			PANIC_SCREAM(ped4);
			PANIC_SCREAM(ped5);
			PANIC_SCREAM(ped6);
			PANIC_SCREAM(ped7);
			PANIC_SCREAM(ped8);
			PANIC_SCREAM(ped9);
			PANIC_SCREAM(ped10);
			PANIC_SCREAM(ped11);
			break;
		}
		else if (( Ped_hp4 < 195 ) || ( Ped_hp5 < 195 ) || ( Ped_hp6 < 195 ) || ( Ped_hp7 < 195 ) || ( Ped_hp8 < 195 ) || ( Ped_hp9 < 195 ) || ( Ped_hp10 < 195 ) || ( Ped_hp11 < 195 ))
		{
			PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT9", 3500, 1);//������� �� ����� ��������� "������� �� ����� ���������. ����� ��������"
			skip = 1;
			PANIC_SCREAM(ped4);
			PANIC_SCREAM(ped5);
			PANIC_SCREAM(ped6);
			PANIC_SCREAM(ped7);
			PANIC_SCREAM(ped8);
			PANIC_SCREAM(ped9);
			PANIC_SCREAM(ped10);
			PANIC_SCREAM(ped11);
			break;
		}
	}
	// ���� ����� ���
	if (skip == 0)
	{
		REMOVE_BLIP(Blip_r);//������� ������ �� ������
		ADD_BLIP_FOR_CHAR(ped1, &Blip_c1);
		CHANGE_BLIP_SPRITE(Blip_c1, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(Blip_c1, 12);   //���� ������ �� ������ (0=�����)
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c1, "NE_RACE1");//������ �� ������ "Blip01" ��������� � ������� �����
		CHANGE_BLIP_SCALE(Blip_c1, 0.77999990); // ������� ������ �� ������

		ADD_BLIP_FOR_CHAR(ped2, &Blip_c2);
		CHANGE_BLIP_SPRITE(Blip_c2, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(Blip_c2, 8);   //���� ������ �� ������ (0=�����)
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c2, "NE_RACE1");//������ �� ������ "Blip01" ��������� � ������� �����
		CHANGE_BLIP_SCALE(Blip_c2, 0.77999990); // ������� ������ �� ������

		ADD_BLIP_FOR_CHAR(ped3, &Blip_c3);
		CHANGE_BLIP_SPRITE(Blip_c3, BLIP_DESTINATION);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(Blip_c3, 19);   //���� ������ �� ������ (0=�����)
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c3, "NE_RACE1");//������ �� ������ "Blip01" ��������� � ������� �����
		CHANGE_BLIP_SCALE(Blip_c3, 0.77999990); // ������� ������ �� ������

		SETTIMERA( 0 );
		SETTIMERB( 0 );
		while(true)
		{
			WAIT(0);
			if (start_race == 0)
			{
				PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
				SETTIMERA(0);
				while (true)
				{
					SET_TEXT_FONT(4);
					SET_TEXT_COLOUR(235, 115, 18, 255);
					SET_TEXT_SCALE(0.5, 0.7);
					SET_TEXT_EDGE(2, 0, 0, 0, 255);
					SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 3);// 3
					if (TIMERA() > 999)
					{
						break;
					}
					WAIT(0);
				}
				PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
				SETTIMERA(0);
				while (true)
				{
					SET_TEXT_FONT(4);
					SET_TEXT_COLOUR(235, 115, 18, 255);
					SET_TEXT_SCALE(0.5, 0.7);
					SET_TEXT_EDGE(2, 0, 0, 0, 255);
					SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 2);// 2
					if (TIMERA() > 999)
					{
						break;
					}
					WAIT(0);
				}
				PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
				SETTIMERA(0);
				while (true)
				{
					SET_TEXT_FONT(4);
					SET_TEXT_COLOUR(235, 115, 18, 255);
					SET_TEXT_SCALE(0.5, 0.7);
					SET_TEXT_EDGE(2, 0, 0, 0, 255);
					SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 1);// 1
					if (TIMERA() > 999)
					{
						break;
					}
					WAIT(0);
				}
				start_race = 2;
			}

			// ����� ���
			if (start_race == 1)
			{
				if (TIMERA() < 900)
				{
					SET_TEXT_FONT(4);
					SET_TEXT_COLOUR(235, 115, 18, 255);
					SET_TEXT_SCALE(0.5, 0.7);
					SET_TEXT_EDGE(2, 0, 0, 0, 255);
					SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "VC2_RACE_TEXT11", 1); // ����� "3...2...1... GO"
				}
				else
				{
					start_race = 3;
				}
			}
			else if (start_race == 2)
			{
				if (TIMERA() < 900)
				{
					SET_TEXT_FONT(4);
					SET_TEXT_COLOUR(235, 115, 18, 255);
					SET_TEXT_SCALE(0.5, 0.7);
					SET_TEXT_EDGE(2, 0, 0, 0, 255);
					SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "GO", 1); // ����� "GO"
				}
				else
				{
					start_race = 3;
				}
			}
			else if (start_race == 3)
			{
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// ������������� ������
				SET_CAR_DENSITY_MULTIPLIER(0.8);// ��������� ����
				PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)

				ADD_BLIP_FOR_COORD(Blip_x, Blip_y, Blip_z, &Blip_r);//������� ������ �� ������ � ���������� "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r, 5);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//������ �� ������ "Blip01" ��������� � ������� �����
				CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // ������� ������ �� ������
				checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.60000000 );
				
				ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, Blip_z2, &Blip_r2);//������� ������ �� ������ � ���������� "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r2, 5);   //���� ������ �� ������ (0=�����)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//������ �� ������ "Blip01" ��������� � ������� �����
				CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // ������� ������ �� ������
				CHANGE_BLIP_ALPHA(Blip_r2, 125);
				start_race = 99;
			}
			//������ �����
			if (zone == 1)
			{
				if (!IS_CHAR_IN_AREA_2D( GetPlayerPed(), startX-50, startY-50, startX+50, startY+50, 0 ))
				{
					SET_CHAR_COORDINATES(ped4, -925, -402, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped5, -926, -402, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped6, -927, -402, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped7, -926, -401, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped8, -926, -402, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped9, -926, -403, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped10, -925, -401, 10.);// ������� ���� �� �����
					SET_CHAR_COORDINATES(ped11, -927, -403, 10.);// ������� ���� �� �����
					zone = 0;
				}
			}
			DRAW_SPHERE(Blip_x, Blip_y, (Blip_z-4.5), 7.0);
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//��������� ���������� ������ � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//�������� "����� �� �����������"
			if ( PlayR < 8.5 )
			{
				play_cord += 1;
				Blip_x = Blip_x2; 
				Blip_y = Blip_y2;
				Blip_z = Blip_z2;
				PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );

				if (play_cord == 2)
				{
					Blip_x2 = 611.174;
					Blip_y2 = -62.76898;
					Blip_z2 = 10.5328;
				}
				else if (play_cord == 3)
				{
					Blip_x2 = 597.841;
					Blip_y2 = -170.383;
					Blip_z2 = 4.4007;
				}
				else if (play_cord == 4)
				{
					Blip_x2 = 558.795;
					Blip_y2 = -264.664;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 5)
				{
					Blip_x2 = 486.418;
					Blip_y2 = -330.375;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 6)
				{
					Blip_x2 = 391.1846;
					Blip_y2 = -339.898;
					Blip_z2 = 4.2782;
				}
				else if (play_cord == 7)
				{
					Blip_x2 = 326.336;
					Blip_y2 = -364.066;
					Blip_z2 = 4.2839;
				}
				else if (play_cord == 8)
				{
					Blip_x2 = 348.3296;
					Blip_y2 = -479.89;
					Blip_z2 = 4.2761;
				}
				else if (play_cord == 9)
				{
					Blip_x2 = 343.5679;
					Blip_y2 = -545.683;
					Blip_z2 = 4.2859;
				}
				else if (play_cord == 10)
				{
					Blip_x2 = 262.3964;
					Blip_y2 = -564.68;
					Blip_z2 = 4.2781;
				}
				else if (play_cord == 11)
				{
					Blip_x2 = 236.0393;
					Blip_y2 = -593.22;
					Blip_z2 = 4.2858;
				}
				else if (play_cord == 12)
				{
					Blip_x2 = 229.1521;
					Blip_y2 = -673.2099;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 13)
				{
					Blip_x2 = 230.1054;
					Blip_y2 = -748.4499;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 14)
				{
					Blip_x2 = 244.8036;
					Blip_y2 = -827.49;
					Blip_z2 = 4.2858;
				}
				else if (play_cord == 15)
				{
					Blip_x2 = 278.3767;
					Blip_y2 = -921.77;
					Blip_z2 = 4.2858;
				}
				else if (play_cord == 16)
				{
					Blip_x2 = 314.3141;
					Blip_y2 = -994.3708;
					Blip_z2 = 4.2858;
				}
				else if (play_cord == 17)
				{
					Blip_x2 = 371.2148;
					Blip_y2 = -1041;
					Blip_z2 = 4.2464;
				}
				else if (play_cord == 18)
				{
					Blip_x2 = 422.218;
					Blip_y2 = -1035.137;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 19)
				{
					Blip_x2 = 433.7286;
					Blip_y2 = -932.25;
					Blip_z2 = 4.2779;
				}
				else if (play_cord == 20)
				{
					Blip_x2 = 471.4977;
					Blip_y2 = -848.4399;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 21)
				{
					Blip_x2 = 499.7618;
					Blip_y2 = -769.4;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 22)
				{
					Blip_x2 = 512.1345;
					Blip_y2 = -676.07;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 23)
				{
					Blip_x2 = 515.2484;
					Blip_y2 = -600.8399;
					Blip_z2 = 4.2858;
				}
				else if (play_cord == 24)
				{
					Blip_x2 = 510.4462;
					Blip_y2 = -514.1701;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 25)
				{
					Blip_x2 = 515.9403;
					Blip_y2 = -423.703;
					Blip_z2 = 4.2613;
				}
				else if (play_cord == 26)
				{
					Blip_x2 = 556.4473;
					Blip_y2 = -352.278;
					Blip_z2 = 4.2465;
				}
				else if (play_cord == 27)
				{
					Blip_x2 = 606.4968;
					Blip_y2 = -280.853;
					Blip_z2 = 4.2465;
				}
				else if (play_cord == 28)
				{
					Blip_x2 = 647.6587;
					Blip_y2 = -217.047;
					Blip_z2 = 4.2465;
				}
				else if (play_cord == 29)
				{
					Blip_x2 = 668.4004;
					Blip_y2 = -152.288;
					Blip_z2 = 4.2372;
				}
				else if (play_cord == 30)
				{
					Blip_x2 = 692.9054;
					Blip_y2 = -61.81598;
					Blip_z2 = 3.8297;
				}
				else if (play_cord == 31)
				{
					Blip_x2 = 734.715;
					Blip_y2 = 7.70398;
					Blip_z2 = 3.8297;
				}
				else if (play_cord == 32)
				{
					Blip_x2 = 797.4172;
					Blip_y2 = 84.84299;
					Blip_z2 = 3.8482;
				}
				else if (play_cord == 33)
				{
					Blip_x2 = 848.5774;
					Blip_y2 = 129.603;
					Blip_z2 = 3.8482;
				}
				else if (play_cord == 34)
				{
					Blip_x2 = 885.7377;
					Blip_y2 = 180.076;
					Blip_z2 = 3.9641;
				}
				else if (play_cord == 35)
				{
					Blip_x2 = 910.2094;
					Blip_y2 = 289.595;
					Blip_z2 = 6.3418;
				}
				else if (play_cord == 36)
				{
					Blip_x2 = 914.9573;
					Blip_y2 = 393.399;
					Blip_z2 = 4.1372;
				}
				else if (play_cord == 37)
				{
					Blip_x2 = 952.2457;
					Blip_y2 = 464.8242;
					Blip_z2 = 4.5878;
				}
				else if (play_cord == 38)
				{
					Blip_x2 = 935.919;
					Blip_y2 = 531.4876;
					Blip_z2 = 5.0202;
				}
				else if (play_cord == 39)
				{
					Blip_x2 = 916.873;
					Blip_y2 = 630.5303;
					Blip_z2 = 5.304;
				}
				else if (play_cord == 40)
				{
					Blip_x2 = 863.4273;
					Blip_y2 = 591.4151;
					Blip_z2 = 5.1727;
				}
				else if (play_cord == 41)
				{
					Blip_x2 = 803.545;
					Blip_y2 = 542.9156;
					Blip_z2 = 5.3602;
				}
				else if (play_cord == 42)
				{
					Blip_x2 = 759.7381;
					Blip_y2 = 506.7269;
					Blip_z2 = 4.9985;
				}
				else if (play_cord == 43)
				{
					Blip_x2 = 742.1655;
					Blip_y2 = 423.874;
					Blip_z2 = 5.2687;
				}
				else if (play_cord == 44)
				{
					Blip_x2 = 705.4493;
					Blip_y2 = 347.687;
					Blip_z2 = 4.8572;
				}
				else if (play_cord == 45)
				{
					Blip_x2 = 662.6478;
					Blip_y2 = 266.739;
					Blip_z2 = 5.962;
				}
				else if (play_cord == 46)
				{
					Blip_x2 = 630.7795;
					Blip_y2 = 165.945;
					Blip_z2 = 4.6223;
				}
				else if (play_cord == 47)
				{
					Blip_x2 = Blip_x2; 
					Blip_y2 = Blip_y2;
					Blip_z2 = Blip_z2;
				}
				else if (play_cord == 48)
				{
					skip = 2;
					break;
				}
				if (play_cord < 47)
				{
					REMOVE_BLIP(Blip_r);//������� ������ �� ������
					REMOVE_BLIP(Blip_r2);//������� ������ �� ������
					DELETE_CHECKPOINT(checkpoint);
					ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//������� ������ �� ������ � ���������� "Blip01"
					CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(Blip_r, 5);   //���� ������ �� ������ (0=�����)
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//������ �� ������ "Blip01" ��������� � ������� �����
					CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // ������� ������ �� ������
					checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.50000000 );
					if (play_cord < 46)
					{
						ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//������� ������ �� ������ � ���������� "Blip01"
						CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(Blip_r2, 5);   //���� ������ �� ������ (0=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//������ �� ������ "Blip01" ��������� � ������� �����
						CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // ������� ������ �� ������
						CHANGE_BLIP_ALPHA(Blip_r2, 125);
					}
					else
					{
						ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//������� ������ �� ������ � ���������� "Blip01"
						CHANGE_BLIP_SPRITE(Blip_r2, BLIP_FINISH_LINE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(Blip_r2, 0);   //���� ������ �� ������ (0=�����)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//������ �� ������ "Blip01" ��������� � ������� �����
						CHANGE_BLIP_SCALE(Blip_r2, 0.77999990); // ������� ������ �� ������
						CHANGE_BLIP_ALPHA(Blip_r2, 125);
					}
				}
				else
				{
					REMOVE_BLIP(Blip_r);//������� ������ �� ������
					REMOVE_BLIP(Blip_r2);//������� ������ �� ������
					DELETE_CHECKPOINT(checkpoint);
					ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//������� ������ �� ������ � ���������� "Blip01"
					CHANGE_BLIP_SPRITE(Blip_r, BLIP_FINISH_LINE);//������ �� ������ "Blip01" ����� "BLIP_FINISH_LINE"
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//������ �� ������ "Blip01" ��������� � ������� �����
					CHANGE_BLIP_COLOUR(Blip_r, 0);   //���� ������ �� ������ (0=�����)
					checkpoint = CREATE_CHECKPOINT( 7, Blip_x, Blip_y, (Blip_z+1.5), Blip_x, Blip_y, Blip_z, 0.80000000 );
				}
			}

//============================== �������� 1 ==============================
			GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//��������� ���������� ��������� � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//�������� "����� �� �����������"
			if ( Ped1R < 55.0)
			{
				if (SetSped1 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 85.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped1 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped1 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 14.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
			}
			if ( Ped1R < 10.0)
			{
				ped1_cord += 1;
				water1X = ped1B_x;
				water1Y = ped1B_y;
				water1Z = ped1B_z;
				GET_CAR_HEADING(car1, &water1R);

				if (ped1_cord == 2)
				{
					ped1B_x = 613.55;
					ped1B_y = 33.5422;
					ped1B_z = 5.0699;
					SetSped1 = 0;
				}
				else if (ped1_cord == 3)
				{
					ped1B_x = 611.174;
					ped1B_y = -62.76898;
					ped1B_z = 10.5328;
					SetSped1 = 0;
				}
				else if (ped1_cord == 4)
				{
					ped1B_x = 597.841;
					ped1B_y = -170.383;
					ped1B_z = 4.4007;
					SetSped1 = 0;
				}
				else if (ped1_cord == 5)
				{
					ped1B_x = 558.795;
					ped1B_y = -264.664;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 6)
				{
					ped1B_x = 486.418;
					ped1B_y = -330.375;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 7)
				{
					ped1B_x = 391.1846;
					ped1B_y = -339.898;
					ped1B_z = 4.2782;
					SetSped1 = 0;
				}
				else if (ped1_cord == 8)
				{
					ped1B_x = 326.336;
					ped1B_y = -364.066;
					ped1B_z = 4.2839;
					SetSped1 = 2;
				}
				else if (ped1_cord == 9)
				{
					ped1B_x = 348.3296;
					ped1B_y = -479.89;
					ped1B_z = 4.2761;
					SetSped1 = 0;
				}
				else if (ped1_cord == 10)
				{
					ped1B_x = 343.5679;
					ped1B_y = -545.683;
					ped1B_z = 4.2859;
					SetSped1 = 1;
				}
				else if (ped1_cord == 11)
				{
					ped1B_x = 262.3964;
					ped1B_y = -564.68;
					ped1B_z = 4.2781;
					SetSped1 = 0;
				}
				else if (ped1_cord == 12)
				{
					ped1B_x = 236.0393;
					ped1B_y = -593.22;
					ped1B_z = 4.2858;
					SetSped1 = 0;
				}
				else if (ped1_cord == 13)
				{
					ped1B_x = 229.1521;
					ped1B_y = -673.2099;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 14)
				{
					ped1B_x = 230.1054;
					ped1B_y = -748.4499;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 15)
				{
					ped1B_x = 244.8036;
					ped1B_y = -827.49;
					ped1B_z = 4.2858;
					SetSped1 = 0;
				}
				else if (ped1_cord == 16)
				{
					ped1B_x = 278.3767;
					ped1B_y = -921.77;
					ped1B_z = 4.2858;
					SetSped1 = 0;
				}
				else if (ped1_cord == 17)
				{
					ped1B_x = 314.3141;
					ped1B_y = -994.3708;
					ped1B_z = 4.2858;
					SetSped1 = 0;
				}
				else if (ped1_cord == 18)
				{
					ped1B_x = 371.2148;
					ped1B_y = -1041;
					ped1B_z = 4.2464;
					SetSped1 = 0;
				}
				else if (ped1_cord == 19)
				{
					ped1B_x = 422.218;
					ped1B_y = -1035.137;
					ped1B_z = 4.278;
					SetSped1 = 1;
				}
				else if (ped1_cord == 20)
				{
					ped1B_x = 433.7286;
					ped1B_y = -932.25;
					ped1B_z = 4.2779;
					SetSped1 = 0;
				}
				else if (ped1_cord == 21)
				{
					ped1B_x = 471.4977;
					ped1B_y = -848.4399;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 22)
				{
					ped1B_x = 499.7618;
					ped1B_y = -769.4;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 23)
				{
					ped1B_x = 512.1345;
					ped1B_y = -676.07;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 24)
				{
					ped1B_x = 515.2484;
					ped1B_y = -600.8399;
					ped1B_z = 4.2858;
					SetSped1 = 0;
				}
				else if (ped1_cord == 25)
				{
					ped1B_x = 510.4462;
					ped1B_y = -514.1701;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 26)
				{
					ped1B_x = 515.9403;
					ped1B_y = -423.703;
					ped1B_z = 4.2613;
					SetSped1 = 0;
				}
				else if (ped1_cord == 27)
				{
					ped1B_x = 556.4473;
					ped1B_y = -352.278;
					ped1B_z = 4.2465;
					SetSped1 = 0;
				}
				else if (ped1_cord == 28)
				{
					ped1B_x = 606.4968;
					ped1B_y = -280.853;
					ped1B_z = 4.2465;
					SetSped1 = 0;
				}
				else if (ped1_cord == 29)
				{
					ped1B_x = 647.6587;
					ped1B_y = -217.047;
					ped1B_z = 4.2465;
					SetSped1 = 0;
				}
				else if (ped1_cord == 30)
				{
					ped1B_x = 668.4004;
					ped1B_y = -152.288;
					ped1B_z = 4.2372;
					SetSped1 = 0;
				}
				else if (ped1_cord == 31)
				{
					ped1B_x = 692.9054;
					ped1B_y = -61.81598;
					ped1B_z = 3.8297;
					SetSped1 = 0;
				}
				else if (ped1_cord == 32)
				{
					ped1B_x = 734.715;
					ped1B_y = 7.70398;
					ped1B_z = 3.8297;
					SetSped1 = 0;
				}
				else if (ped1_cord == 33)
				{
					ped1B_x = 797.4172;
					ped1B_y = 84.84299;
					ped1B_z = 3.8482;
					SetSped1 = 0;
				}
				else if (ped1_cord == 34)
				{
					ped1B_x = 848.5774;
					ped1B_y = 129.603;
					ped1B_z = 3.8482;
					SetSped1 = 1;
				}
				else if (ped1_cord == 35)
				{
					ped1B_x = 885.7377;
					ped1B_y = 180.076;
					ped1B_z = 3.9641;
					SetSped1 = 1;
				}
				else if (ped1_cord == 36)
				{
					ped1B_x = 910.2094;
					ped1B_y = 289.595;
					ped1B_z = 6.3418;
					SetSped1 = 0;
				}
				else if (ped1_cord == 37)
				{
					ped1B_x = 914.9573;
					ped1B_y = 393.399;
					ped1B_z = 4.1372;
					SetSped1 = 1;
				}
				else if (ped1_cord == 38)
				{
					ped1B_x = 952.2457;
					ped1B_y = 464.8242;
					ped1B_z = 4.5878;
					SetSped1 = 0;
				}
				else if (ped1_cord == 39)
				{
					ped1B_x = 935.919;
					ped1B_y = 531.4876;
					ped1B_z = 5.0202;
					SetSped1 = 0;
				}
				else if (ped1_cord == 40)
				{
					ped1B_x = 916.873;
					ped1B_y = 630.5303;
					ped1B_z = 5.304;
					SetSped1 = 1;
				}
				else if (ped1_cord == 41)
				{
					ped1B_x = 863.4273;
					ped1B_y = 591.4151;
					ped1B_z = 5.1727;
					SetSped1 = 0;
				}
				else if (ped1_cord == 42)
				{
					ped1B_x = 803.545;
					ped1B_y = 542.9156;
					ped1B_z = 5.3602;
					SetSped1 = 0;
				}
				else if (ped1_cord == 43)
				{
					ped1B_x = 759.7381;
					ped1B_y = 506.7269;
					ped1B_z = 4.9985;
					SetSped1 = 0;
				}
				else if (ped1_cord == 44)
				{
					ped1B_x = 742.1655;
					ped1B_y = 423.874;
					ped1B_z = 5.2687;
					SetSped1 = 0;
				}
				else if (ped1_cord == 45)
				{
					ped1B_x = 705.4493;
					ped1B_y = 347.687;
					ped1B_z = 4.8572;
					SetSped1 = 0;
				}
				else if (ped1_cord == 46)
				{
					ped1B_x = 662.6478;
					ped1B_y = 266.739;
					ped1B_z = 5.962;
					SetSped1 = 0;
				}
				else if (ped1_cord == 47)
				{
					ped1B_x = 630.7795;
					ped1B_y = 165.945;
					ped1B_z = 4.6223;
					SetSped1 = 0;
				}
				else if (ped1_cord == 48)
				{
					ped1B_x = ped1B_x; 
					ped1B_y = ped1B_y;
					ped1B_z = ped1B_z;
					SetSped1 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 80.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}

//============================== �������� 2 ==============================
			GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//��������� ���������� ��������� � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//�������� "����� �� �����������"
			if ( Ped2R < 55.0)
			{
				if (SetSped2 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 85.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped2 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped2 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 14.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
			}
			if ( Ped2R < 10.0)
			{
				ped2_cord += 1;
				water2X = ped2B_x;
				water2Y = ped2B_y;
				water2Z = ped2B_z;
				GET_CAR_HEADING(car2, &water2R);

				if (ped2_cord == 2)
				{
					ped2B_x = 613.55;
					ped2B_y = 33.5422;
					ped2B_z = 5.0699;
					SetSped2 = 0;
				}
				else if (ped2_cord == 3)
				{
					ped2B_x = 611.174;
					ped2B_y = -62.76898;
					ped2B_z = 10.5328;
					SetSped2 = 0;
				}
				else if (ped2_cord == 4)
				{
					ped2B_x = 597.841;
					ped2B_y = -170.383;
					ped2B_z = 4.4007;
					SetSped2 = 0;
				}
				else if (ped2_cord == 5)
				{
					ped2B_x = 558.795;
					ped2B_y = -264.664;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 6)
				{
					ped2B_x = 486.418;
					ped2B_y = -330.375;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 7)
				{
					ped2B_x = 391.1846;
					ped2B_y = -339.898;
					ped2B_z = 4.2782;
					SetSped2 = 0;
				}
				else if (ped2_cord == 8)
				{
					ped2B_x = 326.336;
					ped2B_y = -364.066;
					ped2B_z = 4.2839;
					SetSped2 = 2;
				}
				else if (ped2_cord == 9)
				{
					ped2B_x = 348.3296;
					ped2B_y = -479.89;
					ped2B_z = 4.2761;
					SetSped2 = 0;
				}
				else if (ped2_cord == 10)
				{
					ped2B_x = 343.5679;
					ped2B_y = -545.683;
					ped2B_z = 4.2859;
					SetSped2 = 1;
				}
				else if (ped2_cord == 11)
				{
					ped2B_x = 262.3964;
					ped2B_y = -564.68;
					ped2B_z = 4.2781;
					SetSped2 = 0;
				}
				else if (ped2_cord == 12)
				{
					ped2B_x = 236.0393;
					ped2B_y = -593.22;
					ped2B_z = 4.2858;
					SetSped2 = 0;
				}
				else if (ped2_cord == 13)
				{
					ped2B_x = 229.1521;
					ped2B_y = -673.2099;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 14)
				{
					ped2B_x = 230.1054;
					ped2B_y = -748.4499;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 15)
				{
					ped2B_x = 244.8036;
					ped2B_y = -827.49;
					ped2B_z = 4.2858;
					SetSped2 = 0;
				}
				else if (ped2_cord == 16)
				{
					ped2B_x = 278.3767;
					ped2B_y = -921.77;
					ped2B_z = 4.2858;
					SetSped2 = 0;
				}
				else if (ped2_cord == 17)
				{
					ped2B_x = 314.3141;
					ped2B_y = -994.3708;
					ped2B_z = 4.2858;
					SetSped2 = 0;
				}
				else if (ped2_cord == 18)
				{
					ped2B_x = 371.2148;
					ped2B_y = -1041;
					ped2B_z = 4.2464;
					SetSped2 = 0;
				}
				else if (ped2_cord == 19)
				{
					ped2B_x = 422.218;
					ped2B_y = -1035.137;
					ped2B_z = 4.278;
					SetSped2 = 1;
				}
				else if (ped2_cord == 20)
				{
					ped2B_x = 433.7286;
					ped2B_y = -932.25;
					ped2B_z = 4.2779;
					SetSped2 = 0;
				}
				else if (ped2_cord == 21)
				{
					ped2B_x = 471.4977;
					ped2B_y = -848.4399;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 22)
				{
					ped2B_x = 499.7618;
					ped2B_y = -769.4;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 23)
				{
					ped2B_x = 512.1345;
					ped2B_y = -676.07;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 24)
				{
					ped2B_x = 515.2484;
					ped2B_y = -600.8399;
					ped2B_z = 4.2858;
					SetSped2 = 0;
				}
				else if (ped2_cord == 25)
				{
					ped2B_x = 510.4462;
					ped2B_y = -514.1701;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 26)
				{
					ped2B_x = 515.9403;
					ped2B_y = -423.703;
					ped2B_z = 4.2613;
					SetSped2 = 0;
				}
				else if (ped2_cord == 27)
				{
					ped2B_x = 556.4473;
					ped2B_y = -352.278;
					ped2B_z = 4.2465;
					SetSped2 = 0;
				}
				else if (ped2_cord == 28)
				{
					ped2B_x = 606.4968;
					ped2B_y = -280.853;
					ped2B_z = 4.2465;
					SetSped2 = 0;
				}
				else if (ped2_cord == 29)
				{
					ped2B_x = 647.6587;
					ped2B_y = -217.047;
					ped2B_z = 4.2465;
					SetSped2 = 0;
				}
				else if (ped2_cord == 30)
				{
					ped2B_x = 668.4004;
					ped2B_y = -152.288;
					ped2B_z = 4.2372;
					SetSped2 = 0;
				}
				else if (ped2_cord == 31)
				{
					ped2B_x = 692.9054;
					ped2B_y = -61.81598;
					ped2B_z = 3.8297;
					SetSped2 = 0;
				}
				else if (ped2_cord == 32)
				{
					ped2B_x = 734.715;
					ped2B_y = 7.70398;
					ped2B_z = 3.8297;
					SetSped2 = 0;
				}
				else if (ped2_cord == 33)
				{
					ped2B_x = 797.4172;
					ped2B_y = 84.84299;
					ped2B_z = 3.8482;
					SetSped2 = 0;
				}
				else if (ped2_cord == 34)
				{
					ped2B_x = 848.5774;
					ped2B_y = 129.603;
					ped2B_z = 3.8482;
					SetSped2 = 1;
				}
				else if (ped2_cord == 35)
				{
					ped2B_x = 885.7377;
					ped2B_y = 180.076;
					ped2B_z = 3.9641;
					SetSped2 = 1;
				}
				else if (ped2_cord == 36)
				{
					ped2B_x = 910.2094;
					ped2B_y = 289.595;
					ped2B_z = 6.3418;
					SetSped2 = 0;
				}
				else if (ped2_cord == 37)
				{
					ped2B_x = 914.9573;
					ped2B_y = 393.399;
					ped2B_z = 4.1372;
					SetSped2 = 1;
				}
				else if (ped2_cord == 38)
				{
					ped2B_x = 952.2457;
					ped2B_y = 464.8242;
					ped2B_z = 4.5878;
					SetSped2 = 0;
				}
				else if (ped2_cord == 39)
				{
					ped2B_x = 935.919;
					ped2B_y = 531.4876;
					ped2B_z = 5.0202;
					SetSped2 = 0;
				}
				else if (ped2_cord == 40)
				{
					ped2B_x = 916.873;
					ped2B_y = 630.5303;
					ped2B_z = 5.304;
					SetSped2 = 1;
				}
				else if (ped2_cord == 41)
				{
					ped2B_x = 863.4273;
					ped2B_y = 591.4151;
					ped2B_z = 5.1727;
					SetSped2 = 0;
				}
				else if (ped2_cord == 42)
				{
					ped2B_x = 803.545;
					ped2B_y = 542.9156;
					ped2B_z = 5.3602;
					SetSped2 = 0;
				}
				else if (ped2_cord == 43)
				{
					ped2B_x = 759.7381;
					ped2B_y = 506.7269;
					ped2B_z = 4.9985;
					SetSped2 = 0;
				}
				else if (ped2_cord == 44)
				{
					ped2B_x = 742.1655;
					ped2B_y = 423.874;
					ped2B_z = 5.2687;
					SetSped2 = 0;
				}
				else if (ped2_cord == 45)
				{
					ped2B_x = 705.4493;
					ped2B_y = 347.687;
					ped2B_z = 4.8572;
					SetSped2 = 0;
				}
				else if (ped2_cord == 46)
				{
					ped2B_x = 662.6478;
					ped2B_y = 266.739;
					ped2B_z = 5.962;
					SetSped2 = 0;
				}
				else if (ped2_cord == 47)
				{
					ped2B_x = 630.7795;
					ped2B_y = 165.945;
					ped2B_z = 4.6223;
					SetSped2 = 0;
				}
				else if (ped2_cord == 48)
				{
					ped2B_x = ped2B_x; 
					ped2B_y = ped2B_y;
					ped2B_z = ped2B_z;
					SetSped2 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 80.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}

//============================== �������� 3 ==============================
			GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//��������� ���������� ��������� � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//�������� "����� �� �����������"
			if ( Ped3R < 55.0)
			{
				if (SetSped3 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 85.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped3 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped3 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 14.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
			}
			if ( Ped3R < 10.0)
			{
				ped3_cord += 1;
				water3X = ped3B_x;
				water3Y = ped3B_y;
				water3Z = ped3B_z;
				GET_CAR_HEADING(car3, &water3R);

				if (ped3_cord == 2)
				{
					ped3B_x = 613.55;
					ped3B_y = 33.5422;
					ped3B_z = 5.0699;
					SetSped3 = 0;
				}
				else if (ped3_cord == 3)
				{
					ped3B_x = 611.174;
					ped3B_y = -62.76898;
					ped3B_z = 10.5328;
					SetSped3 = 0;
				}
				else if (ped3_cord == 4)
				{
					ped3B_x = 597.841;
					ped3B_y = -170.383;
					ped3B_z = 4.4007;
					SetSped3 = 0;
				}
				else if (ped3_cord == 5)
				{
					ped3B_x = 558.795;
					ped3B_y = -264.664;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 6)
				{
					ped3B_x = 486.418;
					ped3B_y = -330.375;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 7)
				{
					ped3B_x = 391.1846;
					ped3B_y = -339.898;
					ped3B_z = 4.2782;
					SetSped3 = 0;
				}
				else if (ped3_cord == 8)
				{
					ped3B_x = 326.336;
					ped3B_y = -364.066;
					ped3B_z = 4.2839;
					SetSped3 = 2;
				}
				else if (ped3_cord == 9)
				{
					ped3B_x = 348.3296;
					ped3B_y = -479.89;
					ped3B_z = 4.2761;
					SetSped3 = 0;
				}
				else if (ped3_cord == 10)
				{
					ped3B_x = 343.5679;
					ped3B_y = -545.683;
					ped3B_z = 4.2859;
					SetSped3 = 1;
				}
				else if (ped3_cord == 11)
				{
					ped3B_x = 262.3964;
					ped3B_y = -564.68;
					ped3B_z = 4.2781;
					SetSped3 = 0;
				}
				else if (ped3_cord == 12)
				{
					ped3B_x = 236.0393;
					ped3B_y = -593.22;
					ped3B_z = 4.2858;
					SetSped3 = 0;
				}
				else if (ped3_cord == 13)
				{
					ped3B_x = 229.1521;
					ped3B_y = -673.2099;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 14)
				{
					ped3B_x = 230.1054;
					ped3B_y = -748.4499;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 15)
				{
					ped3B_x = 244.8036;
					ped3B_y = -827.49;
					ped3B_z = 4.2858;
					SetSped3 = 0;
				}
				else if (ped3_cord == 16)
				{
					ped3B_x = 278.3767;
					ped3B_y = -921.77;
					ped3B_z = 4.2858;
					SetSped3 = 0;
				}
				else if (ped3_cord == 17)
				{
					ped3B_x = 314.3141;
					ped3B_y = -994.3708;
					ped3B_z = 4.2858;
					SetSped3 = 0;
				}
				else if (ped3_cord == 18)
				{
					ped3B_x = 371.2148;
					ped3B_y = -1041;
					ped3B_z = 4.2464;
					SetSped3 = 0;
				}
				else if (ped3_cord == 19)
				{
					ped3B_x = 422.218;
					ped3B_y = -1035.137;
					ped3B_z = 4.278;
					SetSped3 = 1;
				}
				else if (ped3_cord == 20)
				{
					ped3B_x = 433.7286;
					ped3B_y = -932.25;
					ped3B_z = 4.2779;
					SetSped3 = 0;
				}
				else if (ped3_cord == 21)
				{
					ped3B_x = 471.4977;
					ped3B_y = -848.4399;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 22)
				{
					ped3B_x = 499.7618;
					ped3B_y = -769.4;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 23)
				{
					ped3B_x = 512.1345;
					ped3B_y = -676.07;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 24)
				{
					ped3B_x = 515.2484;
					ped3B_y = -600.8399;
					ped3B_z = 4.2858;
					SetSped3 = 0;
				}
				else if (ped3_cord == 25)
				{
					ped3B_x = 510.4462;
					ped3B_y = -514.1701;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 26)
				{
					ped3B_x = 515.9403;
					ped3B_y = -423.703;
					ped3B_z = 4.2613;
					SetSped3 = 0;
				}
				else if (ped3_cord == 27)
				{
					ped3B_x = 556.4473;
					ped3B_y = -352.278;
					ped3B_z = 4.2465;
					SetSped3 = 0;
				}
				else if (ped3_cord == 28)
				{
					ped3B_x = 606.4968;
					ped3B_y = -280.853;
					ped3B_z = 4.2465;
					SetSped3 = 0;
				}
				else if (ped3_cord == 29)
				{
					ped3B_x = 647.6587;
					ped3B_y = -217.047;
					ped3B_z = 4.2465;
					SetSped3 = 0;
				}
				else if (ped3_cord == 30)
				{
					ped3B_x = 668.4004;
					ped3B_y = -152.288;
					ped3B_z = 4.2372;
					SetSped3 = 0;
				}
				else if (ped3_cord == 31)
				{
					ped3B_x = 692.9054;
					ped3B_y = -61.81598;
					ped3B_z = 3.8297;
					SetSped3 = 0;
				}
				else if (ped3_cord == 32)
				{
					ped3B_x = 734.715;
					ped3B_y = 7.70398;
					ped3B_z = 3.8297;
					SetSped3 = 0;
				}
				else if (ped3_cord == 33)
				{
					ped3B_x = 797.4172;
					ped3B_y = 84.84299;
					ped3B_z = 3.8482;
					SetSped3 = 0;
				}
				else if (ped3_cord == 34)
				{
					ped3B_x = 848.5774;
					ped3B_y = 129.603;
					ped3B_z = 3.8482;
					SetSped3 = 1;
				}
				else if (ped3_cord == 35)
				{
					ped3B_x = 885.7377;
					ped3B_y = 180.076;
					ped3B_z = 3.9641;
					SetSped3 = 1;
				}
				else if (ped3_cord == 36)
				{
					ped3B_x = 910.2094;
					ped3B_y = 289.595;
					ped3B_z = 6.3418;
					SetSped3 = 0;
				}
				else if (ped3_cord == 37)
				{
					ped3B_x = 914.9573;
					ped3B_y = 393.399;
					ped3B_z = 4.1372;
					SetSped3 = 1;
				}
				else if (ped3_cord == 38)
				{
					ped3B_x = 952.2457;
					ped3B_y = 464.8242;
					ped3B_z = 4.5878;
					SetSped3 = 0;
				}
				else if (ped3_cord == 39)
				{
					ped3B_x = 935.919;
					ped3B_y = 531.4876;
					ped3B_z = 5.0202;
					SetSped3 = 0;
				}
				else if (ped3_cord == 40)
				{
					ped3B_x = 916.873;
					ped3B_y = 630.5303;
					ped3B_z = 5.304;
					SetSped3 = 1;
				}
				else if (ped3_cord == 41)
				{
					ped3B_x = 863.4273;
					ped3B_y = 591.4151;
					ped3B_z = 5.1727;
					SetSped3 = 0;
				}
				else if (ped3_cord == 42)
				{
					ped3B_x = 803.545;
					ped3B_y = 542.9156;
					ped3B_z = 5.3602;
					SetSped3 = 0;
				}
				else if (ped3_cord == 43)
				{
					ped3B_x = 759.7381;
					ped3B_y = 506.7269;
					ped3B_z = 4.9985;
					SetSped3 = 0;
				}
				else if (ped3_cord == 44)
				{
					ped3B_x = 742.1655;
					ped3B_y = 423.874;
					ped3B_z = 5.2687;
					SetSped3 = 0;
				}
				else if (ped3_cord == 45)
				{
					ped3B_x = 705.4493;
					ped3B_y = 347.687;
					ped3B_z = 4.8572;
					SetSped3 = 0;
				}
				else if (ped3_cord == 46)
				{
					ped3B_x = 662.6478;
					ped3B_y = 266.739;
					ped3B_z = 5.962;
					SetSped3 = 0;
				}
				else if (ped3_cord == 47)
				{
					ped3B_x = 630.7795;
					ped3B_y = 165.945;
					ped3B_z = 4.6223;
					SetSped3 = 0;
				}
				else if (ped3_cord == 48)
				{
					ped3B_x = ped3B_x; 
					ped3B_y = ped3B_y;
					ped3B_z = ped3B_z;
					SetSped3 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 80.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			
			//�������� �������� ���������
			GET_CHAR_HEALTH(ped4, &Ped_hp4);
			GET_CHAR_HEALTH(ped5, &Ped_hp5);
			GET_CHAR_HEALTH(ped6, &Ped_hp6);
			GET_CHAR_HEALTH(ped7, &Ped_hp7);
			GET_CHAR_HEALTH(ped8, &Ped_hp8);
			GET_CHAR_HEALTH(ped9, &Ped_hp9);
			GET_CHAR_HEALTH(ped10, &Ped_hp10);
			GET_CHAR_HEALTH(ped11, &Ped_hp11);

			if (( Ped_hp4 < 195 ) || ( Ped_hp5 < 195 ) || ( Ped_hp6 < 195 ) || ( Ped_hp7 < 195 ) || ( Ped_hp8 < 195 ) || ( Ped_hp9 < 195 ) || ( Ped_hp10 < 195 ) || ( Ped_hp11 < 195 ))
			{
				PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT9", 3500, 1);//������� �� ����� ��������� "������� �� ����� ���������. ����� ��������"
				PANIC_SCREAM(ped4);
				PANIC_SCREAM(ped5);
				PANIC_SCREAM(ped6);
				PANIC_SCREAM(ped7);
				PANIC_SCREAM(ped8);
				PANIC_SCREAM(ped9);
				PANIC_SCREAM(ped10);
				PANIC_SCREAM(ped11);
				skip = 1;
				break;
			}
			else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//���� ����� ���� ��� ����������
			{
				skip = 1;
				break;
			}
			position();

			// HUD ������� ������ 
			DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );

			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.73564852, "NE_RACE5"); //POSITION:

			SET_TEXT_COLOUR(95, 195, 247, 255);
			SET_TEXT_SCALE(0.312, 0.534);
			SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
			DISPLAY_TEXT_WITH_NUMBER(0.920052, 0.725462962, "CP_TIME_NOZERO", poziteon);

			setup_draw_text();
			if (poziteon == 1)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "ST");
			}
			else if (poziteon == 2)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "ND");
			}
			else if (poziteon == 3)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "RD");
			}
			else if (poziteon == 4)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "TH");
			}

			// HUD ������
			if (TIMERA() > 999)
			{
				time_s += 1;
				SETTIMERA( 0 );
			}
			if (time_s > 59)
			{
				time_m += 1;
				time_s = 0;
			}

			DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// ������ ������� ��������.

			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// ������

			setup_draw_value();
			DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if ( time_s > 9 )
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", time_s);// �������
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", time_s);// �������
			}

			/*/================ ����� MW ================
			if ( best_time_s == cop_on )
			{
				GENERATE_RANDOM_INT_IN_RANGE( 1, 6, &cop_on);
				if (cop_on < 3)
				{
					cop_on = 95;
				}
				else
				{
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					cop_on = 85;
				}
			}
			if ((IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)) && (cop_on == 85)) //�������� �������.
			{
				cop_on = 90;
				ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
				APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
				if (IS_CHAR_IN_ZONE(GetPlayerPed(), "FRANI"))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPBAD1")));
					PRELOAD_STREAM("CUTSCENES_RPBAD1");  // ��� ������� �� sounds.dat15, ����� ����� ��������� ������ �� �����
					//Airport
				}
				else if ((IS_CHAR_IN_ZONE(GetPlayerPed(), "PORTU")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "BRALG")))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPED1")));
					PRELOAD_STREAM("CUTSCENES_RPED1");  // ��� ������� �� sounds.dat15, ����� ����� ��������� ������ �� �����
					//PORT
				}
				else if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO"))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPED2")));
					PRELOAD_STREAM("CUTSCENES_RPED2");  // ��� ������� �� sounds.dat15, ����� ����� ��������� ������ �� �����
					//HAVANA
				}
				else if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI"))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPEXG1")));
					PRELOAD_STREAM("CUTSCENES_RPEXG1");  // ��� ������� �� sounds.dat15, ����� ����� ��������� ������ �� �����
					//HAITI
				}
				//=================== ��������� ���� ��� ===================
				else
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPBRI1")));
					PRELOAD_STREAM("CUTSCENES_RPBRI1");  // ��� ������� �� sounds.dat15, ����� ����� ��������� ������ �� �����
					//������ ����
				}
				DISABLE_FRONTEND_RADIO();
				PLAY_STREAM_FRONTEND();
				SETTIMERC(0);
			}
			if (cop_on == 90)
			{
				radio = TIMERC();
				if (radio > 10000)
				{
					//radio_off
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
					cop_on = 95;
				}
			}
			if (cop_on == 95)
			{
				if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)) //�������� �������.
				{
					cop_on = 95;
				}
				else
				{
					cop_on = 85;
				}
			}
			//================ ����� MW ================*/
			//==================== ����� ���������� ���������� ====================
			if (!IS_CHAR_SITTING_IN_ANY_CAR( ped1 ))
			{
				SETTIMERB(0);
				GET_CAR_COORDINATES(car1, &Ped1X, &Ped1Y, &Ped1Z);
				SET_CAR_COORDINATES(car1, Ped1X, Ped1Y, Ped1Z+1);
				GET_CAR_HEADING(car1, &Ped1R);
				SET_CAR_HEADING(car1, Ped1R);//������ �������� ������
				FIX_CAR(car1);
				WARP_CHAR_INTO_CAR(ped1, car1);
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			if (!IS_CHAR_SITTING_IN_ANY_CAR( ped2 ))
			{
				SETTIMERB(0);
				GET_CAR_COORDINATES(car2, &Ped2X, &Ped2Y, &Ped2Z);
				SET_CAR_COORDINATES(car2, Ped2X, Ped2Y, Ped2Z+1);
				GET_CAR_HEADING(car2, &Ped2R);
				SET_CAR_HEADING(car2, Ped2R);//������ �������� ������
				FIX_CAR(car2);
				WARP_CHAR_INTO_CAR(ped2, car2);
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			if (!IS_CHAR_SITTING_IN_ANY_CAR( ped3 ))
			{
				SETTIMERB(0);
				GET_CAR_COORDINATES(car3, &Ped3X, &Ped3Y, &Ped3Z);
				SET_CAR_COORDINATES(car3, Ped3X, Ped3Y, Ped3Z+1);
				GET_CAR_HEADING(car3, &Ped3R);
				SET_CAR_HEADING(car3, Ped3R);//������ �������� ������
				FIX_CAR(car3);
				WARP_CHAR_INTO_CAR(ped3, car3);
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			//==================== ����� ���������-�������� ====================
			if (IS_CAR_IN_WATER(car1))
			{
				SETTIMERB(0);
				FIX_CAR(car1);
				SET_CAR_COORDINATES(car1, water1X, water1Y, water1Z);
				SET_CAR_HEADING(car1, water1R);//������ �������� ������
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			if (IS_CAR_IN_WATER(car2))
			{
				SETTIMERB(0);
				FIX_CAR(car2);
				SET_CAR_COORDINATES(car2, water2X, water2Y, water2Z);
				SET_CAR_HEADING(car2, water2R);//������ �������� ������
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			if (IS_CAR_IN_WATER(car3))
			{
				SETTIMERB(0);
				FIX_CAR(car3);
				SET_CAR_COORDINATES(car3, water3X, water3Y, water3Z);
				SET_CAR_HEADING(car3, water3R);//������ �������� ������
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}
			//==================== ����� ��������� � ����� ====================
			GET_CHAR_SPEED(ped1, &sped_wall1);
			GET_CHAR_SPEED(ped2, &sped_wall2);
			GET_CHAR_SPEED(ped3, &sped_wall3);
			if (sped_wall1 < 2)
			{
				time_wall = TIMERB();
				if (time_wall > 5000)
				{
					FIX_CAR(car1);
					SET_CAR_COORDINATES(car1, water1X, water1Y, water1Z);
					SET_CAR_HEADING(car1, water1R);//������ �������� ������
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
					SETTIMERB(0);
				}
			}
			if (sped_wall2 < 2)
			{
				time_wall = TIMERB();
				if (time_wall > 5000)
				{
					FIX_CAR(car2);
					SET_CAR_COORDINATES(car2, water2X, water2Y, water2Z);
					SET_CAR_HEADING(car2, water2R);//������ �������� ������
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
					SETTIMERB(0);
				}
			}
			if (sped_wall3 < 2)
			{
				time_wall = TIMERB();
				if (time_wall > 5000)
				{
					FIX_CAR(car3);
					SET_CAR_COORDINATES(car3, water3X, water3Y, water3Z);
					SET_CAR_HEADING(car3, water3R);//������ �������� ������
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
					SETTIMERB(0);
				}
			}
			if ((sped_wall1 > 2) && (sped_wall2 > 2) && (sped_wall3 > 2))
			{
				SETTIMERB(0);
			}



		}
	}
	// ������ ������ ���
	WAIT(100);
	SET_CAR_DENSITY_MULTIPLIER(1);// ��������� ����
	SWITCH_ROADS_BACK_TO_ORIGINAL( 715.988, 109.372, -1.286, 602.218, 333.631, 80.0 );//  ���������� �������
	REMOVE_BLIP(Blip_r);//������� ������ �� ������
	REMOVE_BLIP(Blip_r2);//������� ������ �� ������
	REMOVE_BLIP(Blip_c1);//������� ������ �� ������
	REMOVE_BLIP(Blip_c2);//������� ������ �� ������
	REMOVE_BLIP(Blip_c3);//������� ������ �� ������
	DELETE_CHECKPOINT(checkpoint);

	// ��������� �� ������ ������
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//��������� ������ ������
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//��������� ������ ������
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//��������� ������ ������
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//��������� ������ ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//��������� ������ ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//��������� ������ ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//��������� ������ ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//��������� ������ ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//��������� ������ ����
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//��������� ������ ����

	// ��������� �� ������ �����
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//��������� ������ ����(� ����������� ��� ��������)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//��������� ������ ����(� ����������� ��� ��������)

	// ��������� �� ������ ���������
	MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//��������� ������ ������(� ����������� ������ ��������)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//��������� ������ ������(� ����������� ������ ��������)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//��������� ������ ������(� ����������� ������ ��������)

	RELEASE_TEXTURE( fon );
	RELEASE_TEXTURE( timer );
	REMOVE_TXD( textur );

	if (skip == 1)
	{
		SETTIMERA(0); //���������� ������ 
		while (true)
		{
			SET_TEXT_COLOUR(255, 159, 255, 255); // ����� ���� ������
			SET_TEXT_SCALE(0.5, 0.6); // ������� ������
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
			SET_TEXT_CENTRE(1); // ����� ����� ������
			DISPLAY_TEXT(0.5, 0.45, "MISSION_FAILED");// ����� "������ ���������"

			WAIT( 0 );
			if ( TIMERA() > 3000 )
			{
				break;
			}
		}
	}
	else if (skip == 2)
	{
		SETTIMERA(0); //���������� ������ 
		TRIGGER_MISSION_COMPLETE_AUDIO(1);//����������� ������ �������� "(1)" ������������� ���� �� "...\EFLC\pc\audio\Sfx\gps.rpf\GPS\MISSION_COMPLETE_1" (����� "6" = "SMC6" � ���-�� ������)
		while (true)
		{
			SET_TEXT_COLOUR(255, 159, 255, 255); // ����� ���� ������
			SET_TEXT_SCALE(0.5, 0.7); // ������� ������
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
			SET_TEXT_CENTRE(1); // ����� ����� ������
			DISPLAY_TEXT(0.5, 0.45, "MISSION_PASSED");// ����� "������ ���������"

			SET_TEXT_COLOUR(255, 159, 255, 255); // ����� ���� ������
			SET_TEXT_SCALE(0.5, 0.7); // ������� ������
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // ����� ���� ������
			SET_TEXT_CENTRE(1); // ����� ����� ������
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 8000);// +5000$
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
		ADD_SCORE( GetPlayerIndex(), +8000 );//��� ������ �����
		G_SA_RACE += 1;
	}
}
void main(void)
{
	WAIT(500);
	sa_race();
	TERMINATE_THIS_SCRIPT();
}
