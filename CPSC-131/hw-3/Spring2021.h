#pragma once
#ifndef Spring2021_h
#define Spring2021_h
#include <iostream>

using namespace std;
class Spring2021 {
private:

    unsigned int* courses;
    unsigned int num;  // number of students at CollegeA

public:
    // constructors (default, one arg, and copy)
    Spring2021();
    Spring2021(unsigned int numberOfStudents);
    Spring2021(const Spring2021& original);

    // destructor
    ~Spring2021();

    // Member function
    unsigned int coursesAtIndex(unsigned int index);
};

#endif
