#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALAVRAS 100 // tamanho máximo do array de palavras
#define TAMANHO_MAXIMO_PALAVRA 50 // tamanho máximo de cada palavra

// Função que verifica se uma palavra não começa ou termina com 'c' ou 'C'
int verificar_palavra(char *palavra) {
    int tamanho = strlen(palavra);
    if (tamanho == 0) return 0;
    if (palavra[0] == 'c' || palavra[0] == 'C') return 0;
    if (palavra[tamanho-1] == 'c' || palavra[tamanho-1] == 'C') return 0;
    return 1;
}

// Função que lê as palavras do arquivo e retorna as primeiras dez palavras que não começam ou terminam com 'c' ou 'C'
char** buscar_palavras() {
    char **palavras_validas = (char**) malloc(10 * sizeof(char*));
    FILE *arquivo;
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    int cont_palavras_validas = 0;

    arquivo = fopen("txt.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo PALAVRAS.TXT\n");
        exit(1);
    }

    // Ler as palavras do arquivo e buscar as primeiras dez palavras que não começam ou terminam com 'c' ou 'C'
    while (fgets(palavra, TAMANHO_MAXIMO_PALAVRA, arquivo) != NULL && cont_palavras_validas < 10) {
        palavra[strcspn(palavra, "\n")] = '\0'; // remover o caractere de nova linha da palavra
        if (verificar_palavra(palavra)) {
            palavras_validas[cont_palavras_validas] = (char*) malloc((strlen(palavra)+1) * sizeof(char));
            strcpy(palavras_validas[cont_palavras_validas], palavra);
            cont_palavras_validas++;
        }
    }

    fclose(arquivo);

    return palavras_validas;
}

int main() {
    char **palavras_validas = buscar_palavras();

    // Exibir as palavras válidas na tela
    printf("As primeiras dez palavras que nao comecam ou terminam com 'c' ou 'C' sao:\n");
    for (int i = 0; i < 10 && palavras_validas[i] != NULL; i++) {
        printf("%s\n", palavras_validas[i]);
    }

    // Liberar a memória alocada para as palavras válidas
    for (int i = 0; i < 10 && palavras_validas[i] != NULL; i++) {
        free(palavras_validas[i]);
    }
    free(palavras_validas);

    return 0;
}
