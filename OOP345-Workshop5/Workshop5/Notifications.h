#pragma once
#include <iostream>
#include "Message.h"

namespace w5 {
	const unsigned int MAX_TWEETS = 10;
	class Notifications {
		Message* tweets;
		unsigned int numTweets;

	public: 
		Notifications();
		void operator+=(const Message&);
		void display(std::ostream& = std::cout) const;
		~Notifications();

		//COPY CONSTRUCTOR
		Notifications(Notifications&);
		//COPY ASSIGNMENT
		Notifications& operator=(Notifications&);
		
	};
}