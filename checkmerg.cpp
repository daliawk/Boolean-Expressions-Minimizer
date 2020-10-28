#include <iostream>
#include <vector>
using namespace std;
int checkmerg(vector <int> x, vector <int> y,int dn)
{
	int d1,d2;
	int dp = 0;
	int numofdif = 0;
	int count = 0;
	while (count < dn)
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