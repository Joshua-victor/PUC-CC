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

// Função para procurar um valor na matriz e retornar as linhas onde ele está presente
std::vector<int> procurarLinhas(const std::vector<std::vector<int>>& matriz, int procurado) {
    std::vector<int> linhas;

    for (size_t i = 0; i < matriz.size(); i++) {
        for (size_t j = 0; j < matriz[i].size(); j++) {
            if (matriz[i][j] == procurado) {
                linhas.push_back(i);
                break;
            }
        }
    }

    return linhas;
}

int main() {
    std::string nomeArquivo1 = "DADOS1.TXT";
    int procurado = 42;

    // Ler a matriz do arquivo
    std::vector<std::vector<int>> matriz1 = lerArquivo(nomeArquivo1);

    // Procurar o valor na matriz
    std::vector<int> linhasEncontradas = procurarLinhas(matriz1, procurado);

    // Mostrar as linhas onde o valor foi encontrado
    if (linhasEncontradas.empty()) {
        std::cout << "Valor nao encontrado na matriz." << std::endl;
    } else {
        std::cout << "O valor " << procurado << " foi encontrado nas seguintes linhas:" << std::endl;
        for (const auto& linha : linhasEncontradas) {
            std::cout << linha << std::endl;
        }
    }

    return 0;
}
