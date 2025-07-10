#include <iostream>
#include <fstream>
#include <random>

int main() {
    int M, N;
    std::cout << "Informe o número de linhas (M): ";
    std::cin >> M;
    std::cout << "Informe o número de colunas (N): ";
    std::cin >> N;

    // Inicialização do gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Abertura do arquivo para escrita
    std::ofstream file("DADOS.TXT");

    // Verifica se o arquivo foi aberto com sucesso
    if (file.is_open()) {
        file << M * N << std::endl; // Grava a quantidade de números aleatórios (M*N) na primeira linha do arquivo

        // Geração dos valores aleatórios e gravação no arquivo
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                double randomValue = dis(gen);
                file << randomValue << std::endl; // Grava o valor aleatório em uma linha do arquivo
            }
        }

        file.close(); // Fecha o arquivo
        std::cout << "Os dados foram gravados no arquivo DADOS.TXT." << std::endl;
    } else {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }

    return 0;
}
