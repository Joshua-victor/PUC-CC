#include <stdio.h>


int main()
{
int fatorial, numero;
printf("Insira um valor para o qual deseja calcular seu fatorial: ");
scanf("%i", &numero);

for(fatorial = 1; numero > 1; numero = numero - 1)
fatorial = fatorial * numero;

printf("\nFatorial calculado: %d", fatorial);
return 0;
}