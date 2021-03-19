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
#include "Matrix.h"
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