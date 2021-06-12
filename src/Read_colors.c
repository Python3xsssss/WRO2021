 #include "hitechnic-colour-v2.h"
char * fileInd = "Indicators";
char * fileWB = "WhiteBlack";

tHTCS2 colorSensor;

string colors[3] = {"BLUE", "GREEN", "YELLOW"};
short i, q, readValue, val;

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
			writeDebugStream("\n%s INDICATOR: ", colors[q]);
			q++;
			i = 0;
		}
		writeDebugStream("%d ", readValue);
		i++;
	}
	fileClose(fileHandle);

	writeDebugStreamLine("");

	fileHandle = fileOpenRead(fileWB);
	fileReadShort(fileHandle, &readValue);
	writeDebugStreamLine("WHITE: %d", readValue);
	fileReadShort(fileHandle, &readValue);
	writeDebugStreamLine("BLACK: %d", readValue);
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
	if (getButtonPress(LEFT_BUTTON) != 1 && getButtonPress(RIGHT_BUTTON)!=1)
	{
		output();
		return;
	}
	else if (getButtonPress(LEFT_BUTTON) == 1)
	{
		fileHandle = fileOpenWrite(fileInd);
		wait1Msec(500);
		for (i = 0; i < 3; i++)
		{
			displayCenteredBigTextLine(3, "%s", colors[i]);
			do
			{
				readSensor(&colorSensor);
				displayCenteredBigTextLine(7, "R:%d G:%d B:%d", colorSensor.red, colorSensor.green, colorSensor.blue);
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
	else if (getButtonPress(RIGHT_BUTTON) == 1)
	{
		fileHandle = fileOpenWrite(fileWB);
		displayCenteredBigTextLine(3, "%s", "WHITE");
		do
		{
			val=SensorValue[S1];
			displayCenteredBigTextLine(7, "W:%d", val );
			wait1Msec(500);
		}
		while (getButtonPress(ENTER_BUTTON) == 0);
		fileWriteShort(fileHandle, val);
		displayCenteredBigTextLine(3, "%s", "BLACK");
		do
		{
			val=SensorValue[S1];
			displayCenteredBigTextLine(7, "B:%d", val);
			wait1Msec(500);
		}
		while (getButtonPress(ENTER_BUTTON) == 0);
		fileWriteShort(fileHandle, val);
        fileClose(fileHandle);
	}

	output();
}
