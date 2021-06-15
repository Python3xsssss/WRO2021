#pragma once

#ifndef _INIT_H_
#define _INIT_H_

#include "hitechnic-colour-v2.h"

#define WHITE 57
#define BLACK 15

tHTCS2 colorSensor;
char * fileInd = "Indicators";
//char * fileWB = "WhiteBlack";
long fileHandle;

short /*valB, valW,*/ stdPower = 25, zonePower = 40, lineMaxPower = 60;
short GREY;

typedef struct {
	short red;
	short green;
	short blue;
} Indicator;

Indicator blueInd, greenInd, yellowInd;

//short i, q, readValue;

void read ()
{
	//fileHandle = fileOpenRead(fileWB);

  //fileClose(fileHandle);
  fileHandle = fileOpenRead(fileInd);
  fileReadShort(fileHandle, &blueInd.red);
  fileReadShort(fileHandle, &blueInd.green);
  fileReadShort(fileHandle, &blueInd.blue);
	fileReadShort(fileHandle, &greenInd.red);
  fileReadShort(fileHandle, &greenInd.green);
	fileReadShort(fileHandle, &greenInd.blue);
	fileReadShort(fileHandle, &yellowInd.red);
  fileReadShort(fileHandle, &yellowInd.green);
  fileReadShort(fileHandle, &yellowInd.blue);
  fileClose(fileHandle);
}

void init()
{
	read();
	writeDebugStreamLine("Black %f, White %f, BIR %f, BIG %f, BIB %f, GIR %f, GIG %f, GIB %f, YIR %f, YIG %f, YIB %f", BLACK, WHITE, blueInd.red, blueInd.green, blueInd.blue, greenInd.red, greenInd.green, greenInd.blue, yellowInd.red, yellowInd.green, yellowInd.blue);
  GREY = (WHITE + BLACK)/2;
	initSensor(&colorSensor, S4);
}


#endif
