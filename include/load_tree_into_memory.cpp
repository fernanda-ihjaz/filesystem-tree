#include "functions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

//determine_node_type é uma função pra determinar o que é raiz, ramo ou folha
NodeTypes determine_node_type(const fs::path& path, bool is_file, bool is_root) 
{
    if (is_root)
        return NodeTypes::root; //raiz

    if (is_file)
        return NodeTypes::leaf; //folha

    auto iterador = fs::directory_iterator(path); //esse iterador verifica se o nó (pasta no caso) está vazio
    //ai se não tiver itens dentro da pasta, ela é considerada folha:
    return (iterador == fs::end(iterador)) ? NodeTypes::leaf : NodeTypes::branch;
}


Node* load_tree_into_memory(const fs::path& path, bool is_root = false) 
{
    auto* node = new Node; // cria um espaço na memória pra um tipo node e atribui a um ponteiro
    
    node->name = path.filename().string(); 
    node->is_file = fs::is_regular_file(path); 
    node->size = node->is_file ? fs::file_size(path) : 0;
    
    node->type = determine_node_type(path, node->is_file, is_root);

    // se o no não for folha, esse if chama a função recursivamente e adiciona os filhos a arvore
    if (node->type != 3) 
    {
        for (const auto& entry : fs::directory_iterator(path)) 
        {
            node->filhos.push_back(load_tree_into_memory(entry.path())); //esse push_back adiciona o filho ao final do vetor
        }
    }

    return node;
}

