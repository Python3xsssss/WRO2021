#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H

#define FWD_PASS1 288
#define FWD_PASS2 175

short rightWay[2][5] = {{1, 2, 3, 0, -1}, {1, 2, 3, 0, -1}};
short virtualBricks[4];
short cur_zone;
short akkum_gb = 0;

bool zahvats_empty()
{
	writeDebugStreamLine("bricksInRobot:");
	for (int i = 0; i < 4; i++)
	{
		writeDebugStream(" %d", bricksInRobot[i]);
		if (bricksInRobot[i] > -2)
		{
			return false;
		}
	}
	return true;
}

void akkumGB()
{
	move_enc(50, stdPower,'f', "stop");
	zahvat('m');
	move_enc(100, stdPower,'f', "stop");
	zahvat('c');

	while(SensorValue[S1]<WHITE)
		moving(stdPower, 'b');
	while(SensorValue[S1]>BLACK)
		moving(stdPower, 'b');
	motorStop();

	akkum_gb = 1;
	bricksInRobot[3] = -2;
}

void akkum_std()
{
	if(!akkum_gb)
	{
		while(SensorValue[S1]>BLACK)
			moving(stdPower, 'b');
	}
	motorStop();

	zahvat('o');
	motor[motorD] = (bricksInRobot[3] > -2) ? -25 : -75;
	wait10Msec(200);
	zahvatPos = 0;

	bricksInRobot[2] = -2;
}

void put_akkum ()
{
	if (bricksInRobot[3] != -2 && nInds[bricksInRobot[3]] != 2)
		akkumGB();

	if (bricksInRobot[2] == -1 || (bricksInRobot[2] != -2 && nInds[bricksInRobot[2]] != 2))
		akkum_std();

	akkum_gb = 0;
	location = 7;
}

void checkDom(short dom)
{
	Line_enc(212,stdPower,"stop");
	turn90(stdPower, 'r', "stop");
	indDoms[dom][0] = check_ind(FWD_PASS1, stdPower, dom);
	indDoms[dom][1] = check_ind(FWD_PASS2, stdPower, dom);
	motorStop();
	move_enc(FWD_PASS1+FWD_PASS2, zonePower, 'b', "stop");
}

int assignment(int zone)
{
	if(zone == 0)
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
		for(i1=0; i1<4; i1++)
		{
			if(indDoms[dom][0] == virtualBricks[i1])
			{
				virtualBricks[i1]=-2;
				break;
			}
		}
		for(i2=0; i2<4; i2++)
		{
			if(indDoms[dom][1] == virtualBricks[i2])
			{
				virtualBricks[i2]=-2;
				break;
			}
		}

		if(i1 < 4)
		{
			finalRazvoz[dom][i1] = 1;
			virtualBricks[i1]=-2;
		}
		if(i2 < 4)
		{
			finalRazvoz[dom][i2] = 1;
			virtualBricks[i2] = -2;
		}
	}
}

void put(short hapuga1, short hapuga2, short zahvat1, short zahvat2, short dom, bool ifBack)
{
	if (hapuga1)
	{
    startTask(hapugaO);
		nMotorEncoder[motorB]=0;
		LineRed(stdPower, "stop");
		move_enc(65, stdPower, 'b', "stop");
		bricksInRobot[0] = -2;
	}
	if (hapuga2)
	{
		startTask(hapugaM);
		LineRed(stdPower, "stop");
		wait1Msec(400);
		bricksInRobot[1] = -2;
		move_enc(140, stdPower, 'b', "stop");
	}
	if((zahvat1 || zahvat2) && !hapuga1 && !hapuga2 && !ifBack && dom != 1 && (indDoms[dom][0] != -1 || indDoms[dom][1] != -1))
		Line_enc(212, stdPower, "stop");

	if (zahvat1)
	{
		if (!hapuga1 && !hapuga2 && !ifBack)
			motorStop();
		if (!ifBack)
		{
			if (dom == 0) // mb uzhe ne nado
				turn180(stdPower, 'r', "stop");
			else
				turn180(stdPower, 'l', "stop");

			if (hapuga2)
				move_enc(75, stdPower, 'b', "");
		}
		if(!hapuga2)
		{
			startTask(zahvatO);
			wait1Msec(500);
		}
		else
		{
			zahvat('o');
		}
		move_enc(200,stdPower,'b',"stop");
		move_enc(200,stdPower,'f',"");
		bricksInRobot[2] = -2;
	}
	if (zahvat2)
	{
		if (!hapuga1 && !hapuga2 && !zahvat1 && !ifBack)
			motorStop();
		if (!zahvat1 && !ifBack)
		{
			if (dom == 0) // mb uzhe ne nado
				turn180(stdPower,'r',"stop");
			else
			  turn180(stdPower,'l',"stop");
			if (hapuga2)
				move_enc(75, stdPower, 'b', "");
		}
		if (zahvat1)
			motorStop();
		zahvat('m');
		//if (zahvat1)
		//	wait10Msec(250);
		wait1Msec(300);
		move_enc(105,stdPower,'b',"stop");
		move_enc(105,stdPower,'f',"stop");
		bricksInRobot[3] = -2;
	}
	if (!zahvat1 && !zahvat2 && !ifBack)
	{
		if (dom == 0) // mb uzhe ne nado
			turn180(stdPower, 'r', "stop");
		else
			turn180(stdPower, 'l', "stop");
	}

	startTask(hapugaC);
	if (bricksInRobot[3] != -2 && zahvatPos != 0)
		wait1Msec(150);
	startTask(zahvatC);
	if (bricksInRobot[3] != -2 && zahvatPos != 0)
		wait1Msec(1800);
}

