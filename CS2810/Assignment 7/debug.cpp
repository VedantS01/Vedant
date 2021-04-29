/**-----------------------------------------------------------------
 * 
 *  FILE            :           MaximumSpanningTree.cpp 
 * 
 *  PURPOSE         :           Submission to hackerrank problem A7 - MST in Assignment 7
 * 
 *  VERSION         :           1.0
 *  AUTHOR          :           Vedant Ashish Saboo -- CS19B074
 * 
 *  CREATED         :           4/5/2021 3:40 PM
 *  LAST MODIFIED   :           4/6/2021 12:41 AM
 * 
 *  BUGS            :           NONE
 * 
 **------------------------------------------------------------------*/

#include <cmath>
#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

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
    protected:
    //typedef pair<T, int> Node; //used in bfs and ssp; this is different from the node of the adjacency list
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
        vertices--;
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
};
/**
 * END OF TEMPLATE CLASS Graph
 **/

template <class T>
class MST : public Graph<T> {
    private:
    const string NO = "NO";
    const string YES = "YES";
    protected:
    vector<vector<AdjNode<T>>> tree;    //2d vector matrix used to implement adjcancy lists of the graph
    bool flagUpToDate;                  //a flag which is set if the spanning tree is up to date
    public:

    typedef pair<T, int> Node;

    MST():Graph<T>() {
        flagUpToDate = false;
    }
    MST(int n):Graph<T>(n) {
        flagUpToDate = false;
    }
    
    //finding maximum spanning tree using Prim's algorithm
    void prim(int source) {
        vector<T> cost(Graph<T>::vertices, (T)INT_MAX);
        cost[source] = 0;
        vector<int> edge(Graph<T>::vertices, -1);
        vector<bool> present(Graph<T>::vertices, false);
        tree.clear();
        tree = vector<vector<AdjNode<T>>> (Graph<T>::vertices) ;
        priority_queue< Node, vector<Node>, greater<Node> > minHeap;

        Node node;
        for(int i = 0; i < Graph<T>::vertices; i++) {
            node.first = cost[i];
            node.second = i;
            minHeap.push(node);
        }

        int v, u;
        T w;

        while(!minHeap.empty()) {
            cout << "1: ";
            v = minHeap.top().second;
            cout << v << endl;
            minHeap.pop();
            cout << "size of present = " << present.size() << endl;
            present[v] = true;

            if(edge[v] != -1) {
                tree[v].push_back(AdjNode<T>(edge[v], cost[v]));
                tree[edge[v]].push_back(AdjNode<T>(v, cost[v]));
            }
            cout << "Size of adjlists of " << v << " = " << Graph<T>::adjLists[v].size() << endl;
            for(auto i = Graph<T>::adjLists[v].begin(); i != Graph<T>::adjLists[v].end(); i++) {
                u = (*i).vertex;
                w = (*i).weight;
                cout << "2: " << v << " "<< u << " " << w <<"\n";
                //cout << "size of present = " << present.size() << endl;
                /*try {
                    if(present.size() <= u) {
                        throw 1;
                    }
                    if(present.empty()) {
                        throw 2;
                    }
                    if(!present[u]) {
                    if(w < cost[u]) {
                    cost[u] = w;
                    edge[w] = v;
                    }
                }
                } catch(int e) {
                    if(e == 1) {
                        cout << "vertex label huge than number of vertices!\n" ;
                    } else if(e == 2) {
                        cout << "prsent is empty!\n" ;
                    }
                }*/
                if(!present[u]) {
                    cout << "3: \n";
                    if(w < cost[u]) {
                        cout << "4: \n";
                    cost[u] = w;
                    edge[w] = v;
                    }
                }
            }
        }

        T total = (T)0;
        for(int i = 0; i < Graph<T>::vertices; i++) {
            if(cost[i] == INT_MAX) {
                total = INT_MAX;
                break;
            }
            total += cost[i];
        }

        cout << total << endl;


        flagUpToDate = true;
    }
    
    //finding maximum spanning tree using Kruskal's algorithm
    void kruskal() {
        
        flagUpToDate = true;
    }
    
    //finding maximum spanning tree using Prim's algorithm
    void treeUpToDate() {
        if(flagUpToDate) {
            cout << YES << endl;
        }
        else {
            cout << NO << endl;
        }
    }
    
    //display tree
    void displayTree() {
        
    }
    
    //adds a new vertex
    void addV() {                           
        Graph<T>::addV();

        flagUpToDate = false;
    }

    //adds an edge between to two existing distant vertices
    void addE(int v1, int v2, T w) {        
        Graph<T>::addE(v1,v2,w);
        
        flagUpToDate = false;
    }

    //delete a vertex
    void delV(int v) {
        Graph<T>::delV(v);
        
        flagUpToDate = false;
    }

    //delete an existing edge
    void delE(int v1, int v2) {
        Graph<T>::delE(v1,v2);
        
        flagUpToDate = false;
    }
};


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
    MST<int> graph(initVertices);
    
    while(queries > 0) {
        cin >> query;
        if(query == "ADDV") {
            graph.addV();
        } else if(query == "ADDE") {
            cin >> param1 >> param2 >> param3;
            graph.addE(param1, param2, param3);
        } else if(query == "DELV") {
            cin >> param1;
            graph.delV(param1);
        } else if(query == "DELE") {
            cin >> param1 >> param2 ;
            graph.delE(param1, param2);
        } else if(query == "Prims") {
            cin >> param1;
            graph.prim(param1);
        } else if(query == "Kruskal") {
            graph.kruskal();
        } else if(query == "TreeUptodate") {
            graph.treeUpToDate();
        } else if(query == "DisplayTree") {
            graph.displayTree();
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
