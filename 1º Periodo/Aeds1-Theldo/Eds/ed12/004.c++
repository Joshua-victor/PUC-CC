#include <iostream>
#include <fstream>
#include <vector>

// Função para verificar se duas matrizes são iguais
bool areMatricesEqual(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (rows1 != rows2 || cols1 != cols2) {
        return false; // As matrizes têm tamanhos diferentes, então não são iguais
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false; // As matrizes têm elementos diferentes
            }
        }
    }

    return true; // As matrizes são iguais
}

int main() {
    std::ifstream inputFile("dados.txt");
    if (!inputFile.is_open()) {
        std::cout << "Erro ao abrir o arquivo dados.txt." << std::endl;
        return 1;
    }

    // Ler a primeira matriz do arquivo
    std::vector<std::vector<int>> matrix1;
    int num;
    while (inputFile >> num) {
        std::vector<int> row;
        row.push_back(num);
        for (int i = 1; i < num; i++) {
            inputFile >> num;
            row.push_back(num);
        }
        matrix1.push_back(row);
    }

    // Ler a segunda matriz do arquivo
    std::vector<std::vector<int>> matrix2;
    while (inputFile >> num) {
        std::vector<int> row;
        row.push_back(num);
        for (int i = 1; i < num; i++) {
            inputFile >> num;
            row.push_back(num);
        }
        matrix2.push_back(row);
    }

    inputFile.close();

    // Verificar se as matrizes são iguais
    if (areMatricesEqual(matrix1, matrix2)) {
        std::cout << "As matrizes são iguais." << std::endl;
    } else {
        std::cout << "As matrizes são diferentes." << std::endl;
    }

    return 0;
}
