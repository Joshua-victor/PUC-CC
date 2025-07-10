#include <string.h>
#include <stdbool.h>
#include <stdio.h>

 int recursivo(int tamanho, char vet[]){
     
     int maiuscula = 0;

        if (tamanho >= 0) { // Evita acessar índice inválido
            if (vet[tamanho] >= 'A' && vet[tamanho] <= 'Z') {
                maiuscula++;
            }
            maiuscula += recursivo(tamanho - 1, vet); // Soma ao resultado da recursão
        }

        return maiuscula;
    }
     


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

		int maiuscula = recursivo(tamanho, palavra);

	

		printf("%d\n" , maiuscula);



	} while(isfim != true);


}

