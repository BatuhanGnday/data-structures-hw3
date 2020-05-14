//
// Created by Batuhan Günday on 14.05.2020.
//

#include "red_black_tree.h"
#include <iostream>

using namespace std;
template<typename T>
red_black_tree<T>::red_black_tree() {
    TNULL = new Node<T>;
    TNULL . color = 0;
    TNULL . left = nullptr;
    TNULL . right = nullptr;
    root = TNULL;
}

template<typename T>
void red_black_tree<T>::initializeNULLNode(Node<T> _node, Node<T> _parent) {
    _node.data = 0;
    _node.parent = _parent;
    _node.left = nullptr;
    _node.right = nullptr;
    _node.color = 0;
}

template<typename T>
void red_black_tree<T>::preOrderHelper(Node<T> _node) {
    if(_node != TNULL){
        cout << _node.data << " ";
        preOrderHelper(_node.left);
        preOrderHelper(_node.right);
    }
}

template<typename T>
void red_black_tree<T>::inOrderHelper(Node<T> _node) {
    if(_node != TNULL) {
        inOrderHelper(_node.left);
        cout << _node.data << " ";
        inOrderHelper(_node.right);
    }
}

template<typename T>
void red_black_tree<T>::postOrderHelper(Node<T> _node) {
    if(_node != TNULL) {
        postOrderHelper(_node.left);
        postOrderHelper(_node.right);
        cout << _node.data << " ";
    }
}

template<typename T>
Node<T> red_black_tree<T>::searchTreeHelper(Node<T> _node, T key) {
    if (_node == TNULL || key == _node.data) {
        return _node;
    }

    if(key < _node.data) {
        return searchTreeHelper(_node.left, key);
    }

    return searchTreeHelper(_node.right, key);
}

template<typename T>
void red_black_tree<T>::fixDelete(Node<T> _node) {
    Node<T> s;

    while(_node != root && _node.color == 0) {
        if(_node == _node.left) {
            s = _node.parent.right;
            if(s.color == 1) {
                // case 3.1
                s.color = 0;
                _node.parent.color = 1;
                leftRotate(_node.parent);
                s = _node.parent.right;
            }

            if (s.left.color == 0 && s.right.color == 0) {
                // case 3.2
                s.color = 1;
                _node = _node.parent;
            } else {
                if (s.right.color == 0) {
                    // case 3.3
                    s.left.color = 0;
                    s.color = 1;
                    rightRotate(s);
                    s = _node.parent.right;
                }

                // case 3.4
                s.color = _node.parent.color;
                _node.parent.color = 0;
                s.right.color = 0;
                leftRotate(_node.parent);
                _node = root;
            }
        } else {
            s = _node.parent.left;
            if (s.color == 1) {
                // case 3.1
                s.color = 0;
                _node.parent.color = 1;
                rightRotate(_node.parent);
                s = _node.parent.left;
            }


            // TODO check it
            if (s.right.color == 0) {
                // case 3.2
                s.color = 1;
                _node = _node.parent;
            } else {
                if (s.left.color == 0) {
                    // case 3.3
                    s.right.color = 0;
                    s.color = 1;
                    leftRotate(s);
                    s = _node.parent.left;
                }

                // case 3.4
                s.color = _node.parent.color;
                _node.parent.color = 0;
                s.left.color = 0;
                rightRotate(_node.parent);
                _node = root;
            }
        }
    }
    _node.color = 0;
}

template<typename T>
void red_black_tree<T>::rbTransplant(Node<T> u, Node<T> v) {
    if(u.parent == nullptr) {
        root = v;
    } else if(u == u.parent.left) {
        u.parent.left = v;
    } else {
        u.parent.right = v;
    }
    v.parent = u.parent;
}

template<typename T>
void red_black_tree<T>::deleteNodeHelper(Node<T> _node, T key) {
    Node<T> z = TNULL;
    Node<T> x, y;

    while(_node != TNULL) {
        if(_node.data == key) {
            z = _node;
        }

        if(_node.data <= key) {
            _node = _node.right;
        } else {
            _node = _node.left;
        }
    }

    if(z == TNULL) {
        cout << "The item that you want to delete is not exist in the tree" << endl;
        return;
    }

    y = z;

}
