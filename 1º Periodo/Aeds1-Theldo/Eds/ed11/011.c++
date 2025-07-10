#include <iostream>
#include <vector>

bool sao_diferentes(const std::vector<int>& arranjo1, const std::vector<int>& arranjo2) {
    int tamanho1 = arranjo1.size();
    int tamanho2 = arranjo2.size();

    // Verificar se os tamanhos são diferentes
    if (tamanho1 != tamanho2) {
        return true;
    }

    // Verificar elemento por elemento
    for (int i = 0; i < tamanho1; ++i) {
        if (arranjo1[i] != arranjo2[i]) {
            return true;
        }
    }

    // Os arranjos são iguais em todas as posições
    return false;
}

int main() {
    std::vector<int> arranjo1 = {1, 2, 3, 4, 5};
    std::vector<int> arranjo2 = {1, 2, 3, 4, 5};

    if (sao_diferentes(arranjo1, arranjo2)) {
        std::cout << "Os arranjos são diferentes em pelo menos uma posição." << std::endl;
    } else {
        std::cout << "Os arranjos são iguais em todas as posições." << std::endl;
    }

    return 0;
}
