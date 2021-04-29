/**
 * 
 *  FILE            :       CS19B074_A9.cpp --  finds maximmum exchange value of one currency to another using legal transactions
 *                                              and also looks out for currency arbitrage opportunities
 *                          
 *                                          --  IMPLEMENTS bellman ford sssp algorithm, complexity O(|V|^3)
 * 
 *  VERSION         :       1.0
 *  AUTHOR          :       Vedant Ashish Saboo, CS19B074
 * 
 *  CREATED         :       20/4/2021 10:03 AM
 *  LAST MODIFIED   :       20/4/2021 2:02 PM
 * 
 **/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

#define INF INFINITY

typedef long double currencyType;

/**
 *  class ColorGraph -- contains graph of colors represented by adjacency matrix
 **/
class ColorGraph {
    private:
    int cNum;                   //number of colors
    vector<vector<int>> cMat;   //matrix of treaty colors
    public:
    ColorGraph(int c) {
        cNum = c;
        cMat = vector<vector<int>> (c);
        for(int i = 0; i < c; i++) {
            cMat[i] = vector<int> (c, 0);
        }
    }
    ColorGraph(){
        
    }
    //add an edge in color graph
    void addE(int c1, int c2) {
        cMat[c1][c2] = 1;
        cMat[c2][c1] = 1;
    }
    //get matrix entry value at given indices
    int getMatVal(int i, int j) {
        return cMat[i][j];
    }
};
/**
 *  end of class
 **/

/**
 *  class CurrencyGraph -- contains information about currency rates and legal exchange values
 *  IMPLEMENTS          -- method bellmanFord(source, target, amount) that produces maximum exchange value of target currency from amount units of source currency.
 **/
class CurrencyGraph {
    int cNum;                           //number of currencies
    vector<vector<currencyType>> cMat;  //currency rates exchange matrix
    vector<int> cList;                  //currency colors
    vector<vector<currencyType>> wMat;  //helps in the method bellmanFord
    ColorGraph T;                       //color graph instance
    public:
    CurrencyGraph(int c, ColorGraph t) {
        cNum = c;
        cList = vector<int> (c);
        cMat = vector<vector<currencyType>> (c);
        wMat = vector<vector<currencyType>> (c);
        for(int i = 0; i < c; i++) {
            cMat[i] = vector<currencyType> (c);
            wMat[i] = vector<currencyType> (c);
        }
        T = t;
        init();
    }
    //add an edge, is a redundant method in this program
    void addE(int c1, int c2, currencyType w) {
        currencyType w1 = - log(w);
        cMat[c1][c2] = w1;
    }
    //initialise the object data 
    void init() {
        for(int i = 0; i < cNum; i++)
            cin >> cList[i];
        currencyType w;
        for(int i = 0; i < cNum; i++)
            for(int j = 0; j < cNum; j++) {
                cin >> w;
                cMat[i][j] = -log(w);
            }
    }
    //implements bellman ford sssp algorithm to compute the best exchange rates
    void bellmanFord(int source, int target, currencyType amount) {
        vector<currencyType> d(cNum, INF);
        d[source] = 0;
        for(int i = 0; i < cNum; i++)
            for(int j = 0; j < cNum; j++) {
                int color1 = cList[i];
                int color2 = cList[j];
                if(color1 == color2 || T.getMatVal(color1, color2) == 1)
                    wMat[i][j] = cMat[i][j];
                else
                    wMat[i][j] = INF;
            }
        //run cNum - 1 times
        for(int k = 1; k < cNum; k++)
            for(int i = 0; i < cNum; i++)
                for(int j = 0; j < cNum; j++){
                        //if edge is tense, relax it
                        if(d[i] != INF && wMat[i][j] != INF && d[j] > d[i] + wMat[i][j])
                            d[j] = d[i] + wMat[i][j];
                }
        //if the target is not reachable, output -1 on stdout
        if(d[target] == INF) {
            cout << "-1" << endl;
            return;
        }
        //check for increasing weight cycle (negative weight cycle in the algorithm terms)
        for (int i = 0; i < cNum; ++i)
            for (int j = 0; j < cNum; ++j)
                if (d[i] != INF && wMat[i][j] != INF && d[i] + wMat[i][j] < d[j]) {
                    //if j is neither source nor target, don't concern. Carry out relaxation
                    if(j != target && j != source) {
                        d[j] = d[i] + wMat[i][j];
                        continue;
                    }
                    //j is target or source, hence a part of negative weight cycle
                    //output "INF" on stdout
                    cout << "INF" << endl;
                    return;
                }
        //no negative weight cycles in the path from source to target, amount max conversion amount
        //using 3 precision in decimal part of the amount
        cout << std::setprecision(3) << std::fixed << exp(-d[target]) * amount << endl;
        return;
    }
};
/**
 *  end of class
 **/

/**
 *  main        --      program execution begins here
 *  args        --      none
 *  returns     --      int
 *  bugs        --      none
 **/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int C;
    cin >> C;
    ColorGraph T(C);
    int E;
    cin >> E;
    int param1, param2;
    currencyType param3;
    for(int i = 0; i < E; i++) {
        cin >> param1 >> param2;
        T.addE(param1, param2);
    }
    int N;
    cin >> N;
    CurrencyGraph G(N, T);
    int Q;
    cin >> Q;
    while(Q>0) {
        cin >> param1 >> param2 >> param3 ;
        G.bellmanFord(param1, param2, param3);
        Q--;
    }
    return 0;
}

/**
 * END of FILE
 **/
