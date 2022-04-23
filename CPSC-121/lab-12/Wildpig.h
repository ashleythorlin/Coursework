#pragma once
#ifndef WildPig_h
#define WildPig_h
#include <iostream>
#include "Monster.h"

using namespace std;

class WildPig :public Monster
{
public:
	WildPig(string);
	void DoAction();
	void DrawOnScreen();
};

WildPig::WildPig(string n) :Monster(n)
{
	CreatureName = n;
}

void WildPig::DoAction()
{
	cout << "is running!" << endl;
}

void WildPig::DrawOnScreen()
{
	cout << CreatureName << " ";
	DoAction();
}

#endif
