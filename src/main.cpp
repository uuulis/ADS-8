// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> wordTree;
    makeTree(wordTree, "src/war_peace.txt");
    std::cout << "Tree depth: " << wordTree.depth() << std::endl;
    printFreq(wordTree);
    return 0;
}
