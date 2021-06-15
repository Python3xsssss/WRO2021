#pragma once

#ifndef TESTLIB_H
#define TESTLIB_H

#define TURN 248
#define TURNAROUND 499
#define ONEMOTORTURN 525
#define CROSS_ENC 100
#define SPEC_CROSS_L 48
#define SPEC_CROSS_R 155
#define ZAHVATG 124
//#define HAPUGAG 64
#define BEFORE_CROSS 90

//#define LINETOLINE 200

short pauseCounter = 0;
short location, old_location; // location: 0-6 - T-crosses, 7 - accumulator, 8 - from blue zone, 9 - from yellow zone
short sensors = 0;
short indDoms[3][2] = {{-1,-1}, {-1,-1}, {-1,-1}}; // indDoms[0][0] - color index of first indicator in first dom, etc.
short nInds[3] = {0, 0, 0}; // nInds[0] - num of blue indicators, etc.
int encs[6] = {340, 760, 240, 930, 850, 250};
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

int average()
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
	static short eold, e, es, u;
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
	static short eold, e, es, u;
	es=SensorValue[S1]-SensorValue[S2];
	e=SensorValue[S1]-SensorValue[S2]+es;
	u=k1*es+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u)*0.97;
	motor[motorC]=(-speed + u)*1.03;
}

void Line1S1(short speed)
{
	k1 = 0.22; k2 = 11;
	static short eold, e, u;
	e=GREY-SensorValue[S1];
	u=k1*e+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u);
	motor[motorC]=(-speed + u);
}

void Line1S3(short speed)
{
	k1 = 0.2; k2 = 10;
	static short eold, e, u;
	e=SensorValue[S3]-GREY;
	u=k1*e+k2*(e-eold);
	eold=e;
	motor[motorB]=(speed + u)*1.03;
	motor[motorC]=(-speed + u)*0.97;
}

void stopmotor()
{
	motor[motorB]=0;
	motor[motorC]=0;
	wait1Msec(120);
	pauseCounter++;
}

void Line1S1_enc(int nEnc, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;

	while(nMotorEncoder[motorB] < nEnc)
		Line1S1(speed);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			stopmotor();
}

void Line1S1Cross(short speed, const string ifStop)
{
	while(SensorValue[S3] > BLACK)
		Line1S1(speed);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void Line1S1White(short speed, const string ifStop)
{
	while(SensorValue[S3] < WHITE)
		Line1S1(speed);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
		stopmotor();
}

void Line1S3_enc(int nEnc, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;

	while(nMotorEncoder[motorB] < nEnc)
		Line1S3(speed);

	if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			stopmotor();
}

void Line1S3Cross(short speed, const string ifStop)
{
	while(SensorValue[S1] > BLACK)
		Line1S3(speed);

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

void move_enc_old(short enc, short speed, char dir, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	if(dir=='f')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			moving(speed, 'f');
		}
	}
	if(dir=='b')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			moving(speed, 'b');
		}
	}
	if(dir=='l')
	{
		while(nMotorEncoder[motorB]<enc)
		{
			moving(speed, 'l');
		}
	}
	if(dir=='r')
	{
		while(nMotorEncoder[motorB]>-enc)
		{
			moving(speed, 'r');
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
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
		//writeDebugStreamLine("kmot = %.1f, kold = %.1f", kmot, kold);
		nEncMotB = abs(nMotorEncoder[motorB]);
		nEncMotC = abs(nMotorEncoder[motorC]);
	}

	//if(ifRazgon)
	//kmot = 0.73;

	else if(abs(nMotorEncoder[motorB]) % 25 < 5 && abs(nMotorEncoder[motorB]) != 0 && abs(nMotorEncoder[motorC]) != 0)
	{
		//writeDebugStreamLine("nEncMotB: %.3f", (float)(abs(nMotorEncoder[motorB])));
		//writeDebugStreamLine("nEncMotBOld: %.3f", (float)(nEncMotB));
		//writeDebugStreamLine("nEncMotC: %.3f", (float)(abs(nMotorEncoder[motorC])));
		//writeDebugStreamLine("nEncMotCOld: %.3f", (float)(nEncMotC));
		kold = (float)kmot;
		kmot = (float)(abs(nMotorEncoder[motorB]) - nEncMotB) / (float)(abs(nMotorEncoder[motorC]) - nEncMotC) * kold;
		//writeDebugStreamLine("kmot = %.3f, kold = %.1f", kmot, kold);
		//writeDebugStreamLine("chastnoe: %.3f", (float)(abs(nMotorEncoder[motorB]) - nEncMotB) / (float)(abs(nMotorEncoder[motorC]) - nEncMotC));
		nEncMotB = abs(nMotorEncoder[motorB]);
		nEncMotC = abs(nMotorEncoder[motorC]);
	}

	//if(kmot > 1)
		//kmot = 1;

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

	motor[motorB] = speed*dirB;
	motor[motorC] = speed*dirC*kmot;

	while((abs(nMotorEncoder[motorB]) == nEncMotB || abs(nMotorEncoder[motorC]) == nEncMotC) || abs(nMotorEncoder[motorB]) % 25 < 5)
	{
		motor[motorB] = speed*dirB;
		motor[motorC] = speed*dirC*kmot;
	}

	if(abs(nMotorEncoder[motorB]) > 120 && ifRazgon == 0.5)
		ifRazgon = 0;
}

