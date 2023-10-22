//Calcium Language
#include "ADSF.h"
#include"resource.h"
#include"D:\CppHeader\winapicore.h"
//定义ACF的版本信息

string PATH = getselfpath();

string VCNum = to_string(vercode);
string ConfigINI = PATH + "\\config.ini";
string TempCaPKG = getwinenvfast("temp") + "\\CalciumPackage";
string TempCAPT = getwinenvfast("temp") + "\\CalciumPackage\\" + to_string(SpawnRandomNum(11111111,99999999));

//LaunchData
string LoadFile = "NUL";
int LoadMode;//1=CASP.2=CAPT
string parametersA = "";

//0 Error, 1 Normal
int packloader(string packfile, string carun, string TCAPT) {
	ResLoadFile = packfile;
	string NRootLock = TCAPT + "\\session.lock";
	string Nsafemark = TCAPT + "\\unsafe.lock";
	//start
	if (_access(packfile.c_str(), 0)) {
		lntype("lang.calcium.packageNULL");
		return 1;
	}
	// Ready
	//解压7z
	mdfolder(TCAPT);

	n7zUNZIP(PATH + readini(ConfigINI, "7z", "n7zcore"), packfile, TCAPT, "0");

	string CaptINI = TCAPT + "\\capt.ini";
	if (_access(CaptINI.c_str(), 0)) {
		lntype("lang.calcium.packageINIfailed");
		return 1;
	}

	SetCurrentDirectory(TCAPT.c_str());

	cout << endl;
	cout << "Package Loading :  " << packfile << endl;
	cout << endl;

	if (carun == "#default") {
		// SAT
		if (_access(readini(CaptINI, "pubvar", "default").c_str(), 0)) {
			lntype("lang.calcium.packageDefaultLoadFailed");
			return 1;
		}

		ofstream RootLockS;
		RootLockS.open(NRootLock);
		RootLockS << "Lock" << endl;

		ShellExecute(0, "open", CaOutage.c_str(), TCAPT.c_str(), getselfpath().c_str(), SW_SHOW);
		int errlevel = ScriptRun(TCAPT + "\\" + readini(CaptINI, "pubvar", "default").c_str(), vercode, 3, 1, Nsafemark);
		if (errlevel == 1) {
			lntype("lang.calcium.packageException");
			return 1;
		}
		cout << endl;
		SetCurrentDirectory(PATH.c_str());

		return 0;
		// END
	}

	if (_access(carun.c_str(), 0)) {
		cout << Outlang("lang.calcium.packageCARunError") << carun << endl;
		return 1;
	}

	ofstream RootLockS;
	RootLockS.open(NRootLock);
	RootLockS << "Lock" << endl;

	ShellExecute(0, "open", CaOutage.c_str(), TCAPT.c_str(), getselfpath().c_str(), SW_SHOW);
	int errlevel = ScriptRun(TCAPT + "\\" + carun, vercode, 3, 1, Nsafemark);
	if (errlevel == 1) {
		lntype("lang.calcium.packageException");
		return 1;
	}

	cout << endl;
	SetCurrentDirectory(PATH.c_str());

	return 0;
}

void listhelp() {
	cout << endl;
	cout << "Calcium Script Platform  Help Center" << endl;
	cout << "Fast Invoke:  (Only Register) " << endl;
	cout << "                   Cac <COMMAND>" << endl;
	cout << "Run Parameter " << endl;
	cout << "                   -reg :  Register on your PC" << endl;
	cout << "                   -unreg :  Unregister your pc" << endl;
	cout << "                   -casp :  Run Calcium Script" << endl;
	cout << "                   -capt :  Run Calcium Package" << endl <<endl;
	cout << " if you have any problem you can contect us:  " << endl;
	cout << "                     https://www.foxaxu.com/contact" << endl;
	cout << " Official Website" << endl;
	cout << "                     https://calcium.foxaxu.com" << endl;
	cout << " Calcium Version " << endl;
	cout << "                     Fulll Version _" << Version << "_.  Version Code :  _" << to_string(vercode) << "_." << endl;
	cout << "Release Time :  _" << ComVer << "_" << endl;
	if (InsidePreview == 1) {
		cout << "InsidePreview" << endl;
	}
	cout << "Thanks your using" << endl;
	cout << "Copyright FoxaXu@" << endl;
	cout << endl;
	return;
}

