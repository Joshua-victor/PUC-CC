#include <iostream>
#include <string>

class Contato {
private:
    std::string nome;
    int quantidadeTelefones;
    std::string telefones[10];

public:
    // Construtor
    Contato(const std::string& nome) : nome(nome), quantidadeTelefones(0) {}

    // Método para adicionar um telefone
    void adicionarTelefone(const std::string& telefone) {
        if (quantidadeTelefones >= 10) {
            std::cerr << "Erro: Limite máximo de telefones atingido." << std::endl;
        } else {
            telefones[quantidadeTelefones] = telefone;
            quantidadeTelefones++;
        }
    }

    // Método para remover um telefone
    void removerTelefone(int indice) {
        if (indice >= 0 && indice < quantidadeTelefones) {
            for (int i = indice; i < quantidadeTelefones - 1; i++) {
                telefones[i] = telefones[i + 1];
            }
            telefones[quantidadeTelefones - 1] = "";
            quantidadeTelefones--;
        } else {
            std::cerr << "Erro: Índice de telefone inválido." << std::endl;
        }
    }

    // Método para exibir os dados do contato
    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Quantidade de telefones: " << quantidadeTelefones << std::endl;
        for (int i = 0; i < quantidadeTelefones; i++) {
            std::cout << "Telefone " << i + 1 << ": " << telefones[i] << std::endl;
        }
    }
};

int main() {
    Contato contato("Exemplo0240");
    contato.adicionarTelefone("123456789");
    contato.adicionarTelefone("987654321");
    contato.exibirContato();

    contato.removerTelefone(1);
    contato.exibirContato();

    contato.adicionarTelefone("555555555");
    contato.adicionarTelefone("999999999");
    contato.adicionarTelefone("777777777");
    contato.exibirContato();

    contato.removerTelefone(0);
    contato.removerTelefone(2); // Índice inválido
    contato.exibirContato();

    return 0;
}
