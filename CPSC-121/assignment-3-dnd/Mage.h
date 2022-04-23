#pragma once
#ifndef Mage_h
#define Mage_h
#include "CommonStatistics.h"
using namespace std;

class Mage : public CommonStatistics
{
public:
	Mage(string);
	void printStats();
	int rollInitiative();
	int rollAttack();
};

//constructor
Mage::Mage(string n) : CommonStatistics(n)
{
	health = 15;
	AtkDieCount = 1;
	AtkDieSides = 4;
	armor = 2;
	AtkMod = 5;
}

//prints statistics
void Mage::printStats()
{
	cout << "Mage " << name << "'s current stats:" << endl;
	cout << "Health: " << health << endl;
	cout << "Base Attack Die: " << AtkDieCount << " D" << AtkDieSides << endl;
	cout << "Armor: " << armor << endl;
	cout << "Attack Modifier: " << AtkMod << endl;
}

//rolls initiative die and returns value
int Mage::rollInitiative()
{
	int roll = rand() % 20 + 1;
	cout << "The Mage rolled one dice (1-20): Initiative score of " << roll << " and has no bonus speed modifier" << endl;
	return roll;
}

//rolls attack dice and returns value
int Mage::rollAttack()
{
	int roll = (rand() % AtkDieSides + 1);
	cout << name << " rolled " << AtkDieCount << " dice (1-" << AtkDieSides << "): Damage score of " << roll << " + an intellect modifier of " << AtkMod;
	roll += AtkMod;
	cout << " for a total of " << roll << endl;
	return roll;
}

#endif
