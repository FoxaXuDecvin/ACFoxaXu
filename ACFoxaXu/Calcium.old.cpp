//Calcium Language
#include "ADSF.h"
#include"resource.h"
#include"D:\CppHeader\winapicore.h"
//定义ACF的版本信息

string PATH = getselfpath();

string VCNum = to_string(vercode);
string ConfigINI = PATH + "\\config.ini";
string TempCAPT = getwinenvfast("temp") + "\\CalciumPackage\\" + to_string(SpawnRandomNum(11111111, 99999999));

//成功返回 1，失败返回 0
int packloader(string packfile,string carun,string TCAPT) {
	string NRootLock = TCAPT + "\\session.lock";
	string Nsafemark = TCAPT + "\\unsafe.lock";
	//start
	if (_access(packfile.c_str(), 0)) {
		lntype("lang.calcium.packageNULL");
		return 0;
	}
	// Ready
	//解压7z
	mdfolder(TCAPT);

	n7zUNZIP(PATH + readini(ConfigINI, "7z", "n7zcore"), packfile, TCAPT, "0");

	string CaptINI = TCAPT + "\\capt.ini";
	if (_access(CaptINI.c_str(), 0)) {
		lntype("lang.calcium.packageINIfailed");
		return 0;
	}

	SetCurrentDirectory(TCAPT.c_str());

	cout << endl;
	cout << "Package Loading :  " << packfile << endl;
	cout << endl;

	if (carun == "#default") {
		// SAT
		if (_access(readini(CaptINI, "pubvar", "default").c_str(), 0)) {
			lntype("lang.calcium.packageDefaultLoadFailed");
			return 0;
		}

		ofstream RootLockS;
		RootLockS.open(NRootLock);
		RootLockS << "Lock" << endl;

		ShellExecute(0, "open", CaOutage.c_str(), TCAPT.c_str(),getselfpath().c_str(), SW_SHOW);

		int errlevel = ScriptRun(readini(CaptINI, "pubvar", "default").c_str(), vercode, 2, 1,Nsafemark);
		if (errlevel == 1) {
			lntype("lang.calcium.packageException");
			return 0;
		}
		cout << endl;
		SetCurrentDirectory(PATH.c_str());

		return 1;
		// END
	}

	if (_access(carun.c_str(), 0)) {
		cout << Outlang("lang.calcium.packageCARunError") << carun << endl;
		return 0;
	}

	

	ofstream RootLockS;
	RootLockS.open(NRootLock);
	RootLockS << "Lock" << endl;

	ShellExecute(0, "open", CaOutage.c_str(), TCAPT.c_str(), getselfpath().c_str(), SW_SHOW);
	int errlevel = ScriptRun(carun, vercode, 2, 1,Nsafemark);
	if (errlevel == 1) {
		lntype("lang.calcium.packageException");
		return 0;
	}

	cout << endl;
	SetCurrentDirectory(PATH.c_str());

	return 1;
}

int main(int argc, char*argv[]) {
	if (argc == 1) {
		string cmd = "\"\"" + COREFILE + "\" -capt \"" + PATH + readini(PATH + "\\config.ini", "default", "nopara")+"\"\"";
		cout << Outlang("lang.calcium.DefaultRun") << " :  " << cmd << endl;
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
			regcalcium();
			return 0;
		}
		if (ParaFile == "unreg") {
			unregcalcium();
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
			cout << Outlang("lang.calcium.UnableLoad") << " :  " << ParaFile << endl;
			cout << "File Head is NULL. add #Calc in head" << endl;

			cpause(Outlang("lang.public.PAK"));
			cout << endl;
			return 0;
		}

		//加载脚本
		int errlevel = ScriptRun(ParaFile,vercode,2,0,"NULL");
		if (errlevel == 1) {
			cout << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			lntype("lang.calcium.ErrReport");
			lntype("lang.public.PAK");
			cpause(Outlang("lang.public.PAK"));
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
				lntype("lang.calcium.ErrReport");
				lntype("lang.public.PAK");
				cpause(Outlang("lang.public.PAK"));
				return 0;
			}
		}
		if (ParaChar == "-casp") {
			if (_access(ParaPack.c_str(), 0)) {
				cout << Outlang("lang.calcium.UnableLoad") << " :  " << ParaPack << endl;
				lntype("lang.calcium.CheckType");
				cpause(Outlang("lang.public.PAK"));
				cout << endl;
				return 0;
			}

			//验证文件头
			string Head = LineReader(ParaPack, 1);
			if (Head == "#Calc") {}
			else {
				cout << Outlang("lang.calcium.UnableLoad") << " :  " << ParaPack << endl;
				cout << "File Head is NULL. add #Calc in head" << endl;
				cpause(Outlang("lang.public.PAK"));
				cout << endl;
				return 0;
			}

			//加载脚本
			int errlevel = ScriptRun(ParaPack, vercode, 2, 0, "NULL");
			if (errlevel == 1) {
				cout << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "File Exit Error :  " << ParaPack << endl;
				cpause(Outlang("lang.public.PAK"));
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
				lntype("lang.calcium.ErrReport");
				lntype("lang.public.PAK");
				cpause(Outlang("lang.public.PAK"));
				return 0;
			}
		}
		if (ParaChar == "-casp") {
			if (_access(ParaPack.c_str(), 0)) {
				cout << Outlang("lang.calcium.UnableLoad") << " :  " << ParaPack << endl;
				lntype("lang.calcium.CheckType");
				cpause(Outlang("lang.public.PAK"));
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
				cpause(Outlang("lang.public.PAK"));
				cout << endl;
				return 0;
			}
			if (GetLineData == ParaLoadSign) {
				int errlevel = ScriptRun(ParaPack, vercode, CURRLINE, 0,"NULL");
				if (errlevel == 1) {
					cout << endl;
					cout << "-------------------------------------------------------------------------------" << endl;
					cout << "File Exit Error :  " << ParaPack << endl;
					cpause(Outlang("lang.public.PAK"));
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