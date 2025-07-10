#include <stdio.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

void obterTransposta(int matriz[][MAX_COLUNAS], int linhas, int colunas, int transposta[][MAX_LINHAS]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            transposta[j][i] = matriz[i][j];
        }
    }
}

void imprimirMatriz(int matriz[][MAX_COLUNAS], int linhas, int colunas, FILE *arquivo) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
}

int main() {
    int matriz[MAX_LINHAS][MAX_COLUNAS];
    int linhas, colunas;

    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &colunas);

    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    FILE *arquivo = fopen("transposta.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "Matriz original:\n");
    imprimirMatriz(matriz, linhas, colunas, arquivo);

    int transposta[MAX_COLUNAS][MAX_LINHAS];
    obterTransposta(matriz, linhas, colunas, transposta);

    fprintf(arquivo, "Matriz transposta:\n");
    imprimirMatriz(transposta, colunas, linhas, arquivo);

    fclose(arquivo);

    printf("Resposta gravada no arquivo 'transposta.txt'.\n");

    return 0;
}
