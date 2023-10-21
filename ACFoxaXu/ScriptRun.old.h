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
		return "notexist";
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

//正常退出输出 0.异常输出 1
int CaCmdRun(string CaCMDS, string ResCMD, string File, int CURRLINE, int vercode) {
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
			varspaceadd(mbvar, "yes");
		}
		else {
			varspaceadd(mbvar, "no");
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

		varspaceadd(WriteVar, WinEnv);

		return 0;
	}
	if (checkChar(CaCMDS, "$AWinEnv") == 1) {
		string p1 = CleanAuto(ResCMD, "$AWinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		string WinEnv = getwinenv(WinEnvS.c_str());

		varspaceadd(WriteVar, WinEnv);

		return 0;
	}
	if (checkChar(CaCMDS, "$BWinEnv") == 1) {
		string p1 = CleanAuto(ResCMD, "$AWinEnv(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string WinEnvS = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		string WinEnvSet = getwinenvapi(WinEnvS);

		varspaceadd(WriteVar, WinEnvSet);

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
	if (checkChar(ResCMD, "#Debug.TestCrash") == 1) {
		string A = cutlineblockA(what, "N", 2);
		cout << "Its seems not crash happend" << endl;
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

		string varname = cutlineblockA(out, "=", 1);

		if (checkChar(varname, ";") == 1) {
			cout << "Found Text has Forbidden Text :  \";\"" << endl;
			return 2;
		}

		string varinfo = cutlineblockA(out, "=", 2);

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

		string svar = cutlineblockA(out, "<", 1);
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