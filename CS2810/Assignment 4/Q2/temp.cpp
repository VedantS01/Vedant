#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template<class T> 
class Vector{
    protected:
    size_t currentCapacity;
    size_t currentSize;
    T* vec;
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
    void sortHelper(size_t, size_t);
};

template<class T>
Vector<T>::Vector() {
    this->currentCapacity = 1;
    vec = new T[1];
    currentSize = 0;
}
template<class T>
Vector<T>::Vector(size_t c) {
    this->currentCapacity = c;
    vec = new T[c];
    this->currentSize = 0;
}
template<class T>
Vector<T>::Vector(size_t c, T x) {
    this->currentCapacity = c;
    vec = new T[c];
    this->currentSize = c;
    for(size_t i = 0; i < c; i++) {
        vec[i] = x;
    }
}
template<class T>
void Vector<T>::push(T x) {
    if(this->currentSize == this->currentCapacity) {
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
void Vector<T>::pop() {
    if(currentCapacity != 0)
    currentSize = currentSize - 1;
}
template<class T>
size_t Vector<T>::capacity() {
    return currentCapacity;
}
template<class T>
size_t Vector<T>::size() {
    return currentSize;
}
template<class T>
T Vector<T>::front() {
    return vec[0];
}
template<class T>
T Vector<T>::back() {
    return vec[currentSize - 1];
}
template<class T>
T Vector<T>::operator[](int at) {
    T temp;
    try {
        temp = vec[at];
    } catch (const char* expr) {
        cout << "ERROR : " << expr << endl;
    }
    return temp;
}
template<class T>
void Vector<T>::sort() {
    sortHelper(0,currentSize-1);
}
template<class T>
void Vector<T>::sortHelper(size_t left, size_t right) {
    size_t lIndex, rIndex;
    T pivot;
    lIndex = left;
    rIndex = right;
    pivot = vec[left] ;
    do {
        while(vec[lIndex] <= pivot) lIndex++ ;
        while(vec[rIndex] > pivot) rIndex-- ;
        if(lIndex <= rIndex) {
            T temp = vec[lIndex];
            vec[lIndex++] = vec[rIndex];
            vec[rIndex--] = temp;
        }

    } while(lIndex <= rIndex) ;
    if(left < rIndex)  sortHelper(left, rIndex) ;
    if(lIndex < right) sortHelper(lIndex, right) ;
}
template<class T>
void Vector<T>::printAll() {
    for(size_t i = 0; i < currentSize; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}



template<class T>
class Vector2: public Vector<T> {
    public:
    Vector2():Vector<T>(){}
    Vector2(size_t c):Vector<T>(c){}
    Vector2(size_t c,T x):Vector<T>(c,x){}
    void sort();
    private:
    //if some helpers are needed
    void sortHelper(size_t, size_t);
    T medianOfMedians(T*, size_t, size_t);
} ;

template<class T>
void Vector2<T>::sort() {
    sortHelper(0,(int)this->currentSize-1);
}

template<class T>
void Vector2<T>::sortHelper(size_t left, size_t right) {
    size_t lIndex, rIndex;
    T pivot;
    lIndex = left;
    rIndex = right;
    pivot = medianOfMedians(this->vec, left, right) ; //a good pivot
    for(int i = left; i <= right; i++) {
        if(this->vec[i] == pivot) {
            this->vec[i] = this->vec[left];
            this->vec[left] = pivot;
            break;
        }
    }
    do { //partitioning loop
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
T Vector2<T>::medianOfMedians(T* array, size_t left, size_t right) {
    //cout << "***called mom with left and right are : " << left << " " << right << " ***\n";
    size_t k = 0;
    size_t n = right - left + 1;
    if(n == 1) return array[left];
    T* medians;
    if(n % 5 != 0) medians = new T[n/5 + 1];
    else medians = new T[n/5];
    //cout << "***debug 1***\n";
    for(k = 0; k < n/5; k++) {
        for(int i = 1; i < 5; i++) {
            for(int j = i - 1; j >= 0; j--) {
                if(array[5*k+j+left] > array[5*k+j+1+left]) {
                    T temp = array[5*k+j+left];
                    array[5*k+j+left] = array[5*k+j+1+left];
                    array[5*k+j+1+left] = temp;
                }
            }
        }
        medians[k] = array[5*k+2+left];
    }
    //cout << "***debug 2 : k = " << k <<" ***\n";
    for(int i = 1; i < n%5; i++) {
        //cout << "***micro debug out : i = " << i <<" ***\n";
        for(int j = i - 1; j >= 0; j--) {
            //cout << "***micro debug out : j = " << j <<" ***\n";
            if(array[5*k+j+left] > array[5*k+j+1+left]) {
                //cout << "***micro debug out : swap = " << "true" <<" ***\n";
                T temp = array[5*k+j+left];
                array[5*k+j+left] = array[5*k+j+1+left];
                array[5*k+j+1+left] = temp;
            }
            //else cout << "***micro debug out : swap = " << "false" <<" ***\n";
        }
    }
    if(n%5!=0)medians[k] = array[5*k+(n%5)/2+left];
    //cout << "***exit mom with n : " << n/5 << " ***\n";
    return medianOfMedians(medians, 0, n/5);

}




int toInt(char* str, int n) {
    if(n == 0) return 0;
    if(n == 1) return str[0]-'0';
    return str[n-1]-'0' + 10 * toInt(str, n-1);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char str[20];
    int t;
    int param;
    cin.getline(str,20);
    int i = 7;
    Vector2<int>* pointerv;
    while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') i++;
    size_t c = (size_t)toInt(str+7, i-7);
    //cout << c << endl;
    if(c != 0) {
        if(str[i] == '\0') {
            pointerv = new Vector2<int> (c);
        } else {
            int j = ++i;
            while(str[j] != ' ' && str[j] != '\n' && str[j] != '\0') j++;
            int x = toInt(str+i, j-i);
            //cout << x << endl;
            if(x != 0)
                pointerv = new Vector2<int> (c,x);
            else
                pointerv = new Vector2<int> (c);
        }
        
    } else {
        pointerv = new Vector2<int> ;
    }
    cin >> t;
    string query;
    while(t > 0) {
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

