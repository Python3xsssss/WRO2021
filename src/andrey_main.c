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
	move_to(0, "turn", "turn");

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
}

task main()
{
	/*!!NE ZABIVAY INIT!!*/
	//init();
	//zahvat('c');
	//hapuga('c');
	wait1Msec(1000);
	clearTimer(T1);
	clearDebugStream();
	//mainProgram();
	indDoms[0][0] = 1;
	indDoms[0][1] = 0;
	indDoms[1][0] = 1;
	indDoms[1][1] = 0;
	indDoms[2][0] = 2;
	indDoms[2][1] = -1;
	bricksInRobot[0] = 2;
	bricksInRobot[1] = 1;
	bricksInRobot[2] = 2;
	bricksInRobot[3] = 1;
	nInds[1] = 2;
	calculation(1);
	for(short i = 0; i < 4; i++)
	{
		for(short j = 0; j < 4; j++)
		{
			writeDebugStream("%d ", finalRazvoz[i][j]);
		}
		writeDebugStream("\n");
	}
	writeDebugStreamLine("ourWay ");
	for(short i = 0; i < 4; i++)
		writeDebugStream("%d", ourWay[i]);
	writeDebugStreamLine("");
	writeDebugStreamLine("Time: %d seconds", time1[T1] / 1000);

}
