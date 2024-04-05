//
// Created by 101061875 on 3/28/2024.
//

#include "red_black_tree.h"
void RedBlackTree::leftRotate(Node* x)
{
    Node* y = x->right; // set y as right child of x
    x->right = y->left; // turn y's left subtree into x's right subtree

    // if y has a left child, update that child's parent to x
    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent; // make y's parent x's parent

    // if x does not have parent, y is the new root
    if (x->parent == nullptr)
        root = y;
    // if x is the left child of it's parent, update parent's left child to y
    else if (x == x->parent->left)
        x->parent->left = y;
    // if x is the right child of its parent, update parents right child to y
    else
        x->parent->right = y;

    y->left = x; // put x on y's left
    x->parent = y; // make x's parent y
}

void RedBlackTree::rightRotate(Node* y)
{
    Node* x = y->left; // make x left child of y
    y->left = x->right; // make x's right subtree into y's subtree

    // if x has right child, make y the parent
    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent; // make x's parent y's parent

    // if y doesn't have a parent, x is new root
    if (y->parent == nullptr)
        root = x;
    //if y is a left child, update parent's left child to x
    else if (y == y->parent->left)
        y->parent->left = x;
    // if y is the right child, update parent's right child to x
    else
        y->parent->right = x;

    x->right = y; // put y on x's right
    y->parent = x; // make y's parent x
}

void RedBlackTree::fixInsertViolation(Node* z)
{
    // continue fixing conflicts until z is the root or z's parent is black
    while (z != root && z->parent->color == RED)
    {
        // if z's parent is a left child
        if (z->parent == z->parent->parent->left)
        {
            Node* y = z->parent->parent->right; // y is z's aunt
            // case 1: z's aunt is red
            if (y != nullptr && y->color == RED)
            {
                z->parent->color = BLACK; // change colors
                y->color = BLACK;
                z->parent->parent->color = RED; // grandparent becomes red
                z = z->parent->parent; // move z to the grandparent
            }
            else
            {
                // case 2: z's aunt y is black and z is a right child
                if (z == z->parent->right)
                {
                    z = z->parent; // move z up to parent
                    leftRotate(z); // rotate left about z
                }
                // case 3: z's aunt y is black and z is a left child
                z->parent->color = BLACK; // change colors
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent); // rotate right about z's grandparent
            }
        }
        // if z's parent is a right child
        else
        {
            Node* y = z->parent->parent->left; // y is z's aunt

            // case 1: z's aunt y is red
            if (y != nullptr && y->color == RED)
            {
                z->parent->color = BLACK; // change colors
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // move z up to grandparent
            }

            else
            {
                // case 2: z's aunt y is black and z is a left child
                if (z == z->parent->left)
                {
                    z = z->parent; // Move z up to its parent
                    rightRotate(z); // right rotate about z
                }

                // case 3: z's aunt y is black and z is a right child
                z->parent->color = BLACK; // change colors
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent); // left rotate about grandma
            }
        }
    }
    root->color = BLACK; // ensure root is black
}

void RedBlackTree::fixDeleteViolation(Node* x) {
    // continue fixing violations until x is the root or x's color is black
    while (x != root && x && x->color == BLACK)
    {
        // if x is a left child of its parent
        if (x && x->parent && x == x->parent->left)
        {
            Node* w = x->parent->right; // w is x's sibling

            // case 1: x's sibling w is red
            if (w && w->color == RED)
            {
                w->color = BLACK; //sibling becomes black
                x->parent->color = RED; // parent becomes red
                leftRotate(x->parent); // perform left rotation on parent
                w = x->parent->right; // update w to the new sibling
            }
            // case 2: x's sibling w is black and both of w's children are black
            if (w && (!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK))
            {
                if (w)
                    w->color = RED; // sibling becomes red
                x = x->parent; // move up to the parent
            }
            else
            {
                // case 3: x's sibling w is black and w's right child is black
                if (w && w->right && w->right->color == BLACK)
                {
                    if (w->left)
                        w->left->color = BLACK; //  w's left child becomes black
                    if (w)
                        w->color = RED; // sibling becomes red
                    rightRotate(w); // Perform right rotation on sibling
                    w = x->parent->right; // Update w to the new sibling
                }
                // case 4: x's sibling w is black and w's right child is red
                if (w)
                    w->color = x->parent->color; // Set w's color to x's parent's color
                if (x->parent)
                    x->parent->color = BLACK; // Parent becomes black
                if (w && w->right)
                    w->right->color = BLACK; //  w's right child becomes black
                if (x->parent)
                    leftRotate(x->parent); // Perform left rotation on parent
                x = root;
            }
        }
        // If x is a right child of its parent
        else if (x && x->parent)
        {
            Node* w = x->parent->left; // w is x's sibling

            // Case 1: x's sibling w is red
            if (w && w->color == RED)
            {
                w->color = BLACK; // sibling becomes black
                x->parent->color = RED; // Parent becomes red
                rightRotate(x->parent); // Perform right rotation on parent
                w = x->parent->left; // Update w to the new sibling
            }
            // Case 2: x's sibling w is black and both of w's children are black
            if (w && (!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK))
            {
                if (w)
                    w->color = RED; // Flip color: sibling becomes red
                x = x->parent; // Move up to the parent
            } else
            {
                // Case 3: x's sibling w is black and w's left child is black
                if (w && w->left && w->left->color == BLACK)
                {
                    if (w->right)
                        w->right->color = BLACK; // Flip color: w's right child becomes black
                    if (w)
                        w->color = RED; // Flip color: sibling becomes red
                    leftRotate(w); // Perform left rotation on sibling
                    w = x->parent->left; // Update w to the new sibling
                }
                // Case 4: x's sibling w is black and w's left child is red
                if (w)
                    w->color = x->parent->color; // Set w's color to x's parent's color
                if (x->parent)
                    x->parent->color = BLACK; // Parent becomes black
                if (w && w->left)
                    w->left->color = BLACK; // Flip color: w's left child becomes black
                if (x->parent)
                    rightRotate(x->parent); // Perform right rotation on parent
                x = root;
            }
        }
    }
    if (x)
        x->color = BLACK; // Ensure x is black if it's not null
}

