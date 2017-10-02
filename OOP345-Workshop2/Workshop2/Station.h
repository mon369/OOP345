#pragma once
#include <iostream>
#include <string>

namespace w2 {
	enum PassType { Student, Adult };
	class Station {
	private:
		std::string station;
		unsigned int noStd = 0;
		unsigned int noAdt = 0;
	public:
		Station();
		void set(const std::string&, unsigned, unsigned);
		const std::string& getName() const;
		unsigned inStock(PassType) const;
		void update(PassType, int);


	};
}