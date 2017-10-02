#include <iostream>
#include <fstream>
#include <string>
#include "Text.h"
using namespace std;

namespace w3 {
	Text::Text() : lines(0), line(nullptr){}
	
	Text::Text(const char* filename):Text() {
		fstream file;
		file.open(filename, file.in);
		if (file) {
			string l;
			while (getline(file, l)) {
				lines++;
			}
			file.clear();
			file.seekg(0);
			line = new string[lines++];
			for (unsigned i = 0; getline(file, l) && i < lines; i++) {
				size_t f = l.find(r);
				if (f != string::npos) {
					l.erase(f);
				}
				line[i] = l;
			}
		}		
		file.clear();
		file.close();
	}

	Text::Text(Text& tr) {
		*this = tr;
	}

	Text::Text(Text&& tr) {
		*this = move(tr);
	}
	
	Text& Text::operator=(Text& tr) {
		if (this != &tr) {
			lines = tr.lines;
			delete[] line;
			line = new string[lines];
			for (unsigned i = 0; i < lines; i++) {
				line[i] = tr.line[i];
			}
		}
		return *this;
	}

	Text&& Text::operator=(Text&& tr) {
		if (this != &tr) {
			lines = tr.lines;
			line = tr.line;

			tr.line = nullptr;
			tr.lines = 0;

		}
		return std::move(*this);
	}

	Text::~Text() {
		delete [] line;
	}

	size_t Text::size() const {	
		return lines;
	}

}