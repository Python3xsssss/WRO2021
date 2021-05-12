#pragma once

#ifndef TESTLIB_H
#define TESTLIB_H

#include "hitechnic-colour-v2.h"

#define BLACK 15
#define WHITE 56
#define GREY 40
#define TURN 250
#define TURNAROUND 500
#define ONEMOTORTURN 500
#define CROSS_ENC 100
#define SPEC_DIFF 85
#define HAPUGAM 25
#define ZAHVATG 31
#define HAPUGAG 62
//#define LINETOLINE 200

short pauseCounter = 0;
short stdPower, lineMaxPower, zonePower;
short location, old_location;
short sensors = 0;
short indDoms[3][2] = {{-1,-1}, {-1,-1}, {-1,-1}}; // indDoms[0][0] - color index of first indicator in first dom, etc.
short nInds[3] = {0, 0, 0}; // nInds[0] - num of blue indicators, etc.
short bricksInRobot[4] = {-2, -2, -2, -2}; // bricksInRobot[0] - color index of bricks in hapuga, [1] - on hapuga, [2] - in zahvat, [3] - on zahvat
short exColor;
short zahvatPos = 0, hap = 2;
float k1, k2;
tHTCS2 colorSensor;

void Line(short speed)
{
	if (speed == lineMaxPower)
	{
		k1=0.25;
		k2=15;
	}
	if (speed == stdPower)
	{
		k1=0.2;
		k2=10;
	}
	if(speed == zonePower)
	{
		k1=0.15;
		k2=13;
	}
	sensors = 0;
	static short eold, e, es, u;
	es = SensorValue[S2] - SensorValue[S3];
	e = SensorValue[S2] - SensorValue[S3]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u);
	motor[motorC]=(- speed + u);
}

void Line1(short speed)
{
	if (speed == lineMaxPower)
	{
		k1=0.25;
		k2=15;
	}
	if (speed == stdPower)
	{
		k1=0.2;
		k2=10;
	}
	if(speed == zonePower)
	{
		k1=0.15;
		k2=13;
	}
	sensors = 1;
	static short eold, e, es, u;
	es=SensorValue[S1]-SensorValue[S2];
	e=SensorValue[S1]-SensorValue[S2]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u)*0.96;
	motor[motorC]=(-speed + u)*1.04;
}

void Line2(short speed)
{
	k1 = 0.2; k2 = 10;
	static short eold, e, u;
	e=GREY-SensorValue[S1];
	u=k1*e+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u);
	motor[motorC]=(-speed + u);
}

void stopmotor()
{
	motor[motorB]=0;
	motor[motorC]=0;
	wait10Msec(30);
	pauseCounter++;
}

void moving(short speed, char dir)
{
	if(dir=='f')
	{
		motor[motorB]=speed;
		motor[motorC]=-speed;
	}
	if(dir=='b')
	{
		motor[motorB]=-speed;
		motor[motorC]=speed;
	}
	if(dir=='l')
	{
		motor[motorB]=speed;
		motor[motorC]=speed;
	}
	if(dir=='r')
	{
		motor[motorB]=-speed;
		motor[motorC]=-speed;
	}
}

void move_enc(short enc, short speed, char dir, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	if(dir=='f')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			motor[motorB]=speed;
			motor[motorC]=-speed;
		}
	}
	if(dir=='b')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			motor[motorB]=-speed;
			motor[motorC]=speed;
		}
	}
	if(dir=='l')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			motor[motorB]=speed;
			motor[motorC]=speed;
		}
	}
	if(dir=='r')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			motor[motorB]=-speed;
			motor[motorC]=-speed;
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}

}

void povright(short speed, const string ifCross)
{
	if (ifCross == "cross" || ifCross == "Cross" || ifCross == "CROSS")
	{
		move_enc(CROSS_ENC, speed, 'f', "stop");
	}

	if((hap == 1 && bricksInRobot[1] == 1) || (hap == 2 && bricksInRobot[0] == 1))
	{
		stdPower = 18;
	}

	move_enc(100, speed, 'r', "");
	while (SensorValue[S2] > BLACK + 5)
	{
		moving(speed, 'r');
	}
	while (SensorValue[S2] < WHITE - 20)
	{
		moving(speed, 'r');
	}

	stopmotor();
	stdPower = 25;
	sensors = 0;
}

