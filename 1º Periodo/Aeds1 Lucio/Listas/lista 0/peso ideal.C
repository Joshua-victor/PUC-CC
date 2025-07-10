#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main()
{
    printf("peso ideal\n");
    
    char genero;
    bool erro;
    float peso;
    float altura;
    
    do{
    printf("digite seu sexo:");
    scanf ("%c", &genero);
    genero = toupper (genero);
    erro = genero != 'M' && genero != 'F';
    if (erro)puts("genero invalido!");
    }while(erro);
    
    do{
    printf("digite sua altura:");
    scanf ("%f", &altura);
    erro = altura < 0 ;
    if (erro)puts("altura invalida!");
    }while(erro);
    
    
    
    if (genero = 'M'){
        
        peso = 72.7 * altura - 58;
        
        
    }
    
    else peso = 62.1 * altura - 44,7;
    
    
    
    
    printf("seu peso ideal e : %f" , peso);
    
    
    