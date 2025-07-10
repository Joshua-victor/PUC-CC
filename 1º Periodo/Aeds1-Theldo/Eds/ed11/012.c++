#include <iostream>
#include <vector>

std::vector<int> calcular_diferencas(const std::vector<int>& arranjo1, const std::vector<int>& arranjo2) {
    int tamanho1 = arranjo1.size();
    int tamanho2 = arranjo2.size();
    int tamanho_min = std::min(tamanho1, tamanho2);

    std::vector<int> diferencas;

    // Calcular diferenças posição por posição até o tamanho mínimo
    for (int i = 0; i < tamanho_min; ++i) {
        int diferenca = arranjo1[i] - arranjo2[i];
        diferencas.push_back(diferenca);
    }

    // Se um arranjo é maior que o outro, adicionar as diferenças restantes
    if (tamanho1 > tamanho2) {
        for (int i = tamanho_min; i < tamanho1; ++i) {
            diferencas.push_back(arranjo1[i]);
        }
    } else if (tamanho2 > tamanho1) {
        for (int i = tamanho_min; i < tamanho2; ++i) {
            diferencas.push_back(-arranjo2[i]);
        }
    }

    return diferencas;
}

int main() {
    std::vector<int> arranjo1 = {1, 2, 3, 4, 5};
    std::vector<int> arranjo2 = {5, 4, 3, 2};

    std::vector<int> diferencas = calcular_diferencas(arranjo1, arranjo2);

    std::cout << "Diferenças entre os arranjos: ";
    for (int diferenca : diferencas) {
        std::cout << diferenca << " ";
    }
    std::cout << std::endl;

    return 0;
}
