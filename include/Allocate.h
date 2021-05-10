#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H
//short orientation, location;
short rightWay[2][4] = {{2, 1, 3, 0}, {1, 3, 2, 0}};
short ourWay[5];
short ourCrosses[5];
short finalRazvoz[4][4];
//enum zones{smth};

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

int assignment(int zone)
{
	if(zone == -2)
	{
		return 2;
	}

	else if(zone == -1)
	{
		return 3;
	}

	else if(zone == 0)
	{
		return 1;
	}

	else if(zone == 1)
	{
		return 4;
	}

	else if(zone == 2)
	{
		return 5;
	}

	else if(zone == 3)
	{
		return 4;
	}

	else
	{
		return -1;
	}
}

//void assignment(int zone)
//{
//	if(zone == -2)
//	{
//		cross = 2;
//	}

//	if(zone == -1)
//	{
//		cross = 3;
//	}

//	if(zone == 0)
//	{
//		cross = 1;
//	}

//	if(zone == 1)
//	{
//		cross = 4;
//	}

//	if(zone == 2)
//	{
//		cross = 5;
//	}

//	if(zone == 3)
//	{
//		cross = 4;
//	}
//}

void putInDom(short hapuga1, short zahvat1, short zahvat2, short hapuga2)
{
	v=25; k1=0.2; k2=1;
	zahvatPos = 0;

	if(hapuga1 != 1 && hapuga2 == 1)
	{
		hapuga('d');
	}
	if(hapuga1 == 1)
	{
		hapuga('u');
	}

	LineRed(v, "stop");

	if(hapuga1 == 1 || hapuga2 == 1)
	{
		move_enc(220, v, 'b', "stop");
	}

	if(hapuga2 == 1 && hapuga1 == 1)
	{
		hapuga('d');
		LineRed(v, "stop");
		move_enc(100, v, 'b', "stop");
	}

	if(hapuga2 == 1)
	{
		startTask(hapugaM);
	}

	move_enc(TURNAROUND, 20, 'r', "stop");

	if(zahvat1 == 1 || zahvat2 == 1)
	{
		Line_enc(80, v, "stop");
		zahvat(15, 'm');
	}

	if(zahvat1 != zahvat2)
	{
		if(zahvat1 == 1)
		{
			zahvat(15, 'o');
			move_enc(180, v, 'b', "stop");
		}
	}

	if(zahvat1 == 1 && zahvat2 == 1)
	{
		zahvat(15, 'o');
		Line_enc(220, v, "stop");
		zahvat(20, 'm');
		move_enc(220, v, 'b', "stop");
	}

	if(finalRazvoz[1][0] == hapuga1 && finalRazvoz[1][1] == zahvat1 && finalRazvoz[1][2] == zahvat2 && finalRazvoz[1][3] == hapuga2)
	{
		if(hapuga1 == 0)
		{
			startTask(hapugaU);
		}
	}
	else
	{
		startTask(hapugaDM);
	}
	LineCross(v, "");
	startTask(zahvatC);
}


void calculation(short col)
{
	short counter = 0;
	short i1, i2;
	for(short i = 0; i<4; i++)
	{
		for(short j = 0; j<4; j++)
		{
			finalRazvoz[i][j] = 0;
		}
		ourWay[i] = -1*(col + 1);
	}
	ourWay[4] = -1*(col + 1);

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
				ourWay[counter] = rightWay[col][i];
				counter++;
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
			finalRazvoz[rightWay[col][i]][3] = 1;
			ourWay[counter] =  rightWay[col][i];
			counter++;
		}
		if(col==1)
		{
			if(nInds[col+1] == 1 && rightWay[col][i] == 3)
			{
				finalRazvoz[rightWay[col][i]][1] = 1;
				ourWay[counter] =  rightWay[col][i];
				counter++;
			}
		}
	}
}

void move_to(short destination, const string ifTurn)
{
	if(location == 7)
	{
		if(destination == 5)
		{
			fwd_white(3,v,"");
			fwd_black(2, v, "");
			move_enc(30,v,'f',"");
			motor[leftMotor]=0;
			while(SensorValue[S2]<40)
			{
				motor[rightMotor]=v;
			}
			while(SensorValue[S2]>20)
			{
				motor[rightMotor]=v;
			}
			stopmotor();
			while(SensorValue[S3] < WHITE)
			{
				motor[motorC]=-v;
			}
			while(SensorValue[S3] > GREY)
			{
				motor[motorC]=-v;
			}
			motor[motorC] = 0;
			while(SensorValue[S3] < WHITE)
			{
				motor[motorB]=v;
			}
			stopmotor();
		}
		else
		{
			move_enc(TURN, v, 'r', "stop");
			move_enc(200, v, 'f', "");
			fwd_white(1, v, "");
			fwd_black(1, v, "");
			if(destination == 4 && ourWay[0] == 1)
			{
				povright(v, "cross");
			}
			else
			{
				povleft(v, "cross");
				LineCross(v, "");
				location = 4;
			}
		}
	}
	if(location == 8)
	{
		if(ourWay[0] == 1)
		{
			move_enc(TURN, v, 'r', "stop");
		}
		else
		{
			move_enc(200, v, 'b', "stop");
			move_enc(TURNAROUND, v, 'r', "stop");
		}
		fwd_white(2, v, "");
		fwd_black(2, v, "");
		povleft(v, "cross");
		if(ourWay[0] != 1)
		{
			location = 3;
		}
	}
	if(location < 7 && location != destination)
	{
		if(ifTurn == "turn")
		{
			if(location < destination && location % 2 == 1 || location > destination && location % 2 == 0)
			{
				povright(v, "cross");
			}
			else
			{
				povleft(v, "cross");
			}
		}
		crosses(destination, "");
		if(old_location != destination)
		{
			move_enc(CROSS_ENC, v, 'f', "stop");
		}
		else
		{
			stopmotor();
		}
		if((old_location < destination && destination % 2 == 1) || (old_location > destination && destination % 2 == 0))
		{
			povright(v, "");
		}
		else
		{
			povleft(v, "");
		}
	}
}

