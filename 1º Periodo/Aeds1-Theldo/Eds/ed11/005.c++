#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <random>

double calcular_media_entre_posicoes(const std::vector<int>& arranjo, int posicao_inicial, int posicao_final) {
    double soma = 0;
    int quantidade_valores = 0;

    for (int i = posicao_inicial; i <= posicao_final; ++i) {
        soma += arranjo[i];
        quantidade_valores++;
    }

    if (quantidade_valores > 0) {
        return soma / quantidade_valores;
    } else {
        return 0;
    }
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

    // Definir as posições iniciais e finais para o cálculo da média
    int posicao_inicial, posicao_final;
    std::cout << "Digite a posição inicial: ";
    std::cin >> posicao_inicial;
    std::cout << "Digite a posição final: ";
    std::cin >> posicao_final;

    // Calcular a média dos valores entre as posições dadas
    double media = calcular_media_entre_posicoes(arranjo, posicao_inicial, posicao_final);

    // Exibir o resultado
    std::cout << "Média dos valores entre as posições " << posicao_inicial << " e " << posicao_final << ": " << media << std::endl;

    return 0;
}
