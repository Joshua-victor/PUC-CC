#include <iostream>
#include <fstream>
#include <vector>

int encontrar_maior_impar(const std::vector<int>& arranjo) {
    int maior_impar = 2;  // Valor de referência inicial

    for (int valor : arranjo) {
        if (valor % 2 != 0 && valor > maior_impar) {
            maior_impar = valor;
        }
    }

    return maior_impar;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: " << argv[0] << " txt" << std::endl;
        return 1;
    }

    std::string txt = argv[1];

    // Abrir o arquivo para leitura
    std::ifstream arquivo(txt);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << txt << std::endl;
        return 1;
    }

    std::vector<int> arranjo;
    int valor;

    // Ler os valores do arquivo e armazená-los no arranjo
    while (arquivo >> valor) {
        arranjo.push_back(valor);
    }

    // Fechar o arquivo
    arquivo.close();

    // Encontrar o maior valor ímpar
    int maior_impar = encontrar_maior_impar(arranjo);

    // Exibir o resultado
    if (maior_impar != 2) {
        std::cout << "Maior valor ímpar encontrado: " << maior_impar << std::endl;
    } else {
        std::cout << "Não há valores ímpares no arranjo." << std::endl;
    }

    return 0;
}
