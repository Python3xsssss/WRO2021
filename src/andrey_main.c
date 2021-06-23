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
	move_enc(100, zonePower, 'f', "");
//	startTask(hapugaC);
	Line1_enc(300, lineMaxPower, "");
	Line1S1Cross(stdPower, 'r', "stop");
}

void finish()
{
	move_to(0, "turn", "turn");

	Line_enc(100, stdPower, "");
	startTask(zahvatO);
	startTask(hapugaO);
	Line_enc(350, zonePower, "");
	LineCross(stdPower, "stop");
	moving(lineMaxPower, 'f');
	wait10Msec(100);
	stopmotor();
	move_enc(35, stdPower, 'b', "stop");
}

void mainProgram()
{
	stapt();
	checkDom1();
	take_ex_and_blue();
	//indDoms[0][0] = 1;
	//indDoms[0][1] = 0;
	//indDoms[1][0] = 1;
	//indDoms[1][1] = 0;
	//indDoms[2][0] = 2;
	//indDoms[2][1] = -1;
	//nInds[0] = 2;
	//nInds[1] = 2;
	//nInds[2] = 1;
	allocation(0);
	writeDebugStreamLine("Time after first allocation: %d sec", time1[T1] / 1000);
	approachToGreen();
	takeGreenZone();
	writeDebugStreamLine("Time after green zone: %d sec", time1[T1] / 1000);
	takeYellowZone();
	writeDebugStreamLine("Time after yellow zone: %d sec", time1[T1] / 1000);
	allocation(1);
	writeDebugStreamLine("Time after second allocation: %d", time1[T1] / 1000);
	finish();
	writeDebugStreamLine("Time: %d seconds", time1[T1] / 1000);
	while(true)
		wait10Msec(100);
}

task main()
{
	/*!!NE ZABIVAY INIT!!*/
	init();
	//startTask(hapugaC);
//	startTask(zahvatC);
	wait1Msec(1500);
	clearTimer(T1);
	clearDebugStream();
	mainProgram();
//	approachToBlue();
	takeBlueZone();
}
