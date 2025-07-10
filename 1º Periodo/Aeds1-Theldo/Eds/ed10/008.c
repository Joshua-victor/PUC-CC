#include <stdio.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100



void imprimirMatriz(int matriz[][MAX_COLUNAS], int linhas, int colunas, FILE *arquivo, int matriz1[][MAX_COLUNAS], int linhas1, int colunas1) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        
        fprintf(arquivo, "\n");
        
        
        for (int a = 0; a < linhas1; a++) {
        for (int b = 0; b < colunas1; b++) {
            fprintf(arquivo, "%d ", matriz1[a][b]);
        }
        
        fprintf(arquivo, "\n");
    }
        
}
}

int main() {
    int matriz[MAX_LINHAS][MAX_COLUNAS];
    int matriz1[MAX_LINHAS][MAX_COLUNAS];
    int linhas, colunas, linhas1, colunas1;
  

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
    
    
    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &linhas1);

    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &colunas1);

    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas1; j++) {
            scanf("%d", &matriz1[i][j]);
            
        }
    }


    FILE *arquivo = fopen("0 na matirz.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "Matriz :\n");
    imprimirMatriz(matriz, linhas, colunas, arquivo, matriz1, colunas1, linhas1);
   
  
    fclose(arquivo);

    printf("Resposta gravada no arquivo 'transposta.txt'.\n");

   
}


