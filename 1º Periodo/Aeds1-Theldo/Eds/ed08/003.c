#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calcular (int inicio , int fim , int n){
    
  int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int valor = (rand() % (fim - inicio + 1)) + inicio;
        arr[i] = valor;
    }

    FILE *arquivo = fopen("DADOS.TXT", "w");
    fprintf(arquivo, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", arr[i]);
    }
    fclose(arquivo);

    free(arr);

    printf("Valores aleatórios gerados com sucesso e salvos em \"DADOS.TXT\".\n");  
    
    
}

int main() {
    srand(time(NULL)); // seed para a função rand() com base no tempo atual

    int inicio, fim;
    printf("Informe o limite inferior do intervalo: ");
    scanf("%d", &inicio);
    printf("Informe o limite superior do intervalo: ");
    scanf("%d", &fim);

    int n;
    printf("Informe a quantidade de números a serem gerados: ");
    scanf("%d", &n);

    calcular(inicio , fim , n);

    
}

