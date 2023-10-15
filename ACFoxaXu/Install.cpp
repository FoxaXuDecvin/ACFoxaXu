#include "ADSF.h"
using namespace std;

string preroot = getwinenvfast("ProgramFiles") + "\\FoxaXu";
string ProgramRoot = getwinenvfast("ProgramFiles") + "\\FoxaXu\\Calcium";
string PRFile = ProgramRoot + "\\Calcium.exe";
string PRUpd = ProgramRoot + "\\CaUpdater.exe";
string PRInfo = ProgramRoot + "\\DefaultICON.ico";
string GetSelfD = getselfinfo();


string uninstallBLOCK() {
	//Uninstall
	
	Sleep(1000);
	remove(linkfile.c_str());
		if (_access(PGINSDATA.c_str(), 0)) {
			cout << "Install Data is missing, " << endl;
		}
		string current = readini(PGINSDATA, "Install", "Path");

		cout << "Uninstalling Calcium" << endl;

		if (current == "readini-failed") {
			cout << "Failed to Get Install Information" << endl;

			rmfolder(PGDataf);
		}
		else {
			string CURFile = current + "\\Calcium.exe";
			if (_access(CURFile.c_str(), 0)) {
				cout << "Failed to Find File on :  " << current << endl;

				rmfolder(current);
				rmfolder(PGDataf);
			}
			else {
				ShellExecute(0, "runas", CURFile.c_str(), "-unreg", 0, SW_SHOW);
				Sleep(2000);
				string tempWork = getenv("temp");
				SetCurrentDirectory(tempWork.c_str());
				ReDelete:
				rmfolder(current);
				Sleep(1000);
				if (existfolder(current)) {
					cout << endl;
					cout << "Close Calcium Process and try again" << endl;
					Sleep(1000);
					goto ReDelete;
				}
				rmfolder(PGDataf);
			}
		}

		cout << "Program is Complete" << endl;
		return "OK";
}

string installAutoBlock(string ProgramRoot) {
	PRFile = ProgramRoot + "\\Calcium.exe";
	PRUpd = ProgramRoot + "\\CaUpdater.exe";

	cout << "Starting install Calcium" << endl;

	mdfolder(ProgramRoot);
	mdfolder(PGINSDATA);

	string worktemp = getwinenv("temp");

	string TempF;

	if (_access(".\\LocalInstall", 0)) {
		//Download Package
		TempF = worktemp + "\\CalciumSetup";
		mdfolder(TempF);

		cout << "Download Package" << endl;
		URLDown("https://gitcode.net/FoxaXu1/fxtoolcds/-/raw/master/Install.zip", TempF + "\\ins.zip");
		URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.dll", TempF + "\\7z.dll");
		URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.exe", TempF + "\\7z.exe");

		Sleep(1000);
	}
	else {
		TempF = getselfpath();
	}
	Sleep(2000);

	cout << "Setting Program FIle" << endl;
	mdfolder(preroot);

	mdfolder(ProgramRoot);
	cout << ProgramRoot << endl;
	clearfolder(ProgramRoot);

	n7zUNZIP(TempF + "\\7z.exe", TempF + "\\ins.zip", ProgramRoot, "0");

	cout << "Register" << endl;
	Sleep(1000);
	if (_access(PRFile.c_str(), 0)) {
		cout << "Failed to Download Calcium" << endl;
		cout << "Please try to reinstall" << endl;
		cpause("Press any key to cancel");
		return "NULL";
	}
	ShellExecute(0, "runas", PRFile.c_str(), "-reg", 0, SW_SHOW);

	mdfolder(PGDataf);
	writeini(PGINSDATA, "Install", "Path", ProgramRoot);

	string newuninst = preroot + "\\Setup~Calcium.exe";

	CopyFile(GetSelfD.c_str(), newuninst.c_str(), 0);
	cout << "Install Complete" << endl;
	rmfolder(TempF);
	return "OK";
}

