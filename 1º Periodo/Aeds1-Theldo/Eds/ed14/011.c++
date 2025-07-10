#include <iostream>
#include <string>

const int MAX_SEQUENCIAS = 100; // Número máximo de sequências

int split(const std::string& conteudo, char delimitador, std::string sequencia[]) {
    int contador = 0;
    std::string sequenciaAtual;

    for (char caractere : conteudo) {
        if (caractere != delimitador) {
            sequenciaAtual += caractere;
        } else {
            if (!sequenciaAtual.empty()) {
                sequencia[contador] = sequenciaAtual;
                contador++;
                sequenciaAtual.clear();
            }
        }
    }

    if (!sequenciaAtual.empty()) {
        sequencia[contador] = sequenciaAtual;
        contador++;
    }

    return contador;
}

int main() {
    std::string conteudo;
    char delimitador;
    std::string sequencia[MAX_SEQUENCIAS];

    std::cout << "Digite o conteúdo a ser fragmentado: ";
    std::getline(std::cin, conteudo);

    std::cout << "Digite o delimitador: ";
    std::cin >> delimitador;

    int quantidade = split(conteudo, delimitador, sequencia);

    std::cout << "Quantidade de sequências identificadas: " << quantidade << std::endl;
    std::cout << "Sequências identificadas: ";
    for (int i = 0; i < quantidade; i++) {
        std::cout << sequencia[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
