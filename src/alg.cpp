// Copyright 2025 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream input(filename);
  if (!input.is_open()) {
    return;
  }

  std::string buffer;
  char symbol;
  while (input.get(symbol)) {
    if (std::isalpha(static_cast<unsigned char>(symbol))) {
      buffer.push_back(std::tolower(static_cast<unsigned char>(symbol)));
    } else {
      if (buffer.size() > 0) {
        tree.add(buffer);
        buffer = "";
      }
    }
  }
  if (buffer.length() > 0) {
    tree.add(buffer);
  }
  input.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> items = tree.getAll();
  
  for (size_t idx = 0; idx < items.size(); ++idx) {
    std::cout << items[idx].first << " " << items[idx].second << std::endl;
  }

  std::ofstream output("result/freq.txt");
  if (output.good()) {
    for (size_t pos = 0; pos < items.size(); ++pos) {
      output << items[pos].first << " " << items[pos].second << std::endl;
    }
    output.close();
  }
}
