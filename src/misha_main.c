#pragma config(Sensor, S1,     ,               sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     leftSensor,     sensorEV3_Color)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorEV3_Medium, PIDControl, encoder)

#include "WRO_Lib.h"
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

task main()
{
	zahvat('c');
	hapuga('c');
	indDoms[0][0]=0;
	indDoms[0][1]=1;
	indDoms[1][0]=0;
	indDoms[1][1]=-1;
	indDoms[2][0]=2;
	indDoms[2][1]=1;
	bricksInRobot[0]=-1;
	bricksInRobot[1]=0;
	bricksInRobot[2]=-1;
	bricksInRobot[3]=0;
	init();
	location = 8;
	allocation(0);


}
