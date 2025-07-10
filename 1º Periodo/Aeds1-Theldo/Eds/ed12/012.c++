#include <iostream>
#include <vector>

std::vector<std::vector<int>> construirMatrizCaracteristica() {
    std::vector<std::vector<int>> matriz;

    matriz.push_back({1, 5, 9, 13});
    matriz.push_back({1, 4, 7, 2, 6, 10, 14});
    matriz.push_back({1, 3, 2, 5, 8, 3, 7, 11, 15});
    matriz.push_back({2, 4, 3, 6, 9, 4, 8, 12, 16});

    return matriz;
}

void exibirMatriz(const std::vector<std::vector<int>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& elemento : linha) {
            std::cout << elemento << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> matriz = construirMatrizCaracteristica();

    exibirMatriz(matriz);

    return 0;
}
