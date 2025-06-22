#include "functions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

NodeTypes determine_node_type(const fs::path& path, bool is_file, bool is_root) {
    if (is_root)
        return NodeTypes::root;

    if (is_file)
        return NodeTypes::leaf;

    auto it = fs::directory_iterator(path);
    return (it == fs::end(it)) ? NodeTypes::leaf : NodeTypes::branch;
}


Node* load_tree_into_memory(const fs::path& path, bool is_root = false) {
    auto* node = new Node;
    
    node->name = path.filename().string();
    node->is_file = fs::is_regular_file(path);
    node->size = node->is_file ? fs::file_size(path) : 0;
    
    node->type = determine_node_type(path, node->is_file, is_root);

    if (node->type != 3) {
        for (const auto& entry : fs::directory_iterator(path)) {
            node->filhos.push_back(load_tree_into_memory(entry.path()));
        }
    }

    return node;
}

