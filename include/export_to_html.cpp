#include "functions.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>

using namespace std;

int export_to_html(const Node* root, const std::string& filename) {
    if (!root) {
        std::cerr << "Erro: árvore vazia.\n";
        return -1;
    }

    std::ofstream html(filename);
    if (!html.is_open()) {
        std::cerr << "Erro ao criar o arquivo HTML: " << filename << "\n";
        return -2;
    }

    // Função auxiliar para formatar tamanhos
    auto format_size = [](uintmax_t bytes) -> std::string {
        const char* units[] = {"B", "KB", "MB", "GB", "TB"};
        double size = bytes;
        int unit = 0;

        while (size >= 1024 && unit < 4) {
            size /= 1024;
            unit++;
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << size << " " << units[unit];
        return oss.str();
    };

    // Cabeçalho básico do HTML
    html << "<!DOCTYPE html>\n<html lang=\"pt-BR\">\n<head>\n"
         << "<meta charset=\"UTF-8\">\n"
         << "<title>Árvore de Arquivos</title>\n"
         << "<style>\n"
         << "body { font-family: Arial; }\n"
         << "ul { list-style-type: none; }\n"
         << ".dir { color: blue; font-weight: bold; }\n"
         << ".file { color: green; }\n"
         << "</style>\n"
         << "</head>\n<body>\n"
         << "<h1>Árvore de Arquivos: " << root->name << "</h1>\n"
         << "<ul>\n";

    // Função recursiva para imprimir os nós
    std::function<void(const Node*)> write_node;
    write_node = [&](const Node* node) {
        if (!node) return;

        html << "<li>";

        if (!node->is_file)
            html << "<span class=\"dir\">" << node->name << "</span>";
        else
            html << "<span class=\"file\">" << node->name
                 << " (" << format_size(node->size) << ")</span>";

        if (!node->filhos.empty()) {
            html << "\n<ul>\n";
            for (const auto& child : node->filhos)
                write_node(child);
            html << "</ul>\n";
        }

        html << "</li>\n";
    };

    write_node(root);

    html << "</ul>\n</body>\n</html>";
    html.close();

    std::cout << "Árvore exportada para '" << filename << "' com sucesso.\n";
    return 0;
}
