#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H
//short orientation, location;
short rightWay[2][4] = {{1, 3, 2, 0}, {1, 3, 2, 0}};
short ourWay[5];
short ourCrosses[5];
short finalRazvoz[4][4];
short virtualBricks[4];
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

void checkDom(short dom)
{
	move_enc(30, stdPower, 'b', "stop");
	mot1_enc(ONEMOTORTURN, 'c', stdPower, 'b', "stop");
	check_ind(dom, ENC_DOM23_1, ENC_DOM23_2);
	fwd_black(2, stdPower, "");
}

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

void calcDom(short dom)
{
	for(short i = 0; i<4; i++)
	{
		virtualBricks[i] = bricksInRobot[i];
	}

	if(indDoms[dom][0]==0||indDoms[dom][1]==0||indDoms[dom][0]==-1||indDoms[dom][1]==-1)
	{
		short i1, i2;
		for(i1=0; i1<4 || indDoms[dom][0] == bricksInRobot[i2]; i1++)
		{}
		for(i2=0; i2<4 || indDoms[dom][1] == bricksInRobot[i2]; i2++)
		{}

		if(i1 == 4 || i2 == 4)
		{
			for(short i3=0; i3 < 4; i3++)
			{
				if(bricksInRobot[i3] == indDoms[dom][0] || bricksInRobot[i3] == indDoms[dom][1])
				{
					finalRazvoz[dom][i3] = 1;
				}
			}
		}

		else
		{
			for(short i3=0; i3 < 4; i3++)
			{
				if(bricksInRobot[i3] == indDoms[dom][0])
				{
					finalRazvoz[dom][i3] = 1;
				}
			}

			for(short i3=0; i3 < 4; i3++)
			{
				if(bricksInRobot[i3] == indDoms[dom][1])
				{
					finalRazvoz[dom][i3] = 1;
				}
			}
		}
	}
}

void putInDom(short hapuga1, short hapuga2, short zahvat1, short zahvat2, short dom)
{
	if(indDoms[dom][0] == -1 && indDoms[dom][1] == -1)
	{
		checkDom(dom);
		calcDom(dom);
		hapuga1 = finalRazvoz[dom][0]; hapuga2 = finalRazvoz[dom][1]; zahvat1 = finalRazvoz[dom][2]; zahvat2 = finalRazvoz[dom][3];
		if(hapuga1 == 0 && hapuga2 == 0)
		{
			povleft(stdPower, "cross");
		}
		else
		{
			povright(stdPower, "cross");
		}
	}

	zahvatPos = 0;
	if(hapuga1 != 1 && hapuga2 == 1)
	{
		hapuga('d');
	}
	if(hapuga1 == 1)
	{
		hapuga('u');
		bricksInRobot[0] = -2;
	}

	LineRed(zonePower, "stop");

	if(hapuga1 == 1 || hapuga2 == 1)
	{
		move_enc(220, stdPower, 'b', "stop");
	}

	if(hapuga2 == 1 && hapuga1 == 1)
	{
		hapuga('d');
		LineRed(stdPower, "stop");
		move_enc(110, stdPower, 'b', "stop");
	}

	if(hapuga2 == 1)
	{
		bricksInRobot[1] = -2;
		startTask(hapugaM);
	}

	if(hapuga1 == 0 && hapuga2 == 0)
	{
		move_enc(35, stdPower, 'b', "stop");
	}

	if(hapuga1 != 0 || hapuga2 != 0)
	{
		move_enc(TURNAROUND, 20, 'l', "stop");
	}

	if(zahvat1 == 1 || zahvat2 == 1)
	{
		Line_enc(100, stdPower, "stop");
		zahvat('m');
	}

	if(zahvat1 != zahvat2)
	{
		if(zahvat1 == 1)
		{
			zahvat('o');
			move_enc(160, stdPower, 'b', "stop");
			bricksInRobot[2] = -2;
		}
		else
		{
			bricksInRobot[3] = -2;
		}
	}

	if(zahvat1 == 1 && zahvat2 == 1)
	{
		zahvat('o');
		Line_enc(220, stdPower, "stop");
		zahvat('m');
		move_enc(220, stdPower, 'b', "stop");
		bricksInRobot[2] = -2;
		bricksInRobot[3] = -2;
	}

	if(dom == 1)
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
	LineCross(zonePower, "");
	startTask(zahvatC);
}


