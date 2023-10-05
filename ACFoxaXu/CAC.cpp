#include"ADSF.h"
using namespace std;

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址

string PGDataf = getwinenvfast("ProgramData") + "\\CalciumScript";
string PGINSDATA = PGDataf + "\\CaInfo.txt";

int main(int argc, char* argv[]) {
	//Auto Find Root
	if (existfolder) {
		string rootfolder = readini(PGINSDATA, "Install", "Path");
		SetCurrentDirectory(rootfolder.c_str());

		string maincore = rootfolder + "\\Calcium.exe";

		if (_access(maincore.c_str(), 0)) {
			string messageb = Outlang("lang.cac.ErrNoCore") + maincore;
			MessageBox(0,messageb.c_str(), "Calcium Fast Invoke Error", MB_ICONERROR | MB_OK);
			return 0;
		}

		if (argc == 1) {
			ShellExecute(0, "open", maincore.c_str(), 0, 0, SW_SHOW);
			return 0;
		}
		if (argc == 2) {
			int al = 0;
			al++;
			string para = argv[al];

			ShellExecute(0, "open", maincore.c_str(), para.c_str(), 0, SW_SHOW);
			return 0;
		}
		if (argc == 3) {
			int al = 0;
			al++;
			string Apara = argv[al];
			al++;
			string Bpara = argv[al];

			string para = Apara + " " + Bpara;

			ShellExecute(0, "open", maincore.c_str(), para.c_str(), 0, SW_SHOW);
			return 0;
		}
		if (argc == 4) {
			int al = 0;
			al++;
			string Apara = argv[al];
			al++;
			string Bpara = argv[al];
			al++;
			string Cpara = argv[al];

			string para = Apara + " " + Bpara + " " + Cpara;

			ShellExecute(0, "open", maincore.c_str(), para.c_str(), 0, SW_SHOW);
			return 0;
		}

		MessageBox(0, Outlang("lang.cac.NULLParaMeter").c_str(),"Calcium Invoke Error", MB_ICONERROR | MB_OK);
		return 0;
	}
	else {
		MessageBox(0, Outlang("lang.cac.NoInstallInfo").c_str(), "Calcium Fast Invoke Error", MB_ICONERROR | MB_OK);
		return 0;
	}
}