void StartRunMode() {
	//cout << "Start Run" << endl;
	LaunchParameter = parametersA;

	if (LoadMode == 1) {
		if (LoadFile == "NUL") {
			lntype("lang.calcium.DefaultRun");
			cpause(Outlang("lang.public.PAK"));
			return;
		}
		mdfolder(TempCAPT);
		ShellExecute(0, "open", CaOutage.c_str(), TempCAPT.c_str(), 0, SW_SHOW);
		
		string NRootLock = TempCAPT + "\\session.lock";
		string Nsafemark = TempCAPT + "\\unsafe.lock";

		ofstream RootLockS;
		RootLockS.open(NRootLock);
		RootLockS << "Lock" << endl;

		ResLoadFile = LoadFile;
		int backdt = ScriptRun(LoadFile, vercode, 3, 1, Nsafemark);
		SetCurrentDirectory(PATH.c_str());
		if (backdt == 1) {
			cout << "------------------------------------------------------------" << endl;
			lntype("lang.calcium.packageException");
			cout << "Script Mode" << endl;
			cpause(Outlang("lang.public.PAK"));
			return;
		}
		return;
	}

	if (LoadMode == 2) {
		if (LoadFile == "NUL") {
			lntype("lang.calcium.DefaultRun");
			cpause(Outlang("lang.public.PAK"));
			return;
		}
		int backdt = packloader(LoadFile, "#default", TempCAPT);
		if (backdt == 1) {
			cout << "------------------------------------------------------------" << endl;
			lntype("lang.calcium.packageException");
			cout << "Package Mode" << endl;
			cpause(Outlang("lang.public.PAK"));
			return;
		}
		return;
	}

	listhelp();

	cpause(Outlang("lang.public.PAK"));
	return;
}

int main(int argc, char* argv[]) {
	mdfolder(TempCaPKG);
	int ReadLN = 0;
	int Effcode;

	string curpmd;

	//MessageBox(0, "Start Roll CMD", parametersA.c_str(), MB_OK);

BackGetCommand:
	//cout << "RLN : _" << to_string(ReadLN) << "_.  argc :  _" << to_string(argc) << "_" << endl;
	if (ReadLN >= argc) {
		StartRunMode();
		return 0;
	}
	
	curpmd = argv[ReadLN];
	//cout << "Get CMD :  _" << curpmd << "_" << endl;
	parametersA = parametersA + curpmd + " ";

	Effcode = 0;

	if (curpmd == "-capt") {
		Effcode = 1;
		ReadLN++;
		if (ReadLN == argc) {
			LoadMode = 2;
		}
		else {
			curpmd = argv[ReadLN];
			parametersA = parametersA + curpmd + " ";
			LoadFile = argv[ReadLN];
			LoadMode = 2;
			if (_access(LoadFile.c_str(), 0)) {
				cout << "Error. File :  _" << LoadFile << "_. Not Exist " << endl;
				lntype("lang.calcium.packageNULL");
				return 0;
			}
		}
	}
	if (curpmd == "-casp") {
		Effcode = 1;
		ReadLN++;
		if (ReadLN == argc) {
			LoadMode = 1;
		}
		else {
			LoadFile = argv[ReadLN];
			curpmd = argv[ReadLN];
			parametersA = parametersA + curpmd + " ";
			LoadMode = 1;
			if (_access(LoadFile.c_str(), 0)) {
				cout << "Error. File :  _" << LoadFile << "_. Not Exist " << endl;
				lntype("lang.calcium.packageNULL");
				return 0;
			}
		}
	}
	if (curpmd == "-reg") {
		lntype("lang.public.Admin");
		regcalcium();
		return 0;
	}
	if (curpmd == "-unreg") {
		lntype("lang.public.Admin");
		unregcalcium();
		return 0;
	}
	if (checkChar(curpmd, "-p$") == 1) {
		Effcode = 1;
		RunPara = curpmd;
	}

	if (ReadLN == 0){}
	else {
		if (Effcode == 0) {
			cout << "Unknown Calcium Parameter :  _" << curpmd << "_" << endl;
		}
	}

	ReadLN++;
	goto BackGetCommand;
}