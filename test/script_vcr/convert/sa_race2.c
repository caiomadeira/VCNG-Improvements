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

	startX = -150.325;
	startY = 1273.97;
	startZ = 5.35834;
	startH = 268.0;

	Blip_x = -70.7919;
	Blip_y = 1266.26;
	Blip_z = 4.67568;
	Blip_x2 = -42.5209;
	Blip_y2 = 1334.89;
	Blip_z2 = 4.59932;
	play_cord = 1;

	ped1B_x = -70.7919;
	ped1B_y = 1266.26;
	ped1B_z = 4.67568;
	SetSped1 = 1;
	ped1_cord = 1;

	ped2B_x = -70.7919;
	ped2B_y = 1266.26;
	ped2B_z = 4.67568;
	SetSped2 = 1;
	ped2_cord = 1;

	ped3B_x = -70.7919;
	ped3B_y = 1266.26;
	ped3B_z = 4.67568;
	SetSped3 = 1;
	ped3_cord = 1;

	SWITCH_ROADS_OFF( -80.075, 1252.765, -1.286, -230.417, 1300.289, 80.0 );// ��������� ���� �������
	//SET_CAR_DENSITY_MULTIPLIER(0.6);// ��������� ����

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
				//SET_CAR_DENSITY_MULTIPLIER(0.5);// ��������� ����
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

				GET_CAR_COORDINATES(car1, &water1X, &water1Y, &water1Z);
				GET_CAR_COORDINATES(car2, &water2X, &water2Y, &water2Z);
				GET_CAR_COORDINATES(car3, &water3X, &water3Y, &water3Z);
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
					Blip_x2 = -19.78284;
					Blip_y2 = 1389.146;
					Blip_z2 = 4.778739;
				}
				else if (play_cord == 3)
				{
					Blip_x2 = 35.92639;
					Blip_y2 = 1523.321;
					Blip_z2 = 4.778739;
				}
				else if (play_cord == 4)
				{
					Blip_x2 = 93.50073;
					Blip_y2 = 1659.259;
					Blip_z2 = 2.876405;
				}
				else if (play_cord == 5)
				{
					Blip_x2 = 124.7225;
					Blip_y2 = 1736.282;
					Blip_z2 = 4.817236;
				}
				else if (play_cord == 6)
				{
					Blip_x2 = 134.3364;
					Blip_y2 = 1818.371;
					Blip_z2 = 5.39;
				}
				else if (play_cord == 7)
				{
					Blip_x2 = 112.2135;
					Blip_y2 = 1872.981;
					Blip_z2 = 5.39;
				}
				else if (play_cord == 8)
				{
					Blip_x2 = -54.23401;
					Blip_y2 = 1873.135;
					Blip_z2 = 5.39;
				}
				else if (play_cord == 9)
				{
					Blip_x2 = -172.6847;
					Blip_y2 = 1862.062;
					Blip_z2 = 5.39;
				}
				else if (play_cord == 10)
				{
					Blip_x2 = -302.6159;
					Blip_y2 = 1849.694;
					Blip_z2 = 5.39;
				}
				else if (play_cord == 11)
				{
					Blip_x2 = -342.9068;
					Blip_y2 = 1914.552;
					Blip_z2 = 5.66;
				}
				else if (play_cord == 12)
				{
					Blip_x2 = -246.1882;
					Blip_y2 = 1926.108;
					Blip_z2 = 5.66;
				}
				else if (play_cord == 13)
				{
					Blip_x2 = -247.1527;
					Blip_y2 = 1998.886;
					Blip_z2 = 5.72;
				}
				else if (play_cord == 14)
				{
					Blip_x2 = -351.0479;
					Blip_y2 = 2010.804;
					Blip_z2 = 5.54;
				}
				else if (play_cord == 15)
				{
					Blip_x2 = -449.4703;
					Blip_y2 = 1974.777;
					Blip_z2 = 5.54;
				}
				else if (play_cord == 16)
				{
					Blip_x2 = -437.7158;
					Blip_y2 = 1861.706;
					Blip_z2 = 5.09;
				}
				else if (play_cord == 17)
				{
					Blip_x2 = -426.4738;
					Blip_y2 = 1686;
					Blip_z2 = 4.642499;
				}
				else if (play_cord == 18)
				{
					Blip_x2 = -434.7247;
					Blip_y2 = 1574.24;
					Blip_z2 = 4.642499;
				}
				else if (play_cord == 19)
				{
					Blip_x2 = -437.9045;
					Blip_y2 = 1440.219;
					Blip_z2 = 4.7;
				}
				else if (play_cord == 20)
				{
					Blip_x2 = -439.3021;
					Blip_y2 = 1318.542;
					Blip_z2 = 4.7;
				}
				else if (play_cord == 21)
				{
					Blip_x2 = -394.438;
					Blip_y2 = 1291.611;
					Blip_z2 = 4.7;
				}
				else if (play_cord == 22)
				{
					Blip_x2 = -292.9197;
					Blip_y2 = 1284.224;
					Blip_z2 = 4.72;
				}
				else if (play_cord == 23)
				{
					Blip_x2 = -210.1509;
					Blip_y2 = 1280.655;
					Blip_z2 = 5.291577;
				}
				else if (play_cord == 24)
				{
					Blip_x2 = -155.6523;
					Blip_y2 = 1277.019;
					Blip_z2 = 5.279013;
				}
				else if (play_cord == 25)
				{
					Blip_x2 = Blip_x2; 
					Blip_y2 = Blip_y2;
					Blip_z2 = Blip_z2;
				}
				else if (play_cord == 26)
				{
					skip = 2;
					break;
				}
				if (play_cord < 25)
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
					if (play_cord < 24)
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
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 65.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped1 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped1 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 12.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
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
					ped1B_x = -42.52092;
					ped1B_y = 1334.892;
					ped1B_z = 4.599316;
					SetSped1 = 0;
				}
				else if (ped1_cord == 3)
				{
					ped1B_x = -19.78284;
					ped1B_y = 1389.146;
					ped1B_z = 4.778739;
					SetSped1 = 0;
				}
				else if (ped1_cord == 4)
				{
					ped1B_x = 35.92639;
					ped1B_y = 1523.321;
					ped1B_z = 4.778739;
					SetSped1 = 0;
				}
				else if (ped1_cord == 5)
				{
					ped1B_x = 93.50073;
					ped1B_y = 1659.259;
					ped1B_z = 2.876405;
					SetSped1 = 0;
				}
				else if (ped1_cord == 6)
				{
					ped1B_x = 124.7225;
					ped1B_y = 1736.282;
					ped1B_z = 4.817236;
					SetSped1 = 0;
				}
				else if (ped1_cord == 7)
				{
					ped1B_x = 134.3364;
					ped1B_y = 1818.371;
					ped1B_z = 5.39;
					SetSped1 = 1;
				}
				else if (ped1_cord == 8)
				{
					ped1B_x = 112.2135;
					ped1B_y = 1872.981;
					ped1B_z = 5.39;
					SetSped1 = 1;
				}
				else if (ped1_cord == 9)
				{
					ped1B_x = -54.23401;
					ped1B_y = 1873.135;
					ped1B_z = 5.39;
					SetSped1 = 0;
				}
				else if (ped1_cord == 10)
				{
					ped1B_x = -172.6847;
					ped1B_y = 1862.062;
					ped1B_z = 5.39;
					SetSped1 = 0;
				}
				else if (ped1_cord == 11)
				{
					ped1B_x = -302.6159;
					ped1B_y = 1849.694;
					ped1B_z = 5.39;
					SetSped1 = 1;
				}
				else if (ped1_cord == 12)
				{
					ped1B_x = -342.9068;
					ped1B_y = 1914.552;
					ped1B_z = 5.66;
					SetSped1 = 0;
				}
				else if (ped1_cord == 13)
				{
					ped1B_x = -246.1882;
					ped1B_y = 1926.108;
					ped1B_z = 5.66;
					SetSped1 = 1;
				}
				else if (ped1_cord == 14)
				{
					ped1B_x = -247.1527;
					ped1B_y = 1998.886;
					ped1B_z = 5.72;
					SetSped1 = 0;
				}
				else if (ped1_cord == 15)
				{
					ped1B_x = -351.0479;
					ped1B_y = 2010.804;
					ped1B_z = 5.54;
					SetSped1 = 0;
				}
				else if (ped1_cord == 16)
				{
					ped1B_x = -449.4703;
					ped1B_y = 1974.777;
					ped1B_z = 5.54;
					SetSped1 = 1;
				}
				else if (ped1_cord == 17)
				{
					ped1B_x = -437.7158;
					ped1B_y = 1861.706;
					ped1B_z = 5.09;
					SetSped1 = 0;
				}
				else if (ped1_cord == 18)
				{
					ped1B_x = -426.4738;
					ped1B_y = 1686;
					ped1B_z = 4.642499;
					SetSped1 = 0;
				}
				else if (ped1_cord == 19)
				{
					ped1B_x = -434.7247;
					ped1B_y = 1574.24;
					ped1B_z = 4.642499;
					SetSped1 = 0;
				}
				else if (ped1_cord == 20)
				{
					ped1B_x = -437.9045;
					ped1B_y = 1440.219;
					ped1B_z = 4.7;
					SetSped1 = 0;
				}
				else if (ped1_cord == 21)
				{
					ped1B_x = -439.3021;
					ped1B_y = 1318.542;
					ped1B_z = 4.7;
					SetSped1 = 1;
				}
				else if (ped1_cord == 22)
				{
					ped1B_x = -394.438;
					ped1B_y = 1291.611;
					ped1B_z = 4.7;
					SetSped1 = 0;
				}
				else if (ped1_cord == 23)
				{
					ped1B_x = -292.9197;
					ped1B_y = 1284.224;
					ped1B_z = 4.72;
					SetSped1 = 0;
				}
				else if (ped1_cord == 24)
				{
					ped1B_x = -210.1509;
					ped1B_y = 1280.655;
					ped1B_z = 5.291577;
					SetSped1 = 0;
				}
				else if (ped1_cord == 25)
				{
					ped1B_x = -155.6523;
					ped1B_y = 1277.019;
					ped1B_z = 5.279013;
					SetSped1 = 0;
				}
				else if (ped1_cord == 26)
				{
					ped1B_x = ped1B_x; 
					ped1B_y = ped1B_y;
					ped1B_z = ped1B_z;
					SetSped1 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 60.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}

