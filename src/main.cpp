// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> container;
  makeTree(container, "src/war_peace.txt");
  std::cout << "Tree depth: " << container.depth() << std::endl;
  printFreq(container);
  return 0;
}
