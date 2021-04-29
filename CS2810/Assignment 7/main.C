/*******************************************************
 * 
 * Divya S Prajapati-CS19B067
 * 
 * Purpose : Create Template of class Graph with
 *           type of edgeweight as parameter
 *           Implement the given operations
 * 
 * Note : SSP function 
 *        minDistances initialised with INT_MAX
 *        will give error if type parameter is not 'int'
 * 
 * *****************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <queue>

using namespace std;

typedef int Vertex;

// class Node : Definition {START}
// end point of an edge 
template<class T>
class Node
{
    public:
        Vertex vertex; // vertex
        T weight;      // weight of edge 
}; // class Node : Defnition {END}


// comparision function for Node 
// will be used for BFS and SSP for priority_queue
template<class T>
class Compare
{
    public:
        bool operator()(Node<T> a, Node<T> b)
        {
            if(a.weight>b.weight) return true;
            else if(a.weight<b.weight) return false;
            else
            {
                if(a.vertex>b.vertex) return true;
                else return false;
            }
        }
};

template<class T>
class CompareForTreeOrder
{
    public:
        bool operator()(pair<Vertex, Node<T>> p1, pair<Vertex, Node<T>> p2)
        {
            if(p1.second.weight > p2.second.weight)
            {
                return true;
            }
            else if (p1.second.weight < p2.second.weight)
            {
                return false;
            }
            else if(p2.first <= p1.first)
            {
                if(p2.first == p1.first)
                {
                    if(p2.second.vertex < p1.second.vertex)
                    {
                        return true;
                    }
                    else return false;
                }
                else return true;
            }
            else return false;
        }
};

// class Graph : Definition {START}
//
// Function SSP complexity can be improved using
// extra array which stores the state that node is present in the
// Heap or not accordingly updating or inserting it in Heap
// instead inserting distances each time  
//
template<class T> 
class Graph
{
    protected:
        int totalVertices;              // total # of vertices
        vector<vector<Node<T>>> adjList;// adjacency list

    public:
        Graph(int);                     // to initialise graph list 
                                        //with given vertices
        void addVertex();               // to add a vertex 
        void addEdge(Vertex, Vertex, T);// to add an edge
        void DelEdge(Vertex, Vertex);   // to del an edge
}; // class Graph : Definition {END}

// class Graph : Implementation {START}

/**********************************************************
 * Constructor
 * Args          : number of vertices(int) 
 * Purpose       : to initialise adjList
 *********************************************************/
template<class T>
Graph<T>::Graph(int vertices)
{
    totalVertices = vertices;
    for(int i=0;i<totalVertices;i++)
    {
        vector<Node<T>> newRow;
        adjList.push_back(newRow);
    }
}

/**********************************************************
 * Function      : addVertex
 * Args          : -
 * Purpose       : to add a vertex
 * Return Type   : void 
 *********************************************************/
template<class T>
void Graph<T>::addVertex()
{
    totalVertices++;
    vector<Node<T>> newRow;
    adjList.push_back(newRow);
}

/**********************************************************
 * Function      : addEdge
 * Args          : vertex, vertex, T(weight)
 * Purpose       : to add an edge between given two vertices
 *                 with given weight
 * Return Type   : void
 * Implementation:
 * if vertices are invalid output error message through cerr
 * else
 * => add the edge
 *********************************************************/
template<class T>
void Graph<T>::addEdge(Vertex a, Vertex b, T weight)
{
    if(a<totalVertices && b<totalVertices)
    {
        Node<T> edgeNode;
        edgeNode.vertex = b;
        edgeNode.weight = weight;
        adjList[a].push_back(edgeNode);

        edgeNode.vertex = a;
        adjList[b].push_back(edgeNode);
    }
    else
    {
        cerr << "addEdge : Invalid Index" << "\n";
    }
}

/**********************************************************
 * Function      : DelEdge
 * Args          : vertex, vertex
 * Purpose       : to delete an edge
 * Return Type   : void
 * Implementation:
 * => if edge is not present or invalid index then
 *    output error message through cerr 
 * else del the edge
 *********************************************************/
