#include <stdio.h>

int contaImpares(char *cadeia) {
    if (*cadeia == '\0') { // caso base: chegamos ao fim da cadeia
        return 0;
    }
    if (*cadeia % 2 == 1 && *cadeia >= '0' && *cadeia <= '9') { // se o símbolo é um dígito ímpar
        return 1 + contaImpares(cadeia + 1); // soma 1 e chama a função recursivamente para o resto da cadeia
    }
    return contaImpares(cadeia + 1); // chama a função recursivamente para o resto da cadeia
}

int main() {
    char cadeia[100];
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", cadeia);
    printf("A quantidade de digitos impares na cadeia e: %d\n", contaImpares(cadeia));
    return 0;
}
