#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H
//short orientation, location;
short polozhenie=2;
int rightWay[2][4] = {{2, 1, 3, 0}, {1, 2, 3, 0}};
int ourWay[4] = {-1, -1, -1, -1};
int finalRazvoz[4][4];
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

void putInDom(short hapuga1, short zahvat1, short zahvat2, short hapuga2)
{
	v=25; k1=0.2; k2=1;
	zahvatPos = 0;
	if(hapuga2 == 1 && hapuga1 != 1)
	{
		hapuga('d');
	}
	LineRed(v, "");
	if(hapuga1 == 1)
	{
		move_enc(30, v, 'f', "stop");
	}
	move_enc(150, v, 'b', "stop");
	if(hapuga2 == 1 && hapuga1 != 1)
	{
		startTask(hapugaU);
	}
	if(hapuga2 == 1 && hapuga1 == 1)
	{
		hapuga('d');
		LineRed(v, "stop");
		move_enc(100, v, 'b', "stop");
	}
	move_enc(TURNAROUND, v, 'r', "stop");
	if(zahvat1 == 1 || zahvat2 == 1)
	{
		zahvat('d');
	}
	if(zahvat1 == 1 && zahvat2 != 1 || zahvat1 != 1 && zahvat2 == 1)
	{
		move_enc(100, v, 'b', "stop");
		if(zahvat1 == 1)
		{
			zahvat('o');
			move_enc(140, v, 'f', "stop");
			zahvat('c');
		}
		move_enc(100, v, 'f', "");
		startTask(zahvatC);
	}
	if(zahvat1 == 1 && zahvat2 == 1)
	{
		zahvat('o');
		move_enc(140, v, 'f', "stop");
		zahvat('m');
		move_enc(140, v, 'b', "stop");
		move_enc(50, v, 'f', "");
		startTask(zahvatC);
	}
	LineCross(v, "");
}


void calculation(short col)
{
	short i1, i2;
	finalRazvoz[0][0] = 0; finalRazvoz[0][1] = 0; finalRazvoz[0][2] = 0; finalRazvoz[0][3] = 0;
	finalRazvoz[1][0] = 0; finalRazvoz[1][1] = 0; finalRazvoz[1][2] = 0; finalRazvoz[1][3] = 0;
	finalRazvoz[2][0] = 0; finalRazvoz[2][1] = 0; finalRazvoz[2][2] = 0; finalRazvoz[2][3] = 0;
	finalRazvoz[3][0] = 0; finalRazvoz[3][1] = 0; finalRazvoz[3][2] = 0; finalRazvoz[3][3 ]= 0;
	ourWay[0] = -1; ourWay[1] = -1; ourWay[2] = -1; ourWay[3] = -1;
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
							finalRazvoz[i][i3] = 1;
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
							finalRazvoz[i][i3] = 1;
							bricksInRobot[i3] = -2;
							break;
						}
					}
					for(short i3=0; i3 < 4; i3++)
					{
						if(bricksInRobot[i3] == indDoms[rightWay[col][i]][1])
						{
							finalRazvoz[i][i3] = 1;
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
				finalRazvoz[2][1] = 1;
			}
		}
	}
}

void RazvoznBlue()
{
	hapuga('u');
	calculation(0);
	if (finalRazvoz[0][0] == 1 || finalRazvoz[0][1] == 1 || finalRazvoz[0][2] == 1 || finalRazvoz[0][3] == 1)
	{
		fwd_black(2, v, "");
		while(SensorValue[S2] > BLACK)
		{
			motor[motorC]=-v;
		}
		stopmotor();
		putInDom(finalRazvoz[0][0], finalRazvoz[0][1], finalRazvoz[0][2], finalRazvoz[0][3]);
		povleft(v, "cross");
		location = 6;
		orientation = 1;
		crosses(4);
	}
	else
	{
		move_enc(TURN, v, 'r', "stop");
		while (SensorValue[S1]<WHITE)
		{
			moving(v, 'f');
		}
		fwd_black(1, v, "");
	}
	if(finalRazvoz[1][0]==1 || finalRazvoz[1][1]==1 || finalRazvoz[1][2]==1 || finalRazvoz[1][3]==1)
	{
		povright(v, "cross");
		putInDom(finalRazvoz[1][0], finalRazvoz[1][1], finalRazvoz[1][2], finalRazvoz[1][3]);
		if(finalRazvoz[2][3] != 1)
		{
			povright(v, "cross");
		}
	}
	else
	{
		if(finalRazvoz[0][0] != 1 || finalRazvoz[0][1] != 1 || finalRazvoz[0][2] != 1 || finalRazvoz[0][3] != 1)
		{
			povleft(v, "cross");
			LineCross(v, "stop");
			if(finalRazvoz[2][3] != 1)
			{
				povright(v, "cross");
			}
		}
	}
	if(finalRazvoz[2][3] == 1)
	{
		if (finalRazvoz[0][0] == 1 || finalRazvoz[0][1] == 1 || finalRazvoz[0][2] == 1 || finalRazvoz[0][3] == 1)
		{
			povright(v, "cross");
			Line_enc(80, v, "stop");
			move_enc(TURNAROUND, v, 'l', "stop");
		}
		akkumBlGr();
		povright(v, "cross");
	}
	location = 4;
	if(finalRazvoz[3][0] == 1 || finalRazvoz[3][1] == 1 || finalRazvoz[3][2] == 1 || finalRazvoz[3][3] == 1)
	{
		crosses(1);
		povleft(v, "cross");
		putInDom(finalRazvoz[3][0], finalRazvoz[3][1], finalRazvoz[3][2], finalRazvoz[3][3]);
		povright(v, "cross");
		polozhenie=1;
	}
	else
	{
		crosses(2);
	}
}

