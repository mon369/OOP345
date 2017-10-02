#include <iostream>
#include <string>
#include "Station.h"
using namespace std;

namespace w2 {

	Station::Station() {
		noStd = 0;
		noAdt = 0;
	}
	void Station::set(const string& stn, unsigned stdPass, unsigned adtPass) {
		station = stn;
		noStd = stdPass;
		noAdt = adtPass;
	}
	unsigned Station::inStock(PassType p) const {
		return (p == Student) ? noStd : noAdt;
	}
	void Station::update(PassType p, int no) {
		unsigned int* passes_p = nullptr;
		passes_p = (p == Student) ? &noStd : &noAdt;
		
		if (no < 0) {
			no *= -1;
			*passes_p -= no;
		}
		else {
			*passes_p += no;
		}
	}

	const string& Station::getName() const {
		return station;
	}

}