void razgon(short speed, char dir, int nEnc)
{
	ifRazgon = 1;
	short i = 0;

	while(abs(motor[motorC]) < speed && abs(motor[motorB]) < speed)
	{
		i++;

		while(abs(nMotorEncoder[motorB]) < i + i%40*3)
		{
			if(abs(nMotorEncoder[motorB]) >= nEnc - decrease*30)
				break;
			moving_sync(i+14, dir);
				//motor[motorB] = i+4-2
				//motor[motorC] = -1*(i+4)
		}
		if(abs(nMotorEncoder[motorB]) >= nEnc - decrease*30)
			break;
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
	//motor[motorB] = speed*dirB;
	//motor[motorC] = speed*dirC;
	for(short i = 5; i > 0; i-=1)
	{
		short nEncMotorB = abs(nMotorEncoder[motorB]);
		while(abs(nMotorEncoder[motorB]) < nEncMotorB + 6)
		{
			motor[motorB] = (4*i)*dirB;
			motor[motorC] = (4*i)*dirC;
			//moving_sync(speed*((float)(i))/((float)(5)), 'f');
		}
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
}

void razgon_turn(short speed, char dir, int nEnc)
{
	short i = 0;

	while(abs(motor[motorC]) < speed && abs(motor[motorB]) < speed)
	{
		i++;

		while(abs(nMotorEncoder[motorB]) < i + i%40*3)
		{
			if(average() >= nEnc - decrease*30)
				break;
			moving(i+6, dir);
				//motor[motorB] = i+4-2
				//motor[motorC] = -1*(i+4)
		}
		if(average() >= nEnc - decrease*30)
			break;
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
			razgon(speed, dir, nEnc);

		while(abs(nMotorEncoder[motorB]) <= nEnc  - 30*decrease)
			moving_sync(speed, dir);

		if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			tormoz(speed, dir);
	}

	else
	{
		if(motor[motorB] == 0 && motor[motorC] == 0)
			razgon_turn(speed, dir, nEnc);

		while(average() < nEnc)
			moving_sync(speed, dir);

		if(ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
			stopmotor();
	}

	decrease = 0;
}

void povright(short speed, const string ifCross)
{
	if (ifCross == "cross" || ifCross == "Cross" || ifCross == "CROSS")
	{
		move_enc(CROSS_ENC, speed, 'f', "stop");
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

	stopmotor();
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

	stopmotor();
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
	while(SensorValue[S1]>BLACK)
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
	while(SensorValue[S3]>BLACK)
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

void Line_enc(float enc2, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<enc2)
	{
		Line(speed);
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
}

void Line1_enc(float enc2, short speed, const string ifStop)
{
	nMotorEncoder[motorB]=0;
	while(nMotorEncoder[motorB]<enc2)
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
	if(dom == 0)
		dir = 'r';
	else if(dom == 1)
		dir = 'b';
	else if(dom == 2)
		dir = 'f';

	readSensor(&colorSensor);
	nMotorEncoder[motorB] = 0;
	short col = -1;

	while(abs(nMotorEncoder[motorB]) < nEnc)
	{
		moving(speed, dir);
		readSensor(&colorSensor);
		if(col == -1 && (colorSensor.red + colorSensor.green + colorSensor.blue) > 65)
		{
			//short blue_count = 0, green_count = 0, yellow_count = 0;
			if (cosine(blueInd, colorSensor) >= 0.9)
			{
				playSoundFile("Blue");
				writeDebugStreamLine("ret: %d, get: %d, bet: %d", blueInd.red, blueInd.green, blueInd.blue);
				writeDebugStreamLine("r: %d, g: %d, b: %d", colorSensor.red, colorSensor.green, colorSensor.blue);
				writeDebugStreamLine("cosine: %.4f", cosine(blueInd, colorSensor));
				//blue_count++; green_count = 0; yellow_count = 0;
				//if(blue_count == 2)
				col = 0;
			}
			else if (cosine(greenInd, colorSensor) >= 0.94)
			{
				playSoundFile("Green");
				writeDebugStreamLine("ret: %d, get: %d, bet: %d", greenInd.red, greenInd.green, greenInd.blue);
				writeDebugStreamLine("r: %d, g: %d, b: %d", colorSensor.red, colorSensor.green, colorSensor.blue);
				writeDebugStreamLine("cosine: %.4f", cosine(greenInd, colorSensor));
				//green_count++; blue_count = 0; yellow_count = 0;
				//if(green_count == 2)
				col = 1;
			}
			else if (cosine(yellowInd, colorSensor) >= 0.983)
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
		while(nMotorEncoder[motorA] < ZAHVATG)
		{
			motor[motorA]=15;
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
			motor[motorD]=15;
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

void old_crosses(short destination, const string ifStop)
{
	if(location == destination)
	{
		return;
	}
	if(destination % 2 == 0 && destination < location || destination % 2 != 0 && destination > location)
	{
		for(short i = 0; i < abs(destination - location)/2 + abs(destination - location) % 2; i++)
		{
			if(i != 0)
			{
				Line_enc(100, lineMaxPower, "");
			}
			lineWhite(lineMaxPower, "");
			LineCross(lineMaxPower, "");
		}
	}
	else
	{
		for(short i = 0; i < abs(destination - location)/2 + abs(destination - location) % 2; i++)
		{
			if(i != 0)
			{
				Line1_enc(100, lineMaxPower, "");
			}
			line1White(lineMaxPower, "");
			Line1Cross(lineMaxPower, "");
		}
	}
	if (ifStop == "stop" || ifStop == "Stop" || ifStop == "STOP")
	{
		stopmotor();
	}
	old_location = location;
	location = destination;
}

void povrightSpec(short speed)
{
	move_enc(SPEC_CROSS_R, speed, 'f', "stop");
	if((hap == 1 && bricksInRobot[1] == 1) || (hap == 2 && bricksInRobot[0] == 1))
	{
		stdPower = 18;
	}
	move_enc(100, speed, 'r', "");
	while (SensorValue[S1] > BLACK + 5)
	{
		moving(speed, 'r');
	}
	while (SensorValue[S1] < WHITE - 20)
	{
		moving(speed, 'r');
	}
	stdPower = 25;
	stopmotor();
	sensors = 1;
}

void povleftSpec(short speed)
{
	move_enc(SPEC_CROSS_L, speed, 'f', "stop");
	if((hap == 1 && bricksInRobot[1] == 1) || (hap == 2 && bricksInRobot[0] == 1))
	{
		stdPower = 18;
	}
	move_enc(100, speed, 'l', "");
	while (SensorValue[S2] > BLACK + 5)
	{
		moving(speed, 'l');
	}
	while (SensorValue[S2] < WHITE - 20)
	{
		moving(speed, 'l');
	}
	stdPower = 25;
	stopmotor();
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
	LineCross(stdPower, "");
  location = destination;
	if(ifStop == "stop" || ifStop == "STOP" || ifStop == "Stop" || ifStop == "s")
		stopmotor();
}

void move_to(short destination, const string ifTurn1, const string ifTurn2)
{
	if(location == 8)
	{
		writeDebugStreamLine("%d", ourWay[0]);
	//	povleft(stdPower,"stop");// destroy after write put in dom
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
	if(location < 8 && location != destination)
	{
		if(ifTurn1 == "turn")// && location != 9)
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
