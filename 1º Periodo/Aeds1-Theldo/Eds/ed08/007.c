#include <stdbool.h>
#include <stdio.h>

bool estaOrdenadoDecrescente(int arranjo[], int tamanho) {
    bool ordenado = true;
    for (int i = 0; i < tamanho - 1; i++) {
        if (arranjo[i] < arranjo[i+1]) {
            ordenado = false;
            break;
        }
    }
    return ordenado;
}

int main() {
    int arranjo[] = {10,11, 12, 13, 14};
    int tamanho = sizeof(arranjo)/sizeof(arranjo[0]);
    if (estaOrdenadoDecrescente(arranjo, tamanho)) {
        printf("O arranjo esta ordenado em ordem decrescente.\n");
    } else {
        printf("O arranjo nao esta ordenado em ordem decrescente.\n");
    }
    return 0;
}
