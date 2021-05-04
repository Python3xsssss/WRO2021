#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H

short para;
short polozhenie=2;

void otvoz(short dom, short col)
{
	short sit=0;
	v=25; k1=0.2; k2=1;
	LineRed();
	short domcolor1, domcolor2;
	if(dom==1)
	{
		domcolor1=indDom1[0];
		domcolor2=indDom1[1];
	}
	if(dom==2)
	{
		domcolor1=indDom2[0];
		domcolor2=indDom2[1];
	}
	if(dom==3)
	{
		domcolor1=indDom3[0];
		domcolor2=indDom3[1];
	}
	if(col==6||domcolor1==0||domcolor2==0)
	{
		sit=1;
	}
	if(sit==0)
	{
		if(domcolor1==col&&domcolor2==col)
		{
			para=para+2;
			hapuga('d');
			move_enc(200, v, 'b');
			hapuga('u');
			LineRed();
			move_enc(200, v, 'b');
			move_enc(TURNAROUND, v, 'r');
			LineCross();
		}
		else
		{
			para=para+1;
			if(para%2==1)
			{
				hapuga('u');
				move_enc(200, v, 'b');
				move_enc(TURNAROUND, v, 'r');
				LineCross();
			}
			else
			{
				hapuga('d');
				move_enc(200, v, 'b');
				move_enc(TURNAROUND, v, 'r');
				LineCross();
			}
		}
	}
	else
	{
		if(col!=6)
		{
			if(domcolor1!=col&&domcolor2!=col)
			{
				move_enc(200,v,'b');
				move_enc(TURNAROUND, v, 'r');
				move_enc(150,v,'b');
				zahvat('o');
				LineCross();
			}
			else
			{
				hapuga('u');
				move_enc(200,v,'b');
				move_enc(TURNAROUND, v, 'r');
				hapuga('d');
				move_enc(150,v,'b');
				zahvat('o');
				LineCross();
				hapuga('u');
			}
		}
		else
		{
			if(domcolor1!=col||domcolor2!=col)
			{
				move_enc(200,v,'b');
				move_enc(TURNAROUND, v, 'r');
				move_enc(150,v,'b');
				zahvat('o');
				LineCross();
				para++;
			}
			else
			{
				hapuga('u');
				move_enc(200,v,'b');
				move_enc(TURNAROUND, v, 'r');
				hapuga('d');
				move_enc(150,v,'b');
				zahvat('o');
				LineCross();
				hapuga('u');
				para=para+2;
			}
		}
	}
	sit=0;
}

void putnBlue()
{
	while (SensorValue[S1]<WHITE)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	while (SensorValue[S1]>40)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	stopmotor();
	while (SensorValue[S1]<WHITE)
	{
		motor[motorB]=v;
	}
	while (SensorValue[S1]>40)
	{
		motor[motorB]=v;
	}
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<350)
	{
		Line2();
	}
	while(SensorValue[S3]<WHITE)
	{
		Line2();
	}
	while(SensorValue[S3]<BLACK)
	{
		Line2();
	}
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<270)
	{
		Line2();
	}
	move_enc(230, v, 'r');
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]>-230)
	//{
	//	motor[motorB]=-v;
	//	motor[motorC]=-v;
	//}
	//nMotorEncoder[motorB]=0;
	move_enc(230, v, 'b');
	//while(nMotorEncoder[motorB]>-230)
	//{
	//	motor[motorB]=-v;
	//	motor[motorC]=v;
	//}
	//stopmotor();
	motor[motorA]=-100;
	wait10Msec(30);
	motor[motorA]=0;
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	wait1Msec(10);
	stopmotor();
	motor[motorA]=20;
	wait10Msec(50);
	motor[motorA]=0;
	mot1_enc(ONEMOTORTURN, 'b', 'b');
	motor[motorA]=-20;
	wait10Msec(50);
	motor[motorA]=0;
	move_enc(150, v, 'b');
	motor[motorA]=20;
	wait10Msec(50);
	motor[motorA]=0;
	while(SensorValue[S3]<WHITE)//65
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	motor[motorA]=-20;
	goBlack(3);
	move_enc(230, v, 'f');
	motor[motorA]=0;
	move_enc(230, v, 'l');
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	wait1Msec(30);
	stopmotor();
	motor[motorA]=20;
	wait10Msec(35);
	motor[motorA]=0;
	mot1_enc(ONEMOTORTURN, 'b', 'b');
}

