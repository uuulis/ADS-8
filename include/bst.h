// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void insert(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
            return;
        }
        if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        } else {
            ++(node->count);
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    bool search(Node* node, const T& value) const {
        if (node == nullptr) return false;
        if (value == node->key) return true;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& freq) const {
        if (node == nullptr) return;
        collect(node->left, freq);
        freq.push_back({node->key, node->count});
        collect(node->right, freq);
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void add(const T& key) {
        insert(root, key);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    std::vector<std::pair<T, int>> getFreqVector() const {
        std::vector<std::pair<T, int>> result;
        collect(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
