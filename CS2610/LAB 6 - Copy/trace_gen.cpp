#include <fstream>
#include <iostream>
using namespace std;

#define C 1000000

int main() {
    string rw;
    const string stable = "1245";
    string rest;
    ofstream fout;
    fout.open("trace.txt");
    for(long long int i = 0; i < C; i++) {
        rw.clear();
        rest.clear();
        int r = rand() % 2;
        r = 8 * r;
        r++;
        rw.push_back((char) (r + 48));
        //int rest1 = rand() % 16, rest2 = rand() % 16, rest3 = rand() % 16;
        for(int i = 0; i < 3; i++) {
            int rest1 = rand() % 16;
            if(rest1 >= 10) rest1 += 87;
            else rest1 += 48;
            rest.push_back(rest1);
        }
        fout << rw << stable << rest << endl;
    }
}