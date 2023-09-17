#include "ADSF.h"

using namespace std;

int main() {
	Reload:
	cout << "test cutline 1 2 3 4 5 6 7 8 9 10" << endl;

	cout << endl;
	cout << "Type Line:   $";
	string nc;
	getline(cin, nc);
	int cur = atoi(nc.c_str());

	cout << cutlineblock("1 2 3 4 5 6 7 8 9 10", cur) << endl;
	goto Reload;
}