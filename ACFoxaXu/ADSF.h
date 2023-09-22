#pragma once
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"
using namespace std;

string what = "HelloWord";

string RunINFO = getselfinfo();
string RunPath = getselfpath();

string Version = "Hans Core";
string ComVer = "2023/9/17";

string cpause(string Notices) {
	cout << Notices;
	system("pause >nul");
	cout << endl;
	return what;
}

class ClearType {
	int Line;
	string TypeData;
};

void clscmd() {
	system("cls");
}

string LineReader(string File, int line_number) {
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

void WriteIntGlobal(string GlobalData, int intdata) {
	string IntNum = to_string(intdata);
	WriteGlobal(GlobalData, IntNum);
}
int GetIntGlobal(string GlobalData) {
	int RetIntd;
	string GETG = GetGlobal(GlobalData);
	RetIntd = atoi(GETG.c_str());
	return RetIntd;
}

string CleanAuto(string info, string replaceword) {
	return Replace(info, replaceword, "");
}

string cutlineblock(string lines, int line) {

	if (line == NULL) {
		return "NULL";
	}
	if (line < 0) {
		return "MinSetFailed";
	}
	if (line > 10) {
		return "MaxSetFailed";
	}

	char* Slinechar = nullptr;
	char* Slinecut = nullptr;

	const char* STR_Line = nullptr;
	const char* old_Line = nullptr;

	string Rep_INFO = " ";
	old_Line = lines.c_str();
	STR_Line = Rep_INFO.c_str();

	Slinechar = const_cast<char*>(STR_Line);
	Slinecut = const_cast<char*>(old_Line);

	string strback;
	int stepstart = 1;

	WriteIntGlobal("StepRoll", 1);

BackstepP:
	int curfind = GetIntGlobal("StepRoll");

	//Start
	string a = strtok(Slinecut, Slinechar);
	if (line == curfind) {
		return a;
	}
	//P2start
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;
	a = strtok(NULL, Slinechar);
	if (line == curfind) {
		return a;
	}
	
	//END

	curfind++;
	WriteIntGlobal("StepRoll",curfind);
	goto BackstepP;

	return "failed~s";
}

string TransVar(string Info,string PubVar) {
	if (_access(PubVar.c_str(), 0)) {
		return Info;
	}
	if (Info == "") {
		return Info;
	}
	string heronum = "TransVar~T";
	string herodata = "TransVar~D";
	WriteIntGlobal(heronum, 1);
	WriteGlobal(herodata, Info);

BackGet:
	int localget = GetIntGlobal(heronum);
	string geti = "MRA" + to_string(localget);
	
	string GETSMax = readini(PubVar, "MRALIST", "$maxnum");
	int gmax_int = atoi(GETSMax.c_str());

	if (localget > gmax_int) {
		string herocha = GetGlobal(herodata);
		return herocha;
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
		cout << "gvars Error :  " << gets<< endl;
	}
	if (gvars == "NULL") {
		localget++;
		WriteIntGlobal(heronum, localget);
		goto BackGet;
	}
	string herocha = GetGlobal(herodata);
	WriteGlobal(herodata,Replace(herocha, gets, gvars));

	localget++;
	WriteIntGlobal(heronum, localget);
	goto BackGet;
}

int GetMaxNum(string Dict, string Head) {
	string RTCode = readini(Dict, Head, "$maxnum");
	int ReturnINFO;
	ReturnINFO = atoi(RTCode.c_str());
	return ReturnINFO;
}
int WriteMaxNum(string Dict, string Head, int maxnum) {
	string maxnumse = to_string(maxnum);
	writeini(Dict, Head, "$maxnum", maxnumse);
	return maxnum;
}
string WriteNewMRA(string Dict, string Head, string INFO) {
	int getmaxnum = GetMaxNum(Dict, Head);
	getmaxnum++;
	WriteMaxNum(Dict, Head, getmaxnum);
	string gmnstr = to_string(getmaxnum);
	string NewMRA = "MRA" + gmnstr;
	writeini(Dict, Head, NewMRA, INFO);
	return NewMRA;
}

//正常退出输出 0.异常输出 1
int ScriptRun(string File,int vercode,int startline,string PubVar) {
	//初始化环境
	ofstream logs;
	string logfile = "log~" + to_string(SpawnRandomNum(11111, 99999)) + "~record.log";
	logs.open(logfile);
	string EPoint = "ADSF~para";
	WriteIntGlobal(EPoint,startline);

	//StartRun

	logs << "start run" << endl;
	logs << "Script :  " << File << endl;

BackRoll:
	//获取函数
	int CURRLINE = GetIntGlobal(EPoint);
	string cl_str = to_string(CURRLINE);

	//cout << cl_str << endl;

	string GetLineData = LineReader(File, CURRLINE);
	string getlineinfo = TransVar(GetLineData,PubVar);
	logs << "Line :  " << cl_str << " . INFO :  " << getlineinfo << endl;
	

	//cout << getlineinfo << endl;

	if (checkChar(getlineinfo, "///") == 1) {
		logs << "Skip" << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "#load ") == 1) {
		//cout << "Load Part" << endl;
		logs << "Load Other Part" << endl;
		string p1 = CleanAuto(getlineinfo, "#load ");
		//cout << "p1 = _" << p1 << "_" << endl;

		//查找 p1
		string SPoint = "Find~load";
		WriteIntGlobal(SPoint, 2);

	ASBackRoll:
		//获取函数
		int XCURRLINE = GetIntGlobal(SPoint);
		string cl_strx = to_string(XCURRLINE);

		//cout << cl_str << endl;

		string GetLineData = LineReader(File, XCURRLINE);
		//cout << "Line " << cl_strx << "  INFO :  _" << GetLineData << "_" << endl;

		if (GetLineData == "overline") {
			cout << endl;
			cout << endl;
			cout << "Script Crash.." << endl;
			cout << "Unable to load from :  " << File << endl;
			cout << "Head :  _" << p1 << "_, Not Found" << endl;
			remove(PubVar.c_str());
			return 1;
		}
		if (GetLineData == p1) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			logs << "Load Part :  " << p1 << endl;
			logs << "Line :  " << XCURRLINE << endl;
			WriteIntGlobal(EPoint, XCURRLINE);
			goto BackRoll;
		}
		XCURRLINE++;
		WriteIntGlobal(SPoint, XCURRLINE);
		goto ASBackRoll;
		//END p1

	}
	if (checkChar(getlineinfo, "#Include") == 1) {
		logs << "Try Include other part" << endl;
		string p1 = CleanAuto(getlineinfo, "#Include(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string FileInclude = cutlineblock(out, 1);
		string LoadPart = cutlineblock(out, 2);

		if (_access(FileInclude.c_str(), 0)) {
			cout << endl;
			cout << endl;
			cout << "Error, Script Try To load a Null Include. Line :  " << cl_str << endl;
			cout << "Unable to load from :  " << FileInclude << endl;
			cout << "File :  _" << FileInclude << "_, Not Found" << endl;
			remove(PubVar.c_str());
			return 1;
		}
		///PCA 1

		//查找 p1
		string SPoint = "Find~Include";
		WriteIntGlobal(SPoint, 2);

	ANBackRoll:
		//获取函数
		int XCURRLINE = GetIntGlobal(SPoint);
		string cl_strx = to_string(XCURRLINE);

		//cout << cl_str << endl;

		string GetLineData = LineReader(FileInclude, XCURRLINE);
		//cout << "Line " << cl_strx << "  INFO :  _" << GetLineData << "_" << endl;

		if (GetLineData == "overline") {
			cout << endl;
			cout << endl;
			cout << "Error, Script Try To load a Null Include. Line :  " << cl_str << endl;
			cout << "Unable to load from :  " << File << endl;
			cout << "Head :  _" << LoadPart << "_, Found Failed" << endl;
			remove(PubVar.c_str());
			return 1;
		}
		//cout << "_" << GetLineData << "_,_" << LoadPart << "_" << endl;
		if (GetLineData == LoadPart) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			logs << "Include :  " << FileInclude << endl;
			logs << "Include Part :  " << LoadPart << "  Line :  " << cl_strx << endl;
			ScriptRun(FileInclude, vercode, XCURRLINE, PubVar);

			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}
		XCURRLINE++;
		WriteIntGlobal(SPoint, XCURRLINE);
		goto ANBackRoll;

		//PCA End

	}
	if (checkChar(getlineinfo, "$$Prints") == 1) {
		//输出文档
		string p1 = CleanAuto(getlineinfo, "$$Prints(\"");
		string out = CleanAuto(p1, "\");");
		printf(out.c_str());
		logs << "Print :  " << out << endl;
		cout << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$Cout") == 1) {
		//输出文档
		string out = CleanAuto(getlineinfo, "$$Cout ");
		printf(out.c_str());
		logs << "Cout :  " << out << endl;
		cout << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$MsgBox") == 1) {
		//输出文档
		string p1 = CleanAuto(getlineinfo, "$$MsgBox(\"");
		string p2 = CleanAuto(p1, "\");");
		string p3 = Replace(p2, " ", "-$-");
		string out = Replace(p3, "\",\"", " ");
		
		string mbinfoPre = cutlineblock(out, 1);
		string mbtitlePre = cutlineblock(out, 2);
		string mbvar = cutlineblock(out, 3);

		string mbinfo = Replace(mbinfoPre, "-$-", " ");
		string mbtitle = Replace(mbtitlePre, "-$-", " ");

		int USReturn;

		if (mbvar == "NULL") {
			MessageBox(0, mbinfo.c_str(), mbtitle.c_str(), MB_OK);
			goto SkipRecordNUL;
		}
		else {
			WriteIntGlobal("NSTemp~info", MessageBox(0, mbinfo.c_str(), mbtitle.c_str(), MB_YESNO));
		}
		USReturn = GetIntGlobal("NSTemp~info");
		if (USReturn == 6) {
			WriteNewMRA(PubVar, "MRALIST", mbvar);
			writeini(PubVar, "VarST", mbvar,"yes");
		}
		else {
			WriteNewMRA(PubVar, "MRALIST", mbvar);
			writeini(PubVar, "VarST", mbvar, "no");
		}

		SkipRecordNUL:
		logs << "MessageBox :  " << mbtitle << "  Set Var :  " << mbvar << endl;
		cout << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$endl") == 1) {
		cout << endl;
		logs << "Endl Line" << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$~") == 1) {
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$pause") == 1) {
		string p1 = CleanAuto(getlineinfo, "$pause(\"");
		string out = CleanAuto(p1, "\");");
		cout << endl;
		logs << "Pause. Notice :   " << out << endl;
		cpause(out);
		cout << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$Windows.CMD") == 1) {
		//Windows CMD
		string p1 = CleanAuto(getlineinfo, "$Windows.CMD(\"");
		string out = CleanAuto(p1, "\");");
		system(out.c_str());
		logs << "Run Windows Command :  " <<out << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "#end") == 1) {
		logs << "Script End Task" << endl;
		remove(PubVar.c_str());
		logs.close();
		remove(logfile.c_str());
		return 0;
	}
	if (checkChar(getlineinfo, "$$SetConTitle") == 1) {
		//输出文档
		string p1 = CleanAuto(getlineinfo, "$$SetConTitle(\"");
		string out = CleanAuto(p1, "\");");
		SetConsoleTitle(out.c_str());
		logs << "Set Console Title :  " <<out << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$Timeout") == 1) {
		//输出文档
		string p1 = CleanAuto(getlineinfo, "$$Timeout(\"");
		string out = CleanAuto(p1, "\");");
		int sleepout = atoi(out.c_str());
		logs << "Timeout (ms) :  " << out << endl;
		Sleep(sleepout);
		
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$cls") == 1) {
		system("cls");
		logs << "Cls Console" << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "#mgrver") == 1) {
		//输出文档
		string p1 = CleanAuto(getlineinfo, "#mgrver");
		logs << "This Script only running on :   " << p1 << endl;
		int curver = atoi(p1.c_str());
		if (curver == vercode){}
		else {
			string VNIF = to_string(vercode);
			cout << "Warning This Script Only Running on :   " << p1 << endl;
			cout << "Current ADSF Version is :   " << VNIF << endl;
			cpause("press any key to Exit");
			remove(PubVar.c_str());
			logs.close();
			remove(logfile.c_str());
			return 0;
		}

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$Type ") == 1) {
		logs << "Type Text File " << endl;
		string settype = CleanAuto(getlineinfo, "$Type ");
		if (_access(settype.c_str(), 0)) {
			cout << "Missing Text File :  " << settype << endl;
			cout << "Cannot Type File" << endl;
			logs << "Error. End Type " << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}

		//编排
		logs << "Type File :  " << settype << endl;
		string rootd = "$TypeList~Line";
		WriteIntGlobal(rootd, 1);

		BackRead:
		//read
		int currentline = GetIntGlobal(rootd);
		string readtxt = LineReader(settype, currentline);
		if (readtxt == "overline") {
			// Read OK
			logs << "Type OK. Total Line :  " << to_string(currentline--) << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}
		string outtext = TransVar(readtxt, PubVar);

		//output
		cout << outtext << endl;

		currentline++;
		WriteIntGlobal(rootd, currentline);
		goto BackRead;
	}

	//Calcium api
	if (checkChar(getlineinfo, "$ApplyVar") == 1) {

		logs << "$APPLYVAR ~ Processing" << endl;

		string p1 = CleanAuto(getlineinfo, "$ApplyVar(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		logs << "Clean Command :   " << out << endl;

		string SelectVar = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		logs << "Select Var :  _" << SelectVar << "_ .   Write Var :  _" << WriteVar << "_  " << endl;

		if (SelectVar == "#$Version~calcium$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar,Version );
			logs << "Get Var OK" << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}
		if (SelectVar == "#$VersionCode~calcium$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, to_string(vercode));
			logs << "Get Var OK" << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}
		if (SelectVar == "#$CalciumRunPath$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, getselfpath());
			logs << "Get Var OK" << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}
		if (SelectVar == "#$CalciumCore$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, getselfinfo());
			logs << "Get Var OK" << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}
		if (SelectVar == "#$CalciumReleaseTime$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, ComVer);
			logs << "Get Var OK" << endl;
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto BackRoll;
		}

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar,"Null");
		logs << "Get Var Failed. Null Select" << endl;
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$WinEnv") == 1) {
		logs << "Try Get WinEnv. Method : V" << endl;
		string p1 = CleanAuto(getlineinfo, "$WinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);
		logs << "WinEnv Name :  _" << WinEnvS << "_ .  Record Name :  _" << WriteVar << "_" << endl;
		
		string WinEnv = getwinenvfast(WinEnvS.c_str());

		logs << "Win Env Return :   _" << WinEnv << "_." << endl;

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar, WinEnv);

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$AWinEnv") == 1) {
		logs << "Try Get WinEnv. Method : A" << endl;
		string p1 = CleanAuto(getlineinfo, "$AWinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);
		logs << "WinEnv Name :  _" << WinEnvS << "_ .  Record Name :  _" << WriteVar << "_" << endl;

		string WinEnv = getwinenv(WinEnvS.c_str());

		logs << "Win Env Return :   _" << WinEnv << "_." << endl;

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar, WinEnv);

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}

	//WindowsAPI

	//创建文件夹
	if (checkChar(getlineinfo, "$$winapi.md") == 1) {
		string p1 = CleanAuto(getlineinfo, "$$winapi.md(\"");
		string out = CleanAuto(p1, "\");");

		CreateDirectory(out.c_str(), 0);
		logs << "Create Folder :  " << out << endl;

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$winapi.rd") == 1) {
		string p1 = CleanAuto(getlineinfo, "$$winapi.rd(\"");
		string out = CleanAuto(p1, "\");");

		rmfolder(out.c_str());

		logs << "Remove Folder :  " << out << endl;

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$winapi.urlmon") == 1) {
		logs << "URLDownload" << endl;
		string p1 = Replace(getlineinfo, "\",\"", " ");
		string p2 = CleanAuto(p1, "$$winapi.urlmon(\"");
		string out = CleanAuto(p2, "\");");

		string URLINFO = cutlineblock(out, 1);
		string SPINFO = cutlineblock(out, 2);
		string SWITCHS = cutlineblock(out, 3);

		logs << "URL :  "  << URLINFO << endl;
		logs << "Save Path :  " <<SPINFO << endl;
		logs << "SWITCHS :  " << SWITCHS << endl;
		if (SWITCHS == "hide") {
			URLDown(URLINFO, SPINFO);
		}
		else {
			cout << endl;
			cout << "Downloading File :   " << URLINFO << endl;
			cout << "Save Path :  " << SPINFO << endl;
			URLDown(URLINFO, SPINFO);
		}
		if (_access(SPINFO.c_str(), 0)) {
			logs << "Download Failed" << endl;
			cout << "Download Failed" << endl;
		}
		else {
			logs << "Download OK" << endl;
			cout << "Download OK" << endl;
		}
		logs << "Complete" << endl;

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}

	//变量
	if (checkChar(getlineinfo, "$$var.edit") == 1) {

		string p1 = CleanAuto(getlineinfo, "$$var.edit(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string varname = cutlineblock(out, 1);
		string varinfo = cutlineblock(out, 2);

		WriteNewMRA(PubVar, "MRALIST", varname);
		writeini(PubVar, "VarST", varname, varinfo);

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}
	if (checkChar(getlineinfo, "$$var.del") == 1) {

		string p1 = CleanAuto(GetLineData, "$$var.del(\"");
		string out = CleanAuto(p1, "\");");

		writeini(PubVar, "VarST", out, "NULL");
		cout << "Delete Var :  " << out << endl;

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}

	if (checkChar(getlineinfo, "$$GetCin") == 1) {

		string p1 = CleanAuto(getlineinfo, "$$GetCin(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string svar = cutlineblock(out, 1);
		string outinfo = cutlineblock(out, 2);

		string varinfo;
		cout << outinfo;
		getline(cin,varinfo);

		WriteNewMRA(PubVar, "MRALIST", svar);
		writeini(PubVar, "VarST", svar, varinfo);

		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}

	//无效断流区域
	if (getlineinfo == "overline") {
	    	logs << "Over Line Error" << endl;
	     	remove(PubVar.c_str());
		    cout << endl;
			cout << "Script Not Set Exist API" << endl;
			remove(PubVar.c_str());
			return 1;
	}
	if (getlineinfo == "") {
		CURRLINE++;
		WriteIntGlobal(EPoint, CURRLINE);
		goto BackRoll;
	}

	//未知指令
	logs << "Unknown Command :  " << getlineinfo << "  Line :  " << cl_str << endl;
	cout << endl;
	cout << "_" << getlineinfo << "_ is not a command." << "  Line :  " << cl_str << endl;
	cout << "Please Check This Line is Right ? " << endl;
	cout << endl;
	CURRLINE++;
	WriteIntGlobal(EPoint, CURRLINE);
	goto BackRoll;
}