#include <iostream>
#include "Faculty.h"
using namespace std;

#ifndef STUDENT_H
#define STUDENT_H
typedef int RollNumber;
class Student
{
protected:
    /* data */
    RollNumber rollNo;
    string hostel;
    Faculty facad;
    float cgpa;
public:
    Student(RollNumber r, string hostel, Faculty facad, float cgpa);
    Student();
    ~Student();
    string getHostel();
    Faculty getFacad();
    void changeHostel(string);
};

Student::Student(RollNumber r, string hostel, Faculty facad, float cgpa)
{
    this->rollNo = r;
    this->hostel = hostel;
    this->facad = facad;
    this->cgpa = cgpa;
}

Student::Student()
{
}

Student::~Student()
{
    //delete this;
}

string Student::getHostel() {
    return this->hostel;
}

Faculty Student::getFacad() {
    return this->facad;
}

void Student::changeHostel(string newHostel) {
    this->hostel = newHostel;
}


#endif