//============================== �������� 2 ==============================
			GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//��������� ���������� ��������� � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//�������� "����� �� �����������"
			if ( Ped2R < 55.0)
			{
				if (SetSped2 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 65.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped2 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped2 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 12.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
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
					ped2B_x = -42.52092;
					ped2B_y = 1334.892;
					ped2B_z = 4.599316;
					SetSped2 = 0;
				}
				else if (ped2_cord == 3)
				{
					ped2B_x = -19.78284;
					ped2B_y = 1389.146;
					ped2B_z = 4.778739;
					SetSped2 = 0;
				}
				else if (ped2_cord == 4)
				{
					ped2B_x = 35.92639;
					ped2B_y = 1523.321;
					ped2B_z = 4.778739;
					SetSped2 = 0;
				}
				else if (ped2_cord == 5)
				{
					ped2B_x = 93.50073;
					ped2B_y = 1659.259;
					ped2B_z = 2.876405;
					SetSped2 = 0;
				}
				else if (ped2_cord == 6)
				{
					ped2B_x = 124.7225;
					ped2B_y = 1736.282;
					ped2B_z = 4.817236;
					SetSped2 = 0;
				}
				else if (ped2_cord == 7)
				{
					ped2B_x = 134.3364;
					ped2B_y = 1818.371;
					ped2B_z = 5.39;
					SetSped2 = 1;
				}
				else if (ped2_cord == 8)
				{
					ped2B_x = 112.2135;
					ped2B_y = 1872.981;
					ped2B_z = 5.39;
					SetSped2 = 1;
				}
				else if (ped2_cord == 9)
				{
					ped2B_x = -54.23401;
					ped2B_y = 1873.135;
					ped2B_z = 5.39;
					SetSped2 = 0;
				}
				else if (ped2_cord == 10)
				{
					ped2B_x = -172.6847;
					ped2B_y = 1862.062;
					ped2B_z = 5.39;
					SetSped2 = 0;
				}
				else if (ped2_cord == 11)
				{
					ped2B_x = -302.6159;
					ped2B_y = 1849.694;
					ped2B_z = 5.39;
					SetSped2 = 1;
				}
				else if (ped2_cord == 12)
				{
					ped2B_x = -342.9068;
					ped2B_y = 1914.552;
					ped2B_z = 5.66;
					SetSped2 = 0;
				}
				else if (ped2_cord == 13)
				{
					ped2B_x = -246.1882;
					ped2B_y = 1926.108;
					ped2B_z = 5.66;
					SetSped2 = 1;
				}
				else if (ped2_cord == 14)
				{
					ped2B_x = -247.1527;
					ped2B_y = 1998.886;
					ped2B_z = 5.72;
					SetSped2 = 0;
				}
				else if (ped2_cord == 15)
				{
					ped2B_x = -351.0479;
					ped2B_y = 2010.804;
					ped2B_z = 5.54;
					SetSped2 = 0;
				}
				else if (ped2_cord == 16)
				{
					ped2B_x = -449.4703;
					ped2B_y = 1974.777;
					ped2B_z = 5.54;
					SetSped2 = 1;
				}
				else if (ped2_cord == 17)
				{
					ped2B_x = -437.7158;
					ped2B_y = 1861.706;
					ped2B_z = 5.09;
					SetSped2 = 0;
				}
				else if (ped2_cord == 18)
				{
					ped2B_x = -426.4738;
					ped2B_y = 1686;
					ped2B_z = 4.642499;
					SetSped2 = 0;
				}
				else if (ped2_cord == 19)
				{
					ped2B_x = -434.7247;
					ped2B_y = 1574.24;
					ped2B_z = 4.642499;
					SetSped2 = 0;
				}
				else if (ped2_cord == 20)
				{
					ped2B_x = -437.9045;
					ped2B_y = 1440.219;
					ped2B_z = 4.7;
					SetSped2 = 0;
				}
				else if (ped2_cord == 21)
				{
					ped2B_x = -439.3021;
					ped2B_y = 1318.542;
					ped2B_z = 4.7;
					SetSped2 = 1;
				}
				else if (ped2_cord == 22)
				{
					ped2B_x = -394.438;
					ped2B_y = 1291.611;
					ped2B_z = 4.7;
					SetSped2 = 0;
				}
				else if (ped2_cord == 23)
				{
					ped2B_x = -292.9197;
					ped2B_y = 1284.224;
					ped2B_z = 4.72;
					SetSped2 = 0;
				}
				else if (ped2_cord == 24)
				{
					ped2B_x = -210.1509;
					ped2B_y = 1280.655;
					ped2B_z = 5.291577;
					SetSped2 = 0;
				}
				else if (ped2_cord == 25)
				{
					ped2B_x = -155.6523;
					ped2B_y = 1277.019;
					ped2B_z = 5.279013;
					SetSped2 = 0;
				}
				else if (ped2_cord == 26)
				{
					ped2B_x = ped2B_x; 
					ped2B_y = ped2B_y;
					ped2B_z = ped2B_z;
					SetSped2 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 60.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
			}

//============================== �������� 3 ==============================
			GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//��������� ���������� ��������� � ����������
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//�������� "����� �� �����������"
			if ( Ped3R < 55.0)
			{
				if (SetSped3 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 65.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped3 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 20.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
				}
				if (SetSped3 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 12.5, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
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
					ped3B_x = -42.52092;
					ped3B_y = 1334.892;
					ped3B_z = 4.599316;
					SetSped3 = 0;
				}
				else if (ped3_cord == 3)
				{
					ped3B_x = -19.78284;
					ped3B_y = 1389.146;
					ped3B_z = 4.778739;
					SetSped3 = 0;
				}
				else if (ped3_cord == 4)
				{
					ped3B_x = 35.92639;
					ped3B_y = 1523.321;
					ped3B_z = 4.778739;
					SetSped3 = 0;
				}
				else if (ped3_cord == 5)
				{
					ped3B_x = 93.50073;
					ped3B_y = 1659.259;
					ped3B_z = 2.876405;
					SetSped3 = 0;
				}
				else if (ped3_cord == 6)
				{
					ped3B_x = 124.7225;
					ped3B_y = 1736.282;
					ped3B_z = 4.817236;
					SetSped3 = 0;
				}
				else if (ped3_cord == 7)
				{
					ped3B_x = 134.3364;
					ped3B_y = 1818.371;
					ped3B_z = 5.39;
					SetSped3 = 1;
				}
				else if (ped3_cord == 8)
				{
					ped3B_x = 112.2135;
					ped3B_y = 1872.981;
					ped3B_z = 5.39;
					SetSped3 = 1;
				}
				else if (ped3_cord == 9)
				{
					ped3B_x = -54.23401;
					ped3B_y = 1873.135;
					ped3B_z = 5.39;
					SetSped3 = 0;
				}
				else if (ped3_cord == 10)
				{
					ped3B_x = -172.6847;
					ped3B_y = 1862.062;
					ped3B_z = 5.39;
					SetSped3 = 0;
				}
				else if (ped3_cord == 11)
				{
					ped3B_x = -302.6159;
					ped3B_y = 1849.694;
					ped3B_z = 5.39;
					SetSped3 = 1;
				}
				else if (ped3_cord == 12)
				{
					ped3B_x = -342.9068;
					ped3B_y = 1914.552;
					ped3B_z = 5.66;
					SetSped3 = 0;
				}
				else if (ped3_cord == 13)
				{
					ped3B_x = -246.1882;
					ped3B_y = 1926.108;
					ped3B_z = 5.66;
					SetSped3 = 1;
				}
				else if (ped3_cord == 14)
				{
					ped3B_x = -247.1527;
					ped3B_y = 1998.886;
					ped3B_z = 5.72;
					SetSped3 = 0;
				}
				else if (ped3_cord == 15)
				{
					ped3B_x = -351.0479;
					ped3B_y = 2010.804;
					ped3B_z = 5.54;
					SetSped3 = 0;
				}
				else if (ped3_cord == 16)
				{
					ped3B_x = -449.4703;
					ped3B_y = 1974.777;
					ped3B_z = 5.54;
					SetSped3 = 1;
				}
				else if (ped3_cord == 17)
				{
					ped3B_x = -437.7158;
					ped3B_y = 1861.706;
					ped3B_z = 5.09;
					SetSped3 = 0;
				}
				else if (ped3_cord == 18)
				{
					ped3B_x = -426.4738;
					ped3B_y = 1686;
					ped3B_z = 4.642499;
					SetSped3 = 0;
				}
				else if (ped3_cord == 19)
				{
					ped3B_x = -434.7247;
					ped3B_y = 1574.24;
					ped3B_z = 4.642499;
					SetSped3 = 0;
				}
				else if (ped3_cord == 20)
				{
					ped3B_x = -437.9045;
					ped3B_y = 1440.219;
					ped3B_z = 4.7;
					SetSped3 = 0;
				}
				else if (ped3_cord == 21)
				{
					ped3B_x = -439.3021;
					ped3B_y = 1318.542;
					ped3B_z = 4.7;
					SetSped3 = 1;
				}
				else if (ped3_cord == 22)
				{
					ped3B_x = -394.438;
					ped3B_y = 1291.611;
					ped3B_z = 4.7;
					SetSped3 = 0;
				}
				else if (ped3_cord == 23)
				{
					ped3B_x = -292.9197;
					ped3B_y = 1284.224;
					ped3B_z = 4.72;
					SetSped3 = 0;
				}
				else if (ped3_cord == 24)
				{
					ped3B_x = -210.1509;
					ped3B_y = 1280.655;
					ped3B_z = 5.291577;
					SetSped3 = 0;
				}
				else if (ped3_cord == 25)
				{
					ped3B_x = -155.6523;
					ped3B_y = 1277.019;
					ped3B_z = 5.279013;
					SetSped3 = 0;
				}
				else if (ped3_cord == 26)
				{
					ped3B_x = ped3B_x; 
					ped3B_y = ped3B_y;
					ped3B_z = ped3B_z;
					SetSped3 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 60.0, 2, 5, 10);// ��� ���� �� ������ ����������("p1"-���,"a2"-������,�yz,�����-�� ����,�������� ��������,�����-�� �����)
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
	//SET_CAR_DENSITY_MULTIPLIER(1);// ��������� ����
	SWITCH_ROADS_BACK_TO_ORIGINAL( -80.075, 1252.765, -1.286, -230.417, 1300.289, 80.0 );//  ���������� �������
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
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CASH", 2000);// +5000$
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
		ADD_SCORE( GetPlayerIndex(), +2000 );//��� ������ �����
		G_SA_RACE += 1;
	}
}
void main(void)
{
	WAIT(500);
	sa_race();
	TERMINATE_THIS_SCRIPT();
}
