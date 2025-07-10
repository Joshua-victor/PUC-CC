#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void TrocaRecursiva(int tamanho, int j, int i,  char *palavra, char *invertida) {

	if(i == tamanho) {
		return;
	}

	invertida[i] = palavra[j]; 

	TrocaRecursiva(tamanho, j - 1, i + 1, palavra, invertida);
}

int main()
{

	bool isfim = true;
	do {
		char palavra[100];
		fgets(palavra, sizeof(palavra),stdin); // usa-se fgets para ler palavras com espaC'o
		palavra[strcspn(palavra, "\n")] = '\0'; // usa-se strcspn para trocar a primeira apariC'C#o de \n para \0

		if(strcmp(palavra, "FIM") == 0) {
			break;
		}

		int tamanho = strlen(palavra);
		char invertida[100];
		int j = tamanho - 1;

		TrocaRecursiva(tamanho, j, 0,  palavra, invertida);

		invertida[tamanho] = '\0';

		printf("%s\n", invertida);
	} while(1);
	
	return 0;
}
