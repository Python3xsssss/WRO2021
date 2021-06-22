#pragma once

#ifndef TESTLIB_H
#define TESTLIB_H

#define TURNL 254
#define TURNR 252
#define TURNAROUND 500
#define ONEMOTORTURN 505
#define CROSS_ENC 74
#define POV_DIFF 9
#define LINE_POV_DIFF 8
#define SPEC_CROSS_L 35
#define SPEC_CROSS_R 250
#define ZAHVATG 95
#define HAPUGAG 95
#define BEFORE_CROSS 225

//#define LINETOLINE 200

short pauseCounter = 0;
short location, old_location; // location: 0-6 - T-crosses, 7 - accumulator, 8 - from blue zone, 9 - from yellow zone
short sensors = 0;
short indDoms[3][2] = {{-1,-1}, {-1,-1}, {-1,-1}}; // indDoms[0][0] - color index of first indicator in first dom, etc.
short nInds[3] = {0, 0, 0}; // nInds[0] - num of blue indicators, etc.
int encs[6] = {410, 860, 270, 1000, 900, 270};
short bricksInRobot[4] = {-2, -2, -2, -2}; // bricksInRobot[0] - color index of bricks in hapuga, [1] - on hapuga, [2] - in zahvat, [3] - on zahvat
short finalRazvoz[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
short ourWay[5] = {-1, -1, -1, -1, -1};
short our_crosses[5];
short exColor;
short zahvatPos = 2, hap = 2;
//short nEncB = 0;
//short nEncC = 0;
short ifRazgon = 0;
short decrease = 0;
float k1, k2;
bool ifTormoz = false;

int average_enc()
{
	return (abs(nMotorEncoder[motorB]) + abs(nMotorEncoder[motorC])) / 2;
}

void Line(short speed)
{
	if (speed == lineMaxPower)
	{
		k1=0.25;
		k2=15;
	}
	if (speed == stdPower)
	{
		k1=0.2;
		k2=10;
	}
	if(speed == zonePower)
	{
		k1=0.15;
		k2=13;
	}
	sensors = 0;
	static float eold, e, es, u;
	es = SensorValue[S2] - SensorValue[S3];
	e = SensorValue[S2] - SensorValue[S3]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u);
	motor[motorC]=(- speed + u);
}

void Line1(short speed)
{
	if (speed == lineMaxPower)
	{
		k1=0.25;
		k2=15;
	}
	if (speed == stdPower)
	{
		k1=0.2;
		k2=10;
	}
	if(speed == zonePower)
	{
		k1=0.15;
		k2=13;
	}
	sensors = 1;
	static float eold, e, es, u;
	es=SensorValue[S1]-SensorValue[S2];
	e=SensorValue[S1]-SensorValue[S2]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u)*0.97;
	motor[motorC]=(-speed + u)*1.03;
}

void Line1S1(short speed, char side)
{
	k1 = 0.22; k2 = 11;
	static float eold, e, u;
	e = (side == 'l') ? GREY-SensorValue[S1] : SensorValue[S1]-GREY;
	u=k1*e+k2*(e-eold);
	eold=e;
	float kmotB = 0.97, kmotC = 1.03;
	if(side == 'l')
	{
		kmotB = 0.95;
		kmotC = 1.05;
	}

	motor[motorB]=(speed + u)*kmotB;
	motor[motorC]=(-speed + u)*kmotC;
}

void Line1S3(short speed, char side)
{
	k1 = 0.2; k2 = 10;
	static float eold, e, u;
	e = (side == 'r') ? SensorValue[S3]-GREY : GREY-SensorValue[S1];
	u=k1*e+k2*(e-eold);
	eold=e;
	float kmotB = 1.03, kmotC = 0.97;
	if(side == 'l')
	{
		kmotB = 1.01;
		kmotC = 0.99;
	}

	motor[motorB]=(speed + u)*kmotB;
	motor[motorC]=(-speed + u)*kmotC;
}

void stopmotor()
{
	motor[motorB]=0;
	motor[motorC]=0;
	wait1Msec(500);
	pauseCounter++;
}

