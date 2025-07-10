#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int n, i, termo;

    printf("Digite o numero de termos da sequencia de Fibonacci que deseja exibir: ");
    scanf("%d", &n);

    printf("Os termos pares da sequencia de Fibonacci com %d termos sao:\n", n);
    for (i = 0; i < n; i++) {
        termo = fibonacci(i);
        if (termo % 2 == 0) {
            printf("%d ", termo);
        }
    }
    printf("\n");

    return 0;
}


