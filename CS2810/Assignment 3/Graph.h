/**--------------------------------------------------
 * 
 * $id$
 * Graph.h 
 * Version : 1.0
 * Author : Vedant Ashish Saboo CS19B074
 * 
 * Created -- 09:52 AM 2/23/2021
 * Last Modified :
 * 
 * Bugs :
 **---------------------------------------------------*/

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
using namespace std;

/**
 * class Graph
 * public methods : detectCycle, components, reach, operator overloads of += and -=
 **/
class Graph {
    private:
    int** adjMatrix;
    int vertices;
    bool detectCycleHelper(int, bool[], int);
    public:
    Graph(int);
    void operator+= (pair<int, int>);
    void operator-= (pair<int, int>);
    bool detectCycle();
    int components();
    bool reach(int, int);
};

#endif