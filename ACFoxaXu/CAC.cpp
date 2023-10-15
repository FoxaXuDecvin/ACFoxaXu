#include"ADSF.h"
using namespace std;

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址

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

		int ReadLN = 0;

		string parametersA = "";

		//MessageBox(0, "Start Roll CMD", parametersA.c_str(), MB_OK);

	BackGetCommand:
		if (ReadLN == argc) {
			//MessageBox(0, parametersA.c_str(), "Notice Para", MB_OK);
			string clparametersA = cutlineblockA(parametersA, " ", 1);
			parametersA = CleanAuto(parametersA, clparametersA + " ");
			//MessageBox(0, parametersA.c_str(), "After Filiter", MB_OK);
			if (checkChar(parametersA, "-noconsole") == 1) {
				parametersA = CleanAuto(parametersA, " -noconsole");
				ShellExecute(0, "open", maincore.c_str(), parametersA.c_str(), 0, SW_HIDE);
				return 0;
			}
			else {
				ShellExecute(0, "open", maincore.c_str(), parametersA.c_str(), 0, SW_SHOW);
				return 0;
			}
		}
		parametersA = parametersA + "\"" + argv[ReadLN] + "\" ";
		//string msbox = "New LocalNum _" + to_string(ReadLN) + "_ CURRENTMAX = _" + to_string(argc) + "_";
		//MessageBox(0, msbox.c_str(), "COmplete Read", MB_OK);

		//MessageBox(0, "Auto Config", parametersA.c_str(), MB_OK);

		//msbox = "After LocalNum _" + to_string(ReadLN) + "_ CURRENTMAX = _" + to_string(argc) + "_";
		//MessageBox(0, msbox.c_str(), "COmplete Read", MB_OK);
		ReadLN++;
		//MessageBox(0, "Complete Add", to_string(ReadLN).c_str(), MB_OK);
		goto BackGetCommand;

		//MessageBox(0, Outlang("lang.cac.NULLParaMeter").c_str(),"Calcium Invoke Error", MB_ICONERROR | MB_OK);
		return 0;
	}
	else {
		MessageBox(0, Outlang("lang.cac.NoInstallInfo").c_str(), "Calcium Fast Invoke Error", MB_ICONERROR | MB_OK);
		return 0;
	}
}