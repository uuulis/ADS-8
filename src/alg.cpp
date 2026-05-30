// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.add(word);
                word.clear();
            }
        }
    }
    // последнее слово, если файл не заканчивается разделителем
    if (!word.empty()) {
        tree.add(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto freq = tree.getFreqVector();

    // сортировка по убыванию частоты
    std::sort(freq.begin(), freq.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    // вывод на экран
    for (const auto& p : freq) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    // запись в файл result/freq.txt
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Cannot open result/freq.txt for writing" << std::endl;
        return;
    }
    for (const auto& p : freq) {
        out << p.first << ": " << p.second << std::endl;
    }
    out.close();
}
