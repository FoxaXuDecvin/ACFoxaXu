#pragma once
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\ACFoxaXuProject\ACFoxaXu\ACFoxaXu\DLLApi.h"
using namespace std;

int InsidePreview = 0;

string what = "HelloWord";

string RunINFO = getselfinfo();
string RunPath = getselfpath();
string CaMain = getselfpath() + "\\Calcium.exe";
string CaUpdMain = getselfpath() + "\\CaUpdater.exe";
string CaOutage = getselfpath() + "\\CaOutage.exe";
string CONFIGROOT = RunPath + "\\config.ini";
string settings = RunPath + "\\settings.ini";
string PROGData = getwinenvfast("ProgramData") + "\\CalciumScript";

string DLLTPATH = readini(CONFIGROOT, "default", "DLLPATH");
string DLLSPATH = Replace(DLLTPATH, "$CURRENT", getselfpath());
string DLLPATH = Replace(DLLSPATH, "$PROGDATA", PROGData);

string verinfor = readini(CONFIGROOT, "Version", "CURRENT");
int vercode = atoi(verinfor.c_str());
string Version = readini(CONFIGROOT,"Version","CodeName");
string ComVer = readini(CONFIGROOT, "Version", "ComVer");
string KernelFile = getselfpath() + "\\" + readini(CONFIGROOT, "Version", "Kernel");

string VarSpace = "varspace;";
int VarSpaceMax;

string LangOut(string title) {
	string langfile = readini(settings, "setting", "text");
	cout << readini(langfile, "CALCIUM", title) << endl;
}

string Outlang(
	string langblock//Set Type Title
) {
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

void pulltitle() {
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

	int readpoint = 1;
	int startReadVar = 2;
	string VarHead;
	string readvar;
	
	string varhead;
	string varset;

BackTransLate:
	//%var Mark Reader
	VarHead = ";";
	//cout << "readvar Head :  " << VarSpace << ".  " << VarHead << "_  " << to_string(startReadVar) << "_." << endl;
	readvar = cutlineblockA(VarSpace, VarHead, startReadVar);
	//cout << "readvar : " << readvar << endl;
	readvar = CleanAuto(readvar, ";");
	//cout << "readvar After Clean : " << readvar << endl;

	//Get XX = NN

	varhead = cutlineblockA(readvar, "=", 1);
	//cout << "Varhead : _" << varhead << "_" << endl;
	varset = cutlineblockA(readvar, "=", 2);
	//cout << "VarSet : _" << varset << "_" << endl;
	//cout << "Current VarSpace :  _" << VarSpace << "_" << endl;
	backinfo = Replace(backinfo, "%sbar%", " ");
	backinfo = Replace(backinfo, "%selbar%", ";");
	backinfo = Replace(backinfo, "%eqbar%", "=");
	backinfo = Replace(backinfo, "%mnbar%", "$");
	//cout << "VarSet : _" << backinfo << "_  _" << varhead << "_   _" << varset << "_" << endl;
	backinfo = Replace(backinfo, varhead, varset);

	//cout << "BackInfo :  _" << backinfo << "_" << endl;
	//cout << "If Command :  _" << to_string(readpoint) << "_   VarSpaceMax :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (readpoint == VarSpaceMax) {
		//cout << "BackData :  _" << backinfo << "_" << endl;
		//cout << "-----------------------------------------------------------------" << endl;
		backinfo = Replace(backinfo, "%sbar%", " ");
		backinfo = Replace(backinfo, "%selbar%", ";");
		backinfo = Replace(backinfo, "%eqbar%", "=");
		backinfo = Replace(backinfo, "%mnbar%", "$");
		return backinfo;
	}
	readpoint++;
	startReadVar++;
	goto BackTransLate;

}

void varspaceadd(string VarHead, string varinfo) {
	VarHead = CleanAuto(VarHead, " ");
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
	cout << "Please Select \" y/n \" (default: y)>";
	string usersel;
	getline(cin, usersel);

	bool atest = testAdmin(getselfpath() + "\\Plugin");
	if (atest) {}
	else {
		lntype("lang.public.Admin");
		cpause(Outlang("lang.public.PAK"));
		return 1;
	}

	if (usersel == "") {
		usersel = "y";
	}
	if (usersel == "Y") {
		usersel = "y";
	}

	if (usersel == "y") {
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

		return 0;
	}

	return 1;
}

//0 NoFile
//1 NULL Plugin
//2 Plugin Load Error
//3 OK
int dllregister(string DLLNAME) {
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

	//cout << "Complete。。。" << endl;
	return 3;
}

