// assignment 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Warrior.h"
#include "Mage.h"
#include "Rogue.h"
using namespace std;

int main()
{
    //creating objects
    shared_ptr<Warrior> knight = make_shared<Warrior>("Knight Timmy");
    cout << "You are now Knight Timmy, a ferocious Warrior" << endl;

    shared_ptr<Mage> wizard = make_shared<Mage>("Wizard Gandolfo");
    cout << "A Mage named Wizard Gandolfo appears and is ready to battle!" << endl;
    cout << endl;

    //prints stats of player and enemy
    knight->printStats();
    cout << endl;

    wizard->printStats();
    cout << endl;

    bool playerTurn = false;
    int choice;

    bool gameOver = false;

    //game loop for mage battle
    while (knight->getHealth() > 0 && wizard->getHealth() > 0)
    {
        //rolling/comparing initiative
        if (knight->rollInitiative() >= wizard->rollInitiative())
        {
            playerTurn = true;
        }
        cout << endl;
        
        //if player rolls higher initiative...
        if (playerTurn)
        {
            cout << "Your Move:" << endl;
            cout << "What will you do?" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Heal" << endl;
            cin >> choice;

            if (choice == 1)
            {
                wizard->takeDamage(knight->rollAttack());
            }

            if (choice == 2)
            {
                knight->rollHeal();
            }

            playerTurn = false;
            cout << endl;

            //checks if either entity died
            if (knight->getHealth() <= 0 || wizard->getHealth() <= 0)
                break;

            cout << wizard->getName() << "'s Move:" << endl;
            knight->takeDamage(wizard->rollAttack());
            cout << endl;
        }

        //if enemy rolls higher initiative...
        else
        {
            cout << wizard->getName() << "'s Move:" << endl;
            knight->takeDamage(wizard->rollAttack());
            cout << endl;

            //checks if either entity died
            if (knight->getHealth() <= 0 || wizard->getHealth() <= 0)
                break;

            cout << "Your Move:" << endl;
            cout << "What will you do?" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Heal" << endl;
            cin >> choice;

            if (choice == 1)
            {
                wizard->takeDamage(knight->rollAttack());
            }

            if (choice == 2)
            {
                knight->rollHeal();
            }
            cout << endl;
        }
    }

    //if player dies
    if (knight->getHealth() <= 0)
    {
        cout << "You have been slain :/ Game Over!" << endl;
    }

    //if wizard dies, resets health to 20 and begins rogue battle
    if (wizard->getHealth() <= 0)
    {
        cout << "The Mage has been slain!" << endl;
        cout << endl;

        //reset health
        knight->setHealth(20);
        cout << "A magical fairy visits you, health has been reset to 20!" << endl;

        //creating assassin jim
        shared_ptr<Rogue> assassin = make_shared<Rogue>("Assassin Jim");
        cout << "A Rogue named Assassin Jim appears and is ready to battle!" << endl;
        cout << endl;

        //display stats
        knight->printStats();
        cout << endl;
        assassin->printStats();
        cout << endl;

        //game loop for rogue battle
        while (knight->getHealth() > 0 && assassin->getHealth() > 0)
        {
            //rolling/comparing initiative
            if (knight->rollInitiative() >= assassin->rollInitiative())
            {
                cout << endl;
                playerTurn = true;
            }

            //if player rolls higher initiative...
            if (playerTurn)
            {
                cout << "Your Move:" << endl;
                cout << "What will you do?" << endl;
                cout << "1. Attack" << endl;
                cout << "2. Heal" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    if (!(assassin->checkDodge()))
                    {
                        assassin->takeDamage(knight->rollAttack());
                    }
                    else
                    {
                        cout << assassin->getName() << " dodged the attack!" << endl;
                    }
                }
                
                if (choice == 2)
                {
                    knight->rollHeal();
                }
                playerTurn = false;
                cout << endl;
                //check if either entity died

                if (knight->getHealth() <= 0 || assassin->getHealth() <= 0)
                    break;

                cout << assassin->getName() << "'s Move:" << endl;
                knight->takeDamage(assassin->rollAttack());
                cout << endl;
            }

            //if enemy rolls higher initiative...
            else
            {
                cout << assassin->getName() << "'s Move:" << endl;
                knight->takeDamage(assassin->rollAttack());
                cout << endl;

                //check if either entity died
                if (knight->getHealth() <= 0 || assassin->getHealth() <= 0)
                    break;

                cout << "Your Move:" << endl;
                cout << "What will you do?" << endl;
                cout << "1. Attack" << endl;
                cout << "2. Heal" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    if (!(assassin->checkDodge()))
                    {
                        assassin->takeDamage(knight->rollAttack());
                    }

                    else
                    {
                        cout << assassin->getName() << " dodged the attack!" << endl;
                    }
                }

                if (choice == 2)
                {
                    knight->rollHeal();
                }
                cout << endl;
            }
        }

        if (knight->getHealth() <= 0)
        {
            cout << "You have been slain :/ Game Over!" << endl;
        }

        //if wizard dies, resets health to 20 and begins rogue battle
        if (assassin->getHealth() <= 0)
        {
            cout << "The Rogue has been slain!" << endl;
            cout << endl;
            cout << "You Win!" << endl;
        }
    }

    return 0;
}
