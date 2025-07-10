#include <iostream>
#include <string>

class Exemplo1318 {
private:
    std::string nome;
    std::string telefone1;
    std::string telefone2;

public:
    void setNome(const std::string& novoNome) {
        nome = novoNome;
    }

    void setTelefone1(const std::string& novoTelefone) {
        telefone1 = novoTelefone;
    }
    

    void setTelefone2(const std::string& novoTelefone) {
        telefone2 = novoTelefone;
    }

    void atribuirSegundoTelefone() {
        if (telefone2.empty()) {
            std::string resposta;
            std::cout << "Deseja adicionar um segundo telefone? (S/N): ";
            std::cin >> resposta;

            if (resposta == "S" || resposta == "s") {
                std::string novoTelefone;
                std::cout << "Informe o segundo telefone: ";
                std::cin >> novoTelefone;
                telefone2 = novoTelefone;
                std::cout << "Segundo telefone adicionado com sucesso!" << std::endl;
            }
        } else {
            std::cout << "O contato já possui um segundo telefone." << std::endl;
        }
    }

    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Telefone 1: " << telefone1 << std::endl;
        std::cout << "Telefone 2: " << telefone2 << std::endl;
    }
};

int main() {
    Exemplo1318 contato;
    contato.setNome("John Doe");
    contato.setTelefone1("1234567890");
    contato.exibirContato();

    contato.atribuirSegundoTelefone();
    contato.exibirContato();

    return 0;
}
