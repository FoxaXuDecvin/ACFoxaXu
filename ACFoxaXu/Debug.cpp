#include"ADSF.h"

using namespace std;

int main() {
	BackRoll:
	string StartInfo = "123456789";
	
	string abp;
	cout << "Select Read Size: ";

	getline(cin, abp);

	cout << SizeRead(StartInfo, atoi(abp.c_str())) << endl;
	cout << endl;

	goto BackRoll;
	return 0;

}