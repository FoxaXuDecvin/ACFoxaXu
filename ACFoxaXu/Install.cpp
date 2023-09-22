#include "ADSF.h"
using namespace std;

string preroot = getwinenvfast("ProgramFiles") + "\\FoxaXu";
string ProgramRoot = getwinenvfast("ProgramFiles") + "\\FoxaXu\\Calcium";
string PRFile = ProgramRoot + "\\Calcium.exe";
string PGDataf = getwinenvfast("ProgramData") + "\\CalciumScript";
string PGINSDATA = PGDataf + "\\CaInfo.txt";

string GetSelfD = getselfinfo();

string uninstallBLOCK() {
	//Uninstall
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
				ShellExecute(0, "runas", CURFile.c_str(), "unreg", 0, SW_SHOW);
				Sleep(2000);
				rmfolder(current);
				rmfolder(PGDataf);
			}
		}

		cout << "Program is Complete" << endl;
		return "OK";
}

string installAutoBlock() {
	cout << "Starting install Calcium" << endl;

	mdfolder(ProgramRoot);
	mdfolder(PGINSDATA);

	string worktemp = getwinenv("temp");

	string TempF = worktemp + "\\CalciumSetup";
	mdfolder(TempF);
	Sleep(2000);

	cout << "Download Package" << endl;
	URLDown("https://gitcode.net/FoxaXu1/fxtoolcds/-/raw/master/Install.zip", TempF + "\\ins.zip");
	URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.dll", TempF + "\\7z.dll");
	URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.exe", TempF + "\\7z.exe");

	Sleep(1000);

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
	ShellExecute(0, "open", PRFile.c_str(), "reg", 0, SW_SHOW);
	mdfolder(PGDataf);
	writeini(PGINSDATA, "Install", "Path", ProgramRoot);

	string newuninst = preroot + "\\Manager~Calcium.exe";

	CopyFile(GetSelfD.c_str(), newuninst.c_str(), 0);

	cout << "Install Complete" << endl;
	rmfolder(TempF);
	return "OK";
}

int main(int argc,char* argv[]) {
	if (bool a = testAdmin("C:")) {}
	else {
		ShellExecute(0, "runas", getselfinfo().c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	SetConsoleTitle("AutoInstall Calcium");

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
			installAutoBlock();
			cout << "Process End" << endl;
			return 0;
		}

		if (paranew == "--reinstall") {
			cout << "Auto Update/Repair Calcium. No Dialogs" << endl;
			uninstallBLOCK();
			cout << "Uninstall Complete" << endl;
			Sleep(1000);
			installAutoBlock();
			cout << "Process End" << endl;
			return 0;
		}

		cout << "Unknown Parameter :  " << paranew << endl;
		cout << "Please Try other later" << endl;
		cpause("Press any key to Exit ...");
		return 0;
	}

		//Uninstall
		if (existfolder(PGDataf)) {
			string current = readini(PGINSDATA, "Install", "Path");
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

		// Not Install
		cout << "Welcome to Install Calcium. Do you want Start?" << endl;
		cout << "The Program will auto install Calcium" << endl;

		cout << "Auto Install Command :  " << endl;
		cout << "        CaSetup.exe --install            Auto Install Calcium No Dialogs" << endl;
		cout << "        CaSetup.exe --uninst-auto   Auto UnInstall Calcium No Dialogs" << endl;
		cout << "        CaSetup.exe --reinstall         Auto Update/Repair Calcium. No Dialogs" << endl;
		cout << "Copyright FoxaXu" << endl;

		cout << endl;

		cpause("make sure ...(3)");
		cpause("make sure ...(2)");
		cpause("make sure ...(1)");
		installAutoBlock();
		cpause("Press any key to Exit...");
		return 0;

}