#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int somadigito(int soma, char *palavra, int i, int tamanho) {

	if( i == tamanho) {
		return soma;
	}

	soma += palavra[i] - '0' ;
	somadigito(soma, palavra, i + 1, tamanho);

}


int main()
{

	bool isfim = true;
	do {
		char palavra[100];
		fgets(palavra, sizeof(palavra),stdin); // usa-se fgets para ler palavras com espaC'o
		palavra[strcspn(palavra, "\n")] = '\0'; // usa-se strcspn para trocar a primeira apariC'C#o de \n para \0
		int tamanho = strlen(palavra);
		int soma = 0;

		if(strcmp(palavra, "FIM") == 0) {
			break;
		}

		soma = somadigito(soma, palavra, 0, tamanho);
		
    printf("%d\n", soma);
    
	} while(1);

	return 0;
}