#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{

	bool isfim = true; 
	do {
		bool resp = true;  // variavel para falar se é palindromo ou não
		char palavra[100];
		fgets(palavra, sizeof(palavra), stdin); // usa-se fgets para ler palavras com espaço
		palavra[strcspn(palavra, "\n")] = '\0';

		if (strcmp(palavra, "FIM") == 0) {  // caso a palavra for FIM, o programa para
			break;
		}


		char palindromo[100];
		int tamanho = strlen(palavra);


		int j = 0;
		for (int i = 0; palavra[i] != '\0'; i++) { // for para tirar os espaços da palavra
			if (palavra[i] != ' ') {
				palavra[j++] = palavra[i];
			}
		}
		palavra[j] = '\0'; // acrescentando um \0 no final da string


		strcpy(palindromo, palavra); // strcpy serve para fazer a copia de vetores
		tamanho = strlen(palavra);

		for (int i = 0; i < tamanho; i++) { // for para inverter a palavra PALINDROMO
			palindromo[i] = palavra[tamanho - 1 - i];
		}


		for(int i = 0; i < tamanho; i++) { // for para comparar se são iguais


			if (palavra[i] == palindromo[i]) {
				resp = true;
			} else {
				resp = false;
				i = tamanho;
			}
		}


		if(resp == true) {
			printf("SIM\n");
		} else {
			printf("NAO\n");
		}

	} while(1);

}
