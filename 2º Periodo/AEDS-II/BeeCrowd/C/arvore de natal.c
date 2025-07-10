#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Celula {

	int tamanho;
	int expessura;
	int qntdGalhos;
	struct Celula* prox;



} Celula;



Celula* novaCelula(int tamanho, int expessura, int qntdGalhos) {


	Celula* nova = (Celula*) malloc(sizeof(Celula));

	nova->tamanho = tamanho;
	nova->expessura = expessura;
	nova->qntdGalhos = qntdGalhos;
	nova->prox = NULL;
	return nova;


}




Celula* primeiro;
Celula* ultimo;






void start() {


	primeiro =novaCelula(-1, -1, -1);
	ultimo = primeiro;


}


void inserirFim(int x, int y, int z) {

	ultimo->prox = novaCelula(x, y, z);
	ultimo = ultimo->prox;


}



void madeiraIdeal() {
 bool resp = false;

	for(Celula* i = primeiro->prox; i != NULL; i = i->prox) {


		if(i->tamanho >= 200 || i->tamanho > 299) {
			if(i->expessura >= 50) {
				if(i->qntdGalhos >= 150) {
					printf("sim\n");
					resp = true;
				}
			}
		}
		
        if(resp == false){
            printf("nao\n");
        }


	}





}










int main()
{


	start();

	int quantidade;
	int tamanho;
	int expessura;
	int qntdGalhos;


	scanf("%d", &quantidade);


	for(int i = 0; i < quantidade; i++) {


		scanf("%d %d %d", &tamanho, &expessura, &qntdGalhos);
		inserirFim(tamanho, expessura, qntdGalhos);


	}

	madeiraIdeal();

	return 0;
}
