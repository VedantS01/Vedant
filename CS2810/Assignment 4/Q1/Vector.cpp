/**
 * Vector.cpp -- v1.0 -- by Vedant Saboo
 * 
 * contains implementation of template class Vector
 **/

#include <iostream>
#include "Vector.h"
using namespace std;

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
    int lIndex, rIndex, pivot;
    lIndex = left;
    rIndex = right;
    pivot = vec[left] ;
    do { //partitioning loop
        while(vec[lIndex] < pivot) lIndex++ ;
        while(vec[rIndex] > pivot) rIndex-- ;
        if(lIndex <= rIndex) {
            int temp = vec[lIndex];
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