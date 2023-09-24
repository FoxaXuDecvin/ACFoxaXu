//Calcium Language
#include "ADSF.h"
#include"D:\CppHeader\winapicore.h"
//定义ACF的版本信息

string PATH = getselfpath();
string COREFILE = getselfinfo();

string VCNum = to_string(vercode);
string ConfigINI = PATH + "\\config.ini";
string TempCAPT = getwinenvfast("temp") + "\\CalciumPackage\\" + to_string(SpawnRandomNum(11111111, 99999999));
string PubVar = RunPath + "\\vartemp~" + to_string(SpawnRandomNum(1111, 9999)) + ".ini";

//成功返回 1，失败返回 0
int packloader(string packfile,string carun,string TCAPT) {
	//start
	if (_access(packfile.c_str(), 0)) {
		cout << "Package File is Not Exist" << endl;
		return 0;
	}
	// Ready
	//解压7z
	mdfolder(TCAPT);

	n7zUNZIP(PATH + readini(ConfigINI, "7z", "n7zcore"), packfile, TCAPT, "0");

	string CaptINI = TCAPT + "\\capt.ini";
	if (_access(CaptINI.c_str(), 0)) {
		cout << "Capt INI Null" << endl;
		return 0;
	}

	SetCurrentDirectory(TCAPT.c_str());

	if (carun == "#default") {
		// SAT
		if (_access(readini(CaptINI, "pubvar", "default").c_str(), 0)) {
			cout << "Default CAScript Null" << endl;
			return 0;
		}

		int errlevel = ScriptRun(readini(CaptINI, "pubvar", "default").c_str(), vercode, 2, CaptINI);
		if (errlevel == 1) {
			cout << "Script Exception" << endl;
			return 0;
		}
		cout << endl;
		SetCurrentDirectory(PATH.c_str());

		return 1;
		// END
	}

	if (_access(carun.c_str(), 0)) {
		cout << "Failed to Load :  " << carun << endl;
		return 0;
	}

	int errlevel = ScriptRun(carun, vercode, 2, CaptINI);
	if (errlevel == 1) {
		cout << "Script Exception" << endl;
		return 0;
	}

	cout << endl;
	SetCurrentDirectory(PATH.c_str());

	return 1;
}

