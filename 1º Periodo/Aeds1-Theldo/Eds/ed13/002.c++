#include <iostream>
#include <string>

class Contato {
private:
    std::string nome;
    std::string telefone;

public:
    void lerNomeDoTeclado(const std::string& mensagem) {
        std::cout << mensagem;
        std::getline(std::cin, nome);
    }

    void readFone(const std::string& mensagem) {
        std::cout << mensagem;
        std::getline(std::cin, telefone);
    }

    void testarTelefone() {
        if (!telefone.empty()) {
            std::cout << "Telefone: " << telefone << std::endl;
        } else {
            std::cout << "Telefone vazio!" << std::endl;
        }
    }
};

int main() {
    Contato contato1;
    contato1.lerNomeDoTeclado("Digite o nome: ");
    contato1.readFone("Digite o telefone: ");
    contato1.testarTelefone();

}
