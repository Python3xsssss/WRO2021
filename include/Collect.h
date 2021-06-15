#pragma once

#ifndef CHECK_H
#define CHECK_H

#define RIGHT_PASS1 238
#define RIGHT_PASS2 250
#define BACK_PASS1 240
#define BACK_PASS2 140


task checkY()
{
	Line1S3(stdPower);
	readSensor(&colorSensor);
	short j = 0;
	while(j < 3 || nMotorEncoder[motorB] < 300)
	{
		Line1S3(stdPower);
		readSensor(&colorSensor);
		writeDebugStreamLine("R: %d, G: %d", colorSensor.red, colorSensor.green);
		while(colorSensor.red < 6 && colorSensor.green < 6)
		{
			Line1S3(stdPower);
			j = 0;
			readSensor(&colorSensor);
			writeDebugStreamLine("R: %d, G: %d", colorSensor.red, colorSensor.green);
			if(nMotorEncoder[motorB] >= 300)
				return;
		}
		j++;
		if(j == 3)
		{
			playSoundFile("Yellow");
			exColor = 2;
			return;
		}
		wait10Msec(5);
	}
}

task checkG()
{
	Line1S3(stdPower);
	readSensor(&colorSensor);
	short j = 0;
	while(j < 3 || nMotorEncoder[motorB] < 600)
	{
		Line1S3(stdPower);
		readSensor(&colorSensor);
		writeDebugStreamLine("G: %d, B: %d", colorSensor.green, colorSensor.blue);
		while(colorSensor.green < 10 && colorSensor.blue < 10)
		{
			Line1S3(stdPower);
			j = 0;
			readSensor(&colorSensor);
			writeDebugStreamLine("G: %d, B: %d", colorSensor.green, colorSensor.blue);
			if(nMotorEncoder[motorB] >= 600)
				return;
		}
		j++;
		if(j == 3)
		{
			playSoundFile("Green");
			exColor = 1;
			return;
		}
		wait10Msec(3);
	}
}

/*
if (smth == true)
variable = a;
else
variable = b;

variable = (smth == true) ? a : b;
*/

void checkDom1()
{
	move_enc(290, stdPower, 'f', "stop");
	indDoms[0][0] = check_ind(RIGHT_PASS1, 20, 0);
	indDoms[0][1] = check_ind(RIGHT_PASS2, stdPower, 0);
	move_enc(TURNAROUND-RIGHT_PASS1-RIGHT_PASS2, stdPower, 'r', "stop");

	fwd_black(1, zonePower, "");
	fwd_white(1, stdPower, "stop");
	move_enc(TURN, stdPower, 'r', "stop");
	startTask(hapugaO);
}

bool check_yellow_ex()
{
	exColor = 0;
	Line1S3Cross(stdPower, "stop");
	startTask(checkY);
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 333)
	{
		Line1S3(stdPower);
	}

	if(exColor == 2)
		return true;
	else
		return false;
}

bool check_green_ex()
{
	Line1S3_enc(125, stdPower, "");
	Line1S3Cross(lineMaxPower, "");
	startTask(checkG);
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 762)
	{
		Line1S3(stdPower);
	}

	if(exColor == 1)
		return true;
	else
		return false;
}

void take_yellow_ex()
{
	stopmotor();
	move_enc(TURN, stdPower, 'l', "stop");

	move_enc(245, stdPower, 'f', "stop");
	startTask(zahvatO);
	bricksInRobot[1] = -1;
	hapuga('m');
	bricksInRobot[1] = -2;
	startTask(hapugaC);
	wait1Msec(75);
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND-12, stdPower, 'l', "stop");
	move_enc(260, stdPower, 'b', "stop");
	wait10Msec(5);
	bricksInRobot[3] = -1;
	zahvat('m');
	bricksInRobot[3] = -2;
	startTask(zahvatC);
	wait1Msec(75);

	move_enc(230, lineMaxPower, 'f', "");
	fwd_black(2, stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	Line_enc(2375, lineMaxPower, "");
}

void take_green_ex()
{
	stopmotor();
	mot1_enc(200, 'c', stdPower, 'b', "");
	while(SensorValue[S3]>BLACK)
	{
		motor[motorC]=stdPower;
	}
	while(SensorValue[S3]<WHITE)
	{
		motor[motorC]=stdPower;
	}
	mot1_enc(202, 'c', stdPower, 'b', "stop");

	move_enc(240, stdPower, 'f', "stop");
	wait1Msec(50);
	startTask(zahvatO);
	bricksInRobot[1] = -1;
	hapuga('m');
	bricksInRobot[1] = -2;
	startTask(hapugaC);
	wait1Msec(75);
	move_enc(50, stdPower, 'b', "stop");
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(250, stdPower, 'b', "stop");
	bricksInRobot[3] = -1;
	zahvat('m');
	bricksInRobot[3] = -2;
	startTask(zahvatC);
	wait1Msec(75);

	//move_enc(120, zonePower, 'f', "stop");
	fwd_black(3, stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	Line_enc(925, lineMaxPower, "");
}

void take_blue_ex()
{
	Line1S3_enc(1000, lineMaxPower, "");
	Line1S3Cross(stdPower, "stop");

	mot1_enc(200, 'b', stdPower, 'b', "");
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=-stdPower;
	}
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=-stdPower;
	}
	mot1_enc(5, 'b', stdPower, 'b', "stop");

	move_enc(280, stdPower, 'b', "stop");
	wait1Msec(50);
	startTask(hapugaO);
	bricksInRobot[3] = -1;
	zahvat('m');
	bricksInRobot[3] = -2;
	startTask(zahvatC);
	wait1Msec(75);
	move_enc(40, stdPower, 'f', "stop");
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(275, stdPower, 'f', "stop");
	bricksInRobot[1] = -1;
	hapuga('m');
	bricksInRobot[1] = -2;
	startTask(hapugaC);
	wait1Msec(75);

	move_enc(200, zonePower, 'b', "");
	while(SensorValue[S1] < WHITE)
		moving(stdPower, 'b');
	stopmotor();
	povright(stdPower, "");
}