int main(int argc,char* argv[]) {
	if (bool a = testAdmin("C:")) {}
	else {
		if (argc == 2) {
			int alang = 0;
			alang++;
			string paranew = argv[alang];
			ShellExecute(0, "runas", getselfinfo().c_str(), paranew.c_str(), 0, SW_SHOW);
			return 0;
		}
		ShellExecute(0, "runas", getselfinfo().c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	SetConsoleTitle("Calcium Install Tools");

	//cout << "ARGC :  " << to_string(argc) << endl;

	if (argc == 2) {
		int alang = 0;
		alang++;
		string paranew = argv[alang];
		cout << "Parameter :  " << paranew << endl;

		if (paranew == "--uninst-auto") {
			cout << "Auto Uninstall. No Dialogs" << endl;
			system("cls");
			uninstallBLOCK();
			return 0;
		}

		if (paranew == "--install") {
			cout << "Auto install Calcium. No Dialogs" << endl;
			installAutoBlock(ProgramRoot);
			cout << "Process End" << endl;
			return 0;
		}

		if (paranew == "--reinstall") {
			cout << "Auto Update/Repair Calcium. No Dialogs" << endl;
			ProgramRoot = readini(PGINSDATA, "Install", "Path");
			uninstallBLOCK();
			cout << "Uninstall Complete" << endl;
			Sleep(1000);
			installAutoBlock(ProgramRoot);
			cout << "Process End" << endl;
			return 0;
		}

		installAutoBlock(paranew);
		cpause("Press any key to Exit...");
		return 0;
	}

		//Uninstall
		if (existfolder(PGDataf)) {
			string current = readini(PGINSDATA, "Install", "Path");
			LANGID CURRPC = GetUserDefaultUILanguage();
			switch (CURRPC)
			{
			case 0x0804:
				cout << "Calcium 已经安装在了 :  " << current << endl;
				cout << "你想卸载 Calcium 吗?" << endl;
				cpause("按任意键确认3次...(3)");
				cpause("...(2)");
				cpause("...(1)");
				system("cls");
				uninstallBLOCK();
				cpause("Press any key to Exit.... ");
				return 0;
				break;
			}
			cout << "Calcium is Already install on :  " << current << endl;
			cout << "Do you want Uninstall Calcium?" << endl;
			cpause("Make sure...(3)");
			cpause("Make sure...(2)");
			cpause("Make sure...(1)");
			system("cls");
			uninstallBLOCK();
			cpause("Press any key to Exit.... ");
			return 0;
		}

		LANGID CURRPC = GetUserDefaultUILanguage();
		switch (CURRPC)
		{
		case 0x0804:
			cout << "欢迎安装Calcium，你想要安装这个程序吗?" << endl;
			cout << "此程序会执行自动安装" << endl;

			cout << "自动安装指令 :  " << endl;
			cout << "        CaSetup.exe --install            自动安装Calcium，无需确认" << endl;
			cout << "        CaSetup.exe --uninst-auto   自动卸载Calcium，无需确认" << endl;
			cout << "        CaSetup.exe --reinstall         自动更新，修复Calcium,无需确认" << endl;
			cout << "程序默认将会安装在 %ProgramFile%\\FoxaXu\\Calcium" << endl;
			cout << "如果你想安装在其他地方，请使用 CaSetup.exe <path>" << endl;
			cout << "如果你想创建个离线安装包 .\\LocalInstall 标记文件在CaSetup的根目录" << endl;
			cout << "Copyright FoxaXu" << endl;

			cout << endl;

			cpause("如果确认安装，请按任意键3次 ...(3)");
			cpause(" ...(2)");
			cpause(" ...(1)");
			installAutoBlock(ProgramRoot);
			cpause("Press any key to Exit...");
			return 0;
			break;
		}
		cout << "Welcome to Install Calcium. Do you want Start?" << endl;
		cout << "The Program will auto install Calcium" << endl;

		cout << "Auto Install Command :  " << endl;
		cout << "        CaSetup.exe --install            Auto Install Calcium No Dialogs" << endl;
		cout << "        CaSetup.exe --uninst-auto   Auto UnInstall Calcium No Dialogs" << endl;
		cout << "        CaSetup.exe --reinstall         Auto Update/Repair Calcium. No Dialogs" << endl;
		cout << "The Program will Install in %ProgramFile%\\FoxaXu\\Calcium" << endl;
		cout << "If you want install other place, Please use CaSetup.exe <path>" << endl;
		cout << "If you are developer, you can use Add .\\LocalInstall MarkFile on Root Path" << endl;
		cout << "Copyright FoxaXu" << endl;

		cout << endl;

		cpause("If you want install, Please Press any key ...(3)");
		cpause("If you want install, Please Press any key ...(2)");
		cpause("If you want install, Please Press any key ...(1)");
		installAutoBlock(ProgramRoot);
		cpause("Press any key to Exit...");
		return 0;
		// Not Install
}