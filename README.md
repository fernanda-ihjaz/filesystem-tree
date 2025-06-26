# **filesystem-tree**

Este projeto permite visualizar e explorar a estrutura de diretórios e arquivos de um sistema de arquivos como uma árvore interativa. Ele carrega a estrutura a partir de um caminho especificado (ou da pasta atual) e oferece um menu interativo para navegar entre os diretórios e arquivos.

---

## **Como executar**

### **Pré-requisitos**

- GNU/Linux
- Linguagem C++

### **Executando**

Na pasta raiz do repositório, execute:

```bash
g++ -std=c++17 filesystem-tree.cpp -o filesystem-tree.exe
``` 
Para compilar e gerar o executável do programa. Após isso:

```bash
./filesystem-tree
``` 
Para explorar o sistema de pastas do diretório atual, ou:

```bash
./filesystem-tree caminho/qualquer
``` 
Para explorar o sistema de pastas do caminho inserido.

---
## **Funcionalidades**

- **Carregamento da Árvore**
    - Carrega o sistema de arquivos como uma árvore em memória, refletindo a estrutura real dos diretórios e arquivos.

-  **Menu Interativo** com as seguintes opções:

    1. **Exibir árvore completa**: Mostra a estrutura completa com indentação, tamanhos e contagem de arquivos.
    2. **Exportar para HTML**: Gera um arquivo HTML da árvore, mantendo a mesma estrutura e informações.
    3. **Pesquisar**:

        3.1. **Maior arquivo**: Exibe o(s) maior(es) arquivo(s) encontrados no sistema.

        3.2. **Arquivos maiores que N bytes**: Solicita um valor N e lista os arquivos com tamanho maior que esse valor.
        
        3.3. **Pasta com mais arquivos diretos**: Exibe a pasta que contém o maior número de arquivos diretamente.
        
        3.4. **Arquivos por extensão**: Permite buscar arquivos com uma extensão específica.
       
        3.5. **Pastas vazias**: Lista todas as pastas que não possuem arquivos ou subpastas.

---

## **Equipe**

- **Brenda Braga de Lima**
- **Fernanda Japur Ihjaz**
- **Leticia de Fragas**


> Projeto acadêmico — Estrutura de Dados II
