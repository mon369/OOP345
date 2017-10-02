#include <iostream>
#include <fstream>
#include "Stations.h"

using namespace std;
using namespace w2;

int main(int argc, char** argv) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << ' ';
	}
	std::cout << std::endl;
	if (argc != 2) {
		std::cerr << "\nIncorrect number of arguments\n";
		return 1;
	}
	Stations stations(argv[1]);
	stations.report();

	stations.update();
	stations.report();

	stations.restock();
	stations.report();


	return 0;
}
