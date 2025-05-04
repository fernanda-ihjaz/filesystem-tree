#include <iostream>
#include "functions.hpp" // Inclui as funções declaradas no arquivo functions.hpp

int main() 
{
    load_tree_into_memory(); // Carrega a árvore na memória
    display_full_tree(); // Exibe a árvore completa
    export_to_html(); // Exporta a árvore para HTML
    
    search(); // Realiza uma busca na árvore
}