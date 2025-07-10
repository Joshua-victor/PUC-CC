#include <stdio.h>

int main()
{
    int anterior = 0;
    int t = 1;
    int auxiliar;
    int escolha;
    
    printf("escolha quantos valores voce quer:");
    scanf("%i" , &escolha);
    
   
    
    for( int i  = 1; i <= escolha; i++){
        
        auxiliar = t;
        t = t + anterior;
        anterior = auxiliar ;
        printf("%i," , t);
        
    }
    
    
    
    