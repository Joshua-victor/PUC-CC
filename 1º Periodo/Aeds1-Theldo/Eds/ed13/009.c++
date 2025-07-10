#include <iostream>
#include <string>

class Contato {
private:
    std::string nome;
    std::string telefone1;
    std::string telefone2;

public:
    // Construtor
    Contato(const std::string& nome, const std::string& telefone1, const std::string& telefone2) :
        nome(nome), telefone1(telefone1), telefone2(telefone2) {}

    // Método para alterar o valor do segundo telefone
    void setFone2b(const std::string& novoTelefone) {
        if (telefone2.empty()) {
            std::cerr << "Erro: O contato não possui segundo telefone." << std::endl;
            return;
        }
        telefone2 = novoTelefone;
    }

    // Método para exibir as informações do contato
    void exibirContato() const {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Telefone 1: " << telefone1 << std::endl;
        std::cout << "Telefone 2: " << telefone2 << std::endl;
    }
};

int main() {
    // Criando um contato de exemplo
    Contato contato("João", "12345", "54321");

    // Exibindo informações do contato antes da alteração
    std::cout << "Informações do contato antes da alteração:" << std::endl;
    contato.exibirContato();

    // Alterando o segundo telefone
    contato.setFone2b("97777-3333");

    // Exibindo informações do contato após a alteração
    std::cout << "\nInformações do contato após a alteração:" << std::endl;
    contato.exibirContato();

    return 0;
}