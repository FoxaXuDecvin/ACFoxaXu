#pragma once
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"
using namespace std;

int InsidePreview = 1;

string what = "HelloWord";

string RunINFO = getselfinfo();
string RunPath = getselfpath();
string CONFIGROOT = RunPath + "\\config.ini";
string settings = RunPath + "\\settings.ini";

string verinfor = readini(CONFIGROOT, "Version", "CURRENT");
int vercode = atoi(verinfor.c_str());
string Version = readini(CONFIGROOT,"Version","CodeName");
string ComVer = readini(CONFIGROOT, "Version", "ComVer");

string VarSpace = "varspace;";
int VarSpaceMax;

string LangOut(string title) {
	string langfile = readini(settings, "setting", "text");
	cout << readini(langfile, "CALCIUM", title) << endl;
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

string cutlineblock(string lines, int line) {

	//cout << "New Request :  Text " << lines << "    Line " << to_string(line) << endl;

	if (line == NULL) {
		return "NULL";
	}
	if (line < 0) {
		return "MinSetFailed";
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

	int curfind = 1;

	string a;

	//Start

	a = strtok(Slinecut, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;

	AddAgain:

	a = strtok(NULL, Slinechar);
	//cout << "Line :  " << line << "  CurFind :   " << curfind << endl;
	if (line == curfind) {
		//cout << "Return :  " << a << endl;
		return a;
	}
	curfind++;
	goto AddAgain;
	//END

	return "failed~s";
}

string cutlineblockA(string lines,string cutmark, int line) {

	//cout << "New Request :  Text " << lines << "    Line " << to_string(line) << endl;

	if (line == NULL) {
		return "NULL";
	}
	if (line < 0) {
		return "MinSetFailed";
	}

	char* Slinechar = nullptr;
	char* Slinecut = nullptr;

	const char* STR_Line = nullptr;
	const char* old_Line = nullptr;

	string Rep_INFO = cutmark;
	old_Line = lines.c_str();
	STR_Line = Rep_INFO.c_str();

	Slinechar = const_cast<char*>(STR_Line);
	Slinecut = const_cast<char*>(old_Line);

	string strback;

	int curfind = 1;

	string a;

	//Start

	a = strtok(Slinecut, Slinechar);
	if (line == curfind) {
		return a;
	}
	curfind++;

AddAgain:

	a = strtok(NULL, Slinechar);
	//cout << "Line :  " << line << "  CurFind :   " << curfind << endl;
	if (line == curfind) {
		//cout << "Return :  " << a << endl;
		return a;
	}
	curfind++;
	goto AddAgain;
	//END

	return "failed~s";
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

	//cout << "VarSet : _" << backinfo << "_  _" << varhead << "_   _" << varset << "_" << endl;
	backinfo = Replace(backinfo, varhead, varset);
	//cout << "BackInfo :  _" << backinfo << "_" << endl;

	//cout << "If Command :  _" << to_string(readpoint) << "_   VarSpaceMax :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (readpoint == VarSpaceMax) {
		//cout << "BackData :  _" << backinfo << "_" << endl;
		//cout << "-----------------------------------------------------------------" << endl;
		return backinfo;
	}
	readpoint++;
	startReadVar++;
	goto BackTransLate;

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

void varspaceadd(string varhead, string varinfo) {
	VarSpace = VarSpace + varhead + "=" + varinfo + ";";

	VarSpaceMax++;

	return;
}
void varspacedelete(string VarHead) {
	int startReadVar = 1;
	string readvar;

	string varhead;
	string varset;

BackFoundLine:
	//%var Mark Reader
	VarHead = ";";
	//cout << "readvar Head :  " << VarSpace << ".  " << VarHead << "_  " << to_string(startReadVar) << "_." << endl;
	readvar = cutlineblockA(VarSpace, VarHead, startReadVar);
	//cout << "readvar : " << readvar << endl;
	readvar = CleanAuto(readvar, ";");
	//cout << "readvar After Clean : " << readvar << endl;

	//Get XX = NN

	varhead = cutlineblockA(readvar, "=", 1);

	//cout << "IF Command :  _" << to_string(startReadVar) << "_  . VMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (varhead == varhead) {
		//cout << "Varhead : _" << varhead << "_" << endl;
		varset = cutlineblockA(readvar, "=", 2);

		string delvars = varhead + "=" + varset + ";";
		//cout << "Sort Delete Info :  _" << delvars << "_ .  ResData :  _" << VarSpace << "_" << endl;
		VarSpace = CleanAuto(VarSpace, delvars);
		//cout << "After CUT :  _" << VarSpace << "_" << endl;
		VarSpaceMax--;
		//cout << "After VarMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
		//cout << "Var Space is Update.  Max : " << to_string(VarSpaceMax) << " . Message:   " << VarSpace << endl;
		return;
	}

	startReadVar++;
	goto BackFoundLine;
}

//正常退出输出 0.异常输出 1

int CaCmdRun(string CaCMDS, string ResCMD, string File, int CURRLINE, int vercode, string PubVar) {
	if (checkChar(CaCMDS, "///") == 1) {
		return 0;
	}
	if (checkChar(CaCMDS, "#load ") == 1) {
		//cout << "Load Part" << endl;
		string p1 = CleanAuto(CaCMDS, "#load ");
		//cout << "p1 = _" << p1 << "_" << endl;

		//查找 p1
		int XCURRLINE = 2;

	ASBackRoll:
		//获取函数

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
			return 2;
		}
		if (GetLineData == p1) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			return XCURRLINE;
		}
		XCURRLINE++;
		goto ASBackRoll;
		//END p1

	}
	
	if (checkChar(CaCMDS, "$$Prints") == 1) {
		//输出文档
		string p1 = CleanAuto(CaCMDS, "$$Prints(\"");
		string out = CleanAuto(p1, "\");");
		printf(out.c_str());
		cout << endl;
		return 0;
	}
	if (checkChar(CaCMDS, "$Cout") == 1) {
		//输出文档
		string out = CleanAuto(CaCMDS, "$Cout ");
		printf(out.c_str());
		cout << endl;
		return 0;
	}
	if (checkChar(CaCMDS, "$$MsgBox") == 1) {
		//输出文档
		string p1 = CleanAuto(CaCMDS, "$$MsgBox(\"");
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
			writeini(PubVar, "VarST", mbvar, "yes");
		}
		else {
			WriteNewMRA(PubVar, "MRALIST", mbvar);
			writeini(PubVar, "VarST", mbvar, "no");
		}

	SkipRecordNUL:
		cout << endl;
		return 0;
	}
	if (checkChar(CaCMDS, "$$endl") == 1) {
		cout << endl;
		return 0;
	}
	if (checkChar(CaCMDS, "$~") == 1) {
		return 0;
	}
	if (checkChar(CaCMDS, "$pause") == 1) {
		string p1 = CleanAuto(CaCMDS, "$pause(\"");
		string out = CleanAuto(p1, "\");");
		cout << endl;
		cpause(out);
		cout << endl;
		return 0;
	}
	if (checkChar(CaCMDS, "$Windows.CMD") == 1) {
		//Windows CMD
		string p1 = CleanAuto(CaCMDS, "$Windows.CMD(\"");
		string out = CleanAuto(p1, "\");");
		system(out.c_str());
		return 0;
	}
	if (checkChar(CaCMDS, "#end") == 1) {
		return -1;
	}
	if (checkChar(CaCMDS, "$$SetConTitle") == 1) {
		//输出文档
		string p1 = CleanAuto(CaCMDS, "$$SetConTitle(\"");
		string out = CleanAuto(p1, "\");");
		SetConsoleTitle(out.c_str());
		return 0;
	}
	if (checkChar(CaCMDS, "$$Timeout") == 1) {
		//输出文档
		string p1 = CleanAuto(CaCMDS, "$$Timeout(\"");
		string out = CleanAuto(p1, "\");");
		int sleepout = atoi(out.c_str());
		Sleep(sleepout);

		return 0;
	}
	if (checkChar(CaCMDS, "$cls") == 1) {
		system("cls");
		return 0;
	}
	if (checkChar(CaCMDS, "#mgrver") == 1) {
		//输出文档
		string p1 = CleanAuto(CaCMDS, "#mgrver");
		int curver = atoi(p1.c_str());
		if (curver == vercode) {}
		else {
			string VNIF = to_string(vercode);
			cout << "Warning This Script Only Running on :   " << p1 << endl;
			cout << "Current ADSF Version is :   " << VNIF << endl;
			return -2;
		}

		return 0;
	}
	if (checkChar(CaCMDS, "$Type ") == 1) {
		string settype = CleanAuto(CaCMDS, "$Type ");
		if (_access(settype.c_str(), 0)) {
			cout << "Missing Text File :  " << settype << endl;
			cout << "Cannot Type File" << endl;
			return 0;
		}

		//编排
		int currentline = 1;

	BackRead:
		//read
		string readtxt = LineReader(settype, currentline);
		if (readtxt == "overline") {
			// Read OK
			return 0;
		}
		string outtext = TransVar(readtxt);

		//output
		cout << outtext << endl;

		currentline++;
		goto BackRead;
	}

	//Calcium api
	if (checkChar(CaCMDS, "$WinEnv") == 1) {
		string p1 = CleanAuto(ResCMD, "$WinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		string WinEnv = getwinenvfast(WinEnvS.c_str());

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar, WinEnv);

		return 0;
	}
	if (checkChar(CaCMDS, "$AWinEnv") == 1) {
		string p1 = CleanAuto(ResCMD, "$AWinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		string WinEnv = getwinenv(WinEnvS.c_str());

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar, WinEnv);

		return 0;
	}
	if (checkChar(CaCMDS, "$BWinEnv") == 1) {
		string p1 = CleanAuto(ResCMD, "$AWinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		string WinEnvSet = getwinenvapi(WinEnvS);

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar, WinEnvSet);

		return 0;
	}
	if (checkChar(ResCMD, "$UpVar") == 1) {

		varspaceadd("$CalciumVersion$", Version);
		varspaceadd("$CalciumVerCode$", to_string(vercode));
		varspaceadd("$CalciumPackage$", getwinenv("cd"));
		varspaceadd("$CalciumComVer$", ComVer);
		varspaceadd("$CalciumRunPath$", getselfpath());
		varspaceadd("$CalciumCore$", getselfinfo());

		return 0;
	}
	//WindowsAPI

	//创建文件夹
	if (checkChar(CaCMDS, "$$winapi.md") == 1) {
		string p1 = CleanAuto(CaCMDS, "$$winapi.md(\"");
		string out = CleanAuto(p1, "\");");

		CreateDirectory(out.c_str(), 0);

		return 0;
	}
	if (checkChar(CaCMDS, "$$winapi.rd") == 1) {
		string p1 = CleanAuto(CaCMDS, "$$winapi.rd(\"");
		string out = CleanAuto(p1, "\");");

		rmfolder(out.c_str());

		return 0;
	}
	if (checkChar(CaCMDS, "$$winapi.urlmon") == 1) {
		string p1 = Replace(CaCMDS, "\",\"", " ");
		string p2 = CleanAuto(p1, "$$winapi.urlmon(\"");
		string out = CleanAuto(p2, "\");");

		string URLINFO = cutlineblock(out, 1);
		string SPINFO = cutlineblock(out, 2);
		string SWITCHS = cutlineblock(out, 3);

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
			cout << "Download Failed" << endl;
		}
		else {
			cout << "Download OK" << endl;
		}

		return 0;
	}

	//变量
	if (checkChar(ResCMD, "$new.var") == 1) {

		string p1 = CleanAuto(ResCMD, "$new.var ");
		string out = CleanAuto(p1, " ");

		string varname = cutlineblockA(out,"=",1);

		if (checkChar(varname, ";")==1){
			cout << "Found Text has Forbidden Text :  \";\"" << endl;
			return 2;
		}

		string varinfo = cutlineblockA(out,"=", 2);

		//cout << "Old VarSpace :  " << VarSpace << endl;

		varspaceadd(varname, varinfo);

		//cout << "Var Space is Update.  Max : " << to_string(VarSpaceMax) << " . Message:   " << VarSpace << endl;

		return 0;
	}

	if (checkChar(ResCMD, "$del.var") == 1) {

		string p1 = CleanAuto(ResCMD, "$del.var");
		string out = CleanAuto(p1, " ");

		//cout << "Select Delete Var :   _" << out << "_" << endl;

		//Search Var

		if (VarSpaceMax == 0) {
			cout << "[Warning]No Var is Set" << endl;
			return 0;
		}

		if (checkChar(VarSpace, out) == 1) {
			varspacedelete(out);
			return 0;
		}
		else {
			cout << "Var is not exist :  _" << out << "_" << endl;
		}
	}

	if (checkChar(CaCMDS, "$GetCin") == 1) {

		string out = CleanAuto(CaCMDS, "$GetCin ");

		string svar = cutlineblockA(out,"<", 1);
		string outinfo = cutlineblockA(out, "<", 2);

		string varinfo;
		cout << outinfo;
		getline(cin, varinfo);
		cout << endl;

		VarSpace = VarSpace + svar + "=" + varinfo + ";";

		VarSpaceMax++;

		return 0;
	}

	//debug

	if (checkChar(ResCMD, "#$CharTests") == 1) {
		string p1 = CleanAuto(ResCMD, "$CharTests(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string rescmdA = cutlineblock(out, 1);
		string rescmd = Replace(rescmdA, "\\sp%", " ");
		int address = atoi(cutlineblock(out, 2).c_str());

		cout << "Res CMD :  " << rescmd << "    address :  " << to_string(address) << endl;

		cout << cutlineblock(rescmd, address) << endl;
		return 0;
	}
	if (checkChar(ResCMD, "#$OutVarSpace") == 1) {
		cout << "_" << VarSpace << "_" << endl;
		cout << "VarSpaceMax :  _" << to_string(VarSpaceMax) << "_" << endl;
		return 0;
	}

	//无效断流区域
	if (CaCMDS == "overline") {
		cout << endl;
		cout << "Script Not Set Exist API" << endl;
		return 2;
	}
	if (CaCMDS == "") {
		return 0;
	}

	//未知指令
	return 1;
}

