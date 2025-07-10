#include <stdio.h>

int main() {
    int n;
    do {
        printf("Digite o tamanho do arranjo (deve ser positivo e par): ");
        scanf("%d", &n);
    } while (n <= 0 || n % 2 != 0);

    int arr[n];

    for (int i = 0; i < n; i++) {
        do {
            printf("Digite o elemento %d do arranjo (deve ser positivo e par): ", i+1);
            scanf("%d", &arr[i]);
        } while (arr[i] <= 0 || arr[i] % 2 != 0);
        
    }

    
}
