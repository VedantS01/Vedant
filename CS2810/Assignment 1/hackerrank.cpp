/**************************************************************************************
 * 
 * $id$
 * File : SpecialMatrixOperations.cpp -- implements a class Matrix with special operations 
 * 
 * Purpose : Implements Special Sum (SPSUM), Mod Multiplication(MOD), Matrix Right Shift (MRS) and Matrix Special Addition(MADD) 
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
    int findMin(int); //private function -- calculates min value in the row with array index i
    int findMax(int); //private function -- calculates max value in the row with array index i
    int findAverage(int); //private function -- calculates floor of average value in the row with array index i
    public:
    Matrix(int);
    void readData(); //read data (elements of the matrix) from STDIN
    void spsum(); //perform Special Sum and display the results to STDOUT
    void mod(); //perform mod multiplication and display the results to STDOUT
    void mrs(int k, Matrix m); //perform matrix right shift operation and display the output to STDOUT
    void madd(int x, Matrix m); //perform Matrix Special Addition and display the results to STDOUT
};
/********************************************************************
 * END OF CLASS -- MATRIX
 * 
 *********************************************************************/

/****************************************************************************************
 * START OF CLASS DEFINITION:
 * CLASS NAME : MATRIX
 * PRIVATE FUNCTIONS : FindMIn, FindMax, FindAverage
 * PUBLIC FUNCTIONS : spsum, readData, mod, mrs, madd
 * 
 * (SPSUM) Special Sum '+' : This is defined on one matrix. 
 *  Add row index(i) and column index(j) of each element of the matrix. 
 *  If this sum is odd, swap the element A[i][j] with A[j][i].
 *  Now, print the sum of each row of this new matrix. 
 *  Perform this operation on the 1st matrix provided as input.
 * 
 * (MOD) Mod Multiplication '&': This defined on one matrix. 
 *  If row index(i) is divisible by 3, find the max element of that row. 
 *  If i gives 1 on division by 3, then find the minimum element of that row. 
 *  Otherwise, find the floor of average of that row. 
 *  Print the product of these elements. 
 *  Perform this operation on the 1st matrix provided as input.
 * 
 * (MRS) Matrix Right Shift '>>' : This is defined on 2 matrices of same size. 
 *  You will be given 'k' as input. 
 *  Perform right shift operation on both the matrices(k times). 
 *  Print the sum of these shifted matrices.
 *  (eg In a 3X3 matrix, if k=2 , then element at position [0][0] moves to position [0][2] followed by all other elements such that last element at [2][2] moves to position [0][1])
 * 
 * (MADD) special Matrix Addition '+' : This is also defined on 2 matrices of same size. 
 *  Given 'x', If x = 1, then perform a transformation on the elements of 1st matrix such that A[i][j] gets swapped with A[j][i]. 
 *  Then, add it to the 2nd matrix B and print the resulting matrix. 
 *  If x = 2, then perform the transformation on the 2nd matrix such that B[i][j] gets swapped with B[j][i]. 
 *  Then, add it to the 1st matrix A and print the resulting matrix.
 * 
 ****************************************************************************************/
    int Matrix::findMin(int h) { //find the minimum value in the row
        int min = grid[h][0]; //initialise an integer variable min with first elem of the row (this element exists because order >= 1)
        for(int i = 1; i < order; i++) {
            if(min > grid[h][i]) { //if min > current element, min := current element
                min = grid[h][i] ;
            }
        }
        return min; //return the min value of the row
    }
    int Matrix::findMax(int h) { //find the maximum value in the row
        int max = grid[h][0]; //initialise an integer variable max with first elem of the row (this element exists because order >= 1)
        for(int i = 1; i < order; i++) { //if max < current element, min := current element
            if(max < grid[h][i]) {
                max = grid[h][i] ;
            }
        }
        return max; //return the max value of the row
    }
    int Matrix::findAverage(int h) { //find the integer part of the average value in the row
        //NOTE: This is different from floor function for negative numbers. floor(-1.4) gives -2 while integer division gives -1

        int average = 0; //initialise an integer variable average with 0
        for(int i = 0; i < order; i++) {
            average += grid[h][i]; //average contains the sum upto i elements in the array
        }
        return (int)average/order; //return integer result of sum / size as the average
    }
    Matrix::Matrix(int n) {
        order = n; //initailise order
        grid = new int*[n]; //initialise the matrix with n rows
    }
    void Matrix::readData() {
        int read;
        for(int i = 0; i < order; i++) {
            grid[i] = new int[order]; //initialise the row
            for(int j = 0; j < order; j++) {
                cin >> read;
                grid[i][j] = read; //assign value
            }
        }
    }
    void Matrix::spsum() {
        //SPSUM : Special Sum
        int sum;
        for(int i = 0; i < order; i++) {
            sum = 0; // for every row, sum is initialised to zero
            for(int j = 0; j < order; j++) {
                if((i + j) % 2 == 0) { //if sum of array indices is even, add the value to the sum
                    sum += grid[i][j];
                } else { //else add the value stored at the reversed indices
                    sum += grid[j][i];
                }
            }
            cout << sum;
            if(i != order -1)
                cout << ",";
        }
        cout << endl;
    }
    void Matrix::mod() {
        //MOD : Mod Multiplication
        long long int product = 1; //product can be large
        for(int i = 0; i < order; i++) {
            int choice = i % 3; //choice is determined by i mod 3
            if(choice == 0) { //if choice is 0, find max of the row, multiply to the product
                product *= findMax(i);
            } else if(choice == 1) { //if choice is 1, find min of the row, multiply to the product
                product *= findMin(i);
            } else { //if choice is 2 find integer value of average of the row, multiply to the product
                product *= findAverage(i);
            }
        }
        cout << product << endl;
    }
    void Matrix::mrs(int k, Matrix m) {
        //MRS k : Matrix Right Shift by k units
        int c;
        int arraySize = this->order * this->order;
        int* array;
        array = new int[arraySize]; //initialise array of size order*order
        for(int i = 0; i < order; i++) {
            for(int j = 0; j < order; j++) {
                k = k % (arraySize); 
                array[k] = this->grid[i][j] + m.grid[i][j]; //add values (elements of sum of matrices) to the array circularly, starting with index k
                k++;
            }
        }
        c = 0;
        for(int i = 0; i < order; i++) {
            for(int j = 0; j < order; j++) {
                cout << array[c] << " "; //print out the elements in the desired fashion
                c++;
            }
            cout << endl;
        }
    }
    void Matrix::madd(int x, Matrix m) {
        //MADD x : Matrix Special Addtion with parameter x
        for(int i = 0; i < order; i++) {
            for(int j = 0; j < order; j++) {
                if(x == 1)
                    cout << this->grid[j][i] + m.grid[i][j] << " "; //if x is 1, reverse the indices of this matrix 
                else
                    cout << this->grid[i][j] + m.grid[j][i] << " "; //if x is 2, reverse the indices of the matrix given as argument
            }
            cout << endl;
        }
    }
