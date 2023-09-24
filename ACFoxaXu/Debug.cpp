#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include"D:\CppHeader\GlobalVar.h"

using namespace std;

int main() {
	Reload:
	system("cls");
	cout << "Type some Command" << endl;
	string linecin;
	getline(cin,linecin);

	int cmdret = 0;

	while (cmdret == 1) {
		if (linecin == "a") {
			cout << "You Type A" << endl;
			cmdret = 1;
		}
		if (linecin == "b") {
			cout << "You Type B" << endl;
			cmdret = 1;
		}
		if (linecin == "c") {
			cout << "You Type C" << endl;
			cmdret = 1;
		}
		cout << "Null Type" << endl;
		cpause("NULL ....");
		goto
	}
}

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
	if (checkChar(CaCMDS, "#Include") == 1) {
		string p1 = CleanAuto(CaCMDS, "#Include(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string FileInclude = cutlineblock(out, 1);
		string LoadPart = cutlineblock(out, 2);

		if (_access(FileInclude.c_str(), 0)) {
			cout << endl;
			cout << endl;
			cout << "Error, Script Try To load a Null Include. Line :  " << to_string(CURRLINE) << endl;
			cout << "Unable to load from :  " << FileInclude << endl;
			cout << "File :  _" << FileInclude << "_, Not Found" << endl;
			return 2;
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
			cout << "Error, Script Try To load a Null Include. Line :  " << to_string(CURRLINE) << endl;
			cout << "Unable to load from :  " << File << endl;
			cout << "Head :  _" << LoadPart << "_, Found Failed" << endl;
			return 2;
		}
		//cout << "_" << GetLineData << "_,_" << LoadPart << "_" << endl;
		if (GetLineData == LoadPart) {
			//cout << "XCURRLINE :  " << to_string(XCURRLINE) << endl;
			ScriptRun(FileInclude, vercode, XCURRLINE, PubVar);

			return 0;
		}
		XCURRLINE++;
		goto ANBackRoll;

		//PCA End

	}
	if (checkChar(CaCMDS, "$$Prints") == 1) {
		//输出文档
		string p1 = CleanAuto(CaCMDS, "$$Prints(\"");
		string out = CleanAuto(p1, "\");");
		printf(out.c_str());
		cout << endl;
		return 0;
	}
	if (checkChar(CaCMDS, "$$Cout") == 1) {
		//输出文档
		string out = CleanAuto(CaCMDS, "$$Cout ");
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
		string outtext = TransVar(readtxt, PubVar);

		//output
		cout << outtext << endl;

		currentline++;
		goto BackRead;
	}

	//Calcium api
	if (checkChar(CaCMDS, "$ApplyVar") == 1) {

		string p1 = CleanAuto(CaCMDS, "$ApplyVar(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string SelectVar = cutlineblock(out, 1);
		string WriteVar = cutlineblock(out, 2);

		if (SelectVar == "#$Version~calcium$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, Version);
			return 0;
		}
		if (SelectVar == "#$VersionCode~calcium$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, to_string(vercode));
			return 0;
		}
		if (SelectVar == "#$CalciumRunPath$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, getselfpath());
			return 0;
		}
		if (SelectVar == "#$CalciumCore$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, getselfinfo());
			return 0;
		}
		if (SelectVar == "#$CalciumReleaseTime$") {
			WriteNewMRA(PubVar, "MRALIST", WriteVar);
			writeini(PubVar, "VarST", WriteVar, ComVer);
			return 0;
		}

		WriteNewMRA(PubVar, "MRALIST", WriteVar);
		writeini(PubVar, "VarST", WriteVar, "Null");
		return 0;
	}
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
	if (checkChar(CaCMDS, "$$var.edit") == 1) {

		string p1 = CleanAuto(ResCMD, "$$var.edit(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string varname = cutlineblock(out, 1);
		string varinfo = cutlineblock(out, 2);

		WriteNewMRA(PubVar, "MRALIST", varname);
		writeini(PubVar, "VarST", varname, varinfo);

		return 0;
	}
	if (checkChar(CaCMDS, "$$var.del") == 1) {

		string p1 = CleanAuto(ResCMD, "$$var.del(\"");
		string out = CleanAuto(p1, "\");");

		writeini(PubVar, "VarST", out, "NULL");
		cout << "Delete Var :  " << out << endl;

		return 0;
	}

	if (checkChar(CaCMDS, "$$GetCin") == 1) {

		string p1 = CleanAuto(CaCMDS, "$$GetCin(\"");
		string p2 = CleanAuto(p1, "\");");
		string out = Replace(p2, "\",\"", " ");

		string svar = cutlineblock(out, 1);
		string outinfo = cutlineblock(out, 2);

		string varinfo;
		cout << outinfo;
		getline(cin, varinfo);

		WriteNewMRA(PubVar, "MRALIST", svar);
		writeini(PubVar, "VarST", svar, varinfo);

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