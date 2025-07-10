#include <iostream>
#include <vector>

// Função para verificar se a matriz possui a característica de número de elementos irregular em cada linha
bool possuiCaracteristicaIrregular(const std::vector<std::vector<int>>& matriz) {
    for (size_t i = 1; i < matriz.size(); i++) {
        if (matriz[i].size() != matriz[i - 1].size()) {
            return true; // A matriz possui a característica irregular
        }
    }

    return false; // A matriz não possui a característica irregular
}

int main() {
    std::vector<std::vector<int>> matriz = {
        {1, 2, 3, 4},
        {1, 2, 3, 5, 6, 7, 8},
        {1, 2, 4, 5, 6, 9, 10, 11, 12},
        {3, 4, 7, 8, 9, 13, 14, 15, 16}
    };

    // Verificar se a matriz possui a característica irregular
    bool possuiCaracteristica = possuiCaracteristicaIrregular(matriz);

    if (possuiCaracteristica) {
        std::cout << "A matriz possui a caracteristica de numero de elementos irregular em cada linha." << std::endl;
    } else {
        std::cout << "A matriz nao possui a caracteristica de numero de elementos irregular em cada linha." << std::endl;
    }

    return 0;
}
