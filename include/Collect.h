#pragma once

#ifndef CHECK_H
#define CHECK_H

#define DOM1PASS1 200
#define DOM1PASS2 66
#define BACK_PASS1 265
#define BACK_PASS2 230


task checkY()
{
	Line1S3(stdPower, 'r');
	readSensor(&colorSensor);
	short j = 0;
	while(j < 3 || nMotorEncoder[motorB] < 300)
	{
		Line1S3(stdPower, 'r');
		readSensor(&colorSensor);
		writeDebugStreamLine("R: %d, G: %d", colorSensor.red, colorSensor.green);
		while(colorSensor.red < 6 && colorSensor.green < 6)
		{
			Line1S3(stdPower, 'r');
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
	Line1S3(stdPower, 'r');
	readSensor(&colorSensor);
	short j = 0;
	while(j < 3 || nMotorEncoder[motorB] < 600)
	{
		Line1S3(stdPower, 'r');
		readSensor(&colorSensor);
		writeDebugStreamLine("G: %d, B: %d", colorSensor.green, colorSensor.blue);
		while(colorSensor.green < 10 && colorSensor.blue < 10)
		{
			Line1S3(stdPower, 'r');
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
	move_enc(256, stdPower, 'f', "stop");
  move_enc(TURNR, stdPower, 'r', "stop");
  moving (stdPower, 'f');
	wait1Msec(900);
	motorStop();
	indDoms[0][0] = check_ind(DOM1PASS1, stdPower, 0);
	motorStop();
	indDoms[0][1] = check_ind(DOM1PASS2, stdPower, 0);
	motorStop();
	turn90(stdPower, 'r', "stop");
	fwd_black(1, stdPower, "");
	while(SensorValue[S1] < GREY)
		moving(stdPower, 'f');
	motorStop();
	move_enc(TURNR-100, zonePower, 'r', "");
	while(SensorValue[S3] > BLACK)
		moving(stdPower, 'r');
	move_enc(55, stdPower, 'r', "stop");
	startTask(hapugaO);
}

bool check_yellow_ex()
{
	exColor = 0;
	Line1S3Cross(stdPower, 'r', "stop");
	startTask(checkY);
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 333)
	{
		Line1S3(zonePower, 'r');
	}

	if(exColor == 2)
		return true;
	else
		return false;
}

bool check_green_ex()
{
	Line1S3_enc(125, stdPower, 'r', "");
	Line1S3Cross(zonePower, 'r', "");
	startTask(checkG);
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 762)
	{
		Line1S3(stdPower, 'r');
	}

	if(exColor == 1)
		return true;
	else
		return false;
}

void take_yellow_ex()
{
	motorStop();
	turn90(stdPower, 'l', "stop");

	move_enc(245, stdPower, 'f', "stop");
	startTask(zahvatO);
	hapuga('m');
	startTask(hapugaC);
	wait1Msec(75);
	move_enc(70, stdPower, 'b', "stop");
	turn180(stdPower, 'r', "stop");
	move_enc(260, stdPower, 'b', "stop");
	wait10Msec(5);
	zahvat('m');
	startTask(zahvatC);
	wait1Msec(75);

	move_enc(230, lineMaxPower, 'f', "");
	fwd_black(2, stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	Line_enc(2375, lineMaxPower, "");
	bricksInRobot[0] = -1;
	bricksInRobot[2] = -1;
}

void take_green_ex()
{
	motorStop();
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
	hapuga('m');
	startTask(hapugaC);
	wait1Msec(75);
	move_enc(50, stdPower, 'b', "stop");
	turn180(stdPower, 'l', "stop");
	move_enc(250, stdPower, 'b', "stop");
	zahvat('m');
	startTask(zahvatC);
	wait1Msec(75);

	//move_enc(120, zonePower, 'f', "stop");
	fwd_black(3, stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	Line_enc(925, lineMaxPower, "");
	bricksInRobot[0] = -1;
	bricksInRobot[2] = -1;
}

void take_blue_ex()
{
	Line1S3_enc(1000, lineMaxPower, 'r', "");
	Line1S3Cross(stdPower, 'r', "stop");

	mot1_enc(200, 'b', stdPower, 'b', "");
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=-stdPower;
	}
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=-stdPower;
	}
	motorStop();
	//mot1_enc(5, 'b', stdPower, 'b', "stop");

	move_enc(280, stdPower, 'b', "stop");
	wait1Msec(50);
	startTask(hapugaO);
	zahvat('m');
	startTask(zahvatC);
	wait1Msec(75);
	move_enc(40, stdPower, 'f', "stop");
	turn180(stdPower, 'l', "stop");
	move_enc(275, stdPower, 'f', "stop");
	hapuga('m');
	startTask(hapugaC);
	wait1Msec(75);

	move_enc(200, zonePower, 'b', "");
	while(SensorValue[S3] > BLACK)
		moving(stdPower, 'b');
	motorStop();
	move_enc(CROSS_ENC-3, stdPower, 'f', "stop");
	povright(stdPower, "");
	bricksInRobot[0] = -1;
	bricksInRobot[2] = -1;
}

void approachToBlue()
{
	Line1S3Cross(stdPower, 'l', "");
	Line1S3_enc(91, stdPower, 'l', "stop");
	mot1_enc(ONEMOTORTURN-125, 'b', zonePower, 'f', "");
	while(SensorValue[S1] > BLACK)
		motor[motorB] = 25;
	while(SensorValue[S1] < GREY-15)
		motor[motorB] = 15;
	motorStop();
}
void takeBlueZone()
{
	nMotorEncoder[motorB]=0;
	Line1S1_enc(50, 20, 'l', "");
	Line1S1_enc(150, 20, 'l', "");
	Line1S1White(20, 'l', "stop");
	turn90(stdPower, 'l', "stop");
	bricksInRobot[3] = 0;
	startTask(zahvatM);
	move_enc(110, stdPower, 'f', "stop");
	wait1Msec(100);
	move_enc(40, stdPower, 'b', "stop");
	startTask(zahvatC);
	wait1Msec(750);

	turn90(stdPower, 'r', "stop");
	fwd_white(1, zonePower, "");
	fwd_black(1, zonePower, "");

	move_enc(265, zonePower, 'f', "stop");
	turn90(stdPower, 'r', "stop");

	bricksInRobot[1] = 0;
	startTask(hapugaM);
	wait1Msec(400);
	//move_enc(7, zonePower, 'b', "stop");
	move_enc(77, stdPower, 'f', "stop");

	bricksInRobot[3] = 0;
	startTask(hapugaC);
	wait1Msec(750);

	move_enc(50, stdPower, 'b', "");
	move_enc(500, zonePower, 'b', "");
	indDoms[1][1] = check_ind(BACK_PASS1, stdPower, 1);
	indDoms[1][0] = check_ind(BACK_PASS2, stdPower, 1);
	while(SensorValue[S1] > BLACK)
		moving(stdPower, 'b');
	motorStop();
	move_enc(CROSS_ENC + POV_DIFF, stdPower, 'f', "stop");
	location = 8;
}

void take_ex_and_blue()
{
	writeDebugStreamLine("Time after dom1: %d", time1[T1] / 1000);

	if(check_yellow_ex())
		take_yellow_ex();

	else if(check_green_ex())
		take_green_ex();

	else
		take_blue_ex();

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
		LineCross(ZonePower,"");
		Line_enc(275,stdPower,"stop");
		turn90(stdPower, 'r', "stop");
		while (SensorValue[S2]>(WHITE-20))
			moving('b',stdPower);
		motorStop();
	}
	if (location == 7)
	{
		povleftSpec(stdPower);
		Line1Cross(stdPower,"stop");
		move_enc(CROSS_ENC,stdPower,'f',"stop");
		mot1_enc(ONEMOTORTURN,'c',stdPower,'b', "stop");
	  move_enc(CROSS_ENC,stdPower,'f',"stop");
	}
}

void takeGreenZone()
{
	hapuga('g');
	wait1Msec(500);
	move_enc(30, stdPower,'f',"stop");
	motor[motorA] = -15;
	wait10Msec(30);
	move_enc(30, stdPower,'b',"stop");
	motor[motorA] = 0;
	povright(stdPower,"");
	//LineCross(stdPower,"stop");
	Line_enc(340, stdPower,"stop");
	turn90(stdPower, 'r', "stop");
	move_enc(100, stdPower,'f',"stop");
	zahvat('g');
	wait1Msec(500);
	move_enc(100, stdPower,'b',"stop");
	motor[motorD] = -25;
	wait1Msec(500);
	mot1_enc(250, 'b', stdPower, 'f', "");
	while(SensorValue[S2]>BLACK)
		motor[motorB]=stdPower;
	motorStop();
	motor[motorD] = 0;
	mot1_enc(365, 'c', stdPower, 'f', "stop");
	bricksInRobot[1] = 1; bricksInRobot[3] = 1;
}

void takeYellowZone()
{
	Line_enc(275, lineMaxPower, "");
	LineCross(stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	startTask(hapugaO);
	Line_enc(465, lineMaxPower, "");
	Line_enc(75, stdPower, "stop");

	turn90(stdPower, 'r', "stop");
	move_enc(130, stdPower, 'f', "stop");
	hapuga('m');
	startTask(hapugaC);
	wait1Msec(800);
	move_enc(130-18, zonePower, 'b', "stop");
	povright(stdPower, "");

	Line_enc(50, stdPower, "");
	LineCross(zonePower, "");
	Line_enc(600, lineMaxPower, "");
	Line_enc(CROSS_ENC, stdPower, "stop");

	turn90(stdPower, 'r', "stop");
	zahvat('o');
	move_enc(135, stdPower, 'b', "stop");

	zahvat('m');
	startTask(zahvatC);
	wait1Msec(800);
	move_enc(175, lineMaxPower, 'f', "stop");
	turn90(stdPower, 'l', "stop");
	move_enc(400, lineMaxPower, 'f', "");
	fwd_black(1, zonePower, "");
	move_enc(CROSS_ENC, stdPower, 'f', "stop");
	location = 8;
	bricksInRobot[0] = 2; bricksInRobot[2] = 2;
}

#endif
