// lab 13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#include "NBA.h"
#include "MLB.h"
#include "NHL.h"

int main()
{
    cout.setf(ios::fixed);
    cout.precision(2);

    shared_ptr<Athlete> unknown = nullptr;
    int choice;

    cout << "Which Sport does the athlete play? (1-3)" << endl;
    cout << "1: NBA" << endl << "2: MLB" << endl << "3: NHL" << endl;
    cin >> choice;

    //exception handling for sport
    try
    {
        if (choice < 1 || choice > 3)
            throw string("Invalid input: setting default value 1.");
    }
    catch (string exceptionString)
    {
        cout << exceptionString;
        choice = 1;
    }
    
    cout << endl;
    cout << "What is the Athlete Salary?" << endl;
    double inputSal;
    cin >> inputSal;

    //polymorphism
    if (choice == 1)
    {
        unknown = make_shared<NBA>("NBA", inputSal);
    }
    else if (choice == 2)
    {
        unknown = make_shared<MLB>("MLB", inputSal);
    }
    else
    {
        unknown = make_shared<NHL>("NHL", inputSal);
    }

    unknown->pickLeaguePosition();

    unknown->displayLeagueSalaryData();

    return 0;
}


