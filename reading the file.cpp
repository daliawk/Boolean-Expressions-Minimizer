#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int readfile()
{
	int** minAdont=new int [3];
	ofstream myfile;
	string filename,line;
	cout << "enter the file name: ";
	cin >> filename;
	myfile.open(filename);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			stringstream word (line);
			int* num;
			while (std::getline(word, num, ','))
			{
				for (int r = 0; r < 3; r++)
				{
					if (r == 0)
					{
						minAdont[r][0] = num;
					}
					else
					{
						for (int c = 0; c < sizeof (word); c++)
						{
							minAdont[r] = num;
						}
					}
				}
			}
	   }
	}
	else
	{
		cout << "The file didn't open";
	}
	myfile.close();
	return minAdont;
}