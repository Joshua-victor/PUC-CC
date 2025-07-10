#include <stdio.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

void somarMatrizes(int matriz1[][MAX_COLUNAS], int matriz2[][MAX_COLUNAS], int resultado[][MAX_COLUNAS], int linhas, int colunas, int constante) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = matriz1[i][j] + (matriz2[i][j] * constante);
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
    int linhas, colunas, constante;

    FILE *arquivoMatriz1 = fopen("matriz1.txt", "r");
    FILE *arquivoMatriz2 = fopen("matriz2.txt", "r");
    FILE *arquivoResultado = fopen("resultado.txt", "w");

    if (arquivoMatriz1 == NULL || arquivoMatriz2 == NULL || arquivoResultado == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    fscanf(arquivoMatriz1, "%d", &linhas);
    fscanf(arquivoMatriz1, "%d", &colunas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivoMatriz1, "%d", &matriz1[i][j]);
        }
    }

    fscanf(arquivoMatriz2, "%d", &linhas);
    fscanf(arquivoMatriz2, "%d", &colunas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivoMatriz2, "%d", &matriz2[i][j]);
        }
    }

    fscanf(arquivoMatriz2, "%d", &constante);

    somarMatrizes(matriz1, matriz2, resultado, linhas, colunas, constante);

    fprintf(arquivoResultado, "%d %d\n", linhas, colunas);
    imprimirMatriz(resultado, linhas, colunas, arquivoResultado);

    fclose(arquivoMatriz1);
    fclose(arquivoMatriz2);
    fclose(arquivoResultado);

    printf("Resultado gravado no arquivo 'resultado.txt'.\n");

    return 0;
}
