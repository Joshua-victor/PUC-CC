#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int matriz1[MAX_SIZE][MAX_SIZE];
    int matriz2[MAX_SIZE][MAX_SIZE];
    int resultado[MAX_SIZE][MAX_SIZE];
    int linhas1, colunas1, linhas2, colunas2;

    FILE *arquivo1 = fopen("matriz1.txt", "r");
    FILE *arquivo2 = fopen("matriz2.txt", "r");

    if (arquivo1 == NULL || arquivo2 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivo1, "%d", &linhas1);
    fscanf(arquivo1, "%d", &colunas1);

    fscanf(arquivo2, "%d", &linhas2);
    fscanf(arquivo2, "%d", &colunas2);

    if (colunas1 != linhas2) {
        printf("As dimensões das matrizes não são compatíveis para multiplicação.\n");
        return 1;
    }

    // Lê a matriz 1 do arquivo
    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas1; j++) {
            fscanf(arquivo1, "%d", &matriz1[i][j]);
        }
    }

    // Lê a matriz 2 do arquivo
    for (int i = 0; i < linhas2; i++) {
        for (int j = 0; j < colunas2; j++) {
            fscanf(arquivo2, "%d", &matriz2[i][j]);
        }
    }

    // Calcula o produto das matrizes
    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas2; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < colunas1; k++) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    // Verifica se o resultado é a matriz identidade
    int matrizIdentidade = 1;
    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas2; j++) {
            if ((i == j && resultado[i][j] != 1) || (i != j && resultado[i][j] != 0)) {
                matrizIdentidade = 0;
                break;
            }
        }
        if (!matrizIdentidade) {
            break;
        }
    }

    if (matrizIdentidade) {
        printf("O produto das matrizes é igual à matriz identidade.\n");
    } else {
        printf("O produto das matrizes não é igual à matriz identidade.\n");
    }

    fclose(arquivo1);
    fclose(arquivo2);

    return 0;
}
