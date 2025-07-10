#include <iostream>
#include <string>

class Exemplo1313 {
private:
    bool isTelefoneValido(const std::string& telefone) {
        for (char c : telefone) {
            if (!isdigit(c) && c != '-') {
                return false;
            }
        }
        return true;
    }

public:
    void testarTelefone(const std::string& telefone) {
        if (isTelefoneValido(telefone)) {
            std::cout << "Telefone válido: " << telefone << std::endl;
        } else {
            std::cout << "Telefone inválido: " << telefone << std::endl;
        }
    }
};

int main() {
    Exemplo1313 exemplo;
    exemplo.testarTelefone("123456");
    exemplo.testarTelefone("123456");
    exemplo.testarTelefone("12A-3456");

    return 0;
}