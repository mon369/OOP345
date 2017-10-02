#include <iostream>
#include "Notifications.h"
#include "Message.h"
using namespace std;

namespace w5 {
	Notifications::Notifications()
	{
		tweets = new Message[MAX_TWEETS];
		numTweets = 0;
	}

	void Notifications::operator+=(const Message& tweet) {

		
		if (numTweets < MAX_TWEETS) {
			tweets[numTweets] = tweet;
			numTweets++;
		}

	}

	void Notifications::display(ostream& os) const {


		for (unsigned int tweet = 0; tweet < numTweets; tweet++) {
			tweets[tweet].display(os);
		}
	}

	Notifications::Notifications(Notifications& nr) {

		*this = nr;
	}

	Notifications& Notifications::operator=(Notifications& nr) {
		if (this != &nr) {
			//Shallow Copies
			numTweets = nr.numTweets;
			delete[] tweets;

			tweets = new Message[numTweets];
			for (unsigned int tweet = 0; tweet < numTweets; tweet++) {
				tweets[tweet] = nr.tweets[tweet];
			}
			
		}
		return *this;
	}

	Notifications::~Notifications() {
		numTweets = 0;
		delete[] tweets;
	}

}