#pragma once
#ifndef Warrior_h
#define Warrior_h
#include "CommonStatistics.h"
using namespace std;

class Warrior : public CommonStatistics
{
private:
	int HealDieCount;
	int HealDieSides;
	int IniMod;
public:
	Warrior(string);
	int getHealDieCount();
	int getHealDieSides();
	int getIniMod();
	void printStats();
	int rollInitiative();
	int rollAttack();
	void rollHeal();
	void setHealth(int);
};

//constructor
Warrior::Warrior(string n) : CommonStatistics(n)
{
	health = 20;
	HealDieCount = 2;
	HealDieSides = 5;
	AtkDieCount = 1;
	AtkDieSides = 6;
	armor = 5;
	AtkMod = 3;
	IniMod = 4;
}

//returns number of healing dice
int Warrior::getHealDieCount()
{
	return HealDieCount;
}

//returns number of sides on heal dice
int Warrior::getHealDieSides()
{
	return HealDieSides;
}

//returns initiative modifier
int Warrior::getIniMod()
{
	return IniMod;
}

//prints statistics
void Warrior::printStats()
{
	cout << "Warrior " << name << "'s current stats:" << endl;
	cout << "Health: " << health << endl;
	cout << "Healing Die: " << HealDieCount << " D" << HealDieSides << endl;
	cout << "Base Attack Die: " << AtkDieCount << " D" << AtkDieSides << endl;
	cout << "Armor: " << armor << endl;
	cout << "Attack Modifier (Strength): " << AtkMod << endl;
	cout << "Initiative Modifier (Speed): " << IniMod << endl;
}

//rolls initiative die and returns value
int Warrior::rollInitiative()
{
	int roll = rand() % 20 + 1;
	cout << "You rolled one dice (1-20): Initiative score of " << roll << " + a speed modifier of " << IniMod;
	roll += IniMod;
	cout << " for a total of " << roll << endl;
	return roll;
}

//rolls attack dice and returns value
int Warrior::rollAttack()
{
	int roll = (rand() % AtkDieSides + 1);
	cout << "You rolled " << AtkDieCount << " dice (1-" << AtkDieSides << "): Damage score of " << roll << " + a strength modifier of " << AtkMod;
	roll += AtkMod;
	cout << " for a total of " << roll << endl;
	return roll;
}

//rolls healing dices and adds value to health
void Warrior::rollHeal()
{
	int roll = (rand() % HealDieSides + 1) + (rand() % HealDieSides + 1);
	health += roll;
	cout << "You heal yourself for " << roll << " hit points!" << endl;
	cout << "Total HP is now: " << health;
	cout << endl;
}

//updates health w user input (for healing up after mage encounter)
void Warrior::setHealth(int h)
{
	health = h;
}

#endif
