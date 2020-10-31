#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Minterms.h"
using namespace std;

void QuineMcCluskey(string name);
void ImplicationTable(vector<vector<vector<Minterms>>>& table, vector<Minterms>& unmerged, int& var);
void ConstructChart(vector<Minterms> originalListOfMin, int numMinterms, vector<Minterms> originalPI, vector<vector<bool>>& chart);
void SolveTable(vector<Minterms> originalListOfMin, vector<Minterms> originalPI, vector<Minterms>& simplifiedVariables, vector<vector<bool>>& chart);
void CheckDominatedRows(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart);
void CheckDominatingColumns(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart);
void Sort(vector<int>& vec);
void PrintChart(vector<vector<bool>> chart);
bool Find(vector<int> vec, int x);
bool MergedDuplicate(vector<Minterms> list, Minterms object);
bool IsCoveredByEPI(int EPIPosition, int otherPosition, vector<vector<bool>>& chart);

int main() {
	cout << "Test Case 1:\n";
	QuineMcCluskey("Test.txt");
	cout << endl;

	cout << "Test Case 2:\n";
	QuineMcCluskey("Test2.txt");
	cout << endl;

	cout << "Test Case 3:\n";
	QuineMcCluskey("Test3.txt");
	cout << endl;

	cout << "Test Case 4:\n";
	QuineMcCluskey("Test4.txt");
	cout << endl;

	cout << "Test Case 5:\n";
	QuineMcCluskey("Test5.txt");
	cout << endl;

	cout << "Test Case 6:\n";
	QuineMcCluskey("Test6.txt");
	cout << endl;

	cout << "Test Case 7:\n";
	QuineMcCluskey("Test7.txt");
	cout << endl;

	cout << "Test Case 8:\n";
	QuineMcCluskey("Test8.txt");
	cout << endl;

	cout << "Test Case 9:\n";
	QuineMcCluskey("Test9.txt");
	cout << endl;

	cout << "Test Case 10:\n";
	QuineMcCluskey("Test10.txt");
	cout << endl;

	return 0;
}

void QuineMcCluskey(string name) {
	vector<vector<int>> minAdont(3); //The 3 line in the file
	string line;
	ifstream myfile;

	myfile.open(name);

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
	vector<Minterms> onlyMinterms;
	int numMinterms, numDontCares; //To carry number of minterms and number of don't cares
	int variables = minAdont[0][0];

	numMinterms = minAdont[1].size();
	numDontCares = minAdont[2].size();

	mintermsList.resize(numMinterms + numDontCares);
	onlyMinterms.resize(numMinterms);

	for (int i = 0; i < numMinterms + numDontCares; i++) {
		if (i < numMinterms) {
			mintermsList[i].SetUp(minAdont[1][i], variables);
			onlyMinterms[i].SetUp(minAdont[1][i], variables);
		}
		else
			mintermsList[i].SetUp(minAdont[2][i - numMinterms], variables);
	}

	objects[0].resize(variables + 1);//The first 2D table will have number of rows equal to all possible number of 1s

	for (int i = 0; i <= variables; i++) {
		for (int j = 0; j < mintermsList.size(); j++) {
			if (mintermsList[j].NumberOnes() == variables - i) {
				objects[0][i].push_back(mintermsList[j]);

			}
		}
	}

	ImplicationTable(objects, unmerged, variables);


	vector<Minterms>simplifiedVariables;
	vector<vector<bool>> tickChart;
	ConstructChart(onlyMinterms, numMinterms, unmerged, tickChart);

	SolveTable(onlyMinterms, unmerged, simplifiedVariables, tickChart);

	cout << "Simplified Boolean Expression= ";
	for (int i = 0; i < simplifiedVariables.size(); i++) {
		simplifiedVariables[i].BooleanExpression();
		if (i != simplifiedVariables.size() - 1) {
			cout << " + ";
		}
	}
	cout << endl;
}

