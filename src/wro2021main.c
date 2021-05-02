#include "WRO_Lib.h"
float t; //excess's color
float ind1,ind2,ind3,ind4,ind5,ind6,blue,green,yellow,para; //variables for function info
short polozhenie=2; //var for void putgreen
void otvoz(short dom, short col)
{
	short sit=0;
	v=25; k1=0.2; k2=1;
	LineRed();
	short domcolor1, domcolor2;
	if(dom==1)
	{
		domcolor1=ind1;
		domcolor2=ind2;
	}
	if(dom==2)
	{
		domcolor1=ind3;
		domcolor2=ind4;
	}
	if(dom==3)
	{
		domcolor1=ind5;
		domcolor2=ind6;
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

void stapt()
{
	motor[motorD]=-25;
	move_enc(200, v, 'f');
	Line1Cross();
}

void info(short dom)
{
	tHTCS2 colorSensor;
	initSensor(&colorSensor, S4);
	goColor();
	if(colorSensor.color==2||colorSensor.color==3)
	{
		blue=blue+1;
	}
	if(colorSensor.color==4)
	{
		green=green+1;
	}
	if(colorSensor.color==6)
	{
		yellow=yellow+1;
	}
	if(dom==1)
	{
		if(colorSensor.color==3)
		{
			ind1=2;
		}
		else
		{
			ind1=colorSensor.color;
		}
	}
	if(dom==2)
	{
		if(colorSensor.color==3)
		{
			ind1=2;
		}
		else
		{
			ind3=colorSensor.color;
		}
	}
	if(dom==3)
	{
		if(colorSensor.color==3)
		{
			ind1=2;
		}
		else
		{
			ind5=colorSensor.color;
		}
	}
	while(colorSensor.color>0)
	{
		readSensor(&colorSensor);
		motor[motorB]=40;
		motor[motorC]=-40;
	}
	stopmotor();
	nMotorEncoder[motorB]=0;
	while(colorSensor.color!=2&&colorSensor.color!=3&&colorSensor.color!=4&&colorSensor.color!=6)
	{
		readSensor(&colorSensor);
		motor[motorB]=25;
		motor[motorC]=-25;
		if(SensorValue[S2]<15&&SensorValue[S3]<15)
		{
			break;
		}
	}
	if(dom==1)
	{
		if(colorSensor.color==3)
		{
			ind1=2;
		}
		else
		{
			ind2=colorSensor.color;
		}
	}
	if(dom==2)
	{
		if(colorSensor.color==3)
		{
			ind1=2;
		}
		else
		{
			ind4=colorSensor.color;
		}
	}
	if(dom==3)
	{
		if(colorSensor.color==3)
		{
			ind1=2;
		}
		else
		{
			ind6=colorSensor.color;
		}
	}
}

void CheckDom1()
{
	motor[motorD]=-25;
	move_enc(250, v, 'f');
	move_enc(260, 50, 'l');
	motor[motorD]=0;
	motor[motorB]=-40;
	motor[motorC]=40;
	wait10Msec(100);
	stopmotor();
	info(1);
	zahvat('o');
	v=25;
	goBlack(1);
	wait10Msec(20);
	povleft();
	motor[motorD]=0;
	LineCross();
	povright();
	Line_enc(300);
	povright();
}

void excess()
{
	nMotorEncoder[motorB]=0;
	tHTCS2 colorSensor;
	initSensor(&colorSensor, S4);
	readSensor(&colorSensor);
	t=4;
	while(colorSensor.color==0)
	{
		readSensor(&colorSensor);
		Line();
		if(nMotorEncoder[motorB]>550)
		{
			t=3;
			break;
		}
	}
	stopmotor();
	if(t==4)
	{
		mot1_enc(200, 'b', 'f');
		mot1_enc(180, 'c', 'f');
		move_enc(100, v, 'b');
		Line1Cross();
		Line_enc(20);
		mot1_enc(550, 'b', 'b');
		move_enc(420, 30, 'f');
		hapuga('d');
		move_enc(70, 30, 'b');
		move_enc(TURNAROUND-10, 25, 'l');
		move_enc(260, 18, 'b');
		wait10Msec(10);
		zahvat('c');
		move_enc(TURN, v, 'l');
		v=50;
		goBlack(1);
		playSound(soundBlip);
		move_enc(400, v, 'f');
		playSound(soundBlip);
		while(SensorValue[S2]<WHITE)
		{
			moving(v, 'f');
		}
		stopmotor();
		playSound(soundBlip);
		goBlack(1);
		v=25;
		povleft();
	}
	else
	{
		move_enc(400, v, 'b');
		povleft();
		LineCross();
		v=25;
		Line_enc(30);
		mot1_enc(ONEMOTORTURN, 'b', 'f');
		nMotorEncoder[motorB]=0;
		readSensor(&colorSensor);
		while(colorSensor.color==0)
		{
			readSensor(&colorSensor);
			motor[motorB]=30;
			motor[motorC]=-30;
			if(nMotorEncoder[motorB]>400)
			{
				t=2;
				break;
			}
		}
		stopmotor();
		if(t==3)
		{
			move_enc(20, v, 'f');
			move_enc(270, 40, 'r');
			move_enc(180, 30, 'f');
			hapuga('d');
			move_enc(70, 30, 'b');
			move_enc(TURNAROUND, 40, 'l');
			move_enc(200, 20, 'b');
			zahvat('c');
			move_enc(TURNAROUND, v, 'l');
			goBlack(3);
			povleft();
		}
		if(t==2)
		{
			while(SensorValue[S1]>BLACK)
			{
				moving(v, 'b');
			}
			povright();
			LineCross();
			mot1_enc(ONEMOTORTURN, 'b', 'b');
			move_enc(255, 25, 'b');
			zahvat('c');
			move_enc(TURNAROUND, v, 'l');
			move_enc(265, 25, 'f');
			wait1Msec(50);
			hapuga('d');
			move_enc(TURN, v, 'l');
			goBlack(1);
			povright();
		}
	}
}

void CheckDom2()
{
	//v=40;
	LineRed();
	stopmotor();
	move_enc(145, v, 'b');
	move_enc(TURN, 30, 'l');
	move_enc(450, v, 'b');
	info(2);
	goBlack(3);
	povleft();
	Line_enc(200);
}

void akkum1()
{
	v=25;
	//v=50;
	while(SensorValue[S2]>15||SensorValue[S3]>15)
	{
		Line();
	}
	stopmotor();
	move_enc(TURNAROUND, 30, 'l');
	move_enc(115, 35, 'b');
	zahvat('o');
	goBlack(2);
	wait10Msec(500);
	//move_enc(20, v, 'f');
	povright();
	eraseDisplay();
	displayCenteredBigTextLine(2, "%d", SensorValue[S1]);
	stopmotor();
	wait10Msec(500);
}

void CheckDom3()
{
	Line_enc(150);
	perebros();
	move_enc(TURNAROUND, v, 'l');
	LineCross();
	wait10Msec(40);
	povright();
	LineRed();
	stopmotor();
	move_enc(145, v, 'b');
	move_enc(TURN, 30, 'l');
	move_enc(450, v, 'b');
	info(3);
	goBlack(2);
}

void putblue()
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
	mot1_enc(TURNAROUND, 'b', 'b');
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]>-500)
	//{
	//	motor[motorB]=-v;
	//}
	//stopmotor();
	motor[motorA]=-20;
	wait10Msec(50);
	motor[motorA]=0;
	move_enc(150, v, 'b');
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]>-150)
	//{
	//	motor[motorB]=-v;
	//	motor[motorC]=v;
	//}
	//stopmotor();
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
	//while(SensorValue[S3]>30)
	//{
	//	motor[motorB]=v;
	//	motor[motorC]=-v;
	//}
	move_enc(230, v, 'f');
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]<230)
	//{
	//	motor[motorB]=v;
	//	motor[motorC]=-v;
	//}
	motor[motorA]=0;
	move_enc(230, v, 'l');
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]<230)
	//{
	//	motor[motorB]=v;
	//	motor[motorC]=v;
	//}
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
	mot1_enc(500, 'b', 'b');
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]>-500)
	//{
	//	motor[motorB]=-v;
	//}
	//stopmotor();
}

