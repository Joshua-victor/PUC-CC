
#include <stdio.h>
#include <string.h>
#include <math.h>


int main()
{
   float somatoriofat(int i, float a);
   int quantidade = 0;
   printf("Digite a quantidade de vezes que deseja executar o somatorio\n");
   scanf("%i", &quantidade);
   printf("O somatorio e %f\n", somatoriofat(quantidade, 3));
}

float somatoriofat(int i, float a)
{
   float fatorial (int x);
   float soma = 1.0;
   if (i==0)
   {
      soma=0;
   }
   if(i == 1)
   {
      soma = 1.0;
   
   }
   if(i == 2) 
   {
      soma = 0.5+somatoriofat(i-1, a+2);;
   
   }
   if(i > 2)
   {
      soma =  (a-1) /(fatorial(a)) +  somatoriofat(i-1, a+2);
   }
   
   return soma;
}