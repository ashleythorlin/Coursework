#pragma once
#ifndef Game_h
#define Game_h
#include <time.h>

using namespace std;


class Game
{
private:
	int d1, d2, d3;
public:
	Game(); //randomly assigns values to the dice d1, d2, and d3
	~Game(); //also prints when object is destroyed
	//getters
	int getD1();
	int getD2();
	int getD3();
	//setters
	void setD1(int d);
	void setD2(int d);
	void setD3(int d);
	int checkMatch(); //checks how many of the dice match

};

//constructor - randomly assigns values to the dice d1, d2, and d3
Game::Game()
{
	d1 = rand() % 6 + 1;
	d2 = rand() % 6 + 1;
	d3 = rand() % 6 + 1;
}

//deconstructor - also prints when object is destroyed
Game::~Game()
{
	cout << "Deconstructor called on dice object." << endl;
}

//getters
int Game::getD1()
{
	return d1;
}

int Game::getD2()
{
	return d2;
}

int Game::getD3()
{
	return d3;
}

//setters
void Game::setD1(int d)
{
	d1 = d;
}

void Game::setD2(int d)
{
	d2 = d;
}

void Game::setD3(int d)
{
	d3 = d;
}

//checks how many of the dice match
int Game::checkMatch()
{
	int counter = 0;
	if (d1 == d2)
	{
		counter++;
	}
	if (d1 == d3)
	{
		counter++;
	}
	if (d2 == d3)
	{
		counter++;
	}
	return counter;
}

#endif