void akkum2()
{
	LineCross();
	move_enc(100,v,'f');
	hapuga('d');
	move_enc(100,v,'b');
	hapuga('u');
}

void RazvoznBlue()
{
	hapuga('u');
	while (SensorValue[S1]<35)
	{
		moving(v, 'f');
	}
	stopmotor();
	goBlack(1);
	if (indDom3[0]==2||indDom3[1]==2||indDom3[0]==0||indDom3[1]==0)
	{
		otvoz(3, 2);
		povleft();
		Line_enc(550);
		LineCross();
		if(nBlue == 1)
		{
			Line_enc(70);
			move_enc(TURN, v, 'l');
			move_enc(200, v, 'b');
			akkum2();
			if(indDom2[0]==2||indDom2[1]==2||indDom2[0]==0||indDom2[1]==0)
			{
				povright();
				povright();
				otvoz(2, 2);
				povright();
			}
			if(indDom1[0]==2||indDom1[1]==2||indDom1[0]==0||indDom1[1]==0)
			{
				povright();
				Line_enc(300);
				LineCross();
				mot1_enc(200, 'b', 'f');
				mot1_enc(180, 'c', 'f');
				Line1Cross();
				povleft();
				otvoz(1, 2);
				povright();
				polozhenie=1;
			}
		}
		else
		{
			if(indDom2[0]==2||indDom2[1]==2||indDom2[0]==0||indDom2[1]==0)
			{
				povright();
				otvoz(2, 2);
				povright();
				if(indDom1[0]==2||indDom1[1]==2||indDom1[0]==0||indDom1[1]==0)
				{
					Line_enc(300);
					LineCross();
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
					otvoz(1, 2);
					povright();
					polozhenie=1;
				}
			}
			else
			{
				if(indDom1[0]==2||indDom1[1]==2||indDom1[0]==0||indDom1[1]==0)
				{
					Line_enc(300);
					LineCross();
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
					otvoz(1, 2);
					povright();
					polozhenie=1;
				}
			}
		}
	}
	else
	{
		povright();
		Line_enc(550);
		LineCross();
		if(nBlue==1)
		{
			Line_enc(70);
			move_enc(TURN, v, 'l');
			move_enc(200, v, 'b');
			akkum2();
			if(indDom2[0]==2||indDom2[1]==2||indDom2[0]==0||indDom2[1]==0)
			{
				povright();
				povright();
				otvoz(2,2);
				povright();
				if(indDom1[0]==2||indDom1[1]==2||indDom1[0]==0||indDom1[1]==0)
				{
					Line_enc(300);
					LineCross();
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
					otvoz(1, 2);
					povright();
					polozhenie=1;
				}
			}
			else
			{
				if(indDom1[0]==2||indDom1[1]==2||indDom1[0]==0||indDom1[1]==0)
				{
					Line_enc(300);
					LineCross();
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
					otvoz(1, 2);
					povright();
					polozhenie=1;
				}
			}
		}
		else
		{
			if(indDom2[0]==2||indDom2[1]==2||indDom2[0]==0||indDom2[1]==0)
			{
				povright();
				otvoz(2,2);
				povright();
				if(indDom1[0]==2||indDom1[1]==2||indDom2[0]==0||indDom2[1]==0)
				{
					LineCross();
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
					otvoz(1, 2);
					povright();
					polozhenie=1;
				}
			}
		}
	}
}