int main(int argc, char*argv[]) {
	if (argc == 1) {
		string cmd = "\"\"" + COREFILE + "\" -capt \"" + PATH + readini(PATH + "\\config.ini", "default", "nopara")+"\"\"";
		cout << "Load :  " << cmd << endl;
		system(cmd.c_str());
		string pa = getselfpath() + "\\CaShell.exe";
		ShellExecute(0, "open", pa.c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	// P <1> <2>
	if (argc == 2) {

		int al = 0;
		al++;
		string ParaFile = argv[al];
		if (ParaFile == "reg") {
			if (bool r = testAdmin("C:")) {
				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumPackage /ve /t REG_SZ /d \"Calcium Package Program\" /f", SW_SHOW);
				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell /ve /t REG_SZ /d  \"Calcium Run Script \" /f", SW_SHOW);
				string cmds = "reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell\\open\\command /ve /t REG_SZ /f /d \"\\\"" + getselfinfo() + "\\\" -capt \\\"%1\\\"\"";
				WinExec(cmds.c_str(), SW_SHOW);

				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell\\runas /f", SW_SHOW);
				cmds = "reg add HKEY_CLASSES_ROOT\\CalciumPackage\\shell\\runas\\command /ve /t REG_SZ /f /d \"\\\"" + getselfinfo() + "\\\" -capt \\\"%1\\\" \"";
				WinExec(cmds.c_str(), SW_SHOW);

				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumScript /ve /t REG_SZ /d \"Calcium Run Script\" /f", SW_SHOW);
				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell /ve /t REG_SZ /d  \"Calcium Run Script \" /f", SW_SHOW);

				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\open /f", SW_SHOW);
				cmds = "reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\open\\command /ve /t REG_SZ /f /d \"\\\"" + getselfinfo() + "\\\" \\\"%1\\\"\"";
				WinExec(cmds.c_str(), SW_SHOW);
				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\runas /f", SW_SHOW);
				cmds = "reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\runas\\command /ve /t REG_SZ /f /d \"\\\"" + getselfinfo() + "\\\" \\\"%1\\\" \"";
				WinExec(cmds.c_str(), SW_SHOW);
				WinExec("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\edit /f", SW_SHOW);
				cmds = "reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\edit\\command /ve /t REG_SZ /f /d \"\\\"notepad\\\" \\\"%1\\\" \"";
				WinExec(cmds.c_str(), SW_SHOW);

				cmds = "reg add HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v \"Calcium Auto Update\" /t REG_SZ /d \"" + getselfpath() + "\\CaUpdater.exe\"";
				//cout << "_" << cmds << "_" << endl;
				WinExec(cmds.c_str(), SW_SHOW);

				//添加PATH
				SetCurrentDirectory(getselfpath().c_str());
				string cacore = getwinenvfast("SystemRoot") + "\\cac.exe";
				if (_access(".\\Cac.exe", 0)) {
					Sleep(3000);
					if (_access(".\\Cac.exe", 0)) {
						MessageBox(0, "Error, Cac Fast Invoke is Missing on Install", "Auto Install calcium", MB_ICONERROR | MB_OK);
					}
				}
				CopyFile(".\\Cac.exe", cacore.c_str(), 0);

				system("assoc .ca=CalciumScript");
				system("assoc .cascript=CalciumScript");
				system("assoc .capt=CalciumPackage");
				cout << "Complete" << endl;
				return 0;
			}
			ShellExecute(0, "runas", COREFILE.c_str(), "reg", 0, SW_SHOW);
			return 0;
		}
		if (ParaFile == "unreg") {
			if (bool r = testAdmin("C:")) {
				cout << "Delete Register" << endl;
				WinExec("reg delete HKEY_CLASSES_ROOT\\CalciumScript /f", SW_SHOW);
				WinExec("reg delete HKEY_CLASSES_ROOT\\CalciumPackage /f", SW_SHOW);
				WinExec("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v \"Calcium Auto Update\" /f", SW_SHOW);
				
				//删除PATH
				string cacore = getwinenvfast("SystemRoot") + "\\cac.exe";
				remove(cacore.c_str());

				cout << "Complete" << endl;
				return 0;
			}
			ShellExecute(0, "runas", COREFILE.c_str(), "unreg", 0, SW_SHOW);
			return 0;
		}
		if (_access(ParaFile.c_str(), 0)) {
			cout << "Unable to load from :  " << ParaFile << endl;
			cout << "Check your type and try again" << endl;
			cpause("Press any key to Close");
			cout << endl;
			return 0;
		}

		//验证文件头
		string Head = LineReader(ParaFile, 1);
		if (Head=="#Calc") {}
		else {
			cout << "Unable to load from :  " << ParaFile << endl;
			cout << "File Head is NULL. add #Calc in head" << endl;
			cpause("Press any key to Close");
			cout << endl;
			return 0;
		}

		//加载脚本
		int errlevel = ScriptRun(ParaFile,vercode,2,PubVar);
		if (errlevel == 1) {
			cout << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "File Exit Error :  " << ParaFile << endl;
			cout << "Check Log to find problem" << endl;
			cpause("Press any key to Close");
			cout << endl;
			return 0;
		}
		
		return 0;
	}
	if (argc == 3) {
		int al = 0;
		al++;
		string ParaChar = argv[al];
		al++;
		string ParaPack = argv[al];
		if (ParaChar == "-capt") {
			int packrt = packloader(ParaPack, "#default", TempCAPT);
			if (packrt == 1) {
				// OK
				return 0;
			}
			else {
				cout << "-------------------------------------------------------------------" << endl;
				cout << "Error Report..." << endl;
				cout << "Press any key to Exit" << endl;
				cpause("maybe its not a big problem");
				return 0;
			}
		}
		if (ParaChar == "-casp") {
			if (_access(ParaPack.c_str(), 0)) {
				cout << "Unable to load from :  " << ParaPack << endl;
				cout << "Check your type and try again" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}

			//验证文件头
			string Head = LineReader(ParaPack, 1);
			if (Head == "#Calc") {}
			else {
				cout << "Unable to load from :  " << ParaPack << endl;
				cout << "File Head is NULL. add #Calc in head" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}

			//加载脚本
			int errlevel = ScriptRun(ParaPack, vercode,2,PubVar);
			if (errlevel == 1) {
				cout << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "File Exit Error :  " << ParaPack << endl;
				cout << "Check Log to find problem" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}

			return 0;
		}
	}
	// LoadSign
	if (argc == 4) {
		int al = 0;
		al++;
		string ParaChar = argv[al];
		al++;
		string ParaPack = argv[al];
		al++;
		string ParaLoadSign = argv[al];

		if (ParaChar == "-capt") {
			int packrt = packloader(ParaPack, ParaLoadSign, TempCAPT);
			if (packrt == 1) {
				// OK
				return 0;
			}
			else {
				cout << "-------------------------------------------------------------------" << endl;
				cout << "Error Report..." << endl;
				cout << "Press any key to Exit" << endl;
				cpause("maybe its not a big problem");
				return 0;
			}
		}
		if (ParaChar == "-casp") {
			if (_access(ParaPack.c_str(), 0)) {
				cout << "Unable to load from :  " << ParaPack << endl;
				cout << "Check your type and try again" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}

			//查找目标
			string EPoint = "Find~Header";
			WriteIntGlobal(EPoint, 2);

		ABackRoll:
			//获取函数
			int CURRLINE = GetIntGlobal(EPoint);
			string cl_str = to_string(CURRLINE);

			//cout << cl_str << endl;

			string GetLineData = LineReader(ParaPack, CURRLINE);

			if (GetLineData == "overline") {
				cout << endl;
				cout << "Unable to load from :  " << ParaPack << endl;
				cout << "Head :  _" << ParaLoadSign << "_, load failed, not exist" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}
			if (GetLineData == ParaLoadSign) {
				int errlevel = ScriptRun(ParaPack, vercode, CURRLINE, PubVar);
				if (errlevel == 1) {
					cout << endl;
					cout << "-------------------------------------------------------------------------------" << endl;
					cout << "File Exit Error :  " << ParaPack << endl;
					cout << "Check Log to find problem" << endl;
					cpause("Press any key to Close");
					cout << endl;
					return 0;
				}

				return 0;
			}
			CURRLINE++;
			WriteIntGlobal(EPoint, CURRLINE);
			goto ABackRoll;

			return 0;
 		}
	}
}