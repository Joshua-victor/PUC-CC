#include <stdio.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

void multiplicarMatrizes(int matriz1[][MAX_COLUNAS], int matriz2[][MAX_COLUNAS], int resultado[][MAX_COLUNAS], int linhas1, int colunas1, int colunas2) {
    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas2; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < colunas1; k++) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
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
    int matriz1[MAX_LINHAS][MAX_COLUNAS];
    int matriz2[MAX_LINHAS][MAX_COLUNAS];
    int resultado[MAX_LINHAS][MAX_COLUNAS];
    int linhas1, colunas1, linhas2, colunas2;

    FILE *arquivo = fopen("matrizes.txt", "r");
    FILE *arquivoResultado = fopen("resultado.txt", "w");

    if (arquivo == NULL || arquivoResultado == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    fscanf(arquivo, "%d", &linhas1);
    fscanf(arquivo, "%d", &colunas1);

    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas1; j++) {
            fscanf(arquivo, "%d", &matriz1[i][j]);
        }
    }

    fscanf(arquivo, "%d", &linhas2);
    fscanf(arquivo, "%d", &colunas2);

    for (int i = 0; i < linhas2; i++) {
        for (int j = 0; j < colunas2; j++) {
            fscanf(arquivo, "%d", &matriz2[i][j]);
        }
    }

    if (colunas1 != linhas2) {
        printf("As dimensões das matrizes não são compatíveis para multiplicação.\n");
        return 1;
    }

    multiplicarMatrizes(matriz1, matriz2, resultado, linhas1, colunas1, colunas2);

    fprintf(arquivoResultado, "%d %d\n", linhas1, colunas2);
    imprimirMatriz(resultado, linhas1, colunas2, arquivoResultado);

    fclose(arquivo);
    fclose(arquivoResultado);

    printf("Resultado gravado no arquivo 'resultado.txt'.\n");

    return 0;
}
