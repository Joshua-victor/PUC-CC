#include <stdio.h>

int main()
{
    printf("impares e pares\n ");
    
    int numero;
    int par = 0;
     int impar = 0;
    
    for (int x = 0 ; x < 10 ; x++  ){
        
        printf("digite um numero:");
        scanf("%i" , &numero);
        
        if (numero % 2 == 0 ) par++;
         else impar ++;
        
        
        
    }
    
    printf ("temos %i numeros impares\n" , impar);
    printf ("temos %i numeros pares\n", par);
    
    
    

    return 0;
}