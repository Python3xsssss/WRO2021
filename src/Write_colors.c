 #include "hitechnic-colour-v2.h"
char * fileInd = "Indicators";
char * fileWB = "WhiteBlack";

tHTCS2 colorSensor;

string colors[3] = {"BLUE", "GREEN", "YELLOW"};
short i, q, readValue, val;

long fileHandle;

task main()
{
	fileHandle = fileOpenWrite(fileInd);
	//blue RGB
	fileWriteShort(fileHandle, 20);
	fileWriteShort(fileHandle, 60);
	fileWriteShort(fileHandle, 100);

	//green RGB
	fileWriteShort(fileHandle, 50);
	fileWriteShort(fileHandle, 100);
	fileWriteShort(fileHandle, 52);

	//yellow RGB
	fileWriteShort(fileHandle, 100);
	fileWriteShort(fileHandle, 90);
	fileWriteShort(fileHandle, 10);
}