void povleft(short speed, const string ifCross)
{
	if (ifCross == "cross" || ifCross == "Cross" || ifCross == "CROSS")
	{
		move_enc(CROSS_ENC, speed, 'f', "stop");
	}

	if((hap == 1 && bricksInRobot[1] == 1) || (hap == 2 && bricksInRobot[0] == 1))
	{
		stdPower = 18;
	}

	move_enc(100, speed, 'l', "");
	while (SensorValue[S3] > BLACK + 5)
	{
		moving(speed, 'l');
	}
	while (SensorValue[S3] < WHITE - 20)
	{
		moving(speed, 'l');
	}

	stopmotor();
	stdPower = 25;
	sensors = 0;
}

void LineRed(short speed, const string ifStop)
{
	getColorName(S1);
	while(getColorName(S1)!=5)
	{
		Line(speed);
	}

	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
	getColorReflected(S1);
}

void LineCross(short speed, const string ifStop)
{
	while(SensorValue[S1]>BLACK)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void Line1Cross(short speed, const string ifStop)
{
	while(SensorValue[S3]>BLACK)
	{
		Line1(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void lineWhite(short speed, const string ifStop)
{
	while(SensorValue[S1]<WHITE)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void line1White(short speed, const string ifStop)
{
	while(SensorValue[S3]<WHITE)
	{
		Line1(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void Line_enc(float enc2, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<enc2)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void Line1_enc(float enc2, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<enc2)
	{
		Line1(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void fwd_black(short SensorPort, short speed, const string ifStop)
{
	if(SensorPort==1)
	{
		while(SensorValue[S1]>BLACK)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==2)
	{
		while(SensorValue[S2]>BLACK)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==3)
	{
		while(SensorValue[S3]>BLACK)
		{
			moving(speed, 'f');
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void fwd_white(short SensorPort, short speed, const string ifStop)
{
	if(SensorPort==1)
	{
		while(SensorValue[S1] < WHITE)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==2)
	{
		while(SensorValue[S2] < WHITE)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==3)
	{
		while(SensorValue[S3] < WHITE)
		{
			moving(speed, 'f');
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

bool pass_color(short nEnc, short speed)
{
	while(colorSensor.color>0)
	{
		readSensor(&colorSensor);
		moving(speed, 'f');
	}

	nMotorEncoder[motorB]=0;
	while(colorSensor.color != 2 && colorSensor.color != 3 && colorSensor.color != 4 && colorSensor.color != 6)
	{
		readSensor(&colorSensor);
		moving(speed, 'f');
		if (SensorValue[S2] < BLACK && SensorValue[S3] < BLACK || nMotorEncoder[motorB] >= nEnc)
		{
			return false;
		}
	}
	return true;
}

bool back_pass_color(short nEnc, short speed)
{
	while(colorSensor.color > 0)
	{
		readSensor(&colorSensor);
		moving(speed, 'b');
	}

	nMotorEncoder[motorB]=0;
	while(colorSensor.color != 2 && colorSensor.color != 3 && colorSensor.color != 4 && colorSensor.color != 6)
	{
		readSensor(&colorSensor);
		moving(speed, 'b');
		if (nMotorEncoder[motorB] <= -nEnc)
		{
			return false;
		}
	}
	return true;
}

bool pass_any(short nEnc, short speed)
{
	nMotorEncoder[motorB]=0;
	while(colorSensor.color == 0)
	{
		readSensor(&colorSensor);
		moving(speed, 'f');
		if (nMotorEncoder[motorB] >= nEnc)
		{
			return false;
		}
	}
	return true;
}

bool line_any(short nEnc, short speed)
{
	nMotorEncoder[motorB]=0;
	while(colorSensor.color == 0)
	{
		readSensor(&colorSensor);
		Line(speed);
		if (nMotorEncoder[motorB] >= nEnc)
		{
			return false;
		}
	}
	return true;
}

void mot1_enc(short enc, char portMotor, short speed, char dir, const string ifStop)
{
	if (portMotor=='b')
	{
		nMotorEncoder[motorB]=0;
		if(dir=='f')
		{
			while(nMotorEncoder[motorB]<enc)
			{
				motor[motorB]=speed;
			}
		}
		if(dir=='b')
		{
			while(nMotorEncoder[motorB]>-enc)
			{
				motor[motorB]=-speed;
			}
		}
	}
	if (portMotor=='c')
	{
		nMotorEncoder[motorC]=0;
		if(dir=='f')
		{
			while(nMotorEncoder[motorC]>-enc)
			{
				motor[motorC]=-speed;
			}
		}
		if(dir=='b')
		{
			while(nMotorEncoder[motorC]<enc)
			{
				motor[motorC]=speed;
			}
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

//void lineToLine()
//{
//	if(sensors == 0)
//	{
//		mot1_enc(LINETOLINE, 'b', stdPower, 'f', "stop");
//		mot1_enc(LINETOLINE, 'c', stdPower, 'f', "stop");
//		sensors = 1;
//	}
//	else
//	{
//		mot1_enc(LINETOLINE, 'c', stdPower, 'f', "stop");
//		mot1_enc(LINETOLINE, 'b', stdPower, 'f', "stop");
//		sensors = 0;
//	}
//}

void hapuga(char dir)
{
	if(dir=='u')
	{
		motor[motorA]=20;
		wait10Msec(55);
		hap = 2;
	}
	if(dir=='d')
	{
		motor[motorA]=-30;
		wait10Msec(65);
		hap = 0;
	}
	if(dir ==  'm')
	{
		motor[motorA]=15;
		wait10Msec(20);
		motor[motorA]=0;
		wait10Msec(20);
		nMotorEncoder[motorA]=0;
		while(nMotorEncoder[motorA] < HAPUGAM)
		{
			motor[motorA] = 20;
		}
		hap = 1;
	}
	motor[motorA]=0;
}

void zahvat(char dir)
{
	short speed;
	if(bricksInRobot[3] > -2)
	{
		speed = 18;
	}
	else
	{
		speed = 30;
	}

	nMotorEncoder[motorD]=0;
	if(dir=='c')
	{
		if(zahvatPos != 0)
		{
			motor[motorD]=-speed;
			wait10Msec(4200/speed);
		}
		zahvatPos = 0;
	}

	if(dir=='o')
	{
		if(zahvatPos != 2)
		{
			motor[motorD]=speed;
			wait10Msec(3500/speed);
		}
		zahvatPos = 2;
	}

	if(dir=='m')
	{
		nMotorEncoder[motorD]=0;
		if(zahvatPos == 0)
		{
			while(nMotorEncoder[motorD] < 200)
			{
				motor[motorD]=speed;
			}
		}
		if(zahvatPos == 2)
		{
			while(nMotorEncoder[motorD] > -250)
			{
				motor[motorD]=-speed;
			}
		}
		zahvatPos = 1;
	}

	if(dir=='g')
	{
		while(nMotorEncoder[motorD] > -ZAHVATG)
		{
			motor[motorD]=-15;
		}
	}
	motor[motorD]=0;
}

task hapugaU()
{
	hapuga('u');
}

task hapugaDM()
{
	hapuga('d');
	wait10Msec(25);
	hapuga('m');
}

task hapugaM()
{
	hapuga('m');
}

task hapugaD()
{
	hapuga('d');
}

task zahvatC()
{
	zahvat('c');
}

task zahvatO()
{
	zahvat('o');
}

task zahvatCor()
{
	motor[motorD]=-30;
	wait10Msec(35);
	motor[motorD]=0;
}

void perebros(short speed)
{
	hapuga('u');
	startTask(zahvatO);
	move_enc(200, speed, 'b', "stop");
	move_enc(TURNAROUND+20, speed, 'l', "stop");
	move_enc(200, speed, 'b', "stop");
	zahvat('c');
	bricksInRobot[0] = -2; bricksInRobot[1] = -1;
}

void akkumGB()
{
	motor[motorA]=-60;
	wait10Msec(25);
	motor[motorA]=0;
	while(SensorValue[S2] > BLACK)
	{
		moving(stdPower, 'b');
	}
	stopmotor();
	hapuga('u');
	bricksInRobot[1] = -2;
}

void akkum_std()
{
	if(indDoms[2][0] != -1 || indDoms[2][1] != -1)
	{
		stopmotor();
		hapuga('d');
		hapuga('m');
	}
	move_enc(TURNAROUND+12, stdPower, 'l', "stop");
	move_enc(90+CROSS_ENC, 15, 'b', "stop");
	zahvat('o');
	zahvat('c');
	fwd_black(1, stdPower, "");
	bricksInRobot[2] = -2;
}

void crosses(short destination, const string ifStop)
{
	if(destination % 2 == 0 && destination < location || destination % 2 != 0 && destination > location)
	{
		for(short i = 0; i < abs(destination - location)/2 + abs(destination - location) % 2; i++)
		{
			if(i != 0)
			{
				Line_enc(100, lineMaxPower, "");
			}
			lineWhite(lineMaxPower, "");
			LineCross(lineMaxPower, "");
		}
	}
	else
	{
		for(short i = 0; i < abs(destination - location)/2 + abs(destination - location) % 2; i++)
		{
			if(i != 0)
			{
				Line1_enc(100, lineMaxPower, "");
			}
			line1White(lineMaxPower, "");
			Line1Cross(lineMaxPower, "");
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
	old_location = location;
	location = destination;
}

void povrightSpec(short speed)
{
	move_enc(CROSS_ENC+SPEC_DIFF, speed, 'f', "stop");
	if((hap == 1 && bricksInRobot[1] == 1) || (hap == 2 && bricksInRobot[0] == 1))
	{
		stdPower = 18;
	}
	move_enc(100, speed, 'r', "");
	while (SensorValue[S1] > BLACK + 5)
	{
		moving(speed, 'r');
	}
	while (SensorValue[S1] < WHITE - 20)
	{
		moving(speed, 'r');
	}
	stdPower = 25;
	stopmotor();
	sensors = 1;
}

void povleftSpec(short speed)
{
	move_enc(CROSS_ENC-SPEC_DIFF, speed, 'f', "stop");
	if((hap == 1 && bricksInRobot[1] == 1) || (hap == 2 && bricksInRobot[0] == 1))
	{
		stdPower = 18;
	}
	move_enc(100, speed, 'l', "");
	while (SensorValue[S2] > BLACK + 5)
	{
		moving(speed, 'l');
	}
	while (SensorValue[S2] < WHITE - 20)
	{
		moving(speed, 'l');
	}
	stdPower = 25;
	stopmotor();
	sensors = 1;
}

void turning(short destination)
{
	if(location < destination && location % 2 == 1)
	{
		if(destination % 2 == 1)
		{
			povright(stdPower, "cross");
		}
		else
		{
			povrightSpec(stdPower);
		}
	}
	if(location > destination && location % 2 == 0)
	{
		if(destination % 2 == 0)
		{
			povright(stdPower, "cross");
		}
		else
		{
			povrightSpec(stdPower);
		}
	}
	if(location < destination && location % 2 == 0)
	{
		if(destination % 2 == 1)
		{
			povleft(stdPower, "cross");
		}
		else
		{
			povleftSpec(stdPower);
		}
	}
	if(location > destination && location % 2 == 1)
	{
		if(destination % 2 == 0)
		{
			povleft(stdPower, "cross");
		}
		else
		{
			povleftSpec(stdPower);
		}
	}
	stdPower = 25;
}

#endif
