#pragma config(Sensor, S1,     ,               sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     leftSensor,     sensorEV3_Color)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorEV3_Medium, PIDControl, encoder)

#include "WRO_Lib.h"
#include "Check.h"
#include "Allocate.h"

void init()
{
	stdPower=25;
	lineMaxPower=60;
	zonePower=40;
	//k1=0.2;
	//k2=10;
	initSensor(&colorSensor, S4);
}

void stapt()
{
	motor[motorD]=-25;
	move_enc(240, stdPower, 'f', "");
	Line1Cross(zonePower, "");
	//povleft(stdPower, "cross");
}

void mainProgram()
{
	stapt();
	checkAllField();
	allocateAllBricks();
}

task main()
{
	clearTimer(T1);
	clearDebugStream();
	init();
	location = 8;
	//move_to(2, "turn", "turn");
	//takeYellowZone();
	bricksInRobot[0] = 2; bricksInRobot[2] = 2; bricksInRobot[1] = -2; bricksInRobot[3] = -2;
	indDoms[0][0] = 1; indDoms[0][1] = 0;
	indDoms[1][0] = 1; indDoms[1][1] = -1;
	indDoms[2][0] = 2; indDoms[2][1] = 0;
	nInds[2] = 1;
	hapuga('d');
	allocation(1);
	//stapt();
	//checkDom1();
	//checkExcess();
	//mainProgram();
	writeDebugStreamLine("Time: %d", time1[T1] / 1000);
}
