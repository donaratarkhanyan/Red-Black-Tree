#include <iostream>
#include "RBTree.h"

template <typename T>
RBTree<T>::RBTree() {
    NIL = new Node(T{}); 
    NIL -> color = BLACK;
    root = NIL;
}

template <typename T>
RBTree<T>::~RBTree() {
    clear(root);
    delete NIL;
}

template <typename T>
void RBTree<T>::leftRotate(Node*& x){
    Node* y = x -> right;
    x -> right = y -> left;
    if (y -> left != NIL) {
        y -> left -> parent = x;
    }
    y -> parent = x -> parent;
    if (x -> parent == NIL) {
        root = y;
    } else if (x == x -> parent -> left) {
        x -> parent -> left = y;
    } else {
        x -> parent -> right = y;
    }
    y -> left = x;
    x -> parent = y;
}

template <typename T>
void RBTree<T>::rightRotate(Node*& y) {
    Node* x = y -> left;
    y -> left = x -> right;
    if (x -> right != NIL) {
        x -> right -> parent = y;
    }
    x -> parent = y -> parent;
    if (y -> parent == NIL) {
        root = x;
    } else if (y == y -> parent -> left) {
        y -> parent -> left = x;
    } else {
        y -> parent -> right = x;
    }
    x -> right = y;
    y -> parent = x;
}

template <typename T>
void RBTree<T>::insert(T value){
    Node* newNode = new Node(value);
    Node* curr = root;
    Node* parentNode = NIL;

    while (curr != NIL) {
        parentNode = curr;
        if (curr -> val > value) {
            curr = curr -> left;
        } else if (curr -> val < value){
            curr = curr -> right;
        } else {
            delete newNode;
            return;
        }
    }

    newNode -> parent = parentNode;
    if (parentNode == NIL) { 
        root = newNode;
    } else if (parentNode -> val < value) {
        parentNode -> right = newNode;
    } else {
        parentNode -> left = newNode;
    }
    newNode -> left = NIL;
    newNode -> right = NIL;
    newNode -> color = RED;
    fixInsert(newNode);
}

template <typename T>
void RBTree<T>::fixInsert(Node*& newNode) {
    std::cout << newNode -> val << std::endl;
    while (newNode -> parent && newNode -> parent -> color == RED) {
        if (newNode -> parent == newNode -> parent -> parent -> left) {
            Node* uncle = newNode -> parent -> parent -> right;
            if (uncle -> color == RED) {
                uncle -> color = BLACK;
                newNode -> parent -> color = BLACK;
                newNode -> parent -> parent -> color = RED;
                newNode = newNode -> parent -> parent;
            } else {
                if (newNode == newNode -> parent -> right) {
                    newNode = newNode -> parent;
                    leftRotate(newNode);
                }
                newNode -> parent -> color = BLACK;
                newNode -> parent -> parent -> color = RED;
                rightRotate(newNode -> parent -> parent);
            }
        } else {
            Node* uncle = newNode -> parent -> parent -> left;
            if (uncle -> color == RED) {
                uncle -> color = BLACK;
                newNode -> parent -> color = BLACK;
                newNode -> parent -> parent -> color = RED;
                newNode = newNode -> parent -> parent;
            } else {
                if (newNode == newNode -> parent -> left) {
                    newNode = newNode -> parent;
                    rightRotate(newNode);
                }
                newNode -> parent -> color = BLACK;
                newNode -> parent -> parent -> color = RED;
                leftRotate(newNode -> parent -> parent);
            }
        }
    }
    root -> color = BLACK;
}

template <typename T>
void RBTree<T>::deleteNode(T value) {
    Node* target= search(value);
    if (target == NIL) {
        return; 
    }
    Node* nodeToDelete = target;
    Node* replace = nullptr;
    Color originalColor = nodeToDelete -> color;

    if (target -> left == NIL) { // Case 1: Node has no left child
        replace = target -> right;
        transplant(target, target -> right);
    } else if (target -> right == NIL) { // Case 2: Node has no right child
        replace = target -> left;
        transplant(target, target -> left);
    } else { // Case 3: Node has two children
        nodeToDelete = minValue(target -> right);
        originalColor = nodeToDelete -> color; 
        replace = nodeToDelete -> right;
        if (nodeToDelete -> parent == target) {
            replace -> parent = nodeToDelete;
        } else {
            transplant(nodeToDelete, nodeToDelete -> right);
            nodeToDelete -> right = target -> right;
            nodeToDelete -> right -> parent = nodeToDelete;
        }
        // Replace the target with the successor
        transplant(target, nodeToDelete);
        nodeToDelete -> left = target -> left;
        nodeToDelete -> left -> parent = nodeToDelete;
        nodeToDelete -> color = target -> color; 
    }

    delete target;
    if (originalColor == BLACK) {
        fixDelete(replace);
    }
}

