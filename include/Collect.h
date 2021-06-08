#pragma once

#ifndef CHECK_H
#define CHECK_H

#define ENC1_DOM1 160
#define ENC2_DOM1 110

task checkY()
{
	readSensor(&colorSensor);
	short j = 0;
	while(j < 10 && nMotorEncoder[motorB] < 300)
	{
		readSensor(&colorSensor);
		while(colorSensor.red < 5 && colorSensor.green < 5)
		{
			if(colorSensor.red < 5 && colorSensor.green < 5)
				j = 0;

			readSensor(&colorSensor);
		}
		j++
		if(j == 10)
		{
			playSoundFile("Yellow");
			exColor = 2;
		}
	}
}

task checkG()
{
	readSensor(&colorSensor);
	short j = 0;
	while(j < 10 && nMotorEncoder[motorB] < 300)
	{
		readSensor(&colorSensor);
		while(colorSensor.green < 5)
		{
			if(colorSensor.green < 5)
				j = 0;

			readSensor(&colorSensor);
		}
		j++
		if(j == 10)
		{
			playSoundFile("Green");
			exColor = 1;
		}
	}
}

int check_color(short dom)
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
		if(dom != 0)
		{
			while(nMotorEncoder[motorB] > nEncB - 15)
			{
				readSensor(&colorSensor);
				if(colorSensor.color == 4)
				{
					playSoundFile("Green");
					return 1;
				}
				if(colorSensor.color == 6)
				{
					playSoundFile("Yellow");
					return 2;
				}
				moving(stdPower, 'b');
			}
		}
		if(dom == 0)
		{
			while(nMotorEncoder[motorB] < nEncB + 15)
			{
				readSensor(&colorSensor);
				if(colorSensor.color == 4)
				{
					playSoundFile("Green");
					return 1;
				}
				if(colorSensor.color == 6)
				{
					playSoundFile("Yellow");
					return 2;
				}
				moving(stdPower, 'f');
			}
		}
		readSensor(&colorSensor);
		//if(colorSensor.color == 4)
		//{
		//	playSoundFile("Green");
		//	return 1;
		//}
		//if(colorSensor.color == 6)
		//{
		//	playSoundFile("Yellow");
		//	return 1;
		//}
		//else
		//{
		playSoundFile("Blue");
		return 0;
		//}
	}
	else
	{
		playSoundFile("Dog bark 1");
		return -1;
	}
}

void check_ind(short dom, short nEnc1, short nEnc2)
{
	//for (int i = 0; i < 2; i++)
	//{
	//	short enc = (i == 0) ? nEnc1 : nEnc2;
	//	if(dom != 0)
	//	{
	//		back_pass_color(enc, stdPower);
	//	}
	//	else
	//	{
	//		pass_color(enc, stdPower);
	//	}
	//	short color_index = check_color(dom);
	//	if (color_index != -1)
	//	{
	//		nInds[color_index]++;
	//		indDoms[dom][(dom != 0) ? (i + 1) % 2 : i] = color_index;
	//	}
	//}

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
	move_enc(273, stdPower, 'f', "stop");
	move_enc(TURN, 50, 'r', "stop");

	moving(50, 'f');
	wait10Msec(70);
	stopmotor();

	check_ind(0, ENC1_DOM1, ENC2_DOM1);
	move_enc(TURN, stdPower, 'r', "stop");
	fwd_black(3, zonePower, "");
	povright(stdPower, "cross");
}

void take_yellow_ex()
{
	move_enc(245, stdPower, 'f', "stop");
	startTask(zahvatO);
	hapuga('c');
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND-12, stdPower, 'l', "stop");
	move_enc(260, stdPower, 'b', "stop");
	wait10Msec(5);
	zahvat('c');

	move_enc(250, lineMaxPower, 'f', "");

	fwd_black(1, stdPower, "");
	povleftSpec(stdPower);
}

