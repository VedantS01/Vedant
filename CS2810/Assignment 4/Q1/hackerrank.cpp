/**---------------------------------------------------------
 * 
 * Naive implementation of template class vector from STL
 * Version : 1.0.0
 * Author : Vedant Saboo (CS19B074)
 * 
 * Created : 3/2/2021 5:10 PM
 * Last Modified :
 * 
 * Bugs :
 * 
 **---------------------------------------------------------*/ 


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

/**
 * Vector -- template class, implements structure similar to vector from STL
 * 
 **/
template<class T> 
class Vector{
    private:
    size_t currentCapacity; //maintains current capacity 
    size_t currentSize; //maintains current size, that is, number of elements in the vector
    T* vec; //points to starting address of the vector
    public:
    Vector();
    Vector(size_t);
    Vector(size_t,T);
    void push(T);
    void pop();
    T front();
    T back();
    size_t capacity();
    size_t size();
    void sort();
    void printAll();
    T operator[](int);
    private:
    void sortHelper(int, int);
};

template<class T>
Vector<T>::Vector() { //unparameterized constructor, capacity is set to 1
    this->currentCapacity = 1;
    vec = new T[1];
    currentSize = 0;
}
template<class T>
Vector<T>::Vector(size_t c) { //single parameter, capacity is set to  param
    this->currentCapacity = c;
    vec = new T[c];
    this->currentSize = 0;
}
template<class T>
Vector<T>::Vector(size_t c, T x) { //double parameter, capacity is set to first param and all elements are given values of second param
    this->currentCapacity = c;
    vec = new T[c];
    this->currentSize = c;
    for(size_t i = 0; i < c; i++) {
        vec[i] = x;
    }
}
template<class T>
void Vector<T>::push(T x) { //inserts element in the end of the vector
    if(this->currentSize == this->currentCapacity) { //if full, double the capacity
        currentCapacity = currentCapacity * 2;
        T* newSpace = new T[currentCapacity];
        for(size_t i = 0; i < currentSize; i++) {
            newSpace[i] = vec[i];
        }
        delete[] vec;
        vec = newSpace;
    }
    vec[currentSize++] = x;
}
template<class T>
void Vector<T>::pop() { //deletes the last element of the vector if there is any
    if(currentSize != 0)
    currentSize = currentSize - 1;
}
template<class T>
size_t Vector<T>::capacity() { //returns current capacity
    return currentCapacity;
}
template<class T>
size_t Vector<T>::size() { // returns current size
    return currentSize;
}
template<class T>
T Vector<T>::front() { //returns element at front
    return vec[0];
}
template<class T>
T Vector<T>::back() { //returns element at the rear
    return vec[currentSize - 1];
}
template<class T>
T Vector<T>::operator[](int at) { //returns element at a given position
    T temp;
    try {
        temp = vec[at];
    } catch (const char* expr) {
        cout << "ERROR : " << expr << endl;
    }
    return temp;
}
template<class T>
void Vector<T>::sort() { //sorts the elements using quicksort
    sortHelper(0,currentSize-1);
}
template<class T>
void Vector<T>::sortHelper(int left, int right) { //helper function for sort
    int lIndex, rIndex;
    T pivot;
    lIndex = left;
    rIndex = right;
    pivot = vec[left] ;
    do { //partitioning loop
        while(vec[lIndex] < pivot) lIndex++ ;
        while(vec[rIndex] > pivot) rIndex-- ;
        if(lIndex <= rIndex) {
            T temp = vec[lIndex];
            vec[lIndex++] = vec[rIndex];
            vec[rIndex--] = temp;
        }
    } while(lIndex <= rIndex) ;
    if(left < rIndex)  sortHelper(left, rIndex) ; //recursive call in left partition
    if(lIndex < right) sortHelper(lIndex, right) ; //recursive call in right partition
}
template<class T>
void Vector<T>::printAll() {// print all elements
    for(size_t i = 0; i < currentSize; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}
/**
 * END OF CLASS IMPLEMENTATION
 **/

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
    Vector<int>* pointerv;
    while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') i++;
    size_t c = (size_t)toInt(str+7, i-7); 
    if(c != 0) {
        if(str[i] == '\0') {
            pointerv = new Vector<int> (c); //single parameter
        } else {
            int j = ++i;
            while(str[j] != ' ' && str[j] != '\n' && str[j] != '\0') j++;
            int x = toInt(str+i, j-i);
            //cout << x << endl;
            if(x != 0)
                pointerv = new Vector<int> (c,x); //double parameter
            else
                pointerv = new Vector<int> (c); //single parameter
        }
        
    } else {
        pointerv = new Vector<int> ; //no parameter
    }
    cin >> t;
    string query;
    while(t > 0) { //run the loop for each query and perform required operation
        cin >> query;
        if(query == "push") {
            cin >> param;
            pointerv->push(param);
        } else if(query == "pop") {
            pointerv->pop();
        } else if(query == "capacity") {
            cout << pointerv->capacity() << endl;
        } else if(query == "size") {
            cout << pointerv->size() << endl;
        } else if(query == "front") {
            cout << pointerv->front() << endl;
        } else if(query == "back") {
            cout << pointerv->back() << endl;
        } else if(query == "sort") {
            pointerv->sort();
            pointerv->printAll();
        } else if(query == "element") {
            cin >> param;
            if((size_t)param < pointerv->size())
                cout << (*pointerv)[param] << endl;
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
