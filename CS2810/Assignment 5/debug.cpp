/********************************************************************************
 * 
 * $id$
 * BloomBrain.cpp -- implements working solution for management in the BloomBrain institute
 * 
 * Version -- 1.0
 * Author -- Vedant Ashish Saboo (CS19B074)
 * 
 * Created -- 1:31 PM 3/9/2021
 * Last Modified -- 1:49 PM 3/9/2021 by vedant
 * 
 * Bugs -- 
 *******************************************************************************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define UPDATE "update"
#define JOIN "join"
#define LEAVE "leave"
#define PLAY "play"
#define OCCUPIED "occupied"

typedef long long int dataType;

//function declarations useful for the class methods of class Institute
dataType max(dataType, dataType); //returns max of the two operands
dataType max(dataType, dataType, dataType); //returns max of the three operands

/**
 * struct subArraySolution -- useful for calculations of maxSubArraySum in the class Institute
 **/
typedef struct subArraySolution {
    dataType maxSubArraySum;
    dataType prefixSum;
    dataType suffixSum;
    dataType blockSum;
} subArraySolution;

/**
 * class Room -- contains information about the room
 * public data : seraphicNumber, isOccupied
 **/
class Room {
    public:
    int seraphicNumber;
    bool isOccupied;
    Room() {
        seraphicNumber = 0;
    }
    Room(int num) {
        seraphicNumber = num;
    }
};

/**
 * class Institute -- contains information about the institute and the data of its clients
 * public methods : join, leave, update, initUpdate, occupied, play
 **/
