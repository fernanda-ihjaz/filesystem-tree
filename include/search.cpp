#include <iostream>
#include <vector>
#include <string>

#include "functions.hpp"

using namespace std;

// 3.1 - Buscar maior arquivo
void find_largest_file(Node* node, long long& largestSize, vector<string>& paths, string currentPath) {
    if (!node) return;

    string fullPath = currentPath + "/" + node->name;

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
void find_files_larger_than(Node* node, long long N, vector<pair<string, long long>>& results, string currentPath) {
    if (!node) return;

    string fullPath = currentPath + "/" + node->name;

    if (node->is_file && node->size > N) {
        results.push_back({fullPath, node->size});
    }

    for (Node* filho : node->filhos) {
        find_files_larger_than(filho, N, results, fullPath);
    }
}

//encontrar pasta com mais arquivos
void find_directory_with_most_files(Node* node, string currentPath, int& maxCount, string& maxPath){
    if (!node || node -> is_file) return;

    string fullPath = currentPath + "/" + node -> name;
    int count = 0;

    for (Node* filho : node -> filhos){
        if (filho -> is_file) count++;
    }

    if (count > maxCount) {
        maxCount - count;
        maxPath = fullPath;
    }

    for(Node* filho : node -> filhos){
        if (!filho -> is_file){
            find_directory_with_most_files(filho, fullPath, maxCount, maxPath);
        }
    }
}

//achar arquivos pela extensão
void find_files_by_extension(Node* node, const string& ext, vector<string>& results, string currentPath){
    if (!node) return;

    string fullPath = currentPath + "/" + node -> name;
}

//achar pastas vazias
void find_empty_directories(Node* node, vector<string>& results, string currentPath){
    if (!node || node -> is_file) return;

    string fullpath = currentPath + "/" + node -> name;

    if (node -> filhos.empty()){
        results.push_back(fullPath);
    }
}

// Menu de busca
void search(Node* root) {
    int searchOption;
    do {
        cout << "\n=== MENU DE PESQUISA ===\n"
             << "1. Maior Arquivo\n"
             << "2. Arquivos maiores que N bytes\n"
             << "3. Pasta com mais arquivos\n"
             << "4. Arquivos por extensao\n"
             << "5. Pastas Vazias\n"
             << "0. Voltar para o menu principal\n"
             << "Opção: ";
        cin >> searchOption;
        cin.ignore();

        switch (searchOption) {
            case 1: {
                long long largest = 0;
                vector<string> paths;
                find_largest_file(root, largest, paths, ".");
                cout << "\nMaior(es) Arquivo(s):\n";
                for (const string& path : paths) {
                    cout << path << " ( " << largest << " bytes)\n";
                }
                break;
            }
            case 2: {
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
            case 3: {
                int maxCount = 0;
                string maxPath;
                find_directory_with_most_files(root, ".", maxCount, maxPath);
                cout << "\nPasta com mais arquivos: \n";
                cout << maxPath << "(" << maxCount << " arquivos)\n";
                break;

            }
            case 4:{

            }
            case 5:{

            }
            case 0: {
                cout << "Retornando para o menu principal...\n";
                break;
            }
        }
    } while (searchOption != 0);
}