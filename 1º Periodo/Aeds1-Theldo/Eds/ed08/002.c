#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Função para verificar se um número é positivo e par
int verificar_numero(int num) {
    return (num > 0 && num % 2 == 0);
}

int main(int argc, char *argv[]) {
    int arr[MAX_SIZE], arr_filtrado[MAX_SIZE], tamanho = 0, tamanho_filtrado = 0;
    char *nome_arquivo = argv[1];

    FILE *arquivo = fopen("002.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(1);
    }

    // Ler os números do arquivo e armazenar no arranjo
    while (fscanf(arquivo, "%d", &arr[tamanho]) == 1 && tamanho < MAX_SIZE) {
        if (verificar_numero(arr[tamanho])) {
            tamanho_filtrado++;
            arr_filtrado[tamanho_filtrado-1] = arr[tamanho];
        }
        tamanho++;
    }

    fclose(arquivo);

    // Salvar o arranjo filtrado em um novo arquivo
    FILE *arquivo_filtrado = fopen("arr_filtrado.txt", "w");
    if (arquivo_filtrado == NULL) {
        printf("Erro ao criar o arquivo arr_filtrado.txt\n");
        exit(1);
    }

    // Escrever o tamanho do arranjo filtrado no arquivo
    fprintf(arquivo_filtrado, "%d\n", tamanho_filtrado);

    // Escrever os elementos do arranjo filtrado no arquivo, um por linha
    for (int i = 0; i < tamanho_filtrado; i++) {
        fprintf(arquivo_filtrado, "%d\n", arr_filtrado[i]);
    }

    fclose(arquivo_filtrado);

    return 0;
}
