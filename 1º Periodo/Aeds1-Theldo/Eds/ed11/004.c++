#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <random>

int somar_valores_entre_posicoes(const std::vector<int>& arranjo, int posicao_inicial, int posicao_final) {
    int soma = 0;

    for (int i = posicao_inicial; i <= posicao_final; ++i) {
        soma += arranjo[i];
    }

    return soma;
}

void gravar_valores_em_arquivo(const std::vector<int>& valores, const std::string& nome_arquivo) {
    std::ofstream arquivo(nome_arquivo);
    if (arquivo.is_open()) {
        arquivo << valores.size() << '\n';
        for (int valor : valores) {
            arquivo << valor << '\n';
        }
        arquivo.close();
    } else {
        std::cout << "Erro ao abrir o arquivo " << nome_arquivo << std::endl;
    }
}

std::vector<int> gerar_valores_aleatorios(int N, int min, int max) {
    std::vector<int> arranjo;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    for (int i = 0; i < N; ++i) {
        int valor_aleatorio = uni(rng);
        arranjo.push_back(valor_aleatorio);
    }

    return arranjo;
}

int main() {
    int N = 10;
    int min = 1;
    int max = 100;
    std::string nome_arquivo = "DADOS.TXT";

    // Gerar os valores aleatórios
    std::vector<int> valores_aleatorios = gerar_valores_aleatorios(N, min, max);

    // Gravar os valores em um arquivo
    gravar_valores_em_arquivo(valores_aleatorios, nome_arquivo);

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

    // Definir as posições iniciais e finais para a soma
    int posicao_inicial = 2;
    int posicao_final = 7;

    // Somar os valores entre as posições dadas
    int soma = somar_valores_entre_posicoes(arranjo, posicao_inicial, posicao_final);

    // Exibir o resultado
    std::cout << "Soma dos valores entre as posições " << posicao_inicial << " e " << posicao_final << ": " << soma << std::endl;

    return 0;
}
