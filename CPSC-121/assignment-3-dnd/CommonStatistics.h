#pragma once
#ifndef CommonStatistics_h
#define CommonStatistics_h
#include <iostream>
#include <string>
using namespace std;

class CommonStatistics
{
protected:
	string name;
	int health;
	int AtkDieCount;
	int AtkDieSides;
	int armor;
	int AtkMod;
public:
	CommonStatistics(string);
	string getName();
	int getHealth();
	int getAtkDieCount();
	int getAtkDieSides();
	int getArmor();
	int getAtkMod();
	virtual void printStats();
	virtual int rollInitiative();
	virtual int rollAttack();
	void takeDamage(int);
};

CommonStatistics::CommonStatistics(string n)
{
	name = n;
	health = 0;
	AtkDieCount = 0;
	AtkDieSides = 0;
	armor = 0;
	AtkMod = 0;
}

string CommonStatistics::getName()
{
	return name;
}

int CommonStatistics::getHealth()
{
	return health;
}

int CommonStatistics::getAtkDieCount()
{
	return AtkDieCount;
}

int CommonStatistics::getAtkDieSides()
{
	return AtkDieSides;
}

int CommonStatistics::getArmor()
{
	return armor;
}

int CommonStatistics::getAtkMod()
{
	return AtkMod;
}
//default printStats()  
void CommonStatistics::printStats()
{
	cout << "Health: " << health << endl;
	cout << "Base Attack Die: " << AtkDieCount << " D" << AtkDieSides << endl;
	cout << "Armor: " << armor << endl;
	cout << "Attack Modifier: " << AtkMod << endl;
}
//default rollInitiative()
int CommonStatistics::rollInitiative()
{
	int roll = rand() % 20 + 1;
	cout << "Entity rolled one dice (1-20): Initiative score of " << roll << " and has no bonus speed modifier" << endl;
	return roll;
}
//default rollAttack()
int CommonStatistics::rollAttack()
{
	int roll = AtkDieCount * (rand() % AtkDieSides + 1);
	cout << "Entity rolled " << AtkDieCount << "dice (1-" << AtkDieSides << "): Damage score of " << roll << "+ a strength modifier of " << AtkMod;
	roll += AtkMod;
	cout << " for a total of " << roll << endl;
	return roll;
}
//takes input and subtracts value from total health
void CommonStatistics::takeDamage(int d)
{
	health -= d;
	cout << name << " has taken " << d << " damage and is now at " << health << " HP" << endl;
}

#endif
