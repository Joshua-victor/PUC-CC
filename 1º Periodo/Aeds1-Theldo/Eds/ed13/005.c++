#include <iostream>
#include <fstream>
#include <string>

class Exemplo1315 {
private:
    std::string nome;
    std::string telefone;

public:
    void toFile(const std::string& nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            arquivo << nome.size() << std::endl;  // Grava o tamanho do nome
            arquivo << nome << std::endl;         // Grava o nome
            arquivo << telefone << std::endl;     // Grava o telefone
            arquivo.close();
            std::cout << "Dados gravados no arquivo com sucesso!" << std::endl;
        } else {
            std::cout << "Erro ao abrir o arquivo." << std::endl;
        }
    }

    void setNome(const std::string& novoNome) {
        nome = novoNome;
    }

    void setTelefone(const std::string& novoTelefone) {
        telefone = novoTelefone;
    }

    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Telefone: " << telefone << std::endl;
    }
};

int main() {
    Exemplo1315 contato;
    contato.setNome("John Doe");
    contato.setTelefone("1234567890");
    contato.exibirContato();

    contato.toFile("Pessoa1.txt");

    return 0;
}
