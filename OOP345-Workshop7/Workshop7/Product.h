#pragma once
#include <iostream>
#include <string>
#include "iProduct.h"

namespace w7 {

	class Product : public iProduct {
	private:
		std::string prodNum;
	protected:
		double price;
	public: 
		Product();
		Product(std::string&, double&);
		double getCharge() const;
		void display(std::ostream&) const;

	};

}
