#include <iostream>
#include <fstream>
#include <vector>

void escalar_dados(std::vector<int>& arranjo, int constante, int posicao_inicial, int posicao_final) {
    for (int i = posicao_inicial; i <= posicao_final; ++i) {
        arranjo[i] *= constante;
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

    // Ler a constante do teclado
    int constante;
    std::cout << "Digite a constante de multiplicação: ";
    std::cin >> constante;

    // Ler as posições inicial e final do teclado
    int posicao_inicial, posicao_final;
    std::cout << "Digite a posição inicial: ";
    std::cin >> posicao_inicial;
    std::cout << "Digite a posição final: ";
    std::cin >> posicao_final;

    // Escalar os dados no arranjo entre as posições indicadas
    escalar_dados(arranjo, constante, posicao_inicial, posicao_final);

    // Exibir o arranjo resultante
    std::cout << "Arranjo resultante: ";
    for (int valor : arranjo) {
        std::cout << valor << " ";
    }
    std::cout << std::endl;

    return 0;
}
