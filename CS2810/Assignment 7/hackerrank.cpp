/**-----------------------------------------------------------------
 * 
 *  FILE            :           MaximumSpanningTree.cpp 
 * 
 *  PURPOSE         :           Submission to hackerrank problem A7 - MST in Assignment 7
 * 
 *  VERSION         :           1.2
 *  AUTHOR          :           Vedant Ashish Saboo -- CS19B074
 * 
 *  CREATED         :           4/5/2021 3:40 PM
 *  LAST MODIFIED   :           4/6/2021 3:30 PM
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

/**
 *  template class MST<T>   :       computes and represents maximum spanning tree of the parent graph
 **/
template <class T>
class MST : public Graph<T> {
    private:
    const string NO = "NO";
    const string YES = "YES";
    protected:
    vector<vector<AdjNode<T>>> tree;    //2d vector used to implement adjacency lists of the mst
    bool flagUpToDate;                  //a flag which is set if the spanning tree is up to date
    private:
    typedef pair<T, int> Node;
    public:
    MST():Graph<T>() {
        flagUpToDate = false;
    }
    MST(int n):Graph<T>(n) {
        flagUpToDate = false;
    }
    
    //finding maximum spanning tree using Prim's algorithm
    void prim(int source) {

        //cost vector - stores weights of edges of the vertex and its parent in MST. For parent, cost is zero.
        vector<T> cost(Graph<T>::vertices, (T)INT_MAX); //set initially to int max
        cost[source] = 0; //set source cost as 0

        //parent vector - stores parent of a vertex in mst. Note, this is the same vertex with which the given vertex has an edge of cost 0
        vector<int> parent(Graph<T>::vertices, -1);

        //present vector - stores the status of a vertex - whether it has been included in the MST yet.
        vector<bool> present(Graph<T>::vertices, false);

        //clear the tree
        tree.clear();
        //initialise with single vertices
        tree = vector<vector<AdjNode<T>>> (Graph<T>::vertices) ;

        //a min heap (priority queue)
        priority_queue< Node, vector<Node>, greater<Node> > minHeap;
        //push the source vertex
        minHeap.push({0,source});

        int v, u;
        T w;

        //run the loop while minHeap is not empty
        while(!minHeap.empty()) {
            v = minHeap.top().second;
            minHeap.pop();
            if(present[v]) continue; //if the vertex is already present in mst, skip the iteration
            
            //mark vertex as present
            present[v] = true;

            //if the vertex is not source (root) insert the tree edge corresponding to that vertex from its parent
            if(parent[v] != -1) {
                tree[v].push_back(AdjNode<T>(parent[v], cost[v]));
                tree[parent[v]].push_back(AdjNode<T>(v, cost[v]));
            }

            //traverse adjacency list of the vertex
            for(auto i = Graph<T>::adjLists[v].begin(); i != Graph<T>::adjLists[v].end(); i++) {
                u = (*i).vertex;
                w = (*i).weight;

                //if the vertex u is not present AND its edge with v is of smaller cost that that registered, update the cost
                if(!present[u]) {
                    if(w < cost[u]) {
                        cost[u] = w;
                        parent[u] = v;
                        minHeap.push({w,u}); //push updated pair in min heap
                    }
                }
            }
        }

        //find the total weight of the mst
        T total = (T)0;
        for(int i = 0; i < Graph<T>::vertices; i++) {
            if(cost[i] == INT_MAX) {    //indicates that graph is discontinous, 
                                        //(which won't be the case according to the problem statement, but regardless)
                total = INT_MAX;
                break;
            }
            total += cost[i];
        }

        cout << total << endl;

        //set the up to date flag
        flagUpToDate = true;
    }
    
    //finding maximum spanning tree using Kruskal's algorithm
    void kruskal() {
        //This method internally uses disjoint sets data structure

        //parent vector - parenr[i] denotes the root of the subtree containing i
        vector<int> parent(Graph<T>::vertices);

        //rank vector - rank[i] denotes the height of the tree containing i
        //we will be using rank values restrictively for roots of the sub trees
        vector<int> rank(Graph<T>::vertices);
        //clear the tree, initialise with single vertices
        tree.clear();
        tree = vector<vector<AdjNode<T>>> (Graph<T>::vertices) ;
        //set mst weight to be 0 initially
        T mstWeight = (T)0;
        //initially, every vertex is a separate tree of 0 rank
        for(int i = 0; i < Graph<T>::vertices; i++) {
            parent[i] = i ;
            rank[i] = 0 ;
        }

        //min heap used to sort the edges
        priority_queue< pair<T, pair<int, int>>, vector<pair<T, pair<int, int>>>, greater<pair<T, pair<int, int>>> > heap;
        for(int i = 0; i < Graph<T>::vertices; i++) {
            for(auto j = Graph<T>::adjLists[i].begin(); j != Graph<T>::adjLists[i].end(); j++) {
                if(j->vertex > i) {
                    heap.push({j->weight, {i, j->vertex}}) ;
                }
            }
        }

        //iterating in the increasing order of the weights of the edges
        while(!heap.empty()) {
            int u = heap.top().second.first;
            int v = heap.top().second.second;
            T w = heap.top().first;
            
            heap.pop();

            //findParent finds the root of the tree containing a vertex, and updates all the vertices with their parents during the process
            int parentU = findParent(parent, u);
            int parentV = findParent(parent, v);

            //unmatching roots imply that the components are distinct
            if(parentU != parentV) {
                //edge connects two different components
                //add that edge
                tree[u].push_back(AdjNode<T>(v, w));
                tree[v].push_back(AdjNode<T>(u, w));
                //update mst weight
                mstWeight += w;

                //merge method merges the two components by updating parents and ranks of the roots
                merge(parent, rank, parentU, parentV);
            }

        }

        cout << mstWeight << endl;

        flagUpToDate = true;
    }
    
    //returns the up to date status of the mst, also prints on STDOUT
    bool treeUpToDate() {
        if(flagUpToDate) {
            cout << YES << endl;
        }
        else {
            cout << NO << endl;
        }
        return flagUpToDate;
    }
    
    //display tree
    void displayTree() {
        //use a min heap to sort the edges; the format pair<T , pair<int, int>> is used for printing in appropriate order
        priority_queue< pair<T, pair<int, int>>, vector<pair<T, pair<int, int>>>, greater<pair<T, pair<int, int>>> > heap;
        for(int i = 0; i < Graph<T>::vertices; i++) {
            for(auto j = tree[i].begin(); j != tree[i].end(); j++) {
                if(j->vertex > i) { //add the edge only when second vertex is higher than first; avoids duplication
                    heap.push({j->weight, {i, j->vertex}}) ;
                }
            }
        }

        //extract the vertices from the heap and print them
        while(!heap.empty()) {
            int u = heap.top().second.first;
            int v = heap.top().second.second;
            T w = heap.top().first;
            
            heap.pop();

            cout << u << " " << v << " " << w << endl;
        }
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

    private:
    //helpers for kruskal()
    int findParent(vector<int> &parent, int u) {
        if(u != parent[u]) {
            parent[u] = findParent(parent, parent[u]) ;
        }
        return parent[u] ;
    }
    void merge(vector<int> &parent, vector<int> &rank, int u, int v) {
        //assuming u and v are roots of the distinct components
        if (rank[u] > rank[v])
            parent[v] = u;
        else
            parent[u] = v;
  
        if (rank[u] == rank[v])
            rank[v]++;
    }
};
/**
 *  END of class
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
