#include <stdio.h>
#include <stdlib.h>


int* lerArquivo4(const char* nomeArquivo, int* tamanho) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }


    fscanf(arquivo, "%d", tamanho);

 
    int* arranjo = (int*)malloc(*tamanho * sizeof(int));


    for (int i = 0; i < *tamanho; i++) {
        fscanf(arquivo, "%d", &arranjo[i]);
    }

    fclose(arquivo);
    return arranjo;
}


int* soma_arranjos(int* arranjo1, int tamanho1, int* arranjo2, int tamanho2) {
    if (tamanho1 != tamanho2) {
        printf("Erro: os arranjos têm tamanhos incompatíveis.\n");
        exit(1);
    }

    int* soma = (int*)malloc(tamanho1 * sizeof(int));

    for (int i = 0; i < tamanho1; i++) {
        soma[i] = arranjo1[i] + arranjo2[i];
    }

    return soma;
}
int main ()
{

    int tamanho1, tamanho2;
    int* arranjo1 = lerArquivo4("Dados1.txt", &tamanho1);
    int* arranjo2 = lerArquivo4("Dados2.txt", &tamanho2);

    int* soma = soma_arranjos(arranjo1, tamanho1, arranjo2, tamanho2);

    printf("Resultado da soma:\n");
    for (int i = 0; i < tamanho1; i++) {
        printf("%d ", soma[i]);
    }
    printf("\n");

    free(arranjo1);
    free(arranjo2);
    free(soma);
   
  }