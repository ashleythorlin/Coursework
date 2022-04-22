
// Illustrating SLinkedList

#include <iostream>
#include "SLinkedList.hpp"
#include "SLinkedList.hxx"

int main()
{
    
    SLinkedList<int> sll;
    SLinkedList<int>::Iterator it;
    
    
    sll.append(13);
        
    sll.append(4);
    
    sll.append(9);

    sll.append(10);
    
    
    
    for(it = sll.begin(); it != sll.end(); ++it )
         std::cout<<*it <<" ";
    
    
    return 0;
}