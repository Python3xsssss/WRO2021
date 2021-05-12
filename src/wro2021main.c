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
	povleft(stdPower, "cross");
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
	location = 7;
	hapuga('d');
	allocation(0);
	//stapt();
	//mainProgram();
	writeDebugStreamLine("Time: %d", time1[T1] / 1000);
	//for(short i=0; i<3; i++)
	//{
	//	for(short j=0; j<4; j++)
	//	{
	//		writeDebugStream("%d ", finalRazvoz[i][j]);
	//	}
	//}

}
