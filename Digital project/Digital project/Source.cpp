#include <iostream> 
#include <vector>
using namespace std;

void decToBinary(int n,int *arr)
{
 
    int binaryNum[32];
    int storebin[100];
    int row;
    int col;
   
    int i = 0;
    while (n > 0) {

        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 

    for (int j = i - 1; j >= 0; j--)
        storebin[i]= binaryNum[j]; //Putting the whole binary value in one block

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            arr[j][i]=storebin[i];  //putting every binary value in teh columns but not arranged 

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {
            //check merge if true:{

        }
    //arr[i][j + 1] = merged value;
        
    }