void ImplicationTable(vector<vector<vector<Minterms>>>& table, vector<Minterms>& unmerged, int& var) {
	bool anyMerge = true;
	bool mergePerMinterm;
	int impColumn = 0; //First column in implication table aka first 2D tabel in 3D table

	while (anyMerge) {
		anyMerge = false;
		table.resize(impColumn + 2);
		table[impColumn + 1].resize(var - impColumn);


		for (int row = 0; row < table[impColumn].size() - 1; row++) {

			for (int v1 = 0; v1 < table[impColumn][row].size(); v1++) {


				for (int v2 = 0; v2 < table[impColumn][row + 1].size(); v2++) {
					//Call class function to check eligibility to merge
					int position = table[impColumn][row][v1].checkmerg(table[impColumn][row + 1][v2]);

					//if eligible call merge function and anyMerge=true and mergePerMinterm true
					if (position != -1) {

						anyMerge = true;
						Minterms mergedObject = table[impColumn][row][v1].Merge(table[impColumn][row + 1][v2], position);

						if (!MergedDuplicate(table[impColumn + 1][mergedObject.NumberOnes()], mergedObject)) {
							table[impColumn + 1][mergedObject.NumberOnes()].push_back(mergedObject);
						}
					}
				}
			}




		}

		for (int row = 0; row < table[impColumn].size(); row++) {
			for (int v1 = 0; v1 < table[impColumn][row].size(); v1++) {
				if (!table[impColumn][row][v1].isMerged()) {
					unmerged.push_back(table[impColumn][row][v1]);
				}
			}
		}

		impColumn++;
	}



	cout << "Prime Implicants: \n";
	for (int i = 0; i < unmerged.size(); i++) {
		for (int j = 0; j < unmerged[i].NumberOfDecimal(); j++) {
			cout << unmerged[i].GetDecimal(j);

			if (j != unmerged[i].NumberOfDecimal() - 1) {
				cout << ", ";
			}
			else
				cout << " -> ";
		}
		unmerged[i].printBinary();
	}
	cout << endl;
}

void ConstructChart(vector<Minterms> originalListOfMin, int numMinterms, vector<Minterms> originalPI, vector<vector<bool>>& chart) {
	chart.resize(originalPI.size());

	for (int i = 0; i < originalPI.size(); i++) {
		chart[i].resize(numMinterms);
		for (int j = 0; j < numMinterms; j++) {
			for (int r = 0; r < originalPI[i].NumberOfDecimal(); r++) {
				if (originalPI[i].GetDecimal(r) == originalListOfMin[j].GetDecimal(0)) {
					chart[i][j] = true;

				}

			}
		}

	}
}



void SolveTable(vector<Minterms> originalListOfMin, vector<Minterms> originalPI, vector<Minterms>& simplifiedVariables, vector<vector<bool>>& chart) {
	bool recursive = false;
	bool firstRound = true;

	do {
		vector<int> minimizedPIPosition;
		int possibleChosen;


		int numMinterms = originalListOfMin.size();
		int number_of_merged = originalPI.size(); //number of rows in the chart

		//Search for essentials
		for (int j = 0; j < numMinterms; j++) {
			int occurance = 0;
			for (int i = 0; i < number_of_merged; i++) {
				if (chart[i][j]) {
					occurance++;
					possibleChosen = i;
				}
			}
			if (occurance == 1) {
				if (!Find(minimizedPIPosition, possibleChosen)) {
					minimizedPIPosition.push_back(possibleChosen);
					recursive = true;

				}
			}
		}

		Sort(minimizedPIPosition);

		//Adding essentials
		vector<int> includedMintermsPositions;
		for (int r = minimizedPIPosition.size() - 1; r >= 0; r--) {
			int row = minimizedPIPosition[r];

			simplifiedVariables.push_back(originalPI[row]);

			for (int i = 0; i < numMinterms; i++) {
				if (chart[row][i]) {
					includedMintermsPositions.push_back(i);
					//cout << i << " ";
				}
			}


		}


		//Find and print essential PI and PI not covered by them
		if (firstRound) {
			firstRound = false;

			//Printing essential PI
			cout << "Essential PI: \n";
			for (int i = 0; i < minimizedPIPosition.size(); i++) {
				originalPI[minimizedPIPosition[i]].BooleanExpression();
				cout << endl;
			}
			cout << endl;

			//Printing minterms that are not covered by essential PI
			cout << "Minterms not covered by essential PI: \n";
			for (int i = 0; i < number_of_merged; i++) {
				bool covered = false;
				for (int x = 0; x < minimizedPIPosition.size(); x++) {
					if (IsCoveredByEPI(minimizedPIPosition[x], i, chart)) {
						covered = true;
					}
				}

				if (!covered) {
					originalPI[i].BooleanExpression();
					cout << endl;
				}
			}
			cout << endl;

		}


		//Erasing rows from chart
		for (int r = minimizedPIPosition.size() - 1; r >= 0; r--) {
			int row = minimizedPIPosition[r];
			originalPI.erase(originalPI.begin() + row);
			chart.erase(chart.begin() + row);
			number_of_merged--;
		}

		Sort(includedMintermsPositions);
		int lastValue = 1000000;
		for (int j = includedMintermsPositions.size() - 1; j >= 0; j--) {
			if (includedMintermsPositions[j] != lastValue) {
				originalListOfMin.erase(originalListOfMin.begin() + includedMintermsPositions[j]);

				numMinterms--;
				for (int i = 0; i < number_of_merged; i++) {
					chart[i].erase(chart[i].begin() + includedMintermsPositions[j]);

				}

				lastValue = includedMintermsPositions[j];
			}
		}
		if (originalListOfMin.empty()) {
			recursive = false;
		}



		CheckDominatingColumns(originalListOfMin, originalPI, chart);
		CheckDominatedRows(originalListOfMin, originalPI, chart);


	} while (recursive);


}

