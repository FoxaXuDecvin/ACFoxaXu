#include"D:\CppHeader\WinReg.h"
#include"DLLApi.h"

using namespace std;

int main() {
	BKsO:
	system("cls");
	cout << "Type Debug DLL" << endl;
	cout << "DLL >";
	string URL;
	getline(cin, URL);
	cout << "Type Debug DLL Command" << endl;
	cout << "DLLCMD >";
	string URLCMD;
	getline(cin, URLCMD);


	cout << "---------------------------------------------------------------" << endl;
	int a =DllLoad(URL,URLCMD);
	if (a == 1) {
		cout << "No" << endl;
	}
	else {
		cout << "Yes" << endl;
	}
	cout << "---------------------------------------------------------------" << endl;
	if (a == 1) {
		MessageBox(0, "Dll Load Failed. ", "DLL API", MB_ICONERROR | MB_OK);
	}
	cpause("Press any key to Back");
	goto BKsO;
}