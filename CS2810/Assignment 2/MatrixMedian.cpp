/**************************************************************************************
 * 
 * $id$
 * File : MatrixMedian.cpp -- contains definitions of member functions in class MatrixMedian, a child of class Matrix 
 * 
 * Purpose : 
 * Version : 1.0
 * Author : Vedant Ashish Saboo , CS19B074
 * Created : 
 * Last Modified :
 * 
 * Bugs :
 * 
 ***************************************************************************************/

#include <iostream>
#include "MatrixMedian.h"
using namespace std;

/****************************************************************************************
 * START OF CLASS DEFINITION:
 * CLASS NAME : MatrixMedian
 * PUBLIC FUNCTIONS : upperBound, findMedian
 * PUBLIC FUNCTIONS (INHERITED) : readData, binarySearch, matrixSearch, searchFor
 * 
 ****************************************************************************************/
    MatrixMedian::MatrixMedian(int mRows, int mCols) : Matrix(mRows, mCols) {
        isMedianCalculated = false;
    }
    int MatrixMedian::upperBound(ElemType elem, int row) { //uses inherited binarySearch method to compute an upper bound indicator with respect to given element in a given row
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
     * T3 : Printing the value -- O(1)
     * 
     * Overall time complexity -- O(32 * n * log m)
     * Additional space complexity -- O(1)
     * 
     * Please note : according to problem statement, ElemType ranges from -2^31 to 2^31 -1 and hence, sizeof(ElemType) is effectively 31 bits
     **/
    ElemType MatrixMedian::findMedian() { //finds median in a matrix
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
/********************************************************************
 * $log$
 * 
 * END OF FILE -- Matrix.cpp
 * 
 *****************************************************************************/