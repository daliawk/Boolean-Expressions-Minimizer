#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Minterms.h"
using namespace std;

void ImplicationTable(vector<vector<vector<Minterms>>>& table, vector<Minterms>& unmerged, int& var);
void ConstructChart(vector<Minterms> originalListOfMin, int numMinterms, vector<Minterms> originalPI, vector<vector<bool>>& chart);
void EPI2(vector<Minterms> originalListOfMin, vector<Minterms> originalPI, vector<Minterms>& EPIlist, vector<vector<bool>>& chart);
void CheckDominatedRows(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart);
void CheckDominatingColumns(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart);
void Sort(vector<int>& vec);
void PrintChart(vector<vector<bool>> chart);
bool Find(vector<int> vec, int x);
bool MergedDuplicate(vector<Minterms> list, Minterms object);

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

			}
		}
	}

	ImplicationTable(objects, unmerged, variables);

	//Testing EPI
	vector<Minterms> tempMinterms(6);
	tempMinterms[0].SetUp(2, true, 4);
	tempMinterms[1].SetUp(3, true, 4);
	tempMinterms[2].SetUp(7, true, 4);
	tempMinterms[3].SetUp(9, true, 4);
	tempMinterms[4].SetUp(11, true, 4);
	tempMinterms[5].SetUp(13, true, 4);

	vector<Minterms> tempPI(4);
	tempPI[0].SetUp(0, true, 4);
	tempPI[1].SetUp(0, true, 4);
	tempPI[2].SetUp(0, true, 4);
	tempPI[3].SetUp(0, true, 4);


	tempPI[0].SetBoolean("*", "0", "*", "1");
	tempPI[0].Add_Decimal_Value(1);
	tempPI[0].Add_Decimal_Value(3);
	tempPI[0].Add_Decimal_Value(9);
	tempPI[0].Add_Decimal_Value(11);

	tempPI[1].SetBoolean("*", "0", "1", "*");
	tempPI[1].Add_Decimal_Value(2);
	tempPI[1].Add_Decimal_Value(3);
	tempPI[1].Add_Decimal_Value(10);
	tempPI[1].Add_Decimal_Value(11);

	tempPI[2].SetBoolean("1", "*", "*", "1");
	tempPI[2].Add_Decimal_Value(9);
	tempPI[2].Add_Decimal_Value(11);
	tempPI[2].Add_Decimal_Value(13);
	tempPI[2].Add_Decimal_Value(15);

	tempPI[3].SetBoolean("*", "*", "1", "1");
	tempPI[3].Add_Decimal_Value(3);
	tempPI[3].Add_Decimal_Value(11);
	tempPI[3].Add_Decimal_Value(7);
	tempPI[3].Add_Decimal_Value(15);



	vector<Minterms>EPIlist;
	vector<vector<bool>> tickChart;
	//ConstructChart(tempMinterms, 6, tempPI, tickChart);

	//EPI2(tempMinterms, tempPI, EPIlist, tickChart);

	//cout << "Simplified Boolean Expression= ";
	//for (int i = 0; i < EPIlist.size(); i++) {
	//	EPIlist[i].BooleanExpression();
	//	if (i != EPIlist.size() - 1) {
	//		cout << " + ";
	//	}
	//}
}

void ImplicationTable(vector<vector<vector<Minterms>>>& table, vector<Minterms>& unmerged, int& var) {
	bool anyMerge = true;
	bool mergePerMinterm;
	int impColumn = 0; //First column in implication table aka first 2D tabel in 3D table

	while (anyMerge) {
		anyMerge = false;
		table.resize(impColumn + 2);
		table[impColumn + 1].resize(var + 1);


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

						if (!MergedDuplicate(table[impColumn + 1][mergedObject.NumberOnes()], mergedObject)) {
							table[impColumn + 1][mergedObject.NumberOnes()].push_back(mergedObject);
							cout << "Added to other column\n";
						}
					}
				}

				if (!mergePerMinterm) {
					unmerged.push_back(table[impColumn][row][v1]);
				}
			}
		}


		impColumn++;
	}

	//	for (int i = 0; i < table[impColumn].size(); i++) {
	//		for (int j = 0; j < table[impColumn][i].size(); j++) {
	//			unmerged.push_back(table[impColumn][i][j]);
	//		}
	//	}

	cout << "Prime Implicants: ";
	for (int i = 0; i < unmerged.size(); i++) {
		unmerged[i].printBinary();
	}
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
	cout << "Constructed chart\n";
}



