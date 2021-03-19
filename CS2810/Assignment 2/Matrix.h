/**************************************************************************************
 * 
 * $id$
 * File : Matrix.h -- contains declaration of class Matrix
 * 
 * Purpose : Class Matrix
 * Version : 1.0
 * Author : Vedant Ashish Saboo , CS19B074
 * Created : 
 * Last Modified :
 * 
 * Bugs :
 * 
 ***************************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "Pair.h"
#include "ElemType.h"
using namespace std;
#define AVERAGE_ERROR 0

/***************************************************************
 * 
 * Class :  Matrix -- realizes m * n matrix with rows sorted in non decreasing order
 * Data members (public) :
 * Member functions (public) : readData, binarySearch, matrixSearch, searchFor
 * 
 * Bugs :
 **************************************************************/
class Matrix {
    protected: //will be accessed by its derived classes as well
    int rows;
    int cols;
    ElemType** grid; //pointer to 2d array
    private:
    public:
    const static int NOT_FOUND = -1;
    Matrix(int, int);
    void readData(); //reads the data from STDIN
    int binarySearch(ElemType, int); //performs binary search in a given row to find a largest number less than or equal to given value
    Pair matrixSearch(ElemType); //performs search in entire matrix to find a given value
    int searchFor(ElemType, int); //performs binary search to find a given value, and returns the leftmost found value
};
/********************************************************************
 * END OF CLASS -- Matrix
 * 
 *********************************************************************/
#endif
/*********************************************************************************
 * $log$
 * END OF Matrix.h
 * 
 ***********************************************************************************/
