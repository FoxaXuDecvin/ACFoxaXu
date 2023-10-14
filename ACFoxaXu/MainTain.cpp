#include"ADSF.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
using namespace std;

//Default Delete Folder
string Temp = getwinenvfast("temp");
string TempPKG = getwinenvfast("temp") + "\\CalciumPackage";
string TempUPD = Temp + "\\UpdateCalcium.exe";

string BLOCKMARKJ = DLLPATH + "\\CalciumUpdateBlock.txt";

void NoticeB(string Info) {
	MessageBox(0, Info.c_str(), "Notice", MB_ICONQUESTION | MB_OK);
	return;
}

void UpdateBLOCK(string Path,int showorhide) {
	string CURVerPart = readini(".\\config.ini", "Version", "CURRENT");
	string WebURL = readini(".\\config.ini", "Version", "API");
	string NewVersion = geturlcode(WebURL);

	
	string TempWork = Temp + "\\UpdateCalcium.exe";

	URLDown(readini(".\\config.ini", "Version", "UpdateTool"), TempWork);

	Sleep(1000);

	if (_access(TempWork.c_str(), 0)) {
		MessageBox(0, Outlang("lang.update.FailedDownload").c_str(), NewVersion.c_str(), MB_OK);
		return;
	}

	if (showorhide == 0) {
		ShellExecute(0, "runas", TempWork.c_str(), "--reinstall", Path.c_str(), SW_HIDE);
	}
	else {
		ShellExecute(0, "runas", TempWork.c_str(), "--reinstall", Path.c_str(), SW_SHOW);
	}
	return;
}

void UpdateDLL() {
	string ReadP;
	string dllrootsetN = DLLPATH;
	int LRRP = 1;
	int RPTotal = 0;

	int dllgetver;
BackReadDLLV:
	if (_access(DLLRECORD.c_str(), 0)) {
		return;
	}
	ReadP = LineReader(DLLRECORD, LRRP);
	if (ReadP == "overline") {
		return;
	}
	DLLUpdate(ReadP);

	LRRP++;
	RPTotal++;
	goto BackReadDLLV;
}

