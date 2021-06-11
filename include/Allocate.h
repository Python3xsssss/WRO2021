#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H

#define ENC1_DOM 115
#define ENC2_DOM 185
#define BEFORE_CROSS 75

int encs[6]={340, 800, 250, 950, 850, 250};

short our_crosses[5] = {-1,-1,-1,-1,-1};
short rightWay[2][5] = {{1, 2, 3, 0, -1}, {1, 2, 3, 0, -1}};
short ourCrosses[5];
short virtualBricks[4];
short withoutZone = 0;
short importantBricks = -2;
short cur_zone;
short akkum_gb = 0;

bool zahvats_empty()
{
	for (int i = 0; i < 4; i++)
	{
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
  stopmotor();
  akkum_gb = 1;
  importantBricks = -2;
}

void akkum_std()
{
	while(SensorValue[S1]>BLACK)
		moving(stdPower, 'b');
  stopmotor();
	zahvat('m');
	bricksInRobot[3] = importantBricks;
	zahvat('o');
	zahvat('c');
}

void put_akkum ()
{
	importantBricks = bricksInRobot[3];
	bricksInRobot[3] = -2;
	if (importantBricks != -2 && nInds[importantBricks] != 2)
		akkumGB();

	if (bricksInRobot[2] == -1 || nInds[bricksInRobot[2]] != 2)
		akkum_std();

	if(!akkum_gb)
		bricksInRobot[3] = importantBricks;

	akkum_gb = 0;
}

void checkDom(short dom)
{
	move_enc(5, stdPower, 'b', "stop");
	while(SensorValue[S3]<WHITE)
	{
		motor[motorC]=stdPower;
	}
	while(SensorValue[S3]>BLACK)
	{
		motor[motorC]=stdPower;
	}
	while(SensorValue[S3]<WHITE)
	{
		motor[motorC]=stdPower;
	}
	mot1_enc(116, 'c', stdPower, 'b', "stop");
	/*	check_ind(dom, ENC1_DOM, ENC2_DOM);*/
	if(dom != 0)
	{
		fwd_black(2, stdPower, "");
	}
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

void putInDom(short hapuga1, short hapuga2, short zahvat1, short zahvat2, short dom, short partAlloc)
{
	bool ifBack = false;
	if(indDoms[dom][0] == -1 && indDoms[dom][1] == -1) // body of this IF - to the function
	{
		LineRed(stdPower, "stop");
		checkDom(dom);
		if(hapuga1 == 0 && hapuga2 == 0 && zahvat1 == 0 && zahvat2 == 0)
		{
			calcDom(dom);
			hapuga1 = finalRazvoz[dom][0]; hapuga2 = finalRazvoz[dom][1];
			zahvat1 = finalRazvoz[dom][2]; zahvat2 = finalRazvoz[dom][3];
		}
		if(hapuga1 == 0 && hapuga2 == 0)
		{
			povleft(stdPower, "cross");
			ifBack = true;
		}
		else
		{
			povright(stdPower, "cross");
		}
		//otyezd nazad v ishodnuyu
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
		{
			startTask(hapugaO);
		}
		Line_enc(180, stdPower, "");
	}

	if (hapuga1)
	{
		nMotorEncoder[motorB]=0;
		LineRed(stdPower, "");
		int enc = nMotorEncoder[motorB];
		move_enc(65, stdPower, 'f', "stop");
		move_enc(enc + 65, stdPower, 'b', "stop");
		bricksInRobot[0] = -2;
	}
	if (hapuga2)
	{
		startTask(hapugaM);
		nMotorEncoder[motorB]=0;
		Line_enc(160, stdPower, "stop");
		wait1Msec(250);
		move_enc(160, stdPower,'b',"stop");
		bricksInRobot[1] = -2;
	}
	if (zahvat1)
	{
		if (!hapuga1 && !hapuga2 && !ifBack)
			stopmotor();
		if (!ifBack)
		{
			if (dom == 0) // mb uzhe ne nado
				povright(stdPower,"");
			else
				povleft(stdPower,"");
		}
		//if(!hapuga2)
		//{
		//	startTask(zahvatO);
		//	wait1Msec(1000);
		//}
		//else
		//{
		zahvat('o');
		//}
		move_enc(200,stdPower,'b',"stop");
		move_enc(200,stdPower,'f',"");
		bricksInRobot[2] = -2;
	}
	if (zahvat2)
	{
		if (!hapuga1 && !hapuga2 && !zahvat1 && !ifBack)
			stopmotor();
		if (!zahvat1 && !ifBack)
		{
			if (dom == 0) // mb uzhe ne nado
				povright(stdPower,"");
			else
				povleft(stdPower,"");
		}
		if (zahvat1)
			stopmotor();
		zahvat('m');
		//if (zahvat1)
		//	wait10Msec(250);
		wait1Msec(300);
		move_enc(70,stdPower,'b',"stop");
		move_enc(70,stdPower,'f',"stop");
		bricksInRobot[3] = -2;
	}
	if (!zahvat1 && !zahvat2 && !ifBack)
	{
		if (dom == 0) // mb uzhe ne nado
			povright(stdPower,"");
		else
			povleft(stdPower,"");
	}

	startTask(hapugaC);

	if (dom == 1)
	{
		Line_enc(375, zonePower, "");
	}

	LineCross(stdPower, "stop");
	for (int i = 0; i < 4; i++)
		finalRazvoz[dom][i] = 0;
	if (bricksInRobot[3] != -2 && zahvatPos != 0)
		wait1Msec(150);
	startTask(zahvatC);
	if (bricksInRobot[3] != -2 && zahvatPos != 0)
		wait1Msec(1800);
}

void crosses_new(short destination, const string ifStop)
{
	for(short i = location; i != destination; i = (location < destination) ? i+1 : i-1)
	{
		location = i;
		int shift = (abs(i - destination) == 1) ? BEFORE_CROSS : 0;
		int curr_enc = encs[(location > destination) ? i-1 : i] - shift;
		if(!sensors)
			Line_enc(curr_enc, lineMaxPower, "");
		else
			Line1_enc(curr_enc, lineMaxPower, "");
	}
	LineCross(stdPower, "");

	if(ifStop == "stop" || ifStop == "STOP" || ifStop == "Stop" || ifStop == "s")
		stopmotor();
}

void move_to_new(short destination, const string ifTurn1, const string ifTurn2)
{
	if(location == 8)
	{
		return;
	}
	if(location < 8 && location != destination)
	{
		if(ifTurn1 == "turn")// && location != 9)
		{
			turning(destination);
			if (location == 7) // accumulator
			{
				location = 4;
			}

      old_location = location;
			crosses_new(destination, "");

			if(ifTurn2  == "turn")
			{
				if((old_location < destination && destination % 2 == 1) || (old_location > destination && destination % 2 == 0))
				{
					povright(stdPower, "cross");
				}
				else
				{
					povleft(stdPower, "cross");
				}
			}
			else
			{
				stopmotor();
			}
		}
	}
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
	if(nInds[col] < 2)
	{
		virtualBricks[1]=-2;
	}
	if(col==1)
	{
		if(nInds[col+1] < 2)
		{
			virtualBricks[2]=-2;
		}
	}

	for(short i=0; i < 4; i++)
	{
		i1 = 0; i2 = 0;
		if(rightWay[col][i] != 3)
		{
			if(/*indDoms[rightWay[col][i]][0]==col||indDoms[rightWay[col][i]][1]==col||*/ indDoms[rightWay[col][i]][0]==col*2 || indDoms[rightWay[col][i]][1]==col*2)
			{
				ourWay[counter] = rightWay[col][i];
				counter++;
				for(i1 = 0; i1 < 4; i1++)
				{
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
				if(i1 < 4)
				{
					finalRazvoz[rightWay[col][i]][i1] = 1;
					virtualBricks[i1] = -2;
				}
				if(i2 < 4)
				{
					finalRazvoz[rightWay[col][i]][i2] = 1;
					virtualBricks[i2] = -2;
				}
			}
		}
		if(col==1)
		{
			if(nInds[col+1] == 1 && rightWay[col][i] == 3)
			{
				finalRazvoz[rightWay[col][i]][2] = 1;
				ourWay[counter] = rightWay[col][i];
				counter++;
			}
		}
	}
}


void allocation(short part)
{
	cur_zone = -1;
	for(short i = 0; i < 4 && !zahvats_empty(); i++)
	{
		our_crosses[i] = assignment(rightWay[part][i]);
		move_to_new(our_crosses[i], "turn", "turn");
		cur_zone = rightWay[part][i];
		if(cur_zone == 3)
			put_akkum();
		else
			putInDom(0, 0, 0, 0, cur_zone, part);
		if(i == 0 && location == 8)
			location = 4;
	}
}

void allocateAllBricks()
{
	//takeBlueZone();
	writeDebugStreamLine("Time after blue zone: %d sec", time1[T1] / 1000);
	allocation(0);
	writeDebugStreamLine("Time after first allocation: %d sec", time1[T1] / 1000);
	//takeGreenZone();
	//takeYellowZone();
	//writeDebugStreamLine("Time after yellow zone: %d sec", time1[T1] / 1000);
	//allocation(1);
	//writeDebugStreamLine("Time after second allocation: %d", time1[T1] / 1000);
}


#endif
