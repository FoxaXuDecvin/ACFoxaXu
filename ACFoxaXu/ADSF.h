#pragma once
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\ACFoxaXuProject\ACFoxaXu\ACFoxaXu\DLLApi.h"
#include"D:\CppHeader\WinReg.h"
#include"ParaSet.h"
using namespace std;

string RunINFO = getselfinfo();
string RunPath = getselfpath();
string CaMain = getselfpath() + "\\Calcium.exe";
string CaUpdMain = getselfpath() + "\\CaMaintain.exe";
string CaOutage = getselfpath() + "\\CaOutage.exe";
string CONFIGROOT = RunPath + "\\config.ini";
string PROGData = getwinenvfast("ProgramData") + "\\CalciumScript";
string PROGDataMain = getwinenvfast("ProgramData");

//INSTALL 
string PGDataf = getwinenvfast("ProgramData") + "\\CalciumScript";
string PGINSDATA = PGDataf + "\\CaInfo.txt";

string StrTrans(string StringInfo) {
	StringInfo = Replace(StringInfo, "$CURRENT", getselfpath());
	StringInfo = Replace(StringInfo, "$PROGROOT", PROGDataMain);
	StringInfo = Replace(StringInfo, "$PROGDATA", PROGData);
	StringInfo = Replace(StringInfo, "$WINDIR", getwinenvfast("windir"));
	return StringInfo;
}

int InsidePreview = 0;

string what = "HelloWord";

string DLLPATH = StrTrans(readini(CONFIGROOT, "default", "DLLPATH"));

string DLLRECORD = DLLPATH + "\\DllRecord.txt";

string settings = DLLPATH + "\\ProgramConfig.ini";
string verinfor = readini(CONFIGROOT, "Version", "CURRENT");
int vercode = atoi(verinfor.c_str());
string Version = readini(CONFIGROOT,"Version","CodeName");
string ComVer = readini(CONFIGROOT, "Version", "ComVer");
string KernelFile = getselfpath() + "\\" + readini(CONFIGROOT, "Version", "Kernel");

string VarSpace = "varspace;";
int VarSpaceMax;
string DLLRegList = "dllreglist;";

//返回正常值，直接显示
string LangOut(string title) {
	string langfile = readini(settings, "setting", "text");
	cout << readini(langfile, "CALCIUM", title) << endl;
}

//返回正常值，非显示
string Outlang(
	string langblock//Set Type Title
) {
	bool ExistDLLRoot = existfolder(DLLPATH);
	if (ExistDLLRoot) {}
	else {
		mdfolder(DLLPATH);
	}
	if (_access(settings.c_str(), 0)) {
		string ResSET = getselfpath() + "\\DefaultSettings.ini";
		CopyFile(ResSET.c_str(), settings.c_str(), 0);
	}
	string PATHROOTLang = readini(settings, "Settings", "Language");
	string langtext = RunPath + PATHROOTLang;
	if (_access(langtext.c_str(), 0)) {
		MessageBox(0, "Language Resources Load Failed", "Outlang", MB_ICONERROR | MB_OK);
	}

	return readini(langtext, "Language", langblock);
}

string VarTrans(string VarSelect) {
	return VarSelect;
}

string HeadSpaceClean(string Info) {
	int maxCSize = Info.size();
	string readMCS, tempInfo;
	int currentFit;

	//cout << "Max C Size :  _" << maxCSize << endl;
	for (currentFit = 0; currentFit < maxCSize; currentFit++) {
		readMCS = Info[currentFit];
		//cout << "Read MCS :  _" << readMCS << endl;
		if (readMCS == " ") {}
		else {
			while (currentFit < maxCSize) {
				//cout << "Trans Add : _" << Info[currentFit] << endl;
				tempInfo = tempInfo + Info[currentFit];
				currentFit++;
			}
		}
	}
	return tempInfo;
}


void pulltitle() {
	if (InsidePreview == 1) {
		cout << "Pull Title is Disabled by DebugMode" << endl;
		return;
	}
	string pulldownaddress = getenv("temp");
	pulldownaddress = pulldownaddress + "\\CalciumPulltitle.txt";
	if (_access(pulldownaddress.c_str(), 0)) {
		URLDown(readini(CONFIGROOT, "Version", "PullTitle"), pulldownaddress);
		Sleep(400);
		if (_access(pulldownaddress.c_str(), 0)) {
			return;
		}
	}
	int maxread = 1;
	string ReadNULLCheck;
	//获取最大支持范围
	BackCheckRUN:
	ReadNULLCheck = LineReaderA(pulldownaddress, maxread);
	if (ReadNULLCheck == "overline") {
		maxread--;
		goto outputPTS;
	}
	maxread++;
	goto BackCheckRUN;

	outputPTS:
	int PullRand = SpawnRandomNum(1, maxread);
	cout << LineReaderA(pulldownaddress, PullRand) << endl;
	return;
}

