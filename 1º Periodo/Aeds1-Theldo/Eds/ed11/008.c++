#include <iostream>
#include <fstream>
#include <vector>

bool verificar_valor_presente(const std::vector<int>& arranjo, int valor, int posicao_inicial, int posicao_final) {
    for (int i = posicao_inicial; i <= posicao_final; ++i) {
        if (arranjo[i] == valor) {
            return true;
        }
    }
    return false;
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

    // Ler o valor a ser procurado do teclado
    int valor_procurado;
    std::cout << "Digite o valor a ser procurado: ";
    std::cin >> valor_procurado;

    // Ler as posições inicial e final do teclado
    int posicao_inicial, posicao_final;
    std::cout << "Digite a posição inicial: ";
    std::cin >> posicao_inicial;
    std::cout << "Digite a posição final: ";
    std::cin >> posicao_final;

    // Verificar se o valor está presente no arranjo entre as posições indicadas
    bool valor_presente = verificar_valor_presente(arranjo, valor_procurado, posicao_inicial, posicao_final);

    // Exibir o resultado
    if (valor_presente) {
        std::cout << "O valor " << valor_procurado << " está presente no arranjo entre as posições " << posicao_inicial << " e " << posicao_final << "." << std::endl;
    } else {
        std::cout << "O valor " << valor_procurado << " não está presente no arranjo entre as posições " << posicao_inicial << " e " << posicao_final << "." << std::endl;
    }

    return 0;
}
