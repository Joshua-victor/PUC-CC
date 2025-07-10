#include <stdio.h>

int acharQuantos(int valor, int posicaoInicial, int tamanho, int arranjo[]) {
    int contador = 0;
    for (int i = posicaoInicial; i < tamanho; i++) {
        if (arranjo[i] == valor) {
            contador++;
        }
    }
    return contador;
}

int main() {
    int arranjo[100];
    int tamanho = 0;
    char nomeArquivo[50];
    printf("Digite o nome do arquivo que deseja abrir: ");
    scanf("%s", nomeArquivo);
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    fscanf(arquivo, "%d", &tamanho);
    for (int i = 0; i < tamanho; i++) {
        fscanf(arquivo, "%d", &arranjo[i]);
    }
    fclose(arquivo);
    int valorProcurado = 0;
    int posicaoInicial = 0;
    printf("Digite o valor que deseja procurar: ");
    scanf("%d", &valorProcurado);
    printf("Digite a posicao inicial para iniciar a busca: ");
    scanf("%d", &posicaoInicial);
    int vezes = acharQuantos(valorProcurado, posicaoInicial, tamanho, arranjo);
    if (vezes > 0) {
        printf("O valor %d aparece %d vezes a partir da posicao %d.\n", valorProcurado, vezes, posicaoInicial);
    } else {
        printf("O valor %d nao foi encontrado no arranjo a partir da posicao %d.\n", valorProcurado, posicaoInicial);
    }
    return 0;
}
