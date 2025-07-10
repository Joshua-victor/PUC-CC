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

// Função para somar duas matrizes
std::vector<std::vector<int>> somarMatrizes(const std::vector<std::vector<int>>& matriz1, const std::vector<std::vector<int>>& matriz2) {
    std::vector<std::vector<int>> resultado;

    // Verificar se as matrizes têm as mesmas dimensões
    if (matriz1.size() != matriz2.size() || matriz1[0].size() != matriz2[0].size()) {
        std::cout << "Erro: as matrizes têm dimensões diferentes." << std::endl;
        return resultado;
    }

    for (size_t i = 0; i < matriz1.size(); i++) {
        std::vector<int> linha;
        for (size_t j = 0; j < matriz1[i].size(); j++) {
            int soma = matriz1[i][j] + matriz2[i][j];
            linha.push_back(soma);
        }
        resultado.push_back(linha);
    }

    return resultado;
}

// Função para operar duas linhas da matriz
void subtrairLinhas(std::vector<std::vector<int>>& matriz, int linha1, int linha2, int constante) {
    if (linha1 < 0 || linha1 >= matriz.size() || linha2 < 0 || linha2 >= matriz.size()) {
        std::cout << "Erro: índices de linha inválidos." << std::endl;
        return;
    }

    for (size_t i = 0; i < matriz[linha1].size(); i++) {
        matriz[linha1][i] -= matriz[linha2][i] * constante;
    }
}

int main() {
    std::string nomeArquivo1 = "DADOS1.TXT";

    // Ler a matriz do arquivo
    std::vector<std::vector<int>> matriz1 = lerArquivo(nomeArquivo1);

    // Operar as linhas da matriz
    subtrairLinhas(matriz1, 0, 1, 2);

    // Mostrar a matriz resultante
    std::cout << "Matriz resultante:" << std::endl;
    for (const auto& linha : matriz1) {
        for (const auto& valor : linha) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
