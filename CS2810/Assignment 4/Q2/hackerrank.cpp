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
    protected:
    int currentCapacity; //maintains current capacity 
    int currentSize; //maintains current size, that is, number of elements in the vector
    T* vec; //points to starting address of the vector
    public:
    Vector();
    Vector(int);
    Vector(int,T);
    void push(T);
    void pop();
    T front();
    T back();
    int capacity();
    int size();
    void sort();
    void printAll();
    T operator[](int);
    private:
    void sortHelper(int, int);
};
/**
 * END OF CLASS Vector
 **/

/**
 * BEGIN IMPLEMENTATION OF CLASS Vector
 **/
template<class T>
Vector<T>::Vector() { //unparameterized constructor, capacity is set to 1
    this->currentCapacity = 1;
    vec = new T[1];
    currentSize = 0;
}
template<class T>
Vector<T>::Vector(int c) { //single parameter, capacity is set to  param
    this->currentCapacity = c;
    vec = new T[c];
    this->currentSize = 0;
}
template<class T>
Vector<T>::Vector(int c, T x) { //double parameter, capacity is set to first param and all elements are given values of second param
    this->currentCapacity = c;
    vec = new T[c];
    this->currentSize = c;
    for(int i = 0; i < c; i++) {
        vec[i] = x;
    }
}
template<class T>
void Vector<T>::push(T x) { //inserts element in the end of the vector
    if(this->currentSize == this->currentCapacity) { //if full, double the capacity
        currentCapacity = currentCapacity * 2;
        T* newSpace = new T[currentCapacity];
        for(int i = 0; i < currentSize; i++) {
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
int Vector<T>::capacity() { //returns current capacity
    return currentCapacity;
}
template<class T>
int Vector<T>::size() { // returns current size
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
    for(int i = 0; i < currentSize; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}
/**
 * END OF CLASS IMPLEMENTATION
 **/


/**
 * Vector2 : public child of template class Vector
 * With an improved sorting algorithm with worst case complexity nlogn
 **/
template<class T>
class Vector2: public Vector<T> {
    public:
    Vector2():Vector<T>(){}
    Vector2(int c):Vector<T>(c){}
    Vector2(int c,T x):Vector<T>(c,x){}
    void sort(); //overrides the base class sort function
    private:
    void sortHelper(int, int); 
    T medianOfMedians(T*, int, int);
} ;
/**
 * END OF CLASS Vector2
 **/

/**
 * BEGIN IMPLEMENTATION OF CLASS Vector2
 **/

template<class T>
void Vector2<T>::sort() { //new sort method, a quicksort with a good pivot that reduces worst time complexity
    if(this->currentSize > 1)
        sortHelper(0,this->currentSize-1);
}

template<class T>
void Vector2<T>::sortHelper(int left, int right) { //a recursive fucntiom to support the sort
    int lIndex, rIndex;
    T pivot;
    lIndex = left;
    rIndex = right;
    pivot = medianOfMedians(this->vec, left, right) ; //a good pivot, the median of medians of groups of 5
    for(int i = left; i <= right; i++) { //bring pivot to leftmost to avoid reduplication. O(n)
        if(this->vec[i] == pivot) {
            this->vec[i] = this->vec[left];
            this->vec[left] = pivot;
            break;
        }
    }
    do { //partitioning loop -- O(n)
        while(this->vec[lIndex] < pivot) lIndex++ ;
        while(this->vec[rIndex] > pivot) rIndex-- ;
        if(lIndex <= rIndex) {
            T temp = this->vec[lIndex];
            this->vec[lIndex++] = this->vec[rIndex];
            this->vec[rIndex--] = temp;
        }
    } while(lIndex <= rIndex) ;
    if(left < rIndex)  sortHelper(left, rIndex) ; //recursive call in left partition
    if(lIndex < right) sortHelper(lIndex, right) ; //recursive call in right partition
}

template<class T>
T Vector2<T>::medianOfMedians(T* array, int left, int right) { //returns the median of medians of group 5
    int k = 0;
    int n = right - left + 1;
    if(n == 1) return array[left];
    T* medians; //array to store medians
    if(n % 5 != 0) medians = new T[n/5 + 1];
    else medians = new T[n/5];
    for(k = 0; k < n/5; k++) { //run over kth 5-group, sort each
        for(int i = 1; i < 5; i++) {
            for(int j = i - 1; j >= 0; j--) {
                if(array[5*k+j+left] > array[5*k+j+1+left]) {
                    T temp = array[5*k+j+left];
                    array[5*k+j+left] = array[5*k+j+1+left];
                    array[5*k+j+1+left] = temp;
                }
            }
        }
        medians[k] = array[5*k+2+left]; //centre element to be stored in medians
    }
    for(int i = 1; i < n%5; i++) { //sort the leftovers
        for(int j = i - 1; j >= 0; j--) {
            if(array[5*k+j+left] > array[5*k+j+1+left]) {
                T temp = array[5*k+j+left];
                array[5*k+j+left] = array[5*k+j+1+left];
                array[5*k+j+1+left] = temp;
            }
        }
    }
    if(n%5 != 0) medians[k] = array[5*k+(n%5)/2+left]; //if there is a leftover, add the median to the medians array
    return medianOfMedians(medians, 0, n/5); //recursive call
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
    Vector2<int> * vPointer;
    while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') i++;
    int c = (int)toInt(str+7, i-7); 
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
            if((int)param < vPointer->size())
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