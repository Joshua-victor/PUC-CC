#include <iostream>
#include <string>
#include <vector>

class Exemplo1316 {
private:
    std::string nome;
    std::vector<std::string> telefones;

public:
    Exemplo1316() {
        nome = "";
    }

    Exemplo1316(const std::string& nomeContato, const std::vector<std::string>& telefonesContato) {
        nome = nomeContato;
        telefones = telefonesContato;
    }

    void setNome(const std::string& novoNome) {
        nome = novoNome;
    }

    void adicionarTelefone(const std::string& novoTelefone) {
        telefones.push_back(novoTelefone);
    }

    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        for (const auto& telefone : telefones) {
            std::cout << "Telefone: " << telefone << std::endl;
        }
    }

    int getNumTelefones() {
        return telefones.size();
    }
};

int main() {
    Exemplo1316 contato1;
    contato1.setNome("John Doe");
    contato1.adicionarTelefone("1234567890");
    contato1.adicionarTelefone("9876543210");
    contato1.exibirContato();
    std::cout << "Número de telefones: " << contato1.getNumTelefones() << std::endl;

    Exemplo1316 contato2("Jane Smith", { "1111111111", "2222222222" });
    contato2.exibirContato();
    std::cout << "Número de telefones: " << contato2.getNumTelefones() << std::endl;

    Exemplo1316 contato3;
    contato3.setNome("Bob Johnson");
    contato3.adicionarTelefone("9999999999");
    contato3.adicionarTelefone("9876543210"); 
    contato3.adicionarTelefone("9876883210");
    contato3.exibirContato();
    std::cout << "Número de telefones: " << contato3.getNumTelefones() << std::endl;

    return 0;
}
