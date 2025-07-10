#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void remover(int *n, int *vetor, int tamanho, int pos) {
    if (pos < 0 || pos >= *n) { // Corrigida a condição de validação
        printf("Erro: posição inválida!\n");
        return;
    }

    int removido = vetor[pos]; // Armazena o elemento removido
    (*n)--; // Corrige a decretação do tamanho da lista

    for (int i = pos; i < *n; i++) { // Desloca os elementos
        vetor[i] = vetor[i + 1];
    }

    printf("Removido: %d\n", removido); // Exibe o elemento removido
}



void removerFim(int *n) {
    if (*n == 0) { // Verifica se a lista está vazia
        printf("Erro: lista vazia\n");
        return;
    }
    --*n;
}

void removerInicio(int *n, int *vetor, int tamanho) {
    if (*n == 0) { // Verifica se a lista está vazia
        printf("Erro: lista vazia\n");
        return;
    }

    int removido = vetor[0];  // Armazena o elemento removido para exibição
    (*n)--;

    for (int i = 0; i < *n; i++) { // Desloca os elementos
        vetor[i] = vetor[i + 1];
    }

}


void inserirInicio(int x, int *n, int *vetor, int tamanho){
    
    
    if(*n >= tamanho){ // verifica se a lista não esta cheia
        printf("erro, sem espaço\n");
        return; 
    }
    
    for(int i= *n; i > 0; i--){ // desloca o elemento para deixar o inicio livre
        
        vetor[i] = vetor[i - 1];
        
    }
    
    vetor[0] = x; // adiciona o numero desejado na 1º pos
    (*n)++; //incrementa o n para a prox pos desocupada
    
}

void inserirFim(int x, int *n, int *vetor, int tamanho){
    
    
    if(*n >= tamanho){ // verifica se a lista não esta cheia
        printf("erro, sem espaço\n");
        return; 
    }
    
   
    vetor[*n] = x; // adiciona o numero desejado na 1º pos
    (*n)++; //incrementa o n para a prox pos desocupada
    
}

void inserir(int x, int *n, int *vetor, int tamanho, int pos){
    
    
    if(*n >= tamanho || pos < 0  || pos > *n){ // verifica se a lista não esta cheia, se a pos n é negativa e se a pos não e maior que a lista
        printf("erro, sem espaço ou posição invalida!\n");
        return; 
    }
    
      for(int i= *n; i > pos; i--){ // desloca o elemento para deixar o inicio livre
        
        vetor[i] = vetor[i - 1];
        
    }
    
    vetor[pos] = x; // adiciona o numero desejado na 1º pos
    (*n)++; //incrementa o n para a prox pos desocupada
    
}


int main()
{
    int vet[10]; // lista linear com espaço para 11 elementos (0,1,2,3,4,5,6,7,8,9,10)
    int n = 0; // contador, para saber onde tem espaço livre na lista
    while(1){
        
        printf("\nbem vindo aos exemplos de TAD, aqui temos algumas opções para treinar \ntemos as opções:\n a - inserir no inicio\n b - inserir no fim\n c - inserir em alguma posição\n d - remover no inicio\n e - remover no fim\n g - remover\n FIM - para sair do programa\n ");
        char palavra[5];
        fgets(palavra,sizeof(palavra), stdin);
        palavra[strcspn(palavra, "\n")] = '\0';
        int numero; // ultilizado para identificar o valor a ser inserido
		if (strcmp(palavra, "FIM") == 0) {  // caso a palavra for FIM, o programa para
			break;
		}
        
        switch (palavra[0]) {
        case 'a':
        
             numero = 0;
            scanf("%d", &numero);
            getchar();
            inserirInicio(numero, &n, vet, 10); /* n sendo passado como ponteiro pois se passar como valor
        a função cria uma copia para n que não é alterada aqui na Main*/
            break;
            
        case 'b':
             numero = 0;
            scanf("%d", &numero);
            getchar();
            inserirFim(numero, &n, vet, 10); /* n sendo passado como ponteiro pois se passar como valor
        a função cria uma copia para n que não é alterada aqui na Main*/
            break;
            
        case 'c':
            numero = 0;
            scanf("%d", &numero);
            int pos = scanf("%d" , &pos);
            getchar();
            inserir(numero, &n, vet, 10,  pos);
            break;
            
        case 'd':
            removerInicio(&n, vet, 10);
            break;
            
        case 'e':
             removerFim(&n);
            break;
        case 'f':
            printf("Sexta-feira\n");
            break;
        case 'g':
            pos = scanf("%d" , &pos);
            getchar();
            remover(&n, vet, 10,  pos);
            break;
        default:
            printf("inválido!\n");
    }
        
        

        for (int i = 0; i < n; i++) {
         printf("%d ", vet[i]);
        }
    
    }
    return 0;
}
