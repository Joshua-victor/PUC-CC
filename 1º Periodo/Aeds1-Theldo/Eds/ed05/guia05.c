#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>




//1
int multiplo_par (int pos){
    
  return 6 * (pos * 2);
}

//2
int multiplo (int pos){
    
  return 6 * (pos * 1);
}

//3
int multiplo_nove (int pos){
    
  return 9 * (pos  * 1);
}





//5
void denominadoresSequencia(double x, int n) {
  int i = 0;
  while (i < n) {
    double denominador = pow(x, i);
    printf("1/%.0f ", denominador);
    i++;
  }
  printf("\n");
}


//6
int multiplos_pares_de_6(int n) {
    int i, count = 0, soma=0;
    for (i = 6; count < n; i += 6 ) {  
        if(i % 5!= 0){
        printf("%d ", i);
        soma+= i;
        count++;
    }
    }
    printf("\n");
    return soma;
}

//7
int multiplos_pares_de_seis(int n) {
    int i, count = 0, soma=0;
    for (i = 6; count < n; i += 6 ) {  
        if(i % 5!= 0){
        printf("1/%d ", i);
        soma+= i;
        count++;
    }
    }
    printf("\n");
    return soma;
}

//8
int contagem_multiplos(int n) {
    
    
    int i, count = 0, soma=0, inicial = 6, valor = 1;
     
    for (i = 6; count < n; i += 6 ) {  
        
        printf("%d ", inicial);
        inicial = inicial + valor;
        soma+= i;
        count++;
        valor++;
    
    }
    printf("\n");
    return valor;

}

//9
int contagem_potencia(int n) {
    
    
     int i=1, count = 0, soma=0, inicial = 0, valor = 6;
     
    while ( n>0 ) {  
         printf("(%d) - ", valor); 
        
        soma += valor*valor;
        printf("%d ",soma);
        valor=valor+i;
        i++;
        n--;
    }
    printf("\n");
    return soma;
}


//10
int contagem_multiplos_sobre1(int n) {
    
    
    int i, count = 0, soma=0, inicial = 6, valor = 1;
     
    for (i = 6; count < n; i += 6 ) {  
        
        printf("1/%d ", inicial);
        inicial = inicial + valor;
        soma+= i;
        count++;
        valor++;
    
    }
    printf("\n");
    return valor;

}

//11
int fatorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * fatorial(n - 1);
}

//12
double calculate_f(int n) {
    double f = 1.0;
    int i;
    for (i = 2; i <= n+1; i++) {
        f *= (double)(i+1)/(double)i;
        f += 1.0;
    }
    return f;
}





void metodo0 ();
void metodo1 ();
void metodo2 ();
void metodo3 ();
void metodo4 ();
void metodo5 ();
void metodo6 ();
void metodo7 ();
void metodo8 ();
void metodo9 ();
void metodo10 ();
void metodo11 ();
void metodo12 ();


int main()
{
   
   printf("\nAuthor: Joshua Victor\n");
   int x = 0;
 
   do
   {
      printf("0-Sair do programa\n");
      printf("1-mostrar essa quantidade em valores pares múltiplos de 6 em ordem crescente.\n");
      printf("2-mostrar essa quantidade em valores  múltiplos de 6 em ordem crescente.\n");
      printf("3-mostrar essa quantidade em valores  múltiplos de 9 em ordem decrescente.\n");
      printf("4-para ler uma quantidade inteira do teclado e, mediante um procedimento,mostrar essa quantidade em valores crescentes nos denominadores(sequência dos inversos) múltiplos de 6.\n");
      printf("5-mostrar essa quantidade em valores crescentes nos denominadores da sequência: 1 1/x 1/x2 1/x\n");
      printf("6-calcular a soma dos primeiros valores pares positivos começando no valor 6 e não múltiplos de 5.\n");
      printf("7-calcular a soma dos inversos (1/x) dos primeiros valores pares positivos, começando no valor 6 e não múltiplos de 5. \n");
      printf("8- calcular a adição dos primeiros números naturais começando no valor 6. \n");
      printf("9-calcular a soma dos quadrados dos primeiros números naturais começando no valor 6\n");
      printf("10-Testar essa função para quantidades diferentes de valores e mostrar os resultados em outro método\n");
      printf("11-mediante o uso da função, calcular e mostrar o fatorial desse valor em outro método:\n");
      printf("12-ler uma quantidade inteira do teclado (n) e, mediante o uso da função, calcular e mostrar o resultado em outro método de\n");
      printf("escolha qual programa deseja:");
      scanf("%i",&x);
      switch (x)
      {
         case 0:
            metodo0 ();
            break;
         case 1:
            metodo1 ();
            break;
         case 2:
            metodo2 ();
            break;
         case 3:
            metodo3 ();
            break;
         case 4:
            metodo4 ();
            break;
         case 5:
            metodo5 ();
            break;
         case 6:
            metodo6 ();
            break;
         case 7:
            metodo7 ();
            break;
         case 8:
            metodo8 ();
            break;
         case 9:
            metodo9 ();
            break;
         case 10:
            metodo10 ();
            break;
        case 11:
            metodo11 ();
            break;
         default:
            printf("Valor diferente dos propostos, tente outro\n");
            x=1;    
      }
   }while(x!=0);   
   printf("aperte ENTER para finalizar o programa");

   return (0);
}






