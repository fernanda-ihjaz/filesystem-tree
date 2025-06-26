#ifndef FUNCTIONS_HPP //ifndef é pra verificar se FUNCTIONS_HPP está definido
#define FUNCTIONS_HPP //define, se não estava

#include <string>
#include <vector>
#include <filesystem>

enum NodeTypes 
{
    root = 1,
    branch = 2,
    leaf = 3
};

struct Node 
{
    std::string name;
    bool is_file;
    long long size;
    std::vector<Node*> filhos;
    NodeTypes type;
};

#include "load_tree_into_memory.cpp"
#include "display_full_tree.cpp"
#include "export_to_html.cpp"
#include "search.cpp"

Node* load_tree_into_memory(const fs::path& path, bool is_root); // contem o nome do diretório ou arquivo, se é arquivo ou pasta, 
                                                                //o tamanho se for arquivo e um std::vector<Node*> filhos com os filhos que tem dentro
void display_full_tree(const Node* root); //recebe o Node* e percorre recursivamente a arvore em memória
int export_to_html(const Node *root, const std::string &filename);
int search(); // Funções de pesquisa

#endif
