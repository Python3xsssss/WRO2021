#pragma config(Sensor, S1,     ,               sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     leftSensor,     sensorEV3_Color)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorEV3_Medium, PIDControl, encoder)

#include "WRO_Lib.h"
#include "Collect.h"
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
	move_enc(240, stdPower, 'f', "");
	Line1Cross(zonePower, "");
	//povleft(stdPower, "cross");
}

void finish()
{
	motor[motorD]=-50;
	motor[motorA]=50;
	if(location == 5)
		move_to(4, "turn", "");

	if(location == 4)
	{
		Line_enc(100, stdPower, "");
		Line_enc(1750, lineMaxPower, "");
		LineCross(stdPower, "stop");
	}

	else
		move_to(0, "turn", "");

	//move_enc(TURN-18, stdPower, 'r', "stop");
	povright(stdPower, "cross");
	LineCross(stdPower, "stop");
	mot1_enc(50, 'b', stdPower, 'f', "stop");
	mot1_enc(50, 'c', stdPower, 'f', "stop");
	moving(lineMaxPower, 'f');
	wait10Msec(100);
	stopmotor();
	move_enc(35, stdPower, 'b', "stop");

	while(true)
	{
		wait10Msec(100);
	}
}

void mainProgram()
{
	stapt();
	take_ex_and_blue();
	//allocateAllBricks();
	//finish();
}

task main()
{
	/*!!NE ZABIVAY INIT!!*/
	clearTimer(T1);
	clearDebugStream();
	init();
	mainProgram();
	writeDebugStreamLine("Time: %d seconds", time1[T1] / 1000);

}
