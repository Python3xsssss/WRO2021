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
	v=25;
	k1=0.2;
	k2=10;
	initSensor(&colorSensor, S4);
}

void stapt()
{
	motor[motorD]=-25;
	move_enc(240, v, 'f', "");
	Line1Cross(v, "");
}
/*
void batarei()
{
LineCross();
povright();
Line_enc(250);
move_enc(TURN,v,'l');
move_enc(200,v,'f');
hapuga('d');
move_enc(TURN,v,'l');
move_enc(100,v,'b');
hapuga('u');
move_enc(200,v,'b');
move_enc(TURN,v,'l');
while (SensorValue[S1]<WHITE)
{
motor[motorB]=v;
motor[motorC]=-v;
}
while (SensorValue[S1]>BLACK+20)
{
motor[motorB]=v;
motor[motorC]=-v;
}
move_enc(20, v, 'f');
povright();
while(SensorValue[S3]<WHITE)
{
Line1();
}
while(SensorValue[S3]>BLACK+20)
{
Line1();
}
move_enc(200,v,'f');
move_enc(TURN,v,'r');
move_enc(333,v,'f');
hapuga('d');
move_enc(TURN,v,'r');
move_enc(135,v,'b');
hapuga('u');
move_enc(270,v,'b');
}*/

task main()
{
	v=25; k1=0.2; k2=2;
	init();
	//stapt();
	//checkAllField();
	//allocateAllBricks();
	hapuga('d');
	location = 8;
	allocation(1);
}