void lntype(string block) {
	cout << Outlang(block) << endl;
	return;
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
		return "ReadFailed";
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
	if (checkChar(info, replaceword) == 0) {
		return info;
	}
	return Replace(info, replaceword, "");
}

string TransVar(string Info) {
	string backinfo = Info;

	if (VarSpaceMax == 0) {
		return backinfo;
	}

	string getfullLine,ResChar,ReplaceChar;

	for (int startrollmax = 0, readmark = 2; startrollmax < VarSpaceMax; startrollmax++, readmark++) {
		getfullLine = cutlineblockA(VarSpace, ";", readmark);
		ResChar = cutlineblockA(getfullLine, "=", 1);
		ReplaceChar = cutlineblockA(getfullLine, "=", 2);
		ReplaceChar = Replace(ReplaceChar, "%sbar%", " ");
		ReplaceChar = Replace(ReplaceChar, "%selbar%", ";");
		ReplaceChar = Replace(ReplaceChar, "%eqbar%", "=");
		ReplaceChar = Replace(ReplaceChar, "%mnbar%", "$");

		backinfo = Replace(backinfo, ResChar, ReplaceChar);
	}

	return backinfo;
}

void varspaceadd(string VarHead, string varinfo) {
	VarHead = CleanAuto(VarHead, " ");

	if (varinfo == "") {
		varinfo = "NULL";
	}

	varinfo = Replace(varinfo, " ", "%sbar%");
	varinfo = Replace(varinfo, ";", "%selbar%");
	varinfo = Replace(varinfo, "%eqbar%", "=");
	varinfo = Replace(varinfo, "%mnbar%", "$");

	if (checkChar(VarHead, ";") == 1) {
		cout << "There is illegal text in the var" << endl;
		return;
	}

	if (VarSpaceMax == 0) {
		
		VarSpace = VarSpace + VarHead + "=" + varinfo + ";";

		VarSpaceMax++;

		return;
	}

	int startReadVar = 2;
	string readvar;

	string varhead;
	string varset;

BackFoundOldLine:
	//%var Mark Reader
	//cout << "readvar Head :  " << VarSpace << ".  " << VarHead << "_  " << to_string(startReadVar) << "_." << endl;
	readvar = cutlineblockA(VarSpace, ";", startReadVar);
	//cout << "readvar : " << readvar << endl;
	readvar = CleanAuto(readvar, ";");
	//cout << "readvar After Clean : " << readvar << endl;

	//Get XX = NN

	varhead = cutlineblockA(readvar, "=", 1);

	if (varhead == VarHead) {
		//cout << "Varhead : _" << varhead << "_. Select :  _" << VarHead << "_" << endl;
		varset = cutlineblockA(readvar, "=", 2);
		//cout << "Var Set :  _" << varset << "_" << endl;
		string delvars = varhead + "=" + varset + ";";
		string newvars = varhead + "=" + varinfo + ";";
		//cout << "Sort Delete Info :  _" << delvars << "_ .  ResData :  _" << VarSpace << "_" << endl;
		VarSpace = Replace(VarSpace, delvars,newvars);
		//cout << "After CUT :  _" << VarSpace << "_" << endl;
		//cout << "After VarMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
		//cout << "Var Space is Update.  Max : " << to_string(VarSpaceMax) << " . Message:   " << VarSpace << endl;
		return;
	}

	startReadVar--;
	//cout << "IF Command :  _" << to_string(startReadVar) << "_  . VMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (startReadVar == VarSpaceMax) {

		VarSpace = VarSpace + VarHead + "=" + varinfo + ";";

		VarSpaceMax++;

		return;
	}

	startReadVar++;
	startReadVar++;
	goto BackFoundOldLine;
}

void varspacedelete(string VarHead) {

	if (VarSpaceMax == 0) {
		cout << "No any var is Set" << endl;
		return;
	}
	int startReadVar = 2;
	string readvar;

	string varhead;
	string varset;

BackFoundLine:
	//%var Mark Reader
	//cout << "readvar Head :  _" << VarSpace << "_.  _" << VarHead << "_  _" << to_string(startReadVar) << "_." << endl;
	readvar = cutlineblockA(VarSpace, ";", startReadVar);
	//cout << "readvar : " << readvar << endl;
	readvar = CleanAuto(readvar, ";");
	//cout << "readvar After Clean : " << readvar << endl;

	//Get XX = NN

	varhead = cutlineblockA(readvar, "=", 1);
	
	if (varhead == VarHead) {
		//cout << "Varhead : _" << varhead << "_. Select :  _" << VarHead << "_" << endl;
		varset = cutlineblockA(readvar, "=", 2);
		//cout << "Var Set :  _" << varset << "_" << endl;
		string delvars = varhead + "=" + varset + ";";
		//cout << "Sort Delete Info :  _" << delvars << "_ .  ResData :  _" << VarSpace << "_" << endl;
		VarSpace = CleanAuto(VarSpace, delvars);
		//cout << "After CUT :  _" << VarSpace << "_" << endl;
		VarSpaceMax--;
		//cout << "After VarMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
		//cout << "Var Space is Update.  Max : " << to_string(VarSpaceMax) << " . Message:   " << VarSpace << endl;
		return;
	}

	startReadVar--;
	//cout << "IF Command :  _" << to_string(startReadVar) << "_  . VMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (startReadVar == VarSpaceMax) {
		cout << "Var Not Found" << endl;
		return;
	}

	startReadVar++;
	startReadVar++;
	goto BackFoundLine;
}

