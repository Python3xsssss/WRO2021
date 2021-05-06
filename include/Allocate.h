#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H
//short orientation, location;
short polozhenie=2;
int rightWay[2][4] = {{2, 1, 3, 0}, {1, 2, 3, 0}};
int ourWay[4] = {-1, -1, -1, -1};
int finalRazvoz[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
/*
short sw;
switch (sw)
{
case 1:
//do smth
break;
case 2:
//do smth
break;
case 3:
//do smth
break;
default:
//do smth
break;
}
*/

task hapugaU()
{
	hapuga('u');
}

task zahvatC()
{
	zahvat('c');
}

void putInDom(short zahvat1, short hapuga1, short zahvat2, short hapuga2)
{
	v=25; k1=0.2; k2=1;
	if(hapuga2 == 1 && hapuga1 != 1)
	{
		hapuga('d');
	}
	LineRed(v, "");
	if(hapuga1 == 1)
	{
		move_enc(30, v, 'f', "stop");
	}
	if(hapuga2 == 1 && hapuga1 != 1)
	{
		startTask(hapugaU);
	}
	move_enc(150, v, 'b', "stop");
	if(hapuga2 == 1 && hapuga1 == 1)
	{
		hapuga('d');
		LineRed(v, "stop");
		move_enc(100, v, 'b', "stop");
	}
	move_enc(TURNAROUND, v, 'r', "stop");
	if(zahvat1 == 1 && zahvat2 != 1 || zahvat1 != 1 && zahvat2 == 1)
	{
		if(zahvat2 == 1)
		{
			zahvat('d');
		}
		move_enc(170, v, 'b', "stop");
		if(zahvat1 == 1)
		{
			zahvat('o');
		}
		move_enc(50, v, 'f', "");
		startTask(zahvatC);
	}
	if(zahvat1 == 1 && zahvat2 == 1)
	{
		zahvat('o');
		move_enc(170, v, 'b', "stop");
		move_enc(100, v, 'f', "stop");
		zahvat('d');
		move_enc(100, v, 'b', "stop");
		move_enc(50, v, 'f', "");
		startTask(zahvatC);
	}
	LineCross(v, "stop");
}


void calculation(short col)
{
	short i1, i2;
	if(nInds[col] == 1)
	{
		bricksInRobot[3]=-2;
	}
	if(col==1)
	{
		if(nInds[col+1] == 1)
		{
			bricksInRobot[1]=-2;
		}
	}
	for(short i=0; i < 4; i++)
	{
		i1 = 0; i2 = 0;
		if(rightWay[col][i] != 3)
		{
			if(indDoms[rightWay[col][i]][0]==col||indDoms[rightWay[col][i]][1]==col||indDoms[rightWay[col][i]][0]==-1&&col==0||indDoms[rightWay[col][i]][1]==-1&&col==0||indDoms[rightWay[col][i]][0]==2&&col==1||indDoms[rightWay[col][i]][1]==2&&col==1)
			{
				ourWay[i] = rightWay[col][i];
				for(i1=0; i1<4; i1++)
				{
					if(indDoms[rightWay[col][i]][0] == bricksInRobot[i1])
					{
						break;
					}
				}
				for(i2=0; i2<4; i2++)
				{
					if(indDoms[rightWay[col][i]][1] == bricksInRobot[i2])
					{
						break;
					}
				}
				if(i1 == 4 || i2 == 4)
				{
					for(short i3=0; i3 < 4; i3++)
					{
						if(bricksInRobot[i3] == indDoms[rightWay[col][i]][0] || bricksInRobot[i3] == indDoms[rightWay[col][i]][1])
						{
							finalRazvoz[rightWay[col][i]][i3] = 1;
							bricksInRobot[i3] = -2;
							break;
						}
					}
				}
				else
				{
					for(short i3=0; i3 < 4; i3++)
					{
						if(bricksInRobot[i3] == indDoms[rightWay[col][i]][0])
						{
							finalRazvoz[rightWay[col][i]][i3] = 1;
							bricksInRobot[i3] = -2;
							break;
						}
					}
					for(short i3=0; i3 < 4; i3++)
					{
						if(bricksInRobot[i3] == indDoms[rightWay[col][i]][1])
						{
							finalRazvoz[rightWay[col][i]][i3] = 1;
							bricksInRobot[i3] = -2;
							break;
						}
					}
				}
			}
		}
		if(nInds[col] == 1 && rightWay[col][i] == 3)
		{
			finalRazvoz[3][3] = 1;
		}
		if(col==1)
		{
			if(nInds[col+1] == 1 && rightWay[col][i] == 3)
			{
				finalRazvoz[3][1] = 1;
			}
		}
	}
}

//void calculationGrYe()
//{
//	short i1, i2;
//	ourWay[0] = -1; ourWay[1] = -1; ourWay[2] = -1; ourWay[3] = -1;
//	if(nInds[1] == 1)
//	{
//		bricksInRobot[3] = -2;
//	}
//	for(short i=0; i < 4; i++)
//	{
//		writeDebugStreamLine("waygrye = %d", wayGrYe[i]);
//		i1=0; i2=0;
//		if(wayGrYe[i] != 3)
//		{
//			if(indDoms[wayGrYe[i]][0] == 1 || indDoms[wayGrYe[i]][1] == 1 || indDoms[wayGrYe[i]][0] == 2 || indDoms[wayGrYe[i]][1] == 2)
//			{
//				ourWay[i] = wayGrYe[i];
//				for(i1=0; i1<4; i1++)
//				{
//					if(indDoms[wayGrYe[i]][0] == bricksInRobot[i1])
//					{
//						break;
//					}
//				}
//				for(i2=0; i2<4; i2++)
//				{
//					if(indDoms[wayGrYe[i]][1] == bricksInRobot[i2])
//					{
//						break;
//					}
//				}
//				if(i1 == 4 || i2 == 4)
//				{
//					for(short i3=0; i3 < 4; i3++)
//					{
//						if(bricksInRobot[i3] == indDoms[wayGrYe[i]][0] || bricksInRobot[i3] == indDoms[wayGrYe[i]][1])
//						{
//							finalRazvozGrYe[i][i3] = 1;
//							//writeDebugStreamLine("zona %d: %d, %d, %d, %d", wayGrYe[i]+1, finalRazvozGrYe[wayGrYe[i]][0], finalRazvozGrYe[wayGrYe[i]][1], finalRazvozGrYe[wayGrYe[i]][2], finalRazvozGrYe[wayGrYe[i]][3]);
//							bricksInRobot[i3] = -2;
//							break;
//						}
//					}
//				}
//				else
//				{
//					for(short i3=0; i3 < 4; i3++)
//					{
//						if(bricksInRobot[i3] == indDoms[wayGrYe[i]][0])
//						{
//							finalRazvozGrYe[i][i3] = 1;
//							//writeDebugStreamLine("zona %d: %d, %d, %d, %d", wayGrYe[i]+1, finalRazvozGrYe[wayGrYe[i]][0], finalRazvozGrYe[wayGrYe[i]][1], finalRazvozGrYe[wayGrYe[i]][2], finalRazvozGrYe[wayGrYe[i]][3]);
//							bricksInRobot[i3] = -2;
//							break;
//						}
//					}
//					for(short i3=0; i3 < 4; i3++)
//					{
//						if(bricksInRobot[i3] == indDoms[wayGrYe[i]][1])
//						{
//							finalRazvozGrYe[i][i3] = 1;
//							//writeDebugStreamLine("zona %d: %d, %d, %d, %d", wayGrYe[i]+1, finalRazvozGrYe[wayGrYe[i]][0], finalRazvozGrYe[wayGrYe[i]][1], finalRazvozGrYe[wayGrYe[i]][2], finalRazvozGrYe[wayGrYe[i]][3]);
//							bricksInRobot[i3] = -2;
//							break;
//						}
//					}
//				}
//			}
//			if(nInds[1] == 1 && wayGrYe[i] == 3)
//			{
//				ourWay[i] = wayGrYe[i];
//				finalRazvozGrYe[i][3] = 1;
//				//writeDebugStreamLine("zona %d: %d, %d, %d, %d", wayGrYe[i]+1, finalRazvozGrYe[wayGrYe[i]][0], finalRazvozGrYe[wayGrYe[i]][1], finalRazvozGrYe[wayGrYe[i]][2], finalRazvozGrYe[wayGrYe[i]][3]);
//			}
//			if(nInds[2] == 1 && wayGrYe[i] == 3)
//			{
//				ourWay[i] = wayGrYe[i];
//				finalRazvozGrYe[i][1] = 1;
//				//writeDebugStreamLine("zona %d: %d, %d, %d, %d", wayGrYe[i]+1, finalRazvozGrYe[wayGrYe[i]][0], finalRazvozGrYe[wayGrYe[i]][1], finalRazvozGrYe[wayGrYe[i]][2], finalRazvozGrYe[wayGrYe[i]][3]);
//			}
//			writeDebugStreamLine("waygrye = %d", wayGrYe[i]);
//		}
//	}
//}

void RazvoznBlue()
{
	hapuga('u');
	calculation(0);
	if (finalRazvoz[0][0] == 1 || finalRazvoz[0][1] == 1 || finalRazvoz[0][2] == 1 || finalRazvoz[0][3] == 1)
	{

	}
	else
	{
		move_enc(TURNAROUND, v, 'r', "stop");
	}
	while (SensorValue[S1]<35)
	{
		moving(v, 'f');
	}
	fwd_black(1, v, "");
	povright(v, "cross");


}

//void RazvoznGrYe()
//{
//	hapuga('u');
//	calculationGrYe();


//}

//void AllocateAllBricks()
//{
//	takeBlueZone();
//	RazvoznBlue();
//	takeGreenZone();
//	RazvoznGreen();
//	takeYellowZone();
//}

//void takeBlueZone()
//{
//	fwd_white(v, "");
//	//while (SensorValue[S1]<WHITE)
//	//{
//	//	motor[motorB]=v;
//	//	motor[motorC]=-v;
//	//}
//	while (SensorValue[S1]>40)
//	{
//		motor[motorB]=v;
//		motor[motorC]=-v;
//	}
//	stopmotor();
//	while (SensorValue[S1]<WHITE)
//	{
//		motor[motorB]=v;
//	}
//	while (SensorValue[S1]>40)
//	{
//		motor[motorB]=v;
//	}
//	nMotorEncoder[motorB]=0;
//	while(nMotorEncoder[motorB]<350)
//	{
//		Line2();
//	}
//	while(SensorValue[S3]<WHITE)
//	{
//		Line2();
//	}
//	while(SensorValue[S3]<BLACK)
//	{
//		Line2();
//	}
//	nMotorEncoder[motorB]=0;
//	while(nMotorEncoder[motorB]<270)
//	{
//		Line2();
//	}
//	move_enc(230, v, 'r');
//	//nMotorEncoder[motorB]=0;
//	//while(nMotorEncoder[motorB]>-230)
//	//{
//	//	motor[motorB]=-v;
//	//	motor[motorC]=-v;
//	//}
//	//nMotorEncoder[motorB]=0;
//	move_enc(230, v, 'b');
//	//while(nMotorEncoder[motorB]>-230)
//	//{
//	//	motor[motorB]=-v;
//	//	motor[motorC]=v;
//	//}
//	//stopmotor();
//	motor[motorA]=-100;
//	wait10Msec(30);
//	motor[motorA]=0;
//	while(SensorValue[S1]<WHITE)
//	{
//		motor[motorB]=v;
//		motor[motorC]=-v;
//	}
//	while(SensorValue[S1]>BLACK)
//	{
//		motor[motorB]=v;
//		motor[motorC]=-v;
//	}
//	wait1Msec(10);
//	stopmotor();
//	motor[motorA]=20;
//	wait10Msec(50);
//	motor[motorA]=0;
//	mot1_enc(ONEMOTORTURN, 'b', 'b');
//	motor[motorA]=-20;
//	wait10Msec(50);
//	motor[motorA]=0;
//	move_enc(150, v, 'b');
//	motor[motorA]=20;
//	wait10Msec(50);
//	motor[motorA]=0;
//	while(SensorValue[S3]<WHITE)//65
//	{
//		motor[motorB]=v;
//		motor[motorC]=-v;
//	}
//	motor[motorA]=-20;
//	goBlack(3);
//	move_enc(230, v, 'f');
//	motor[motorA]=0;
//	move_enc(230, v, 'l');
//	while(SensorValue[S1]<WHITE)
//	{
//		motor[motorB]=v;
//		motor[motorC]=-v;
//	}
//	while(SensorValue[S1]>BLACK)
//	{
//		motor[motorB]=v;
//		motor[motorC]=-v;
//	}
//	wait1Msec(30);
//	stopmotor();
//	motor[motorA]=20;
//	wait10Msec(35);
//	motor[motorA]=0;
//	mot1_enc(ONEMOTORTURN, 'b', 'b');
//}

//void takeGreenZone()
//{
//	if(polozhenie==2)
//	{
//		while(SensorValue[S1]<WHITE)
//		{
//			Line();
//		}
//		LineCross();
//		move_enc(TURN, v, 'l');
//		move_enc(90, v, 'b');
//		hapuga('d');
//		goBlack(2);
//	}
//	if(polozhenie==1)
//	{
//		mot1_enc(200, 'b', 'f');
//		mot1_enc(180, 'c', 'f');
//		Line1Cross();
//		nMotorEncoder[motorB]=0;
//		while(nMotorEncoder[motorB]<80)
//		{
//			Line1();
//		}
//		while(SensorValue[S3]>27)
//		{
//			Line1();
//		}
//		stopmotor();
//		move_enc(TURN, v, 'r');
//		move_enc(70, v, 'b');
//		hapuga('d');
//		goBlack(2);
//	}
//	nMotorEncoder[motorA]=0;
//	while(nMotorEncoder[motorA]<35)
//	{
//		motor[motorA]=25;
//	}
//	motor[motorA]=0;
//	move_enc(130, v, 'f');
//	hapuga('u');
//	while(SensorValue[S2]>BLACK)
//	{
//		moving(v, 'b');
//	}
//	stopmotor();
//	povleft();
//	LineCross();
//	zahvat('c');
//	Line_enc(240);
//	move_enc(TURN, v, 'l', "stop");
//	move_enc(200, v, 'b', "stop");
//	hapuga('d');
//	move_enc(150, v, 'b',, "stop");
//	hapuga('u');
//	goBlack(3, v);
//	hapuga('d');
//	wait10Msec(10);
//	nMotorEncoder[motorA]=0;
//	while(nMotorEncoder[motorA]<35)
//	{
//		motor[motorA]=25;
//	}
//	motor[motorA]=0;
//	move_enc(135, v, 'f');
//	while(nMotorEncoder[motorA]<80)
//	{
//		motor[motorA]=25;
//	}
//	motor[motorA]=0;
//	wait10Msec(20);
//	move_enc(40, 15, 'b');
//	hapuga('d');
//	wait10Msec(25);
//	nMotorEncoder[motorA]=0;
//	while(nMotorEncoder[motorA]<65)
//	{
//		motor[motorA]=50;
//	}
//	motor[motorA]=0;
//	while(SensorValue[S1]>BLACK)
//	{
//		moving(15, 'b');
//	}
//	stopmotor();
//}

//void takeYellowZone()
//{
//	LineCross();
//	povleft();
//	Line_enc(610);
//	move_enc(TURN,v,'l');
//	move_enc(70,v,'b');
//	stopmotor();
//	zahvat('c');
//	povleft();
//	LineCross();
//	Line_enc(700);
//	move_enc(TURN,v,'l');
//	move_enc(200,v,'f');
//	hapuga('d');
//}


#endif
