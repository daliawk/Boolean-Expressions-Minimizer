#ifndef MINTERMS
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
	vector <string> getdigits() { return digits; }
	int checkmerg(Minterms object);
	Minterms Merge(Minterms object1, int position);
	Minterms(vector<string> newbinary);
	void Add_Decimal_Value(int number) { values.push_back(number); }
	void printDecimal() { for (int i = 0; i < values.size(); i++) cout << values[i] << ", "; cout << endl; }
	int NumberOfDecimal() { return values.size(); }
	int GetDecimal(int position) { return values[position]; }
	void SetBoolean(string a1, string a2, string a3, string a4) { digits[0] = a4; digits[1] = a3; digits[2] = a2; digits[3] = a1; } //for testing
	void BooleanExpression();
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

	numOnes = 0;
	for (int i = 0; i < size; i++) {
		if (digits[i] == "1") {
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

}
int Minterms::checkmerg(Minterms object)
{
	int dp = 0;
	int numofdif = 0;
	int count = 0;
	while (count < size)
	{
		if (numofdif <= 1)
		{

			if (this->digits[count] != object.digits[count])
			{
				dp = count;
				numofdif++;
			}
		}
		else
		{
			return -1;
		}
		count++;
	}

	if (numofdif == 1)
		return dp;
	else
		return -1;
}

Minterms Minterms::Merge(Minterms object1, int position) {
	vector<string> mergestring(size);
	for (int i = 0; i < size; i++) {
		if (i == position)
			mergestring[i] = "*";
		else
			mergestring[i] = object1.digits[i];
	}
	Minterms object2(mergestring);

	for (int i = 0; i < object1.values.size(); i++) {
		object2.values.push_back(object1.values[i]);
		object2.values.push_back(this->values[i]);
	}
	this->printBinary();
	cout << "+" << endl;
	object1.printBinary();
	cout << "=\n";
	object2.printBinary();
	return object2;

}
Minterms::Minterms(vector<string>newbinary) {
	digits.resize(newbinary.size());
	size = newbinary.size();
	numOnes = 0;

	for (int i = 0; i < size; i++) {
		digits[i] = newbinary[i];
		if (digits[i] == "1")
			numOnes++;
	}
}


void Minterms::BooleanExpression() {
	string alpha = "ABCDEFGHIJKLMNOPQRSTUVXYZ";
	for (int i = 0; i < size; i++) {
		if (digits[size - 1 - i] == "0")
			cout << alpha[i] << "'";
		else if (digits[size - 1 - i] == "1")
			cout << alpha[i];
	}

}


#endif
