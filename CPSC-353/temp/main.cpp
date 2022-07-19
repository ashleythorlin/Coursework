#include "s01c06-break-repeating-key-xor.cpp"

#include <cstdlib>
#include <iostream>



int main(int argc, const char* argv[]) {

    int choice = 0;
    std::cout << "Which challenge would you like to run?\n";
    std::cin >> choice;

    switch(choice){
        // case 1:  challenge1();  break;
        // case 2:  challenge2();  break;
        // case 3:  challenge3();  break;
        // case 4:  challenge4();  break;
        // case 5:  challenge5();  break;
        case 6:  s01::c06::break_repeating_key_xor(argc, argv);  break;
        default: std::cerr << "Error: invalid option.\n"; break;
    }

    return 0;

}