// 0 OK
// 1 FAILED
int DLLSETUP(string DLLNAME) {
	TRYAGAINDLLSETUP:
	cout << endl;
	lntype("lang.kernel.dllsetup");
	cout << endl;
	string WebDoc = getenv("temp");
	WebDoc = WebDoc + "\\CalciumPLG.txt";
	if (_access(WebDoc.c_str(),0)){}
	else {
		goto SkipDownloadWDC;
	}

	URLDown(readini(CONFIGROOT, "Version", "PluginAPI"), WebDoc);
	Sleep(800);
	if (_access(WebDoc.c_str(), 0)) {
		lntype("lang.kernel.errorwebdoc");
		cpause(Outlang("lang.public.PTA"));
		goto TRYAGAINDLLSETUP;
	}
	
SkipDownloadWDC:
	string WDLLRead = readini(WebDoc, "PluginServer", DLLNAME);
	if (WDLLRead == "readini-failed") {
		lntype("lang.kernel.dllnotfound");
		cout << "DLL :  _" << DLLNAME << "_" << endl;
 		cpause(Outlang("lang.public.PAK"));
		return 1;
	}
	cout << endl;
	lntype("lang.kernel.dllsetupNow");
	cout << "Plugin :  _" << DLLNAME << "_.  Info  :   " << readini(WebDoc, "PluginServer", DLLNAME + "-INFO") << endl;
	string dllsetpath = DLLPATH + "\\" + DLLNAME;
	cout << "Install Plugin :  " << WDLLRead << ".  to  " << dllsetpath << endl;
	URLDown(WDLLRead, dllsetpath);
	Sleep(800);
	if (_access(dllsetpath.c_str(), 0)) {
			cout << "Failed to Download Plugin" << endl;
			cpause(Outlang("lang.public.PAK"));
			return 1;
		}

	cout << "Plugin Install OK" << endl;

	fstream CreateDLLReg;
	CreateDLLReg.open(DLLRECORD, ios::out | ios::app);
	CreateDLLReg << DLLNAME << endl;
	CreateDLLReg.close();

	return 0;
}

//0 NoFile
//1 NULL Plugin
//2 Plugin Load Error
//3 OK
//4 Not Need Load Again
int dllregister(string DLLNAME) {
	DLLNAME = Replace(DLLNAME, "\"", "");
	if (checkChar(DLLRegList, DLLNAME) == 1) {
		return 4;
	}
	ReLoadDLLREG:
	DLLNAME = Replace(DLLNAME, "\"", "");
	//cout << "StartLoadDLL" << endl;
	if (_access(DLLNAME.c_str(), 0)) {
		string newpath = DLLPATH;
		mdfolder(newpath);
		string nDLLNAME = newpath + "\\" + DLLNAME;
		if (_access(nDLLNAME.c_str(), 0)) {
			cout << "DLL ACTIVITY" << endl;
			//DLL Activity
			int BACKDSP = DLLSETUP(DLLNAME);
			if (BACKDSP == 1) {
				cout << "DLL Error" << endl;
				return 0;
			}
			goto ReLoadDLLREG;
		}
		else {
			DLLNAME = nDLLNAME;
		}
	}
	//cout << "LoadAPI" << endl;
	int back = DllCheckPlugin(DLLNAME);
	//cout << "Verify。。。" << endl;
	if (back == 1) {
		return 1;
	}

	//cout << "Get Reg。。。" << endl;
	string newvardll = DLLRegAPI(DLLNAME,1);
	//cout << "Reg is :  _" << newvardll << "_" << endl;
	if (newvardll == "LOADFAIL") {
		return 2;
	}
	if (newvardll == "LOADNULL") {
		return 2;
	}
	//DLL Translate API
	//cout << "Replace API。。。" << endl;
	newvardll = Replace(newvardll, "lpDllPath", DLLNAME);

	//END
	//cout << "Add VarSpace。。。" << endl;
	VarSpace = VarSpace + newvardll;

	//cout << "Add VarSpaceMax。。。" << endl;
	int maxvarget = atoi(DLLRegAPI(DLLNAME, 2).c_str());

	//cout << "Make Add" << endl;

	VarSpaceMax=VarSpaceMax + maxvarget;
	DLLRegList = DLLRegList + DLLNAME + ";";

	//cout << "Complete。。。" << endl;
	return 3;
}

