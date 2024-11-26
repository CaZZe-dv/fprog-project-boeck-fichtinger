#pragma once

#include <memory>
#include <iostream>
#include <functional>
#include <cassert>
#include <vector>
#include <algorithm>

// Define the color enumeration
enum class Color { Red, Black };
// Forward declaration of the Node structure
template <typename T>
struct Node;
// Define a shared pointer type for the Node
template <typename T>
using NodePtr = std::shared_ptr<const Node<T>>;
// Node structure representing each element in the tree
template <typename T>
struct Node {
    Color _color;
    T _value;
    NodePtr<T> _left;
    NodePtr<T> _right;
    Node(Color color, T val, NodePtr<T> left = nullptr, NodePtr<T> right = nullptr) : _color(color), _value(val), _left(left), _right(right) {}
};
// Function to create a new node
template <typename T>
NodePtr<T> makeNode(Color color, T value, NodePtr<T> left = nullptr, NodePtr<T> right = nullptr) {
    return std::make_shared<const Node<T>>(color, value, left, right);
}
// Function to perform a left rotation
template <typename T>
NodePtr<T> rotateLeft(const NodePtr<T>& node) {
    assert(node && node->_right);
    auto newRoot = node->_right;
    return makeNode(newRoot->_color, newRoot->_value,makeNode(Color::Red, node->_value, node->_left, newRoot->_left),newRoot->_right);
}
// Function to perform a right rotation
template <typename T>
NodePtr<T> rotateRight(const NodePtr<T>& node) {
    assert(node && node->_left);
    auto newRoot = node->_left;
    return makeNode(newRoot->_color, newRoot->_value,newRoot->_left,makeNode(Color::Red, node->_value, newRoot->_right, node->_right));
}
// Function to flip colors
template <typename T>
NodePtr<T> flipColors(const NodePtr<T>& node) {
    assert(node && node->_left && node->_right);
    return makeNode(Color::Red, node->_value,makeNode(Color::Black, node->_left->_value, node->_left->_left, node->_left->_right),makeNode(Color::Black, node->_right->_value, node->_right->_left, node->_right->_right));
}
// Function to balance the tree after insertion
template <typename T>
NodePtr<T> balance(Color color, NodePtr<T> left, const T& value, NodePtr<T> right) {
    if (color == Color::Black) {
        if (doubledLeft(left)) {
            return makeNode(Color::Red, left->_value,makeNode(Color::Black, left->_left->_value, left->_left->_left, left->_left->_right),makeNode(Color::Black, value, left->_right, right));
        }
        if (doubledRight(left)) {
            return makeNode(Color::Red, left->_right->_value,makeNode(Color::Black, left->_value, left->_left, left->_right->_left),makeNode(Color::Black, value, left->_right->_right, right));
        }
        if (doubledLeft(right)) {
            return makeNode(Color::Red, right->_left->_value,makeNode(Color::Black, value, left, right->_left->_left),makeNode(Color::Black, right->_value, right->_left->_right, right->_right));
        }
        if (doubledRight(right)) {
            return makeNode(Color::Red, right->_value,makeNode(Color::Black, value, left, right->_left),makeNode(Color::Black, right->_right->_value, right->_right->_left, right->_right->_right));
        }
    }
    return makeNode(color, value, left, right);
}
template <typename T>
bool doubledLeft(const NodePtr<T>& node) {
    return node && node->_color == Color::Red && node->_left && node->_left->_color == Color::Red;
}
template <typename T>
bool doubledRight(const NodePtr<T>& node) {
    return node && node->_color == Color::Red && node->_right && node->_right->_color == Color::Red;
}
// Recursive function to insert a value into the tree
template <typename T>
NodePtr<T> insert(const NodePtr<T>& node, const T& value) {
    if (!node) return makeNode(Color::Red, value);
    if (value < node->_value) return balance(node->_color, insert(node->_left, value), node->_value, node->_right);
    else if (value > node->_value) return balance(node->_color, node->_left, node->_value, insert(node->_right, value));
    else return node; //Returns the same node if the value is already present in the tree
}
// In-order traversal of the tree
template <typename T>
void inOrderTraversal(const NodePtr<T>& node, const std::function<void(const T&)>& visit) {
    if (!node) return;
    inOrderTraversal(node->_left, visit);
    visit(node->_value);
    inOrderTraversal(node->_right, visit);
}
// Public interface for the Red-Black Tree
template <typename T>
class RedBlackTree {
    NodePtr<T> root;

public:
    RedBlackTree() : root(nullptr) {}
    // Insert a value into the tree
    RedBlackTree insert(const T& value) const {
        auto newRoot = ::insert(root, value);
        return RedBlackTree(makeNode(Color::Black, newRoot->_value, newRoot->_left, newRoot->_right));
    }
    // In-order traversal to extract sorted words
    std::vector<T> getSortedWords() const {
        std::vector<T> sortedWords;
        inOrderTraversal(root, std::function<void(const T&)>([&](const T& word) {
            sortedWords.push_back(word);
        }));
        return sortedWords;
    }
    // Validate the tree (check Red-Black Tree properties)
    bool validate() const {
        if (!root) return true;
        // Rule 2: The root must be black.
        if (root->_color != Color::Black) {
            return false;
        }
        // Rule 5: The black-height must be the same for all paths.
        int blackHeight = -1;
        return validateNode(root, blackHeight, 0);
    }
private:
    // Private constructor used internally
    RedBlackTree(NodePtr<T> root) : root(root) {}
    bool validateNode(const NodePtr<T>& node, int& expectedBlackHeight, int currentBlackHeight) const {
        if (!node) {
            if (expectedBlackHeight == -1) {
                expectedBlackHeight = currentBlackHeight;
            }
            return expectedBlackHeight == currentBlackHeight;
        }
        if (node->_color == Color::Red) {
            if ((node->_left && node->_left->_color == Color::Red) ||
                (node->_right && node->_right->_color == Color::Red)) {
                return false;
            }
        } else {
            currentBlackHeight++;
        }
        return validateNode(node->_left, expectedBlackHeight, currentBlackHeight) && validateNode(node->_right, expectedBlackHeight, currentBlackHeight);
    }
};