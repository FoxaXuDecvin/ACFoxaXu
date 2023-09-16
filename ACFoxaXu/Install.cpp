#include "ADSF.h"
using namespace std;

int main() {
	if (bool a = testAdmin("C:")){}
	else {
		ShellExecute(0, "runas", getselfinfo().c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	SetConsoleTitle("AutoInstall Calcium");
	cout << "Welcome to use Calcium" << endl;
	cout << "Do you want install Calcium ? " << endl;
	cout << "Press any key to Start Install" << endl;

	cpause("Make sure 3");
	cout << endl;
	cpause("Make sure 2");
	cout << endl;
	cpause("Make sure 1");
	cout << endl;
	clscmd;

	cout << "Start Install Calcium" << endl;
	cout << "Please wait" << endl;

	string worktemp = getwinenv("temp");

	string TempF = worktemp + "\\ACFoxaxu";
	clearfolder(TempF);
	Sleep(2000);

	cout << "Download Package" << endl;
	URLDown("https://gitcode.net/FoxaXu1/fxtoolcds/-/raw/master/Install.zip", TempF + "\\ins.zip");
	URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.dll", TempF + "\\7z.dll");
	URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.exe", TempF + "\\7z.exe");

	Sleep(3000);

	cout << "Setting Program FIle" << endl;
	string preroot = getwinenv("ProgramFiles") + "\\FoxaXu";
	mdfolder(preroot);

	string ProgramRoot = getwinenv("ProgramFiles") + "\\FoxaXu\\AScript";
	mdfolder(ProgramRoot);
	cout << ProgramRoot << endl;
	clearfolder(ProgramRoot);
	
	n7zUNZIP(TempF + "\\7z.exe", TempF + "\\ins.zip", ProgramRoot, "0");
	
	cout << "Register" << endl;
	string PRFile = ProgramRoot + "\\acfoxaxu.exe";
	Sleep(4000);
	if (_access(PRFile.c_str(), 0)) {
		cout << "Failed to Download AScript" << endl;
		cout << "Please try to reinstall" << endl;
		cpause("Press any key to cancel");
		return 0;
	}
	ShellExecute(0, "open", PRFile.c_str(), "reg", 0, SW_SHOW);
	cout << "Install Complete" << endl;
	cpause("Press any key to Exit");
	return 0;
}