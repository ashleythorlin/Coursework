#pragma once
#ifndef MLB_h
#define MLB_h

#include "Athlete.h"
using namespace std;

class MLB :public Athlete
{
private:
	string positions[5] = { "Pitcher", "Catcher", "Baseman", "Shortstop", "Outfielder" };
public:
	MLB(string, double);
	void pickLeaguePosition();
	void displayLeagueSalaryData();
};

MLB::MLB(string sport, double sal) :Athlete(sport, sal)
{
	salary = sal;
	league = sport;
}

void MLB::pickLeaguePosition()
{
	cout << "Which position does the athlete play? (1-5)" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ": " << positions[i] << endl;
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
	cout << "Athlete Data: MLB " << position << endl;
}

void MLB::displayLeagueSalaryData()
{
	double comparison = 100 * (salary / 4170000.00);
	cout << "This Athlete's salary of $" << salary << " compares to " << comparison << "% of the average MLB player's salary of $4170000.00";
	cout << endl;
}
#endif
