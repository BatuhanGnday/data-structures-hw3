//
// Created by Batuhan Günday on 14.05.2020.
//

#ifndef TEST_RED_BLACK_TREE_H
#define TEST_RED_BLACK_TREE_H

#include <istream>
using namespace std;



// color enums for each node
enum color {
    black = 0,
    red = 1,
};

// Data structure that represents a node in the tree
template<typename T>
struct Node{
    T data;
    Node* parent;
    Node* left;
    Node* right;
    color color;
    typedef Node<T>* Nodeptr;
};

template <typename T>
class RedBlackTree {

public:

    RedBlackTree();

    void preOrder();

    void inOrder();

    void postOrder();

    Node<T> searchTree(T key);

    Node<T> findMin(Node<T> _node);

    Node<T> findMax(Node<T> _node);

    Node<T> findSuccessor(Node<T> _node);

    Node<T> predecessor(Node<T> _node);

    void leftRotate(Node<T> _node);

    void rightRotate(Node<T> _node);

    void insert(T key);

    Node<T> getRoot();

    void deleteNode(T key);

    void print();

private:
    Node<T> root;

    Node<T> TNULL;

    void initializeNULLNode(Node<T> _node, Node<T> _parent);

    void preOrderHelper(Node<T> _node);

    void inOrderHelper(Node<T> _node);

    void postOrderHelper(Node<T> _node);

    Node<T> searchTreeHelper(Node<T> _node, T key);

    void fixDelete(Node<T> _node);

    void rbTransplant(Node<T> u, Node<T> v);

    void deleteNodeHelper(Node<T> _node, T key);

    void fixInsert(Node<T> _node);

    void printHelper(Node<T> _root, string indent, bool last);

};


template<typename T>
RedBlackTree<T>::RedBlackTree() {
    TNULL = new Node<T>;
    TNULL -> color = black;
    TNULL -> left = nullptr;
    TNULL -> right = nullptr;
    root = TNULL;
}

#endif //TEST_RED_BLACK_TREE_H
