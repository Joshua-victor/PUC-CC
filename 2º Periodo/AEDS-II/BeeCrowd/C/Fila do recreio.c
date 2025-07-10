#include <stdio.h>
#include <stdlib.h>


typedef struct Celula {

	int nota;
	struct Celula* prox;

} Celula;


Celula* novaCelula(int nota) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));
	nova -> nota = nota;
	nova -> prox = NULL;
	return nova;

}

Celula* primeiro;
Celula* ultimo;


void start() {

	primeiro = novaCelula(-1);
	ultimo = primeiro;


}


void inserirFim(int x) {

	ultimo->prox = novaCelula(x);
	ultimo = ultimo->prox;



}

void mostrar(){
    
    
    for(Celula* i = primeiro->prox; i != NULL; i = i-> prox){
        
        printf("%d " , i->nota);
        
    }
    
    
}


void mudanças(int alunos){
    
    int quant = alunos;
    for(Celula* i = primeiro->prox; i != NULL; i = i->prox){
        
        
         for(Celula* j = i->prox; j != NULL; j = j->prox){
        
        
            if(i->nota < j->nota){
                
                quant -= 2;
                
            }
     
        
    }
        
       
        
        
    }
    
    printf("%d", quant);
    
    
    
    
}


int main()
{


	start();

	int quantidade = 0;
	scanf("%d", &quantidade);

    for(int i = 0; i < quantidade; i++){


	int quantidadeAlunos;
	scanf("%d", &quantidadeAlunos);
	int nota;

	for(int i = 0; i < quantidadeAlunos; i++) {

		scanf("%d", &nota);
		inserirFim(nota);


	}
	
	
	mudanças(quantidadeAlunos);

   


}








	return 0;
}