#include <iostream>
#include "red-black-tree/RedBlackTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    RedBlackTree<string> rbt;
    rbt.insert("lorem");
    rbt.insert("ipsum");
    rbt.insert("dolor");
    rbt.insert("sit");
    rbt.insert("amet");
    rbt.insert("consectetur");
    rbt.insert("adipiscing");
    rbt.insert("elit");
    rbt.print();

    return 0;
}
