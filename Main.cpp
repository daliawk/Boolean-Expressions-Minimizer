#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Minterms.h"
using namespace std;


int main() {
	vector<vector<int>> minAdont(3);
	ifstream myfile;
	string filename, line;

	//cout << "enter the file name: ";
	//cin >> filename;
	myfile.open("Test.txt");

	string num;
	if (myfile.is_open())
	{
		int r = 0;
		while (!myfile.eof())
		{
			
			getline(myfile, line);
			stringstream word(line);
			
			while (getline(word, num, ','))
			{
				minAdont[r].push_back(stoi(num));
				
			}
			r++;
		}
	}
	else
	{
		cout << "The file didn't open";
		exit(1);
	}
	myfile.close();


	vector<vector<vector<Minterms>>> objects(1);
	vector<Minterms> mintermsList;
	int numMinterms, numDontCares; //To carry number of minterms and number of don't cares
	int variables = minAdont[0][0];

	numMinterms = minAdont[1].size();
	numDontCares = minAdont[2].size();

	mintermsList.resize(numMinterms + numDontCares);

	for (int i = 0; i < numMinterms + numDontCares; i++) {
		if(i<numMinterms)
			mintermsList[i].SetUp(minAdont[1][i], true, variables);
		else
			mintermsList[i].SetUp(minAdont[2][i-numMinterms], false, variables);
	}

	objects[0].resize(variables + 1);//The first 2D table will have number of rows equal to all possible number of 1s

	for (int i = 0; i <= variables; i++) {
		for (int j = 0; j < mintermsList.size(); j++) {
			if (mintermsList[j].NumberOnes() == variables - i) {
				objects[0][i].push_back(mintermsList[j]);
				mintermsList[j].printBinary();
			}
		}
	}


}