//0-OK 1-FAILED
int DLLUpdate(string DLLNAMEX) {
	string DLLNAME = CleanAuto(DLLNAMEX, "\"");
	string dllrootset = DLLPATH + "\\" + DLLNAME;

	if (_access(dllrootset.c_str(), 0)) {
		cout << "No This Plugin, This Plugin maybe not enabled" << endl;
		return 1;
	}

	int dllgetver = dllCurrVersion(dllrootset);

	if (dllgetver == 404) {
		cout << "Failed to Find DLL Version" << endl;
		return 1;
	}

	cout << "Dll Update :  _" << to_string(dllgetver) << "_ .  DLL Name :  _" << DLLNAME << "_." << endl;

	string TempWDC = getenv("temp");
	string WebDoc = TempWDC + "\\CalciumPLG.txt";

	if (_access(WebDoc.c_str(), 0)) {
		URLDown(readini(CONFIGROOT, "Version", "PluginAPI"), WebDoc);
		if (_access(WebDoc.c_str(), 0)) {
			cout << "Failed to Connect Plugin Server. Please Check your internet." << endl;
			cout << "or Use other Server" << endl;
			return 1;
		}
	}

	//GetVersion
	string NewVersion = readini(WebDoc, "PluginServer", DLLNAME + "-LatestVer");
	if (NewVersion == "readini-failed") {
		cout << "This DLL is not on Support List" << endl;
		return 1;
	}

	int LatestSupportVer = atoi(NewVersion.c_str());

	if (LatestSupportVer == dllgetver) {
		cout << "This DLL is Latest Version" << "   DLL NAME :  _" << DLLNAME << "_.  Current Version :  _" << to_string(dllgetver) << "_." << endl;
		return 0;
	}

	//New Update
	cout << "Update Your DLL Library..." << endl;
	cout << "DLL NAME :  _" << DLLNAME << "_.  Current Version :  _" << to_string(dllgetver) << "_.  New Version :  _" << to_string(LatestSupportVer) << "_" << endl;

	remove(dllrootset.c_str());

	cout << "Download From :  " << readini(WebDoc, "PluginServer", DLLNAME) << "  . To " << dllrootset << endl;
	URLDown(readini(WebDoc, "PluginServer", DLLNAME), dllrootset);
	Sleep(300);
	if (_access(dllrootset.c_str(), 0)) {
		cout << "Update Failed. Download Failed" << endl;
		return 1;
	}

	cout << "Update Complete" << endl;
	return 0;
}

