#include <stdio.h>
#include <stdbool.h>

void lerArquivo(FILE *arquivo,int arranjo[], int quantidade) {
    
    bool Resposta;
    
     for (int i = 1; i < quantidade; i++) {
        if (arranjo[i] > arranjo[i - 1]) {
           Resposta = false;
        }
        else Resposta = true;
    }
   if(Resposta == true){
       printf("esta decrescente!");
   }
   else printf("nao esta decrescente!");
   
    
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

    

    arquivo = fopen("Dados.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    lerArquivo(arquivo, arranjo, quantidade);

    fclose(arquivo);

    return 0;
}
