// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }
    
    std::string word;
    int c;
    
    while ((c = file.get()) != EOF) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            word += static_cast<char>(c | 32);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    
    if (!word.empty()) {
        tree.insert(word);
    }
    
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.getAll();
    
    std::sort(words.begin(), words.end(),
        [](const std::pair<std::string, int>& a,
           const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    
    std::ofstream out("result/freq.txt");
    
    for (const auto& p : words) {
        std::cout << p.first << " " << p.second << "\n";
        if (out) {
            out << p.first << " " << p.second << "\n";
        }
    }
}
