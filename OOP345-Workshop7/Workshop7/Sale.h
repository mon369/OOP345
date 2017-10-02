#pragma once
#include <iostream>
#include <string>
#include <list>
#include "iProduct.h"

namespace w7 {
	class Sale {


		char* filename;
		int noOfProducts = 0;
		std::list<iProduct*> products;
	public:
		Sale(const char*);
		void display(std::ostream&) const;

		~Sale();
	};

}
