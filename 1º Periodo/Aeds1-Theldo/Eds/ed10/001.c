#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void numerosAleatorios(int um, int dois) {
    int quantidade, i;
    
    printf("Digite a quantidade de valores que você quer gerar: ");
    scanf("%d", &quantidade);
    
    int arranjo[quantidade];  
    
    for (i = 0; i < quantidade; i++) {
        arranjo[i] = rand() % (dois - um + 1) + um;  
    }
    
    // Exibe os números armazenados no array
    printf("Números aleatórios gerados: ");
    for (i = 0; i < quantidade; i++) {
        printf("%d ", arranjo[i]);
    }
    printf("\n");
    
    
    FILE *arquivo;
    arquivo = fopen("Dados.txt", "w");  
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    }
    
    fprintf(arquivo, "Números aleatórios gerados: ");
    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "\n %d ", arranjo[i]);
    }
    
    fclose(arquivo);  // Fecha o arquivo
    printf("Resposta gravada no arquivo 'numeros.txt'.\n"); 
}

