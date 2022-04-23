#pragma once
#ifndef Rogue_h
#define Rogue_h
#include "CommonStatistics.h"
using namespace std;

class Rogue : public CommonStatistics
{
private:
	int IniMod;
	double DodgeVal;
public:
	Rogue(string);
	int getIniMod();
	double getDodgeVal();
	void printStats();
	int rollInitiative();
	int rollAttack();
	bool checkDodge();
};

//constructor
Rogue::Rogue(string n) : CommonStatistics(n)
{
	health = 10;
	AtkDieCount = 2;
	AtkDieSides = 4;
	armor = 3;
	AtkMod = 4;
	IniMod = 5;
	DodgeVal = 50;
}

//returns initiative modifier
int Rogue::getIniMod()
{
	return IniMod;
}

//returns dodge value
double Rogue::getDodgeVal()
{
	return DodgeVal;
}

//prints statistics
void Rogue::printStats()
{
	cout << "Rogue " << name << "'s current stats:" << endl;
	cout << "Health: " << health << endl;
	cout << "Base Attack Die: " << AtkDieCount << " D" << AtkDieSides << endl;
	cout << "Armor: " << armor << endl;
	cout << "Attack Modifier (Agility): " << AtkMod << endl;
	cout << "Initiative Modifier (Speed):" << IniMod << endl;
	cout << "Dodge: " << DodgeVal << "% chance to dodge an incoming attack" << endl;
}

//rolls initiative die and returns value
int Rogue::rollInitiative()
{
	int roll = rand() % 20 + 1;
	cout << "The Rogue rolled one dice (1-20): Initiative score of " << roll << " + a speed modifier of " << IniMod;
	roll += IniMod;
	cout << " for a total of " << roll << endl;
	return roll;
}

//rolls attack dice and returns value
int Rogue::rollAttack()
{
	int roll = (rand() % AtkDieSides + 1) + (rand() % AtkDieSides + 1);
	cout << name << " rolled " << AtkDieCount << " dice (1-" << AtkDieSides << "): Damage score of " << roll << " + a agility modifier of " << AtkMod;
	roll += AtkMod;
	cout << " for a total of " << roll << endl;
	return roll;
}

//checks if rogue dodges attack before calling takeDamage()
bool Rogue::checkDodge()
{
	int roll = (rand() % 100 + 1);
	if (roll <= DodgeVal)
		return true;
	else
		return false;
}

#endif
