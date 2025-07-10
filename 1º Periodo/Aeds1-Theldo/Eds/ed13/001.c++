#include <iostream>
#include <string>

class Contato {
private:
    std::string nome;

public:
    void readNome(const std::string& mensagem) {
        std::cout << mensagem;
        std::getline(std::cin, nome);
    }

    void testarNome() {
        if (!nome.empty()) {
            std::cout << "Nome: " << nome << std::endl;
        } else {
            std::cout << "Nome vazio!" << std::endl;
        }
    }
};

int main() {
    Contato contato1;
    contato1.readNome("Digite o nome: ");
    contato1.testarNome();

}
