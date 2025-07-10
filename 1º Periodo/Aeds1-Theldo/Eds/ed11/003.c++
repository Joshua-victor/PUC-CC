#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <random>

int encontrar_menor_par(const std::vector<int>& arranjo) {
    int menor_par = std::numeric_limits<int>::max(); // Valor máximo possível

    for (int valor : arranjo) {
        if (valor % 2 == 0 && valor < menor_par) {
            menor_par = valor;
        }
    }

    return menor_par;
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

    // Encontrar o menor valor par
    int menor_par = encontrar_menor_par(arranjo);

    // Exibir o resultado
    if (menor_par != std::numeric_limits<int>::max()) {
        std::cout << "Menor valor par encontrado: " << menor_par << std::endl;
    } else {
        std::cout << "Não há valores pares no arranjo." << std::endl;
    }

    return 0;
}
