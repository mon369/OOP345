#pragma once
#include <iostream>

namespace w5 {
	class Message {

		std::string tweet;
		std::string from;
		std::string to;
		std::string message;

	public: 

		Message();
		Message(std::ifstream&, const char);
		bool empty() const;
		void display(std::ostream&) const;

	private:
		void parse(std::string);

	};

}