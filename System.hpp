/************************************************
*                   System.h                    *
*************************************************
*          This file is a part of:              *
*               COLUMBUS ENGINE                 *
*************************************************
*             Nikolay(Columbus) Red             *
*                   20.07.2017                  *
*************************************************/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
#endif

namespace ColumbusCompiler
{

	//Return current Operating System
	char* C_GetSystem();
	//Read file
	char* C_ReadFile(const char* aPath);
	//Return file size
	unsigned long int C_FileSize(const char* aFile);
	//Write buffer to file
	bool C_WriteFile(const char* aFile, const char* aText);
	//Create file
	bool C_CreateFile(const char* aPath);
	//Delete file
	bool C_DeleteFile(const char* aPath);
	//Create folder
	bool C_CreateFolder(const char* aPath);
	//Conversion from degrees to radians
	float C_DegToRads(float aDeg);
	//Conversion from radians to degrees
	float C_RadsToDeg(float aRads);
	//Random between two floats
	float C_RandomBetween(float aMin, float aMax);


}
