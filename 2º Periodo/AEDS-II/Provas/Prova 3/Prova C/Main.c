#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Celula
{
    
    int nota;
    struct Celula* prox;



}Celula;


Celula* novaCelula(int nota){

Celula* nova = (Celula*) malloc(sizeof(Celula));
nova->nota = nota;
nova->prox = NULL;
return nova;

}

Celula* primiero;
Celula* ultimo;


void start(){

primiero = novaCelula(-1);
ultimo = primiero;



}

void inserirFim(int x){

ultimo->prox = novaCelula(x);
ultimo = ultimo->prox;


}


void mostrar(){

for(Celula* i = primiero->prox; i != NULL; i = i->prox){

printf("%d " , i->nota);

}


}


void somaNotas(int quant){


int soma = 0;
int aux = quant;
int maior = 0;
int delimitador = 0;



        
        for(Celula* i = primiero->prox; i != NULL; i = i->prox){

            if(i->nota > maior){
                maior = i->nota;
                
            }




        }
        soma += maior;
        delimitador = maior; // 10
        
     



for(int i = 0; i < quant -1 ; i++){
    maior = 0;
 for(Celula* i = primiero->prox; i != NULL; i = i->prox){
            
            if(i->nota > maior && i->nota < delimitador){
                maior = i->nota;
                
            }




        }
        
        soma += maior;
        delimitador = maior;
    

        

}

printf("%d\n" , soma);
soma = 0;

}

int main()
{
   

   for(int i = 0; i < 3; i++){
      int quantNotas = 0;
   int Maiornota = 0;
   int nota = 0;
   start();

    scanf("%d %d" , &quantNotas, &Maiornota);

   for(int i = 0; i < quantNotas; i++){

        scanf("%d" , &nota);
        inserirFim(nota);
   } 

    
    somaNotas(Maiornota);




   }

   


    return 0;
}