template<class T>
void Graph<T>::DelEdge(Vertex a, Vertex b)
{
    if(a<totalVertices && b<totalVertices)
    {
        size_t index;
        for(index=0;index<adjList[a].size();index++)
        {
            if(adjList[a][index].vertex==b) break;
        }
        if(index<adjList[a].size())
        {
            adjList[a].erase(adjList[a].begin()+index);
            for(index=0;index<adjList[b].size();index++)
            {
                if(adjList[b][index].vertex==a) break;
            }
            adjList[b].erase(adjList[b].begin()+index);
        }
        else
        {
            cerr << "DelEdge : Invalid Edge" << "\n";
        }
    }
    else
    {
        cerr << "DelEdge : Invalid Index" << "\n";
    }
}

template<class T> 
class MST : public Graph<T>
{
    private:
        vector<vector<Node<T>>> tree;
        bool isUptodate;
        T spanningTreeWeight;
        Vertex findRoot(vector<T>, Vertex);
    public:
        MST(int);
        void addV();               // to add a vertex 
        void addE(Vertex, Vertex, T);// to add an edge
        void DelE(Vertex, Vertex);   // to del an edge
        void treeUptodate();
        void displayTree();
        T prims(Vertex);
        T kruskal();
};

template<class T>
MST<T>::MST(int vertices):Graph<T>(vertices)
{
    for(int i=0;i<vertices;i++)
    {
        vector<Node<T>> newRow;
        tree.push_back(newRow);
    }
    isUptodate = false;
    spanningTreeWeight = 0;
}

template<class T>
void MST<T>::addV()
{
    this->addVertex();
    vector<Node<T>> newRow;
    tree.push_back(newRow);
    isUptodate = false;
}

template<class T>
void MST<T>::addE(Vertex a, Vertex b, T weight)
{
    this->addEdge(a, b, weight);
    isUptodate = false;
}

template<class T>
void MST<T>::DelE(Vertex a, Vertex b)
{
    this->DelEdge(a, b);
    isUptodate = false;
}

template<class T>
void MST<T>::treeUptodate()
{
    if(isUptodate)
    {
        cout << "YES";
    }
    else cout << "NO";
}

template<class T>
void MST<T>::displayTree()
{
    priority_queue<pair<Vertex, Node<T>>, vector<pair<Vertex, Node<T>>>, CompareForTreeOrder<T>> printingOrder;
    vector<bool> isVisited(Graph<T>::totalVertices, false);
    
    for(int i=0;i<Graph<T>::totalVertices;i++)
    {
        vector<Node<T>> edges = tree[i];
        for(size_t j=0;j<edges.size();j++)
        {
            if(!isVisited[edges[j].vertex])
            {
                printingOrder.push(make_pair(i, edges[j]));
            }
        }
        isVisited[i] = true;
    }
    
    while(printingOrder.size()!=0)
    {
        pair<Vertex, Node<T>> p = printingOrder.top();
        printingOrder.pop();
        cout << p.first << " " << p.second.vertex << " " << p.second.weight << endl;
    }
}

