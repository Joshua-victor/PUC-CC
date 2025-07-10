#include <iostream>
#include <fstream>
#include <vector>

// Função para ler uma matriz de um arquivo
std::vector<std::vector<int>> lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<std::vector<int>> matriz;
    int valor;

    if (arquivo.is_open()) {
        std::vector<int> linha;
        while (arquivo >> valor) {
            linha.push_back(valor);

            if (arquivo.peek() == '\n' || arquivo.peek() == EOF) {
                matriz.push_back(linha);
                linha.clear();
            }
        }

        arquivo.close();
    }

    return matriz;
}

// Função para procurar um valor na matriz e retornar as colunas onde ele está presente
std::vector<int> procurarColunas(const std::vector<std::vector<int>>& matriz, int procurado) {
    std::vector<int> colunas;

    for (size_t j = 0; j < matriz[0].size(); j++) {
        for (size_t i = 0; i < matriz.size(); i++) {
            if (matriz[i][j] == procurado) {
                colunas.push_back(j);
                break;
            }
        }
    }

    return colunas;
}

int main() {
    std::string nomeArquivo1 = "DADOS1.TXT";
    int procurado = 42;

    // Ler a matriz do arquivo
    std::vector<std::vector<int>> matriz1 = lerArquivo(nomeArquivo1);

    // Procurar o valor na matriz
    std::vector<int> colunasEncontradas = procurarColunas(matriz1, procurado);

    // Mostrar as colunas onde o valor foi encontrado
    if (colunasEncontradas.empty()) {
        std::cout << "Valor nao encontrado na matriz." << std::endl;
    } else {
        std::cout << "O valor " << procurado << " foi encontrado nas seguintes colunas:" << std::endl;
        for (const auto& coluna : colunasEncontradas) {
            std::cout << coluna << std::endl;
        }
    }

    return 0;
}
