#include <iostream>
#include "red-black-tree/RedBlackTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    RedBlackTree<int> rbt;
    rbt.insert(34);
    rbt.insert(23);
    rbt.print();

    return 0;
}
