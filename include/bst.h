// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
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

  Node* insert(Node* node, const T& val) {
    if (node == nullptr) {
      return new Node(val);
    }
    if (val < node->key) {
      node->left = insert(node->left, val);
    } else if (val > node->key) {
      node->right = insert(node->right, val);
    } else {
      node->count = node->count + 1;
    }
    return node;
  }

  int search(Node* node, const T& val) const {
    if (node == nullptr) {
      return 0;
    }
    if (val == node->key) {
      return node->count;
    }
    if (val < node->key) {
      return search(node->left, val);
    } else {
      return search(node->right, val);
    }
  }

  int depth(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    int leftH = depth(node->left);
    int rightH = depth(node->right);
    if (leftH > rightH) {
      return leftH + 1;
    } else {
      return rightH + 1;
    }
  }

  void collect(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (node == nullptr) {
      return;
    }
    collect(node->left, vec);
    vec.push_back(std::make_pair(node->key, node->count));
    collect(node->right, vec);
  }

  void clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void add(const T& val) {
    root = insert(root, val);
  }

  int search(const T& val) const {
    return search(root, val);
  }

  int depth() const {
    return depth(root);
  }

  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    collect(root, result);
    std::sort(result.begin(), result.end(),
      [](const std::pair<T, int>& x, const std::pair<T, int>& y) {
        if (x.second != y.second) {
          return x.second > y.second;
        }
        return x.first < y.first;
      });
    return result;
  }
};

#endif  // INCLUDE_BST_H_
