// lab 14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int palindrome(string, int, int, int);

int main()
{
    palindrome("XYBZBYX", 0, 0, 0);
    palindrome("XYBYYYX", 0, 0, 0);

    return 0;
}

int palindrome(string inputString, int position1, int position2, int runCount)
{
    if (runCount == 0)
    {
        position1 = 0;
        position2 = inputString.length() -1;
    }
    if (position2 > -1)
    {
        if (inputString[position1] != inputString[position2])
        {
            cout << "The string " << inputString << " is not a palindrome" << endl;
            return 0;
        }
        else
        {
            return palindrome(inputString, position1 + 1, position2 - 1, runCount + 1);
        }
    }
    else
    {
        cout << "The string " << inputString << " is a palindrome" << endl;
        return 0;
    }

}
