//
// Created by 101061875 on 3/28/2024.
//

#ifndef PROG2_RED_BLACK_TREE_H
#define PROG2_RED_BLACK_TREE_H


#include<iostream>
#include <ostream>
#include <fstream>
#include <string>

using namespace std;

//enumeration for red and black nodes
enum Color { RED, BLACK };

// node structure
struct Node {
    int item; // data
    Color color; // color of node
    Node* left; // left child
    Node* right; // right child
    Node* parent; // parent

    // constructor
    Node(int k) : item(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void fixInsertViolation(Node* z);
    void fixDeleteViolation(Node* x);
    Node* findMin(Node* node);
    void inOrderTraversal(Node* node);
    void generateDot(Node* node, ofstream& out);

public:
    // constructor
    RedBlackTree() : root(nullptr) {}

    void insert(int data);
    void remove(int data);
    void erase();
    void inOrderTraversal();
    void dotFile(const string &filename);
};



#endif //PROG2_RED_BLACK_TREE_H
