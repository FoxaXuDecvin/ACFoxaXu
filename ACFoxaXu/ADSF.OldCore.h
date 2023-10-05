#pragma once
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\ACFoxaXuProject\ACFoxaXu\ACFoxaXu\DLLApi.h"
using namespace std;

int InsidePreview = 1;

string what = "HelloWord";

string RunINFO = getselfinfo();
string RunPath = getselfpath();
string CaMain = getselfpath() + "\\Calcium.exe";
string CaUpdMain = getselfpath() + "\\CaUpdater.exe";
string CaOutage = getselfpath() + "\\CaOutage.exe";
string CONFIGROOT = RunPath + "\\config.ini";
string settings = RunPath + "\\settings.ini";

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

//0 NoFile
//1 NULL Plugin
//2 Plugin Load Error
//3 OK
int dllregister(string DLLNAME) {
	if (_access(DLLNAME.c_str(), 0)) {
		return 0;
	}
	int back = DllCheckPlugin(DLLNAME);
	if (back == 1) {
		return 1;
	}

	string newvardll = DLLRegAPI(DLLNAME,1);
	if (newvardll == "LOADFAIL") {
		return 2;
	}
	if (newvardll == "LOADNULL") {
		return 2;
	}
	//DLL Translate API
	newvardll = Replace(newvardll, "lpDllPath", DLLNAME);

	VarSpace = VarSpace + newvardll;

	int maxvarget = atoi(DLLRegAPI(DLLNAME, 2).c_str());

	VarSpaceMax=VarSpaceMax + maxvarget;

	return 3;
}

