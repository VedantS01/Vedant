/**--------------------------------------------------
 * 
 * $id$
 * Graph.cpp 
 * Version : 1.0
 * Author : Vedant Ashish Saboo CS19B074
 * 
 * Created -- 09:52 AM 2/23/2021
 * Last Modified :
 * 
 * Bugs :
 **---------------------------------------------------*/

#include <iostream>
#include "Stack.h"
#include "Graph.h"
using namespace std;

/**
 * Begin implementation of class Graph
 **/
Graph::Graph(int n) { //parameterized constructor
    this->vertices = n;
    adjMatrix = new int*[n]; //dynamic allocation of adjacency matrix
    for(int i = 0; i < n; i++) {
        adjMatrix[i] = new int[n];
        for(int j = 0; j < n; j++) {
            adjMatrix[i][j] = 0; //initialize all to zero
        }
    }
}
void Graph::operator+=(pair<int, int> p) { //adds an edge in the graph corresponding to the pair of values, by registering the entry twice in the adjacency matrix
    adjMatrix[p.first][p.second] = 1;
    adjMatrix[p.second][p.first] = 1;
}
void Graph::operator-=(pair<int, int> p) { //removes an existing edge in the graph corresponding to the pair of vertices
    adjMatrix[p.first][p.second] = 0;
    adjMatrix[p.second][p.first] = 0;
}
bool Graph::detectCycle() {//detects cycles in the graph
    //visited -- bool array to keep track of visits
    bool* visited = new bool[vertices];
    //do DFS, from each vertex if not visited
    for (int i = 0; i < vertices ; i++) {
        if(visited[i]==false){
            if(detectCycleHelper(i, visited, -1)){ //call the recursive helper function detectCycleHelper; initial parent can be any negative number
                return true;
            }
        }
    }
    return false;
}
bool Graph::detectCycleHelper(int currentVertex, bool* visited, int parent) { //heper function for the method detectCycle
    //add this vertex to visited vertex
    visited[currentVertex] = true;

    //visit neighbors except its direct parent
    for (int i = 0; i < vertices ; i++) {
        if(adjMatrix[currentVertex][i] == 0)
            continue;
        //check the adjacent vertex from current vertex
        if(i != parent) {
            //if destination vertex is not its direct parent then
            if(visited[i]) {
                //if here means this destination vertex is already visited
                //means cycle has been detected
                return true;
            }
            else {
                //recursion from destination node
                if (detectCycleHelper(i, visited, currentVertex)) {
                    return true;
                }
            }
        }
    }
    return false;
}
int Graph::components() { //finds number of connected components in the graph
    Stack stack; //we use the data structure of stack
    bool* visited = new bool[vertices]; //a bool array to keep track of visited vertices
    for(int i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    int numComponents = 0;
    for(int i = 0; i < vertices; i++) {
        if(visited[i]) continue;
        //here, we have identified a new component, by visiting a vertex never before visited
        visited[i] = true;
        numComponents ++;
        stack.push(i); //push the vertex on the stack
        while(!stack.isEmpty()) {
            int vertex = stack.pop(); //pop the recent vertex to explore its neighbours
            for(int j = 0; j < vertices; j++) {
                if(adjMatrix[vertex][j] == 1) {
                    if(!visited[j]) { //visit the unvisited neighbours and put them on the stack
                        visited[j] = true; 
                        stack.push(j);
                    }
                }
            }
        }
        //post loop: stack is empty here. Since the graph is finite, stack will be emptied at certain point
    }
    return numComponents;
}
bool Graph::reach(int u, int v) { //determines whether a path exists between two vertices of the graph
    Stack stack; //we use the data structure of stack
    bool* visited = new bool[vertices]; //a bool array to keep track of visited vertices
    for(int i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    //bool result = false;
    visited[u] = true; //start with one vertex
    stack.push(u);
    while(!stack.isEmpty()) {
        int vertex = stack.pop();
        for(int j = 0; j < vertices; j++) {
            if(adjMatrix[vertex][j] == 1) {
                if(j == v) return true; //other vertex found
                if(!visited[j]) {
                    visited[j] = true;
                    stack.push(j);
                }
            }
        }
    }
    //we have now explored the entire component of the graph that includes the first vertex and still haven't found other vertex
    //this means that the desired path doesn't exist
    return false;
}
/**
 * End of implementation of class Graph
 **/