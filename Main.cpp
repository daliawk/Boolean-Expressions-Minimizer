#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Minterms.h"
using namespace std;

void ImplicationTable(vector<vector<vector<Minterms>>>& table, vector<Minterms>& unmerged, int& var);

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
	vector<Minterms> unmerged;
	int numMinterms, numDontCares; //To carry number of minterms and number of don't cares
	int variables = minAdont[0][0];

	numMinterms = minAdont[1].size();
	numDontCares = minAdont[2].size();

	mintermsList.resize(numMinterms + numDontCares);

	for (int i = 0; i < numMinterms + numDontCares; i++) {
		if (i < numMinterms)
			mintermsList[i].SetUp(minAdont[1][i], true, variables);
		else
			mintermsList[i].SetUp(minAdont[2][i - numMinterms], false, variables);
	}

	objects[0].resize(variables + 1);//The first 2D table will have number of rows equal to all possible number of 1s

	for (int i = 0; i <= variables; i++) {
		for (int j = 0; j < mintermsList.size(); j++) {
			if (mintermsList[j].NumberOnes() == variables - i) {
				objects[0][i].push_back(mintermsList[j]);
				objects[0][i].back().printBinary();
			}
		}
	}

	ImplicationTable(objects, unmerged, variables);
}

void ImplicationTable(vector<vector<vector<Minterms>>>& table, vector<Minterms>& unmerged, int& var) {
	bool anyMerge = true;
	bool mergePerMinterm;
	int impColumn = 0; //First column in implication table aka first 2D tabel in 3D table

	while (anyMerge) {
		anyMerge = false;
		table.resize(impColumn + 2);
		table[impColumn + 1].resize(var);


		for (int row = 0; row < table[impColumn].size() - 1; row++) {
			cout << "Row\n";

			for (int v1 = 0; v1 < table[impColumn][row].size(); v1++) {
				mergePerMinterm = false;


				for (int v2 = 0; v2 < table[impColumn][row + 1].size(); v2++) {
					//Call class function to check eligibility to merge
					int position = table[impColumn][row][v1].checkmerg(table[impColumn][row + 1][v2]);

					//if eligible call merge function and anyMerge=true and mergePerMinterm true
					if (position != -1) {

						anyMerge = true;
						mergePerMinterm = true;
						Minterms mergedObject = table[impColumn][row][v1].Merge(table[impColumn][row + 1][v2], position);
						cout << "Merged\n";


						table[impColumn + 1][mergedObject.NumberOnes()].push_back(mergedObject);
						cout << "Added to other column\n";
					}
				}

				if (!mergePerMinterm) {
					unmerged.push_back(table[impColumn][row][v1]);
				}
			}
		}


		impColumn++;
	}

	for (int i = 0; i < table[impColumn].size(); i++) {
		for (int j = 0; j < table[impColumn][i].size(); j++) {
			unmerged.push_back(table[impColumn][i][j]);
		}
	}

	cout << "Prime Implicants: ";
	for (int i = 0; i < unmerged.size(); i++) {
		unmerged[i].printBinary();
	}
}