void EPI2(vector<Minterms> originalListOfMin, vector<Minterms> originalPI, vector<Minterms>& EPIlist, vector<vector<bool>>& chart) {
	bool recursive = false;

	do {
		recursive = false;
		cout << "A recursion\n";
		vector<int> essentialPIPosition;
		int possibleEssential;

		PrintChart(chart);


		CheckDominatingColumns(originalListOfMin, originalPI, chart);
		CheckDominatedRows(originalListOfMin, originalPI, chart);


		int numMinterms = originalListOfMin.size();
		int number_of_merged = originalPI.size(); //number of rows in the chart

		cout << "Found essentials: ";
		//Search for essentials
		for (int j = 0; j < numMinterms; j++) {
			int occurance = 0;
			for (int i = 0; i < number_of_merged; i++) {
				if (chart[i][j]) {
					occurance++;
					possibleEssential = i;
				}
			}
			if (occurance == 1) {
				if (!Find(essentialPIPosition, possibleEssential)) {
					essentialPIPosition.push_back(possibleEssential);
					recursive = true;
					cout << possibleEssential << " ";
				}
			}
		}
		cout << " done\n";

		Sort(essentialPIPosition);

		//Adding essentials
		cout << "Added to EPI: \n";
		vector<int> includedMintermsPositions;
		for (int r = essentialPIPosition.size() - 1; r >= 0; r--) {
			int row = essentialPIPosition[r];

			EPIlist.push_back(originalPI[row]);

			cout << row << " with minterms ";

			for (int i = 0; i < numMinterms; i++) {
				if (chart[row][i]) {
					includedMintermsPositions.push_back(i);
					cout << i << " ";
				}
			}

			cout << "done\n";



			originalPI.erase(originalPI.begin() + row);
			chart.erase(chart.begin() + row);
			number_of_merged--;
			cout << "Erased " << row << endl << endl;
		}
		cout << "Added essentials\n";

		Sort(includedMintermsPositions);
		cout << "Erasing Minterms: \n";
		int lastValue = 1000000;
		for (int j = includedMintermsPositions.size() - 1; j >= 0; j--) {
			if (includedMintermsPositions[j] != lastValue) {
				originalListOfMin.erase(originalListOfMin.begin() + includedMintermsPositions[j]);
				cout << includedMintermsPositions[j] << " " << "done ";
				numMinterms--;
				for (int i = 0; i < number_of_merged; i++) {
					chart[i].erase(chart[i].begin() + includedMintermsPositions[j]);

				}
				cout << "done\n";
				lastValue = includedMintermsPositions[j];
			}
		}
		if (originalListOfMin.empty()) {
			recursive = false;
		}


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
	cout << "Erased dominating columns: ";
	for (int j = dominatingColumns.size() - 1; j >= 0; j--) {
		cout << dominatingColumns[j] << " ";
		originalListOfMin.erase(originalListOfMin.begin() + dominatingColumns[j]);
		numMinterms--;
		for (int i = 0; i < number_of_merged; i++) {
			chart[i].erase(chart[i].begin() + dominatingColumns[j]);

		}
	}
	cout << endl;
}

void CheckDominatedRows(vector<Minterms>& originalListOfMin, vector<Minterms>& originalPI, vector<vector<bool>>& chart) {
	int ticksA, ticksB, similarities;
	vector<int> dominatedRows;
	int number_of_merged = originalPI.size();
	int numMinterms = originalListOfMin.size();
	bool varADominated;

	cout << "Erased dominated rows: ";

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
					cout << r << " ";
					r--;
					number_of_merged--;

				}
			}
		}
	}


	for (int i = dominatedRows.size() - 1; i >= 0; i--) {
		chart.erase(chart.begin() + dominatedRows[i]);
		originalPI.erase(originalPI.begin() + dominatedRows[i]);
		cout << dominatedRows[i] << " ";
	}
	cout << "done\n";
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