#include <iostream>
#include <string>

bool contains(const std::string& texto, const std::string& parametro) {
    if (texto.find(parametro) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::string texto = "Exemplo de texto contendo uma palavra";
    std::string parametro = "palavra";

    bool resultado = contains(texto, parametro);
    std::cout << "Contém o parâmetro? " << std::boolalpha << resultado << std::endl;

    return 0;
}
