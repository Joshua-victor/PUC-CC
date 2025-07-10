#include <stdio.h>

#define MAX_SIZE 100

void ordenarArranjo(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: programa <nome_do_arquivo>\n");
        return 1;
    }

    char *nomeArquivo = argv[1];
    int arr[MAX_SIZE];
    int n = 0;

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê os elementos do arranjo do arquivo
    while (fscanf(arquivo, "%d", &arr[n]) != EOF) {
        n++;
    }

    fclose(arquivo);

    // Ordena o arranjo em ordem crescente
    ordenarArranjo(arr, n);

    // Imprime o arranjo ordenado
    printf("Arranjo ordenado em ordem crescente: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
