#include <stdio.h>
#include <stdlib.h>

double acharMedia(int arranjo[], int tamanho)
{
    int i;
    double soma = 0.0;
    for (i = 0; i < tamanho; i++)
    {
        soma += arranjo[i];
    }
    return soma / tamanho;
}

void separarValores(int arranjo[], int tamanho, char n[], double media)
{
    int i, aux;
    FILE *maiores, *menores;
    maiores = fopen("maiores.txt", "w");
    menores = fopen("menores.txt", "w");
    if (maiores == NULL || menores == NULL)
    {
        printf("Erro ao abrir os arquivos de saída.");
        exit(1);
    }
    for (i = 0; i < tamanho; i++)
    {
        aux = arranjo[i];
        if (aux >= media)
        {
            fprintf(maiores, "%d\n", aux);
        }
        else
        {
            fprintf(menores, "%d\n", aux);
        }
    }
    fclose(maiores);
    fclose(menores);
    printf("Os valores maiores ou iguais a media foram armazenados no arquivo maiores.txt.\n");
    printf("Os valores menores que a media foram armazenados no arquivo menores.txt.\n");
}

int main()
{
    char n[50];
    int tamanho = 0, i;
    int arranjo[100];
    double media;
    FILE *arquivo;
    printf("Digite o nome do arquivo que deseja testar:\n");
    scanf("%s", n);
    arquivo = fopen(n, "r");
    if (arquivo == NULL)
    {
        printf("O arquivo nao existe.\n");
        exit(1);
    }
    fscanf(arquivo, "%d", &tamanho);
    for (i = 0; i < tamanho; i++)
    {
        fscanf(arquivo, "%d", &arranjo[i]);
    }
    media = acharMedia(arranjo, tamanho);
    separarValores(arranjo, tamanho, n, media);
    fclose(arquivo);
    return 0;
}
