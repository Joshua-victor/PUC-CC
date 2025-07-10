#include <iostream>
#include <string>

class Exemplo1316 {
private:
    std::string nome;
    std::string telefone1;
    std::string telefone2;

public:
    Exemplo1316() {
        nome = "";
        telefone1 = "";
        telefone2 = "";
    }

    Exemplo1316(const std::string& nomeContato, const std::string& tel1, const std::string& tel2) {
        nome = nomeContato;
        telefone1 = tel1;
        telefone2 = tel2;
    }

    void setNome(const std::string& novoNome) {
        nome = novoNome;
    }

    void setTelefone1(const std::string& novoTelefone) {
        telefone1 = novoTelefone;
    }

    void setTelefone2(const std::string& novoTelefone) {
        telefone2 = novoTelefone;
    }

    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Telefone 1: " << telefone1 << std::endl;
        std::cout << "Telefone 2: " << telefone2 << std::endl;
    }
};

int main() {
    Exemplo1316 contato1;
    contato1.setNome("John Doe");
    contato1.setTelefone1("1234567890");
    contato1.setTelefone2("9876543210");
    contato1.exibirContato();

    Exemplo1316 contato2("Jane Smith", "1111111111", "2222222222");
    contato2.exibirContato();

    return 0;
}
