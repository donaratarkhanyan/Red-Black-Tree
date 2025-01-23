#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
class RBTree {
private:
    enum Color {RED, BLACK};

    struct Node {
        T val;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        explicit Node(int value) : val(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}     
    };
    Node* root;
    Node* NIL;

    void leftRotate(Node*& x); // done
    void rightRotate(Node*& y); // done
    Node* searchHelper(Node* root, T value); // done
    void fixInsert(Node*& newNode); //done
    void fixDelete(Node*& fixNode); // done
    void preorderHelper(Node*& node); // done
    void inorderHelper(Node*& node); // done
    void postorderHelper(Node*& node); // done
    void transplant(Node*& u, Node*& v); // done
    int getSizeHelper(Node* node); // done

public:
    RBTree(); // done 
    ~RBTree(); // done
    Node* search(T value); // done
    void insert(T value); // done
    void deleteNode(T value); // done
    void preorder();  // done
    void inorder(); // done
    void postorder(); // done
    int getColor(Node*& node) const; //done
    void setColor(Node*& node, Color color); //done
    Node* minValue(Node*& node) const; // done
    Node* maxValue(Node*& node) const; // done
    int getBlackHeight(Node* node) const;//done
    Node* getRoot() const;//done
    void clear(Node* node); // done
    int getSize(); // done
};

#include "RBTree.cpp"
#endif //RED_BLACK_TREE