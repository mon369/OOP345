#include <iostream>
#include <fstream>
#include <string>
#include "Stations.h"
using namespace std;

namespace w2 {
	Stations::Stations() { noStations = 0; }

	Stations::Stations(const char* argv) {
		file.open(argv, file.in);
		if (file) {
			while (file.good()) {
				file >> noStations;
				file.ignore(1, ';');
				stations = new Station[noStations];
				for (int i = 0; i < noStations; i++) {
					string stn;
					int stdPasses;
					int adtPasses;
					getline(file, stn, ';');
					file >> stdPasses;
					file >> adtPasses;
					stations[i].set(stn, stdPasses, adtPasses);
				}
			}
			file.clear();
			file.close();
		}
	}



	void Stations::update() const{
		cout << endl;
		cout << "Passes Sold :" << endl;
		cout << "-------------" << endl;
		for (int i = 0; i < noStations; i++) {
			int n;
			cout << stations[i].getName() << endl;
			cout << " Student Passes sold : "; cin >> n; stations[i].update(Student, n * -1);
			cout << " Adult Passes sold : "; cin >> n; stations[i].update(Adult, n * -1);
		}
	}

	void Stations::restock() const {
		cout << endl;
		cout << "Passes Added :" << endl;
		cout << "-------------" << endl;
		for (int i = 0; i < noStations; i++) {
			int n;
			cout << stations[i].getName() << endl;
			cout << " Student Passes added : "; cin >> n; stations[i].update(Student, n);
			cout << " Adult Passes added : "; cin >> n; stations[i].update(Adult, n);
		}
	}

	void Stations::report() const {
		cout << "Passes in Stock : Student Adult" << endl;
		cout << "-------------------------------" << endl;
		for (int i = 0; i < noStations; i++) {
			cout << stations[i].getName() << ";" << stations[i].inStock(Student) << " " << stations[i].inStock(Adult);
		}
	}

	Stations::~Stations() {
		delete [] stations;
	}
}