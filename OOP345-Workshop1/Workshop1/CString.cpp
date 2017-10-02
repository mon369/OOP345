#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "CString.h"
using namespace std;

namespace w1 {
	CString::CString(const char* argv) {
		strncpy(arg, argv, MAX_CHARS);
		arg[MAX_CHARS] = 0;
	}

	ostream& CString::display(ostream& os)const {
		os << arg << endl;
		return os;
	}

	ostream& operator<<(ostream& os, CString& cs){
		cs.display(os);
		return os;
	}	
}