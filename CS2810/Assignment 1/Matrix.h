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
using namespace std;
#define AVERAGE_ERROR 0

/***************************************************************
 * 
 * Class :  Matrix -- implements a square matrix data structure with custom operations
 * Data members (public) :
 * Member functions (public) : readData, spsum, mod, mrs, madd
 * 
 * Bugs :
 **************************************************************/
class Matrix {
    private:
    int** grid; //square matrix data structure in the form of a 2d array
    int order; //order of the square matrix
    int FindMin(int); //private function -- calculates min value in the row with array index i
    int FindMax(int); //private function -- calculates max value in the row with array index i
    int FindAverage(int); //private function -- calculates floor of average value in the row with array index i
    public:
    Matrix(int);
    void readData(); //read data (elements of the matrix) from STDIN
    void spsum(); //perform Special Sum and display the results to STDOUT
    void mod(); //perform mod multiplication and display the results to STDOUT
    void mrs(int k, Matrix m); //perform matrix right shift operation and display the output to STDOUT
    void madd(int x, Matrix m); //perform Matrix Special Addition and display the results to STDOUT
};
#endif
/*********************************************************************************
 * $log$
 * END OF Matrix.h
 * 
 ***********************************************************************************/
