#include <iostream>
#include <filesystem>
#include "include/functions.hpp"

using namespace std;
using namespace filesystem;

int main(int argc, char* argv[]) 
{
    path root_path = (argc >= 2) ? path(argv[1]) : current_path();

    if (!exists(root_path) || !is_directory(root_path)) 
    {
        cerr << "Erro: caminho inválido.\n";
        return 1;
    }

    Node* root = load_tree_into_memory(root_path, true); // Carrega a árvore
    if (!root) 
    {
        cerr << "Erro ao carregar a árvore.\n";
        return 1;
    }

    int option;
    do {
        cout << "\n=== MENU ===\n"
             << "1. Exibir árvore completa\n"
             << "2. Exportar para HTML\n"
             << "3. Pesquisar\n"
             << "0. Sair\n"
             << "Opção: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                display_full_tree(root);
                break;
            case 2:
                //export_to_html(root, "saida.html");
                cout << "Exportado para 'saida.html'\n";
                break;
            case 3:
                //search(root);
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }
    } while (option != 0);

    return 0;
}