Node* RedBlackTree::findMin(Node* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

void RedBlackTree::insert(int data)
{
    Node* z = new Node(data); // Create a new node with the given data
    Node* y = nullptr; // Initialize y as nullptr
    Node* x = root; // Start from the root of the tree

    // Find the appropriate position to insert the new node
    while (x != nullptr)
    {
        y = x; // Update y to the current node
        if (z->item < x->item)
            x = x->left; // Move to the left subtree if z's data is less than the current node's data
        else
            x = x->right; // Move to the right subtree if z's data is greater than or equal to the current node's data
    }

    z->parent = y; // Set z's parent to the last non-null node encountered during traversal

    // If the tree is empty, set z as the root
    if (y == nullptr)
        root = z;
        // Otherwise, insert z as the left or right child of y depending on its data
    else if (z->item < y->item)
        y->left = z;
    else
        y->right = z;

    fixInsertViolation(z); // Fix any violations of the red-black tree properties caused by the insertion
}

void RedBlackTree::remove(int data)
{
    Node* z = root;
    // Find the node to be deleted
    while (z != nullptr)
    {
        if (data == z->item)
            break;
        else if (data < z->item)
            z = z->left; // Move to the left subtree if data is less than the current node's data
        else
            z = z->right; // Move to the right subtree if data is greater than the current node's data
    }
    if (z == nullptr)
        return; // If the node to be deleted is not found, return

    Node* y;
    Node* x;
    Color original_color = z->color;

    // Determine the node to replace z
    if (z->left == nullptr)
    {
        x = z->right;
        if (x == nullptr)
            y = z->parent;
        else
            x->parent = z->parent;
        if (z->parent == nullptr)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        x->parent = z->parent;
        if (z->parent == nullptr)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
    }
    else
    {
        y = findMin(z->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            if (x != nullptr) // If x is not null, update its parent to y
                x->parent = y;
        }
        else
        {
            if (x != nullptr && y->parent != nullptr) // If x and y's parent are not null, update x's parent to y's parent
                x->parent = y->parent;
            if (y->parent != nullptr) // If y's parent is not null, update y's parent's left child to x
                y->parent->left = x;
            y->right = z->right;
            if (z->right != nullptr) // If z's right child is not null, update its parent to y
                z->right->parent = y;
        }
        y->parent = z->parent;
        if (z->parent == nullptr)
            root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color; // Set y's color to z's color
    }

    if (original_color == BLACK) // If the original color of the deleted node was black, fix any violations
        fixDeleteViolation(x);

    delete z; // Delete the node
}

void RedBlackTree::erase()
{
    while (root != nullptr)
    {
        remove(root->item);
    }
}

void RedBlackTree::inOrderTraversal(Node* node)
{
    if (node == nullptr)
        return;
    inOrderTraversal(node->left);
    std::cout << node->item << " ";
    inOrderTraversal(node->right);
}

void RedBlackTree::generateDot(Node* node, ofstream& out)
{
    string color;

    if(node == nullptr)
        return; // tree is empty

    if(node->color == RED)
        color = "red";
    else
        color = "black";
    // [label="element", fillcolor="color"];
    out << "    " << node->item << " [label=\"" << node->item << "\", fillcolor=\"" << color << "\"];" << endl;

    // if left exists
    if (node->left != nullptr)
    {
        out << "    " << node->item << " -> " << node->left->item << ";" << std::endl;
        generateDot(node->left, out);
    }

    // if right exists
    if (node->right != nullptr)
    {
        out << "    " << node->item << " -> " << node->right->item << ";" << std::endl;
        generateDot(node->right, out);
    }
}

void RedBlackTree::inOrderTraversal()
{
    inOrderTraversal(root);
    std::cout << std::endl;
}

void RedBlackTree::dotFile(const std::string &filename)
{
    ofstream out(filename); // open file
    if (!out.is_open())
    {
        throw logic_error("Cannot open file");
    }

    out << "digraph RedBlackTree {" << endl;
    out << "    node [shape=circle, style=filled, color=black, fontcolor=white];" << endl;

    generateDot(root, out);

    out << "}" << endl;

    out.close();
}