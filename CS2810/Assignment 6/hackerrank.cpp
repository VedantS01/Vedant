/**-----------------------------------------------------------------
 * 
 *  FILE            :           GraphAlgorithmsImplementation.cpp 
 * 
 *  PURPOSE         :           Submission to hackerrank problem A6 - BFS in Assignment 6
 * 
 *  VERSION         :           1.0
 *  AUTHOR          :           Vedant Ashish Saboo -- CS19B074
 * 
 *  CREATED         :           3/22/2021 3:40 PM
 *  LAST MODIFIED   :           3/22/2021 3:40 PM
 * 
 *  BUGS            :           NONE
 * 
 **------------------------------------------------------------------*/       

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

#define ADDV "ADDV"
#define ADDE "ADDE"
#define DELV "DELV"
#define DELE "DELE"
#define BFS "BFS"
#define SSP "SSP"

/**
 * Template class to draw out adjacency node for the graph, with weight type T
 **/
template <class T>
class AdjNode {                         //a node in the adjacency list
    public:
    int vertex;                         //vertex label 
    T weight;                           //weight of the edge from the vertex label of the list to this vertex
    AdjNode<T>();
    AdjNode<T>(int v, T w) {            //parameterized constructor
        vertex = v;
        weight = w;
    }

    //comparison operators overloaded
    bool operator<(AdjNode<T> n) {
        if(weight == n.weight) {
            return vertex < n.vertex;
        }
        return weight < n.weight;
    }
    bool operator>(AdjNode<T> n) {
        if(weight == n.weight) {
            return vertex > n.vertex;
        }
        return weight > n.weight;
    }
    bool operator<=(AdjNode<T> n) {
        if(weight == n.weight) {
            return vertex <= n.vertex;
        }
        return weight <= n.weight;
    }
    bool operator>=(AdjNode<T> n) {
        if(weight == n.weight) {
            return vertex >= n.vertex;
        }
        return weight >= n.weight;
    }
};
/**
 * END OF TEMPLATE CLASS AdjNode
 **/

/**
 * Template Class Graph         :       Represents a undirected weighted graph, where template parameter represents data type of weights
 * 
 * IMPLEMENTS BFS (Breadth First Search) and SSP (Single Source Shortest Path) METHODS
 * 
 **/
template <class T>
class Graph {
    typedef pair<T, int> Node; //used in bfs and ssp; this is different from the node of the adjacency list
    vector<vector<AdjNode<T>>> adjLists;    //2d vector matrix used to implement adjcancy lists of the graph
    int vertices;                           //number of current vertices
    public:
    Graph<T>() {                            //default constructor -- sets empty graph
        vertices = 0;
    }

    Graph<T>(int v) {                       //parameter v represents initial vertices of the graph
        vertices = v;
        adjLists = vector<vector<AdjNode<T>>>(v);
    }

    //adds a new vertex
    void addV() {                           
        adjLists.push_back(vector<AdjNode<T>>());
        vertices++;
    }

    //adds an edge between to two existing distant vertices
    void addE(int v1, int v2, T w) {        
        if(v1 >= vertices || v2 >= vertices || v1 == v2) {
            cerr << "ERROR: INVALID VERTICES\n" ;
            return;
        }
        //check if the vertex does already exists, if it does, update the weight.
        bool found = false;
        for(auto i = adjLists[v1].begin(); i != adjLists[v1].end(); i++) {
            if((*i).vertex == v2) {
                (*i).weight = w;
                found = true;
                break;
            }
        }
        if(found) for(auto i = adjLists[v2].begin(); i != adjLists[v2].end(); i++) {
            if((*i).vertex == v1) {
                (*i).weight = w;
                return;
            }
        } else {
            //the edge does not already exists
            adjLists[v1].push_back(AdjNode<T>(v2, w));
            adjLists[v2].push_back(AdjNode<T>(v1, w));
        }
    }

    //delete a vertex
    void delV(int v) {
        if(v >= vertices) {
            cerr << "ERROR: INVALID VERTICES\n" ;
            return;
        }
        for(int i = 0; i < vertices; i++) {
            if(i != v) {
                for(auto j = adjLists[i].begin(); j != adjLists[i].end(); j++) {
                    if((*j).vertex == v) {
                        adjLists[i].erase(j);
                        break;
                    }
                }
            }
        }
        adjLists.erase(adjLists.begin()+v);
    }