int main(int argc, char* argv[]) {
	//Anti Run Much
	//CheckConfig

	string MTSwitch = readini(settings, "Settings", "AutoUpdate");
	if (MTSwitch == "open"){}
	else {
		return 0;
	}

	string systemp = getenv("temp");
	string sessionlock = systemp + "\\MarkCaUpdate.lock";

	if (argc == 1) {
		if (_access(sessionlock.c_str(), 0)) {}
		else {
			remove(sessionlock.c_str());
			Sleep(500);
			if (_access(sessionlock.c_str(), 0)) {}
			else {
				MessageBox(0, Outlang("lang.update.isrun").c_str(), "Service is Running on PC", MB_ICONQUESTION | MB_OK);
				return 0;
			}
		}

		ofstream SessionLockOpen;
		SessionLockOpen.open(sessionlock);
		SessionLockOpen << "Hello World" << endl;

		//Maintain Part
		Sleep(2000);
		rmfolder(TempPKG.c_str());
		remove(TempUPD.c_str());
		string CaTemp = getenv("temp");
		string CaPLGWebDoc = CaTemp + "\\CalciumPLG.txt";
		remove(CaPLGWebDoc.c_str());
		string CaPTFile = CaTemp + "\\CalciumPulltitle.txt";
		remove(CaPTFile.c_str());
		UpdateDLL();

		//Auto Update Services
		if (_access(PGINSDATA.c_str(), 0)) {
			MessageBox(0, Outlang("lang.update.failpath").c_str(), PGINSDATA.c_str(), MB_ICONERROR | MB_OK);
			return 0;
		}

		string curfolder = readini(PGINSDATA, "Install", "Path");
		if (existfolderA(curfolder,"Calcium.exe")) {
			SetCurrentDirectory(curfolder.c_str());
			string CURVerPart = readini(".\\config.ini", "Version", "CURRENT");
			string WebURL = readini(".\\config.ini", "Version", "API");
		ReCheckUpdate:
			string NewVersion = geturlcode(WebURL);

			if (CURVerPart == NewVersion) {
				if (atoi(readini(".\\config.ini", "Version", "UpdateSleep").c_str()) == -1) {
					//Only Check Once a Update On StartUp
					return 0;
				}
				Sleep(atoi(readini(CONFIGROOT, "Version", "UpdateSleep").c_str()));
				goto ReCheckUpdate;
			}
			if (NewVersion == "geturlfailed") {
				if (atoi(readini(".\\config.ini", "Version", "UpdateSleep").c_str()) == -1) {
					//Only Check Once a Update On StartUp
					return 0;
				}
				Sleep(atoi(readini(CONFIGROOT, "Version", "UpdateSleep").c_str()));
				goto ReCheckUpdate;
			}

			//Find New Version
			
			string BlockVer = LineReader(BLOCKMARKJ, 1);
			if (BlockVer == NewVersion) {
				Sleep(atoi(readini(CONFIGROOT, "Version", "UpdateSleep").c_str()));
				goto ReCheckUpdate;
			}

			int SelectNVGiveUp = MessageBox(0, Outlang("lang.update.nutrueorfalse").c_str(), "It`s Time to Update", MB_ICONWARNING | MB_YESNO);
			if (SelectNVGiveUp == 6) {}
			else {
				cmarkfile(BLOCKMARKJ, NewVersion);
				MessageBox(0, "This Version is Blocked.", NewVersion.c_str(), MB_OK);
				Sleep(atoi(readini(CONFIGROOT, "Version", "UpdateSleep").c_str()));
				goto ReCheckUpdate;
			}

			//Auto Update
			if (bool a = testAdmin(admincheckpath)) {}
			else {
				ShellExecute(0, "runas", getselfinfo().c_str(), 0, 0, SW_SHOW);
				return 0;
			}

			UpdateBLOCK(curfolder,0);

			return 0;

		}
		else {
			MessageBox(0,Outlang("lang.update.failinstdata").c_str(), curfolder.c_str(), MB_ICONERROR | MB_OK);
			return 0;
		}
	}

	if (argc == 2) {
		int alang = 0;
		alang++;
		string rootfolderS = argv[alang];
		if (bool a = testAdmin(rootfolderS)) {}
		else {
			MessageBox(0, Outlang("lang.public.Admin").c_str(), "Warning", MB_ICONERROR | MB_OK);
			return 0;
		}
		if (existfolder(rootfolderS)) {

			SetCurrentDirectory(argv[alang]);
			if (_access("config.ini", 0)) {
				string o = argv[alang];
				string text = Outlang("lang.update.dirnull") + " :  " + o;
				MessageBox(0, text.c_str(), "Path Error", MB_OK);
				return 0;
			}

			string CURVerPart = readini(".\\config.ini", "Version", "CURRENT");
			string WebURL = readini(".\\config.ini", "Version", "API");
			string NewVersion = geturlcode(WebURL);

			//NoticeB(WebURL);
			//NoticeB(NewVersion);

			if (CURVerPart == NewVersion) {
				MessageBox(0, Outlang("lang.update.noupdate").c_str(), NewVersion.c_str(), MB_OK);
				return 0;
			}
			if (NewVersion == "geturlfailed") {
				MessageBox(0, Outlang("lang.update.nointernet").c_str(), NewVersion.c_str(), MB_OK);
				return 0;
			}
			int usel = MessageBoxA(0, Outlang("lang.update.newupdate").c_str(), NewVersion.c_str(), MB_YESNO| MB_ICONQUESTION);
			if (usel == 6) {
				//YES
				string curfolder = readini(PGINSDATA, "Install", "Path");
				if (curfolder == getselfpath()){}
				else {
					MessageBoxA(0, Outlang("lang.update.portableunsupport").c_str(), NewVersion.c_str(), MB_ICONERROR | MB_OK);
					return 0;
				}
				UpdateBLOCK(argv[alang],1);

				return 0;
			}
			else {
				MessageBox(0, "User Cancel Update", NewVersion.c_str(), MB_OK);
				return 0;
			}

		}
		else {
			MessageBox(0, "Failed to Find Path", "Calcium Update Service", MB_ICONERROR | MB_OK);
			return 0;
		}
	}
	
	MessageBox(0, "NullParameter", "Calcium MainTain Service", MB_ICONERROR | MB_OK);
	return 0;
}