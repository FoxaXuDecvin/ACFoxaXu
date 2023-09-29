#include"D:\CppHeader\WinReg.h"

using namespace std;

int main() {
	Reload:
	string File;
	cout << "File >";
	getline(cin, File);
	cout << endl;

	string SAVE;
	cout << "Save >";
	getline(cin, SAVE);
	cout << endl;
	
	string ICON;
	cout << "ICON >";
	getline(cin, ICON);

	string INFO;
	cout << "INFO >";
	getline(cin, INFO);

	createlink(File, SAVE, ICON, INFO);
	goto Reload;
}