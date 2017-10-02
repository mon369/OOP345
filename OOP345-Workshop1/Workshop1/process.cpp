#include <iostream>
#include "process.h"
#include "CString.h"
using namespace std;

namespace w1 {
	void process(const char* argv) {
		CString cs(argv);
		cout << cs;
	}
}