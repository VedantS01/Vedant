/**************************************************************************************
 * 
 * $id$
 * File : main.cpp -- main function resides here 
 * 
 * Purpose : contains main
 * Version : 1.0
 * Author : Vedant Ashish Saboo , CS19B074
 * Created : 9/2/2021 12:31 PM
 * Last Modified :
 * 
 * Bugs :
 * 
 ***************************************************************************************/

#include <iostream>
#include "MatrixMedian.h"
using namespace std;

/**************************************************************
 * 
 * Main : Program execution begins here
 * Args :
 * Returns : int
 * 
 * Bugs :
 **************************************************************/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    const string MS = "MS", BS = "BS", Median = "Median";
    int mRows, mCols;
    int numQueries;
    cin >> mRows;
    cin >> mCols;
    MatrixMedian matrixMedian(mRows,mCols);
    matrixMedian.readData();
    cin >> numQueries;
    string query;
    ElemType param1;
    int param2;
    while(numQueries > 0) {
        cin >> query;
        if(query == MS) {
            cin >> param1;
            cout << matrixMedian.matrixSearch(param1).i << " " << matrixMedian.matrixSearch(param1).j << "\n";
        } else if (query == BS) {
            cin >> param1 >> param2;
            cout << matrixMedian.binarySearch(param1, param2) << "\n";
        } else if (query == Median) {
            cout << matrixMedian.findMedian() << "\n";
        }
        numQueries--;
    }

    return 0;
}
/************************************
 * END OF MAIN
 * 
 **************************************/