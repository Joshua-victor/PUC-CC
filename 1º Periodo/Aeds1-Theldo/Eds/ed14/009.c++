#include <iostream>
#include <string>

std::string decrypt(const std::string& texto, int chave) {
    std::string resultado = texto;
    chave = chave % 26; // Ajusta a chave para um valor válido no intervalo de 0 a 25

    for (char& caractere : resultado) {
        if (std::isalpha(caractere)) {
            char base = (std::isupper(caractere)) ? 'A' : 'a';
            caractere = ((caractere - base - chave + 26) % 26) + base;
        }
    }

    return resultado;
}

int main() {
    std::string texto;
    int chave;

    std::cout << "Digite o texto a ser decodificado: ";
    std::getline(std::cin, texto);

    std::cout << "Digite a chave da cifra de César: ";
    std::cin >> chave;

    std::string resultado = decrypt(texto, chave);
    std::cout << "Texto decodificado: " << resultado << std::endl;

    return 0;
}
