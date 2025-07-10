#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int leMes();
int main()
{

 leMes;

printf("o mes escolhido tem %i dias" , leMes());


}


int leMes()
{
    int meses[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int m;
    int mes = 0 ;
    bool erro;

    do{
    printf ("mes [1...12]");
    scanf("%i" , &m);
    erro  = m < 1 || m > 12;
    if (erro) puts ("mes invalido");
    }while(erro);


     mes = meses[m];

    return mes;


}