void akkum2()
{
	LineCross();
	move_enc(100,v,'f');
	hapuga('d');
	move_enc(100,v,'b');
	hapuga('u');
}

void RazvozBlue()
{
	hapuga('u');
	while (SensorValue[S1]<35)
	{
		moving(v, 'f');
	}
	stopmotor();
	goBlack(1);
	if (ind5==2||ind6==2||ind5==0||ind6==0)
	{
		otvoz(3, 2);
		povleft();
		Line_enc(550);
		LineCross();
		if(blue==1)
		{
			Line_enc(70);
			move_enc(TURN, v, 'l');
			move_enc(200, v, 'b');
			akkum2();
			if(ind3==2||ind4==2||ind3==0||ind4==0)
			{
				povright();
				povright();
				otvoz(2, 2);
				povright();
			}
			if(ind1==2||ind2==2||ind1==0||ind2==0)
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
			if(ind3==2||ind4==2||ind3==0||ind4==0)
			{
				povright();
				otvoz(2, 2);
				povright();
				if(ind1==2||ind2==2||ind1==0||ind2==0)
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
				if(ind1==2||ind2==2||ind1==0||ind2==0)
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
		if(blue==1)
		{
			Line_enc(70);
			move_enc(TURN, v, 'l');
			move_enc(200, v, 'b');
			akkum2();
			if(ind3==2||ind4==2||ind3==0||ind4==0)
			{
				povright();
				povright();
				otvoz(2,2);
				povright();
				if(ind1==2||ind2==2||ind1==0||ind2==0)
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
				if(ind1==2||ind2==2||ind1==0||ind2==0)
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
			if(ind3==2||ind4==2||ind3==0||ind4==0)
			{
				povright();
				otvoz(2,2);
				povright();
				if(ind1==2||ind2==2||ind3==0||ind4==0)
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

void putgreen()
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

void RazvozGreen()
{
	hapuga('u');
	if(ind1==4||ind2==4)
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
		if(ind1!=4||ind2!=4)
		{
			nMotorEncoder[motorB]=0;
			while(nMotorEncoder[motorB]<200)
			{
				Line1();
			}
			Line1Cross();
		}
		if(green==1)
		{
			akkum2();
		}
		if(ind3==4||ind4==4)
		{
			povleft();
			otvoz(2, 4);
			povright();
		}
		if(ind5==4||ind6==4)
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
		if(green==1)
		{
			povleft();
			Line_enc(300);
			povright();
			akkum2();
			if(ind3==4||ind4==4)
			{
				povleft();
				otvoz(2, 4);
				povright();
			}
			if(ind5==4||ind6==4)
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
			if(ind3==4||ind4==4)
			{
				povleft();
				otvoz(2, 4);
				if(ind5==4||ind6==4)
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

void putyellow()
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

void RazvozYellow()
{
	move_enc(200, v, 'b');
	if(ind3==6||ind4==6)
	{
		move_enc(TURN, v, 'r');
		hapuga('u');
		goBlack(3);
		povleft();
		otvoz(2, 6);
		if(yellow==1)
		{
			akkum2();
			povright();
			LineCross();
			povright();
		}
		if(ind1==6||ind2==6)
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
		if(ind5==6||ind6==6)
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
		if(ind3==6&&ind4==6)
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
		if(yellow==1)
		{
			povleft();
			mot1_enc(200, 'b', 'f');
			mot1_enc(180, 'c', 'f');
			Line1Cross();
			povleft();
			Line_enc(300);
			povleft();
			akkum2();
			if(ind5==6||ind6==6)
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
			if(ind5==6||ind6==6)
			{
				povleft();
				LineCross();
				povright();
				otvoz(3, 6);
				povleft();
				if(ind1==6||ind2==6)
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

void batarei()
{
	LineCross();
	povright();
	Line_enc(250);
	move_enc(TURN,v,'l');
	move_enc(200,v,'f');
	hapuga('d');
	move_enc(TURN,v,'l');
	move_enc(100,v,'b');
	hapuga('u');
	move_enc(200,v,'b');
	move_enc(TURN,v,'l');
	while (SensorValue[S1]<WHITE)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	while (SensorValue[S1]>BLACK+20)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	move_enc(20, v, 'f');
	povright();
	while(SensorValue[S3]<WHITE)
	{
		Line1();
	}
	while(SensorValue[S3]>BLACK+20)
	{
		Line1();
	}
	move_enc(200,v,'f');
	move_enc(TURN,v,'r');
	move_enc(333,v,'f');
	hapuga('d');
	move_enc(TURN,v,'r');
	move_enc(135,v,'b');
	hapuga('u');
	move_enc(270,v,'b');
}


task main()
{
	v=25; k1=0.2; k2=10;
	motor[motorD]=0;
	stapt();
	CheckDom1();
	excess();
	CheckDom2();
	akkum1();
	CheckDom3();
	//putblue();
	//RazvozBlue();
	//putgreen();
	//RazvozGreen();
	//putyellow();
	//batarei();
}