void allocation(short col)
{
	hapuga('m');
	calculation(col);
	for(short i = 0; i < 5; i++)
	{
		ourCrosses[i] = assignment(ourWay[i]);
	}
	for(short i = 0; (i < 4) && (ourWay[i] >= 0); i++)
	{
		if(((nInds[col] == 1 || nInds[2*col] == 1) && location == 4 && old_location == 4) || (col == 1 && ourWay[i] != 1 && i == 0))
		{
			move_to(ourCrosses[i], "");
		}
		else
		{
			move_to(ourCrosses[i], "turn");
		}
		if(ourWay[i] != 3)
		{
			putInDom(finalRazvoz[ourWay[i]][0], finalRazvoz[ourWay[i]][1], finalRazvoz[ourWay[i]][2], finalRazvoz[ourWay[i]][3]);
		}
		else
		{
			if(col == 0)
			{
				hapuga('u');
				akkumBlGr();
				povright(v, "cross");
				Line_enc(100, v, "");
			}
			else
			{
				if(ourWay[0] != 1)
				{
					Line_enc(250, v, "stop");
					move_enc(TURNAROUND, v, 'r', "stop");
				}
				if(nInds[1] == 1)
				{
					hapuga('u');
					akkumBlGr();
					if(ourWay[i+1] == 2)
					{
						povleft(v, "cross");
					}
					else
					{
						povright(v, "cross");
					}
					Line_enc(100, v, "");
				}
				else
				{
					akkum_std();
					if(ourWay[i+1] == 2)
					{
						povright(v, "cross");
					}
					else
					{
						povleft(v, "cross");
					}
				}
			}
		}
		old_location = location;
		location = ourCrosses[i];
	}
	if(col == 0)
	{
		if((ourWay[1] == 3 || ourWay[2] == 3) && location == 4 && nInds[2] == 1)
		{
			povleft(v, "cross");
		}
		else
		{
			povright(v, "cross");
		}
	}
}

void takeYellowZone()
{
	LineCross(v, "");
	povleft(v, "cross");
	Line_enc(610, v, "stop");
	move_enc(TURN,v,'l',"stop");
	move_enc(120,v,'f',"stop");
	zahvat(20, 'o');
	move_enc(120+CROSS_ENC,v,'b',"stop");
	zahvat(15, 'c');
	povleft(v, "cross");
	LineCross(v, "");
	Line_enc(660, v, "stop");
	move_enc(TURN,v,'l',"stop");
	move_enc(170,v,'f',"stop");
	hapuga('d');
	bricksInRobot[0] = 2; bricksInRobot[1] = 2;
	location = 8;
}

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
	while(SensorValue[S3]>BLACK)
	{
		Line2(v);
	}
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<200)
	{
		Line2(v);
	}
	startTask(hapugaD);
	while(SensorValue[S2]>30)
	{
		moving(v, 'f');
	}
	move_enc(100, v, 'f', "stop");
	mot1_enc(ONEMOTORTURN, 'b', v, 'b', "stop");
	move_enc(145, v, 'f', "stop");
	hapuga('u');
	move_enc(125,v,'b',"stop");
	move_enc(250,v,'r',"stop");
	fwd_white(3,v,"");
	fwd_black(3, v, "");
	move_enc(240, v, 'f', "stop");
	move_enc(TURN, v, 'r', "stop");
	move_enc(50, v, 'f', "stop");
	move_enc(100, v, 'b', "stop");
	zahvat(20, 'c');
	mot1_enc(500,'b', v,  'f', "");
	bricksInRobot[2] = 0; bricksInRobot[3] = 0;
	location = 7;
}

void takeGreenZone()
{
	startTask(hapugaU);
	if(location < 3)
	{
		while(SensorValue[S1]<50)
		{
			Line(v);
		}
		LineCross(v, "stop");
		move_enc(60, v, 'b', "stop");
		move_enc(TURN+20, v, 'r', "stop");
		move_enc(70, v, 'b', "stop");
	}
	if(location > 3)
	{
		LineCross(v, "");
		fwd_white(1, v, "");
		LineCross(v, "stop");
		move_enc(TURN, v, 'l', "stop");
		move_enc(70, v, 'b', "stop");
	}
	hapuga('d');
	fwd_black(2, v, "stop");
	nMotorEncoder[motorA]=0;
	while(nMotorEncoder[motorA]<ZAHVATG-4)
	{
		motor[motorA]=15;
	}
	motor[motorA]=0;
	move_enc(130, 18, 'f', "stop");
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
	move_enc(200, v, 'f',"stop");
	zahvat(20, 'm');
	wait10Msec(10);
	zahvat(15, 'g');
	wait10Msec(15);
	move_enc(160, 18, 'b', "stop");
	zahvat(25, 'c');
	povleft(v, "");
	lineWhite(v, "");
	LineCross(v, "");
	povright(v, "cross");
	bricksInRobot[2] = 1; bricksInRobot[3] = 1;
}

void allocateAllBricks()
{
	takeBlueZone();
	allocation(0);
	takeGreenZone();
	takeYellowZone();
	allocation(1);
}

#endif
