// Homework 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Spring2021.h"
using namespace std;

//default constructor
Spring2021::Spring2021()
{
	num = 50;
	courses = new unsigned int[num];
}
//one arg constructor
Spring2021::Spring2021(unsigned int numberOfStudents)
{
	num = numberOfStudents;
	courses = new unsigned int[num];
}
//copy constructor
Spring2021::Spring2021(const Spring2021& original)
{
	courses = new unsigned int[num];
	for (int i = 0; i < num; i++)
	{
		courses[i] = original.courses[i];
	}
}
//destructor
Spring2021::~Spring2021()
{
	delete[] courses;
}
//member function
unsigned int Spring2021::coursesAtIndex(unsigned int index)
{
	return courses[index];
}