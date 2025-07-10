#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>




// metodo 2
int eh_letra_maiuscula(char c) {
    return c >= 'A' && c <= 'Z';
}

int eh_nenhuma(char c) {
    return  c =!'A' &&  c !='Z' || c !='a' && c !='z'||c != '0' && c !='9';
}

int eh_letra_maiuscula_e_minsucula(char c) {
    return  c < 'K' || c <'k';
}



int conta_letras_maiusculas(char *palavra) {
    int cont = 0; // contador de letras maiúsculas menores que 'K'

    // contagem das letras maiúsculas menores que 'K'
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (isupper(palavra[i]) && palavra[i] < 'K') {
            cont++;
        }
    }

    return cont;
}

int conta_letras_maiusculas_e_minuscula(char *palavra) {
    int cont = 0; // contador de letras maiúsculas menores que 'K'

    // contagem das letras maiúsculas menores que 'K'
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (islower(palavra[i]) || isupper(palavra[i]) && palavra[i] < 'K') {
            cont++;
        }
    }

    return cont;
}

//10
int eh_alfanumerico(char c) {
    return  c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9';
}


//11
int eh_alfanumerico_e_espaco_em_branco(char c) {
    return  c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == ' ';
}

//12
int contar_digitos(char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            count++;
        }
    }
    return count;
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


int main()
{
   
   printf("\nAuthor: Joshua Victor\n");
   int x = 0;
 
   do
   {
      printf("0-Sair do programa\n");
      printf("1-contar quantos desses valores estão dentro do intervalo, e quantos estão fora dele\n");
      printf("2-ler palavra do teclado e contar e mostrar letras maiusculas\n");
      printf("3-ler palavra do teclado e contar  letras maiusculas menores que K\n");
      printf("4-ler palavra do teclado e mostrar  letras maiusculas menores que K\n");
      printf("5-ler palavra do teclado e contar  letras maiusculas e minusculas menores que K\n");
      printf("6-ler palavra do teclado e mostrar  letras maiusculas e minusculas menores que K\n");
      printf("7-ler palavra do teclado e mostrar  numeros impares na cadeia\n");
      printf("8-ler palavra do teclado e mostrar  algoritimos nao alfanumericos\n");
      printf("9-mostrar todos os símbolos alfanuméricos (letras e dígitos) em uma cadeia de caracteres\n");
      printf("10-mostrar e contar todos os símbolos alfanuméricos (letras e dígitos) em uma cadeia de caracteres\n");
      printf("11-mostrar e contar todos os símbolos alfanuméricos (letras e dígitos)e os espaços em branco em uma cadeia de caracteres\n");
      printf("11-contar e mostrar qual das cadeias de digitos é menor\n");
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
   float a , b , x ;
   int  n , countDentro, countFora;
   
   
   
  
    printf("Digite um valor e em seguida um valor maior para definir um intervalo entre esses valores\n ");
   scanf("%f",&a);
   
   printf("Digite um valor e em seguida um valor maior para definir um intervalo entre esses valores\n ");
   scanf("%f", &b);
   
  
  
   
   
   
   
   printf("digite quantos valores voce deseja testar:");
   scanf("%d" , &n);
   
   for(int i = 0; i < n; i++){
       
        printf("Informe o valor %d: ", i + 1);
        scanf("%f", &x);
        
         if (  x >= a && x <= b ) { 
             
             countDentro++;
             
         }
         
         else {
             
             countFora++;
         }
         
       
         
   }
   
    printf("existem %d numeros dentro do intervalo \n" , countDentro);
         printf("existem %d numeros fora do intervalo \n" , countFora);
         getchar();
   
}




void metodo2()
{
    char palavra[21] = "aa";
   int x = 0;
   int contador = 0;//contador para dizer quantas letras sao maiusculas
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar as letras maiusculas\n");// ate 20, pois o caracter 21 sera \0
   scanf("%s",palavra);
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_letra_maiuscula(palavra[x]) && palavra[x] < 'K')//verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
         ++contador;//somar 1 ao contador cada vez que uma letra maiuscula for detectada
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
  printf("existem %d letras menores que K na palavra \n" , contador);
}



void metodo3()
{
    char palavra[100]; // sequência de caracteres

    // leitura da sequência de caracteres
    printf("Digite uma sequencia de caracteres: ");
   scanf("%s" , palavra);

    // contagem das letras maiúsculas menores que 'K'
    int cont = conta_letras_maiusculas(palavra);

    // exibição do resultado
    printf("Quantidade de letras maiusculas menores que 'K': %d\n", cont);

    
}


