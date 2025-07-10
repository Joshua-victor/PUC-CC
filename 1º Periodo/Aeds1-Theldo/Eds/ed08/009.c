#include <stdio.h>
#include <stdbool.h>

// Função que busca um valor em um arranjo a partir de uma posição inicial
bool buscarValor(int valor, int inicio, int tamanho, int arranjo[]) {
    // Verifica se o início está dentro dos limites do arranjo
    if (inicio < 0 || inicio >= tamanho) {
        printf("Posição inicial inválida\n");
        return false;
    }

    // Percorre o arranjo a partir da posição indicada
    for (int i = inicio; i < tamanho; i++) {
        // Se encontrar o valor, retorna true
        if (arranjo[i] == valor) {
            printf("Valor encontrado na posição %d\n", i);
            return true;
        }
    }

    // Se não encontrou o valor, retorna false
    printf("Valor não encontrado\n");
    return false;
}

int main() {
    char nome_arquivo[50];
    int arranjo[100], tamanho_arranjo, valor_procurado, posicao_inicial;
    FILE *arquivo;

    // Lê o nome do arquivo
    printf("Digite o nome do arquivo que deseja ler: ");
    scanf("%s", nome_arquivo);

    // Abre o arquivo para leitura
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", nome_arquivo);
        return 1;
    }

    // Lê o tamanho do arranjo
    fscanf(arquivo, "%d", &tamanho_arranjo);

    // Lê os valores do arranjo
    for (int i = 0; i < tamanho_arranjo; i++) {
        fscanf(arquivo, "%d", &arranjo[i]);
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Lê o valor a ser procurado
    printf("Digite o valor a ser procurado: ");
    scanf("%d", &valor_procurado);

    // Lê a posição inicial para a busca
    printf("Digite a posição inicial para a busca: ");
    scanf("%d", &posicao_inicial);

    // Chama a função de busca
    buscarValor(valor_procurado, posicao_inicial, tamanho_arranjo, arranjo);

    return 0;
}