void take_green_ex()
{
	move_enc(165, stdPower, 'f', "stop");
	wait1Msec(50);
	startTask(zahvatO);
	hapuga('c');
	move_enc(70, stdPower, 'b', "stop");
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(200, stdPower, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND+18, stdPower, 'l', "stop");
	fwd_white(3, stdPower, "");
	fwd_black(3, stdPower, "");
	povright(stdPower, "cross");
	LineCross(stdPower, "stop");
	povleftSpec(stdPower);
}

void take_blue_ex()
{
	startTask(zahvatO);
	mot1_enc(200, 'b', stdPower, 'b', "");
	while(SensorValue[S1]>BLACK)
	{
		motor[motorB]=-stdPower;
	}
	while(SensorValue[S1]<WHITE)
	{
		motor[motorB]=-stdPower;
	}
	mot1_enc(82, 'b', stdPower, 'b', "stop");
	move_enc(200, stdPower, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND, stdPower, 'l', "stop");
	move_enc(265, stdPower, 'f', "stop");
	wait1Msec(30);
	hapuga('c');
	move_enc(TURN, zonePower, 'l', "stop");
	move_enc(200, zonePower, 'f', "");
	fwd_white(1, zonePower, "");
	fwd_black(1, stdPower, "");
	povleft(stdPower, "cross");
	Line_enc(75, stdPower, "");
	Line_enc(200, lineMaxPower, "");
	LineCross(stdPower, "stop");
}

void check_and_take_ex()
{
	exColor = 0;
	LineCross(stdPower, "stop");
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 300)
	{
		Line(stdPower);
		startTask(checkY);
	}
	stopmotor();

	if(exColor == 2)
	{
		move_enc(TURN, stdPower, 'l', "stop");
		take_yellow_ex();
		return;
	}

	mot1_enc(160, 'c', stdPower, 'f', "stop");
	mot1_enc(150, 'b', stdPower, 'f', "stop");
	Line_enc(80, stdPower, "");
	LineCross(zonePower, "");
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 300)
	{
		Line(stdPower);
		startTask(checkG);
	}
	stopmotor();

	if(exColor == 1)
	{
		move_enc(TURN, stdPower, 'l', "stop");
		take_green_ex();
		return;
	}

	stopmotor();
	LineCross(lineMaxPower, "stop");
	take_blue_ex();
}

void approachToBlue()
{
	move_to(6, "", "");
	move_enc(35, stdPower, 'b', "stop");
	move_enc(TURN, stdPower, 'l', "stop");
}

/*void takeBlueZone()
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

	move_enc(140, stdPower, 'f', "stop");
	bricksInRobot[1] = 0;
	hapuga('u');
	move_enc(110,stdPower,'b',"stop");

	move_enc(250,stdPower,'r',"stop");
	fwd_white(3,stdPower,"");
	fwd_black(3, stdPower, "");

	move_enc(230, stdPower, 'f', "stop");
	move_enc(TURN+3, stdPower, 'r', "stop");

	startTask(zahvatM);
	move_enc(50, stdPower, 'f', "stop");
	//zahvat('m');
	move_enc(105, stdPower, 'b', "stop");

	bricksInRobot[3] = 0;
	startTask(zahvatC);
	wait1Msec(1000);

	startTask(hapugaD);
	move_enc(500, zonePower, 'f', "");
	fwd_black(2, stdPower, "stop");

	location = 7;
}*/

void take_ex_and_blue()
{
	checkDom1();
	//writeDebugStreamLine("Time after dom1: %d", time1[T1] / 1000);
	check_and_take_ex();
	writeDebugStreamLine("Time after excess: %d", time1[T1] / 1000);
	//checkDom2();
	writeDebugStreamLine("Time after put excess: %d", time1[T1] / 1000);
	//checkDom3();
	//approachToBlue();
	approachToBlue();
	//takeBlueZone
	writeDebugStreamLine("Time after checking all field: %d", time1[T1] / 1000);
	writeDebugStreamLine("pauseCounter: %d", pauseCounter);
}


/*void takeGreenZone()
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
} */
#endif
