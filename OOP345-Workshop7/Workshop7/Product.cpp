#include <iostream>
#include <iomanip>
#include <string>
#include "iProduct.h"
#include "Product.h"
using namespace std;
namespace w7 {

	Product::Product(): price(0.0){}

	Product::Product(string& p_prodNum, double& p_price) {
		prodNum = p_prodNum;
		price = p_price;
	}
	

	double Product::getCharge() const {
		return price;
	}

	void Product::display(ostream& os) const {
		os << setw(10) << right << prodNum << setw(5) << " " << fixed << setprecision(2) << price << " ";
	}
}