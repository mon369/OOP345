#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <cmath>
using namespace std;

namespace w8 {
	template<class T>
	class DataTable {
	private:
		vector<T> x_coordinates;;
		vector<T> y_coordinates;
		size_t dataSize = 0;
		int outputWidth, decimalPlaces;
		T x_sum = 0, y_sum = 0, xx_sum = 0, xy_sum = 0;
		T y_mean = 0;
		T y_sigma = 0;
	public:
		DataTable() {}
		DataTable(ifstream& ifile, const int p_fw, const int p_nw) {
			outputWidth = p_fw;
			decimalPlaces = p_nw;
			T x, y;
			while (ifile >> x >> y) {
				x_coordinates.push_back(move(x));
				y_coordinates.push_back(move(y));
				++dataSize;
			}
			if (!dataSize) {
				throw string("Error, no data has been read");
			}
			if (x_coordinates.empty() || y_coordinates.empty()) {
				throw string("Error initializing X and Y coordinates");
			}
			x_sum = accumulate(x_coordinates.begin(), x_coordinates.end(), (T)0);
			y_sum = accumulate(y_coordinates.begin(), y_coordinates.end(), (T)0);
			auto square_elements = [](T x, T y) { return x + y * y; };
			xx_sum = accumulate(x_coordinates.begin(), x_coordinates.end(), (T)0, square_elements);
			y_mean = y_sum / dataSize;
			for (size_t i = 0; i < dataSize; i++) {
				xy_sum += x_coordinates.at(i) * y_coordinates.at(i);
			}
		}
		void regression(T& slope, T& y_intercept) const {
			
			slope = ((dataSize*xy_sum)-(x_sum*y_sum))/((dataSize*xx_sum)-(x_sum*x_sum));
			y_intercept = (y_sum - (slope*x_sum)) / dataSize;	
		}
		void display(ostream& os) const {
			os << fixed<< setprecision(decimalPlaces);
			for (size_t i = 0; i < dataSize; i++) {
				os << "X: " << x_coordinates.at(i) << " Y: " << y_coordinates.at(i) << endl;
			}
		}
		T mean() const {
			return y_mean;
		}
		T sigma() const {
			vector<T> y_transform;
			y_transform.resize(dataSize);
			transform(y_coordinates.begin(), y_coordinates.end(), y_transform.begin(), [&](T y) {
				return pow((y - y_mean), (T) 2);
			});
			auto sum = accumulate(y_transform.begin(), y_transform.end(), (T)0);		
			auto ssd = sqrt(sum / (dataSize - 1));
			return ssd;
		}
		T median() const {
			vector<T> y_sort(y_coordinates);
			sort(y_sort.begin(), y_sort.end());
			int m_index = (int)dataSize / 2;
			return y_sort.at(m_index);
		}
	};

	template<typename T>
	ostream& operator<<(ostream& os, const DataTable<T>& dt) {
		dt.display(os);
		return os;
	}
}