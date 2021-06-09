#include "hitechnic-colour-v2.h"

char * fileInd = "Indicator";
char * fileWB = "Value";
tHTCS2 colorSensor;

string colors[3] = {"BLUE", "GREEN", "YELLOW"};
short i, q, obj, readValue, val;

long fileHandle;


void output ()
{
	i = 3;
	q = 0;
	writeDebugStreamLine("COLORS");
	fileHandle = fileOpenRead(fileInd);
	while (fileReadShort(fileHandle, &readValue))
	{
		if (i == 3)
		{
			writeDebugStreamLine("%s", colors[q]);
			q++;
			i = 0;
		}
		writeDebugStreamLine("%d ", readValue);
		i++;
	}
	fileClose(fileHandle);
}

// MAIN

task main()
{
	clearDebugStream();
	initSensor(&colorSensor, S4);
	displayCenteredBigTextLine(7, "Rewrite colors?");
	waitForButtonPress();
	eraseDisplay();
	if (getButtonPress(DOWN_BUTTON) != 1)
	{
		return;
	}
	waitForButtonPress();
	if (getButtonPress(UP_BUTTON) == 1)
	{
		fileHandle = fileOpenWrite(fileInd);
		wait1Msec(500);
		for (i = 0; i < 3; i++)
		{
			displayCenteredBigTextLine(4, "%s", colors[i]);
			do
			{
				readSensor(&colorSensor);
				displayBigTextLine(7, "R:%d G:%d B:%d", colorSensor.red, colorSensor.green, colorSensor.blue);
				wait1Msec(100);
			}
			while (getButtonPress(ENTER_BUTTON) == 0);
			fileWriteShort(fileHandle, colorSensor.red);
			fileWriteShort(fileHandle, colorSensor.green);
			fileWriteShort(fileHandle, colorSensor.blue);
			wait1Msec(1000);
		}
		fileClose(fileHandle);
	}
	wait1Msec(1000);

	waitForButtonPress();
	if (getButtonPress(LEFT_BUTTON) == 1)
	{
		fileHandle = fileOpenWrite(fileWB);
		displayCenteredBigTextLine(4, "%s", "WHITE");
		do
		{
			val=SensorValue[S1];
			displayBigTextLine(7, "B:%d", val );
			wait1Msec(100);
		}
		while (getButtonPress(ENTER_BUTTON) == 0);
		fileWriteShort(fileHandle, val);
		wait1Msec(1000);
		fileClose(fileHandle);
		waitForButtonPress();
		fileHandle = fileOpenWrite(fileWB, val);
		displayCenteredBigTextLine(4, "%s", "BLACK");
		do
		{
			val=SensorValue[S1];
			displayBigTextLine(7, "B:%d", val );
			wait1Msec(100);
		}
		while (getButtonPress(ENTER_BUTTON) == 0);
		fileWriteShort(fileWB, val);
		wait1Msec(1000);
	}

	output();
}
