#pragma config(Sensor, S1,     ,               sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     leftSensor,     sensorEV3_Color)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorEV3_Medium, PIDControl, encoder)

#include "Init.h"
#include "WRO_Lib.h"
#include "Collect.h"
#include "Allocate.h"

void stapt()
{
	move_enc(50, stdPower, 'f', "");
	move_enc(150, zonePower, 'f', "");
	startTask(hapugaC);
	Line1Cross(lineMaxPower, "");
}

void finish()
{
	move_to(4, "turn", "turn");

	Line_enc(100, stdPower, "");
	startTask(zahvatO);
	startTask(hapugaO);
	Line_enc(350, zonePower, "");
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
	allocateAllBricks();
	finish();
}

task main()
{
	/*!!NE ZABIVAY INIT!!*/
	init();
	zahvat('c');
	hapuga('c');
	clearTimer(T1);
	clearDebugStream();
	//mainProgram();
	location = 8;
	bricksInRobot[0] = 2;
	bricksInRobot[1] = 1;
	bricksInRobot[2] = 2;
	bricksInRobot[3] = 1;
	indDoms[0][0] = 0;
	indDoms[0][1] = 1;
	indDoms[1][0] = 0;
	indDoms[1][1] = 1;
	indDoms[2][0] = 2;
	indDoms[2][1] = -1;
	nInds[0] = 2;
	nInds[1] = 2;
	nInds[2] = 1;
	allocation(1);
	writeDebugStreamLine("Time: %d seconds", time1[T1] / 1000);

}
