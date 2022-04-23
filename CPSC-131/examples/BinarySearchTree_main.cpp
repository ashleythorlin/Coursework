#include <iostream>
#include <string>

#include "BinarySearchTree.hpp"




using namespace std;

int main()
{

  BinarySearchTree<int, int> tree; 
  tree.insert(6, 6);
  tree.insert(2, 4);
  tree.insert(7, 7);
  tree.insert(7, 2);
  tree.insert(8, 0);
  tree.insert(6, 8);
  tree.insert(7, 4);

  cout << tree.evenKeyCount();

}



// Explicit instantiation - a technique to ensure all functions of the template are created and semantically checked.  By default,
// only functions called get instantiated so you won't know it has compile errors until you actually call it.
template class BinarySearchTree<unsigned, float>;
