#include <iostream>
#include "red-black-tree/RedBlackTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    //RedBlackTree<int> *rbt;
    //rbt->insert(34);
    //rbt->insert(23);
    //rbt->insert(12);
    //rbt->insert(43);
    //rbt->print();

    RedBlackTree<int> rbt = RedBlackTree<int>();

    rbt.insert(23);
    rbt.insert(22);
    rbt.insert(25);
    rbt.insert(27);
    rbt.print();

    return 0;
}
