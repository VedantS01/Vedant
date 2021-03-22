#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define ADDV "ADDV"
#define ADDE "ADDE"
#define DELV "DELV"
#define DELE "DELE"
#define BFS "BFS"
#define SSP "SSP"

template <class T>
class AdjNode {
    public:
    int vertex;
    T weight;
    AdjNode<T>();
    AdjNode<T>(int v, T w) {
        vertex = v;
        weight = w;
    }
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

template <class T>
class Graph {
    typedef pair<T, int> Node; //used in bfs and ssp;
    vector<vector<AdjNode<T>>> adjLists;
    int vertices;
    public:
    Graph<T>() {
        vertices = 0;
    }
    Graph<T>(int v) {
        vertices = v;
        adjLists = vector<vector<AdjNode<T>>>(v);
    }
    void addV() {
        adjLists.push_back(vector<AdjNode<T>>());
        vertices++;
    }
    void addE(int v1, int v2, T w) {
        if(v1 >= vertices || v2 >= vertices) {
            cout << "ERROR: INVALID VERTICES\n" ;
            exit(0);
        }
        //TODO: improve: check if the vertex does already exists, if it does, update the weight.
        adjLists[v1].push_back(AdjNode<T>(v2, w));
        adjLists[v2].push_back(AdjNode<T>(v1, w));
    }
    void delV(int v) {
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
    void delE(int v1, int v2) {
        for(auto i = adjLists[v1].begin(); i != adjLists[v1].end(); i++) {
            if((*i).vertex == v2) {
                adjLists[v1].erase(i);
                break;
            }
        }
        for(auto i = adjLists[v2].begin(); i != adjLists[v2].end(); i++) {
            if((*i).vertex == v1) {
                adjLists[v2].erase(i);
                break;
            }
        }
    }
    void bfs(int v) {
        priority_queue<Node, vector<Node>, greater<Node>> helperQueue;
        queue<int> que;
        Node node;
        node.first = 0;
        node.second = v;
        bool visited[vertices] = {false};
        visited[v] = true;
        que.push(v);
        while (!que.empty()) {
            int w = que.front();
            que.pop();
            cout << w << " ";
            for(auto i = adjLists[w].begin(); i != adjLists[w].end(); i++) {
                int u = (*i).vertex;
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
    void ssp(int source) {
        priority_queue<Node, vector<Node>, greater<Node>> helperQueue;
        
        vector<T> distances(vertices, (T)INFINITY) ;
        distances[source] = 0;

        Node node;
        node.first = 0;
        node.second = source;

        helperQueue.push(node);
        while (!helperQueue.empty()) {
            /* code */
            int u = helperQueue.top().second;
            //T weight = helperQueue.top().first;
            helperQueue.pop();

            for(auto i = adjLists[u].begin(); i != adjLists[u].end(); i++) {
                int v = (*i).vertex;
                int weight = (*i).weight;
                if(distances[v] > distances[u] + weight) {
                    distances[v] = distances[u] + weight ;
                    node.first = distances[v];
                    node.second = v;
                    helperQueue.push(node);
                }
            }
        }
        for(int i = 0; i < vertices; i++) {
            cout << distances[i] << " ";
        }
        cout << endl;
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int initVertices;
    int queries;
    cin >> initVertices >> queries;
    string query;
    int param1, param2;
    int param3;
    Graph<int> graph(initVertices);
    vector<int> v;
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
            cout << "unrecognised command called:\n";
        }
        queries--;
    }
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
            cout << "unrecognised command called:\n";
        }
        queries--;
    }
    return 0;
}
