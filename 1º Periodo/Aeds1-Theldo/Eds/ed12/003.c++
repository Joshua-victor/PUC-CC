#include <iostream>
#include <fstream>
#include <vector>

// Função para verificar se uma matriz é a identidade
bool isIdentityMatrix(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (rows != cols) {
        return false; // A matriz não é quadrada, então não pode ser a identidade
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == j && matrix[i][j] != 1) || (i != j && matrix[i][j] != 0)) {
                return false; // A matriz contém um elemento não esperado para a identidade
            }
        }
    }

    return true; // A matriz é a identidade
}

int main() {
    std::ifstream inputFile("dados.txt");
    if (!inputFile.is_open()) {
        std::cout << "Erro ao abrir o arquivo dados.txt." << std::endl;
        return 1;
    }

    // Ler a matriz do arquivo
    std::vector<std::vector<int>> matrix;
    int num;
    while (inputFile >> num) {
        std::vector<int> row;
        row.push_back(num);
        for (int i = 1; i < num; i++) {
            inputFile >> num;
            row.push_back(num);
        }
        matrix.push_back(row);
    }

    inputFile.close();

    // Verificar se a matriz é a identidade
    if (isIdentityMatrix(matrix)) {
        std::cout << "A matriz lida é a identidade." << std::endl;
    } else {
        std::cout << "A matriz lida NÃO é a identidade." << std::endl;
    }

    return 0;
}
