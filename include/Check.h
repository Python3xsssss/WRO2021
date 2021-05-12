#pragma once

#ifndef CHECK_H
#define CHECK_H

//#define ENC_DOM1_1 160
//#define ENC_DOM1_2 90
#define ENC_DOM23_1 100
#define ENC_DOM23_2 125

int check_color()
{
	if (colorSensor.color==2 || colorSensor.color==3)
	{
		playSoundFile("Blue");
		return 0;
	}
	else if (colorSensor.color==4)
	{
		playSoundFile("Green");
		return 1;
	}
	else if (colorSensor.color==6)
	{
		playSoundFile("Yellow");
		return 2;
	}
	else
	{
		playSoundFile("Dog bark 1");
		return -1;
	}
}

void check_ind(short dom, short nEnc1, short nEnc2)
{
	for (int i = 0; i < 2; i++)
	{
		short enc = (i == 0) ? nEnc1 : nEnc2;
		if(dom == 0)
		{
			pass_color(enc, stdPower);
		}
		else
		{
			back_pass_color(enc, stdPower);
		}

		short color_index = check_color();
		if (color_index != -1)
		{
			nInds[color_index]++;
			indDoms[dom][(i + 1) % 2] = color_index;
		}
	}
}

//task grip()
//{
//	zahvat('c');
//}

//void checkDom1()
//{
//	motor[motorD]=-25;
//	move_enc(260, stdPower, 'f', "stop");
//	move_enc(TURN+10, 50, 'l', "stop");
//	motor[motorD]=0;

//	moving(50, 'b');
//	wait10Msec(70);
//	stopmotor();

//	check_ind(0, ENC_DOM1_1, ENC_DOM1_2);

//	startTask(grip);

//	fwd_black(1, stdPower, "");
//	povleft(stdPower, "cross");

//	LineCross(zonePower, "");
//	povright(stdPower, "cross");
//}

void take_yellow_ex()
{
	/*
	move_enc(80, stdPower, 'b', "stop");
	mot1_enc(200, 'b', stdPower, 'f', "stop");
	mot1_enc(180, 'c', stdPower, 'f', "stop");

	Line1Cross(stdPower, "");
	Line_enc(20, stdPower, "stop");
	mot1_enc(550, 'b', stdPower, 'b', "stop");
	line_correction(15, "stop");
	wait1Msec(2000);
	*/
	move_enc(TURN, stdPower, 'r', "stop");
	move_enc(245, stdPower, 'f', "stop");
	startTask(zahvatO);
	hapuga('d');
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND-10, stdPower, 'l', "stop");
	move_enc(260, stdPower, 'b', "stop");
	wait10Msec(5);
	zahvat('c');
	move_enc(TURN, stdPower, 'l', "stop");
	stdPower = 50;

	fwd_black(1, lineMaxPower, "");
	move_enc(400, lineMaxPower, 'f', "");

	fwd_white(2, lineMaxPower, "");
	fwd_black(1, stdPower, "");
	//povleft(stdPower, "cross");
	povright(stdPower, "cross");
}

