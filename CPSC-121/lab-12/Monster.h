#pragma once
#ifndef Monster_h
#define Monster_h
#include <iostream>
#include "Creature.h"

using namespace std;

class Monster :public Creature
{
public:
	Monster(string);
	void DoAction();
	void DrawOnScreen();
};

Monster::Monster(string n) :Creature(n)
{
	CreatureName = n;
}

void Monster::DoAction()
{
	cout << "is doing monster stuff!" << endl;
}

void Monster::DrawOnScreen()
{
	cout << CreatureName << " ";
	DoAction();
}

#endif
