#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Product.h"


namespace w7 {


	class TaxableProduct : public Product {
		double taxRate[2] = { 0.13, 0.08 };
		char rate;

	public:
		TaxableProduct();
		TaxableProduct(std::string&, double&, const char);
		double getCharge() const;
		void display(std::ostream&) const;
	};

}