#include <iostream>
#include <string>

std::string inverterOrdem(const std::string& cadeia) {
    std::string invertida;

    for (int i = cadeia.length() - 1; i >= 0; i--) {
        invertida += cadeia[i];
    }

    return invertida;
}

int main() {
    std::string cadeia;

    std::cout << "Digite uma cadeia de caracteres: ";
    std::getline(std::cin, cadeia);

    std::string invertida = inverterOrdem(cadeia);

    std::cout << "Cadeia invertida: " << invertida << std::endl;

    return 0;
}
