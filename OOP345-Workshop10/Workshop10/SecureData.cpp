// Workshop 10 - Multi-Threading
// SecureData.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <future>
#include "SecureData.h"

namespace w10 {


	SecureData::SecureData(const char* file, char key) {

		//Count the number of threads;
		int hwc = std::thread::hardware_concurrency();
		threadCount = (hwc > 3) ? 3 : hwc;
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

		int i = 0;
		while (input.good())
			input >> text[i++];
		text[--i] = '\0';
		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		
		//Create partitions before encrypt/decrypt
		createPartitions();
		//Set encoded flag to false
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	void SecureData::code(char key) {
		if (!encoded) std::cout << "ENCRYPTING..." << std::endl;
		else std::cout << "DECRYPTING..." << std::endl;
		std::vector<std::thread> threadList;

		auto converter = [](char* t, char key, int begin, int end, const Cryptor& c) {
			for (int i = begin; i <= end; i++) {
				t[i] = c(t[i], key);
			}
		};

		for (auto &p : partition) {
			std::cout << "Begin: " << p.begin << " End: " << p.end << std::endl;
			std::cout << "Creating thread..." << std::endl;
			auto c = std::bind(std::ref(converter), text, key, p.begin, p.end, Cryptor());
			threadList.emplace_back(c);
		}
		for (auto &t : threadList) {
			t.join();
		}
		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			// open binary file
			std::ofstream ofile;
			ofile.open(file, ofile.out | ofile.trunc);
			if (!ofile) {
				throw std::string("\n***Output file cannot be opened");
			}

			// write binary file here
			ofile << text;
			ofile.clear();
			ofile.close();
		}
	}

	void SecureData::restore(const char* file, char key) {
		// open binary file
		if (text) {
			delete[] text;
		}

		std::ifstream infile;
		infile.open(file, infile.in);
		if (!infile) {
			throw std::string("\n***File cannot be opened for restore");
		}

		// allocate memory here
		text = new char[nbytes+1];

		// read binary file here
		int i = 0;
		infile >> std::noskipws;
		while (infile.good()) {
			infile >> text[i++];
		}
		text[nbytes] = 0;

		infile.clear();
		infile.close();

		std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
			<< file << " into memory (null byte included)\n";
		encoded = true;

		// decode using key
		code(key);
		std::cout << "Data decrypted in memory\n\n";
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}

	void SecureData::createPartitions() {
		int begin = 0, end = 0;
		int textlen = (int)strlen(text);
		for (int i = 0; i < threadCount; i++) {
			begin = (textlen* i) / threadCount;
			end = ((textlen * (i + 1)) / threadCount) - 1;
			partition.emplace_back(begin, end);
		}
	}


}