int ScriptRun(string File, int vercode, int startline, string PubVar) {
	ofstream logs;
	string logfile = "log~" + to_string(SpawnRandomNum(11111, 99999)) + "~record.log";
	logs.open(logfile);

	int readline = startline;
	string ReadPoint;
	string AfterTranslate;

RollBackScript:
	ReadPoint = LineReader(File, readline);
	AfterTranslate = TransVar(ReadPoint);

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
			ScriptRun(FileInclude, vercode, XCURRLINE, PubVar);

			readline++;
			goto RollBackScript;
		}
		XCURRLINE++;
		goto ANBackRoll;

		//PCA End

	}

	int cmrd = CaCmdRun(AfterTranslate, ReadPoint, File, readline, vercode, PubVar);
	if (cmrd == -2) {
		// version Not Allow
		cpause("press any key to Exit");
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
		logs << "Unknown Command :  " << ReadPoint << "  Line :  " << to_string(readline) << endl;
		goto RollBackScript;
	}
	if (cmrd == 2) {
		cout << endl;
		cout << "Script is Crash." << endl;
		cout << "On The :  " << to_string(readline) << " .  COMMAND :  " << ReadPoint << endl;
		cout << "This Problem is happend by Script" << endl;
		cout << endl;
		remove(PubVar.c_str());
		return 1;
	}
	if (cmrd > 2) {
		readline = cmrd;
		goto RollBackScript;
	}

	readline++;
	goto RollBackScript;
}