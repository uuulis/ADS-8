// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>
#include <string>
#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        int freq;
        Node* leftChild;
        Node* rightChild;
        
        explicit Node(const T& val) : data(val), freq(1), leftChild(nullptr), rightChild(nullptr) {}
    };

    Node* top;

    Node* addNode(Node* current, const T& value) {
        if (current == nullptr) {
            return new Node(value);
        }
        
        if (value < current->data) {
            current->leftChild = addNode(current->leftChild, value);
        } else if (value > current->data) {
            current->rightChild = addNode(current->rightChild, value);
        } else {
            current->freq++;
        }
        return current;
    }

    int computeHeight(Node* current) const {
        if (current == nullptr) return 0;
        int leftHeight = computeHeight(current->leftChild);
        int rightHeight = computeHeight(current->rightChild);
        return 1 + std::max(leftHeight, rightHeight);
    }

    bool findKey(Node* current, const T& target) const {
        if (current == nullptr) return false;
        if (target == current->data) return true;
        if (target < current->data) return findKey(current->leftChild, target);
        return findKey(current->rightChild, target);
    }

    void gatherData(Node* current, std::vector<std::pair<T, int>>& output) const {
        if (current == nullptr) return;
        gatherData(current->leftChild, output);
        output.push_back({current->data, current->freq});
        gatherData(current->rightChild, output);
    }

    void eraseTree(Node* current) {
        if (current == nullptr) return;
        eraseTree(current->leftChild);
        eraseTree(current->rightChild);
        delete current;
    }

 public:
    BST() : top(nullptr) {}
    ~BST() { eraseTree(top); }

    void insert(const T& value) {
        top = addNode(top, value);
    }

    int depth() const {
        return computeHeight(top);
    }

    int search(const T& target) const {
        return findKey(top, target) ? 1 : 0;
    }

    std::vector<std::pair<T, int>> getAll() const {
        std::vector<std::pair<T, int>> result;
        gatherData(top, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
