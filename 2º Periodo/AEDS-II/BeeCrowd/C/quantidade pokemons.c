#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Celula {
    
    char pokemon[15];
    struct Celula* prox;
   
}Celula;


Celula* novacelula(char pokemon[]){
    
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    
    strcpy(nova->pokemon, pokemon);
    nova -> prox = NULL;
    return nova;
    
    
}


Celula* primeiro;
Celula* ultimo;


void start(){
    
  primeiro = novacelula(" ");
  ultimo = primeiro;
    
    
}


void inserirFim(char x[] ){
    bool repetido = false;
    
    for(Celula* i  = primeiro-> prox; i != NULL; i = i -> prox){
        
        if(strcmp(x, i->pokemon) == 0){
        repetido = true;
        }
    }
  
  
  if(repetido != true){
    ultimo->prox = novacelula(x);
    ultimo = ultimo->prox;

    
  }
    
}

void mostrar(){
    
  int quant = 0;
   for(Celula* i = primeiro->prox; i != NULL; i = i-> prox){
       
       
       
     quant++;
       
   } 
    
    int pokemons = 151;
    pokemons -= quant;
    printf("Falta(m) %d pokemon(s)", pokemons);
    
}


int main()
{
    
    
    start();
    
    int quantidade;
    scanf("%d" , &quantidade);
    
    char pokemon[15];

    
    for(int i = 0; i < quantidade; i++){
        
       scanf("%s" , pokemon); 
        inserirFim(pokemon);
        
    }
    
    
    mostrar();


    return 0;
}