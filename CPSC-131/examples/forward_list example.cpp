
// Illustrating forward_list

#include <iostream>
#include <forward_list>


int main()
{
    
    std::forward_list<int> fl;
    std::forward_list<int>::iterator it;
    
    
    fl.push_front(13);
    it = fl.begin();
    
    it = fl.insert_after(it,4);
    
    it = fl.insert_after(it,9);
    
    it = fl.insert_after(it,10);
    
    for(it = fl.begin(); it != fl.end(); ++it )
         std::cout<<" "<<*it;
    
    
    

    return 0;
}