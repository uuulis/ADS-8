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
        T key;
        int count;
        Node *left, *right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& val) {
        if (!node) return new Node(val);
        if (val < node->key) {
            node->left = insert(node->left, val);
        } else if (val > node->key) {
            node->right = insert(node->right, val);
        } else {
            node->count++;
        }
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    int search(Node* node, const T& val) const {
        if (!node) return 0;
        if (val == node->key) return node->count;
        if (val < node->key) return search(node->left, val);
        return search(node->right, val);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.push_back({node->key, node->count});
        collect(node->right, out);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& val) { root = insert(root, val); }
    int depth() const { return depth(root); }
    int search(const T& val) const { return search(root, val); }
    std::vector<std::pair<T, int>> getAll() const {
        std::vector<std::pair<T, int>> result;
        collect(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
