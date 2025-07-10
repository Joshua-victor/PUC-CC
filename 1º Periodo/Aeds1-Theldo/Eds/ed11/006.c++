#include <iostream>
#include <fstream>
#include <vector>

bool verificar_valores_positivos(const std::vector<int>& arranjo) {
    for (int valor : arranjo) {
        if (valor <= 0) {
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

    // Verificar se todos os valores são positivos
    bool sao_positivos = verificar_valores_positivos(arranjo);

    // Exibir o resultado
    if (sao_positivos) {
        std::cout << "Todos os valores são positivos." << std::endl;
    } else {
        std::cout << "Existem valores não positivos." << std::endl;
    }

    return 0;
}
