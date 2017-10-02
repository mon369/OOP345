#include <iostream>
#include <string>
#include <fstream>
#include "Message.h"
using namespace std;

namespace w5 {

	Message::Message() {}

	Message::Message(ifstream& is, const char delim) {
		if (is.eof()) {
			is.close();
		}
		getline(is, tweet, delim);

		if (!empty()) {

			const char cr = '\r';
			if (tweet.find(cr) != string::npos) {
				tweet.erase(cr);
			}
			parse(tweet);
		}

	}

	bool Message::empty() const {
		const char space = ' ';
		return (tweet.find(space) == string::npos);
	}
	void Message::display(ostream& os) const {


		cout << from << endl;
		if (to.length() > 0 ) {
			cout << to << endl;

		}
		cout << message << endl;
		cout << "----------" << endl;



	}

	void Message::parse(string tweet) {
		const char space = ' ';
		const char at = '@';
		size_t index = 0;
		while (index < tweet.size() && tweet[index] != space) {
			from += tweet[index];
			index++;
		}
		index++;
		if (tweet[index] == at) {
			while (index < tweet.size() && tweet[index] != space) {
				to += tweet[index];
				index++;
			}
			index++;
		}

		while (index < tweet.size()) {
			message += tweet[index];
			index++;
		}




	}
}