void calculation(short col)
{
	short counter = 0;
	short i1, i2;
	for(short i = 0; i<4; i++)
	{
		ourWay[i] = -1*(col + 1);
		virtualBricks[i] = bricksInRobot[i];
	}
	ourWay[4] = -1*(col + 1);

	if(nInds[col] == 1)
	{
		virtualBricks[3]=-2;
	}
	if(col==1)
	{
		if(nInds[col+1] == 1)
		{
			virtualBricks[2]=-2;
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
					if(indDoms[rightWay[col][i]][0] == virtualBricks[i1])
					{
						break;
					}
				}
				for(i2=0; i2<4; i2++)
				{
					if(indDoms[rightWay[col][i]][1] == virtualBricks[i2])
					{
						break;
					}
				}
				if(i1 == 4 || i2 == 4)
				{
					for(short i3=0; i3 < 4; i3++)
					{
						if(virtualBricks[i3] == indDoms[rightWay[col][i]][0] || virtualBricks[i3] == indDoms[rightWay[col][i]][1])
						{
							finalRazvoz[rightWay[col][i]][i3] = 1;
							virtualBricks[i3] = -2;
							break;
						}
					}
				}
				else
				{
					for(short i3=0; i3 < 4; i3++)
					{
						if(virtualBricks[i3] == indDoms[rightWay[col][i]][0])
						{
							finalRazvoz[rightWay[col][i]][i3] = 1;
							virtualBricks[i3] = -2;
							break;
						}
					}
					for(short i3=0; i3 < 4; i3++)
					{
						if(virtualBricks[i3] == indDoms[rightWay[col][i]][1])
						{
							finalRazvoz[rightWay[col][i]][i3] = 1;
							virtualBricks[i3] = -2;
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
				finalRazvoz[rightWay[col][i]][2] = 1;
				ourWay[counter] =  rightWay[col][i];
				counter++;
			}
		}
	}
	writeDebugStreamLine("finalRazvoz: ");
	for(short i = 0; i < 4; i++)
	{
		for(short j = 0; j < 4; j++)
		{
			writeDebugStream("%d ", finalRazvoz[i][j]);
		}
		writeDebugStream("\n");
	}
	writeDebugStreamLine("ourWay: ");
	for(short i = 0; i < 3; i++)
	{
		writeDebugStream("%d ", ourWay[i]);
	}
}

void move_to(short destination, const string ifTurn1, const string ifTurn2)
{
	if(location == 7)
	{
		if(ourWay[0] == 1)
		{
			povright(stdPower, "cross");
		}
		else
		{
			startTask(hapugaU);
			povleft(stdPower, "cross");
			LineCross(zonePower, "");
			location = 4;
		}
	}
	if(location == 8)
	{
		if(ourWay[0] == 1)
		{
			move_enc(TURN, stdPower, 'r', "stop");
		}
		else
		{
			move_enc(200, zonePower, 'b', "stop");
			move_enc(TURNAROUND, stdPower, 'r', "stop");
		}
		fwd_white(2, zonePower, "");
		fwd_black(2, stdPower, "");
		povleft(stdPower, "cross");
		if(ourWay[0] != 1)
		{
			if(ourWay[0] == 3)
				startTask(hapugaU);
			location = 3;
		}
	}
	if(location < 7 && location != destination)
	{
		if(ifTurn1 == "turn")
		{
			turning(destination);
		}
		if(location == 4)
		{
			startTask(hapugaDM);
		}
		crosses(destination, "");
		if(ifTurn2  == "turn")
		{
			if(old_location != destination)
			{
				move_enc(CROSS_ENC, stdPower, 'f', "stop");
			}
			else
			{
				stopmotor();
			}
			if((old_location < destination && destination % 2 == 1) || (old_location > destination && destination % 2 == 0))
			{
				povright(stdPower, "");
			}
			else
			{
				povleft(stdPower, "");
			}
		}
		else
		{
			stopmotor();
		}
	}
}

void allocation(short col)
{
	hapuga('m');
	for(short i = 0; i<4; i++)
	{
		for(short j = 0; j<4; j++)
		{
			finalRazvoz[i][j] = 0;
		}
	}
	if(col == 1)
	{
		calculation(col);
	}
	else
	{
		for(short i = 0; i<4; i++)
		{
			if(rightWay[col][i] != 3 || nInds[col] == 2)
			{
				ourWay[i] = rightWay[col][i];
			}
		}
	}
	for(short i = 0; i < 5; i++)
	{
		ourCrosses[i] = assignment(ourWay[i]);
	}
	for(short i = 0; (i < 4) && (ourWay[i] >= 0); i++)
	{
		if(((nInds[col] == 1 || nInds[2*col] == 1) && location == 4 && old_location == 4) || (col == 1 && ourWay[i] != 1 && i == 0))
		{
			move_to(ourCrosses[i], "", "turn");
		}
		else
		{
			move_to(ourCrosses[i], "turn", "turn");
		}
		if(ourWay[i] != 3)
		{
			putInDom(finalRazvoz[ourWay[i]][0], finalRazvoz[ourWay[i]][1], finalRazvoz[ourWay[i]][2], finalRazvoz[ourWay[i]][3], ourWay[i]);
		}
		else
		{
			if(col == 0)
			{
				akkumGB();
				povright(stdPower, "cross");
				Line_enc(100, stdPower, "");
			}
			else
			{
				if(ourWay[0] != 1)
				{
					Line_enc(250, stdPower, "stop");
					move_enc(TURNAROUND, stdPower, 'r', "stop");
				}
				if(nInds[1] == 1)
				{
					akkumGB();
					if(ourWay[i+1] == 2)
					{
						povleft(stdPower, "cross");
					}
					else
					{
						povright(stdPower, "cross");
					}
					Line_enc(100, stdPower, "");
				}
				else
				{
					akkum_std();
					if(ourWay[i+1] == 2)
					{
						povright(stdPower, "cross");
					}
					else
					{
						povleft(stdPower, "cross");
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
			povleft(stdPower, "cross");
		}
		else
		{
			povright(stdPower, "cross");
		}
	}
}

void takeYellowZone()
{
	LineCross(stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(600, stdPower, "stop");

	move_enc(TURN,stdPower,'l',"stop");
	move_enc(160,stdPower,'f',"stop");
	zahvat('o');
	move_enc(240,stdPower,'b',"stop");
	zahvat('c');
	move_enc(15,stdPower,'f',"");
	povleft(stdPower, "cross");

	LineCross(stdPower, "");
	Line_enc(670, stdPower, "stop");

	move_enc(TURN,stdPower,'l',"stop");
	move_enc(175,stdPower,'f',"stop");
	hapuga('d');

	bricksInRobot[0] = 2; bricksInRobot[2] = 2;
	location = 8;
}

void takeBlueZone()
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<350)
	{
		Line2(stdPower);
	}
	while(SensorValue[S3]<WHITE)
	{
		Line2(stdPower);
	}
	while(SensorValue[S3]>BLACK)
	{
		Line2(stdPower);
	}
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<200)
	{
		Line2(stdPower);
	}
	startTask(hapugaD);
	move_enc(165, stdPower, 'f', "stop");
	mot1_enc(ONEMOTORTURN, 'b', stdPower, 'b', "stop");

	move_enc(145, stdPower, 'f', "stop");
	hapuga('u');
	move_enc(125,stdPower,'b',"stop");

	move_enc(250,stdPower,'r',"stop");
	fwd_white(3,stdPower,"");
	fwd_black(3, stdPower, "");
	move_enc(240, stdPower, 'f', "stop");
	move_enc(TURN, stdPower, 'r', "stop");

	move_enc(50, stdPower, 'f', "stop");
	zahvat('m');
	move_enc(130, stdPower, 'b', "stop");
	zahvat('c');

	startTask(hapugaD);
	move_enc(80, stdPower, 'f', "");
	fwd_black(2, stdPower, "stop");

	bricksInRobot[1] = 0; bricksInRobot[3] = 0;
	location = 7;
}

void takeGreenZone()
{
	if(location != 4)
	{
		startTask(hapugaU);
	}
	startTask(zahvatCor);
	if(location < 3)
	{
		while(SensorValue[S1]<50)
		{
			Line(stdPower);
		}
		LineCross(stdPower, "stop");
		move_enc(70, stdPower, 'b', "stop");
		move_enc(TURN+10, stdPower, 'r', "stop");
		startTask(hapugaD);
		move_enc(70, stdPower, 'b', "stop");
	}
	if(location > 3)
	{
		if(location == 5)
		{
			LineCross(lineMaxPower, "");
			Line_enc(200, lineMaxPower, "");
		}
		lineWhite(lineMaxPower, "");
		LineCross(stdPower, "stop");
		move_enc(TURN, stdPower, 'l', "stop");
		startTask(hapugaD);
		move_enc(70, stdPower, 'b', "stop");
	}
	fwd_black(2, stdPower, "stop");
	nMotorEncoder[motorA]=0;
	while(nMotorEncoder[motorA]<HAPUGAG)
	{
		motor[motorA]=15;
	}
	motor[motorA]=0;
	move_enc(130, 18, 'f', "stop");
	hapuga('u');
	while(SensorValue[S2]>BLACK)
	{
		moving(stdPower, 'b');
	}
	stopmotor();
	povleft(stdPower, "cross");
	LineCross(stdPower, "");
	Line_enc(240, stdPower, "stop");
	move_enc(TURN, stdPower, 'l',"stop");
	move_enc(200, stdPower, 'f',"stop");
	zahvat('m');
	wait10Msec(10);
	zahvat('g');
	wait10Msec(15);
	move_enc(180, 18, 'b', "stop");
	zahvat('c');
	povleft(stdPower, "");
	lineWhite(stdPower, "");
	LineCross(stdPower, "");
	povright(stdPower, "cross");
	bricksInRobot[1] = 1; bricksInRobot[3] = 1;
}

void allocateAllBricks()
{
	takeBlueZone();
	writeDebugStreamLine("Time after taking blue zone: %d", time1[T1] / 1000);
	allocation(0);
	writeDebugStreamLine("Time after first allocation: %d", time1[T1] / 1000);
	takeGreenZone();
	takeYellowZone();
	writeDebugStreamLine("Time after taking green and yellow zones: %d", time1[T1] / 1000);
	allocation(1);
	writeDebugStreamLine("Time after allocateing all bricks: %d", time1[T1] / 1000);
}

#endif
