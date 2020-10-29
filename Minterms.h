#define MINTERMS
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


class Minterms {
private:
	vector<int> values;
	vector<string> digits;
	int numOnes;
	int size;
	bool minterm;
public:
	Minterms() { numOnes = 0; size = 0; }
	Minterms(int value, bool min, int s);
	void SetUp(int value, bool min, int s);
	void decToBinary();
	int NumberOnes() { return numOnes; }
	void printBinary() { for (int i = size - 1; i >= 0; i--) cout << digits[i]; cout << endl; }
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

	for (int i = 0; i < s; i++) {
		digits[i] = "0";
	}

	decToBinary();

	numOnes;
	for (int i = 0; i < size; i++) {
		if (digits[i] == "0") {
			numOnes++;
		}
	}
}

void Minterms::decToBinary()
{
	int n = values[0];

	int i = 0;
	while (n > 0) {

		digits[i] = to_string(n % 2);
		n = n / 2;
		i++;
	}
	/*
		cout << endl;
		for (int j = size-1; j>=0; j--)
			cout << digits[j];
		cout << endl;
		*/
}

#endif