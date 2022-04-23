#pragma once
#ifndef NBA_h
#define NBA_h

#include "Athlete.h"
#include <iostream>
using namespace std;

class NBA :public Athlete
{
private:
	string positions[5] = { "Point Guard", "Shooting Guard", "Small Forward", "Power Forward", "Center" };
public:
	NBA(string, double);
	void pickLeaguePosition();
	void displayLeagueSalaryData();
};

NBA::NBA(string sport, double sal) :Athlete(sport, sal)
{
	salary = sal;
	league = sport;
}


void NBA::pickLeaguePosition()
{
	cout << "Which position does the athlete play? (1-5)" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ": " << positions[i]<<endl;
	}

	int choice;
	cin >> choice;
	
	//exception handling
	try
	{
		if (choice < 1 || choice > 5)
			throw string("Invalid input: setting default value 1.");
	}
	catch (string exceptionString)
	{
		cout << exceptionString << endl;
		choice = 1;
	}

	choice--;
	position = positions[choice];
	cout << "Athlete Data: NBA " << position << endl;
}

void NBA::displayLeagueSalaryData()
{
	double comparison = 100 * (salary / 4580000.00);
	cout << "This Athlete's salary of $" << salary << " compares to " << comparison << "% of the average NBA player's salary of $4580000.00.";
	cout << endl;
}
#endif
