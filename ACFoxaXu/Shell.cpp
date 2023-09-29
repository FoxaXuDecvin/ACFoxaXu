//Calcium Shell Debug Tools

#include"ADSF.h"

string PubVar = getwinenvfast("temp") + "\\ShellVar.ini";

int main() {
	if (_access(PubVar.c_str(),0)){}
	else {
		remove(PubVar.c_str());
	}

	SetConsoleTitle("Calcium Shell");
	system("cls");
	if (InsidePreview == 1) {
		cout << "Warning :  This version is Insider Preview, Do not Share this software" << endl;
		cout << "You Need Keep Privacy Rule," << endl;
		cout << "This Version is Not Release" << endl;
		cout << "-------------------------------------------------------------------" << endl;
	}
	cout << "Welcome to use Calcium." << endl;
	cout << "Version :  " << Version << "~" << vercode << endl;
	cout << "This Version Release Time :  " << ComVer << endl;
	cout << "Copyright FoxaXu 2023" << endl;
	cout << "Use Command to Debug or run command" << endl;
	cout << "Use #end to Close Shell" << endl;
	string ShellCMD;

backshell:
	cout << endl;
	cout << "Calcium Shell Console   $ ";
	getline(cin, ShellCMD);

	if (checkChar(ShellCMD, "#load") == 1) {
		cout << "Shell Mode not support #load :  " << ShellCMD << endl;
		goto backshell;
	}
	if (checkChar(ShellCMD, "#Include") == 1) {
		cout << "Shell Mode not support #Include :  " << ShellCMD << endl;
		goto backshell;
	}

	string atranscmd = TransVar(ShellCMD);
	int cmrd = CaCmdRun(atranscmd, ShellCMD, ",\\unknown.txt", 1, vercode, PubVar);
	if (cmrd == -2) {
		// version Not Allow
		cpause("press any key to Exit");
		remove(PubVar.c_str());
		goto backshell;
	}
	if (cmrd == -1) {
		//Return Exit
		remove(PubVar.c_str());
		return 0;
	}
	if (cmrd == 1) {
		cout << "Unknown Command :  " << atranscmd << endl;
		goto backshell;
	}
	if (cmrd == 2) {
		cout << endl;
		cout << "Script is Crash." << endl;
		cout << "This Problem is happend by Script" << endl;
		cout << endl;
		goto backshell;
	}
	if (cmrd > 2) {
		cout << "[Notice] Shell Mode not support skip line" << endl;
		goto backshell;
	}

	goto backshell;
}