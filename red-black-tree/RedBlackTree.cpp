//
// Created by Batuhan Günday on 14.05.2020.
//

#include "RedBlackTree.h"
#include <iostream>

using namespace std;

//<editor-fold desc="Helpers">

template<typename T>
void RedBlackTree<T>::initializeNULLNode(Node<T> _node, Node<T> _parent) {
    _node -> data = 0;
    _node -> parent = _parent;
    _node -> left = nullptr;
    _node -> right = nullptr;
    _node -> color = black;
}

template<typename T>
void RedBlackTree<T>::preOrderHelper(Node<T> _node) {
    if(_node != TNULL){
        cout << _node -> data << " ";
        preOrderHelper(_node -> left);
        preOrderHelper(_node -> right);
    }
}

template<typename T>
void RedBlackTree<T>::inOrderHelper(Node<T> _node) {
    if(_node != TNULL) {
        inOrderHelper(_node -> left);
        cout << _node -> data << " ";
        inOrderHelper(_node -> right);
    }
}

template<typename T>
void RedBlackTree<T>::postOrderHelper(Node<T> _node) {
    if(_node != TNULL) {
        postOrderHelper(_node -> left);
        postOrderHelper(_node -> right);
        cout << _node -> data << " ";
    }
}

template<typename T>
Node<T> RedBlackTree<T>::searchTreeHelper(Node<T> _node, T key) {
    if (_node == TNULL || key == _node -> data) {
        return _node;
    }

    if(key < _node -> data) {
        return searchTreeHelper(_node -> left, key);
    }

    return searchTreeHelper(_node -> right, key);
}

template<typename T>
void RedBlackTree<T>::fixDelete(Node<T> _node) {
    Node<T> s;

    while(_node != root && _node -> color == black) {
        if(_node == _node -> left) {
            s = _node -> parent.right;
            if(s.color == red) {
                // case 3.1
                s.color = black;
                _node -> parent.color = red;
                leftRotate(_node -> parent);
                s = _node -> parent.right;
            }

            if (s.left.color == black && s.right.color == black) {
                // case 3.2
                s.color = red;
                _node = _node -> parent;
            } else {
                if (s.right.color == black) {
                    // case 3.3
                    s.left.color = black;
                    s.color = red;
                    rightRotate(s);
                    s = _node -> parent.right;
                }

                // case 3.4
                s.color = _node -> parent.color;
                _node -> parent.color = black;
                s.right.color = black;
                leftRotate(_node -> parent);
                _node = root;
            }
        } else {
            s = _node -> parent.left;
            if (s.color == red) {
                // case 3.1
                s.color = black;
                _node -> parent.color = red;
                rightRotate(_node -> parent);
                s = _node -> parent.left;
            }


            // TODO check it
            if (s.right.color == black) {
                // case 3.2
                s.color = red;
                _node = _node -> parent;
            } else {
                if (s.left.color == black) {
                    // case 3.3
                    s.right.color = red;
                    s.color = red;
                    leftRotate(s);
                    s = _node -> parent.left;
                }

                // case 3.4
                s.color = _node -> parent.color;
                _node -> parent.color = black;
                s.left.color = black;
                rightRotate(_node -> parent);
                _node = root;
            }
        }
    }
    _node -> color = black;
}

