#include <iostream>
#include "Student.h"
using namespace std;

#ifndef BTECH_H
#define BTECH_H
typedef int RollNumber;
class BTech : public Student
{
private:
    /* data */
    Faculty BTPGuide;
public:
    BTech();
    BTech(RollNumber r, string hostel, Faculty facad, float cgpa);
    ~BTech();
    Faculty getBTPGuide();
    void setBTPGuide(Faculty);
};

BTech::BTech()
{
}

BTech::BTech(RollNumber r, string hostel, Faculty facad, float cgpa)
{
    this->rollNo = r;
    this->hostel = hostel;
    this->facad = facad;
    this->cgpa = cgpa;
}

BTech::~BTech()
{
}

Faculty BTech::getBTPGuide() {
    return this->BTPGuide;
}

void BTech::setBTPGuide(Faculty f) {
    this->BTPGuide = f;
}

#endif