void CheckDominatingColumns(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart) {
	vector<int> dominatingColumns;
	int number_of_merged = originalPI.size();
	int numMinterms = originalListOfMin.size();

	for (int j = 0; j < numMinterms; j++) {
		int occurance = 0;
		for (int i = 0; i < number_of_merged; i++) {
			if (chart[i][j]) {
				occurance++;
			}
		}
		if (occurance == number_of_merged) {
			dominatingColumns.push_back(j);
		}
	}

	for (int j = dominatingColumns.size() - 1; j >= 0; j--) {

		originalListOfMin.erase(originalListOfMin.begin() + dominatingColumns[j]);
		numMinterms--;
		for (int i = 0; i < number_of_merged; i++) {
			chart[i].erase(chart[i].begin() + dominatingColumns[j]);

		}
	}

}

void CheckDominatedRows(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart) {
	int ticksA, ticksB, similarities;
	vector<int> dominatedRows;
	int number_of_merged = originalPI.size();
	int numMinterms = originalListOfMin.size();
	bool varADominated;


	for (int i = 0; i < number_of_merged - 1; i++) {

		varADominated = false;

		for (int r = i + 1; r < number_of_merged; r++) {
			ticksA = 0;
			ticksB = 0;
			similarities = 0;

			for (int j = 0; j < numMinterms; j++) {
				if (chart[i][j] && chart[r][j]) {
					similarities++;
					ticksB++;
					ticksA++;

				}
				else {
					if (chart[r][j]) {
						ticksB++;
					}
					if (chart[i][j]) {
						ticksA++;
					}
				}
			}

			if (ticksA < ticksB) {
				if (ticksA == similarities) {
					if (!varADominated) {
						dominatedRows.push_back(i);
						varADominated = true;
					}
				}

			}
			else {
				if (ticksB == similarities) {
					chart.erase(chart.begin() + r);
					originalPI.erase(originalPI.begin() + r);

					r--;
					number_of_merged--;

				}
			}
		}
	}


	for (int i = dominatedRows.size() - 1; i >= 0; i--) {
		chart.erase(chart.begin() + dominatedRows[i]);
		originalPI.erase(originalPI.begin() + dominatedRows[i]);

	}

}


void Sort(vector<int>& vec)
{
	int key, j;
	for (int i = 1; i < vec.size(); i++)
	{
		key = vec[i];
		j = i - 1;

		while (j >= 0 && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			j = j - 1;
		}
		vec[j + 1] = key;
	}
}

void PrintChart(vector<vector<bool>> chart) {
	for (int i = 0; i < chart.size(); i++) {
		for (int j = 0; j < chart[i].size(); j++) {
			if (chart[i][j]) {
				cout << "X";

			}
			else {
				cout << "*";
			}
		}
		cout << endl;
	}
}

bool Find(vector<int> vec, int x)
{
	for (int i = 0; i < vec.size(); i++)
		if (vec[i] == x)
			return true;
	return false;
}

bool MergedDuplicate(vector<Minterms> list, Minterms object) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].getdigits() == object.getdigits()) {
			return true;
		}
	}

	return false;
}

bool IsCoveredByEPI(int EPIPosition, int otherPosition, vector<vector<bool>>& chart) {
	for (int i = 0; i < chart[0].size(); i++) {
		if (chart[otherPosition][i] && !chart[EPIPosition][i]) {
			return false;
		}
	}
	return true;
}