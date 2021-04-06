#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     leftSensor,     sensorEV3_Color)
#include "hitechnic-colour-v2.h"
#include "WRO_Lib.h"
float /*e,es,eold,v=50,u,k1=0.2,k2=10,*/ t,ind1,ind2,ind3,ind4,ind5,ind6;

void stapt()
{
	nMotorEncoder[motorB]=0;
	while (SensorValue[S3]>20)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	if (nMotorEncoder[motorB]<140)
	{
		t=4;
	}
	if (nMotorEncoder[motorB]>140)
	{
		t=3;
	}
	if (nMotorEncoder[motorB]>210)
	{
		t=2;
	}
	stopmotor();
}
void info(short dom)
{
	tHTCS2 colorSensor;
	initSensor(&colorSensor, S4);
	readSensor(&colorSensor);
	while(colorSensor.color!=2&&colorSensor.color!=3&&colorSensor.color!=4&&colorSensor.color!=6)
	{
		readSensor(&colorSensor);
		motor[motorB]=25;
		motor[motorC]=-25;
	}
	stopmotor();
	if(dom==1)
	{
		ind1=colorSensor.color;
	}
	if(dom==2)
	{
		ind3=colorSensor.color;
	}
	if(dom==3)
	{
		ind5=colorSensor.color;
	}
	while(colorSensor.color>0)
	{
		readSensor(&colorSensor);
		motor[motorB]=40;
		motor[motorC]=-40;
	}
	stopmotor();
	nMotorEncoder[motorB]=0;
	while(colorSensor.color!=2&&colorSensor.color!=3&&colorSensor.color!=4&&colorSensor.color!=6)
	{
		readSensor(&colorSensor);
		motor[motorB]=25;
		motor[motorC]=-25;
		if(nMotorEncoder[motorB]>110)
		{
			break;
		}
	}
	move_enc(30, 20, 'f');
	if(dom==1)
	{
		ind2=colorSensor.color;
	}
	if(dom==2)
	{
		ind4=colorSensor.color;
	}
	if(dom==3)
	{
		ind6=colorSensor.color;
	}
}
task main()
{
	stapt();
	while (SensorValue[S1]>25)
	{
		motor[motorB]=v;
	}
	stopmotor();
	while (SensorValue[S1]<65)
	{
		motor[motorC]=-v;
	}
	while(SensorValue[S3]>20)
	{
		Line1();
	}
	move_enc(250, v, 'f');
	move_enc(260, 50, 'l');
	motor[motorB]=-50;
	motor[motorC]=50;
	wait10Msec(100);
	stopmotor();
	info(1);
	while(SensorValue[S1]>18)
	{
		motor[motorB]=25;
		motor[motorC]=-25;
	}
	wait10Msec(5);
	displayCenteredBigTextLine(3, "%d, %d",ind1,ind2);
	povleft();
	while(SensorValue[S1]>20)
	{
		Line();
	}
	povright();
	if(t==2)
	{
		while(SensorValue[S1]>20)
		{
			Line();
		}
		nMotorEncoder[motorB]=0;
		while(nMotorEncoder[motorB]<80)
		{
			Line();
		}
		while(SensorValue[S1]>20)
		{
			Line();
		}
		stopmotor();
		while(SensorValue[S2]>20)
		{
			motor[motorB]=-v;
			writeDebugStreamLine("%d", SensorValue[leftSensor]);
		}
		while(SensorValue[S2]<50)
		{
			motor[motorB]=-v;
			writeDebugStreamLine("%d", SensorValue[leftSensor]);
		}
		while(SensorValue[S2]>17)
		{
			motor[motorB]=-v;
		}
		while(SensorValue[S2]<50)
		{
			motor[motorB]=-v;
			writeDebugStreamLine("%d", SensorValue[leftSensor]);
		}
		stopmotor();
		wait10Msec(10);
		while(SensorValue[S3]>20)
		{
			motor[motorC]=-v;
			writeDebugStreamLine("%d", SensorValue[S2]);
		}
		stopmotor();
		nMotorEncoder[motorB]=0;
		move_enc(233, 25, 'b');
		motor[motorD]=-40;
		wait10Msec(110);
		motor[motorD]=0;
		move_enc(500, v, 'l');
		move_enc(240, 25, 'f');
		wait1Msec(50);
		motor[motorA]=-30;
		wait10Msec(70);
		motor[motorA]=0;
	}
	if(t==3)
	{
		motor[motorD]=100;
		while(SensorValue[S1]>20)
		{
			Line();
		}
		v=25;
		nMotorEncoder[motorB]=0;
		while(nMotorEncoder[motorB]<400)
		{
			Line();
		}
		v=50;
		stopmotor();
		nMotorEncoder[motorC]=0;
		while(nMotorEncoder[motorC]>-550)
		{
			motor[motorC]=-25;
		}
		stopmotor();
		move_enc(220, 25, 'b');
		motor[motorD]=-40;
		wait10Msec(200);
		nMotorEncoder[motorB]=0;
		move_enc(500, 25, 'l');
		move_enc(370, 20, 'f');
		motor[motorA]=-100;
		wait10Msec(100);
		motor[motorA]=0;
	}
	if(t==4)
	{
		nMotorEncoder[motorB]=0;
		while(nMotorEncoder[motorB]<180)
		{
			Line();
		}
		stopmotor();
		move_enc(275, 25, 'r');
		move_enc(200, 25, 'b');
		motor[motorD]=-40;
		wait10Msec(110);
		motor[motorD]=0;
		nMotorEncoder[motorB]=0;
		move_enc(500, v, 'l');
		nMotorEncoder[motorB]=0;
		move_enc(240, 25, 'f');
		wait1Msec(50);
		motor[motorA]=-30;
		wait10Msec(70);
		motor[motorA]=0;
	}
}
