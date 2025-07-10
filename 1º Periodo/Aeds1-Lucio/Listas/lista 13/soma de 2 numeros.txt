#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
int primeiroNumero();
int segundoNumero();
int calculo( int primeiroNumero , int segundoNumero );

int main()
{
    int um = primeiroNumero();
    int dois = segundoNumero();

    printf("a soma e : %i ",  calculo( um ,dois));
}

int primeiroNumero()
{
   int a;

   printf("digite o 1: ");
    scanf("%i" ,&a);

   return a;
}

 int segundoNumero ()
{
    int b ;
    printf("digite o 2:");
    scanf("%i" , &b);
    return b;
}



int calculo( int a , int b  )
{
   int resultado = 0;




       resultado =  a + b;




 return resultado;
}