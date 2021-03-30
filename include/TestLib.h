//Test library
#pragma once

#ifndef TESTLIB_H
#define TESTLIB_H

void goFwd(int maxPower)
{
	motor[motorB] = maxPower;
	motor[motorC] = maxPower;
}

int newColorCheck()
{
	return SensorValue[S1];
}

#endif //TESTLIB_H
