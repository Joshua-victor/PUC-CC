#include <iostream>
#include <fstream>
#include <vector>

void ordenar_arranjo(std::vector<int>& arranjo) {
    int tamanho = arranjo.size();
    bool houve_troca = true;

    while (houve_troca) {
        houve_troca = false;

        for (int i = 0; i < tamanho - 1; ++i) {
            if (arranjo[i] > arranjo[i + 1]) {
                std::swap(arranjo[i], arranjo[i + 1]);
                houve_troca = true;
            }
        }
    }
}

int main() {
    std::string nome_arquivo = "DADOS.TXT";

    // Ler os valores do arquivo
    std::ifstream arquivo_leitura(nome_arquivo);
    if (!arquivo_leitura.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << nome_arquivo << std::endl;
        return 1;
    }

    int quantidade_valores;
    arquivo_leitura >> quantidade_valores;
    std::vector<int> arranjo;
    int valor;
    for (int i = 0; i < quantidade_valores; ++i) {
        arquivo_leitura >> valor;
        arranjo.push_back(valor);
    }

    arquivo_leitura.close();

    // Ordenar o arranjo
    ordenar_arranjo(arranjo);

    // Exibir o arranjo ordenado
    std::cout << "Arranjo ordenado: ";
    for (int valor : arranjo) {
        std::cout << valor << " ";
    }
    std::cout << std::endl;

    return 0;
}
