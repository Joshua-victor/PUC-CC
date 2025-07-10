#include <iostream>

int* intercalarArraysOrdenado(const int* arr1, int tamanho1, const int* arr2, int tamanho2) {
    int tamanhoTotal = tamanho1 + tamanho2;
    int* arrResultado = new int[tamanhoTotal];

    int indiceArr1 = 0;
    int indiceArr2 = 0;
    int indiceResultado = 0;

    while (indiceArr1 < tamanho1 && indiceArr2 < tamanho2) {
        if (arr1[indiceArr1] <= arr2[indiceArr2]) {
            arrResultado[indiceResultado++] = arr1[indiceArr1++];
        } else {
            arrResultado[indiceResultado++] = arr2[indiceArr2++];
        }
    }

    while (indiceArr1 < tamanho1) {
        arrResultado[indiceResultado++] = arr1[indiceArr1++];
    }

    while (indiceArr2 < tamanho2) {
        arrResultado[indiceResultado++] = arr2[indiceArr2++];
    }

    return arrResultado;
}

int main() {
    int arr1[] = {1, 3, 5};
    int tamanho1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {2, 4, 6, 8};
    int tamanho2 = sizeof(arr2) / sizeof(arr2[0]);

    int* arrResultado = intercalarArraysOrdenado(arr1, tamanho1, arr2, tamanho2);

    int tamanhoResultado = tamanho1 + tamanho2;

    std::cout << "Array resultante em ordem crescente: ";
    for (int i = 0; i < tamanhoResultado; i++) {
        std::cout << arrResultado[i] << " ";
    }
    std::cout << std::endl;

    delete[] arrResultado; // Libera a memória alocada pelo novo array

    return 0;
}