// -2 Version Not Allow
// -1 Normal Exit
// 0 No Dialog Next
// 1 Unknown Command
// 2 CrashScript
// >2 Skip Goto
int RollCMD(string CaCMDS, string ResCMD, string File, int CURRLINE, int vercode) {
	
	string ReadCMD = cutlineblockA(CaCMDS, " ", 1);
	string ReadSource = cutlineblockA(ResCMD, " ", 1);
	if (ReadCMD == "") {
		return 0;
	}

	BackRollResCMD:
	//cout << "Read CMD :   _" << ReadCMD << "_" << endl;
	if (ReadSource == "new.var") {
		ResCMD = CleanAuto(ResCMD, "new.var ");
		ResCMD = CleanAuto(ResCMD, "new.var");
		if (ResCMD == "") {
			cout << ReadCMD <<" Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     new.var <var> = <data>" << endl;
			return 0;
		}
		string VARS = cutlineblockA(ResCMD, "=", 1);
		string VARINFO = cutlineblockA(ResCMD, "=", 2);
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
			return 0;
		}
		varspacedelete(ResCMD);
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
			return 0;
		}
		int dlrback = dllregister(CaCMDS);
		if (dlrback == 0) {
			lntype("lang.kernel.nothisdll");
			return 2;
		}
		if (dlrback == 1) {
			lntype("lang.kernel.notcadll");
			return 2;
		}
		if (dlrback == 2) {
			lntype("lang.kernel.dllfail");
			return 2;
		}
		if (dlrback == 3) {
			lntype("lang.kernel.dllok");
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
			return 0;
		}
		if (checkChar(CaCMDS, "|") == 0) {
			cout << "You Need to Register \"|\" to DLLCMD" << endl;
			return 2;
		}
		string DLLNAME = cutlineblockA(CaCMDS, "|", 1);
		//cout << "DLL :  _" << DLLNAME << "_" << endl;
		string DCMD = cutlineblockA(CaCMDS, "|", 2);
		//cout << "DLL :  _" << DLLNAME << "_.  COMMAND :   _" << DCMD << "_" << endl;

		if (_access(DLLNAME.c_str(), 0)) {
			cout << "_" << DLLNAME << "_" << endl;
			cout << "DLL Not Exist. DLL CMD" << endl;
			return 2;
		}
		
		//cout << "Run DLL Start" << endl;
		int DLLOutage = DllLoad(DLLNAME, DCMD);
		//cout << "Run DLL End" << endl;
		if (DLLOutage == 1) {
			cout << "DLL Run Exception" << endl;
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
			return 0;
		}

		//查找 p1
		int XCURRLINE = 2;

	ASBackRoll:
		//获取函数

		string cl_strx = to_string(XCURRLINE);

		//cout << cl_str << endl;

		string GetLineData = LineReader(File, XCURRLINE);
		//cout << "Line " << cl_strx << "  INFO :  _" << GetLineData << "_" << endl;

		if (GetLineData == "overline") {
			cout << "Goto Error:  Head :  _" << CaCMDS << "_" << endl;
			return 2;
		}
		if (GetLineData == CaCMDS) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			return XCURRLINE;
		}
		XCURRLINE++;
		goto ASBackRoll;
	}
	if (ReadCMD == "msgbox.var") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		CaCMDS = CleanAuto(CaCMDS, "msgbox.var ");
		CaCMDS = CleanAuto(CaCMDS, "msgbox.var");
		CaCMDS = CleanAuto(CaCMDS, "anticrashHEAD");
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << " COMMAND :     msgbox.var <var> = <Title>|<Info>" << endl;
			return 0;
		}
		string VARS = cutlineblockA(CaCMDS, "=", 1);

		string MsgTag = cutlineblockA(CaCMDS, "=", 2);

		string mgtitle = cutlineblockA(MsgTag, "|", 1);
		string mginfo = cutlineblockA(MsgTag, "|", 2);

		int MGBack = MessageBox(0, mginfo.c_str(), mgtitle.c_str(), MB_ICONWARNING | MB_YESNO);
		if (MGBack == 6) {
			varspaceadd(VARS, "YES");
			return 0;
		}
		else {
			varspaceadd(VARS, "NO");
			return 0;
		}
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
			return 0;
		}
		system(CaCMDS.c_str());
		return 0;
	}
	if (ReadCMD == "list") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
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
		cout << "Unknown List :  _" << CaCMDS << "_" << endl;
		return 1;
	}
	if (ReadCMD == "cout") {
		CaCMDS = CleanAuto(CaCMDS, ReadCMD + " ");
		CaCMDS = CleanAuto(CaCMDS, ReadCMD);
		if (CaCMDS == "") {
			cout << ReadCMD << " Command:  " << endl;
			cout << " COMMAND :     cout <Message>" << endl;
			return 0;
		}
		if (CaCMDS == "%nextline%") {
			cout << endl;
			return 0;
		}
		cout << CaCMDS << endl;
		return 0;
	}
	if (ReadCMD == "cls") {
		system("cls");
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
int ScriptRun(string File, int vercode, int startline, int rootlockmode,string unsafelock) {
	int readline = startline;
	string ReadPoint;
	string AfterTranslate;
	string ErrCode;
	string Tercmd;

RollBackScript:
	ReadPoint = LineReader(File, readline);
	if (ReadPoint == "overline") {
		cout << endl;
		cout << "[ WARNING ]   Please add \"end\" on Script" << endl;
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
		cout << "Check Administrator" << endl;
		bool TestOAV = testAdmin(readini(settings, "Settings", "AdminCheckPath"));
		if (TestOAV) {
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

	if (rootlockmode == 1) {
		writeini(unsafelock, "Run", "Command",ReadPoint);
		writeini(unsafelock, "Run", "Script", File);
		writeini(unsafelock, "Run", "Line",to_string(readline));
		writeini(unsafelock, "Run", "FullVersion", Version + "~" + to_string(vercode));
		writeini(unsafelock, "Run", "VarSpace", VarSpace);
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


	remove(unsafelock.c_str());
	readline++;
	goto RollBackScript;
}