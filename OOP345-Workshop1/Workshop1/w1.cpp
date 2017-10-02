#include <iostream>
#include "process.h"
#include "CString.h"
using namespace std;
using namespace w1;
#define DEBUG

int main(int argc, char** argv) {

#ifdef DEBUG

	argc = 2;
	argv[0] = "w1.cpp";
	argv[1] = "Yuriy";
	
#endif

	cout << "Command Line : ";
	for (int i = 0; i < argc; i++) {
			cout << argv[i] << " ";
		}
	cout << endl;
	if (argc > 1) {
		cout << "Maximum number of characters stored : " << MAX_CHARS << endl;
		for (int i = 1; i < argc; i++) {
			cout << i - 1 << ": ";
			process(argv[i]);			
		}
	}
	else {
		cout << "Insufficient number of arguments (min 1)" << endl;
	}
	return 0;
}