#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Celula {

	char nome[15];
	int poder;
	int qntMatou;
	int qntMortes;
	struct Celula* prox;

} Celula;


Celula* novaCelula(char nome[], int poder, int qntMatou, int qntMortes) {


	Celula* nova = (Celula*) malloc(sizeof(Celula));

	strcpy(nova->nome, nome);
	nova-> poder = poder;
	nova-> qntMortes = qntMortes;
	nova-> qntMatou = qntMatou;
	nova->prox = NULL;
	return nova;

}


Celula* primeiro;
Celula* ultimo;

void start() {


	primeiro = novaCelula(" ", -1, -1, -1);
	ultimo = primeiro;

}

void inserirFim(char nome[], int poder, int qntMatou, int qntMortes) {


	ultimo->prox = novaCelula(nome, poder, qntMatou, qntMortes);
	ultimo = ultimo->prox;

}


void mostrar() {


	for(Celula* i = primeiro->prox; i != NULL; i = i-> prox) {


		printf("%s %d %d %d\n", i->nome, i->poder, i->qntMatou, i->qntMortes);



	}


}


void godofor() {

	int maiorPoder = 0;
	int concorrenciaPoder = 0;
	Celula* melhor;

	for(Celula* i = primeiro->prox; i != NULL; i = i-> prox) {


		for(Celula* j = i->prox; j != NULL; j = j-> prox) {




			if(i->poder == j-> poder) {

				if(i->qntMatou > j->qntMatou) {
					melhor = i;
					break;

				} else if(i->qntMatou < j->qntMatou) {
					melhor = j;
					break;

				} else if(i->qntMatou == j->qntMatou) {

					if(i->qntMortes < j->qntMortes) {

						melhor = i;
						break;

					} else if(i->qntMortes > j->qntMortes) {

						melhor = j;
						break;

					}

				}


			}


		}


	}

	printf("%s\n", melhor->nome);
}



int main()
{

	start();


	int quantidade;
	scanf("%d", &quantidade);
	char nome[15];
	int poder;
	int qntMatou;
	int qntMortes;



	for(int i = 0; i < quantidade; i++) {


		scanf("%s %d %d %d", nome, &poder, &qntMatou, &qntMortes);

		inserirFim(nome, poder, qntMatou, qntMortes);


	}

	//mostrar();
	godofor();



	return 0;
}