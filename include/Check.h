#pragma once

#ifndef CHECK_H
#define CHECK_H

#include "hitechnic-colour-v2.h"
#include "WRO_Lib.h"

void CheckDom1()
{
	motor[motorD]=-25;
	move_enc(250, v, 'f');
	move_enc(260, 50, 'l');
	motor[motorD]=0;
	motor[motorB]=-40;
	motor[motorC]=40;
	wait10Msec(100);
	stopmotor();
	info(1);
	zahvat('o');
	v=25;
	goBlack(1);
	wait10Msec(20);
	povleft();
	motor[motorD]=0;
	LineCross();
	povright();
	Line_enc(300);
	povright();
}

#endif
