#pragma once
#include"D:\CppHeader\winapicore.h"

int NoGUI = 0;

int DebugMode = 0;

string LaunchParameter;

int ErrorRecord = 0;
int WarningRecord = 0;

string $PCUserName = getenv("username");
string $PCPATH = getenv("path");
string $PCTemp = getenv("temp");
string $PCSYSDRV = getenv("systemdrive");

string ResLoadFile;

string TempChart;

string TempCharB;

string RunPara;

int ProcessLine;

int MainMode = 0;
int MainRoll = 0;