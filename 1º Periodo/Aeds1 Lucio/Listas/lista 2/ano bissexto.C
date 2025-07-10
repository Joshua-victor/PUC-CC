#include <stdio.h>

int main()
{
    printf("ano bisexto\n");
    
    int ano;

    
    
    
    
    printf("digite o ano:");
    scanf("%i", &ano);
    
    
    if (((ano% 4==0) && (ano% 100!=0)) || (ano% 400==0)){

       puts( " e um ano bissexto");
    }
     
     else puts("nao e bissexto");
    