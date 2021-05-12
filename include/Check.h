#pragma once

#ifndef CHECK_H
#define CHECK_H

task checkY()
{
	readSensor(&colorSensor);
	while(colorSensor.color == 0)
	{
		readSensor(&colorSensor);
	}
	playSoundFile("Yellow");
	exColor = 2;
}

int check_color()
{
	if (colorSensor.color==2 /*|| colorSensor.color==3*/)
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
		back_pass_color(enc, stdPower);

		short color_index = check_color();
		if (color_index != -1)
		{
			nInds[color_index]++;
			indDoms[dom][(i + 1) % 2] = color_index;
		}
	}
}

void take_yellow_ex()
{;
	move_enc(245, stdPower, 'f', "stop");
	startTask(zahvatO);
	hapuga('d');
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND, stdPower, 'l', "stop");
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
	startTask(zahvatO);
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=-stdPower;
	}
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=-stdPower;
	}
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=-stdPower;
	}
	while(SensorValue[S1]>WHITE-5)
	{
		motor[motorB]=-stdPower;
	}
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
	exColor = 1;
	LineCross(stdPower, "");
	Line_enc(285, stdPower, "stop");
	startTask(checkY);
	move_enc(TURNAROUND+25, stdPower, 'l', "");
	stopTask(checkY);

	if(exColor == 2)
	{
		stopmotor();
		move_enc(TURN+60, stdPower, 'r', "stop");
		take_yellow_ex();
		return;
	}

	move_enc(TURNAROUND-40, stdPower, 'l', "stop");
  Line_enc(40,stdPower,"");
	LineCross(lineMaxPower, "");
	Line_enc(20, stdPower, "stop");
	mot1_enc(ONEMOTORTURN, 'b', stdPower, 'f', "stop");
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
	take_blue_ex();
}

void approachToBlueNew()
{
	povrightSpec(stdPower);
	Line1_enc(360, stdPower, "stop");
	perebros(stdPower);
	Line1Cross(stdPower, "stop");
	move_enc(24, stdPower, 'b', "stop");
	move_enc(TURN, stdPower, 'l', "stop");
}

void checkAllField()
{
	//checkDom1();
	//writeDebugStreamLine("Time after dom1: %d", time1[T1] / 1000);
	checkExcess();
	writeDebugStreamLine("Time after excess: %d", time1[T1] / 1000);
	//checkDom2();
	akkum_std();
	writeDebugStreamLine("Time after put excess: %d", time1[T1] / 1000);
	//checkDom3();
	//approachToBlue();
	approachToBlueNew();
	writeDebugStreamLine("Time after checking all field: %d", time1[T1] / 1000);
	writeDebugStreamLine("pauseCounter: %d", pauseCounter);
}

#endif
