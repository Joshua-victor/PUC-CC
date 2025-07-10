#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main(){
int numero;
char decisao;
bool erro;
int maiorNumero = 0 ;
int menorNumero = 2;
int amplitude;

printf("amplitude\n");






do{
    
do{
printf("digite um numero");
scanf(" %i" , &numero);
erro = numero < 0;
if(erro) puts("numero invalido");
}while(erro);

printf("deseja cadastrar mais um numero?");
scanf(" %c" , &decisao);
decisao = toupper (decisao);
erro = decisao !='S' && decisao !='N';
if(erro) puts ("digito invalido");

}while(decisao !='N');

   if (numero > maiorNumero) {
            
            maiorNumero = numero;
            
        }
       

amplitude = maiorNumero - menorNumero;

if (amplitude != numero )  printf("amplitude invalida\n");
  else printf("amplitude e de %i numeros" , amplitude);






printf("maior numero %i\n" ,  maiorNumero);



return 0;}