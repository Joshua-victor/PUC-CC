#include <stdio.h>
#include <stdlib.h>

int maior(int x[], int y);
int arranjomaior(FILE *pont_arq, int arranjo[]);

int main()
{
    char palavra[20];
    FILE *pont_arq;

    pont_arq = fopen("arquivo_palavra.txt", "w");
    if (pont_arq == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

    printf("Escreva uma palavra para testar gravacao de arquivo: ");
    scanf("%s", palavra);
    fprintf(pont_arq, "%s", palavra);
    fclose(pont_arq);

    printf("Dados gravados com sucesso!\n");

    int arranjo[10];
    int nmaior = arranjomaior(pont_arq, arranjo);
    printf("Maior = %d\n", nmaior);

    return 0;
}

int arranjomaior(FILE *pont_arq, int arranjo[])
{
    int i = 0;
    int aux = 0;
    FILE *arquivo = fopen("arquivo_palavra.txt", "rt");

    if (arquivo == NULL)
    {
        printf("O arquivo nao existe\n");
        return -1;
    }

    while (fscanf(arquivo, "%d", &aux) != EOF)
    {
        arranjo[i] = aux;
        i++;
    }

    if (i > 10)
    {
        printf("Erro, o arquivo e maior que o esperado\n");
        return -1;
    }

    int nmaior = maior(arranjo, i);
    fclose(arquivo);

    return nmaior;
}

int maior(int x[], int y)
{
    int maior = x[0];
    for (int i = 1; i < y; i++)
    {
        if (x[i] > maior && x[i] % 2 == 0)
        {
            maior = x[i];
        }
    }
    return maior;
}
