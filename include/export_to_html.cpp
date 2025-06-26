#include "functions.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>

int export_to_html(const Node *root, const std::string &filename)
{
    // Função auxiliar para formatar tamanhos (deve ser declarada antes de ser usada)
    auto format_size = [](uintmax_t bytes) -> std::string
    {
        const char *units[] = {"B", "KB", "MB", "GB", "TB"};
        double size = bytes;
        int unit = 0;

        while (size >= 1024 && unit < 4)
        {
            size /= 1024;
            unit++;
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << size << " " << units[unit];
        return oss.str();
    };

    // 1. Abrir o arquivo HTML para escrita
    std::ofstream html(filename);
    if (!html.is_open())
    {
        std::cerr << "Erro ao criar arquivo HTML: " << filename << "\n";
        return -1;
    }

    // 2. Escrever o cabeçalho HTML com estilos CSS
    html << R"(<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Estrutura de Arquivos: )"
         << root->name << R"(</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        h1 {
            color: #2c3e50;
            border-bottom: 2px solid #3498db;
            padding-bottom: 10px;
        }
        ul.tree {
            list-style-type: none;
            padding-left: 20px;
        }
        .dir {
            color: #2980b9;
            font-weight: bold;
            cursor: pointer;
        }
        .dir::before {
            content: "📁 ";
        }
        .file {
            color: #27ae60;
        }
        .file::before {
            content: "📄 ";
        }
        .details {
            font-size: 0.9em;
            color: #7f8c8d;
            margin-left: 10px;
        }
        .size {
            font-weight: normal;
        }
        .toggle {
            cursor: pointer;
            margin-right: 5px;
        }
        .collapsed {
            display: none;
        }
        footer {
            margin-top: 30px;
            font-size: 0.8em;
            color: #95a5a6;
            text-align: center;
        }
    </style>
</head>
<body>
    <h1>Estrutura de Arquivos: )"
         << root->name << R"(</h1>
    <ul class="tree">)";

    // 3. Função auxiliar recursiva para gerar a árvore
    std::function<void(const Node *, bool)> generate_node = [&](const Node *node, bool is_last)
    {
        // Determinar a classe CSS baseado no tipo
        std::string node_class = node->is_file ? "dir" : "file";

        // Criar string de detalhes
        std::ostringstream details;
        if (node->is_file)
        {
            details << " (" << node->filhos.size() << " itens, "
                    << format_size(node->size) << ")";
        }
        else
        {
            details << " (" << format_size(node->size) << ")";
        }

        // Escrever o item da lista
        html << "\n        <li>";

        // Adicionar toggle para diretórios
        if (node->is_file && !node->filhos.empty())
        {
            html << R"(<span class="toggle" onclick="toggle(this)">[-]</span>)";
        }
        else
        {
            html << "<span style=\"width: 20px; display: inline-block;\"></span>";
        }

        html << "<span class=\"" << node_class << "\">" << node->name
             << "<span class=\"details\">" << details.str() << "</span></span>";

        // Processar filhos se existirem
        if (!node->filhos.empty())
        {
            html << "\n          <ul>";

            for (size_t i = 0; i < node->filhos.size(); ++i)
            {
                bool child_is_last = (i == node->filhos.size() - 1);
                generate_node(node->filhos[i].get(), child_is_last);
            }

            html << "\n          </ul>";
        }

        html << "\n        </li>";
    };

    // 5. Gerar o conteúdo HTML principal
    generate_node(root, true);

    // 6. Adicionar JavaScript para funcionalidade de toggle
    html << R"(
    </ul>

    <script>
        function toggle(element) {
            const parentLi = element.parentElement;
            const childUl = parentLi.querySelector('ul');
            
            if (childUl) {
                if (childUl.style.display === 'none') {
                    childUl.style.display = '';
                    element.textContent = '[-]';
                } else {
                    childUl.style.display = 'none';
                    element.textContent = '[+]';
                }
            }
        }
    </script>

    <footer>
        Gerado em )"
         << __DATE__ << " " << __TIME__ << R"( |
        Sistema de Arquivos como Árvore
    </footer>
</body>
</html>)";

    // 7. Fechar o arquivo e verificar se houve erros
    html.close();
    if (html.fail())
    {
        std::cerr << "Erro ao escrever no arquivo HTML\n";
        return -2;
    }

    std::cout << "Árvore exportada com sucesso para: " << filename << "\n";
    return 0;
}