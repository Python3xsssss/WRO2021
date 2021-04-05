#pragma config(Sensor, S4,     ,               sensorEV3_Color, modeEV3Color_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float e,es,eold,v=50,u,k1=0.2,k2=10,t,ind1,ind2,ind3,ind4,ind5,ind6,s4;
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
void povright()
{
	nMotorEncoder[motorB]=0;
	while (nMotorEncoder[motorB]<60)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	stopmotor();
	nMotorEncoder[motorB]=0;
	while (nMotorEncoder[motorB]>-100)
	{
		motor[motorB]=-v;
		motor[motorC]=-v;
	}
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
	nMotorEncoder[motorB]=0;
	while (nMotorEncoder[motorB]<60)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	stopmotor();
	nMotorEncoder[motorB]=0;
	while (nMotorEncoder[motorB]<100)
	{
		motor[motorB]=v;
		motor[motorC]=v;
	}
	while (SensorValue[S3]>10)
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
	while(SensorValue[S4]==0)
	{
		motor[motorB]=25;
		motor[motorC]=-25;
	}
	stopmotor();
	if(dom==1)
	{
		ind1=SensorValue[S4];
	}
	if(dom==2)
	{
		ind3=SensorValue[S4];
	}
	if(dom==3)
	{
		ind5=SensorValue[S4];
	}
	while(SensorValue[S4]>0)
	{
		motor[motorB]=40;
		motor[motorC]=-40;
	}
	stopmotor();
	nMotorEncoder[motorB]=0;
	while(SensorValue[S4]==0||SensorValue[S4]==1)
	{
		motor[motorB]=25;
		motor[motorC]=-25;
		if(nMotorEncoder[motorB]>110)
		{
			break;
		}
	}
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<30)
	{
		motor[motorB]=20;
		motor[motorC]=-20;
	}
	if(dom==1)
	{
		ind2=SensorValue[S4];
	}
	if(dom==2)
	{
		ind4=SensorValue[S4];
	}
	if(dom==3)
	{
		ind6=SensorValue[S4];
	}
	stopmotor();
}
task main()
{
	//stapt();
	//while (SensorValue[S1]>25)
	//{
	//	motor[motorB]=v;
	//}
	//stopmotor();
	//while (SensorValue[S1]<65)
	//{
	//	motor[motorC]=-v;
	//}
	//while(SensorValue[S3]>20)
	//{
	//	Line1();
	//}
	//nMotorEncoder[motorB]=0;
	//while (nMotorEncoder[motorB]<250)
	//{
	//	motor[motorB]=v;
	//	motor[motorC]=-v;
	//}
	//stopmotor();
	//nMotorEncoder[motorB]=0;
	//while(nMotorEncoder[motorB]<260)
	//{
	//	motor[motorB]=50;
	//	motor[motorC]=50;
	//}
	//stopmotor();
	//motor[motorB]=-50;
	//motor[motorC]=50;
	//wait10Msec(100);
	//stopmotor();
	//info(1);
	//while(SensorValue[S1]>18)
	//{
	//	motor[motorB]=25;
	//	motor[motorC]=-25;
	//}
	//displayCenteredBigTextLine(3, "%d, %d",ind1,ind2);
	//povleft();
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
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]>-220)
	{
		motor[motorB]=-25;
		motor[motorC]=25;
	}
	stopmotor();
	motor[motorD]=-40;
	wait10Msec(200);
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<500)
	{
		motor[motorB]=25;
		motor[motorC]=25;
	}
	stopmotor();
 	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<370)
	{
		motor[motorB]=20;
		motor[motorC]=-20;
	}
		motor[motorA]=-100;
		wait10Msec(100);
	}
