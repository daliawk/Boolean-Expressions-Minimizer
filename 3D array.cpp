#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
int  threeDarray(int** parameter,vector<int>** values,int RS,int CS)
{
	int count = 0;
	int digitnum = 0;
	for (int r = 1; r < 3; r++)
	{
		for (auto c = 0; c < sizeof(parameter[r]); c++)
		{
			if (parameter[r][c] > digitnum)
				digitnum = parameter[r][c];
		}
	}
	digitnum = sqrt (digitnum + 1) ;
	vector<int>** mergingarray;
	for (int q = 0; q < RS; q++)
	{
		int num1 = 0;
		int digit;
		while (count < digitnum)
		{
			digit = values[q][0] % 10;
			values[q][0] /= 10;
			if (digit == 1)
				num1++;
			count++;
		}
		values[q][1] = num1;
	}
	for (int s = 0; s < RS; s++)
	{
		vector<int> x, y;
		if (values[s][1] > values[s + 1][1])
		{
			x = values[s][0];
			y = values[s][1];
			values[s][1] = values[s + 1][1];
			values[s][0] = values[s + 1][0];
			values[s + 1][0] = x;
			values[s][1] = y;
		}
	}
	for (int q = 0; q < digitnum; q++)
	{
		int d = 0;
		count = 0;
		while (count < digitnum)
		{
			for (int s = 0; s < RS; s++)
			{
				if (count == values[s][1])
				{
					mergingarray[q][d] = values[s][0];
					d++;
				}
			}
			count++;
		}
	}
}