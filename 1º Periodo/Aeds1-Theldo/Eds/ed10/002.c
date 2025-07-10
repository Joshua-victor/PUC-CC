#include <stdio.h>
#include <stdbool.h>

void lerArquivo(FILE *arquivo, char digito) {
    char caractere;
    int encontrou = 0;

    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere == digito) {
            encontrou = 1;
            break;
        }
    }

    if (encontrou) {
        printf("O dígito %c foi encontrado no arquivo.\n", digito);
    } else {
        printf("O dígito %c não foi encontrado no arquivo.\n", digito);
    }
}

int main() {
    int quantidade;

    printf("Digite a quantidade que deseja gravar: ");
    scanf("%d", &quantidade);
    int arranjo[quantidade];

    for (int i = 0; i < quantidade; i++) {
        printf("Digite o %dº termo: ", i + 1);
        scanf("%d", &arranjo[i]);
    }

    FILE *arquivo;
    arquivo = fopen("Dados.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "Números do arranjo:\n");
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n", arranjo[i]);
    }

    fclose(arquivo);
    printf("Resposta gravada no arquivo 'Dados.txt'.\n");

    char digito;
    printf("Digite o dígito a ser procurado: ");
    scanf(" %c", &digito);

    arquivo = fopen("Dados.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    lerArquivo(arquivo, digito);

    fclose(arquivo);

    return 0;
}