void metodo0 ()
{
   
}


void metodo1 ()
{
   
    int quantidade;
   int resultado;
   
   printf("quantos multiplos quer calcular?");
   scanf("%d" , &quantidade);

   for(int i = 0; i < quantidade; i++) {
       resultado = multiplo_par(i);
       printf("%d " , resultado);
   }
}

   
   

void metodo2()
{
      int quantidade;
   int resultado;
   
   printf("quantos multiplos quer calcular?");
   scanf("%d" , &quantidade);

   for(int i = 0; i < quantidade; i++) {
       resultado = multiplo(i);
       printf("%d " , resultado);
   }
    
}

void metodo3()
{
      int quantidade;
   int resultado;
   
   printf("quantos multiplos quer calcular?");
   scanf("%d" , &quantidade);

   for(int i = quantidade; i >= 0; i--) {
     
       resultado = multiplo_nove(i);
       if(resultado % 2 == 1){
       printf("%d " , resultado);
   }
   }
    
}




void metodo4()
{
    
        int quantidade;
   int resultado;
   
   printf("quantos multiplos quer calcular?");
   scanf("%d" , &quantidade);

   for(int i = 1; i <= quantidade; i++) {
       resultado = multiplo(i);
       printf("1/%d\n " , resultado);
   }
    
    
    
}




void metodo5()
{
    
   
  double x;
  int quantidade;
  printf("Digite o valor de x: ");
  scanf("%lf", &x);
  printf("Digite a quantidade de termos desejada: ");
  scanf("%d", &quantidade);
  denominadoresSequencia(x, quantidade);
   
}

void metodo6()
{
    
  int num;
    printf("Digite a quantidade de termos: ");
    scanf("%d", &num);
    printf("Os %d primeiros multiplos pares de 6 sao: ", num);
    int soma =    multiplos_pares_de_6(num);
    printf("A soma das quantidades de termos (%d) e : %d", num, soma);
        
    }
    

    
    



void metodo7 ()
{
     int num;
    printf("Digite a quantidade de termos: ");
    scanf("%d", &num);
    printf("Os %d primeiros multiplos pares de 6 sao: ", num);
    int soma =    multiplos_pares_de_seis(num);
    printf("A soma das quantidades de termos (%d) e : %d", num, soma);
    
    
   
        
    


}



void metodo8()
{
    

     int num;
    printf("Digite a quantidade de termos: ");
    scanf("%d", &num);
    int valor =   contagem_multiplos(num);
    
        
    
}

void metodo9()
{
    
    
 int num;
    printf("Digite a quantidade de termos: ");
    scanf("%d", &num);
      printf("Os %d primeiros numeros naturais comecando de 6 mais a soma de cada um sao: ", num);
    int soma =   contagem_potencia(num);
     printf("A soma das quantidades de termos (%d) e : %d", num, soma);
    
    
    
}



void metodo10()
{
    
     int num;
    printf("Digite a quantidade de termos: ");
    scanf("%d", &num);
    printf("Os %d primeiros multiplos pares de 6 sao: ", num);
    int soma =    contagem_multiplos_sobre1(num);
    printf("A soma das quantidades de termos (%d) e : %d", num, soma);
    
    
 
}





void metodo11()
{
    
      int n;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n);
    printf("O fatorial de %d eh %d\n", n, fatorial(n));
    
    
    
    
}




void metodo12()
{
    
     int n;
    printf("Digite um número inteiro: ");
    scanf("%d", &n);
    double result = calculate_f(n);
    printf("O resultado de f(n) é: %.4f\n", result);
    
    

    
}