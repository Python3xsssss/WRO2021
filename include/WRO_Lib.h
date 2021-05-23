#pragma once

#ifndef TESTLIB_H
#define TESTLIB_H

#include "hitechnic-colour-v2.h"

#define BLACK 15
#define WHITE 57
#define GREY 40
#define TURN 253
#define TURNAROUND 505
#define ONEMOTORTURN 505
#define CROSS_ENC 90
#define SPEC_CROSS_L 25
#define SPEC_CROSS_R 150
#define HAPUGAM 25
#define ZAHVATG 30
#define HAPUGAG 64
//#define LINETOLINE 200

short pauseCounter = 0;
short stdPower, lineMaxPower, zonePower;
short location, old_location;
short sensors = 0;
short indDoms[3][2] = {{-1,-1}, {-1,-1}, {-1,-1}}; // indDoms[0][0] - color index of first indicator in first dom, etc.
short nInds[3] = {0, 0, 0}; // nInds[0] - num of blue indicators, etc.
short bricksInRobot[4] = {-2, -2, -2, -2}; // bricksInRobot[0] - color index of bricks in hapuga, [1] - on hapuga, [2] - in zahvat, [3] - on zahvat
short finalRazvoz[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
short exColor;
short zahvatPos = 0, hap = 2;
string ifCrossAkkum = "cross";
short nEncB = 0;
short nEncC = 0;
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
	motor[motorB]=(speed + u)*0.97;
	motor[motorC]=(-speed + u)*1.03;
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
	wait10Msec(20);
	pauseCounter++;
}

void moving(short speed, char dir)
{
	if(dir=='f')
	{
		motor[motorB]=(speed >= zonePower) ? speed* 0.95 : speed;
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
			moving(speed, 'f');
		}
	}
	if(dir=='b')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			moving(speed, 'b');
		}
	}
	if(dir=='l')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			moving(speed, 'l');
		}
	}
	if(dir=='r')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			moving(speed, 'r');
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
	while(SensorValue[S1]<WHITE+3)
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
	moving(speed, 'f');
	readSensor(&colorSensor);
	while(colorSensor.color>0)
	{
		readSensor(&colorSensor);
	}
	nMotorEncoder[motorB]=0;
	while(colorSensor.color != 2 && colorSensor.color != 3 && colorSensor.color != 4 && colorSensor.color != 6)
	{
		readSensor(&colorSensor);
		if (SensorValue[S2] < BLACK && SensorValue[S3] < BLACK || nMotorEncoder[motorB] >= nEnc)
		{
			return false;
		}
	}
	return true;
}

bool back_pass_color(short nEnc, short speed)
{
	moving(speed, 'b');
	readSensor(&colorSensor);
	while(colorSensor.color > 0)
	{
		readSensor(&colorSensor);
	}

	nMotorEncoder[motorB]=0;
	while(colorSensor.color != 2 && colorSensor.color != 3 && colorSensor.color != 4 && colorSensor.color != 6)
	{
		readSensor(&colorSensor);
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

void hapuga(char dir)
{
	short speed;
	if(bricksInRobot[1] > -2)
	{
		speed = 16;
	}
	else
	{
		speed = 30;
	}
	if(dir=='u' && hap != 2)
	{
		motor[motorA]=speed;
		wait10Msec(1000/speed);
		hap = 2;
	}
	if(dir=='d' && hap != 0)
	{
		motor[motorA]=-speed;
		wait10Msec(2000/speed);
		hap = 0;
	}
	if(dir == 'm' && hap != 1)
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
		speed = 14;
	}
	else
	{
		speed = 40;
	}

	nMotorEncoder[motorD]=0;
	if(dir=='c')
	{
		if(zahvatPos != 0)
		{
			motor[motorD]=-speed;
			wait10Msec((3000 + 500 * zahvatPos)/speed);
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

task zahvatM()
{
	zahvat('m');
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
	move_enc(TURNAROUND+25, speed, 'l', "stop");
	move_enc(200, speed, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND+38, stdPower, 'r', "stop");
	bricksInRobot[0] = -2; bricksInRobot[2] = -1;
}

void akkumGB()
{
	if(ifCrossAkkum == "cross")
	{
		move_enc(CROSS_ENC, stdPower, 'f', "");
	}
	move_enc(38, stdPower, 'f', "stop");
	wait1Msec(250);
	motor[motorA]=-35;
	wait1Msec(500);
	motor[motorA]=0;
	while(SensorValue[S2] > BLACK)
	{
		moving(stdPower, 'b');
	}
	move_enc(40, stdPower, 'f', "stop");
	hap = 1;
	hapuga('u');
	bricksInRobot[1] = -2;
	for(short i = 0; i < 4; i++)
		finalRazvoz[3][i] = 0;
	writeDebugStreamLine("Time after akkum: %d sec", time1[T1] / 1000);
}

void akkum_std()
{
	if(hap == 2 && bricksInRobot[0] != -2)
	{
		hapuga('d');
		startTask(hapugaM);
	}
	stopmotor();
	if(ifCrossAkkum == "cross")
	{
		move_enc(TURNAROUND, stdPower, 'l', "stop");
		move_enc(CROSS_ENC, stdPower, 'b', "");
	}
	move_enc(110, stdPower, 'b', "stop");
	zahvat('o');
	startTask(zahvatC);
	wait1Msec(750);
	fwd_black(1, stdPower, "stop"); //"" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	bricksInRobot[2] = -2;
	for(short i = 0; i < 4; i++)
		finalRazvoz[3][i] = 0;
	writeDebugStreamLine("Time after akkum: %d sec", time1[T1] / 1000);
}

void crosses(short destination, const string ifStop)
{
	if(location == destination)
	{
		return;
	}
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
	move_enc(SPEC_CROSS_R, speed, 'f', "stop");
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
	move_enc(SPEC_CROSS_L, speed, 'f', "stop");
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
}

#endif
