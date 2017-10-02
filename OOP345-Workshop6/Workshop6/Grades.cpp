#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "Grades.h"
using namespace std;

Grades::Grades(): file(nullptr){}


Grades::Grades(const char* p_file) {
	if (p_file != nullptr) {
		file = new char[ strlen(p_file) + 1];
		strcpy(file, p_file);
		file[strlen(p_file)] = 0;

		ifstream ifile(file);
		if (ifile) {
			string studentID; 
			double grade = 0;
			while (ifile >> studentID >> grade ) {

				Grade g(studentID, grade);
				grades.push_back(g);
			}
		}
		ifile.clear();
		ifile.close();
	}
}



Grades::~Grades() {
	
	delete [] file;
	grades.clear();
}