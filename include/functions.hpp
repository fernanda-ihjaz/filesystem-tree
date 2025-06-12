#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

int load_tree_into_memory();
int display_full_tree();
int export_to_html();
int search(); // Funções de pesquisa
struct Node {
    std::string name;
    bool is_file;
    long long size;
    std::vector<Node*> filhos;
};

#endif
