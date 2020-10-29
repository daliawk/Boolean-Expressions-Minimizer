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
	int checkmerg (int y);
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
int checkmerg (int x, int Y)
{
	int d1,d2;
	int dp = 0;
	int numofdif = 0;
	int count = 0;
	while (count < size)
	{
		if (numofdif <= 1)
		{
			d1 = x % 10;
			x /= 10;
			d2 = y % 10;
			y /= 10;
			if (d1 != d2)
			{
				dp++;
				numofdif++;
			}
		}
		else
		{
			return -1;
		}
		count++;
	}
	return dp;
}
#endif