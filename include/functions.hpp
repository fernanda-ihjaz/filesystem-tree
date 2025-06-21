#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

enum NodeTypes {
    root = 1,
    branch = 2,
    leaf = 3
};

struct Node {
    std::string name;
    bool is_file;
    long long size;
    std::vector<Node*> filhos;
    NodeTypes type;
};

#include "load_tree_into_memory.cpp"
#include "display_full_tree.cpp"
//#include "export_to_html.cpp"
//#include "search.cpp"

Node* load_tree_into_memory(const fs::path& path, bool is_root);
void display_full_tree(const Node* root);
// int export_to_html();
// int search(); // Funções de pesquisa

#endif
