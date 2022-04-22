

#include <iostream>

using namespace std;

int main()
{
    int number = 3;
    cout << "number is " << number << endl;
    cout << "address of number is " << &number << endl;

    int* intPointer;

    intPointer = &number;

    cout << "address of number is " << intPointer << endl;

    cout << "address of intPointer is " << &intPointer << endl;

    *intPointer = 5;

    cout << "now number is " << number << endl;

    string author = "Samuel Clemens";

    string& penName = author;

    cout << "penName is " << penName << endl;

    cout << "address of author is " << &author << endl;




    cout << "address of penName is " << &penName << endl;

    penName = "Mark Twain";

    cout << "Reassigning a value to penName changes author: " << author << endl;

    string author2 = "ABC";
    cout << "address of author2 is " << &author2 << endl;
    penName = author2;

    cout << "penName is " << penName << endl;
    cout << "address of penName is " << &penName << endl;
    cout << "address of author2 is " << &author2 << endl;


}


