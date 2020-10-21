#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Minterms {
private:
	vector<int> values;
	int digits;
	bool minterm;
public:
	Minterms(int value, bool min );
};


Minterms::Minterms(int value, bool min) {
	values.push_back(value);
	minterm = min;
}