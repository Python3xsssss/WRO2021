#pragma once

#ifndef CHECK_H
#define CHECK_H

#define ENC1_DOM1 160
#define ENC2_DOM1 110

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
	if (colorSensor.color==2)
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
	else if(colorSensor.color==3)
	{
		playSound(soundBlip);
		nEncB = nMotorEncoder[motorB];
		while(nMotorEncoder[motorB] > nEncB - 15)
		{
			moving(stdPower, 'b');
		}
		if(colorSensor.color == 4)
		{
			playSoundFile("Green");
			return 1;
		}
		else
		{
			playSoundFile("Blue");
			return 0;
		}
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
		if(dom != 0)
		{
			back_pass_color(enc, stdPower);
		}
		else
		{
			pass_color(enc, stdPower);
		}

		short color_index = check_color();
		if (color_index != -1)
		{
			nInds[color_index]++;
			indDoms[dom][(dom != 0) ? (i + 1) % 2 : i] = color_index;
		}
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
	move_enc(260, stdPower, 'f', "stop");
	move_enc(TURN+10, 50, 'l', "stop");

	moving(50, 'b');
	wait10Msec(70);
	stopmotor();

	check_ind(0, ENC1_DOM1, ENC2_DOM1);
	move_enc(TURN, stdPower, 'l', "stop");
	fwd_black(3, zonePower, "");
	povright(stdPower, "cross");
}

void take_yellow_ex()
{
	move_enc(245, stdPower, 'f', "stop");
	startTask(zahvatO);
	hapuga('d');
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(260, stdPower, 'b', "stop");
	wait10Msec(5);
	zahvat('c');
	move_enc(TURN, stdPower, 'l', "stop");

	move_enc(25, stdPower, 'f', "");
	move_enc(25, zonePower, 'f', "");
	move_enc(1400, lineMaxPower, 'f', "");

	fwd_black(1, stdPower, "");
	povright(stdPower, "cross");
	Line_enc(100, stdPower, "");
	LineCross(stdPower, "stop");
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
	move_enc(TURNAROUND+18, stdPower, 'l', "stop");
	fwd_white(3, stdPower, "");
	fwd_black(3, stdPower, "");
	povright(stdPower, "cross");
	Line_enc(75, stdPower, "");
	LineCross(stdPower, "stop");
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
	mot1_enc(92, 'b', stdPower, 'b', "stop");
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
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	Line_enc(200, lineMaxPower, "");
	LineCross(stdPower, "stop");
}

void checkExcess()
{
	exColor = 1;
	LineCross(stdPower, "");
	Line_enc(295, stdPower, "stop");
	move_enc(TURN, stdPower, 'l', "");
	startTask(checkY);
	move_enc(TURN+25, stdPower, 'l', "");
	stopTask(checkY);

	if(exColor == 2)
	{
		stopmotor();
		move_enc(TURN+38, stdPower, 'r', "stop");
		take_yellow_ex();
		LineCross(stdPower, "stop");
		return;
	}

	move_enc(TURNAROUND-40, stdPower, 'l', "stop");
  Line_enc(40,stdPower,"");
	Line_enc(620, lineMaxPower, "");
	LineCross(stdPower, "");
	Line_enc(15, stdPower, "stop");
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
	Line1Cross(zonePower, "stop");
	move_enc(35, stdPower, 'b', "stop");
	move_enc(TURN, stdPower, 'l', "stop");
}

void checkAllField()
{
	checkDom1();
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
