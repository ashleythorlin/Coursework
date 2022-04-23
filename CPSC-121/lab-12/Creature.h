#pragma once
#ifndef Creature_h
#define Creature_h

#include <string>
using namespace std;


class Creature
{
protected:
	string CreatureName;
public:
	Creature(string);
	virtual void DoAction() = 0;
	virtual void DrawOnScreen() = 0;
};

Creature::Creature(string n)
{
	CreatureName = n;
}
	
#endif
