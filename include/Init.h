#pragma once

#ifndef _INIT_H_
#define _INIT_H_
char * fileInd = "Indicator";
char * fileWB = "Value";

void init()
{
	stdPower=25;
	lineMaxPower=60;
	zonePower=40;
	//k1=0.2;
	//k2=10;
	initSensor(&colorSensor, S4);
}


#endif
