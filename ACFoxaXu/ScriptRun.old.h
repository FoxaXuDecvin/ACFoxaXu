#pragma once
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"
using namespace std;

string LineReaderA(string File, int line_number) {
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(File.c_str());
	lines = CountLines(File);

	if (line_number <= 0)
	{
		return "Line Error";
	}
	if (file.fail())
	{
		return "Error File not exist";
	}
	if (line_number > lines)
	{
		return "overline";
	}
	while (getline(file, temp) && i < line_number - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

string TransVarA(string Info, string PubVar) {
	if (_access(PubVar.c_str(), 0)) {
		return Info;
	}
	if (Info == "") {
		return Info;
	}
	string herodata = Info;

	int localget = 1;

BackGet:

	string geti = "MRA" + to_string(localget);

	string GETSMax = readini(PubVar, "MRALIST", "$maxnum");
	int gmax_int = atoi(GETSMax.c_str());

	if (localget > gmax_int) {
		return Info;
	}

	string gets = readini(PubVar, "MRALIST", geti);
	if (gets == "readini-failed") {
		cout << "gets Error :  " << geti << endl;
	}

	if (GETSMax == "readini-failed") {
		cout << "getsmax Error :  " << GETSMax << endl;
	}
	int gsmax_int = atoi(GETSMax.c_str());

	string gvars = readini(PubVar, "VarST", gets);
	if (gvars == "readini-failed") {
		cout << "gvars Error :  " << gets << endl;
	}
	if (gvars == "NULL") {
		localget++;
		goto BackGet;
	}
	string herocha = GetGlobal(herodata);
	WriteGlobal(herodata, Replace(herocha, gets, gvars));

	localget++;
	goto BackGet;
}

void cpauseA(string Notices) {
	cout << Notices;
	system("pause >nul");
	cout << endl;
	return;
}

int ScriptRun(string File, int vercode, int startline, string PubVar) {
	//初始化环境
	ofstream logs;
	string logfile = "log~" + to_string(SpawnRandomNum(11111, 99999)) + "~record.log";
	logs.open(logfile);

	int CURRLINE = startline;

	//StartRun

	logs << "start run" << endl;
	logs << "Script :  " << File << endl;

BackRoll:
	//获取函数
	//cout << cl_str << endl;

	string GetLineData = LineReaderA(File, CURRLINE);
	string CaCMDS = TransVarA(GetLineData, PubVar);
	logs << "Line :  " << to_string(CURRLINE) << " . INFO :  " << CaCMDS << endl;

	int cmrd = CaCmdRun(CaCMDS, GetLineData, File, CURRLINE, vercode, PubVar);
	//cout << CaCMDS << endl;
	if (cmrd == -2) {
		// version Not Allow
		cpauseA("press any key to Exit");
		remove(PubVar.c_str());
		logs.close();
		remove(logfile.c_str());
		return 0;
	}
	if (cmrd == -1) {
		//Return Exit
		remove(PubVar.c_str());
		logs.close();
		remove(logfile.c_str());
		return 0;
	}
	if (cmrd == 1) {
		logs << "Unknown Command :  " << CaCMDS << "  Line :  " << to_string(CURRLINE) << endl;
	}
	if (cmrd == 2) {
		cout << endl;
		cout << "Script is Crash." << endl;
		cout << "On The :  " << to_string(CURRLINE) << " .  COMMAND :  " << GetLineData << endl;
		cout << "This Problem is happend by Script" << endl;
		cout << endl;
		remove(PubVar.c_str());
		return 1;
	}
	if (cmrd > 2) {
		CURRLINE = cmrd;
		goto BackRoll;
	}

	CURRLINE++;
	goto BackRoll;
}