/************************************************************
 * 
 * END OF CLASS DEFINITION -- CLASS MATRIX
 * 
 ***************************************************************/



/**************************************************************
 * 
 * Main : Program execution begins here
 * Args :
 * Returns : int
 * 
 * Bugs :
 **************************************************************/
int main() {
    int numQueries; //number of queries to be processed
    int order; //common order for matrices
    cin >> numQueries >> order;
    Matrix firstMatrix(order); //first matrix
    firstMatrix.readData();
    Matrix secondMatrix(order); //second matrix
    secondMatrix.readData();
    string query;
    int secondParam;
    while(numQueries > 0) {
        cin >> query;
        // if else loop to process the query
        if(query == "SPSUM") {
            firstMatrix.spsum(); //call spsum on first matrix if query is SPSUM
        } else if(query == "MOD") {
            firstMatrix.mod(); //call mod on first matrix if query is MOD
        } else if(query == "MRS") {
            cin >> secondParam;
            firstMatrix.mrs(secondParam, secondMatrix); //call mrs on first matrix, second matrix as argument, and another paramter, if query is MRS
        } else if(query == "MADD") {
            cin >> secondParam;
            firstMatrix.madd(secondParam, secondMatrix); //call madd on first matrix, second matrix as argument, and another paramter, if query is MADD
        } else {
            //default case : do nothing here
        }
        //end of if else ladder
        numQueries--;
    }
    return 0;
}
/************************************
 * END OF MAIN
 * 
 **************************************/