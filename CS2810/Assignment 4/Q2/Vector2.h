/**
 * Vector.h -- v1.0 -- by Vedant Saboo
 * 
 * contains template class Vector
 **/

#ifndef CUSTOM_VECTOR_II_H
#define CUSTOM_VECTOR_II_H
#include <iostream>
#include "Vector.h"
using namespace std;

/**
 * Vector2 : public child of template class Vector
 * With an improved sorting algorithm with worst case complexity nlogn
 **/
template<class T>
class Vector2: public Vector<T> {
    public:
    Vector2():Vector<T>(){}
    Vector2(size_t c):Vector<T>(c){}
    Vector2(size_t c,T x):Vector<T>(c,x){}
    ~Vector2(){
        delete[] this->vec;
    }
    void sort(); //overrides the base class sort function
    private:
    void sortHelper(size_t, size_t); 
    T medianOfMedians(T*, size_t, size_t);
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
void Vector2<T>::sortHelper(size_t left, size_t right) { //a recursive fucntiom to support the sort
    size_t lIndex, rIndex;
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
T Vector2<T>::medianOfMedians(T* array, size_t left, size_t right) { //returns the median of medians of group 5
    size_t k = 0;
    size_t n = right - left + 1;
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

#endif