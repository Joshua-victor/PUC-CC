#include <stdio.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100



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
    int count = 0;

    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &colunas);

    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);
            if (matriz[i][j] == 0){
                count++;
            }
        }
    }

    FILE *arquivo = fopen("0 na matirz.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "Matriz :\n");
    imprimirMatriz(matriz, linhas, colunas, arquivo);
    fprintf(arquivo, "existem %d zeros na matriz", count);
  

    
    fclose(arquivo);

    printf("Resposta gravada no arquivo 'transposta.txt'.\n");

    return 0;
}
