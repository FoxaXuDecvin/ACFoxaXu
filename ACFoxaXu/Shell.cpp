//Calcium Shell Debug Tools

#include"ADSF.h"

string UserProfileENV = getenv("userprofile");
string RunPathSe = UserProfileENV + "\\Desktop";

int main() {
	SetCurrentDirectory(RunPathSe.c_str());
RELOAD:
	system("cls");
	if (InsidePreview == 1) {
		cout << "-------------------------------------------------------------------" << endl;
		lntype("lang.public.unrelease");
		cout << "-------------------------------------------------------------------" << endl;
	}
	if (readini(settings, "Settings", "PullTitle") == "open") {
		cout << "----------------------------------------------------------------------" << endl;
		pulltitle();
	}
	cout << "----------------------------------------------------------------------" << endl;
	lntype("lang.shell.welcome");
	cout << Outlang("lang.shell.ver") << " :  " << Version << "~" << vercode << endl;
	cout << Outlang("lang.shell.reltime") << " :  " << ComVer << endl;
	cout << "Run Path :  " << RunPathSe << endl;
	cout << "Copyright FoxaXu 2023" << endl;
	lntype("lang.shell.usehelp");
	lntype("lang.shell.endcmd");
	string ShellCMD;

backshell:
	cout << endl;
	cout << "Calcium Shell Console   $ ";
	getline(cin, ShellCMD);

	if (checkChar(ShellCMD, "$goto") == 1) {
		cout << "Shell Mode not support $goto :  " << ShellCMD << endl;
		goto backshell;
	}
	if (checkChar(ShellCMD, "#Include") == 1) {
		cout << "Shell Mode not support #Include :  " << ShellCMD << endl;
		goto backshell;
	}

	//API
	if (checkChar(ShellCMD, "$capt ") == 1) {
		string Out = CleanAuto(ShellCMD, "$capt ");
		string para = "-capt " + Out;
		ShellExecute(0, "open", CaMain.c_str(), para.c_str(), 0, SW_SHOW);
		goto backshell;
	}
	if (checkChar(ShellCMD, "$loadroot") == 1) {
		cout << "Loading " << endl;
		CaRootLoaderX();
		cout << "Load OK" << endl;
		goto backshell;
	}
	if (checkChar(ShellCMD, "$casp ") == 1) {
		string Out = CleanAuto(ShellCMD, "$casp ");
		string para = "-casp " + Out;
		ShellExecute(0, "open", CaMain.c_str(), para.c_str(), 0, SW_SHOW);
		goto backshell;
	}
	if (checkChar(ShellCMD, "$uninstall") == 1) {
		string PGDataf = getwinenvfast("ProgramData") + "\\CalciumScript";
		string PGINSDATA = PGDataf + "\\CaInfo.txt";
		if (_access(PGINSDATA.c_str(), 0)) {
			cout << "Error :  " << PGINSDATA << endl;
			goto backshell;
		}

		string current = readini(PGINSDATA, "Install", "Path");
		current = CleanAuto(current, "\\Calcium");
		string mainprocess = current + "\\Manager~Calcium.exe";
		if (_access(mainprocess.c_str(), 0)) {
			cout << "Error :  " << mainprocess << endl;
			goto backshell;
		}
		ShellExecute(0, "runas", mainprocess.c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	if (checkChar(ShellCMD, "$update") == 1){
		string paraNew = "\"" + getselfpath() + "\"";
		ShellExecute(0, "runas", CaUpdMain.c_str(),paraNew.c_str(), 0, SW_SHOW);
		goto backshell;
	}
	if (checkChar(ShellCMD, "$reload") == 1) {
		goto RELOAD;
	}
	if (checkChar(ShellCMD, "$edit.varspace") == 1) {
		cout << "Type New VarSpace" << endl;
		getline(cin, VarSpace);
		
		cout << endl;
		string vsmd;
		cout << "VarSpaceMax >  ";
		getline(cin, vsmd);
		VarSpaceMax = atoi(vsmd.c_str());

		goto backshell;
	}

	string atranscmd = TransVar(ShellCMD);
	int cmrd = RollCMD(atranscmd, ShellCMD, ",\\unknown.txt", 1,vercode);
	if (cmrd == -2) {
		// version Not Allow
		cpause("press any key to Exit");
		goto backshell;
	}
	if (cmrd == -1) {
		//Return Exit
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