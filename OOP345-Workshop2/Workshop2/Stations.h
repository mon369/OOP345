#pragma once
#include <fstream>
#include <string>
#include "Station.h"

namespace w2 {

	class Stations {
	
	private:

		std::fstream file;
		int noStations;
		Station* stations;


	public:
		Stations();
		Stations(const char*);
		~Stations();

		void update() const;;
		void restock() const;
		void report() const;
	};
}