#include "ADSF.h"
//定义ACF的版本信息

int vercode = 1002;
string Version = "Hans Core";
string ComVer = "2023/9/3";

string VCNum = to_string(vercode);

string PATH = getselfpath();
string COREFILE = getselfinfo();

int main(int argc, char*argv[]) {
	if (argc == 1) {
		cout << "Welcome to use Access Center FoxaXu Script," << endl;
		cout << "Hope this program can help you" << endl;
		cout << "Use Command :  ACFoxaXu.exe <script>" << endl;
		cout << "ACF Version :   " << Version << " " << VCNum << endl;
		cout << "Running on : " << endl;
		cout << "     " << PATH << endl;
		cout << "     " << COREFILE << endl;
		cout << endl;
		cout << "Copyright FoxaXu. 2023" << endl;
		cout << "Compile time :   " << ComVer << endl;
		cout << endl;
		cpause("Press any key to Close");
		cout << endl;
		ShellExecute(0, "open", "cmd", 0, PATH.c_str(), SW_SHOW);
		return 0;
	}
	if (argc == 2) {

		int al = 0;
		al++;
		string ParaFile = argv[al];
		if (_access(ParaFile.c_str(), 0)) {
			cout << "Unable to load from :  " << ParaFile << endl;
			cout << "Check your type and try again" << endl;
			cpause("Press any key to Close");
			cout << endl;
			return 0;
		}

		//验证文件头
		string Head = LineReader(ParaFile, 1);
		if (Head=="#adsf") {}
		else {
			cout << "Unable to load from :  " << ParaFile << endl;
			cout << "File Head is NULL. add #adsf in head" << endl;
			cpause("Press any key to Close");
			cout << endl;
			return 0;
		}

		//加载脚本
		int errlevel = ScriptRun(ParaFile);
		if (errlevel == 1) {
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "File Exit Error :  " << ParaFile << endl;
			cout << "Check Log to find problem" << endl;
			cpause("Press any key to Close");
			cout << endl;
			return 0;
		}
		
		return 0;
	}

}