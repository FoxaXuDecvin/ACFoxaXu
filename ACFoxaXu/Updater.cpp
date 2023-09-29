#include"ADSF.h"

using namespace std;

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址

void NoticeB(string Info) {
	MessageBox(0, Info.c_str(), "Notice", MB_ICONQUESTION | MB_OK);
	return;
}

void UpdateBLOCK(string Path) {
	string CURVerPart = readini(".\\config.ini", "Version", "CURRENT");
	string WebURL = readini(".\\config.ini", "Version", "API");
	string NewVersion = geturlcode(WebURL);

	string Temp = getwinenvfast("temp");
	string TempWork = Temp + "\\UpdateCalcium.exe";

	URLDown(readini(".\\config.ini", "Version", "UpdateTool"), TempWork);

	Sleep(1000);

	if (_access(TempWork.c_str(), 0)) {
		MessageBox(0, "Update Failed, cannot Download Update Tools", NewVersion.c_str(), MB_OK);
		return;
	}

	ShellExecute(0, "runas", TempWork.c_str(), "--reinstall", Path.c_str(), SW_SHOW);
	return;
}

int main(int argc, char* argv[]) {
	//Anti Run Much

	string systemp = getenv("temp");
	string sessionlock = systemp + "\\MarkCaUpdate.lock";

	if (_access(sessionlock.c_str(),0)){}
	else {
		remove(sessionlock.c_str());
		Sleep(500);
		if (_access(sessionlock.c_str(), 0)){}
		else {
			MessageBox(0, "Calcium Update Service is Already Running on your PC. Please try to use taskmgr taskkill old process and run again", "Service is Running on PC", MB_ICONQUESTION | MB_OK);
			return 0;
		}
	}

	ofstream SessionLockOpen;
	SessionLockOpen.open(sessionlock);
	SessionLockOpen << "Hello World" << endl;

	if (argc == 1) {
		//Auto Update Services
		string sysdata = getenv("ProgramData");
		string PGDataf = sysdata + "\\CalciumScript";
		string PGINSDATA = PGDataf + "\\CaInfo.txt";

		if (_access(PGINSDATA.c_str(), 0)) {
			MessageBox(0, "Failed to Find Install Path, Check your Calcium is Install On Your Computer. if your Calcium is Portable Version, Dont use this Update. Calcium Cannot Auto Update.if you dont want update. please disabled caupdater.exe autorun", PGINSDATA.c_str(), MB_ICONERROR | MB_OK);
			return 0;
		
		}

		string curfolder = readini(PGINSDATA, "Install", "Path");
		if (existfolderA(curfolder,"Calcium.exe")) {
		ReCheckUpdate:
			SetCurrentDirectory(curfolder.c_str());
			string CURVerPart = readini(".\\config.ini", "Version", "CURRENT");
			string WebURL = readini(".\\config.ini", "Version", "API");
			string NewVersion = geturlcode(WebURL);

			if (CURVerPart == NewVersion) {
				if (atoi(readini(".\\config.ini", "Version", "UpdateSleep").c_str()) == -1) {
					//Only Check Once a Update On StartUp
					return 0;
				}
				Sleep(atoi(readini(".\\config.ini", "Version", "UpdateSleep").c_str()));
				goto ReCheckUpdate;
			}
			if (NewVersion == "geturlfailed") {
				NoticeB("Failed to Connect Server. Calcium Cannot Auto Update.if you dont want update. please disabled caupdater.exe autorun");
				return 0;
			}

			//Find New Version

			//Auto Update
			if (bool a = testAdmin("C:")) {}
			else {
				ShellExecute(0, "runas", getselfinfo().c_str(), 0, 0, SW_SHOW);
				return 0;
			}

			UpdateBLOCK(curfolder);

			return 0;

		}
		else {
			MessageBox(0,"Failed to Find Folder. Calcium Cannot Auto Update.if you dont want update. please disabled caupdater.exe autorun",curfolder.c_str(),MB_ICONERROR|MB_OK);
			return 0;
		}
	}

	if (argc == 2) {
		if (bool a = testAdmin("C:")) {}
		else {
			cout << "Use Administrator Run" << endl;
			cpause("Press any key to Exit .... ");
			return 0;
		}
		int alang = 0;
		alang++;
		if (existfolder(argv[alang])) {

			SetCurrentDirectory(argv[alang]);
			if (_access("config.ini", 0)) {
				string o = argv[alang];
				string text = "Directory is null :  " + o;
				MessageBox(0, text.c_str(), "Path Error", MB_OK);
				return 0;
			}

			string CURVerPart = readini(".\\config.ini", "Version", "CURRENT");
			string WebURL = readini(".\\config.ini", "Version", "API");
			string NewVersion = geturlcode(WebURL);

			//NoticeB(WebURL);
			//NoticeB(NewVersion);

			if (CURVerPart == NewVersion) {
				MessageBox(0, "You are using latest version of Calcium", NewVersion.c_str(), MB_OK);
				return 0;
			}
			if (NewVersion == "geturlfailed") {
				MessageBox(0, "Failed to Connect Server, Please Check your Internet", NewVersion.c_str(), MB_OK);
				return 0;
			}
			int usel = MessageBoxA(0, "New Update is Release. Do you want install? ", NewVersion.c_str(), MB_YESNO| MB_ICONQUESTION);
			if (usel == 6) {
				//YES
				UpdateBLOCK(argv[alang]);

				return 0;
			}
			else {
				MessageBox(0, "User Cancel Update", NewVersion.c_str(), MB_OK);
				return 0;
			}

		}
		else {
			NoticeB("Failed To Find Path.");
			return 0;
		}
	}
	
	NoticeB("Null Parameter");
	return 0;
}