void RazvoznGreenAndYellow()
{
	hapuga('u');
	calculation(1);
	if (finalRazvoz[0][0] == 1 || finalRazvoz[0][1] == 1 || finalRazvoz[0][2] == 1 || finalRazvoz[0][3] == 1)
	{
		move_enc(TURN, v, 'r', "stop");
	}
	else
	{
		move_enc(TURNAROUND, v, 'r', "stop");
	}
	fwd_white(2, v, "");
	fwd_black(2, v, "");
	povleft(v, "cross");
	if (finalRazvoz[0][0] == 1 || finalRazvoz[0][1] == 1 || finalRazvoz[0][2] == 1 || finalRazvoz[0][3] == 1)
	{
		putInDom(finalRazvoz[0][0], finalRazvoz[0][1], finalRazvoz[0][2], finalRazvoz[0][3]);
	}
	else
	{
		location = 3;
		orientation=3;
		crosses(4);
		if(nInds[1] == 1 || nInds[2] == 1)
		{
			move_enc(TURN, v, 'r', "stop");
			while(SensorValue[S2]>BLACK)
			{
				moving(v, 'b');
			}
			stopmotor();
		}
	}
	if(nInds[1]==1)
	{
		akkumBlGr();
	}
	if(nInds[2]==1)
	{
		akkum_std();
	}
	if(finalRazvoz[2][0] == 1 || finalRazvoz[2][1] == 1 || finalRazvoz[2][2] == 1 || finalRazvoz[2][3] == 1)
	{
		if(nInds[1] == 1 || nInds[2] == 1)
		{
			povleft(v, "cross");
		}
		location = 4;
		orientation = 3;
		crosses(5);
		povright(v, "cross");
		putInDom(finalRazvoz[2][0], finalRazvoz[2][1], finalRazvoz[2][2], finalRazvoz[2][3]);
		povleft(v, "cross");
		orientation=1;
		location = 6;
	}
	else
	{
		povright(v, "");
		location = 4;
		orientation = 1;
		crosses(2);
	}
	if(finalRazvoz[3][0] == 1 || finalRazvoz[3][1] == 1 || finalRazvoz[3][2] == 1 || finalRazvoz[3][3] == 1)
	{
		crosses(1);
		povleft(v, "cross");
		putInDom(finalRazvoz[3][0], finalRazvoz[3][1], finalRazvoz[3][2], finalRazvoz[3][3]);
		povright(v, "cross");
		orientation = 3;
		crosses(2);
		povleft(v, "cross");
	}
	if(finalRazvoz[3][0] == 0 && finalRazvoz[3][1] == 1 && finalRazvoz[3][2] == 0 && finalRazvoz[3][3] == 0)
	{
		povright(v, "cross");
	}
}


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

void takeBlueZone()
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<350)
	{
		Line2(v);
	}
	while(SensorValue[S3]<WHITE)
	{
		Line2(v);
	}
	while(SensorValue[S3]<BLACK)
	{
		Line2(v);
	}
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<270)
	{
		Line2(v);
	}
	move_enc(TURN, v, 'r', "stop");
	move_enc(250, v, 'b', "stop");
	hapuga('d');
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	fwd_white(1,v,"");
	fwd_black(1,v,"");
	wait1Msec(10);
	stopmotor();
	hapuga('u');
	mot1_enc(ONEMOTORTURN, v, 'b', 'b', "stop");
	//motor[motorA]=-20;
	//wait10Msec(50);
	//motor[motorA]=0;
	//move_enc(150, v, 'b');
	//motor[motorA]=20;
	//wait10Msec(50);
	//motor[motorA]=0;
	while(SensorValue[S3]<WHITE)//65
	{
		motor[motorB]=v;
		motor[motorC]=-v;
	}
	fwd_black(1, v, "");
	move_enc(230, v, 'f', "stop");
	motor[motorA]=0;
	move_enc(TURN, v, 'r', "stop");
	zahvat('m');
	move_enc(200,v,'b',"stop");
	zahvat('c');
	mot1_enc(ONEMOTORTURN, v, 'b', 'b', "stop");
}



void takeGreenZone()
{
	if(polozhenie==1)
	{
		while(SensorValue[S1]<WHITE)
		{
			Line(v);
		}
		LineCross(v, "stop");
		move_enc(TURN, v, 'l', "stop");
		move_enc(90, v, 'b', "stop");
		hapuga('d');
		fwd_black(2, v, "");
	}
	if(polozhenie==0)
	{
		lineToLine();
		Line1Cross(v, "");
		nMotorEncoder[motorB]=0;
		while(nMotorEncoder[motorB]<80)
		{
			Line1(v);
		}
		while(SensorValue[S3]>27)
		{
			Line1(v);
		}
		stopmotor();
		move_enc(TURN, v, 'r', "stop");
		move_enc(70, v, 'b', "stop");
		hapuga('d');
		fwd_black(2, v, "");
	}
	nMotorEncoder[motorA]=0;
	while(nMotorEncoder[motorA]<35)
	{
		motor[motorA]=25;
	}
	motor[motorA]=0;
	move_enc(130, v, 'f', "stop");
	hapuga('u');
	while(SensorValue[S2]>BLACK)
	{
		moving(v, 'b');
	}
	stopmotor();
	povleft(v, "cross");
	LineCross(v, "");
	Line_enc(240, v, "stop");
	move_enc(TURN, v, 'l',"stop");
	zahvat('m');
	zahvat('g');
	move_enc(200, v, 'b', "stop");
	zahvat('c');
	fwd_black(1, v, "stop");
}

//void AllocateAllBricks()
//{
//	takeBlueZone();
//	RazvoznBlue();
//	takeGreenZone();
//	RazvoznGreen();
//	takeYellowZone();
//}

#endif
