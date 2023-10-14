//Anti Crash No Notices

#include"ADSF.h"
using namespace std;

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址'

char* stringTocharX(string ConVert) {
	char ch[20];
	string s = "123456";
	strcpy(ch, s.c_str());
	return ch;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		MessageBox(0, Outlang("lang.caoutage.noparameter").c_str(),"Calcium Anti Outage", MB_ICONWARNING | MB_OK);
		return 0;
	}
	if (argc == 2) {
		int alang = 0;
		alang++;
		string CaptService = argv[alang];

		if (existfolder(CaptService)) {
			string RootLock = CaptService + "\\session.lock";
			string safemark = CaptService + "\\unsafe.lock";
			if (_access(RootLock.c_str(), 0)) {
				Sleep(2000);
				if (_access(RootLock.c_str(), 0)) {
					string ag = "Run Anti Outage Services Timeout, Folder :  <" + CaptService + "> is failed to Lock";
					MessageBox(0, ag.c_str(), "Calcium Anti Outage", MB_ICONERROR | MB_OK);
					return 0;
				}
			}

		StartProtect:
			remove(RootLock.c_str());
			if (_access(RootLock.c_str(), 0)) {
				if (_access(safemark.c_str(), 0)) {
					//not Crash
					Sleep(2000);
					rmfolder(CaptService);
					return 0;
				}
				//Warning CrashRight
				string ErrCMD = readini(safemark, "Run", "Command");
				if (checkChar(ErrCMD, "pause") == 1) {
					//在暂停时中断
					//not Crash
					Sleep(2000);
					rmfolder(CaptService);
					return 0;
				}
				string ErrCMDLine = readini(safemark, "Run", "Line");
				string FullVersion = readini(safemark, "Run", "FullVersion");
				string ErrScript = readini(safemark, "Run", "Script");
				string crashvarmem = readini(safemark, "Run", "VarSpace");
				string dllrglist = readini(safemark, "Run", "DllregList");
				string launchprm = readini(safemark, "Run", "LaunchPara");


				//OutLogs
				string CrashLogPath;
				string setpathdf = readini(settings, "Settings", "CrashSavePath");
				if (setpathdf == "[Default]") {
					CrashLogPath = getwinenvfast("UserProfile") + "\\Desktop\\Calcium~CrashReport.txt";
				}
				else {
					CrashLogPath = setpathdf + "\\Calcium~CrashReport.txt";
				}
				ofstream CrashLog;
				CrashLog.open(CrashLogPath);
				CrashLog << Outlang("lang.caoutage.CrashTitle") << endl;
				CrashLog << endl;
				CrashLog << Outlang("lang.caoutage.CrashTitleA") << endl;
				CrashLog << Outlang("lang.caoutage.CrashTitleB") << endl;
				CrashLog << Outlang("lang.caoutage.CrashTitleC") << " https://www.foxaxu.com/contact" << endl;
				CrashLog << endl;
				CrashLog << endl;
				CrashLog << "                    Crash Command :   _" + ErrCMD +"_" << endl;
				CrashLog << "                    Crash Address Line :  _" + ErrCMDLine + "_" << endl;
				CrashLog << "                    Calcium Full Version :  _" + FullVersion + "_" << endl;
				CrashLog << "                    Launch Command :  _" + launchprm + "_" << endl;
				CrashLog << endl;
				CrashLog << "Script :  _" + ErrScript + "_" << endl;
				CrashLog << "RunTemp :  _" + CaptService + "_" << endl;
				CrashLog << "Crash Report is Save on :  _" + CrashLogPath + "_" << endl;
				CrashLog << "------------------------------------------------------------------------------------------------------------------------" << endl;
				CrashLog << "memory Var Space :  " << endl;
				CrashLog << crashvarmem << endl;
				CrashLog << "------------------------------------------------------------------------------------------------------------------------" << endl;
				CrashLog << "DLL Reg List (Calcium Plugin) :   " << endl;
				CrashLog << dllrglist << endl;
				CrashLog << "------------------------------------------------------------------------------------------------------------------------" << endl;
				CrashLog.close();
				
				ShellExecute(0, "open", "notepad",CrashLogPath.c_str(), 0, SW_SHOW);
				rmfolder(CaptService);
				return 0;
			}
			else {
				Sleep(1000);
				goto StartProtect;
			}

		}
		else {
			string ag = Outlang("lang.caoutage.runservicefailed") + " :  <" + CaptService + "> is Null.";
			MessageBox(0,ag.c_str(), "Calcium Anti Outage", MB_ICONERROR | MB_OK);
			return 0;
		}

	}
	MessageBox(0, Outlang("lang.caoutage.noparameter").c_str(),"Calcium Outage Service", MB_ICONERROR | MB_OK);
	return 0;
}