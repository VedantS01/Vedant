/**--------------------------------------------------
 * 
 * $id$
 * main.cpp 
 * Version : 1.0
 * Author : Vedant Ashish Saboo CS19B074
 * 
 * Created -- 11:05 PM 2/22/2021
 * Last Modified :
 * 
 * Bugs :
 **---------------------------------------------------*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Stack.h"
#include "Graph.h"
using namespace std;

#define ERR -1
#define YES 1
#define NO 0

/**-------------------------------
 * MAIN -- program execution begins here
 * args :
 * returns : int
 * 
 * Bugs :
 **-------------------------------*/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Stack stack;
    int numQueries, vertices;
    cin >> numQueries;
    string query;
    const string push = "push", pop = "pop", top = "top", empty = "empty", add = "add", del = "del", cycle = "cycle", components = "components", reach = "reach";
    int param1, param2;
    pair<int, int> pair;
    while(numQueries > 0) { //query processing system for stack operations
        cin >> query;
        if(query == push) {
            cin >> param1;
            stack.push(param1);
        } else if (query == pop) {
            cout << stack.pop();
            cout << endl;
        } else if (query == top) {
            cout << stack.top();
            cout << endl;
        } else if (query == empty) {
            if(stack.isEmpty()) {
                cout << YES;
            } else {
                cout << NO;
            }
            cout << endl;
        }
        numQueries--;
    }
    cin >> vertices;
    Graph graph(vertices);
    cin >> numQueries;
    while(numQueries > 0) { //query processing system for the graph operations
        cin >> query;
        if(query == add) {
            cin >> pair.first >> pair.second;
            graph += pair;
        } else if(query == del) {
            cin >> pair.first >> pair.second;
            graph -= pair;
        } else if (query == cycle) {
            if(graph.detectCycle()) {
                cout << YES << endl;
            } else {
                cout << NO << endl;
            }
        } else if (query == components) {
            cout << graph.components() << endl;
        } else if (query == reach) {
            cin >> param1 >> param2;
            if(graph.reach(param1, param2)) {
                cout << YES << endl;
            } else {
                cout << NO << endl;
            }
        }
        numQueries--;
    }
    return 0;
}

/**-------------------------------
 * 
 * END OF FILE
 * 
 **---------------------------------*/