// -2 Version Not Allow
// -1 Normal Exit
// 0 No Dialog Next
// 1 Unknown Command
// 2 CrashScript
// >2 Skip Goto
int RollCMD(string CaCMDS, string ResCMD, string File, int CURRLINE, int vercode) {

	string ReadCMD = cutlineblockA(CaCMDS, " ", 1);
	string ReadSourceX = cutlineblockA(ResCMD, " ", 1);
	string ReadSource = CleanAuto(ReadSourceX, " ");
	if (ReadCMD == "") {
		return 0;
	}

	BackRollResCMD:
	//cout << "Read CMD :   _" << ReadCMD << "_" << endl;
	if (ReadCMD == "NUL") {
		ReadSource = ResCMD;
		ReadCMD = ResCMD;
	}

	if (ReadSource == "var") {
		ResCMD = CleanAuto(ResCMD, "var ");
		ResCMD = CleanAuto(ResCMD, "var");
		CaCMDS = CleanAuto(CaCMDS, "var ");
		CaCMDS = CleanAuto(CaCMDS, "var");

		if (ResCMD == "") {
			cout << ReadCMD <<" Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     var <var> = <data>" << endl;
			WarningRecord++;
			return 0;
		}
		if (checkChar(ResCMD, "=")==0) {
			cout << ReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     var <var> = <data>" << endl;
			WarningRecord++;
			return 0;
		}

		string VARS = cutlineblockA(ResCMD, "=", 1);
		ResCMD = CleanAuto(ResCMD, VARS + "=");
		if (ResCMD == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     var <var> = <data>" << endl;
			WarningRecord++;
			return 0;
		}
		string VARINFO = cutlineblockA(CaCMDS, "=", 2);

		//cout << "Res CMD _" << ResCMD << "_" << endl;

		varspaceadd(VARS, VARINFO);
		return 0;
	}
	if (ReadSource == "del.var") {
		ResCMD = CleanAuto(ResCMD, "del.var ");
		ResCMD = CleanAuto(ResCMD, "del.var");
		if (ResCMD == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     del.var <var>" << endl;
			WarningRecord++;
			return 0;
		}
		varspacedelete(ResCMD);
		return 0;
	}

	if (ReadSource == "dll.var") {
		CaCMDS = CleanAuto(CaCMDS, "dll.var ");
		CaCMDS = CleanAuto(CaCMDS, "dll.var");
		ResCMD = CleanAuto(ResCMD, "dll.var ");
		ResCMD = CleanAuto(ResCMD, "dll.var");
		if (ResCMD == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << "DLLVAR :     dll.var a = <DLLFILE>|<FULL COMMAND>" << endl;
			cout << "Use on DLL Register" << endl;
			WarningRecord++;
			return 0;
		}

		string VarSTA = cutlineblockA(ResCMD, "=", 1);

		CaCMDS = cutlineblockA(CaCMDS, "=", 2);

		if (checkChar(CaCMDS, "|") == 0) {
			cout << "You Need to Register \"|\" to DLLCMD" << endl;
			ErrorRecord++;
			return 2;
		}
		string DLLNAME = cutlineblockA(CaCMDS, "|", 1);
		//cout << "DLL :  _" << DLLNAME << "_" << endl;
		string DCMD = cutlineblockA(CaCMDS, "|", 2);
		//cout << "DLL :  _" << DLLNAME << "_.  COMMAND :   _" << DCMD << "_" << endl;

		if (_access(DLLNAME.c_str(), 0)) {
			cout << "_" << DLLNAME << "_" << endl;
			cout << "DLL Not Exist. DLL CMD" << endl;
			ErrorRecord++;
			return 2;
		}

		//cout << "Run DLL Start" << endl;
		string nDLLOutage = DllLoadCmd(DLLNAME, DCMD);
		//cout << "Run DLL End" << endl;
		if (nDLLOutage == "nul") {
			cout << "DLL Run Exception" << endl;
			ErrorRecord++;
			return 2;
		}

		varspaceadd(VarSTA, nDLLOutage);

		return 0;
	}

	//DLLRegister
	if (ReadCMD == "LoadDLL") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     LoadDLL <DLLFile>" << endl;
			WarningRecord++;
			return 0;
		}
		int dlrback = dllregister(CaCMDS);
		if (dlrback == 0) {
			lntype("lang.kernel.nothisdll");
			ErrorRecord++;
			return 2;
		}
		if (dlrback == 1) {
			lntype("lang.kernel.notcadll");
			ErrorRecord++;
			return 2;
		}
		if (dlrback == 2) {
			lntype("lang.kernel.dllfail");
			ErrorRecord++;
			return 2;
		}
		if (dlrback == 3) {
			lntype("lang.kernel.dllok");
			ErrorRecord++;
			return 0;
		}
		if (dlrback == 4) {
			lntype("lang.kernel.dllnotneed");
			ErrorRecord++;
			return 0;
		}
		return 0;
	}
	if (ReadCMD == "DLLCMD") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << "DLLCMD :     $DLLCMD |<DLLFILE>|<FULL COMMAND>" << endl;
			cout << "Use on DLL Register" << endl;
			WarningRecord++;
			return 0;
		}
		if (checkChar(CaCMDS, "|") == 0) {
			cout << "You Need to Register \"|\" to DLLCMD" << endl;
			ErrorRecord++;
			return 2;
		}
		string DLLNAME = cutlineblockA(CaCMDS, "|", 1);
		//cout << "DLL :  _" << DLLNAME << "_" << endl;
		string DCMD = cutlineblockA(CaCMDS, "|", 2);
		//cout << "DLL :  _" << DLLNAME << "_.  COMMAND :   _" << DCMD << "_" << endl;

		if (_access(DLLNAME.c_str(), 0)) {
			cout << "_" << DLLNAME << "_" << endl;
			cout << "DLL Not Exist. DLL CMD" << endl;
			ErrorRecord++;
			return 2;
		}
		
		//cout << "Run DLL Start" << endl;
		int DLLOutage = DllLoad(DLLNAME, DCMD);
		//cout << "Run DLL End" << endl;
		if (DLLOutage == 1) {
			cout << "DLL Run Exception" << endl;
			ErrorRecord++;
			return 2;
		}

		return 0;
	}

	//VaR
	if (ReadCMD == "goto") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "Text: :AAA:    Command: goto :AAA:" << endl;
			WarningRecord++;
			return 0;
		}

		//查找 p1
		int XCURRLINE = 3;

	ASBackRoll:
		//获取函数

		string cl_strx = to_string(XCURRLINE);

		//cout << cl_str << endl;

		string GetLineData = LineReader(File, XCURRLINE);
		//cout << "Line " << cl_strx << "  INFO :  _" << GetLineData << "_" << endl;

		if (GetLineData == "overline") {
			cout << "Goto Error:  Head :  _" << CaCMDS << "_" << endl;
			ErrorRecord++;
			return 2;
		}
		if (GetLineData == CaCMDS) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			return XCURRLINE;
		}
		XCURRLINE++;
		goto ASBackRoll;
	}
	if (ReadCMD == "pause") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cpause(Outlang("lang.public.PAK"));
			return 0;
		}
		cpause(CaCMDS);
		return 0;
	}
	if (ReadCMD == "end") {
		return -1;
	}
	if (ReadCMD == "system") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << " COMMAND :     system <OS Command>" << endl;
			WarningRecord++;
			return 0;
		}
		CaCMDS = HeadSpaceClean(CaCMDS);
		CaCMDS = cutlineblockA(CaCMDS, "\"", 1);
		if (CaCMDS == "NUL") {
			cout << "Null Type. Add \" in Message Head." << endl;
			WarningRecord++;
			return 0;
		}
		system(CaCMDS.c_str());
		return 0;
	}
	if (ReadCMD == "list") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		CaCMDS = HeadSpaceClean(CaCMDS);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << "Please select you want list" << endl;
			cout << "Like a  varspace," << endl;
			return 0;
		}
		if (CaCMDS == "varspace") {
			cout << "Var Space Block :  _" << VarSpace << "_" << endl;
			cout << "MaxVar :  " << to_string(VarSpaceMax) << endl;
			return 0;
		}
		if (CaCMDS == "vp") {
			cout << "Var Space Block :  _" << VarSpace << "_" << endl;
			cout << "MaxVar :  " << to_string(VarSpaceMax) << endl;
			return 0;
		}
		if (CaCMDS == "dllroot") {
			cout << "DLL ROOT  :  _" << DLLPATH << "_" << endl;
			return 0;
		}
		if (CaCMDS == "dllreg") {
			cout << "DLL Reg List  :  _" << DLLRegList << "_" << endl;
			return 0;
		}
		if (CaCMDS == "dllver") {
			cout << "List All Dll Version" << endl;
			cout << endl;
			string ReadP;
			string dllrootsetN = DLLPATH;
			int LRRP = 1;
			int RPTotal = 0;

			int dllgetver;
		BackReadDLLV:
			ReadP = LineReader(DLLRECORD, LRRP);
			if (ReadP == "overline") {
				cout << "Read Complete" << endl;
				cout << "Total :  _" << to_string(RPTotal) << "_" << endl;
				cout << endl;
				return 0;
			}
			string dllrootset = dllrootsetN + "\\" + ReadP;
			
			dllgetver = dllCurrVersion(dllrootset);

			if (dllgetver == 404) {
				//read failed
				cout << "DLL :  _" << ReadP << "_.  Version :  _ReadError_." << endl;
			}
			else {
				cout << "DLL :  _" << ReadP << "_.  Version :  _" << to_string(dllgetver) << "_." << endl;
			}
			
			LRRP++;
			RPTotal++;
			goto BackReadDLLV;
		}
		if (CaCMDS == "path") {
			string GetPath = getrunpath();
			cout << "Current Path :  " << GetPath << endl;
			return 0;
		}
		ErrorRecord++;
		cout << "Unknown List :  _" << CaCMDS << "_" << endl;
		return 1;
	}
	if (ReadCMD == "cout") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << " COMMAND :     cout \"<Message>\"" << endl;
			WarningRecord++;
			return 0;
		}
		if (CaCMDS == "%n") {
			cout << endl;
			return 0;
		}
		
		CaCMDS = HeadSpaceClean(CaCMDS);
		CaCMDS = cutlineblockA(CaCMDS, "\"", 1);
		if (CaCMDS == "NUL") {
			cout << "Null Type. Add \" in Message Head." << endl;
			WarningRecord++;
			return 0;
		}

		cout << CaCMDS << endl;
		return 0;
	}
	if (ReadCMD == "cls") {
		system("cls");
		return 0;
	}
	if (ReadCMD == "setpath") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << " COMMAND :    setpath <PATH>" << endl;
			WarningRecord++;
			return 0;
		}
		CaCMDS = HeadSpaceClean(CaCMDS);
		CaCMDS = cutlineblockA(CaCMDS, "\"", 1);
		if (CaCMDS == "NUL") {
			cout << "Null Type. Add \" in Message Head." << endl;
			WarningRecord++;
			return 0;
		}
		SetCurrentDirectory(CaCMDS.c_str());
		return 0;
	}
	//Other
	if (ReadSource == "update.dll") {
		CaCMDS = CleanAuto(CaCMDS, "update.dll ");
		CaCMDS = CleanAuto(CaCMDS, "update.dll");
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << " COMMAND :     update.dll <DllName>" << endl;
			cout << "only support list plugin" << endl;
			WarningRecord++;
			return 0;
		}
		CaCMDS = CleanAuto(CaCMDS, "\"");
		int abdllu = DLLUpdate(CaCMDS);
		if (abdllu == 1) {
			cout << "DLL Update Failed :  " << CaCMDS << endl;
			WarningRecord++;
			return 0;
		}
		else {
			cout <<"DLL Check Update Complete :  " << CaCMDS << endl;
			return 0;
		}
		return 0;
	}

	return 1;
}