int RollCMD(string CaCMDS, string ResCMD, string File, int CURRLINE, int vercode) {
	//cout << "RSCommand :  _" << CaCMDS << "_" << endl;
	//cout << "RCommand :  _" << ResCMD << "_" << endl;

	//防止冲突
	CaCMDS = Replace(CaCMDS, "$$", "$");
	ResCMD = Replace(ResCMD, "$$", "$");

	if (ResCMD == "") {
		return 0;
	}
	if (ResCMD == "$") {
		return 1;
	}
	if (ResCMD == "$ ") {
		return 1;
	}
	if (CaCMDS == "") {
		//cout << "No Command" << endl;
		return 0;
	}

	CaCMDS = "anticrashHEAD$" + CaCMDS;//AntiCrash
	ResCMD = "anticrashHEAD$" + ResCMD;//AntiCrash

	int sk = 0;
	if (readini(settings, "Settings", "ShellAutoMark") == "open") {
		sk = 1;
	}
	else {
		sk = 0;
	}

	//再次Filter

	//cout << "A:  RSCommand :  _" << CaCMDS << "_" << endl;
	//cout << "A:  RCommand :  _" << ResCMD << "_" << endl;

	string UseCMD;

	if (sk == 1) {
		UseCMD = cutlineblockA(CaCMDS, "$", 2);
	}
	else {
		CaCMDS = CleanAuto(CaCMDS, "anticrashHEAD$");
		if (checkChar(CaCMDS, "$") == 0)return 0;
		UseCMD = CaCMDS;
	}

	//cout << "B:  RSCommand :  _" << CaCMDS << "_" << endl;
	//cout << "B:  RCommand :  _" << ResCMD << "_" << endl;

	UseCMD = CleanAuto(UseCMD, "$");

	//cout << ResCMD << endl;

	string UseRCMD = cutlineblockA(ResCMD, "$", 2);

	//cout << UseRCMD << endl;

	UseRCMD = CleanAuto(UseRCMD, "$");
	//cout << "Command :   _" << UseCMD << "_" << endl;

	//cout << "C:  RSCommand :  _" << CaCMDS << "_" << endl;
	//cout << "C:  RCommand :  _" << ResCMD << "_" << endl;
	//cout << "C:  USECommand :  _" << UseCMD << "_" << endl;
	//cout << "C:  RUSECommand :  _" << UseRCMD << "_" << endl;

	string ReadCMD = cutlineblockA(UseRCMD, " ", 1);
	string VReadCMD = cutlineblockA(UseCMD, " ", 1);

	cout << "D: RSCommand :  _" << ReadCMD << "_" << endl;
	cout << "D: RUSECommand :  _" << VReadCMD << "_" << endl;

	int brc = 0;

	//cout << "Command :  _" << ReadCMD << "_" << endl;
	BackRollResCMD:
	//cout << "Read CMD :   _" << ReadCMD << "_" << endl;
	if (ReadCMD == "new.var") {
		UseRCMD = CleanAuto(UseRCMD, "new.var ");
		UseRCMD = CleanAuto(UseRCMD, "new.var");
		UseRCMD = CleanAuto(UseRCMD, "anticrashHEAD");
		if (UseRCMD == "") {
			cout << "new.var Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     new.var <var> = <data>" << endl;
			return 0;
		}
		string VARS = cutlineblockA(UseRCMD, "=", 1);
		string VARINFO = cutlineblockA(UseRCMD, "=", 2);
		varspaceadd(VARS, VARINFO);
		return 0;
	}
	if (ReadCMD == "del.var") {
		UseRCMD = CleanAuto(UseRCMD, "del.var ");
		UseRCMD = CleanAuto(UseRCMD, "del.var");
		UseRCMD = CleanAuto(UseRCMD, "anticrashHEAD");
		if (UseRCMD == "") {
			cout << "del.var Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     del.var <var>" << endl;
			return 0;
		}
		varspacedelete(UseRCMD);
		return 0;
	}

	//DLLRegister
	if (ReadCMD == "LoadDLL") {
		UseCMD = CleanAuto(UseCMD, "LoadDLL ");
		UseCMD = CleanAuto(UseCMD, "LoadDLL");
		UseCMD = CleanAuto(UseCMD, "anticrashHEAD");
		if (UseCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << " COMMAND :     LoadDLL <DLLFile>" << endl;
			return 0;
		}
		int dlrback = dllregister(UseCMD);
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
		UseRCMD = CleanAuto(UseRCMD, "DLLCMD ");
		UseRCMD = CleanAuto(UseRCMD, "DLLCMD");
		UseRCMD = CleanAuto(UseRCMD, "anticrashHEAD");
		if (UseRCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
			cout << "If you using Shell Mode. You can use \"list varspace\" to Show All var" << endl;
			cout << "DLLCMD :     $DLLCMD |<DLLFILE>|<FULL COMMAND>" << endl;
			cout << "Use on DLL Register" << endl;
			return 0;
		}
		if (checkChar(UseRCMD, "|") == 0) {
			cout << "You Need to Register \"|\" to DLLCMD" << endl;
			return 2;
		}
		string DLLNAME = cutlineblockA(UseRCMD, "|", 1);
		//cout << "DLL :  _" << DLLNAME << "_" << endl;
		string DCMD = cutlineblockA(UseRCMD, "|", 2);
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
		UseCMD = CleanAuto(UseCMD, "$goto ");
		UseCMD = CleanAuto(UseCMD, "$goto");
		UseCMD = CleanAuto(UseCMD, "anticrashHEAD");
		if (UseCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
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
			cout << "Goto Error:  Head :  _" << UseCMD << "_" << endl;
			return 2;
		}
		if (GetLineData == UseCMD) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			return XCURRLINE;
		}
		XCURRLINE++;
		goto ASBackRoll;
	}
	if (ReadCMD == "msgbox.var") {
		UseRCMD = CleanAuto(UseRCMD, "msgbox.var ");
		UseRCMD = CleanAuto(UseRCMD, "msgbox.var");
		UseRCMD = CleanAuto(UseRCMD, "anticrashHEAD");
		UseCMD = CleanAuto(UseCMD, "msgbox.var ");
		UseCMD = CleanAuto(UseCMD, "msgbox.var");
		UseCMD = CleanAuto(UseCMD, "anticrashHEAD");
		if (UseCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
			cout << " COMMAND :     msgbox.var <var> = <Title>|<Info>" << endl;
			return 0;
		}
		string VARS = cutlineblockA(UseRCMD, "=", 1);

		string MsgTag = cutlineblockA(UseCMD, "=", 2);

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
		UseCMD = CleanAuto(UseCMD, "pause ");
		UseCMD = CleanAuto(UseCMD, "pause");
		UseCMD = CleanAuto(UseCMD, "anticrashHEAD");
		if (UseCMD == "") {
			cpause(Outlang("lang.public.PAK"));
			return 0;
		}
		cpause(UseCMD);
		return 0;
	}
	if (ReadCMD == "end") {
		return -1;
	}
	if (ReadCMD == "system") {
		UseCMD = CleanAuto(UseCMD, "system ");
		UseCMD = CleanAuto(UseCMD, "system");
		UseCMD = CleanAuto(UseCMD, "anticrashHEAD");
		if (UseCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
			cout << " COMMAND :     system <OS Command>" << endl;
			return 0;
		}
		system(UseCMD.c_str());
		return 0;
	}
	if (ReadCMD == "list") {
		UseRCMD = CleanAuto(UseRCMD, "list ");
        UseRCMD = CleanAuto(UseRCMD, "list");
		UseRCMD = CleanAuto(UseRCMD, "anticrashHEAD");
		if (UseRCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
			cout << "Please select you want list" << endl;
			cout << "Like a  varspace," << endl;
			return 0;
		}
		if (UseRCMD == "varspace") {
			cout << "Var Space Block :  _" << VarSpace << "_" << endl;
			cout << "MaxVar :  " << to_string(VarSpaceMax) << endl;
			return 0;
		}
		if (UseRCMD == "vp") {
			cout << "Var Space Block :  _" << VarSpace << "_" << endl;
			cout << "MaxVar :  " << to_string(VarSpaceMax) << endl;
			return 0;
		}
		cout << "Unknown List :  _" << UseRCMD << "_" << endl;
		return 1;
	}
	if (ReadCMD == "cout") {
		UseCMD = CleanAuto(UseCMD, "cout ");
		UseCMD = CleanAuto(UseCMD, "cout");
		UseCMD = CleanAuto(UseCMD, "anticrashHEAD");
		if (UseCMD == "") {
			cout << VReadCMD << " Command:  " << endl;
			cout << " COMMAND :     cout <Message>" << endl;
			return 0;
		}
		if (UseCMD == "%nextline%") {
			cout << endl;
			return 0;
		}
		cout << UseCMD << endl;
		return 0;
	}
	if (ReadCMD == "cls") {
		system("cls");
		return 0;
	}

	if (brc == 0) {
		ReadCMD = cutlineblockA(UseCMD, " ", 1);
		ReadCMD = CleanAuto(ReadCMD, "$");
		brc = 1;
		goto BackRollResCMD;
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
	string VarSpace, ErrCode;
	string Tercmd;

RollBackScript:
	ReadPoint = LineReader(File, readline);
	if (ReadPoint == "overline") {
		cout << endl;
		cout << "[ WARNING ]   Please add $end on Script" << endl;
		return 1;
	}
	if (checkChar(ReadPoint, "$") == 1) {
		goto SkipTercmd;
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

	SkipTercmd:
	//cout << "Check LockMode" << endl;
	if (rootlockmode == 1) {
		writeini(unsafelock, "Run", "Command",ReadPoint);
		writeini(unsafelock, "Run", "Script", File);
		writeini(unsafelock, "Run", "Line",to_string(readline));
		cmarkfile(unsafelock + "~DVS", VarSpace);
		writeini(unsafelock, "Run", "FullVersion", Version + "~" + to_string(vercode));
	}
	//cout << "TransVar" << endl;
	AfterTranslate = TransVar(ReadPoint);

	//cout << "Check Var Include" << endl;
	if (checkChar(AfterTranslate, "#Include") == 1) {
		string p1 = CleanAuto(AfterTranslate, "#Include(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string FileInclude = cutlineblock(out, 1);
		string LoadPart = cutlineblock(out, 2);

		if (_access(FileInclude.c_str(), 0)) {
			cout << endl;
			cout << endl;
			cout << "Error, Script Try To load a Null Include. Line :  " << to_string(readline) << endl;
			cout << "Unable to load from :  " << FileInclude << endl;
			cout << "File :  _" << FileInclude << "_, Not Found" << endl;
			return 1;
		}
		///PCA 1

		//查找 p1
		int XCURRLINE = 2;

	ANBackRoll:
		//获取函数

		string cl_strx = to_string(XCURRLINE);

		//cout << cl_str << endl;

		string GetLineData = LineReader(FileInclude, XCURRLINE);
		//cout << "Line " << cl_strx << "  INFO :  _" << GetLineData << "_" << endl;

		if (GetLineData == "overline") {
			cout << endl;
			cout << endl;
			cout << "Error, Script Try To load a Null Include. Line :  " << to_string(readline) << endl;
			cout << "Unable to load from :  " << File << endl;
			cout << "Head :  _" << LoadPart << "_, Found Failed" << endl;
			return 1;
		}
		//cout << "_" << GetLineData << "_,_" << LoadPart << "_" << endl;
		if (GetLineData == LoadPart) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			ScriptRun(FileInclude, vercode, XCURRLINE, 0, "NULL");

			readline++;
			goto RollBackScript;
		}
		XCURRLINE++;
		goto ANBackRoll;

		//PCA End

	}

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