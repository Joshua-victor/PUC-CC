#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char linha[201];  
    char palavra1[100], palavra2[100];

    while (true) {
        if (fgets(linha, sizeof(linha), stdin) == NULL || linha[0] == '\n') {
            break;
        }

      
        linha[strcspn(linha, "\n")] = '\0';

      
        if (sscanf(linha, "%s %s", palavra1, palavra2) != 2) {
            break;  
        }

        int tamanho1 = strlen(palavra1);
        int tamanho2 = strlen(palavra2);

        char combinatoria[tamanho1 + tamanho2 + 1];
        int k = 0;

        for (int i = 0; i < tamanho1 || i < tamanho2; i++) {
            if (i < tamanho1) {
                combinatoria[k++] = palavra1[i];
            }
            if (i < tamanho2) {
                combinatoria[k++] = palavra2[i];
            }
        }

        combinatoria[k] = '\0';
        printf("%s\n", combinatoria);
    }

    return 0;
}
