#include <iostream>
#include "Student.h"
using namespace std;

#ifndef DD_H
#define DD_H
typedef int RollNumber;
class DD : public Student
{
private:
    /* data */
    Faculty DDPGuide;
    Faculty TASupervisor;
public:
    DD();
    DD(RollNumber r, string hostel, Faculty facad, float cgpa);
    ~DD();
    Faculty getDDPGuide();
    void setDDPGuide(Faculty);
    Faculty getTAsupervisor();
    void setTAsupervisor(Faculty);
    
};

DD::DD()
{
}

DD::DD(RollNumber r, string hostel, Faculty facad, float cgpa)
{
    this->rollNo = r;
    this->hostel = hostel;
    this->facad = facad;
    this->cgpa = cgpa;
}

DD::~DD()
{
}

Faculty DD::getDDPGuide() {
    return this->DDPGuide;
}

void DD::setDDPGuide(Faculty f) {
    this->DDPGuide = f;
}

Faculty DD::getTAsupervisor() {
    return this->TASupervisor;
}

void DD::setTAsupervisor(Faculty f) {
    this->TASupervisor = f;
}

#endif