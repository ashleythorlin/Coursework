// lab 10 smart pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

using namespace std;

//prototypes

void rerollDice(shared_ptr<Game> game); //allows user to reroll one of the dice
void displayDice(shared_ptr<Game> game);//displays values of dice
void stateMatch(shared_ptr<Game> game); //prints out the amount of matching dice


int main()
{
    srand(time(0));

    //shared pointer 2
    cout << "===Creating Shared Pointer #1 to manage the object===" << endl;
    shared_ptr<Game> game1 = make_shared<Game>();
    displayDice(game1);
    stateMatch(game1);

    cout << endl;

    //shared pointer 2
    cout << "===Now creating Shared Pointer #2 to manage the same object===" << endl;
    shared_ptr<Game> game2 = game1;
    rerollDice(game2);
    displayDice(game1);
    stateMatch(game1);

    cout << endl;

    //check utilization/references
    bool checking = true;

    while (checking == true)
    {
        cout << "===Checking if pointers are being utilized===" << endl;
        if (game1)
        {
            cout << "Ptr 1 currently points to an object" << endl;
        }
        else
        {
            cout << "Ptr 1 does not point to an object" << endl;
        }
        if (game2)
        {
            cout << "Ptr 2 currently points to an object" << endl;
        }
        else
        {
            cout << "Ptr 2 does not point to an object" << endl;
        }

        cout << endl;

        cout << "Ptr 1's # of references in shared grouping: " << game1.use_count() << endl;
        cout << "Ptr 2's # of references in shared grouping: " << game2.use_count() << endl;

        cout << endl;

        //releases pointers in order
        if (game1)
        {
            cout << "===Releasing Pointer #1===" << endl;
            game1.reset();
        }
        else if (game2)
        {
            cout << "===Releasing Pointer #2===" << endl;
            game2.reset();
        }
        else
        {
            checking = false;
        }
    }
    
    
    //release pointer 1


    return 0;
}

void rerollDice(shared_ptr<Game> game)
{
    int diceNum;
    cout << "Pick a dice to reroll:" << endl;
    cin >> diceNum;
    if (diceNum == 1)
    {
        game->setD1(rand() % 6 + 1);
    }
    if (diceNum == 2)
    {
        game->setD2(rand() % 6 + 1);
    }
    if (diceNum == 3)
    {
        game->setD3(rand() % 6 + 1);
    }
}

void displayDice(shared_ptr<Game> game)
{
    cout << "Dice #1 is " << game->getD1() << endl;
    cout << "Dice #2 is " << game->getD2() << endl;
    cout << "Dice #3 is " << game->getD3() << endl;
}

void stateMatch(shared_ptr<Game> game)
{
    int count = game->checkMatch();
    if (count == 0)
    {
        cout << "No dice are equal." << endl;
    }
    if (count == 1)
    {
        cout<<"Two dice are equal."<<endl;
    }
    if (count >= 2)
    {
        cout<<"All three dice are equal."<<endl;
    }
}