template <typename T>
void RBTree<T>::fixDelete(Node*& fixNode) {
    while (fixNode != root && fixNode->color == BLACK) {
        if (fixNode == fixNode->parent->left) {
            Node* sibling = fixNode->parent->right; 

            // Case 1: Sibling is red
            if (sibling->color == RED) {
                sibling->color = BLACK;
                fixNode->parent->color = RED;
                leftRotate(fixNode->parent);
                sibling = fixNode->parent->right; 
            }
            // Case 2: Sibling is black, children are black
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                fixNode = fixNode->parent; 
            } else {
                // Case 3: Sibling is black, left child is red, right child is black
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = fixNode->parent->right; 
                }

                // Case 4: Sibling is black, right child is red
                sibling->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(fixNode->parent);
                fixNode = root; 
            }
        } else {
            Node* sibling = fixNode->parent->left; 

            // Case 1: Sibling is red
            if (sibling->color == RED) {
                sibling->color = BLACK;
                fixNode->parent->color = RED;
                rightRotate(fixNode->parent);
                sibling = fixNode->parent->left; 
            }

            // Case 2: Sibling is black, children are black
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                fixNode = fixNode->parent; 
            } else {
                // Case 3: Sibling is black, right child is red, left child is black
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = fixNode->parent->left; 
                }

                // Case 4: Sibling is black, left child is red
                sibling->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(fixNode->parent);
                fixNode = root; // stop loop
            }
        }
    }
    fixNode->color = BLACK; 
}

template <typename T>
void RBTree<T>::preorder() {
    if (root != NIL) {
        preorderHelper(root);
    }
    std::cout << std::endl;
}


template <typename T>
void RBTree<T>::preorderHelper(Node*& node) {
    if (node != NIL) { 
        std::cout << node -> val << " ";
        preorderHelper(node -> left);
        preorderHelper(node -> right);
    }
}

template <typename T>
void RBTree<T>::inorder() {
    if (root != NIL) {
        inorderHelper(root);
    }
    std::cout << std::endl;
}

template <typename T>
void RBTree<T>::inorderHelper(Node*& node) {
    if (node != NIL) { 
        inorderHelper(node -> left);
        std::cout << node -> val << " ";
        inorderHelper(node -> right);
    }
}

template <typename T>
void RBTree<T>::postorder() {
    if (root != NIL) {
        postorderHelper(root);
    }
    std::cout << std::endl;
}

template <typename T>
void RBTree<T>::postorderHelper(Node*& node) {
    if (node != NIL) { 
        postorderHelper(node -> left);
        postorderHelper(node -> right);
        std::cout << node -> val << " ";
    }
}

template <typename T>
void RBTree<T>::transplant(Node*& u, Node*& v) {
    if (u -> parent == NIL) {
        root = v;
    } else if (u == u -> parent -> left) {
        u -> parent -> left = v;
    } else if (u == u -> parent -> right) {
        u -> parent -> right = v;
    }
    if (v != NIL) {
        v->parent = u->parent;
    }
}

template <typename T>
void RBTree<T>::clear(Node* node) {
    if (node == NIL) return; 
    clear(node -> left);
    clear(node -> right);
    delete node;
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::minValue(Node*& node) const {
    Node* curr = node;
    while (curr -> left != NIL) {
        curr = curr -> left;
    }
    return curr;
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::maxValue(Node*& node) const {
    Node* curr = node;
    while (curr -> right != NIL) {
        curr = curr -> right;
    }
    return curr;
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::searchHelper(Node* root, T value) {
    Node* current = root;
    if(root == NIL || root -> val == value) {
        return root;
    }
    if (value < root -> val) {
        return searchHelper(root -> left, value);
    }
    return searchHelper(root -> right, value);
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::search(T value) {
    return searchHelper(root, value);
}

template <typename T>
int RBTree<T>::getColor(Node*& node) const {
    return (node == nullptr) ? BLACK : node -> color;
}

template <typename T>
void RBTree<T>::setColor(Node*& node, Color color) {
    if (node) {
        node -> color = color;
    }
}

template <typename T>
int RBTree<T>::getBlackHeight(Node* node) const {
    if (node == NIL) {
        return 1;
    }

    int leftBlackHeight = getBlackHeight(node->left);
    int rightBlackHeight = getBlackHeight(node->right);

    if (leftBlackHeight != rightBlackHeight) {
        throw std::runtime_error("Invalid Red-Black Tree: Black heights are not equal");
    }

    return leftBlackHeight + (node->color == BLACK ? 1 : 0);
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::getRoot() const {
    return root;
}

template <typename T>
int RBTree<T>::getSizeHelper(Node* node)
{
    if (node == NIL) {
        return 0;
    }
    return getSizeHelper(node -> left) + getSizeHelper(node -> right) + 1;
}

template <typename T>
int RBTree<T>::getSize() 
{
    return getSizeHelper(root);
}