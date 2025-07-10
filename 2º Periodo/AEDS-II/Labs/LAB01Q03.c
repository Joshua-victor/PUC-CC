#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int main() 
{
	bool isfim = false;
	
	do {
		char palavra[100];
		fgets(palavra, sizeof(palavra), stdin); // usa-se fgets para ler palavras com espaço
		palavra[strcspn(palavra, "\n")] = '\0';

		if(strcmp(palavra,"FIM")==0) {
			isfim = true;
			break;
		}
		int tamanho = strlen(palavra);

		int maiuscula = 0;

		for(int i = 0; i < tamanho ; i++) {

			if(palavra[i] >= 'A' && palavra[i] <= 'Z') {
				maiuscula++;
			}

		}

		printf("%d\n" , maiuscula);



	} while(isfim != true);


}

