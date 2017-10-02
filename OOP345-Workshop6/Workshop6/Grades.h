#pragma once
#include <vector>
#include <string>

class Grades {
private:
	struct Grade {
		std::string studentID;
		double grade;

		Grade(std::string& p_studentID, double& p_grade) {
			studentID = p_studentID;
			grade = p_grade;
		}
	};

	std::vector<Grade> grades;
	char* file;

public:

	Grades();
	Grades(const char*);

	~Grades();


	//PROHIBITIONS
	Grades(const Grades&)				= delete;
	Grades(Grades&&)					= delete;
	Grades& operator=(const Grades&)	= delete;
	Grades&& operator=(Grades&&)		= delete;


	//Display Grades
	template <typename L>
	void displayGrades(std::ostream& os, L letter) {

		for (auto g = grades.begin(); g != grades.end(); g++) {
			std::cout << g->studentID << " " << g->grade << " " << letter(g->grade) << std::endl;
		}
	}
};