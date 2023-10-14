#pragma once
#include"ADSF.h"
#include<time.h>
typedef int(*DllDebugTest)();
typedef string(*DllHeadCheck)();
typedef string(*DllLoadCommand)(string Command);
typedef string(*DllLoadCommandA)(string Command);
typedef string(*DllReg)();
typedef int(*DllCUV)();

string cutlineblockB(string lines, string cutmark, int line) {
	string backapi;
	char* readcut = NULL;

	char Texts[65535] = "a";
	char CUMark[65535] = "a";

	strcpy_s(Texts, lines.c_str());
	strcpy_s(CUMark, cutmark.c_str());

	// 分割字符串，返回分割后的子字符串
	int cutrecord = 1;
	char* token = strtok_s(Texts, CUMark, &readcut);
	if (token == NULL) {
		backapi = "";
		return backapi;
	}

	if (cutrecord == line) {

		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}

NextRollCR:
	if (cutrecord == line) {
		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}
	if (token == NULL) {
		backapi = "";
		return backapi;
	}
	cutrecord++;
	token = strtok_s(NULL, CUMark, &readcut);
	goto NextRollCR;
}

int DllLoadDebug(string DLLNAME) {
	DllDebugTest PluginHelloWorld;
	HINSTANCE loadadll;
	loadadll = LoadLibrary(DLLNAME.c_str());
	if (loadadll == NULL) {
		FreeLibrary(loadadll);
		return 1001;
	}
	PluginHelloWorld = (DllDebugTest)GetProcAddress(loadadll, "PluginHelloWorld");
	if (PluginHelloWorld == NULL) {
		FreeLibrary(loadadll);
		return 1002;
	}
	PluginHelloWorld();
	FreeLibrary(loadadll);
	return 0;
}

int DllCheckPlugin(string DLLNAME) {
	DllHeadCheck CaPluginTest;
	HINSTANCE loadadll;
	loadadll = LoadLibrary(DLLNAME.c_str());
	if (loadadll == NULL) {
		FreeLibrary(loadadll);
		return 1;
	}
	CaPluginTest = (DllHeadCheck)GetProcAddress(loadadll, "CaPluginTest");
	if (CaPluginTest == NULL) {
		FreeLibrary(loadadll);
		return 1;
	}
	string BLOCK = CaPluginTest();
	FreeLibrary(loadadll);
	if (BLOCK == "caplugintrue") {
		return 0;
	}
	else {
		return 1;
	}
}

int DllLoad(string DLLNAME, string Command) {
	DllLoadCommand PluginCommand;
	HINSTANCE loadadll;
	loadadll = LoadLibrary(DLLNAME.c_str());
	if (loadadll == NULL) {
		FreeLibrary(loadadll);
		return 1;
	}
	PluginCommand = (DllLoadCommand)GetProcAddress(loadadll, "PluginCommand");
	if (PluginCommand == NULL) {
		FreeLibrary(loadadll);
		return 1;
	}
	string backpg = PluginCommand(Command);
	FreeLibrary(loadadll);
	if (backpg == "NO") {
		return 1;
	}
	else {
		return 0;
	}
	
}

string DllLoadCmd(string DLLNAME, string Command) {
	DllLoadCommandA PluginCommandA;
	HINSTANCE loadadll;
	loadadll = LoadLibrary(DLLNAME.c_str());
	if (loadadll == NULL) {
		FreeLibrary(loadadll);
		return "nul";
	}
	PluginCommandA = (DllLoadCommandA)GetProcAddress(loadadll, "PluginCommandA");
	if (PluginCommandA == NULL) {
		FreeLibrary(loadadll);
		return "nul";
	}
	string backpg = PluginCommandA(Command);
	FreeLibrary(loadadll);
	return backpg;
}

// BLOCK == 1 Return Var
// BLOCK == 2 Return MaxVar
string DLLRegAPI(string DLLNAME,int BLOCK) {
	if (BLOCK > 2) {
		return "LOADFAIL";
	}

	DllReg DLLRegVar;
	HINSTANCE loadadll;
	loadadll = LoadLibrary(DLLNAME.c_str());
	if (loadadll == NULL) {
		FreeLibrary(loadadll);
		return "LOADFAIL";
	}
	DLLRegVar = (DllReg)GetProcAddress(loadadll, "DLLRegVar");
	if (DLLRegVar == NULL) {
		FreeLibrary(loadadll);
		return "LOADNULL";
	}

	string FULLVARD = DLLRegVar();
	FreeLibrary(loadadll);

	string AutoCUT = cutlineblockB(FULLVARD, "&", BLOCK);
	
	return AutoCUT;
}

int dllCurrVersion(string DLLNAME) {
	DllCUV currentver;
	HINSTANCE loadadll;
	loadadll = LoadLibrary(DLLNAME.c_str());
	if (loadadll == NULL) {
		FreeLibrary(loadadll);
		return 404;
	}
	currentver = (DllCUV)GetProcAddress(loadadll, "currentver");
	if (currentver == NULL) {
		FreeLibrary(loadadll);
		return 404;
	}
	int acuV = currentver();
	FreeLibrary(loadadll);
	return acuV;
}