// lab 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Dragon.h"
#include "WildPig.h"
using namespace std;

int main()
{
    shared_ptr<Player> player1 = make_shared<Player>("Timmy");
    cout << "Player ";
    player1->DrawOnScreen();
    
    shared_ptr<Monster> monster1 = make_shared<Monster>("UFO");
    cout << "Monster ";
    monster1->DrawOnScreen();

    shared_ptr<WildPig> wildpig1 = make_shared<WildPig>("Piglet");
    cout << "WildPig ";
    wildpig1->DrawOnScreen();

    shared_ptr<Dragon> dragon1 = make_shared<Dragon>("Viserion");
    cout << "Dragon ";
    dragon1->DrawOnScreen();



    return 0;
}