void CaRootLoaderX() {
	//cout << "Start Load Root" << endl;
	varspaceadd("CalciumVersion", Version);
	varspaceadd("CalciumVerCode", to_string(vercode));
	varspaceadd("CalciumPKG", getwinenv("cd"));
	varspaceadd("CalciumComVer", ComVer);
	varspaceadd("CalciumRunPath", getselfpath());
	varspaceadd("CalciumCore", getselfinfo());
	//cout << "Load OK Root" << endl;
	return;
}

//rootlockmode 1-open 0-off
//Return Num :  1=Exception 0=Normal
int ScriptRun(string File, int vercode, int startline, int rootlockmode, string unsafelock) {
	ReTryRollScript:
	int readline = startline;
	string ReadPoint;
	string AfterTranslate;
	string ErrCode;
	string Tercmd;
	string RunPathSet = CutFilePath(ResLoadFile);

	SetCurrentDirectory(RunPathSet.c_str());
	cout << "Set Local Path :  _" << RunPathSet << "_" << endl;

RollBackScript:
	ReadPoint = LineReader(File, readline);
	if (ReadPoint == "ReadFailed") {
		cout << "Calcium Run Script Error" << endl;
		cout << "Path :  " << RunPathSet << endl;
		cout << "Script File :  " << File << endl;
		cpause(Outlang("lang.public.PAK"));
		return 0;
	}
	if (ReadPoint == "") {
		readline++;
		goto RollBackScript;
	}
	if (checkChar(ReadPoint, "$") == 1) {
		readline++;
		goto RollBackScript;
	}
	if (ReadPoint == "overline") {
		cout << endl;
		cout << "[ WARNING ]   Please add \"end\" on Script" << endl;
		ErrorRecord++;
		return 1;
	}

	Tercmd = cutlineblockA(ReadPoint, " ", 1);

	if (Tercmd == "#setminver") {
		int MXVer = atoi(cutlineblockA(ReadPoint, " ", 2).c_str());
		if (MXVer > vercode) {
			lntype("lang.kernel.vernotallow");
			cout << "Min Set :  _" << to_string(MXVer) << "_.    Current Version :   _" << to_string(vercode) << "_." << endl;
			cpause(Outlang("lang.public.PAK"));
			return 0;
		}
		readline++;
		goto RollBackScript;
	}
	if (Tercmd == "#onlyadmin") {
		//cout << "Check Administrator" << endl;
		if (testAdminA() == 1) {
			cout << "Run On Administrator" << endl;
			readline++;
			goto RollBackScript;
		}
		else {
			cout << "Run Not on Administrator" << endl;
			lntype("lang.kernel.onlyAdmin");
			cpause(Outlang("lang.public.PAK"));
			return 0;
		}
	}
	if (Tercmd == "#loadcaroot") {
		//cout << "Loading Calcium Root" << endl;
		CaRootLoaderX();
		//cout << "Load OK" << endl;
		readline++;
		goto RollBackScript;
	}
	//cout << "TerCMD :  _" << Tercmd << "_" << endl;
	//cout << "No TerCMD" << endl;

	if (rootlockmode == 1) {
		writeini(unsafelock, "Run", "Command", ReadPoint);
		writeini(unsafelock, "Run", "Script", File);
		writeini(unsafelock, "Run", "Line", to_string(readline));
		writeini(unsafelock, "Run", "FullVersion", Version + "~" + to_string(vercode));
		writeini(unsafelock, "Run", "VarSpace", VarSpace);
		writeini(unsafelock, "Run", "DllregList", DLLRegList);
		writeini(unsafelock, "Run", "LaunchPara", LaunchParameter);
		writeini(unsafelock, "Run", "ErrRec", to_string(ErrorRecord));
		writeini(unsafelock, "Run", "WarRec", to_string(WarningRecord));
	}
	AfterTranslate = TransVar(ReadPoint);

	//cout << "Start Roll CMD" << endl;
	//cout << "----------------------------------------------------------------------------------------------------" << endl;
	//cout << "Command :  _" << AfterTranslate << "_ .  ResCommand :   _" << ReadPoint << "_" << endl;
	int cmrd = RollCMD(AfterTranslate, ReadPoint, File, readline, vercode);
	//cout << "CMRD :  _" << to_string(cmrd) << "_" << endl;
	//cout << "----------------------------------------------------------------------------------------------------" << endl;
	//cout << "VarSpace :  " << VarSpace << endl;
	//cout << "----------------------------------------------------------------------------------------------------" << endl;
	if (cmrd == -3) {
		// KernelError
		cout << endl;
		lntype("lang.dllapi.loadkernelfailed");
		remove(unsafelock.c_str());
		cpause(Outlang("lang.public.PAK"));
		return 0;
	}
	if (cmrd == -2) {
		// version Not Allow
		cpause("press any key to Exit");
		remove(unsafelock.c_str());
		return 0;
	}
	if (cmrd == -1) {
		//Return Exit
		remove(unsafelock.c_str());
		return 0;
	}
	if (cmrd == 1) {
		cout << "Unknown Command :  " << ReadPoint << "  Line :  " << to_string(readline) << endl;
		ErrorRecord++;
	}
	if (cmrd == 2) {
		cout << endl;
		cout << "Script is Crash." << endl;
		cout << "On The :  " << to_string(readline) << " .  COMMAND :  " << ReadPoint << endl;
		cout << "This Problem is happend by Script" << endl;
		cout << endl;
		return 1;
	}
	if (cmrd > 2) {
		readline = cmrd;
		goto RollBackScript;
	}

	readline++;
	goto RollBackScript;
}

