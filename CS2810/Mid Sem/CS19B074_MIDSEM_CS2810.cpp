/**************************************************************************************************************
 * 
 * $id$
 * CS2800 MIDSEM Q2 --  FINDING RANK LISTS OF A PARALLEL UNIVERSE SYSTEM AND 
 *                      ITS COST OF MERGING INTO A SINGLE UNIVERSE
 * 
 * AUTHOR           --  VEDANT ASHISH SABOO 
 * ROLL NUMBER      --  CS19B074
 * 
 * VERSION          --  1.0
 * 
 * CREATED          --  3:47 PM 3/15/2021
 * LAST MODIFIED    --  3:59 PM 3/15/2021
 * 
 * BUGS             --  NONE
 * 
 ***************************************************************************************************************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// some data types used in this code
// this enables us to change the data type effectively to meet our needs
typedef long long int type_id;
typedef int type_duration;
typedef long long int type_index;
typedef int type_entropy;


/**
 *  CLASS MagicianData  :   CONTAINS THE DATA OF THE MAGICIAN LIKE THE DURATION OF HIS/HER MAGIC SHOWS, 
 *                          THE ID OF HIS/HER PARALLEL UNIVERSE AND THE ENTROPY OF HIS/HER UNIVERSE
 * 
 *  PUBLIC METHODS      :   calcEntropy, operator >, operator <, operator ==, operator >=, operator <=  
 * 
 **/
class MagicianData {
    public:
    type_id id;                             //denotes id of the universe of the magician
    type_duration t1;                       //denotes duration of first magic show
    type_duration t2;                       //denotes duration of second magic show
    type_duration t3;                       //denotes duration of third magic show
    type_duration t4;                       //denotes duration of fourth magic show
    type_duration t5;                       //denotes duration of fifth magic show
    type_entropy entropy;                   //denotes entropy of the universe of the magician
    void calcEntropy() {                    //calculates entropy of the universe based on the magic shows of the magician
        entropy = t1 ^ t2 ^ t3 ^ t4 ^ t5 ;
    }
    MagicianData() {                        //empty public constructor
        
    }
    MagicianData(type_id mId, type_duration mT1, type_duration mT2, type_duration mT3, type_duration mT4, type_duration mT5) {
                                            //parameterized constructor
        id = mId;
        t1 = mT1;
        t2 = mT2;
        t3 = mT3;
        t4 = mT4;
        t5 = mT5;
    }
    bool operator >(MagicianData md) {      //overload for operator >
        if(this->entropy == md.entropy)
            return this->id > md.id;
        else
            return this->entropy > md.entropy;
    }
    bool operator >=(MagicianData md) {     //overload for operator >=
        if(this->entropy == md.entropy)
            return this->id >= md.id;
        else
            return this->entropy >= md.entropy;
    }
    bool operator <(MagicianData md) {      //overload for operator <
        if(this->entropy == md.entropy)
            return this->id < md.id;
        else
            return this->entropy < md.entropy;
    }
    bool operator <=(MagicianData md) {     //overload for operator <=
        if(this->entropy == md.entropy)
            return this->id <= md.id;
        else
            return this->entropy <= md.entropy;
    }
    bool operator ==(MagicianData md) {     //overload for operator ==
        if(this->entropy == md.entropy)
            return this->id == md.id;
        else
            return false;
    }
};
/***
 * END OF CLASS MagicianData
 **/

/***
 *  CLASS Universes     :   CONTAINS DATA OF THE ENTIRE PARALLEL UNIVERSE SYSTEM
 * 
 *  PUBLIC METHODS      :   printRankList, readData, findMergeCost
 **/
class Universes {
    MagicianData* universes;                //dynamic array containing all parallel universes
    type_index n;                           //number of parallel universes in existence
    public:
    Universes(int num) {                    //parameterized constructor
        n = num;
        universes = new MagicianData[num];  //dynamic storage allocation
    }
    void readData() {                       //read the data of the parallel universes from the STDIN
        for(type_index i = 0; i < n; i++) {
            cin >> universes[i].id >> universes[i].t1 >> universes[i].t2 >> universes[i].t3 >> universes[i].t4 >> universes[i].t5 ;
            universes[i].calcEntropy();     //calculate individual entropies
        }
    }
    void printRankList() {                  //prints the ids of the universes in ascending order of their ranks
        sort();                             //sort the universes according to their ranks. This is a merge sort, worst case O(nlogn)
        for(type_index i = 0; i < n; i++) { 
            cout << universes[i].id << " ";
        }
        cout << endl;
    }
    type_entropy findMergeCost() {          //find the minimum cost of merging all the universes
        type_entropy returnVal = 0;         //set the cost initially to zero
        sort();                             //sort the universes according to their ranks. This is a merge sort, worst case O(nlogn)
        for(type_index i = 0; i < n / 2; i++) {
                                            //take the difference between the (i+1)th from the left and the (i+1)th from the right 
                                            // and add to the existing value, because this difference will have to be incurred.
                                            //entire loop is O(n/2) = O(n), making overall function complexity O(nlogn)
            returnVal += universes[n - i - 1].entropy - universes[i].entropy;
        }
        return returnVal;
    }
    protected:                              //protected methods : hidden methods this class implements. This is kept protected with the 
                                            //                    hope that some classes would be inherited from this and would then 
                                            //                    implement and improvise these algorithms

    void sort() {                           //sorts the universes in ascending order of their ranks. Implements merge sort.
        MagicianData* temp = new MagicianData[n];
        sortHelper(temp, 0, n - 1);
        delete[] temp;
    }
    void sortHelper(MagicianData* temp, type_index left, type_index right) {
                                            //a helper function for the sort method
        if(left < right) {
            type_index mid = (left + right) / 2;
            sortHelper(temp, left, mid);
            sortHelper(temp, mid+1, right);
            merge(temp, left, mid+1, right);
        }
    }
    void merge(MagicianData* temp, type_index left, type_index mid, type_index right) {
                                            //to merge two sorted sections. used in sorting algorithm.
        type_index i, j, k;
        i = left;
        j = mid;
        k = left;
        while ((i <= mid - 1) && (j <= right)) {
            if (universes[i] > universes[j]) temp[k++] = universes[j++];
            else temp[k++] = universes[i++];
        }
        while (i <= mid - 1) temp[k++] = universes[i++]; 
        while (j <= right) temp[k++] = universes[j++];
        for(i = left; i <= right; i++) universes[i] = temp[i] ;
    }
};
/***
 *  END OF CLASS Universes
 **/



/**
 *  MAIN        --      PROGRAM EXECUTION BEGINS HERE
 *  ARGS        --      NONE
 *  RETURNS     --      INT
 *  
 *  BUGS        --      NONE
 **/
int main() {
    type_index numberOfUniverses;           //number of universes in existence
    cin >> numberOfUniverses;
    Universes parallelUniverseSystem(numberOfUniverses);
    parallelUniverseSystem.readData();      //read the data of the existing universes
    int query;
    cin >> query;                           //a single query
    if(query == 2)                          //print the rank list
        parallelUniverseSystem.printRankList();
    else if(query == 1)                     //find the minimum cost of merging the universes
        cout << parallelUniverseSystem.findMergeCost() << endl;
    return 0;
}
/**
 *  END OF FILE
 **/
