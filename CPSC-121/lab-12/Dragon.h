#pragma once
#ifndef Dragon_h
#define Dragon_h
#include <iostream>
#include "Monster.h"

using namespace std;

class Dragon :public Monster
{
public:
	Dragon(string);
	void DoAction();
	void DrawOnScreen();
};

Dragon::Dragon(string n) :Monster(n)
{
	CreatureName = n;
}

void Dragon::DoAction()
{
	cout << "is breathing fire!" << endl;
}

void Dragon::DrawOnScreen()
{
	cout << CreatureName << " ";
	DoAction();
}

#endif
