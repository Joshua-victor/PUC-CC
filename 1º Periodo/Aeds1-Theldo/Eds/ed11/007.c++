#include <iostream>
#include <fstream>
#include <vector>

bool verificar_ordem_crescente(const std::vector<int>& arranjo) {
    for (int i = 1; i < arranjo.size(); ++i) {
        if (arranjo[i] < arranjo[i - 1]) {
            return false;
        }
    }
    return true;
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

    // Verificar se os valores estão ordenados em ordem crescente
    bool esta_ordenado = verificar_ordem_crescente(arranjo);

    // Exibir o resultado
    if (esta_ordenado) {
        std::cout << "O arranjo está ordenado em ordem crescente." << std::endl;
    } else {
        std::cout << "O arranjo não está ordenado em ordem crescente." << std::endl;
    }

    return 0;
}
