/**************************************************************************************
 * 
 * $id$
 * File : MatrixElementsManipulations.cpp -- implements a class Matrix (sorted by rows) and another class MatrixMedian inherited from Matrix
 * 
 * Purpose : Processes user queries to perform binary searching in a row (sorted by default), matrix search, and finding median in most efficient way 
 * Version : 1.0
 * Author : Vedant Ashish Saboo , CS19B074
 * Created : 
 * Last Modified :
 * 
 * Bugs :
 * 
 ***************************************************************************************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long int ElemType;

typedef struct Pair {
    int i;
    int j;
} Pair;

/***************************************************************
 * 
 * Class :  Matrix -- realizes m * n matrix with rows sorted in non decreasing order
 * Data members (public) :
 * Member functions (public) : readData, binarySearch, matrixSearch, searchFor
 * 
 * Bugs :
 **************************************************************/
class Matrix {
    protected:
    int rows;
    int cols;
    ElemType** grid;
    private:
    public:
    const static int NOT_FOUND = -1;
    Matrix(int mRows, int mCols) { //constructor
        rows = mRows;
        cols = mCols;
        grid = new ElemType*[mRows]; //allocate space dynamically
        for(int i = 0; i < mRows; i++) {
            grid[i] = new ElemType[mCols]; //allocate space dynamically
        }
    }
    void readData() { //reads data from the STDIN and assigns to the matrix
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                cin >> grid[i][j];
            }
        }
    }
    int binarySearch(ElemType elem, int row) { //uses binary search algorithm to return index to largest element in given row less than or equal to given element, and return -1 if not found
        
        //Lets say the elements in the given row with the property that they are less than or equal to given element, belong to a certain CANDIDATE SET

        int beginIndex = 0, endIndex = cols - 1;
        int middleIndex;
        while(beginIndex <= endIndex) {
            middleIndex = (beginIndex + endIndex)/2;
            if(grid[row][middleIndex] <= elem) { //if the current element belongs to CANDIDATE SET
                if(middleIndex == endIndex) return middleIndex; //if it is at last, return its index. We have found it.
                if(grid[row][middleIndex + 1] > elem) return middleIndex; //if next element is out of CANDIDATE SET, return the current index. We have found it.
                beginIndex = middleIndex + 1; //search in the later half of the current segment
            } else {
                endIndex = middleIndex - 1; //search in the early half of the current segment
            }
        }
        return NOT_FOUND; //we reach here only when the CANDIDATE SET is empty. Return NOT_FOUND
    }
    Pair matrixSearch(ElemType elem) { //searches for an element in the matrix and returns the array indices of the first element found in row major order
        Pair pair;
        pair.i = NOT_FOUND;
        pair.j = NOT_FOUND;
        for(int i = 0; i < rows; i++) {
            int j = searchFor(elem, i); //searchFor applies binary search in peculiar way, to return the first element in the row major order
            if(j != -1) {
                pair.i = i;
                pair.j = j;
                break;
            }
        }
        return pair;
    }
    int searchFor(ElemType elem, int row) { //applies binary search to find an element in the given row. Returns first element found from the left end.
        int beginIndex = 0, endIndex = cols - 1;
        int middleIndex;
        while(beginIndex <= endIndex) {
            middleIndex = (beginIndex + endIndex)/2;
            if(grid[row][middleIndex] == elem) { //element found
                if(middleIndex == beginIndex) return middleIndex; //it the at leftmost of current segment, return current
                if(grid[row][middleIndex - 1] < elem) return middleIndex; //element to left is smaller than this, return currennt
                endIndex = middleIndex - 1; //element to left is also of same value, search in left half
            } 
            else if(grid[row][middleIndex] < elem) beginIndex = middleIndex + 1; //search in right half
            else endIndex = middleIndex - 1; //search in left half
        }
        return NOT_FOUND; //element not found
    }
};
/********************************************************************
 * END OF CLASS -- Matrix
 * 
 *********************************************************************/

/***************************************************************
 * 
 * Class :  MatrixMedian -- child of class Matrix
 * Data members (public) :
 * Member functions (public) : upperBound, findMedian, readData(inherited), binarySearch(inherited), matrixSearch(inherited), searchFor(inherited)
 * 
 * Bugs :
 **************************************************************/
class MatrixMedian : public Matrix {
    private:
    ElemType median;
    bool isMedianCalculated;
    public:
    MatrixMedian(int mRows, int mCols) : Matrix(mRows, mCols) {
        isMedianCalculated = false;
    }
    int upperBound(ElemType elem, int row) { //uses inherited binarySearch method to compute an upper bound indicator with respect to given element in a given row
        int j = 1 + binarySearch(elem, row);
        if(j >= cols) {
            j = NOT_FOUND;
        }
        return j;
    }
    /**
     * Time Complexity for findMedian :
     * The major steps are -
     * T1 : finding minimum and maximum values in the matrix -- O(n)
     * T2 : while loop for calculating number of elements less than or equal to current average of extreme elements, 
     *      and checking if this number is (m*n + 1)/2 -- O( (sizeof(ElemType) in bits + 1) * n * log m) => O(32 * n * log m)
     * T3 : Printing the value
     * 
     * Overall time complexity -- O(32 * n * log m)
     * Additional space complexity -- O(1)
     * 
     * Please note : according to problem statement, ElemType ranges from -2^31 to 2^31 -1 and hence, sizeof(ElemType) is effectively 31 bits
     **/
    ElemType findMedian() { //finds median in a matrix
        if(isMedianCalculated) { //bool to check if this process has been done before. 
                                 //Since this method will return fixed results provided that contents are retained, 
                                 //It will simply return the value calculated earlier
                                 //To be noted : the contents of the matrix don'numQueries change after once set.
            return median;
        }
        ElemType minValue = grid[0][0], maxValue = grid[0][cols-1]; 
        for (int i=1; i < rows; i++) {
            if (grid[i][0] < minValue) 
                minValue = grid[i][0]; 
  
            if (grid[i][cols-1] > maxValue) 
                maxValue = grid[i][cols-1]; 
        } 
        int midIndexPos = (rows * cols + 1) / 2;
        while (minValue <= maxValue) //this while loop should run in the worst case roughly less than log(range(ELemType)) + 1 => 32 in this case; a constant
        { 
            ElemType midValue = (maxValue + minValue) / 2; //current average of extremes
            int counter = 0;
  
            for (int i = 0; i < rows; ++i) // loop over each row -- O(n)
                counter += binarySearch(midValue, i) + 1; //elements in ith row less than or equal to midValue -- O(log m)
            if (counter < midIndexPos) 
                minValue = midValue + 1; 
            else
                maxValue = midValue - 1; 
        }
        median = minValue;
        isMedianCalculated = true;
        return minValue;
    }
};
/********************************************************************
 * END OF CLASS -- MatrixMedian
 * 
 *********************************************************************/

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