void approachToBlue()
{
	LineCross(stdPower, "");
	Line_enc(70, stdPower, "stop");
	mot1_enc(ONEMOTORTURN, 'b', stdPower, 'f', "stop");
}

void takeBlueZone()
{
	nMotorEncoder[motorB]=0;
	Line1S1_enc(50, stdPower, "");
	Line1S1_enc(150, zonePower, "");
	Line1S1White(stdPower, "stop");
	move_enc(TURN, stdPower, 'l', "stop");
	bricksInRobot[3] = 0;
	startTask(zahvatM);
	move_enc(110, zonePower, 'f', "stop");
	wait10Msec(100);
	move_enc(40, lineMaxPower, 'b', "stop");
	startTask(zahvatC);
	wait1Msec(750);

	move_enc(TURN+3, stdPower, 'r', "stop");
	fwd_white(1, zonePower, "");
	fwd_black(1, zonePower, "");

	move_enc(272, zonePower, 'f', "stop");
	move_enc(TURN+4, stdPower, 'r', "stop");

	bricksInRobot[1] = 0;
	startTask(hapugaM);
	wait1Msec(400);
	//move_enc(7, zonePower, 'b', "stop");
	move_enc(77, zonePower, 'f', "stop");

	bricksInRobot[3] = 0;
	startTask(hapugaC);
	wait1Msec(750);

	move_enc(550, lineMaxPower, 'b', "");
	indDoms[1][1] = check_ind(BACK_PASS1, stdPower, 1);
	indDoms[1][0] = check_ind(BACK_PASS2, stdPower, 1);
	while(SensorValue[S1] < WHITE)
		moving(stdPower, 'b');
	stopmotor();
	location = 8;
}

void take_ex_and_blue()
{
	checkDom1();
	writeDebugStreamLine("Time after dom1: %d", time1[T1] / 1000);

	if(check_yellow_ex())
	{
		take_yellow_ex();
	}

	else if(check_green_ex())
	{
		take_green_ex();
	}

	else
	{
		take_blue_ex();
	}
	writeDebugStreamLine("Time after excess: %d", time1[T1] / 1000);

	approachToBlue();
	takeBlueZone();
	writeDebugStreamLine("Time after taking excess and blue: %d", time1[T1] / 1000);
	writeDebugStreamLine("pauseCounter: %d", pauseCounter);
}

void approachToGreen()
{
	if (location == 1)
	{
		povright(stdPower,"cross");
		LineCross(stdPower,"");
		Line_enc(250,stdPower,"stop");
		move_enc(TURN,stdPower,'r',"stop");
		while (SensorValue[S2]>(WHITE-20))
			moving('b',stdPower);
		stopmotor();
	}
	if (location == 7)
	{
		povleftSpec(stdPower);
		Line1Cross(stdPower,"stop");
		move_enc(50,stdPower,'f',"stop");
		mot1_enc(ONEMOTORTURN,'c',stdPower,'b', "stop");
	}
}

void takeGreenZone()
{
	hapuga('g');
	move_enc(60, stdPower,'f',"stop");
	motor[motorA] = -25;
	move_enc(60, stdPower,'b',"stop");
	motor[motorA] = 0;
	povright(stdPower,"");
	LineCross(stdPower,"stop");
	Line_enc(250, stdPower,"stop");
	move_enc(TURN,stdPower,'r',"stop");
	move_enc(100, stdPower,'f',"stop");
	zahvat('g');
	move_enc(100, stdPower,'b',"stop");
	motor[motorD] = -25;
	while(SensorValue[S2]>BLACK)
		motor[motorB]=stdPower;
	stopmotor();
	motor[motorD] = 0;
	mot1_enc(200,'c',stdPower,'f',"stop");
	bricksInRobot[1] = 1; bricksInRobot[3] = 1;
}

void takeYellowZone()
{
	Line_enc(50, stdPower, "");
	Line_enc(350, lineMaxPower, "");
	LineCross(stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	startTask(hapugaO);
	Line_enc(465, lineMaxPower, "");
	Line_enc(75, stdPower, "stop");

	move_enc(TURN, stdPower, 'r', "stop");
	move_enc(130, stdPower, 'f', "stop");
	hapuga('m');
	startTask(hapugaC);
	wait1Msec(100);
	move_enc(110, zonePower, 'b', "stop");
	povright(stdPower, "");

	Line_enc(50, stdPower, "");
	LineCross(zonePower, "");
	Line_enc(600, lineMaxPower, "");
	Line_enc(CROSS_ENC, stdPower, "stop");

	move_enc(TURN-150, stdPower, 'r', "");
	startTask(zahvatO);
	move_enc(150, stdPower, 'r', "stop");
	wait1Msec(700);
	move_enc(135, stdPower, 'b', "stop");

	zahvat('m');
	startTask(zahvatC);
	wait1Msec(100);
	move_enc(125, lineMaxPower, 'f', "stop");
	move_enc(TURN, stdPower, 'l', "stop");
	move_enc(400, lineMaxPower, 'f', "");
	fwd_black(1, zonePower, "");
	move_enc(CROSS_ENC, stdPower, 'f', "stop");
	location = 8;
	bricksInRobot[0] = 2; bricksInRobot[2] = 2;
}

#endif
