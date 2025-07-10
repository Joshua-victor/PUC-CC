#include <iostream>
#include <string>

class Contato {
private:
    std::string nome;
    std::string telefone1;
    std::string telefone2;

public:
    // Construtor
    Contato(const std::string& nome, const std::string& telefone1, const std::string& telefone2)
        : nome(nome), telefone1(telefone1), telefone2(telefone2) {}

    // Método para remover o segundo telefone
    void removeSegundoTelefone() {
        if (telefone2.empty()) {
            std::cerr << "Erro: O contato não possui um segundo telefone." << std::endl;
        } else {
            telefone2 = "";
        }
    }

    // Método para exibir os dados do contato
    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Telefone 1: " << telefone1 << std::endl;
        std::cout << "Telefone 2: " << telefone2 << std::endl;
    }
};

int main() {
    Contato contato("Exemplo0240", "123456789", "987654321");
    contato.exibirContato();

    contato.removeSegundoTelefone();
    contato.exibirContato();

    return 0;
}
