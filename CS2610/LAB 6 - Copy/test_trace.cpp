#include <fstream>
#include <iostream>
using namespace std;

#define A "1124567b"
#define B "12345678"
#define C "2341765c"
#define D "3421764d"
#define E "1234566a"
#define F "22225644"

int main() {
    ofstream fout;
    fout.open("trace.txt");
    fout << A << endl;
    fout << B << endl;
    fout << C << endl;
    fout << D << endl;
    fout << C << endl;
    fout << D << endl;
    fout << C << endl;
    fout << D << endl;
    fout << E << endl;
    fout << B << endl;
    fout << A << endl;
    fout << D << endl;
    fout << C << endl;
    fout << D << endl;
    fout << C << endl;
    fout << D;
}