template<typename T>
void RedBlackTree<T>::rbTransplant(Node<T> u, Node<T> v) {
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
void RedBlackTree<T>::deleteNodeHelper(Node<T> _node, T key) {
    Node<T> z = TNULL;
    Node<T> x, y;

    while(_node != TNULL) {
        if(_node -> data == key) {
            z = _node;
        }

        if(_node -> data <= key) {
            _node = _node -> right;
        } else {
            _node = _node -> left;
        }
    }

    if(z == TNULL) {
        cout << "The item that you want to delete is not exist in the tree" << endl;
        return;
    }

    y = z;

    color y_original_color = y.color;

    if(z.left == TNULL) {
        x = z.right;
        rbTransplant(z, z.right);
    } else if(z.right == TNULL) {
        x = z.left;
        rbTransplant(z, z.left);
    } else {
        y = findMin(z.right);
        y_original_color = y.color;
        x = y.right;
        if(y.parent == z) {
            x.parent = y;
        } else {
            rbTransplant(y, y.right);
            y.right = z.right;
            y.right.parent = y;
        }

        rbTransplant(z, y);
        y.left = z.left;
        y.left.parent = y;
        y.color = z.color;

        delete z;

        if(y_original_color == black) {
            fixDelete(x);
        }
    }
}

template<typename T>
void RedBlackTree<T>::fixInsert(Node<T> _node) {

    Node<T> u;

    while (_node -> parent.color == red) {
        if (_node -> parent == _node -> parent.parent.right) {
            u = _node -> parent.parent.left; // uncle
            if (u.color == red) {
                // case 3.1
                u.color = black;
                _node -> parent.color = black;
                _node -> parent.parent.color = red;
                _node = _node -> parent.parent;
            } else {
                if (_node == _node -> parent.left) {
                    // case 3.2.2
                    _node = _node -> parent;
                    rightRotate(_node);
                }
                // case 3.2.1
                _node -> parent.color = black;
                _node -> parent.parent.color = red;
                leftRotate(_node -> parent.parent);
            }
        } else {
            u = _node -> parent.parent.right; // uncle

            if (u.color == red) {
                // mirror case 3.1
                u.color = black;
                _node -> parent.color = black;
                _node -> parent.parent.color = red;
                _node = _node -> parent.parent;
            } else {
                if (_node == _node -> parent.right) {
                    // mirror case 3.2.2
                    _node = _node -> parent;
                    leftRotate(_node);
                }
                // mirror case 3.2.1
                _node -> parent.color = black;
                _node -> parent.parent.color = red;
                rightRotate(_node -> parent.parent);
            }
        }
        if (_node == root) {
            break;
        }
    }
    root.color = black;
}

template<typename T>
void RedBlackTree<T>::printHelper(Node<T> _root, string indent, bool last) {
    if (_root != TNULL) {
        cout<<indent;
        if (last) {
            cout<<"R----";
            indent += "     ";
        } else {
            cout<<"L----";
            indent += "|    ";
        }

        string sColor = _root.color?"RED":"BLACK";
        cout<<_root->data<<"("<<sColor<<")"<<endl;
        printHelper(_root.left, indent, false);
        printHelper(_root.right, indent, true);
    }
}

//</editor-fold>

template<typename T>
void RedBlackTree<T>::preOrder() {
    preOrderHelper(this->root);
}

template<typename T>
void RedBlackTree<T>::inOrder() {
    inOrderHelper(this->root);
}

template<typename T>
void RedBlackTree<T>::postOrder() {
    postOrder(this->root);
}

template<typename T>
Node<T> RedBlackTree<T>::searchTree(T key) {
    searchTreeHelper(this->root, key);
}

template<typename T>
Node<T> RedBlackTree<T>::findMin(Node<T> _node) {
    while(_node -> left != TNULL) {
        _node = _node -> left;
    }
    return _node;
}

template<typename T>
Node<T> RedBlackTree<T>::findMax(Node<T> _node) {
    while(_node -> right != TNULL) {
        _node = _node -> right;
    }
    return _node;
}

template<typename T>
Node<T> RedBlackTree<T>::findSuccessor(Node<T> _node) {
    if(_node -> right != TNULL) {
        return findMin(_node -> right);
    }

    Node<T> y = _node -> parent;

    while(y!=TNULL && _node == y.right) {
        _node = y;
        y = y.parent;
    }
    return y;
}

template<typename T>
Node<T> RedBlackTree<T>::predecessor(Node<T> _node) {
    // if the left subtree is not null,
    // the predecessor is the rightmost node in the
    // left subtree
    if (_node->left != TNULL) {
        return maximum(_node->left);
    }

    Node<T> y = _node->parent;
    while (y != TNULL && _node == y->left) {
        _node = y;
        y = y->parent;
    }
    return y;
}

template<typename T>
void RedBlackTree<T>::leftRotate(Node<T> _node) {

    Node<T> y = _node->right;
    _node->right = y->left;

    if (y->left != TNULL) {
        y->left->parent = _node;
    }

    y->parent = _node->parent;

    if (_node->parent == nullptr) {
        this->root = y;
    } else if (_node == _node->parent->left) {
        _node->parent->left = y;
    } else {
        _node->parent->right = y;
    }

    y->left = _node;
    _node->parent = y;
}

template<typename T>
void RedBlackTree<T>::rightRotate(Node<T> _node) {
    Node<T> y = _node->left;
    _node->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = _node;
    }
    y->parent = _node->parent;
    if (_node->parent == nullptr) {
        this->root = y;
    } else if (_node == _node->parent->right) {
        _node->parent->right = y;
    } else {
        _node->parent->left = y;
    }
    y->right = _node;
    _node->parent = y;
}

template<typename T>
void RedBlackTree<T>::insert(T key) {
    // Ordinary Binary Search Insertion
    Node<T> node = new Node<T>;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = red; // new node must be red

    Node<T> y = nullptr;
    Node<T> x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y is parent of x
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // if new node is a root node, simply return
    if (node->parent == nullptr){
        node->color = 0;
        return;
    }

    // if the grandparent is null, simply return
    if (node->parent->parent == nullptr) {
        return;
    }

    // Fix the tree
    fixInsert(node);

}

template<typename T>
Node<T> RedBlackTree<T>::getRoot() {
    return this->root;
}

template<typename T>
void RedBlackTree<T>::deleteNode(T key) {
    deleteNodeHelper(this->root, key);
}

template<typename T>
void RedBlackTree<T>::print() {
    if(root) {
        printHelper(this->root, "", true);
    }
}
