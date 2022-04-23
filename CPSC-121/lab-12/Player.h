#pragma once
#ifndef Player_h
#define Player_h
#include <iostream>
#include "Creature.h"

using namespace std;

class Player :public Creature
{
public:
	Player(string);
	void DoAction();
	void DrawOnScreen();
};

Player::Player(string n) :Creature(n)
{
	CreatureName = n;
}

void Player::DoAction()
{
	cout << "is attacking!" << endl;
}

void Player::DrawOnScreen()
{
	cout << CreatureName << " ";
	DoAction();
}

#endif
