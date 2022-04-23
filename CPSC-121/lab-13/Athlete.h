#pragma once
#ifndef Athlete_h
#define Athlete_h

#include <iostream>
using namespace std;

class Athlete
{
protected:
	double salary;
	string position;
	string league;
public:
	Athlete(string sport, double sal)
	{
		salary = sal;
		league = sport;
	}

	virtual void pickLeaguePosition() = 0;
	virtual void displayLeagueSalaryData() = 0;
	string getAthletePosition() { return position; }
	string getAthleteSport() { return league; }

};


#endif
