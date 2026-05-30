// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream sourceFile(filename);
    if (!sourceFile.is_open()) {
        return;
    }
    
    std::string buffer;
    unsigned char symbol;
    
    while (sourceFile.get(reinterpret_cast<char&>(symbol))) {
        if (std::isalpha(symbol)) {
            buffer += static_cast<char>(std::tolower(symbol));
        } else {
            if (!buffer.empty()) {
                tree.insert(buffer);
                buffer.clear();
            }
        }
    }
    
    if (!buffer.empty()) {
        tree.insert(buffer);
    }
    
    sourceFile.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> statistics = tree.getAll();
    
    std::sort(statistics.begin(), statistics.end(),
        [](const std::pair<std::string, int>& first,
           const std::pair<std::string, int>& second) {
            return first.second > second.second;
        });
    
    std::ofstream outputFile("result/freq.txt");
    
    for (const auto& entry : statistics) {
        std::cout << entry.first << ": " << entry.second << std::endl;
        if (outputFile.is_open()) {
            outputFile << entry.first << ": " << entry.second << std::endl;
        }
    }
}
