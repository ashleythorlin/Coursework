#include <iostream>
#include <stdexcept>
#include <string>

#include "SLinkListhpp.h"



int main()
{
    SLinkedList<int> nums;
    nums.append(1);
    nums.append(2);
    nums.append(3);
    nums.append(5);
    nums.append(1);
    nums.append(2);
    nums.append(11);
    nums.append(1);
    nums.append(5);
    nums.append(2);
    nums.append(4);
    nums.append(1);
    nums.append(1);
 
    std::cout << "Frequency of 1 is: " << nums.freqR(1);
        // << " or " << nums.freqR(1);
}

// For testing purposes, explicitly instantiate the class template.  Template
// class member functions are only instantiated, and thus semantically checked
// by the compiler, when used.  Explicitly instantiating the class forces all
// the member functions to be instantiated, and thus semantically checked by the
// compiler.  It enables the compiler to find errors in your code.
// template class SLinkedList<Student>;