string linkfile = getwinenvfast("public") + "\\Desktop\\Calcium Script Shell.lnk";
string COREFILE = getselfinfo();

void regcalcium() {
	int TSAREG = testAdminA();
	if (TSAREG == 1) {
		cout << "Calcium Register" << endl;
		system("reg add HKEY_CLASSES_ROOT\\CalciumPackage /ve /t REG_SZ /d \"Calcium Package Program\" /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell /ve /t REG_SZ /d  \"open\" /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell\\open\\command /ve /t REG_SZ /f /d \"Cac.exe -capt \\\"%1\\\"\"");

		system("reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell\\runas /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell\\runas\\command /ve /t REG_SZ /f /d \"Cac.exe -capt \\\"%1\\\"\"");

		system("reg add HKEY_CLASSES_ROOT\\CalciumScript /ve /t REG_SZ /d \"Calcium Run Script\" /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell /ve /t REG_SZ /d  \"open\" /f");

		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\open /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\open\\command /ve /t REG_SZ /f /d \"Cac.exe -casp \\\"%1\\\"\"");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\runas /f");

		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\runas\\command /ve /t REG_SZ /f /d \"Cac.exe -casp \\\"%1\\\"\"");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\edit /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\edit\\command /ve /t REG_SZ /f /d \"Notepad.exe \\\"%1\\\"\"");

		system("reg add HKEY_CLASSES_ROOT\\.ca /ve /t REG_SZ /d  \"CalciumScript \" /f");
		system("reg add HKEY_CLASSES_ROOT\\.cascript /ve /t REG_SZ /d  \"CalciumScript \" /f");
		system("reg add HKEY_CLASSES_ROOT\\.casp /ve /t REG_SZ /d  \"CalciumScript \" /f");
		system("reg add HKEY_CLASSES_ROOT\\.capt /ve /t REG_SZ /d  \"CalciumPackage \" /f");

		string cmds = "reg add HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v \"Calcium Auto Update\" /t REG_SZ /d \"" + CaUpdMain +"\"";
		//cout << "_" << cmds << "_" << endl;
		system(cmds.c_str());

		//添加PATH
		SetCurrentDirectory(getselfpath().c_str());
		string cacore = getwinenvfast("SystemRoot") + "\\cac.exe";
		if (_access(".\\Cac.exe", 0)) {
			Sleep(3000);
			if (_access(".\\Cac.exe", 0)) {
				MessageBox(0, "Error, Cac Fast Invoke is Missing on Install", "Auto Register calcium", MB_ICONERROR | MB_OK);
			}
		}
		CopyFile(".\\Cac.exe", cacore.c_str(), 0);
		string MainTain = getselfpath() + "\\CaMainTain.exe";

		ShellExecute(0, "runas", MainTain.c_str(), 0, 0, SW_SHOW);

		string CASHELCore = getselfpath() + "\\CaShell.exe";

		createlink(CASHELCore, linkfile, "", "Calcium Program Shell");
		mdfolder(PGDataf);
		writeini(PGINSDATA, "Install", "Path", getselfpath());

		system("assoc .ca=CalciumScript");
		system("assoc .cascript=CalciumScript");
		system("assoc .casp=CalciumScript");
		system("assoc .capt=CalciumPackage");
		cout << "Complete" << endl;
		return;
	}
	MessageBox(0, "Using Administrator Run", "Run Notice", MB_OK);
	ShellExecute(0, "runas", COREFILE.c_str(), "-reg", 0, SW_SHOW);
	return;
}

