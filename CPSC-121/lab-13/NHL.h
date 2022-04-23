#pragma once
#ifndef NHL_h
#define NHL_h

#include "Athlete.h"
using namespace std;

class NHL :public Athlete
{
private:
	string positions[4] = { "Center", "Winger", "Defenseman", "Goalie"};
public:
	NHL(string, double);
	void pickLeaguePosition();
	void displayLeagueSalaryData();
};

NHL::NHL(string sport, double sal) :Athlete(sport, sal)
{
	salary = sal;
	league = sport;
}

void NHL::pickLeaguePosition()
{
	cout << "Which position does the athlete play? (1-4)" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ": " << positions[i] << endl;
	}

	int choice;
	cin >> choice;

	//exception handling
	try
	{
		if (choice < 1 || choice > 4)
			throw string("Invalid input: setting default value 1.");
	}
	catch (string exceptionString)
	{
		cout << exceptionString << endl;
		choice = 1;
	}

	choice--;
	position = positions[choice];
	cout << "Athlete Data: NHL " << position << endl;
}

void NHL::displayLeagueSalaryData()
{
	double comparison = 100 * (salary / 2620000.00);
	cout << "This Athlete's salary of $" << salary << " compares to " << comparison << "% of the average NHL player's salary of $2620000.00.";
	cout << endl;
}
#endif
