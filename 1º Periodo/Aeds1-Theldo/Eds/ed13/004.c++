#include <iostream>
#include <fstream>
#include <string>



class Exemplo1314 {
private:
    std::string nome;
    std::string telefone;

public:
    void fromFile(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            std::getline(arquivo, nome);
            std::getline(arquivo, telefone);
            arquivo.close();
            std::cout << "Dados lidos do arquivo com sucesso!" << std::endl;
        } else {
            std::cout << "Erro ao abrir o arquivo." << std::endl;
        }
    }

   

    void exibirContato() {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Telefone: " << telefone << std::endl;
    }

private:
    bool validarNumerosTelefone(const std::string& telefone) {
        for (char c : telefone) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Exemplo1314 contato1;
    contato1.fromFile("Pessoas1.txt");
    contato1.exibirContato();


    return 0;
}