void take_green_ex()
{
	move_enc(5, stdPower, 'f', "stop");
	move_enc(TURN, stdPower, 'r', "stop");
	move_enc(160, stdPower, 'f', "stop");
	wait1Msec(50);
	startTask(zahvatO);
	hapuga('d');
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(200, stdPower, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	fwd_black(3, stdPower, "");
	//povleft(stdPower, "cross");
	povright(stdPower, "cross");
}


void take_blue_ex()
{
	move_enc(200, stdPower, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(265, stdPower, 'f', "stop");
	wait1Msec(30);
	hapuga('d');
	move_enc(TURN, zonePower, 'l', "stop");
	move_enc(200, zonePower, 'f', "");
	fwd_white(1, zonePower, "");
	fwd_black(1, stdPower, "");
	//povright(stdPower, "cross");
	povleft(stdPower, "cross");
}

void checkExcess()
{
	Line_enc(400, zonePower, "stop");
	povright(stdPower, "");
	nMotorEncoder[motorB] = 0;
	readSensor(&colorSensor);
	exColor = 2;
	if (!line_any(350, stdPower))
	{
		exColor -= 1;
	}
	stopmotor();
	writeDebugStreamLine("%d", nMotorEncoder[motorB]);
	if(exColor == 2)
	{
		if(nMotorEncoder[motorB]>300)
		{
			move_enc(nMotorEncoder[motorB]-250, stdPower, 'b', "");
		}
		take_yellow_ex();
		return;
	}

	povright(stdPower, "");
  Line_enc(150,stdPower,"");
	LineCross(lineMaxPower, "");
	Line_enc(20, stdPower, "stop");
	mot1_enc(ONEMOTORTURN+25, 'b', stdPower, 'f', "stop");
	nMotorEncoder[motorB]=0;
	if (!pass_any(400, stdPower))
	{
		exColor -= 1;
	}
	stopmotor();

	if(exColor == 1)
	{
		take_green_ex();
		return;
	}

	while(SensorValue[S1]>BLACK)
	{
		moving(stdPower, 'b');
	}
	stopmotor();
	povright(stdPower, "cross");
	Line_enc(150,stdPower,"");
	LineCross(lineMaxPower, "stop");
	startTask(zahvatO);
	mot1_enc(ONEMOTORTURN, 'b', stdPower, 'b', "stop");
	take_blue_ex();
}

//void checkDom2()
//{
//	bricksInRobot[0] = -1; bricksInRobot[1] = -1;
//	stdPower = 40;
//	LineRed(zonePower, "stop");
//	move_enc(30, stdPower, 'b', "stop");
//	mot1_enc(ONEMOTORTURN, 'c', stdPower, 'b', "stop");
//	check_ind(1, ENC_DOM23_1, ENC_DOM23_2);
//	fwd_black(3, stdPower, "");
//	povleft(stdPower, "cross");
//	while(SensorValue[S2]>BLACK||SensorValue[S3]>BLACK)
//	{
//		Line(stdPower);
//	}
//	stopmotor();
//}

//void checkDom3()
//{
//	povright(stdPower, "cross");
//	Line_enc(400, stdPower, "");

//	perebros(stdPower);
//	move_enc(TURNAROUND, stdPower, 'r', "stop");

//	LineCross(stdPower, "");
//	povright(stdPower, "cross");
//	LineRed(zonePower, "stop");
//	move_enc(30, stdPower, 'b', "stop");
//	mot1_enc(ONEMOTORTURN, 'c', stdPower, 'b', "stop");
//	check_ind(2, ENC_DOM23_1, ENC_DOM23_2);
//	fwd_black(2, stdPower, "");
//}

//void approachToBlue()
//{
//	fwd_white(2, stdPower, "");
//	move_enc(25, stdPower, 'f', "stop");
//	while (SensorValue[S1]<WHITE)
//	{
//		motor[motorB]=stdPower;
//	}
//	while (SensorValue[S1]>BLACK)
//	{
//		motor[motorB]=stdPower;
//	}
//	move_enc(50, stdPower, 'f', "");
//}

void approachToBlueNew()
{
	povrightSpec(stdPower);
	Line1_enc(360, stdPower, "stop");

	perebros(stdPower);
	move_enc(TURNAROUND, stdPower, 'r', "stop");

	Line1Cross(stdPower, "stop");
	move_enc(TURN, stdPower, 'l', "stop");
}

void checkAllField()
{
	//checkDom1();
	writeDebugStreamLine("Time after dom1: %d", time1[T1] / 1000);
	povleft(stdPower, "cross");
	LineCross(stdPower, "");
	checkExcess();
	writeDebugStreamLine("Time after excess: %d", time1[T1] / 1000);
	//checkDom2();
	akkum_std();
	writeDebugStreamLine("Time after dom2 and excess: %d", time1[T1] / 1000);
	//checkDom3();
	//approachToBlue();
	approachToBlueNew();
	writeDebugStreamLine("Time after checking all field: %d", time1[T1] / 1000);
	writeDebugStreamLine("pauseCounter: %d", pauseCounter);
}

#endif
