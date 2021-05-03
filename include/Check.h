#pragma once

#ifndef CHECK_H
#define CHECK_H

short indDoms[3][2] = {{-1, -1}, {-1, -1}, {-1, -1}}; // indDoms[0][0] - color index of first indicator in first dom
short nInds[3] = {0, 0, 0}; // nInds[0] - num of blue indicators, etc.
short exColor;

int check_color()
{
	if (colorSensor.color==2 || colorSensor.color==3)
	{
		return 0;
	}
	else if (colorSensor.color==4)
	{
		return 1;
	}
	else if (colorSensor.color==6)
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

void check_ind(short dom)
{
	for (int i = 0; i < 2; i++)
	{
		pass_color(120, v); //
		short color_index = check_color();
		if (color_index != -1)
		{
			nInds[color_index]++;
			indDoms[dom][(dom == 0) ? (i + 1) % 2 : i] = color_index;
		}
	}
}

void checkDom1()
{
	motor[motorD]=-25;
	move_enc(250, v, 'f', "stop");
	move_enc(260, 50, 'l', "stop");
	motor[motorD]=0;

	moving(40, 'f');
	wait10Msec(100);
	stopmotor();

	check_ind(1);
	zahvat('o');

	v=25;
	fwd_black(1, v, "");
	povleft(v, "cross");

	LineCross(v, "");
	povright(v, "cross");
}

void take_yellow_ex()
{
	mot1_enc(200, 'b', v, 'f', "stop");
	mot1_enc(180, 'c', v, 'f', "stop");
	move_enc(100, v, 'b', "stop");
	Line1Cross(v, "");
	Line_enc(20, v, "stop");
	mot1_enc(550, 'b', v, 'b', "stop");
	move_enc(420, v, 'f', "stop");
	hapuga('d');
	move_enc(70, v, 'b', "stop");
	move_enc(TURNAROUND-10, 25, 'l', "stop");
	move_enc(260, v, 'b', "stop");
	wait10Msec(10);
	zahvat('c');
	move_enc(TURN, v, 'l', "stop");
	v=50;

	fwd_black(1, v, "");
	move_enc(400, v, 'f', "");

	fwd_white(2, v, "stop");
	fwd_black(1, v, "");
	v=25;
	povleft(v, "cross");
}

void take_green_ex()
{
	move_enc(20, v, 'f', "stop");
	move_enc(TURN, v, 'r', "stop");
	move_enc(180, v, 'f', "stop");
	wait1Msec(50);
	hapuga('d');
	move_enc(70, v, 'b', "stop");
	move_enc(TURNAROUND, v, 'l', "stop");
	move_enc(200, v, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND, v, 'l', "stop");
	fwd_black(3, v, "");
	povleft(v, "cross");
}


void take_blue_ex()
{
	move_enc(255, v, 'b', "stop");
	zahvat('c');
	move_enc(TURNAROUND, v, 'l', "stop");
	move_enc(265, v, 'f', "stop");
	wait1Msec(50);
	hapuga('d');
	move_enc(TURN, v, 'l', "stop");
	fwd_black(1, v, "");
	povright(v, "cross");
}

void checkExcess()
{
	Line_enc(300, v, "stop");
	povright(v, "");

	nMotorEncoder[motorB] = 0;
	readSensor(&colorSensor);
	exColor = 2;
	if (!pass_any(550, v))
	{
		exColor -= 1;
	}
	stopmotor();

	if(exColor == 2)
	{
		take_yellow_ex();
		return;
	}

	v=40;
	move_enc(250, v, 'b', "stop");
	povleft(v, "");
	LineCross(v, "");
	v=25;
	Line_enc(30, v, "stop");
	mot1_enc(ONEMOTORTURN, 'b', v, 'f', "stop");
	nMotorEncoder[motorB]=0;
	if (!pass_any(400, v))
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
		moving(v, 'b');
	}
	stopmotor();
	povright(v, "cross");
	LineCross(v, "stop");
	mot1_enc(ONEMOTORTURN, 'b', v, 'b', "stop");
	take_blue_ex();
}

void checkDom2()
{
	//v=40;
	LineRed(v, "stop");
	move_enc(160, v, 'b', "stop");
	move_enc(TURN, 30, 'l', "stop");
	move_enc(450, v, 'b', "stop");
	check_ind(2);
	fwd_black(3, v, "stop");
	povleft(v, "cross");
	Line_enc(200, v, "");
}

void akkum_std()
{
	v=25;
	//v=50;
	while(SensorValue[S2]>15||SensorValue[S3]>15)
	{
		Line(v);
	}
	stopmotor();
	move_enc(TURNAROUND, v, 'l', "stop");
	move_enc(115, v, 'b', "stop");
	zahvat('o');
	fwd_black(2, v, "stop");
	//move_enc(20, v, 'f');
	povright(v, "cross");
}

void checkDom3()
{
	Line_enc(150, v, "stop");
	perebros(v);
	move_enc(TURNAROUND, v, 'l', "stop");
	LineCross(v, "stop");
	povright(v, "cross");
	LineRed(v, "stop");
	move_enc(160, v, 'b', "stop");
	move_enc(TURN, v, 'l', "stop");
	move_enc(450, v, 'b', "stop");
	check_ind(3);
	fwd_black(2, v, "stop");
}

void checkAllField()
{
	checkDom1();
	checkExcess();
	checkDom2();
	akkum_std();
	checkDom3();
}

#endif
