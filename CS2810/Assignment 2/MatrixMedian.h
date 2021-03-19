/**
 * MatrixMedian.h -- contains the class MatrixMedian, child of class Matrix
 * 
 **/

#ifndef MATRIX_MEDIAN_H
#define MATRIX_MEDIAN_H
#include <iostream>
#include "Matrix.h"
#include "ElemType.h"
using namespace std;
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
    MatrixMedian(int, int); //parameterized constructor matching parent class constructor
    int upperBound(ElemType, int); //uses inherited binarySearch method to compute an upper bound indicator with respect to given element in a given row
    ElemType findMedian(); //finds median in a matrix;
};
/********************************************************************
 * END OF CLASS -- MatrixMedian
 * 
 *********************************************************************/
#endif