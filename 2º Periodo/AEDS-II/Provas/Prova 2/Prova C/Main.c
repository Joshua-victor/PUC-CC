#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
/* criação da Celula e da Fila*/
typedef struct Celula{

    int polen;
    struct Celula* prox;


}Celula;

Celula* novaCelula(int polen){

Celula* nova = (Celula*) malloc(sizeof(Celula));

nova->polen = polen;
nova->prox = NULL;
return nova;

}

typedef struct Fila{

    Celula* primeiro;
    Celula* ultimo;

}Fila;


void start(Fila* fila){

fila->primeiro = novaCelula(-1);
fila->ultimo = fila->primeiro;


}

void inserirUltimo(Fila* fila, int x){

Celula* tmp = novaCelula(x);

fila->ultimo->prox = tmp;
fila->ultimo = tmp;
tmp = NULL;

}

void mostrar(Fila* fila){

for(Celula* i = fila->primeiro->prox; i != NULL; i = i->prox){

    printf("%d", i->polen);
}


}

int quantidadePolen(Fila* fila, int abelha1, int abelha2, int posGertrude, int gertrude ){

//já na função quis deixar a enteder que se o polen da primeira for menor que abelha1 ou 2 ou gertrude ele passaria para a proxima
//e ate que chegue ne gertrude e tire a quantidade de polen dela
int polen;
int pos = 0;
Celula* tmp = fila->primeiro->prox;

for(Celula* i = fila->primeiro->prox; i != NULL; i = i->prox){

 i->polen = i->polen - abelha1;

if( i->polen < abelha2){ //Caso o polen tenha "acabado" iria pro proximo elemento

tmp = tmp->prox;
tmp->polen = tmp->polen - abelha2; 
gertrude = tmp->polen;

}

/*if(i->polen < gertrude){

i = i->prox;
i->polen -= gertrude;

}*/


return gertrude;



}

}




int main()
{
   /* passo a passo: tentei criar a quantidade de polen más não lembrei como inicializar o vetor e converter para string
    conseguir pegar cada digito, enão criei esse cenario de 5 flores */
Fila polen;
start(&polen);
int gertrude = 6;
int abelha1 = 4;
int abelha2 = 9;
int Qntdflores;
int posGertrude;
scanf("%d %d" , &Qntdflores, &posGertrude);
int flor1;
int flor2;
int flor3;
int flor4;
int flor5;





scanf("%d %d %d %d %d" , &flor1, &flor2, &flor3, &flor4, &flor5 );
inserirUltimo(&polen, flor1);
inserirUltimo(&polen, flor2);
inserirUltimo(&polen, flor3);
inserirUltimo(&polen, flor4);
inserirUltimo(&polen, flor5);

//aqui eu insiro elas em uma fila, lista sla o criterio que usei para inserção. 


int quantdidadepolenger = quantidadePolen( &polen, abelha1,  abelha2,  posGertrude,  gertrude );
//aqui não entendi muito bem como o algoritimo pegaria o valor de abelha 1 e abrelha 2, então tive que colocar para enteder e ja que não coloquei
// como vetor não conseguirua pegar a soma dos 2 elementos

printf("%d" , quantdidadepolenger);

    return 0;
}

//