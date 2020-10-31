#ifndef MINTERMS
#define MINTERMS
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


class Minterms {
private:
	vector<int> values; //Decimal value of the minterm or values of minterms
	vector<string> digits; //Binary digits of the minterm or merged minterms
	int numOnes; //number of ones in the binary value
	int size; //Number of variables aka number of binary digits
	bool merged; //If this minterm has been merged with another minterm or not
public:
	Minterms() { numOnes = 0; size = 0; merged = false; } //Constructor
	Minterms(vector<string> newbinary); //Constructs a merged minterm
	void SetUp(int value, int s); //Modifier to set the private values
	void DecToBinary(); //Sets the binary value of the minterm from its decimal value
	int NumberOnes() { return numOnes; }
	void printBinary() { for (int i = size - 1; i >= 0; i--) cout << digits[i]; cout << endl; }
	vector <string> getdigits() { return digits; }
	int checkmerg(Minterms object); //Checks if 2 minterms are eligible for merging
	Minterms Merge(Minterms& object1, int position); //Merges 2 minterms
	void Add_Decimal_Value(int number) { values.push_back(number); }
	void printDecimal() { for (int i = 0; i < values.size(); i++) cout << values[i] << ", "; cout << endl; }
	int NumberOfDecimal() { return values.size(); }
	int GetDecimal(int position) { return values[position]; }
	void BooleanExpression(); //Prints the minterm or merged minterms as a boolean expression
	bool isMerged() { return merged; }
};


void Minterms::SetUp(int value, int s) {
	values.push_back(value);
	size = s;
	digits.resize(s);

	for (int i = 0; i < s; i++) {
		digits[i] = "0";
	}

	DecToBinary();

	numOnes = 0;
	for (int i = 0; i < size; i++) {
		if (digits[i] == "1") {
			numOnes++;
		}
	}
	merged = false;
}

void Minterms::DecToBinary()
{
	int n = values[0];

	int i = 0;
	while (n > 0) {

		digits[i] = to_string(n % 2);
		n = n / 2;
		i++;
	}

}
int Minterms::checkmerg(Minterms object) //Returns -1 if not eligble to merge, otherwize, returns the position of the different digit
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

Minterms Minterms::Merge(Minterms& object1, int position) {
	vector<string> mergestring(size); //Binary digits of the new merged minterm

	for (int i = 0; i < size; i++) { //adds * in the place of the different digit
		if (i == position)
			mergestring[i] = "*";
		else
			mergestring[i] = object1.digits[i];
	}

	Minterms object2(mergestring);//declares the merged object

	for (int i = 0; i < object1.values.size(); i++) { //Adds decimal values of minterms in the merged minterm
		object2.values.push_back(object1.values[i]);
		object2.values.push_back(this->values[i]);
	}

	this->merged = true;
	object1.merged = true;


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

	merged = false;
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

