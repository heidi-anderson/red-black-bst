#include <iostream>
#include "red_black_tree.h"

int main() {
    RedBlackTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);

    std::cout << "In-order traversal: ";
    tree.inOrderTraversal();
    tree.dotFile("afterInsertions.dot");

    tree.remove(30);
    tree.remove(50);

    std::cout << "In-order traversal after deletion: ";
    tree.inOrderTraversal();
    tree.dotFile("afterDeletions.dot");

    tree.erase();
    std::cout << "In-order traversal after erasure: ";
    tree.inOrderTraversal();
    tree.dotFile("afterErase.dot");


    RedBlackTree tree1;
    tree1.insert(15);
    tree1.insert(7);
    tree1.insert(30);
    tree1.insert(29);
    tree1.insert(11);
    tree1.insert(65);
    tree1.insert(44);

    std::cout << "In-order traversal: ";
    tree1.inOrderTraversal();
    tree1.dotFile("afterInsertions1.dot");

    tree1.remove(30);
    tree1.remove(44);

    std::cout << "In-order traversal after deletion: ";
    tree1.inOrderTraversal();
    tree1.dotFile("afterDeletions1.dot");

    tree1.erase();
    std::cout << "In-order traversal after erasure: ";
    tree1.inOrderTraversal();
    tree1.dotFile("afterErase1.dot");

    return 0;
}