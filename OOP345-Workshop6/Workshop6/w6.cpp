// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include "Grades.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}


	Grades grades(argv[1]);
	// define the lambda expression for letter
 

	auto letter = [](double g) { 
		std::string gl;
		if (g >= 90 && g <= 100) {
			gl = "A+";
		}
		else if (g >= 80 && g <= 89.9) {
			gl = "A";
		}
		else if (g >= 75 && g <= 79.9) {
			gl = "B+";
		}
		else if (g >= 70 && g <= 74.9) {
			gl = "B";
		}
		else if (g >= 65 && g <= 69.9) {
			gl = "C+";
		}
		else if (g >= 60 && g <= 64.9) {
			gl = "C";
		}
		else if (g >= 55 && g <= 59.9) {
			gl = "D+";
		}
		else if (g >= 50 && g <= 54.9) {
			gl = "D";
		}
		else if (g >= 0 && g <= 49) {
			gl = "F";
		}
		
		return gl;
	};



	grades.displayGrades(std::cout, letter);




	std::cout << "Press any key to continue ... ";
	std::cin.get();
}