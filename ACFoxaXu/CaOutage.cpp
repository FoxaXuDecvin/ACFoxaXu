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
		MessageBox(0, "Please Set Parameter to Run This Program", "Calcium Anti Outage", MB_ICONWARNING | MB_OK);
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
				string ErrCMDLine = readini(safemark, "Run", "Line");
				string FullVersion = readini(safemark, "Run", "FullVersion");
				string ErrScript = readini(safemark, "Run", "Script");
				string crashvarmem = LineReader(safemark + "~DVS", 1);

				//OutLogs
				ofstream CrashLog;
				CrashLog.open("err~crash~report.log");
				CrashLog << "-Calcium Crash/Exception Report-" << endl;
				CrashLog << endl;
				CrashLog << "            Calcium Seems Exit Exception.We apologize for the inconvenience caused by this crash" << endl;
				CrashLog << "              if this problem from Package, Please contact capt auther, to send this Error Screen" << endl;
				CrashLog << "    If this problem occurs in the Calcium Kernel, Please Contact us, Go To https://www.foxaxu.com/contact" << endl;
				CrashLog << endl;
				CrashLog << endl;
				CrashLog << "                    Crash Command :   _" + ErrCMD +"_" << endl;
				CrashLog << "                    Crash Address Line :  _" + ErrCMDLine + "_" << endl;
				CrashLog << "                    Calcium Full Version :  _" + FullVersion + "_" << endl;
				CrashLog << endl;
				CrashLog << "Script :  _" + ErrScript + "_" << endl;
				CrashLog << "RunTemp :  _" + CaptService + "_" << endl;
				CrashLog << "Crash Report is Save on :  _" + getselfpath() + "\\err~crash~report.log" + "_" << endl;
				CrashLog << "------------------------------------------------------------------------------------------------------------------------" << endl;
				CrashLog << "memory Var Space :  " << endl;
				CrashLog << crashvarmem << endl;
				CrashLog << "------------------------------------------------------------------------------------------------------------------------" << endl;
				CrashLog.close();
				
				ShellExecute(0, "open", "notepad", "err~crash~report.log", 0, SW_SHOW);
				rmfolder(CaptService);
				return 0;
			}
			else {
				Sleep(1000);
				goto StartProtect;
			}

		}
		else {
			string ag = "Run Anti Outage Services Failed, Folder :  <" + CaptService + "> is Null.";
			MessageBox(0,ag.c_str(), "Calcium Anti Outage", MB_ICONERROR | MB_OK);
			return 0;
		}

	}
	MessageBox(0, "Unknown Parameter", "Calcium Anti Outage", MB_ICONERROR | MB_OK);
	return 0;
}