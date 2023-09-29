#include"D:\CppHeader\winapicore.h"
using namespace std;

int main(int argc, char* argv[]) {
	//FORMAT:
	// TransLine <OUTFILE> <Info>
	// MAXSUPPORT 6

	if (argc == 1) {
		return 0;
	}
	int al = 1;
	string outfile = argv[al];
	remove(outfile.c_str());
	string TempFileName = outfile + "~temp";
	remove(TempFileName.c_str());

	int markdown = argc;

	cout << to_string(markdown) << " /1/ " << to_string(al) << endl;

	al++;
	cout << to_string(markdown) << " /2/ " << to_string(al) << endl;
	string P1 = argv[al];
	al++;
	cout << to_string(markdown) << " /3/ " << to_string(al) << endl;
	if (al == markdown) {
		writeini(TempFileName, "TransLine", "P1", P1);

		rename(TempFileName.c_str(), outfile.c_str());
		return 0;
	}
	string P2 = argv[al];
	al++;
	cout << to_string(markdown) << " /4/ " << to_string(al) << endl;
	if (al == markdown) {
		writeini(TempFileName, "TransLine", "P1", P1);
		writeini(TempFileName, "TransLine", "P2", P2);
		rename(TempFileName.c_str(), outfile.c_str());
		return 0;
	}
	string P3 = argv[al];
	al++;
	cout << to_string(markdown) << " /5/ " << to_string(al) << endl;
	if (al == markdown) {
		writeini(TempFileName, "TransLine", "P1", P1);
		writeini(TempFileName, "TransLine", "P2", P2);
		writeini(TempFileName, "TransLine", "P3", P3);
		rename(TempFileName.c_str(), outfile.c_str());
		return 0;
	}
	string P4 = argv[al];
	al++;
	cout << to_string(markdown) << " /6/ " << to_string(al) << endl;
	if (al == markdown) {
		writeini(TempFileName, "TransLine", "P1", P1);
		writeini(TempFileName, "TransLine", "P2", P2);
		writeini(TempFileName, "TransLine", "P3", P3);
		writeini(TempFileName, "TransLine", "P4", P4);
		rename(TempFileName.c_str(), outfile.c_str());
		return 0;
	}
	string P5 = argv[al];
	al++;
	cout << to_string(markdown) << " /7/ " << to_string(al) << endl;
	if (al == argc) {
		writeini(TempFileName, "TransLine", "P1", P1);
		writeini(TempFileName, "TransLine", "P2", P2);
		writeini(TempFileName, "TransLine", "P3", P3);
		writeini(TempFileName, "TransLine", "P4", P4);
		writeini(TempFileName, "TransLine", "P5", P5);
		rename(TempFileName.c_str(), outfile.c_str());
		return 0;
	}
	string P6 = argv[al];
	writeini(TempFileName, "TransLine", "P1", P1);
	writeini(TempFileName, "TransLine", "P2", P2);
	writeini(TempFileName, "TransLine", "P3", P3);
	writeini(TempFileName, "TransLine", "P4", P4);
	writeini(TempFileName, "TransLine", "P5", P5);
	writeini(TempFileName, "TransLine", "P6", P6);
	rename(TempFileName.c_str(), outfile.c_str());
	return 0;

	string nuls = to_string(argc);
	string renuls = to_string(al);
	cout << "failed " << nuls << "  al : " << al <<"   outfile : "<<outfile << endl;
	return 0;
}