template<class T>
T MST<T>::prims(Vertex v)
{
    if(v>=Graph<T>::totalVertices)
    {
        cerr << "Prims : Invalid Vertices" << endl; 
        return -1;
    }
    T result = 0;
    for(int i=0;i<Graph<T>::totalVertices;i++)
    {
        tree[i].clear();
    }
    vector<bool> presentInTree(Graph<T>::totalVertices, false);
    vector<T> key(Graph<T>::totalVertices, INT_MAX);
    vector<Vertex> parent(Graph<T>::totalVertices, -1);
    
    key[v] = 0;
    
    for(int i=0;i<Graph<T>::totalVertices-1;i++)
    {
        int minWeightVertex;
        int minWeight = INT_MAX;
        
        for(int j=0;j<Graph<T>::totalVertices;j++)
        {
            if(!presentInTree[j])
            {
                if(minWeight > key[j])
                {
                    minWeight = key[j];
                    minWeightVertex = j;
                }
            }
        }
        presentInTree[minWeightVertex] = true;
        for(size_t j=0;j<Graph<T>::adjList[minWeightVertex].size();j++)
        {
            Node<T> current = Graph<T>::adjList[minWeightVertex][j];
            if(!presentInTree[current.vertex] && current.weight < key[current.vertex])
            {
                key[current.vertex] = current.weight;
                parent[current.vertex] = minWeightVertex;
            }
        }
    }
    for(int i=0;i<Graph<T>::totalVertices;i++)
    {
        if(i!=v)
        {
            Node<T> treeNode;
            treeNode.vertex = i;
            treeNode.weight = key[i];
            
            tree[parent[i]].push_back(treeNode);
            treeNode.vertex = parent[i];
            tree[i].push_back(treeNode);
            
            result += key[i];
        }
    }
    isUptodate = true;
    spanningTreeWeight = result;
    return result;
}

template<class T>
Vertex MST<T>::findRoot(vector<T> parent, Vertex v)
{
    while(parent[v]!=v)
    {
        v = parent[v];
    }
    return v;
}

template<class T>
T MST<T>::kruskal()
{
    for(int i=0;i<Graph<T>::totalVertices;i++)
    {
        tree[i].clear();
    }
    T result = 0;
    vector<Vertex> parent(Graph<T>::totalVertices);
    vector<bool> isVisited(Graph<T>::totalVertices, false);
    priority_queue<pair<Vertex, Node<T>>, vector<pair<Vertex, Node<T>>>, CompareForTreeOrder<T>> sorted;
     
    for(size_t i=0;i<parent.size();i++) parent[i] = i;
    
    for(int i=0;i<Graph<T>::totalVertices;i++)
    {
        for(size_t j=0;j<Graph<T>::adjList[i].size();j++)
        {
            Node<T> currentNode = Graph<T>::adjList[i][j];
            if(!isVisited[currentNode.vertex])
            {
                sorted.push(make_pair(i,currentNode));   
            }
        }
        isVisited[i] = true;
    }
    
    while(sorted.size()!=0)
    {
        pair<Vertex, Node<T>> p = sorted.top();
        sorted.pop();
        
        Vertex firstRoot = findRoot(parent, p.first);
        Vertex secondRoot = findRoot(parent, p.second.vertex);
        if(firstRoot != secondRoot)
        {
            if(secondRoot != p.second.vertex)
            {
                parent[p.first] = p.second.vertex;
            }
            else
            {
                parent[p.second.vertex] = p.first;
            }
            
            tree[p.first].push_back(p.second);
            Vertex temp = p.first;
            p.first = p.second.vertex;
            p.second.vertex = temp;
            tree[p.first].push_back(p.second); 
            
            result += p.second.weight;
        }
    }
    isUptodate = true;
    spanningTreeWeight = result;
    return result;
}

int main()
{
    int inputVertices;
    int queries;
    cin >> inputVertices >> queries;
    MST<int> treeResult(inputVertices);
    
    while(queries--)
    {
        string command;
        cin >> command;
        if(command == "ADDV")
        {
            treeResult.addV();
        }
        else if(command == "ADDE")
        {
            Vertex a;
            Vertex b;
            int weight;
            cin >> a >> b >> weight;
            treeResult.addE(a, b, weight);
        }
        else if(command == "DELE")
        {
            Vertex a;
            Vertex b;
            cin >> a >> b;
            treeResult.DelE(a, b);
        }
        else if(command == "TreeUptodate")
        {
            treeResult.treeUptodate();
            cout << endl;
        }
        else if(command == "DisplayTree")
        {
            treeResult.displayTree();
        }
        else if(command == "Prims")
        {
            Vertex v;
            int result;
            cin >> v;
            result = treeResult.prims(v);
            cout << result << endl;
        }
        else if(command == "Kruskal")
        {
            int result;
            result = treeResult.kruskal();
            cout << result << endl;
        }
    }
}