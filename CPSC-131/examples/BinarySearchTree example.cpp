

#include <iostream>


#include "BinarySearchTree.hxx"


int main()
{

    BinarySearchTree<int,int> tree;
    tree.insert(7,11);
    tree.insert(5,1);
    tree.insert(13,10);
    tree.insert(15,2);
    tree.insert(9,8);
    tree.insert(3,81);

    /* test on following as well....
    tree.insert(5,1);
    tree.insert(3,34);
    tree.insert(4,2);
    tree.insert(8,6);
    tree.insert(7,1);
    tree.insert(9,4);
    tree.insert(13,6);
    tree.insert(12,2);
    tree.insert(11,1); */

    std::cout << std::endl << "Inorder Traversal: "<<std::endl;
    tree.printInorder();
    
  //  std::cout << std::endl << "Tree height: " << std::endl;
  //  std::cout << tree.getHeight();

     return 0;

}