#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Sale.h"
#include "iProduct.h"
#include "Product.h"
#include "TaxableProduct.h"
using namespace std;

namespace w7 {

	Sale::Sale(const char* p_filename) {
		if (p_filename != nullptr) {
			filename = new char[strlen(p_filename) + 1];
			strcpy(filename, p_filename);

			ifstream ifile(filename);
			
			if (ifile) {
				while (ifile) {
					products.push_back(move(readProduct(ifile)));
				}			
				ifile.clear();
				ifile.close();
			}
			else {
				throw "File not found";
			}


			
		}

	}

	void Sale::display(ostream& os) const {
		os << setw(10) << "Product No" << setw(5) << " " << setw(5) << right << "Cost" << setw(1) << " " << setw(7) << "Taxable" << endl;
		double total = 0.0;
		for(auto p : products) {
			os << *p << endl;
			total += p->getCharge();
		}
		os << setw(10) << "Total" << setw(4) << " " << setw(5) << fixed << setprecision(2) << total << endl;
	}

	Sale::~Sale() {
		delete filename;
		products.clear();
	}


	ostream& operator<<(ostream& os, const iProduct& ip) {
		ip.display(os);
		return os;
	}

	iProduct* readProduct(std::ifstream& ifs) {
		string prodNum; double price; char rate = 0;
		ifs >> prodNum >> price;
		if (ifs.get() == ' ') {
			ifs >> rate;
			return new TaxableProduct(prodNum, price, rate);
		}
		else {
			return new Product(prodNum, price);
		}
		
	}

}