void unregcalcium() {
	int TSAREG = testAdminA();
	if (TSAREG==1) {
		cout << "Calcium UnRegister" << endl;
		cout << "Taskkill CaMainTain" << endl;
		ShellExecute(0, "runas", "taskkill.exe", "/f /im CaMainTain.exe", 0, SW_HIDE);
		cout << "Delete Register" << endl;
		system("reg delete HKEY_CLASSES_ROOT\\CalciumScript /f");
		system("reg delete HKEY_CLASSES_ROOT\\CalciumPackage /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v \"Calcium Auto Update\" /f");
		system("reg delete HKEY_CLASSES_ROOT\\.ca /f");
		system("reg delete HKEY_CLASSES_ROOT\\.casp /f");
		system("reg delete HKEY_CLASSES_ROOT\\.cascript /f");
		system("reg delete HKEY_CLASSES_ROOT\\.capt /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\.capt /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\.ca /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\.casp /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\.cascript /f");
		system("reg delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.ca /f");
		system("reg delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.casp /f");
		system("reg delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.cascript /f");
		system("reg delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.capt /f");
		//删除CAC
		string cacore = getwinenvfast("SystemRoot") + "\\cac.exe";
		remove(cacore.c_str());
		remove(linkfile.c_str());

		rmfolder(PGDataf);

		cout << "Complete" << endl;
		return;
	}
	MessageBox(0, "Using Administrator Run", "Run Notice", MB_OK);
	ShellExecute(0, "runas", COREFILE.c_str(), "-unreg", 0, SW_SHOW);
	return;
}

