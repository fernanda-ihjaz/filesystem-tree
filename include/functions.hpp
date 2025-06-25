#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>
#include <filesystem>


#include "export_to_html.cpp"
#include "search.cpp"
#include "load_tree_into_memory.cpp"
#include "display_full_tree.cpp"

enum NodeTypes {
    root = 1,
    branch = 2,
    leaf = 3
};

int load_tree_into_memory();
int display_full_tree();
int export_to_html();
int search(); // Funções de pesquisa

struct Node {
    std::string name;
    bool is_file;
    long long size;
    std::vector<Node*> filhos;
    NodeTypes type;
};

Node* load_tree_into_memory(const std::filesystem::path& path, bool is_root);
void display_full_tree(const Node* root);
void search(Node* root)

#endif
