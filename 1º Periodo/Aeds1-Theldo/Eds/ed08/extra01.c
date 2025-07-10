#include <stdio.h>

#define MAX_DIVISORES 100 // tamanho máximo do array de divisores

// Função que calcula os divisores de um número e guarda em um array
int calcular_divisores(int n, int divisores[]) {
    int i, cont = 0;
    for (i = 1; i <= n; i++) {
        if (n % i == 0) { // Verificar se i é um divisor de n
            divisores[cont] = i; // Adicionar i ao array de divisores
            cont++; // Incrementar o contador de divisores
        }
    }
    return cont;
}

int main() {
    int n, i, cont_divisores;
    int divisores[MAX_DIVISORES];

    // Ler o valor de n do teclado
    printf("Digite um valor inteiro: ");
    scanf("%d", &n);

    // Calcular os divisores de n e guardar em um array
    cont_divisores = calcular_divisores(n, divisores);

    // Mostrar os divisores na tela
    printf("Os divisores de %d sao: ", n);
    for (i = 0; i < cont_divisores; i++) {
        printf("%d ", divisores[i]);
    }
    printf("\n");

    // Gravar os divisores em um arquivo
    FILE *arquivo;
    arquivo = fopen("DIVISORES.TXT", "w");
    fprintf(arquivo, "Os divisores de %d sao: ", n);
    for (i = 0; i < cont_divisores; i++) {
        fprintf(arquivo, "%d ", divisores[i]);
    }
    fclose(arquivo);

    return 0;
}
