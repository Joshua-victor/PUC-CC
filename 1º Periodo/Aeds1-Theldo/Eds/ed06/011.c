
#include <stdio.h>
#include <string.h>
#include <math.h>


int main()
{
   int somatorioxn (int x, int y);
   int quantidade = 0;
   int x = 0;
   printf("Digite a quantidade de vezes que deseja executar o somatorio \n");
   scanf("%i", &quantidade);
   printf("Digite o valor de x\n");
   scanf("%i", &x);
   printf("O somatorio e %i\n", somatorioxn (x, quantidade));
   
}

int somatorioxn (int x, int y)
{
   int soma = 1;
   if (y==0)
   {
      soma = 0;
   }
   if (y-1 > 0 )
   {
      soma = pow(x,y*2-3) + somatorioxn (x,y-1);
   }
   return soma;
}
