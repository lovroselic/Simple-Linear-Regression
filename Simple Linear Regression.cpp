// Simple Linear Regression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <cmath>
#include <cassert>
#include <limits>
#include <numeric>

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

vector<double> SLR(vector<long> x, vector<long> y);

int main() {
	auto t1 = high_resolution_clock::now();
	cout << "Simple Linear Regression v" << VERSION << "!\n\n";
	//string path = "Test.txt";
	string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	vector<long> x;
	vector<long> y;

	for (int i = 1; i < raw_data.size(); i++) {
		vector<string> line = splitString(raw_data[i], " ");
		x.push_back(stol(line[1]));
		y.push_back(stol(line[2]));
	}
	vector<double> coeff = SLR(x, y);
	cout << "\nSolution: " << joinVector(coeff, " ") << endl;;

	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

vector<double> SLR(vector<long> x, vector<long> y) {
	double slope = 0.0;
	double offset = 0.0;
	
	vector<long> xx;
	vector<long> xy;
	vector<long> yy;
	double N = x.size();
	for (int i = 0; i < N; i++) {
		xx.push_back(x[i] * x[i]);
		xy.push_back(x[i] * y[i]);
		yy.push_back(y[i] * y[i]);
	}
	long Sx = accumulate(x.begin(), x.end(), 0);
	long Sy = accumulate(y.begin(), y.end(), 0);
	long Sxx = accumulate(xx.begin(), xx.end(), 0);
	long Sxy = accumulate(xy.begin(), xy.end(), 0);
	long Syy = accumulate(yy.begin(), yy.end(), 0);

	slope = (N * Sxy - Sx * Sy) / (N * Sxx - Sx * Sx);
	offset = (1.0 / N) * Sy - slope * (1.0 / N) * Sx;
	
	return vector<double> { slope, offset };
}
