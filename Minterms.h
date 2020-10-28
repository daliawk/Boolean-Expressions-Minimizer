#ifndef MINTERMS
#define MINTERMS
#include <iostream>
#include <vector>

using namespace std;


class Minterms {
private:
	vector<int> values;
	vector<char> digits;
	int numOnes;
	int size;
	bool minterm;
public:
	Minterms() { numOnes = 0; size = 0; }
	Minterms(int value, bool min, int s);
	void SetUp(int value, bool min, int s);
	void decToBinary();
	int NumberOnes() { return numOnes; }
	void printBinary() { for (int i = 0; i < size; i++) cout << digits[i]; }
};


Minterms::Minterms(int value, bool min, int s) {
	values.push_back(value);
	minterm = min;
	size = s;
	digits.resize(s);
}

void Minterms::SetUp(int value, bool min, int s) {
	values.push_back(value);
	minterm = min;
	size = s;
	digits.resize(s);
	decToBinary();

	numOnes;
	for (int i = 0; i < size; i++) {
		if (digits[i] == 0) {
			numOnes++;
		}
	}
}

void Minterms::decToBinary()
{
	int n = values[0];

	int i = 0;
	while (n > 0) {

		digits[i] = n % 2;
		n = n / 2;
		i++;
	}

	cout << endl;
	for (int j = i - 1; j >= 0; j--)
		cout << digits[j];
	cout << endl;
}

#endif