/**--------------------------------------------------
 * 
 * $id$
 * Operations using Graphs 
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
using namespace std;

#define ERR -1
#define YES 1
#define NO 0

/**
 * class StackNode
 */
class StackNode {
    private:
    int data;
    StackNode* next;
    friend class Stack;
};

/**
 * class Stack
 * public methods: top, pop, push, isEmpty
 */
class Stack {
    private:
    StackNode* tos;
    public:
    Stack() {
        tos = NULL;
    }
    int top();
    int pop();
    void push(int);
    bool isEmpty();
};
/**
 * Begin implementation of class Stack Methods
 **/
int Stack::top() { //returns value stored at the top of the stack
    if(!isEmpty()) {
        return tos->data;
    }
    return ERR;
}
int Stack::pop() { //deletes an element from the top and returns its value
    StackNode* temp = tos->next;
    int retValue = tos->data;
    delete tos;
    tos = temp;
    return retValue;
}
void Stack::push(int val) { //inserts an element in the stack
    StackNode* temp = new StackNode;
    temp->data = val;
    temp->next = tos;
    tos = temp;
}
bool Stack::isEmpty() { //checks whether the stack is empty.
    return tos == NULL;
}
/**
 * End of class Stack implementation
 **/

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
