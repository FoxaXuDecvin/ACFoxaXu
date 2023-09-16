//Calcium Language
#include "ADSF.h"
//定义ACF的版本信息

string PATH = getselfpath();
string COREFILE = getselfinfo();

int vercode = 1003;

string VCNum = to_string(vercode);
string ConfigINI = PATH + "\\config.ini";
string TempCAPT = getwinenvfast("temp") + "\\CalciumPackage\\" + to_string(SpawnRandomNum(11111111, 99999999));
string PubVar = RunPath + "\\vartemp~" + to_string(SpawnRandomNum(1111, 9999)) + ".ini";

int main(int argc, char*argv[]) {
	if (argc == 1) {
		string cmd = "\"\"" + COREFILE + "\" -capt \"" + PATH + readini(PATH + "\\config.ini", "default", "nopara")+"\"\"";
		cout << "Load :  " << cmd << endl;
		system(cmd.c_str());
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
				system("assoc .ca=CalciumScript");
				system("assoc .cascript=CalciumScript");
				system("assoc .capt=CalciumPackage");
				cout << "Complete" << endl;
				system("pause");
				return 0;
			}
			ShellExecute(0, "runas", COREFILE.c_str(), "reg", 0, SW_SHOW);
			return 0;
		}
		if (ParaFile == "unreg") {
			if (bool r = testAdmin("C:")) {
				WinExec("reg delete HKEY_CLASSES_ROOT\\CalciumScript /f", SW_SHOW);
				WinExec("reg delete HKEY_CLASSES_ROOT\\CalciumPackage /f", SW_SHOW);
				cout << "Complete" << endl;
				system("pause");
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
			if(_access(ParaPack.c_str(),0)) {
				cout << "Cannot Load Calcium Package:  " << ParaPack << endl;
				cout << "Check your type and try again" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}

			if (_access(ConfigINI.c_str(), 0)) {
				cout << "Config File is missing" << endl;
				cout << "Please Try to reinstall Calcium" << endl;
				cpause("Press any key to Exit");
				return 0;
			}

			//解压7z
			rmfolder(TempCAPT);
			RMTCAP:
			if (existfolder(TempCAPT)) {
				Sleep(100);
				goto RMTCAP;
			}
			else {
				mdfolder(TempCAPT);
			}
			Sleep(100);
			n7zUNZIP(PATH + readini(ConfigINI, "7z", "n7zcore"), ParaPack, TempCAPT, "0");
			Sleep(200);
			string CaptINI = TempCAPT + "\\capt.ini";
			if (_access(CaptINI.c_str(), 0)) {
				cout << "Cannot Load Calcium Package:  " << ParaPack << endl;
				cout << "This Package is Null" << endl;
				cpause("Press any key to Close");
				cout << endl;
				rmfolder(TempCAPT);
				return 0;
			}

			SetCurrentDirectory(TempCAPT.c_str());
		
			if (_access(readini(CaptINI, "pubvar", "default").c_str(), 0)) {
				cout << "Cannot Load Calcium Package:  " << ParaPack << endl;
				cout << "Package Default Failed Loader :  " << readini(CaptINI, "pubvar", "default") << endl;
				cpause("Press any key to Close");
				cout << endl;
				rmfolder(TempCAPT);
				return 0;
			}

			int errlevel = ScriptRun(readini(CaptINI, "pubvar", "default"), vercode,2,CaptINI);
			if (errlevel == 1) {
				cout << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "File Exit Error :  " << readini(CaptINI, "pubvar", "default") << endl;
				cout << "Check Log to find problem" << endl;
				cpause("Press any key to Close");
				cout << endl;
			}

			cout << endl;
			SetCurrentDirectory(PATH.c_str());
			Sleep(300);
			rmfolder(TempCAPT);
			return 0;
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
			if (_access(ParaPack.c_str(), 0)) {
				cout << "Cannot Load Calcium Package:  " << ParaPack << endl;
				cout << "Check your type and try again" << endl;
				cpause("Press any key to Close");
				cout << endl;
				return 0;
			}

			if (_access(ConfigINI.c_str(), 0)) {
				cout << "Config File is missing" << endl;
				cout << "Please Try to reinstall Calcium" << endl;
				cpause("Press any key to Exit");
				return 0;
			}

			//解压7z
			rmfolder(TempCAPT);
		RMTCAP2:
			if (existfolder(TempCAPT)) {
				Sleep(100);
				goto RMTCAP2;
			}
			else {
				mdfolder(TempCAPT);
			}
			Sleep(100);
			n7zUNZIP(PATH + readini(ConfigINI, "7z", "n7zcore"), ParaPack, TempCAPT, "0");
			Sleep(200);
			string CaptINI = TempCAPT + "\\capt.ini";
			if (_access(CaptINI.c_str(), 0)) {
				cout << "Cannot Load Calcium Package:  " << ParaPack << endl;
				cout << "This Package is Null" << endl;
				cpause("Press any key to Close");
				cout << endl;
				rmfolder(TempCAPT);
				return 0;
			}

			SetCurrentDirectory(TempCAPT.c_str());

			if (_access(ParaLoadSign.c_str(), 0)) {
				cout << "Cannot Load Calcium Package:  " << ParaPack << endl;
				cout << "Package Default Failed Loader :  " << ParaLoadSign.c_str() << endl;
				cpause("Press any key to Close");
				cout << endl;
				rmfolder(TempCAPT);
				return 0;
			}

			int errlevel = ScriptRun(ParaLoadSign, vercode,2,CaptINI);
			if (errlevel == 1) {
				cout << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "File Exit Error :  " << readini(CaptINI, "pubvar", "default") << endl;
				cout << "Check Log to find problem" << endl;
				cpause("Press any key to Close");
				cout << endl;
			}

			cout << endl;
			SetCurrentDirectory(PATH.c_str());
			rmfolder(TempCAPT);
			return 0;
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