void metodo4()
{
    char palavra[21] = "aa";
   int x = 0;
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar as letras maiusculas\n");// ate 20, pois o caracter 21 sera \0
   scanf("%s",palavra);
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_letra_maiuscula(palavra[x]) && palavra[x] < 'K')//verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
        
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
  
}




void metodo5()
{
    char palavra[100]; // sequência de caracteres

    // leitura da sequência de caracteres
    printf("Digite uma sequencia de caracteres: ");
   scanf("%s" , palavra);

    // contagem das letras maiúsculas menores que 'K'
    int cont = conta_letras_maiusculas_e_minuscula(palavra);

    // exibição do resultado
    printf("Quantidade de letras maiusculas e minusculas menores que 'K': %d\n", cont);

    
}

void metodo6()
{
    char palavra[21] = "aa";
   int x = 0;
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar as letras maiusculas\n");// ate 20, pois o caracter 21 sera \0
   scanf("%s",palavra);
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_letra_maiuscula_e_minsucula(palavra[x]) )//verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
        
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
   
  
}


void metodo7 ()
{
   int quantidade = 0;
   char c = 0;
   int comparador = 0;
   int contador =0;
   int z = 0;
   int i = 0;
   static char pares [80];
   printf("Digite a quantidade de caracteres que deseja analisar, o programa retornará os digitos pares\n");
   scanf("%i", &quantidade);
   while (comparador != quantidade)
   {
      printf("Digite o caractere desejado\n");
      getchar();
      scanf ("%c", &c);
      if (c >= '0' && c <= '9') 
   {
      z = (int) c;
      
      if (z % 2 == 0)
      {
         pares[i] = c;
         i++;
         contador++;
        
      }
   }

      comparador++;
   } 
   pares[i]='\0';
   printf("O números pares são %s e total de numeros pares e %i\n", pares, contador);
}



void metodo8()
{
    char palavra[21] = "aa";
   int x = 0;
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar as letras maiusculas\n");// ate 20, pois o caracter 21 sera \0
   scanf("%s",palavra);
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_nenhuma(palavra[x]) )//verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
         
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
   
  
}

void metodo9()
{
    char palavra[21] = "aa";
   int x = 0;
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar as letras maiusculas\n");// ate 20, pois o caracter 21 sera \0
   scanf("%s",palavra);
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_alfanumerico(palavra[x])) //verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
         
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
   
  
}



void metodo10()
{
    char palavra[21] = "aa";
   int x = 0;
   int contador = 0;
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar os alfanumericos\n");// ate 20, pois o caracter 21 sera \0
   scanf("%s",palavra);
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_alfanumerico(palavra[x]) )//verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
         contador++;
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
  printf("o total de alfanumericos e %d\n" , contador);
}





void metodo11()
{
    char palavra[50] = "aa";
   int x = 0;
   int contador = 0;
   printf("Digite uma palavra (com ate 20 caracteres) para o programa mostrar os alfanumericos e os espaços\n");// ate 20, pois o caracter 21 sera \0
   fgets(palavra,50,stdin);//fgets para ler o espaco
  
   while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
      if(eh_alfanumerico_e_espaco_em_branco(palavra[x]) )//verificar se esta entre as letras maiusculas
      {
         printf("%c\n", palavra[x]);//caso sim imprimir
         contador++;
      }
      ++x;//mudar a posicao das letras da string
      
   } 
   
  printf("o total de alfanumericos e %d\n" , contador);
}




void metodo12()
{

    char palavra[21] = "aa";
    char palavra1[21] = "aa";
    int contador = 0 ;

    printf("Digite a primeira sequencia\n");// ate 20, pois o caracter 21 sera \0
    getchar();
    fgets(palavra, 21, stdin);

    printf("Digite a segunda equencia\n");// ate 20, pois o caracter 21 sera \0
    getchar();
    fgets(palavra1,21,stdin);





    if (palavra < palavra1 )
    {
        printf("A primeira sequencia possui a menor quantidade de digitos.\n");
    }
    else if (palavra1 < palavra)
    {
        printf("A segunda sequencia possui a menor quantidade de digitos.\n");
    }
    else
    {
        printf("As duas sequencias possuem a mesma quantidade de digitos.\n");
    }










}