void putnGreen()
{
	if(polozhenie==2)
	{
		while(SensorValue[S1]<WHITE)
		{
			Line();
		}
		LineCross();
		move_enc(TURN, v, 'l');
		move_enc(90, v, 'b');
		hapuga('d');
		goBlack(2);
	}
	if(polozhenie==1)
	{
		mot1_enc(200, 'b', 'f');
		mot1_enc(180, 'c', 'f');
		Line1Cross();
		nMotorEncoder[motorB]=0;
		while(nMotorEncoder[motorB]<80)
		{
			Line1();
		}
		while(SensorValue[S3]>27)
		{
			Line1();
		}
		stopmotor();
		move_enc(TURN, v, 'r');
		move_enc(70, v, 'b');
		hapuga('d');
		goBlack(2);
	}
	nMotorEncoder[motorA]=0;
	while(nMotorEncoder[motorA]<35)
	{
		motor[motorA]=25;
	}
	motor[motorA]=0;
	move_enc(130, v, 'f');
	hapuga('u');
	while(SensorValue[S2]>BLACK)
	{
		moving(v, 'b');
	}
	stopmotor();
	povleft();
	LineCross();
	Line_enc(240);
	move_enc(275, v, 'r');
	move_enc(200, v, 'b');
	hapuga('d');
	move_enc(150, v, 'b');
	hapuga('u');
	goBlack(3);
	hapuga('d');
	wait10Msec(10);
	nMotorEncoder[motorA]=0;
	while(nMotorEncoder[motorA]<35)
	{
		motor[motorA]=25;
	}
	motor[motorA]=0;
	move_enc(135, v, 'f');
	while(nMotorEncoder[motorA]<80)
	{
		motor[motorA]=25;
	}
	motor[motorA]=0;
	wait10Msec(20);
	move_enc(40, 15, 'b');
	hapuga('d');
	wait10Msec(25);
	nMotorEncoder[motorA]=0;
	while(nMotorEncoder[motorA]<65)
	{
		motor[motorA]=50;
	}
	motor[motorA]=0;
	while(SensorValue[S1]>BLACK)
	{
		moving(15, 'b');
	}
	stopmotor();
}

void RazvoznGreen()
{
	hapuga('u');
	if(indDom1[0]==4||indDom1[1]==4)
	{
		povright();
		Line_enc(600);
		mot1_enc(200, 'b', 'f');
		mot1_enc(180, 'c', 'f');
		Line1Cross();
		povleft();
		otvoz(1, 4);
		povright();
		Line_enc(300);
		mot1_enc(200, 'b', 'f');
		mot1_enc(180, 'c', 'f');
		Line1Cross();
		if(indDom1[0]!=4||indDom1[1]!=4)
		{
			nMotorEncoder[motorB]=0;
			while(nMotorEncoder[motorB]<200)
			{
				Line1();
			}
			Line1Cross();
		}
		if(nGreen == 1)
		{
			akkum2();
		}
		if(indDom2[0]==4||indDom2[1]==4)
		{
			povleft();
			otvoz(2, 4);
			povright();
		}
		if(indDom3[0]==4||indDom3[1]==4)
		{
			mot1_enc(200, 'c', 'f');
			mot1_enc(180, 'b', 'f');
			LineCross();
			povright();
			otvoz(3, 4);
			povleft();
		}
	}
	else
	{
		povleft();
		Line_enc(300);
		mot1_enc(200, 'b', 'f');
		mot1_enc(180, 'c', 'f');
		Line1Cross();
		if(nGreen==1)
		{
			povleft();
			Line_enc(300);
			povright();
			akkum2();
			if(indDom2[0]==4||indDom2[1]==4)
			{
				povleft();
				otvoz(2, 4);
				povright();
			}
			if(indDom3[0]==4||indDom3[1]==4)
			{
				mot1_enc(200, 'c', 'f');
				mot1_enc(180, 'b', 'f');
				LineCross();
				povright();
				otvoz(3, 4);
				povleft();
			}
		}
		else
		{
			if(indDom2[0]==4||indDom2[1]==4)
			{
				povleft();
				otvoz(2, 4);
				if(indDom3[0]==4||indDom3[1]==4)
				{
					povleft();
					LineCross();
					povright();
					otvoz(3, 4);
					povleft();
				}
				else
				{
					povright();
				}
			}
			else
			{
				mot1_enc(200, 'c', 'f');
				mot1_enc(180, 'b', 'f');
				LineCross();
				povright();
				otvoz(3, 4);
				povleft();
			}
		}
	}
}

