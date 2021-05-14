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

void finish()
{
	//finish ne rabotaet,
	//tk po priezdu v dom = 0 bez kubikov mi povorachivaem k domu,
	//a esli mi vigruzili poslednie cubiki v etom dome, to mi doezhaem do perekrestka s glavnoy liniey i smotrim perpendikularno ey
	//popravit', esli voobshe finish budem uspevat. Esli net, to udalit' ego iz progi.
	mot1_enc(ONEMOTORTURN * 80 / 90, 'c', zonePower, 'f', "stop");
	move_enc(1000, lineMaxPower, 'f', "stop");
}


void mainProgram()
{
	init();
	stapt();
	checkAllField();
	allocateAllBricks();
	//finish();
}

task main()
{
	clearTimer(T1);
	clearDebugStream();
	mainProgram();
	writeDebugStreamLine("Time: %d seconds", time1[T1] / 1000);
}