void putInDom(short hapuga1, short hapuga2, short zahvat1, short zahvat2, short dom, short partAlloc)
{
	bool ifBack = false;
	if (location == 8)
	{
		if (bricksInRobot[1] == indDoms[1][0] || bricksInRobot[1] == indDoms[1][1] || bricksInRobot[0] == indDoms[1][0] || bricksInRobot[0] == indDoms[1][1])
			povleft(stdPower, "");

		else
		{
			povright(stdPower, "");
			Line_enc(50, stdPower,"");
			Line_enc(350, zonePower,"");
			LineCross(stdPower,"stop");
			location = 4;
			return;
		}
	}
	//
	if(indDoms[dom][0] == -1 && indDoms[dom][1] == -1) // body of this IF - to the function
	{
		checkDom(dom);
		calcDom(dom);
		hapuga1 = finalRazvoz[dom][0]; hapuga2 = finalRazvoz[dom][1];
		zahvat1 = finalRazvoz[dom][2]; zahvat2 = finalRazvoz[dom][3];
		if(!hapuga1 && !hapuga2)
		{
			povright(stdPower, "");
			ifBack = true;
		}
		else
		{
			povleft(stdPower, "");
		}
	}
	else
	{
		if(partAlloc == 0)
		{
			calcDom(dom);
			hapuga1 = finalRazvoz[dom][0]; hapuga2 = finalRazvoz[dom][1];
			zahvat1 = finalRazvoz[dom][2]; zahvat2 = finalRazvoz[dom][3];
		}

		if (hapuga1)
			startTask(hapugaO);
	}

	//sama vigruzka
	put(hapuga1, hapuga2, zahvat1, zahvat2, dom, ifBack);

	for (int i = 0; i < 4; i++)
		finalRazvoz[dom][i] = 0;

	if (dom == 1)
		Line_enc(600, lineMaxPower, "");

	LineCross(stdPower, "");
}

void calculation(short col)
{
	short counter = 0;
	short i1, i2;
	for(short i = 0; i<4; i++)
	{
		ourWay[i] = -1;
		virtualBricks[i] = bricksInRobot[i];
	}
	ourWay[4] = -1;
	if(nInds[col] < 2)
	{
		virtualBricks[3]=-2;
	}
	if(col==1 && nInds[col+1] < 2)
	{
		virtualBricks[2]=-2;
	}

	for(short i=0; i < 4; i++)
	{
		i1 = 0; i2 = 0;
		if(rightWay[col][i] != 3)
		{
			if(indDoms[rightWay[col][i]][0]==col || indDoms[rightWay[col][i]][1]==col || indDoms[rightWay[col][i]][0]==col*2 || indDoms[rightWay[col][i]][1]==col*2)
			{
				ourWay[counter] = rightWay[col][i];
				counter++;

				for(i1 = 0; i1 < 4; i1++)
				{
					if(i == 3)
						writeDebugStreamLine("virtualBricks: %d", virtualBricks[i1]);
					if(indDoms[rightWay[col][i]][0] == virtualBricks[i1])
					{
						virtualBricks[i1]=-2;
						break;
					}
				}

				for(i2 = 0; i2 < 4; i2++)
				{
					if(indDoms[rightWay[col][i]][1] == virtualBricks[i2])
					{
						virtualBricks[i2]=-2;
						break;
					}
				}
				if(i == 3)
					writeDebugStreamLine("i1: %d, i2: %d", i1, i2);
				if(i1 < 4)
					finalRazvoz[rightWay[col][i]][i1] = 1;

				if(i2 < 4)
					finalRazvoz[rightWay[col][i]][i2] = 1;
			}
		}
		else
		{
			if(nInds[col] < 2)
			{
				finalRazvoz[3][3] = 1;
				ourWay[counter] = rightWay[col][i];
				counter++;
			}
			else if(col == 1 && nInds[col+1] < 2)
			{
				finalRazvoz[3][2] = 1;
				ourWay[counter] = rightWay[col][i];
				counter++;
			}
		}
	}
}


void allocation(short part)
{
	if(part == 1)
		calculation(part);

	else
	{
		for(short i = 0; i < 4; i++)
		{
			ourWay[i] = rightWay[part][i];
		}
	}

	writeDebugStreamLine("%d", ourWay[0]);
	cur_zone = -1;
	for(short i = 0; i < 4 && !zahvats_empty(); i++)
	{
		our_crosses[i] = assignment(ourWay[i]);
		move_to(our_crosses[i], "turn", "turn");
		cur_zone = ourWay[i];
		if(cur_zone == 3)
			put_akkum();
		else
			putInDom(finalRazvoz[ourWay[i]][0], finalRazvoz[ourWay[i]][1], finalRazvoz[ourWay[i]][2], finalRazvoz[ourWay[i]][3], cur_zone, part);
		if(i == 0 && location == 8)
			location = 4;
	}
}

void allocateAllBricks()
{
	writeDebugStreamLine("Time after blue zone: %d sec", time1[T1] / 1000);
	allocation(0);
	writeDebugStreamLine("Time after first allocation: %d sec", time1[T1] / 1000);
	approachToGreen();
	takeGreenZone();
	writeDebugStreamLine("Time after green zone: %d sec", time1[T1] / 1000);
	takeYellowZone();
	writeDebugStreamLine("Time after yellow zone: %d sec", time1[T1] / 1000);
	allocation(1);
	writeDebugStreamLine("Time after second allocation: %d", time1[T1] / 1000);
}


#endif