void putnYellow()
{
	LineCross();
	povleft();
	Line_enc(610);
	move_enc(TURN,v,'l');
	move_enc(70,v,'b');
	stopmotor();
	zahvat('c');
	povleft();
	LineCross();
	Line_enc(700);
	move_enc(TURN,v,'l');
	move_enc(200,v,'f');
	hapuga('d');
}

void RazvoznYellow()
{
	move_enc(200, v, 'b');
	if(indDom2[0]==6||indDom2[1]==6)
	{
		move_enc(TURN, v, 'r');
		hapuga('u');
		goBlack(3);
		povleft();
		otvoz(2, 6);
		if(nYellow == 1)
		{
			akkum2();
			povright();
			LineCross();
			povright();
		}
		if(indDom1[0]==6||indDom1[1]==6)
		{
			povright();
			LineCross();
			Line_enc(300);
			mot1_enc(200, 'b', 'f');
			mot1_enc(180, 'c', 'f');
			Line1Cross();
			povleft();
			otvoz(1, 6);
			povright();
			Line_enc(150);
			mot1_enc(200, 'b', 'f');
			mot1_enc(180, 'c', 'f');
			Line1Cross();
			povleft();
		}
		if(indDom3[0]==6||indDom3[1]==6)
		{
			povleft();
			LineCross();
			povright();
			otvoz(3, 6);
			povleft();
			LineCross();
			Line_enc(300);
			LineCross();
			povright();
		}
		if(indDom2[0]==6&&indDom2[1]==6)
		{
			povright();
			LineCross();
			povright();
		}
	}
	else
	{
		move_enc(TURNAROUND, v, 'l');
		hapuga('u');
		goBlack(3);
		if(nYellow==1)
		{
			povleft();
			mot1_enc(200, 'b', 'f');
			mot1_enc(180, 'c', 'f');
			Line1Cross();
			povleft();
			Line_enc(300);
			povleft();
			akkum2();
			if(indDom3[0]==6||indDom3[1]==6)
			{
				povleft();
				LineCross();
				povright();
				otvoz(3, 6);
				povleft();
				LineCross();
				Line_enc(300);
				LineCross();
				povright();
			}
			else
			{
				povright();
				LineCross();
				Line_enc(300);
				mot1_enc(200, 'b', 'f');
				mot1_enc(180, 'c', 'f');
				Line1Cross();
				povleft();
				otvoz(1, 6);
				povright();
				Line_enc(150);
				mot1_enc(200, 'b', 'f');
				mot1_enc(180, 'c', 'f');
				Line1Cross();
				povleft();
			}
		}
		else
		{
			if(indDom3[0]==6||indDom3[1]==6)
			{
				povleft();
				LineCross();
				povright();
				otvoz(3, 6);
				povleft();
				if(indDom1[0]==6||indDom1[1]==6)
				{
					LineCross();
					Line_enc(300);
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
					otvoz(1, 6);
					povright();
					Line_enc(150);
					mot1_enc(200, 'b', 'f');
					mot1_enc(180, 'c', 'f');
					Line1Cross();
					povleft();
				}
				else
				{
					LineCross();
					Line_enc(300);
					LineCross();
					povright();
				}
			}
			else
			{
				povright();
				LineCross();
				Line_enc(300);
				mot1_enc(200, 'b', 'f');
				mot1_enc(180, 'c', 'f');
				Line1Cross();
				povleft();
				otvoz(1, 6);
				povright();
				Line_enc(150);
				mot1_enc(200, 'b', 'f');
				mot1_enc(180, 'c', 'f');
				Line1Cross();
				povleft();
			}
		}
	}
}

void AllocateAllBricks()
{
	putnBlue();
	RazvoznBlue();
	putnGreen();
	RazvoznGreen();
	putnYellow();
}

#endif
