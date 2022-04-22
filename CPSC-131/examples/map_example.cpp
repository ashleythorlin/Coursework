

#include <iostream>
#include <map>

int main()
{
    std::pair <int, char> keyVal(3, 'a');

    std::cout << "Key " << keyVal.first << " Value " << keyVal.second << '\n';


    std::map<int, char> tree;



    tree.insert(keyVal);


    tree.insert(std::pair<int, char>(7, 'b'));

    std::map<int, char>::iterator it;

    std::cout << "tree contains " << tree.size() << " elements.\n";

    for (it = tree.begin(); it != tree.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    tree[1] = 'c';
    tree[5] = 'd';
    tree[9] = 'e';
    tree[2] = 'f';

    std::cout << "tree now contains " << tree.size() << " elements.\n";

    for (it = tree.begin(); it != tree.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    tree[2] = 'z';

    std::cout << "tree now contains " << tree.size() << " elements.\n";

    for (it = tree.begin(); it != tree.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    std::pair<std::map<int, char>::iterator,bool> p = tree.insert(std::pair<int, char>(2, 'b'));
    std::cout << std::endl <<" can insert key " << p.first->first<<" ? "<< p.second <<std::endl;

    std::cout << "tree now contains " << tree.size() << " elements.\n";

    for (it = tree.begin(); it != tree.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    p = tree.insert(std::pair<int, char>(11, 'b'));
    std::cout << std::endl << " can insert key " << p.first->first << " ? " << p.second << std::endl;

    std::cout << "tree now contains " << tree.size() << " elements.\n";

    for (it = tree.begin(); it != tree.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    int searchKey = 9;
    it = tree.find(searchKey);
    if (it != tree.end())
        tree.erase(it);
    std::cout << "after deleting "<<searchKey<<", tree now contains " << tree.size() << " elements.\n";
    return 0;
}
