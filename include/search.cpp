#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "functions.hpp"

using namespace std;

string build_path(const string& currentPath, const string& name){
    return currentPath + "/" + name;
}

// Buscar maior arquivo
void find_largest_file(Node* node, long long& largestSize, vector<string>& paths, const string& currentPath) {
    if (!node) return;

    string fullPath = build_path(currentPath, node -> name);

    if (node->is_file) {
        if (node->size > largestSize) {
            largestSize = node->size;
            paths.clear();
            paths.push_back(fullPath);
        } else if (node->size == largestSize) {
            paths.push_back(fullPath);
        }
    }

    for (Node* filho : node->filhos) {
        find_largest_file(filho, largestSize, paths, fullPath);
    }
}

// Encontrar arquivos maiores que N bytes
void find_files_larger_than(Node* node, long long N, vector<pair<string, long long>>& results, const string& currentPath) {
    if (!node) return;

    string fullPath = build_path(currentPath, node -> name);

    if (node->is_file && node->size > N) {
        results.push_back({fullPath, node->size});
    }

    for (Node* filho : node->filhos) {
        find_files_larger_than(filho, N, results, fullPath);
    }
}

//encontrar pasta com mais arquivos
void find_directory_with_most_files(Node* node, const string& currentPath, int& maxCount, string& maxPath){
    if (!node || node -> is_file) return;

    string fullPath = build_path(currentPath, node -> name);
    int count = 0;

    for (Node* filho : node -> filhos){
        if (filho -> is_file) count++;
    }

    if (count > maxCount) {
        maxCount = count;
        maxPath = fullPath;
    }

    for(Node* filho : node -> filhos){
        if (!filho -> is_file){
            find_directory_with_most_files(filho, fullPath, maxCount, maxPath);
        }
    }
}

//achar arquivos pela extensão
void find_files_by_extension(Node* node, const string& ext, vector<string>& results, const string& currentPath){
    if (!node) return;

    string fullPath = build_path(currentPath, node -> name);

    if (node -> is_file && node -> name.size() >= ext.size()){
        if (node -> name.substr(node -> name.size() - ext.size()) == ext){
            results.push_back(fullPath);
        }
    }

    for (Node* filho : node -> filhos){
        find_files_by_extension(filho, ext, results, fullPath);
    }
}

//achar pastas vazias
void find_empty_directories(Node* node, vector<string>& results, const string& currentPath){
    if (!node || node -> is_file) return;

    string fullPath = build_path(currentPath, node -> name);

    if (node -> filhos.empty()){
        results.push_back(fullPath);
    }

    for (Node* filho : node -> filhos){
        if (!filho -> is_file){
            find_empty_directories(filho, results, fullPath);
        }
    }
}

void print_search_menu(){
     cout << "\n=== MENU DE PESQUISA ===\n"
          << "1. Maior Arquivo\n"
          << "2. Arquivos maiores que N bytes\n"
          << "3. Pasta com mais arquivos\n"
          << "4. Arquivos por extensao\n"
          << "5. Pastas vazias\n"
          << "0. Voltar para o menu principal\n"
          << "Opção: ";
}

// Enum exclusivo para a função de busca
enum SearchOptions {
    EXIT_SEARCH = 0,
    LARGEST_FILE = 1,
    FILES_LARGER_THAN = 2,
    MOST_FILES_IN_DIR = 3,
    FILES_BY_EXTENSION = 4,
    EMPTY_DIRS = 5
};

// Menu de busca
void search(Node* root) {
    int searchOption;

    do {
        print_search_menu();
        cin >> searchOption;
        
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida! Por favor, digite um numero. \n";
            continue;
        }
        cin.ignore();

        switch (searchOption) {
            case LARGEST_FILE: {
                long long largest = 0;
                vector<string> paths;
                find_largest_file(root, largest, paths, ".");
                cout << "\nMaior(es) Arquivo(s):\n";
                for (const auto& path : paths) {
                    cout << path << " (" << largest << " bytes)\n";
                }
                break;
            }
            case FILES_LARGER_THAN: {
                long long N;
                cout << "Digite o tamanho do arquivo em bytes: ";
                cin >> N;
                vector<pair<string, long long>> results;
                find_files_larger_than(root, N, results, ".");
                cout << "\nArquivos maiores que " << N << " bytes:\n";
                for (const auto& [path, size] : results) {
                    cout << path << " (" << size << " bytes)\n";
                }
                break;
            }
            case MOST_FILES_IN_DIR: {
                int maxCount = 0;
                string maxPath;
                find_directory_with_most_files(root, ".", maxCount, maxPath);
                cout << "\nPasta com mais arquivos: \n";
                cout << maxPath << " (" << maxCount << " arquivos)\n";
                break;
            }
            case FILES_BY_EXTENSION:{
                string ext;
                cout << "Digite a extensao do arquivo (e.g., .txt): ";
                cin >> ext;
                vector<string> results;
                find_files_by_extension(root, ext, results, ".");
                cout << "\nArquivos com a extensao " << ext << ":\n";
                for (const auto& path : results){
                    cout << path << "\n";
                }
                break;
            }
            case EMPTY_DIRS:{
                vector<string> results;
                find_empty_directories(root, results, ".");
                cout << "\nPastas vazias: \n";
                for(const auto& path : results){
                    cout << path << "\n";
                }
                break;
            }
            case EXIT_SEARCH: {
                cout << "Retornando para o menu principal...\n";
                break;
            }
            default: {
                cout << "Opcao Invalida.\n";
            }
        }
    } while (searchOption != EXIT_SEARCH);
}