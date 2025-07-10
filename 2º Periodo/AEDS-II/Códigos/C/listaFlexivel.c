#include <stdio.h>
#include <stdlib.h>

//classe da celula
typedef struct Celula{
    
    int elemento;
    struct Celula* prox;

}Celula;

Celula* NovaCelula(int elemento){
    
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova -> elemento = elemento; // em java this.elemento = elemento;
    nova -> prox = NULL; // em java prox = null;
    return nova;   
}

//criando os pornteiros da lista
Celula* primeiro;
Celula* ultimo;



void start(){
    
   primeiro = NovaCelula(-1);
   ultimo = primeiro;
 
}


void inserirFim(int x){
    
    ultimo->prox = NovaCelula(x);
    ultimo = ultimo->prox;
    
}


void inserirInicio(int x){
    
    Celula* tmp = NovaCelula(x);
    tmp->prox = primeiro->prox;
    primeiro->prox = tmp;
    
    if(primeiro == ultimo){
        ultimo = tmp;
    }
    tmp = NULL;
}


void removerInicio(){
    
    if(primeiro == ultimo){
        printf("erro ao remover!");
        return;
    }
    
    Celula* tmp = primeiro;
    primeiro = primeiro->prox;
    tmp->prox = NULL;
    free(tmp); // sempre quando inultilizar um ponteiro é preciso dar um free para liberar a alocação de memoria
    tmp = NULL;
    
}


void removerFim(){
    
      if(primeiro == ultimo){
        printf("erro ao remover!");
        return;
      }
    
    Celula* i;
    for( i = primeiro; i->prox != ultimo; i = i->prox);
    
    ultimo = i;
    free(ultimo->prox);
    i = ultimo->prox = NULL;
 
}

void mostrar(){
    
    printf("[");
    for(Celula* j = primeiro->prox; j != NULL; j = j->prox){
        
        printf("%d ", j->elemento);
    }
    printf("]");
    
}

int main()
{
    start(); //dar inicio a lista;
    
    inserirInicio(75);
    inserirInicio(83);
    inserirInicio(12);
    inserirInicio(54);
    inserirInicio(56);
    mostrar();
    
    
    
    


    return 0;
}
