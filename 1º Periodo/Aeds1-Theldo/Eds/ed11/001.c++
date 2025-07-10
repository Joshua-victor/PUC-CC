#include <iostream>
#include <fstream>
#include <random>

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

int main() {
    int N = 10;
    int min = 1;
    int max = 100;
    std::string nome_arquivo = "DADOS.TXT";

    std::vector<int> valores_aleatorios = gerar_valores_aleatorios(N, min, max);
    gravar_valores_em_arquivo(valores_aleatorios, nome_arquivo);

    return 0;
}
