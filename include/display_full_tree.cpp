#include "functions.hpp"

#include <iostream>
#include <string>

void print_tree(const Node* node, const std::string& prefix = "", bool is_last = true) {
    if (!node) return;

    std::cout << prefix;

    if (!prefix.empty()) {
        std::cout << (is_last ? "└── " : "├── ");
    }

    std::cout << node->name;

    if (node->is_file)
        std::cout << " (" << node->size << " bytes)";
    
    std::cout << std::endl;

    for (size_t i = 0; i < node->filhos.size(); ++i) {
        bool last = (i == node->filhos.size() - 1);
        print_tree(node->filhos[i], prefix + (is_last ? "    " : "│   "), last);
    }
}

void display_full_tree(const Node* root) {
    if (!root) {
        std::cout << "Árvore vazia.\n";
        return;
    }

    print_tree(root);
}