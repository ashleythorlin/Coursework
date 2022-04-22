// inserting into a list
#include <iostream>
#include "DLinkedList.hpp"
#include "DummyNodeDLinkedList.hxx"

// Comment out #include "DLinkedList.hxx" in DLinkedList.hpp
//  Uncomment #include "DummyNodeDLinkedList.hxx" in DLinkedList.hpp



int main()
{
    DLinkedList<int> mylist;
    DLinkedList<int>::Iterator it;

    // set some initial values: // 1 2 3 4 5
    mylist.append(1);
    mylist.append(2);
    mylist.append(3);
    mylist.append(4);
    mylist.append(5);

    it = mylist.begin();                               // 1 2 3 4 5
                     // it points now to number 1         ^
    
    ++it;                                           // 1 2 3 4 5
    
                 // it points now to number 2            ^

    it = mylist.insertBefore(it, 10);                        // 1 10 2 3 4 5

    // "it" now points to number 10                                ^


        
    --it;                                    // 1 10 2 3 4 5
   
    // it points now to number 1                ^

    std::cout << "mylist contains:";
    for (it = mylist.begin(); it != mylist.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}