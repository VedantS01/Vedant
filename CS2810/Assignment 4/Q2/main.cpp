/**---------------------------------------------------------
 * 
 * Naive implementation of template class vector from STL
 * Version : 2.0.0 -- introducing Vector2 with a new and better sorting algorithm that reduces 
 *                    worst case complexity to O(nlogn)
 * Author : Vedant Saboo (CS19B074)
 * 
 * Created : 3/2/2021 5:10 PM
 * Last Modified :
 * 
 * Bugs :
 * 
 **---------------------------------------------------------*/

#include <iostream>
#include "Vector.h"
#include "Vector2.h"
using namespace std;

/**
 * toInt -- converts a string of given size into its numerical value (recursively)
 * 
 * args -- string with numerical characters, size
 * returns -- int correspondddding to its numerical value
 **/
int toInt(char* str, int n) {
    if(n == 0) return 0;
    if(n == 1) return str[0]-'0';
    return str[n-1]-'0' + 10 * toInt(str, n-1);
}

/**
 * Main -- program execution begins here
 * 
 * args -- none
 * returns -- int
 **/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char str[20]; //to read the first line
    int t; //number of queries
    int param; //optional parameter in some queries
    cin.getline(str,20); //get the entire line
    int i = 7;
    Vector2<int> * vPointer;
    while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') i++;
    size_t c = (size_t)toInt(str+7, i-7); 
    if(c != 0) {
        if(str[i] == '\0') {
            vPointer = new Vector2<int> (c); //single parameter
        } else {
            int j = ++i;
            while(str[j] != ' ' && str[j] != '\n' && str[j] != '\0') j++;
            int x = toInt(str+i, j-i);
            //cout << x << endl;
            if(x != 0)
                vPointer = new Vector2<int> (c,x); //double parameter
            else
                vPointer = new Vector2<int> (c); //single parameter
        }
        
    } else {
        vPointer = new Vector2<int> ; //no parameter
    }
    cin >> t;
    string query;
    while(t > 0) { //run the loop for each query and perform required operation
        cin >> query;
        if(query == "push") {
            cin >> param;
            vPointer->push(param);
        } else if(query == "pop") {
            vPointer->pop();
        } else if(query == "capacity") {
            cout << vPointer->capacity() << endl;
        } else if(query == "size") {
            cout << vPointer->size() << endl;
        } else if(query == "front") {
            cout << vPointer->front() << endl;
        } else if(query == "back") {
            cout << vPointer->back() << endl;
        } else if(query == "sort") {
            vPointer->sort();
            vPointer->printAll();
        } else if(query == "element") {
            cin >> param;
            if((size_t)param < vPointer->size())
                cout << (*vPointer)[param] << endl;
            else
                cout << "-1" << endl;
        } else {
            
        }
        t--;
    }
    
    return 0;
}
/**
 * END OF FILE
 **/