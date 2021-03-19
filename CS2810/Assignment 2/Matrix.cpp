/**************************************************************************************
 * 
 * $id$
 * File : Matrix.cpp -- contains definitions of member functions in matrix class 
 * 
 * Purpose : program execution begins here
 * Version : 1.0
 * Author : Vedant Ashish Saboo , CS19B074
 * Created : 
 * Last Modified :
 * 
 * Bugs :
 * 
 ***************************************************************************************/

#include <iostream>
#include "Matrix.h"
using namespace std;

/****************************************************************************************
 * START OF CLASS DEFINITION:
 * CLASS NAME : Matrix
 * PUBLIC FUNCTIONS : readData, binarySearch, matrixSearch, searchFor
 * 
 ****************************************************************************************/
    Matrix::Matrix(int mRows, int mCols) { //constructor
        rows = mRows;
        cols = mCols;
        grid = new ElemType*[mRows]; //allocate space dynamically
        for(int i = 0; i < mRows; i++) {
            grid[i] = new ElemType[mCols]; //allocate space dynamically
        }
    }
    void Matrix::readData() { //reads data from the STDIN and assigns to the matrix
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                cin >> grid[i][j];
            }
        }
    }
    int Matrix::binarySearch(ElemType elem, int row) { //uses binary search algorithm to return index to largest element in given row less than or equal to given element, and return -1 if not found
        
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
    Pair Matrix::matrixSearch(ElemType elem) { //searches for an element in the matrix and returns the array indices of the first element found in row major order
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
    int Matrix::searchFor(ElemType elem, int row) { //applies binary search to find an element in the given row. Returns first element found from the left end.
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
/********************************************************************
 * $log$
 * 
 * END OF FILE -- Matrix.cpp
 * 
 *****************************************************************************/