    //delete an existing edge
    void delE(int v1, int v2) {
        if(v1 >= vertices || v2 >= vertices || v1 == v2) {
            cerr << "ERROR: INVALID VERTICES\n" ;
            return;
        }
        bool found = false;
        for(auto i = adjLists[v1].begin(); i != adjLists[v1].end(); i++) {
            if((*i).vertex == v2) {
                adjLists[v1].erase(i);
                found = true;
                break;
            }
        }
        if(!found) {
            cerr << "ERROR: EDGE DOES NOT EXIST\n" ;
            return;
        }
        for(auto i = adjLists[v2].begin(); i != adjLists[v2].end(); i++) {
            if((*i).vertex == v1) {
                adjLists[v2].erase(i);
                break;
            }
        }
    }

    //perform bfs, starting from vertex v;
    void bfs(int v) {
        if(v >= vertices) {
            cerr << "ERROR: INVALID VERTICES\n" ;
            return;
        }

        //using in inner loop to sort the vertices by weights and then by vertex labels
        priority_queue<Node, vector<Node>, greater<Node>> helperQueue;

        //queue for storing vertex labels
        queue<int> que;

        Node node;      //temporary object, using in helperQueue

        vector<bool> visited(vertices, false);
        visited[v] = true;

        //push the first vertex in the queue : root vertex of the bfs tree
        que.push(v);
        while (!que.empty()) {
            int w = que.front();
            que.pop();
            //print the vertex
            cout << w << " ";
            for(auto i = adjLists[w].begin(); i != adjLists[w].end(); i++) {
                int u = (*i).vertex;
                //if not visited, visit u and add to queue, through first adding to helperQueue
                if(!visited[u]) {
                    visited[u] = true;
                    node.first = (*i).weight;
                    node.second = u;
                    helperQueue.push(node);
                }
            }
            while (!helperQueue.empty()) {
                que.push(helperQueue.top().second);
                helperQueue.pop();
            }
        }
        cout << endl;
    }

    //performs single source shortest path algorithm (Dijkstra) starting from source
    void ssp(int source) {
        if(source >= vertices) {
            cerr << "ERROR: INVALID VERTICES\n" ;
            return;
        }

        //priority queue used to store temporary minimal distances
        priority_queue<Node, vector<Node>, greater<Node>> helperQueue;
        
        //distance vector to store the minimum distances from the source
        vector<T> distances(vertices, (T)INT_MAX) ;
        distances[source] = 0; //set source distance to 0

        Node node;
        node.first = 0;
        node.second = source;

        //push source node on the min heap (priority queue)
        helperQueue.push(node);
        while (!helperQueue.empty()) {
            //retrieve minimum distance node in the queue
            int u = helperQueue.top().second;
            helperQueue.pop();

            //look in the adjacency lists and update the distance values. For each update, put the corresponding vertex on the heap.
            for(auto i = adjLists[u].begin(); i != adjLists[u].end(); i++) {
                int v = (*i).vertex;
                int weight = (*i).weight;

                //if path from u shorts the direct path to u, update
                if(distances[v] > distances[u] + weight) {
                    distances[v] = distances[u] + weight ;
                    node.first = distances[v];
                    node.second = v;
                    //push updated values on the heap
                    helperQueue.push(node);
                }
            }
        }
        //exited the while loop. no more updations needed.

        //print the shortest distance values
        for(int i = 0; i < vertices; i++) {
            cout << distances[i] << " ";
        }
        cout << endl;
    }
};
/**
 * END OF TEMPLATE CLASS Graph
 **/

/**
 * Main         :       program execution begins here
 * Args         :       none
 * Returns      :       int
 * Bugs         :       none
 **/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int initVertices;
    int queries;
    cin >> initVertices >> queries;
    string query;
    int param1, param2;
    int param3;

    //create object graph, initialise
    Graph<int> graph(initVertices);

    while(queries > 0) {
        cin >> query;
        if(query == ADDV) {
            graph.addV();
        } else if(query == ADDE) {
            cin >> param1 >> param2 >> param3;
            graph.addE(param1, param2, param3);
        } else if(query == DELV) {
            cin >> param1;
            graph.delV(param1);
        } else if(query == DELE) {
            cin >> param1 >> param2 ;
            graph.delE(param1, param2);
        } else {
            cerr << "ERROR: unrecognised command called\n";
        }
        queries--;
    }

    //exactly two queries to process
    queries = 2;
    while(queries > 0) {
        cin >> query;
        if(query == BFS) {
            cin >> param1;
            graph.bfs(param1);
        } else if(query == SSP) {
            cin >> param1;
            graph.ssp(param1);
        } else {
            cerr << "ERROR: unrecognised command called\n";
        }
        queries--;
    }
    return 0;
}

/**
 * END OF FILE
 **/