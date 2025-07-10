#include <iostream>
#include <sstream>

int* separarValores(const std::string& sequencia, int& tamanho) {
    std::istringstream iss(sequencia);

    int valor;
    int capacidade = 10;  
    int* arr = new int[capacidade];

    tamanho = 0;
    while (iss >> valor) {
  
        if (tamanho == capacidade) {
          
            capacidade *= 2;
            int* novoArr = new int[capacidade];

         
            for (int i = 0; i < tamanho; i++) {
                novoArr[i] = arr[i];
            }

            delete[] arr;  
            arr = novoArr; 
        }

        arr[tamanho] = valor;
        tamanho++;
    }

    return arr;
}

int main() {
    std::string sequencia;

    std::cout << "Digite a sequência de valores separados por espaço: ";
    std::getline(std::cin, sequencia);

    int tamanho;
    int* arrResultado = separarValores(sequencia, tamanho);

    std::cout << "Array resultante: ";
    for (int i = 0; i < tamanho; i++) {
        std::cout << arrResultado[i] << " ";
    }
    std::cout << std::endl;

    delete[] arrResultado; 

    return 0;
}