void Line1S1_enc(int nEnc, short speed, char side, const string ifStop)
{
	nMotorEncoder[motorB]=0;

	while(nMotorEncoder[motorB] < nEnc)
		Line1S1(speed, side);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void Line1S1Cross(short speed, char side, const string ifStop)
{
	while(SensorValue[S3] > BLACK)
		Line1S1(speed, side);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void Line1S1White(short speed, char side, const string ifStop)
{
	while(SensorValue[S3] < WHITE)
		Line1S1(speed, side);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void Line1S3_enc(int nEnc, short speed, char side, const string ifStop)
{
	nMotorEncoder[motorB]=0;

	while(nMotorEncoder[motorB] < nEnc)
		Line1S3(speed, side);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void Line1S3Cross(short speed, char side, const string ifStop)
{
	while(SensorValue[S1] > BLACK)
		Line1S3(speed, side);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void moving(short speed, char dir)
{
	if(dir=='f')
	{
		motor[motorB]=speed;
		motor[motorC]=-speed;
	}
	if(dir=='b')
	{
		motor[motorB]=-speed;
		motor[motorC]=speed;
	}
	if(dir=='l')
	{
		motor[motorB]=speed;
		motor[motorC]=speed;
	}
	if(dir=='r')
	{
		motor[motorB]=-speed;
		motor[motorC]=-speed;
	}
}

void moving_sync(short speed, char dir)
{
	short dirB; short dirC;
	static float kmot = 1, kold = 1;
	static short nEncMotB = 0, nEncMotC = 0;

	if(ifTormoz)
	{
		nEncMotB = 0;
		nEncMotC = 0;
		ifTormoz = false;
	}

	if(motor[motorB] == 0 && motor[motorC] == 0)
	{
		nEncMotB = abs(nMotorEncoder[motorB]);
		nEncMotC = abs(nMotorEncoder[motorC]);
	}
	else if(abs(nMotorEncoder[motorB]) > nEncMotB + 5 && abs(nMotorEncoder[motorC]) > nEncMotC + 5 && (abs(nMotorEncoder[motorB]) % 25 < 5 && abs(nMotorEncoder[motorB]) != 0 && abs(nMotorEncoder[motorC]) != 0))
	{
		kold = (float)kmot;
		kmot = (float)(abs(nMotorEncoder[motorB]) - nEncMotB) / (float)(abs(nMotorEncoder[motorC]) - nEncMotC) * kold;
		nEncMotB = abs(nMotorEncoder[motorB]);
		nEncMotC = abs(nMotorEncoder[motorC]);
	}

	if(dir == 'f')
	{
		dirB = 1;
		dirC = -1;
	}
	if(dir == 'b')
	{
		dirB = -1;
		dirC = 1;
	}
	if(dir == 'r')
	{
		dirB = -1;
		dirC = -1;
	}
	if(dir == 'l')
	{
		dirB = 1;
		dirC = 1;
	}

	motor[motorB] = speed * dirB;
	motor[motorC] = speed * dirC * kmot;

	if(abs(nMotorEncoder[motorB]) > 120 && ifRazgon == 0.5)
		ifRazgon = 0;
}

void razgon_sync(short speed, char dir, int nEnc)
{
	ifRazgon = 1;
	short enc = 0;
	short cur_speed = 14;

	while(abs(motor[motorC]) < speed && abs(motor[motorB]) < speed)
	{
		enc++;

		while(abs(nMotorEncoder[motorB]) < enc + enc / 40 * 3)
		{
			if(abs(nMotorEncoder[motorB]) >= nEnc - decrease*30)
				return;
			moving_sync(cur_speed, dir);
		}
		cur_speed++;
		enc = abs(nMotorEncoder[motorB]);
	}
	ifRazgon = 0.5;
}

void tormoz(float speed, char dir)
{
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	short dirB, dirC;
	ifTormoz = true;

	if(dir == 'f')
	{
		dirB = 1;
		dirC = -1;
	}
	if(dir == 'b')
	{
		dirB = -1;
		dirC = 1;
	}
	if(dir == 'r')
	{
		dirB = -1;
		dirC = -1;
	}
	if(dir == 'l')
	{
		dirB = 1;
		dirC = 1;
	}

	short nEncMotorB = abs(nMotorEncoder[motorB]);
	while(abs(nMotorEncoder[motorB]) < nEncMotorB + 30)
	{
		short diff = nEncMotorB + 30 - abs(nMotorEncoder[motorB]);
		if (abs(motor[motorB]) >= diff)
		{
			motor[motorB] = ((diff > 4) ? diff : 4) * dirB;
			motor[motorC] = ((diff > 4) ? diff : 4) * dirC;
		}
	}

	motor[motorB] = 0;
	motor[motorC] = 0;
}

void razgon(short speed, char dir, int nEnc)
{
	short enc = 9;
	short cur_speed = 10;

	while(cur_speed < speed)
	{
		enc++;

		while(abs(nMotorEncoder[motorB]) < enc + enc / 40 * 3)
		{
			if(average_enc() >= nEnc - decrease * 30)
				return;
			moving(cur_speed, dir);
		}
		cur_speed++;
		enc = abs(nMotorEncoder[motorB]);
	}
}

void move_enc(int nEnc, short speed, char dir, const string ifStop)
{
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;

	if((dir == 'f' || dir == 'b') && nEnc >= 30)
	{
		if((ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP") /*&& dir != 'r' && dir != 'l'*/)
			decrease = 1;

		if(motor[motorB] == 0 && motor[motorC] == 0)
			razgon_sync(speed, dir, nEnc);

		while(abs(nMotorEncoder[motorB]) <= nEnc  - 30*decrease)
			moving_sync(speed, dir);

		if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			tormoz(speed, dir);
	}

	else if (nEnc < 30)
	{
		while(average_enc() < nEnc)
			moving(speed, dir);

		if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			stopmotor();
	}

	else if(dir == 'r' || dir == 'l')
	{
		if((ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP") /*&& dir != 'r' && dir != 'l'*/)
			decrease = 1;

		if(motor[motorB] == 0 && motor[motorC] == 0)
			razgon(speed, dir, nEnc);

		while(average_enc() < nEnc - 30*decrease)
			moving(speed, dir);

		if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			tormoz(speed, dir);
	}

	decrease = 0;
}

void turn90(short speed, char dir, const string ifStop)
{
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;

	if((ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP") /*&& dir != 'r' && dir != 'l'*/)
		decrease = 1;
	else
		decrease = 0;

	if(motor[motorB] == 0 && motor[motorC] == 0)
		razgon(speed, dir, (TURNL + TURNR)/2);

	while(nMotorEncoder[motorB] < TURNL - 30*decrease && nMotorEncoder[motorC] > -TURNR + 30*decrease)
		moving(speed, dir);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		tormoz(speed, dir);
}

void povright(short speed, const string ifCross)
{
	if (ifCross == "cross" || ifCross == "Cross" || ifCross == "CROSS")
	{
		move_enc(CROSS_ENC + POV_DIFF, speed, 'f', "stop");
	}

	move_enc(70, speed, 'r', "");
	while (SensorValue[S2] < WHITE)
	{
		moving(speed, 'r');
	}
	while (SensorValue[S2] > BLACK)
	{
		moving(speed, 'r');
	}
	while (SensorValue[S2] < WHITE)
	{
		moving(speed, 'r');
	}
	move_enc(26, speed, 'r', "stop");
	//stopmotor();
	stdPower = 25;
	sensors = 0;
}

void povleft(short speed, const string ifCross)
{
	if (ifCross == "cross" || ifCross == "Cross" || ifCross == "CROSS")
	{
		move_enc(CROSS_ENC, speed, 'f', "stop");
	}
	move_enc(70, speed, 'l', "");
	while (SensorValue[S3] < WHITE)
	{
		moving(speed, 'l');
	}
	while (SensorValue[S3] > BLACK)
	{
		moving(speed, 'l');
	}
	while (SensorValue[S3] < WHITE)
	{
		moving(speed, 'l');
	}
	move_enc(26, speed, 'l', "stop");
	//stopmotor();
	stdPower = 25;
	sensors = 0;
}

void LineRed(short speed, const string ifStop)
{
	getColorName(S1);
	while(getColorName(S1)!=5)
	{
		Line(speed);
	}

	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
	getColorReflected(S1);
}

void LineCross(short speed, const string ifStop)
{
	while(SensorValue[S1] > BLACK)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void Line1Cross(short speed, const string ifStop)
{
	while(SensorValue[S3] > BLACK)
	{
		Line1(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void lineWhite(short speed, const string ifStop)
{
	while(SensorValue[S1]<WHITE+3)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void line1White(short speed, const string ifStop)
{
	while(SensorValue[S3]<WHITE)
	{
		Line1(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void razgon_line(short speed, int nEnc)
{
	short cur_speed = 10;
	short enc = nMotorEncoder[motorB];
	while(cur_speed < speed)
	{
		if(nEnc >= average_enc())
			return;

		while(nMotorEncoder[motorB] < enc + 2)
			Line(cur_speed);

		enc = nMotorEncoder[motorB];
		cur_speed++;
	}
}

void razgon_line1(short speed, int nEnc)
{
	short cur_speed = 10;
	short enc = nMotorEncoder[motorB];
	while(cur_speed < speed)
	{
		if(nEnc >= average_enc())
			return;

		while(nMotorEncoder[motorB] < enc + 2)
			Line1(cur_speed);

		enc = nMotorEncoder[motorB];
		cur_speed++;
	}
}

void Line_enc(int nEnc, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;

	if(motor[motorB] == 0 && motor[motorC] == 0)
		razgon_line(speed, nEnc);

	while(average_enc() < nEnc)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void Line1_enc(float nEnc, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;

	if(motor[motorB] == 0 && motor[motorC] == 0)
		razgon_line1(speed, nEnc);

	while(average_enc() < nEnc)
	{
		Line1(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void fwd_black(short SensorPort, short speed, const string ifStop)
{
	if(SensorPort==1)
	{
		while(SensorValue[S1]>BLACK)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==2)
	{
		while(SensorValue[S2]>BLACK)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==3)
	{
		while(SensorValue[S3]>BLACK)
		{
			moving(speed, 'f');
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void fwd_white(short SensorPort, short speed, const string ifStop)
{
	if(SensorPort==1)
	{
		while(SensorValue[S1] < WHITE)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==2)
	{
		while(SensorValue[S2] < WHITE)
		{
			moving(speed, 'f');
		}
	}
	if(SensorPort==3)
	{
		while(SensorValue[S3] < WHITE)
		{
			moving(speed, 'f');
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

float cosine (Indicator ind, tHTCS2 sensor)
{
	float numer = ind.red * sensor.red + ind.green * sensor.green + ind.blue * sensor.blue;
	float sqrt1 = sqrt(ind.red * ind.red + ind.green * ind.green + ind.blue * ind.blue);
	float sqrt2 = sqrt(sensor.red * sensor.red + sensor.green * sensor.green + sensor.blue * sensor.blue);
	return numer / (sqrt1 * sqrt2);
}

int check_ind(int nEnc, short speed, short dom)
{
	char dir;
	if(dom == 2)
		dir = 'f';
	else
		dir = 'b';

	readSensor(&colorSensor);
	nMotorEncoder[motorB] = 0;
	short col = -1;

	while(abs(nMotorEncoder[motorB]) < nEnc-20)
	{
		moving(speed, dir);
		readSensor(&colorSensor);
		if(col == -1 && (colorSensor.red > 65 || colorSensor.green > 55 || colorSensor.blue > 55))
		{
			//short blue_count = 0, green_count = 0, yellow_count = 0;
			if (cosine(blueInd, colorSensor) > 0.95)
			{
				playSoundFile("Blue");
				writeDebugStreamLine("ret: %d, get: %d, bet: %d", blueInd.red, blueInd.green, blueInd.blue);
				writeDebugStreamLine("r: %d, g: %d, b: %d", colorSensor.red, colorSensor.green, colorSensor.blue);
				writeDebugStreamLine("cosine: %.4f", cosine(blueInd, colorSensor));
				//blue_count++; green_count = 0; yellow_count = 0;
				//if(blue_count == 2)
				col = 0;
			}
			else if (cosine(greenInd, colorSensor) > 0.912)
			{
				playSoundFile("Green");
				writeDebugStreamLine("ret: %d, get: %d, bet: %d", greenInd.red, greenInd.green, greenInd.blue);
				writeDebugStreamLine("r: %d, g: %d, b: %d", colorSensor.red, colorSensor.green, colorSensor.blue);
				writeDebugStreamLine("cosine: %.4f", cosine(greenInd, colorSensor));
				//green_count++; blue_count = 0; yellow_count = 0;
				//if(green_count == 2)
				col = 1;
			}
			else if (cosine(yellowInd, colorSensor) > 0.95)
			{
				playSoundFile("Yellow");
				writeDebugStreamLine("ret: %d, get: %d, bet: %d", yellowInd.red, yellowInd.green, yellowInd.blue);
				writeDebugStreamLine("r: %d, g: %d, b: %d", colorSensor.red, colorSensor.green, colorSensor.blue);
				writeDebugStreamLine("cosine: %.4f", cosine(yellowInd, colorSensor));
				//yellow_count++; blue_count = 0; green_count = 0;
				//if(yellow_count == 2)
				col = 2;
			}
		}
	}
	if(col >= 0)
		nInds[col]++;

	while(abs(nMotorEncoder[motorB]) < nEnc)
		moving(speed, dir);
	stopmotor();

	return col;
}

void mot1_enc(short enc, char portMotor, short speed, char dir, const string ifStop)
{
	if (portMotor=='b')
	{
		nMotorEncoder[motorB]=0;
		if(dir=='f')
		{
			while(nMotorEncoder[motorB]<enc)
			{
				motor[motorB]=speed;
			}
		}
		if(dir=='b')
		{
			while(nMotorEncoder[motorB]>-enc)
			{
				motor[motorB]=-speed;
			}
		}
	}
	if (portMotor=='c')
	{
		nMotorEncoder[motorC]=0;
		if(dir=='f')
		{
			while(nMotorEncoder[motorC]>-enc)
			{
				motor[motorC]=-speed;
			}
		}
		if(dir=='b')
		{
			while(nMotorEncoder[motorC]<enc)
			{
				motor[motorC]=speed;
			}
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void hapuga(char dir)
{
	short speed;
	speed = (bricksInRobot[1] > -2) ? 25 : 80;
	nMotorEncoder[motorA] = 0;

	if(dir == 'c' && hap != 0)
	{
		if(hap == 2)
		{
			while(nMotorEncoder[motorA] > -250 + 75*sgn(bricksInRobot[1] + 2))
			{
				motor[motorA]=-25;
			}
		}
		motor[motorA]=-speed;
		wait10Msec(4200/speed);
		hap = 0;
	}

	if(dir == 'o' && hap != 2)
	{
		motor[motorA]=speed;
		wait10Msec((2000 + (1800 * ((hap + 1)%2)) - sgn(bricksInRobot[1] + 2)*600)/speed);
		hap = 2;
	}

	if(dir == 'm' && hap != 1)
	{
		nMotorEncoder[motorA]=0;
		if(hap == 0)
		{
			while(nMotorEncoder[motorA] < 200)
			{
				motor[motorA]=speed;
			}
		}
		if(hap == 2)
		{
			while(nMotorEncoder[motorA] > (-250) + 75*sgn(bricksInRobot[1] + 2))
			{
				motor[motorA]=-25;
			}
		}
		hap = 1;
	}

	if(dir == 'g')
	{
		while(nMotorEncoder[motorA] < HAPUGAG)
		{
			motor[motorA]=12;
		}
	}
	motor[motorA]=0;
}

void zahvat(char dir)
{
	short speed;
	speed = (bricksInRobot[3] > -2) ? 25 : 80;
	nMotorEncoder[motorD] = 0;

	if(dir == 'c' && zahvatPos != 0)
	{
		if(zahvatPos == 2)
		{
			while(nMotorEncoder[motorD] > -250 + 75*sgn(bricksInRobot[3] + 2))
			{
				motor[motorD]=-25;
			}
		}
		motor[motorD]=-speed;
		wait10Msec(4200/speed);
		zahvatPos = 0;
	}

	if(dir == 'o' && zahvatPos != 2)
	{
		motor[motorD]=speed;
		wait10Msec((2000 + (1800 * ((zahvatPos + 1)%2)) - sgn(bricksInRobot[3] + 2)*600)/speed);
		zahvatPos = 2;
	}

	if(dir == 'm' && zahvatPos != 1)
	{
		nMotorEncoder[motorD]=0;
		if(zahvatPos == 0)
		{
			while(nMotorEncoder[motorD] < 200)
			{
				motor[motorD]=speed;
			}
		}
		if(zahvatPos == 2)
		{
			while(nMotorEncoder[motorD] > (-250) + 75*sgn(bricksInRobot[3] + 2))
			{
				motor[motorD]=-25;
			}
		}
		zahvatPos = 1;
	}

	if(dir == 'g')
	{
		while(nMotorEncoder[motorD] < ZAHVATG)
		{
			motor[motorD]=10;
		}
	}
	motor[motorD]=0;
}

task hapugaM()
{
	hapuga('m');
}

task hapugaO()
{
	hapuga('o');
}

task hapugaC()
{
	hapuga('c');
}

task zahvatC()
{
	zahvat('c');
}

task zahvatO()
{
	zahvat('o');
}

task zahvatM()
{
	zahvat('m');
}

void povrightSpec(short speed)
{
	move_enc(SPEC_CROSS_R, speed, 'f', "stop");
	move_enc(160, speed, 'r', "");
	while (SensorValue[S1] > BLACK + 5)
	{
		moving(speed, 'r');
	}
	while (SensorValue[S1] < WHITE - 20)
	{
		moving(speed, 'r');
	}
	move_enc(26, speed, 'r', "stop");
	sensors = 1;
}

void povleftSpec(short speed)
{
	move_enc(SPEC_CROSS_L, speed, 'f', "stop");
	move_enc(160, speed, 'l', "");
	while (SensorValue[S2] > BLACK + 5)
	{
		moving(speed, 'l');
	}
	while (SensorValue[S2] < WHITE - 20)
	{
		moving(speed, 'l');
	}
	move_enc(25, speed, 'l', "stop");
	sensors = 1;
}

void turning(short destination)
{
	if(location < destination)
	{
		if (location % 2 == 1)
		{
			if (destination % 2 == 1)
			{
				povright(stdPower, "cross");
			}
			else
			{
				povrightSpec(stdPower);
			}
		}
		else if (location % 2 == 0)
		{
			if (destination % 2 == 1)
			{
				povleft(stdPower, "cross");
			}
			else
			{
				povleftSpec(stdPower);
			}
		}
	}
	else if (location > destination)
	{
		if (location % 2 == 1)
		{
			if (destination % 2 == 0)
			{
				povleft(stdPower, "cross");
			}
			else
			{
				povleftSpec(stdPower);
			}
		}
		else if (location % 2 == 0)
		{
			if (destination % 2 == 0)
			{
				povright(stdPower, "cross");
			}
			else
			{
				povrightSpec(stdPower);
			}
		}
	}
}

void crosses(short destination, const string ifStop)
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

	if(!sensors)
	{
		Line_enc(100, stdPower, "");
		fwd_black(1, stdPower, "");
	}
	else
	{
		Line1_enc(100, stdPower, "");
		fwd_black(3, stdPower, "");
	}

	location = destination;

	if(ifStop == "stop" || ifStop == "STOP" || ifStop == "Stop" || ifStop == "s")
		stopmotor();
}

void move_to(short destination, const string ifTurn1, const string ifTurn2)
{
	if(location == 8)
	{
		writeDebugStreamLine("%d", ourWay[0]);
		if(ourWay[0] == 1)
			return;
		else
		{
			povright(stdPower, "");
			Line_enc(50, stdPower, "");
			Line_enc(300, lineMaxPower, "");
			LineCross(stdPower, "");
			location = 4;
		}
	}

	if(location == destination)
	{
		if(location == 4 && destination == 4)
		{
			povright(stdPower, "");
			move_enc(CROSS_ENC, stdPower, 'b', "stop");
		}
		old_location = location;
		location = destination;
		return;
	}

	if(location < 8)
	{
		if(ifTurn1 == "turn")
		{
			turning(destination);

			if (location == 7) // accumulator
			{
				location = 4;
			}
			writeDebugStreamLine("loc:%d",location);
			old_location = location;

			crosses(destination, "");

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



#endif
