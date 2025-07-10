#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct Celula {

	int pacote;
	struct Celula* prox; 

} Celula;


Celula* novaCelula(int pacote) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));
	nova -> pacote = pacote;
    return nova;
}


Celula* primeiro;
Celula* ultimo;


void start() {

	primeiro = novaCelula(-1);
	ultimo = primeiro;

}



void inserirFim(int x) {

  Celula* nova = novaCelula(x);

    Celula* i = primeiro;
    while (i->prox != NULL && i->prox->pacote < x) {
        i = i->prox;
    }

    nova->prox = i->prox;
    i->prox = nova;

    if (nova->prox == NULL) {
        ultimo = nova;
    }
}


void mostrar(){
    
 for(Celula* i = primeiro->prox; i!= NULL; i = i ->prox){
     
     printf("Pacote 00%d\n", i->pacote);
     
     
 }   
    
}


int main()
{



	char pacote[50];
    start();

	fgets(pacote, sizeof(pacote), stdin);
	int numero;
	int quant = 0;
	if(pacote[0] == '1') {
		while(pacote[0] != '0') {
			

				fgets(pacote, sizeof(pacote), stdin);
				sscanf(pacote, "Pacote %d", &numero);
				pacote[strcspn(pacote, "\n")] = '\0';
				quant++;
				inserirFim(numero);


		}
	}
	
	
	mostrar();
	
	
	
	

	return 0;
}
