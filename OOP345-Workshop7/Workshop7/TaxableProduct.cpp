#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "iProduct.h"
#include "Product.h"
#include "TaxableProduct.h"
using namespace std;
namespace w7 {

	TaxableProduct::TaxableProduct() : rate(0) {}

	TaxableProduct::TaxableProduct(string& p_prodNum, double& p_price, const char p_rate) : Product(p_prodNum, p_price) {
		rate = p_rate;
	}

	double TaxableProduct::getCharge() const{

		switch (rate) {
		case 'P':
			return (price * (1 + taxRate[1]));
			break;

		default:
			return (price * (1 + taxRate[0]));
			break;
		}
	}

	void TaxableProduct::display(ostream& os) const {
		Product::display(os);	
		os << rate << "ST";
	}	
}