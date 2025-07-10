
#include <iostream>
#include <string>

int split(std::string sequencia[]) {
    std::string input;

    std::cout << "Digite a sequência de caracteres separadas por espaços em branco: ";
    std::getline(std::cin, input);

    int contador = 0;
    std::string palavra;

    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] != ' ') {
            palavra += input[i];
        } else {
            if (!palavra.empty()) {
                sequencia[contador] = palavra;
                contador++;
                palavra.clear();
            }
        }
    }

    if (!palavra.empty()) {
        sequencia[contador] = palavra;
        contador++;
    }

    return contador;
}

int main() {
    const int tamanho = 100; // Tamanho máximo do array de sequências
    std::string sequencia[tamanho];

    int quantidade = split(sequencia);

    std::cout << "Quantidade de sequências identificadas: " << quantidade << std::endl;
    std::cout << "Sequências identificadas: ";
    for (int i = 0; i < quantidade; i++) {
        std::cout << sequencia[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
