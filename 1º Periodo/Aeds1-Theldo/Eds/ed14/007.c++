#include <iostream>
#include <string>

std::string replace(char original, char novo, const std::string& texto) {
    std::string resultado = texto;
    for (char& caractere : resultado) {
        if (caractere == original) {
            caractere = novo;
        }
    }
    return resultado;
}

int main() {
    char original, novo;
    char texto[10];

    std::cout << "Digite o caractere original: ";
    std::cin >> original;

    std::cout << "Digite o novo caractere: ";
    std::cin >> novo;

    std::cout << "Digite o texto: ";
    std::cin >> texto;

    std::string resultado = replace(original, novo, texto);
    std::cout << "Texto com substituições: " << resultado << std::endl;

    return 0;
}
