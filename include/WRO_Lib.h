#pragma config(Sensor, S1,     ,               sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     leftSensor,     sensorEV3_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma once

#include "hitechnic-colour-v2.h"

#ifndef TESTLIB_H
#define TESTLIB_H
float e,es,eold,v,u,k1,k2; //variables for functions Line and Line1
void Line()
{
	es=SensorValue[S2]-SensorValue[S3];
	e=SensorValue[S2]-SensorValue[S3]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(v+u);
	motor[motorC]=(-v+u);
}

void Line1()
{
	es=SensorValue[S1]-SensorValue[S2];
	e=SensorValue[S1]-SensorValue[S2]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(v+u);
	motor[motorC]=(-v+u);
}

void stopmotor()
{
	motor[motorB]=0;
	motor[motorC]=0;
	wait10Msec(10);
}

void move_enc(float enc, float v1, char dir)
{
	nMotorEncoder[motorB]=0;
	if(dir=='f')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			motor[motorB]=v1;
			motor[motorC]=-v1;
		}
		stopmotor();
	}
	if(dir=='b')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			motor[motorB]=-v1;
			motor[motorC]=v1;
		}
	}
	if(dir=='l')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			motor[motorB]=v1;
			motor[motorC]=v1;
		}
	}
	if(dir=='r')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			motor[motorB]=-v1;
			motor[motorC]=-v1;
		}
	}
	stopmotor();
}

void povright()
{
	move_enc(70, v, 'f');
	move_enc(100, v, 'r');
	while (SensorValue[S2]>10)
	{
		motor[motorB]=-v;
		motor[motorC]=-v;
	}
	while (SensorValue[S2]<40)
	{
		motor[motorB]=-v;
		motor[motorC]=-v;
	}
	stopmotor();
}

void povleft()
{
	move_enc(70, v, 'f');
	move_enc(100, v, 'l');
	while (SensorValue[S3]>20)
	{
		motor[motorB]=v;
		motor[motorC]=v;
	}
	while (SensorValue[S3]<40)
	{
		motor[motorB]=v;
		motor[motorC]=v;
	}
	stopmotor();
}

void LineRed()
{
	getColorName(S1);
	while(getColorName(S1)!=5)
	{
		Line();
	}
	getColorReflected(S1);
}

void LineCross()
{
	while(SensorValue[S1]>20)
	{
		Line();
	}
	stopmotor();
}

void Line1Cross()
{
	while(SensorValue[S3]>20)
	{
		Line1();
	}
	stopmotor();
}

void Line_enc(float enc2)
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<enc2)
	{
		Line();
	}
	stopmotor();
}

void goBlack(short SensorPort)
{
	if(SensorPort==1)
	{
		while(SensorValue[S1]>15)
		{
			motor[motorB]=v;
			motor[motorC]=-v;
		}
		stopmotor();
	}
	if(SensorPort==2)
	{
		while(SensorValue[S2]>15)
		{
			motor[motorB]=v;
			motor[motorC]=-v;
		}
		stopmotor();
	}
	if(SensorPort==3)
	{
		while(SensorValue[S3]>15)
		{
			motor[motorB]=v;
			motor[motorC]=-v;
		}
		stopmotor();
	}
}

void goColor()
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
}
//void info(short dom)
//{
//	tHTCS2 colorSensor;
//	initSensor(&colorSensor, S4);
//	readSensor(&colorSensor);
//	while(colorSensor.color!=2&&colorSensor.color!=3&&colorSensor.color!=4&&colorSensor.color!=6)
//	{
//		readSensor(&colorSensor);
//		motor[motorB]=25;
//		motor[motorC]=-25;
//	}
//	stopmotor();
//	if(dom==1)
//	{
//		ind1=colorSensor.color;
//	}
//	if(dom==2)
//	{
//		ind3=colorSensor.color;
//	}
//	if(dom==3)
//	{
//		ind5=colorSensor.color;
//	}
//	while(colorSensor.color>0)
//	{
//		readSensor(&colorSensor);
//		motor[motorB]=40;
//		motor[motorC]=-40;
//	}
//	stopmotor();
//	nMotorEncoder[motorB]=0;
//	while(colorSensor.color!=2&&colorSensor.color!=3&&colorSensor.color!=4&&colorSensor.color!=6)
//	{
//		readSensor(&colorSensor);
//		motor[motorB]=25;
//		motor[motorC]=-25;
//		if(nMotorEncoder[motorB]>110)
//		{
//			break;
//		}
//	}
//	nMotorEncoder[motorB]=0;
//	while(nMotorEncoder[motorB]<30)
//	{
//		motor[motorB]=20;
//		motor[motorC]=-20;
//	}
//	if(dom==1)
//	{
//		ind2=colorSensor.color;
//	}
//	if(dom==2)
//	{
//		ind4=colorSensor.color;
//	}
//	if(dom==3)
//	{
//		ind6=colorSensor.color;
//	}
//	stopmotor();
//}

#endif
