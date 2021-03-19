#include <iostream>
#include <vector>
#include "BTech.h"
#include "DD.h"
#include "Faculty.h"
using namespace std;

class IITM
{
private:
    /* data */
    vector<BTech> btechStudents;
    vector<DD> ddStudents;
    vector<Faculty> faculties;
    vector<string> hostels;
public:
    IITM();
    ~IITM();
};

IITM::IITM()
{
}

IITM::~IITM()
{
}
