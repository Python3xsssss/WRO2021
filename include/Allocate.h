#pragma once

#ifndef ALLOCATE_H
#define ALLOCATE_H

#define ENC1_DOM 115
#define ENC2_DOM 185

short rightWay[2][5] = {{1, 2, 3, 0, -1}, {1, 2, 3, 0, -1}};
short ourWay[5] = {-1, -1, -1, -1, -1};
short ourCrosses[5];
short virtualBricks[4];
short withoutZone = 0;
short importantBricks = -2;

void checkDom(short dom)
{
	move_enc(12, stdPower, 'b', "stop");
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
	mot1_enc(95, 'c', stdPower, 'b', "stop");
	check_ind(dom, ENC1_DOM, ENC2_DOM);
	if(dom != 0)
	{
		fwd_black(2, stdPower, "");
	}
}

int assignment(int zone)
{
	if(zone == -2)
	{
		return 0;
	}

	else if(zone == -1)
	{
		return 2;
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

void putInDom(short hapuga1, short hapuga2, short zahvat1, short zahvat2, short dom, short col)
{
	bool ifBack = false;
	if(indDoms[dom][0] == -1 && indDoms[dom][1] == -1)
	{
		LineRed(stdPower, "stop");
		checkDom(dom);
		if(hapuga1 == 0 && hapuga2 == 0 && zahvat1 == 0 && zahvat2 == 0)
		{
			calcDom(dom);
			hapuga1 = finalRazvoz[dom][0]; hapuga2 = finalRazvoz[dom][1]; zahvat1 = finalRazvoz[dom][2]; zahvat2 = finalRazvoz[dom][3];
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
		if(col == 0)
		{
			calcDom(dom);
			hapuga1 = finalRazvoz[dom][0]; hapuga2 = finalRazvoz[dom][1];
			zahvat1 = finalRazvoz[dom][2]; zahvat2 = finalRazvoz[dom][3];
		}
		if (hapuga1)
		{
			startTask(hapugaU);
		}
		Line_enc(180,stdPower, "");
	}

	if (hapuga1)
	{
		nMotorEncoder[motorB]=0;
		LineRed(stdPower,"");
		int enc = nMotorEncoder[motorB];
		move_enc(65, stdPower, 'f', "stop");
		move_enc(enc + 65, stdPower, 'b', "stop");
		bricksInRobot[0] = -2;
	}
	if (hapuga2)
	{
		startTask(hapugaD);
		nMotorEncoder[motorB]=0;
		Line_enc(120, stdPower, "stop");
		wait1Msec(250);
		move_enc(130, stdPower,'b',"stop");
		bricksInRobot[1] = -2;
	}
	if (zahvat1)
	{
		if (!hapuga1 && !hapuga2 && !ifBack)
			stopmotor();
		if (!ifBack)
		{
			if (dom == 0)
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
			if (dom == 0)
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
		//move_enc(30,stdPower,'b',"stop");
		//move_enc(30,stdPower,'f',"stop");
		bricksInRobot[3] = -2;
	}
	if (!zahvat1 && !zahvat2 && !ifBack)
	{
		if (dom == 0)
			povright(stdPower,"");
		else
			povleft(stdPower,"");
	}

	if(col == 0 || dom == 1)
	{
		startTask(hapugaU);
	}
	else
		startTask(hapugaD);

	if (dom == 1)
	{
		Line_enc(400, zonePower, "");
	}

	LineCross(stdPower, "stop");
	for (int i = 0; i < 4; i++)
		finalRazvoz[dom][i] = 0;
	if (bricksInRobot[3] != -2 && zahvatPos != 0)
		wait1Msec(150);
	startTask(zahvatC);
	if (bricksInRobot[3] != -2 && zahvatPos != 0)
		wait1Msec(1300);
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
				for(i1=0; i1<4; i1++)
				{
					if(indDoms[rightWay[col][i]][0] == virtualBricks[i1])
					{
						virtualBricks[i1]=-2;
						break;
					}
				}
				for(i2=0; i2<4; i2++)
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
		//if(nInds[col] == 1 && rightWay[col][i] == 3)
		//{
		//	finalRazvoz[rightWay[col][i]][3] = 1;
		//	ourWay[counter] = rightWay[col][i];
		//	counter++;
		//}
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
	//writeDebugStreamLine("finalRazvoz: ");
	//for(short i = 0; i < 4; i++)
	//{
	//	for(short j = 0; j < 4; j++)
	//	{
	//		writeDebugStream("%d ", finalRazvoz[i][j]);
	//	}
	//	writeDebugStream("\n");
	//}
	//writeDebugStreamLine("ourWay: ");
	//for(short i = 0; i < 3; i++)
	//{
	//	writeDebugStream("%d ", ourWay[i]);
	//}
	//writeDebugStream("\n");
}

void move_to(short destination, const string ifTurn1, const string ifTurn2)
{
	if(location == 7)
	{
		povright(stdPower, "cross");
	}
	if(location == 8)
	{
		move_enc(200, zonePower, 'b', "stop");
		if(ourWay[0] == 1)
		{
			move_enc(TURN, stdPower, 'r', "stop");
		}
		else
		{
			move_enc(TURNAROUND, stdPower, 'r', "stop");
		}
		move_enc(300 - 100*ourWay[0]%2, zonePower, 'f', "");
		fwd_black(2, stdPower, "");
		if(indDoms[0][0] == 2 && indDoms[0][1] == 2)
			povrightSpec(stdPower);
		else if(nInds[2] < 2 || indDoms[1][0] == 2 || indDoms[1][1] == 2)
			povleftSpec(stdPower);
		else
			povleft(stdPower, "cross");

		Line_enc(120, stdPower, "");

		if(ourWay[0] != 1)
		{
			//if(ourWay[0] == 3)
			//{
			//	startTask(hapugaU);
			//}
			location = 3;
		}
	}
	if(location < 7 && location != destination)
	{
		if(ifTurn1 == "turn")
		{
			turning(destination);
		}
		if(location == 4 && (bricksInRobot[0] == 2 || bricksInRobot[1] == 2))
		{
			startTask(hapugaD);
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
	clearDebugStream();
	if (col == 1)
		startTask(hapugaD);
	else
		startTask(hapugaU);

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

	for(short i = 0; i < 4; i++)
	{
		if(col == 0)
		{
			if(bricksInRobot[0] > -2 || bricksInRobot[1] > -2 || bricksInRobot[2] > -2 || bricksInRobot[3] > -2)
			{
				if(rightWay[col][i] == 3 && nInds[col] == 2)
					withoutZone++;

				ourWay[i] = rightWay[col][i+withoutZone];
			}
		}
		if(ourWay[i] == -1 || ourWay[i] == -2)
		{
			return;
		}
		ourCrosses[i] = assignment(ourWay[i]);
		writeDebugStreamLine("way: %d", ourWay[i]);
		if(col == 0 && nInds[col] < 2 && ourWay[i] != 3 && bricksInRobot[3] != -2)
		{
			bricksInRobot[1] = -2;
		}
		writeDebugStreamLine("loc: %d", location);
		if(i != 0)
		{
			if(ourWay[i-1] == 3)
			{
				move_to(ourCrosses[i], "", "turn");
			}
		}
		if(col == 1 && ourWay[i] != 1 && i == 0)
		{
			move_to(ourCrosses[i], "", "turn");
		}
		else
		{
			if(ourWay[i] != 3 && ourCrosses[i] != 0)
			{
				move_to(ourCrosses[i], "turn", "turn");
			}
			else
			{
				move_to(ourCrosses[i], "turn", "");
			}
		}
		writeDebugStreamLine("loc: %d", location);
		//for(short i = 0; i<4; i++)
		if(ourWay[i] != 3)
		{
			putInDom(finalRazvoz[ourWay[i]][0], finalRazvoz[ourWay[i]][1], finalRazvoz[ourWay[i]][2], finalRazvoz[ourWay[i]][3], ourWay[i], col);
		}
		else
		{
			if(i == 0)
			{
				povleft(stdPower, "cross");
				Line_enc(250, stdPower, "stop");
				move_enc(TURNAROUND, stdPower, 'r', "stop");
				LineCross(stdPower, "");
			}
			else
			{
				if(ourWay[i-1] == 2)
				{
					ifCrossAkkum = "";
					Line_enc(CROSS_ENC-20, stdPower, "stop");
					startTask(hapugaU);
					wait1Msec(250);
					if(nInds[2] < 2)
					{
						povright(stdPower, "");
					}
					else
					{
						move_enc(TURN, stdPower, 'l', "stop");
					}
				}
			}
			if(nInds[2] < 2)
			{
				stopmotor();
				akkum_std();
				if(indDoms[0][0] == 2 || indDoms[0][1] == 2)
					povleftSpec(stdPower);
				else
					povleft(stdPower, "cross");
			}
			else
			{
				akkumGB();
				if(indDoms[0][0] == 0 || indDoms[0][1] == 0 || indDoms[0][0] == -1 || indDoms[0][1] == -1)
					povrightSpec(stdPower);
				else
					povright(stdPower, "cross");
			}
		}
		old_location = location;
		location = ourCrosses[i];
		if(col == 0 && bricksInRobot[1] == -2 && ourWay[i] != 3 && ourWay[i] > 0)
		{
			bricksInRobot[1] = 0;
		}
	}
	withoutZone = 0;
}

void takeYellowZone()
{
	startTask(hapugaU);
	Line_enc(250, zonePower, "");
	LineCross(stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(595, stdPower, "stop");

	move_enc(TURN,stdPower,'l',"stop");
	startTask(zahvatO);
	move_enc(160,stdPower,'f',"stop");

	move_enc(240,stdPower,'b',"stop");
	zahvat('c');
	move_enc(15,stdPower,'f',"");
	povleft(stdPower, "cross");

	Line_enc(50, stdPower, "");
	LineCross(zonePower, "");
	Line_enc(400, zonePower, "");
	Line_enc(195+CROSS_ENC, stdPower, "stop");

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
	move_enc(175, stdPower, 'f', "stop");
	mot1_enc(ONEMOTORTURN, 'b', stdPower, 'b', "stop");

	move_enc(160, stdPower, 'f', "stop");
	bricksInRobot[1] = 0;
	hapuga('u');
	move_enc(145,stdPower,'b',"stop");

	move_enc(250,stdPower,'r',"stop");
	fwd_white(3,stdPower,"");
	fwd_black(3, stdPower, "");

	move_enc(240, stdPower, 'f', "stop");
	move_enc(TURN+5, stdPower, 'r', "stop");

	startTask(zahvatM);
	move_enc(50, stdPower, 'f', "stop");
	//zahvat('m');
	move_enc(130, stdPower, 'b', "stop");

	bricksInRobot[3] = 0;
	startTask(zahvatC);
	wait1Msec(1000);

	startTask(hapugaD);
	move_enc(500, zonePower, 'f', "");
	fwd_black(2, stdPower, "stop");

	location = 7;
}

void allocateAllBricks()
{
	takeBlueZone();
	writeDebugStreamLine("Time after blue zone: %d sec", time1[T1] / 1000);
	allocation(0);
	writeDebugStreamLine("Time after first allocation: %d sec", time1[T1] / 1000);
	//takeGreenZone();
	//takeYellowZone();
	//writeDebugStreamLine("Time after yellow zone: %d sec", time1[T1] / 1000);
	//allocation(1);
	//writeDebugStreamLine("Time after second allocation: %d", time1[T1] / 1000);
}


/*
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
} */

#endif