class Institute {
    int numberRooms;  //total number of rooms
    int currentOccupancy;  //total number of occupied rooms
    Room* rooms;  //header to the array 'rooms' 
    int start;  //index to first occupied room from the left. its value id numberRooms if the institute is completely empty
    public:
    Institute(int num) {  //parameterized constructor
        numberRooms = num; //set number of rooms
        rooms = new Room[num]; //dynamically allot storage to the rooms array
        currentOccupancy = 0; //set current occupancy 0
        start = num; //set start numberRooms
    }
    void join(int sNum) { //join a new member with seraphic number sNum, if the institute has a vacant place
        if(currentOccupancy == numberRooms) return;
        for(int i = numberRooms - 1; i >= 0; i--) {
            if(!rooms[i].isOccupied) { //last unoccupied room
                rooms[i].isOccupied = true;
                rooms[i].seraphicNumber = sNum;
                currentOccupancy++;
                if(i < start) start = i;
                return;
            }
        }
        return;
    }
    void leave(int roomNum) { //member with room number roomNum leaves the institute
        if(currentOccupancy == 0) return;
        rooms[roomNum].isOccupied = false;
        rooms[roomNum].seraphicNumber = 0;
        currentOccupancy--;
        if(start == roomNum) { //reset start value;
            while (!rooms[start].isOccupied) start++;
        }
        return;
    }
    dataType update() { //update the seraphic numbers of the members by values from the STDIN
        for(int i = 0; i < numberRooms; i++) {
            cin >> rooms[i].seraphicNumber;
        }
        return numQualityTalks(); //return number of quality talks possible
    }
    dataType initUpdate() { //update the seraphic numbers of the members by values from the STDIN, filling all the rooms
        for(int i = 0; i < numberRooms; i++) {
            cin >> rooms[i].seraphicNumber;
            rooms[i].isOccupied = true;
        }
        start = 0;
        currentOccupancy = numberRooms;
        return numQualityTalks(); //return number of quality talks possible
    }
    int occupied() { //return current occupancy
        return currentOccupancy; 
    }
    // more methods to come here ...
    dataType play() { //return the minimum seraphic number for a guru so that it won't lose in a crossover
        /*
        if(currentOccupancy == 0) {
            return 0;
        }
        int returnVal = 0, currentMax = 0;
        int i = start;
        int maxIfAllNegative = rooms[i].seraphicNumber;
        bool isAllNegative = (rooms[i].seraphicNumber < 0);
        while (i < numberRooms) {
            if(!rooms[i].isOccupied) {
                i++;
                continue;
            }
            if(rooms[i].seraphicNumber > 0) {
                isAllNegative = false;
            }
            maxIfAllNegative = maxIfAllNegative > rooms[i].seraphicNumber ? maxIfAllNegative : rooms[i].seraphicNumber;
            currentMax = currentMax + rooms[i].seraphicNumber;
            if (currentMax < 0) currentMax = 0;
            else if (returnVal < currentMax) returnVal = currentMax;

            i++;
        }
        if(isAllNegative) return maxIfAllNegative;
        return returnVal;
        */
        subArraySolution sol = maxSubarraySum(start, numberRooms-1);
        return sol.maxSubArraySum;
    }
    private:
    dataType numQualityTalks() {
        int* arr;
        arr = new int[currentOccupancy];
        int* temp;
        temp = new int[currentOccupancy];
        int i = start;
        int k = 0;
        while (i < numberRooms) {
            if(rooms[i].isOccupied) {
                arr[k++] = rooms[i].seraphicNumber;
            }
            i++;
        }
        return numQualityTalks(arr, temp, 0, currentOccupancy - 1);
        delete[] arr;
        delete[] temp;
    }
    dataType numQualityTalks(int* arr, int* temp, int left, int right) {
        int mid;
        dataType returnVal = 0;
        if(left < right) {
            mid = (left + right) / 2;
            returnVal += numQualityTalks(arr, temp, left, mid);
            returnVal += numQualityTalks(arr, temp, mid+1, right);
            returnVal += merge(arr, temp, left, mid+1, right);
        }
        return returnVal;
    }
    dataType merge(int* arr, int* temp, int left, int mid, int right) {
        int i, j, k;
        dataType returnVal = 0;
        i = left;
        j = mid;
        k = left;
        while ((i <= mid - 1) && (j <= right)) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            }
            else {
                temp[k++] = arr[j++];
                returnVal = returnVal + (dataType)(mid - i);
            }
        }
        while (i <= mid - 1) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        for(i = left; i <= right; i++) arr[i] = temp[i] ;
        return returnVal;
    }
    subArraySolution maxSubarraySum(int left, int right) {
        subArraySolution sol;
        if(left == right) {
            sol.blockSum = rooms[left].seraphicNumber;
            sol.prefixSum = rooms[left].seraphicNumber;
            sol.suffixSum = rooms[left].seraphicNumber;
            sol.maxSubArraySum = rooms[left].seraphicNumber;
            return sol;
        }
        int mid = (left + right) / 2;
        subArraySolution sol1 = maxSubarraySum(left, mid);
        subArraySolution sol2 = maxSubarraySum(mid + 1, right);
        sol.blockSum = sol1.blockSum + sol2.blockSum;
        sol.prefixSum = max(sol1.prefixSum, sol1.blockSum + sol2.prefixSum);
        sol.suffixSum = max(sol2.suffixSum, sol2.blockSum + sol1.suffixSum);
        sol.maxSubArraySum = max(sol1.maxSubArraySum, sol2.maxSubArraySum, sol2.prefixSum + sol1.suffixSum);
        return sol;
    }
};

dataType max(dataType x, dataType y) {
    return x > y ? x : y;
}
dataType max(dataType x, dataType y, dataType z) {
    dataType temp = x > y ? x : y;
    return temp > z ? temp : z;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numRooms, numQueries;
    bool initialUpdate = false;
    cin >> numRooms;
    cin >> numQueries;
    Institute bloomBrain(numRooms);
    string query;
    int param;
    while(numQueries > 0) {
        cin >> query;
        if(query == UPDATE) {
            if(!initialUpdate) {
                cout << bloomBrain.initUpdate() << endl;
                initialUpdate = true;
            } else {
                cout << bloomBrain.update() << endl;
            }
        } else if(query == JOIN) {
            cin >> param;
            bloomBrain.join(param);
        } else if(query == LEAVE) {
            cin >> param;
            bloomBrain.leave(param);
        } else if(query == PLAY) {
            cout << bloomBrain.play() << endl;
        } else if(query == OCCUPIED) {
            cout << bloomBrain.occupied() << endl;;
        }
        numQueries--;
    }
    return 0;
}
