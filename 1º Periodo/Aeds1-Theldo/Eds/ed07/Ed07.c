#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//2
int multiplo_cinco (int pos){
    
  return 5 * (pos  * 1);
}


//6
void calculateAndSaveSums(int n) {
    FILE *fileOut = fopen("RESULTADO06.TXT", "w");
    if (fileOut == NULL) {
        printf("Erro ao abrir arquivo de saída.\n");
        return;
    }

    // ler valores do arquivo de entrada
    FILE *fileIn = fopen("005.txt", "r");
    if (fileIn == NULL) {
        printf("Erro ao abrir arquivo de entrada.\n");
        fclose(fileOut);
        return;
    }

    int count = 0;
    double x, value, sum = 0.0;
    while (fscanf(fileIn, "%lf", &value) == 1) {
        if (count == 0) {
            x = value;
        } else if (count <= n) {
            sum += 1.0 / pow(x, 2 * (count - 1));
        }
        count++;
    }
    fclose(fileIn);

    // gravar resultado no arquivo de saída
    fprintf(fileOut, "Quantidade = %d\tResultado = %.2lf\n", n, sum);

    fclose(fileOut);
}

//7
void calcularSoma(int n) {
    FILE* arquivoEntrada;
    FILE* arquivoSaida;
    int i;
    double soma = 0, termo;

    arquivoEntrada = fopen("dados4.txt", "r");
    arquivoSaida = fopen("resultado07.txt", "w");

    if(arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro na abertura de arquivos.");
        return;
    }

    for(i = 0; i < n; i++) {
        fscanf(arquivoEntrada, "%lf", &termo);
        soma += 1/pow(termo, 2*i);
    }

    fprintf(arquivoSaida, "Quantidade de termos: %d\nSoma: %lf", n, soma);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);
}



//8

void arquivofibonacci( int x)
{
   FILE* arquivo = fopen ("RESULTADO08.TXT","w" );
   void resultado08();
   int resposta = 0;
   int a = 0;
   int b = 1;
   int soma = 0;
   fprintf(arquivo, "Os primeiros %i termos pares de fibonacci sao:  \n", x);
   while(x > 0)
   {
      soma = a + b;
      b = a;
      a = soma;
      if ( soma % 2 == 0)
      {
         fprintf(arquivo, " %i - ", soma);
         x--;
      }
   }   
    fprintf(arquivo, "\n");
   fclose (arquivo);

}

void resultado08(char c[])
{
   FILE* arq = fopen ("resultado08", "a");
   FILE* arquivo = fopen (c, "rt");
   char leitura [1000];
   fgets(leitura ,1000 ,arquivo);
   while ( !(feof (arquivo)))
   {
      fputs(leitura, arq);
      fgets(leitura ,1000 ,arquivo);
   }
   fclose (arquivo);
   fclose (arq);
}

//12
int contar_palavras_c() {
    int cont = 0;
    char palavra[100];

    printf("Digite as palavras (uma por linha) e pressione enter.\n");
    printf("Pressione enter sem digitar nada para encerrar.\n");

    while (fgets(palavra, sizeof(palavra), stdin) != NULL) { // Ler uma linha por vez
        if (palavra[0] == '\n') { // Verificar se a linha está vazia (apenas o caractere de nova linha)
            break; // Encerrar o loop se a linha estiver vazia
        }
        if (tolower(palavra[0]) == 'c') { // Verificar se a primeira letra é 'c' ou 'C'
            cont++;
        }
    }

    return cont;
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
      printf("1-gravar essa quantidade em múltiplos de 3, pares, em ordem crescente, começando em 6.\n");
      printf("2-gravar essa quantidade em múltiplos de 5, ímpares, em ordem decrescente encerrando em 15.\n");
      printf("3- ler um valor inteiro do teclado e gravar essa quantidade em valores da sequência: 1 6 36 216 1296\n");
      printf("4- ler um valor inteiro do teclado e gravar essa quantidade em valores decrescentes da sequência:1/1296 1/216 1/36 1/6 1\n");
      printf("5- ler um valor inteiro do teclado (n) e outro valor real (x), gravar essa quantidade (n) em valores reais da sequência\n");
      printf("6-\n");
      printf("7-\n");
      printf("8- ler um valor inteiro do teclado, e até atingir essa quantidade, um valor por vez, gravar o valor correspondente aos primeiros termos pares da série de Fibonacci.\n");
      printf("9- para calcular a quantidade de minúsculas em cadeia de caracteres de um arquivo texto.\n");
      printf("10- para contar dígitos maiores ou iguais a 3 em uma cadeia de caracteres. \n");
      printf("11- programa ler um valor inteiro do teclado, e gravar em arquivo os seus divisores em ordem decrescente\n");
      printf("12- ler palavras de um arquivo, uma por linha, e contar quantas começam com a letra 'c' (ou 'C').\n");
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
         case 12:
            metodo12 ();
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
    FILE* arquivo ;
     int y = 0;
     int n ;
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

    arquivo = fopen ("001.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
   
  }

    printf("\nDigite n termos: ");
    scanf("%d",&n);
    fprintf ( arquivo, "Numero de termos:%d\n", n );

    for ( y = 1; y <= n; y = y + 1 )
    {
        fprintf ( arquivo, "%d\n", 6*y );
    } 

    fclose ( arquivo );
    getchar();
    
   
         
}
   
   

void metodo2()
{
    
    FILE* arquivo ;
     int y = 0;
     int quantidade ;
     int resultado = 0;
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

            arquivo = fopen ("002.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
   
  }

    printf("\nDigite n termos: ");
    scanf("%d",&quantidade);
    fprintf ( arquivo, "Numero de termos:%d\n",quantidade );

  for(int y = quantidade - 2 ; y >= 0; y--){
   
 
   resultado = multiplo_cinco(y);
   
  
       fprintf ( arquivo, "%d\n", resultado );
   
  
    
  }
  
  fprintf ( arquivo, "15" );

    fclose ( arquivo );
    getchar();
  
    
    
}



void metodo3()
{
    
     FILE* arquivo ;
     int y = 0;
     int quantidade ;
     int soma = 1;
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

            arquivo = fopen ("003.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
   
  }

    printf("\nDigite n termos: ");
    scanf("%d",&quantidade);
    fprintf ( arquivo, "Numero de termos:%d\n", quantidade );

    if(quantidade == 1){
    
     fprintf ( arquivo, "1"  );}
    else{
        
 fprintf ( arquivo, "1\n"  );}
    for ( y = 1; y < quantidade; y = y + 1 )
    {
        
        soma = soma *6;
        
        fprintf ( arquivo, "%d\n", soma );
        
        
    } 

    fclose ( arquivo );
    getchar();
    
    
    } 



void metodo4()
{
    
     FILE* arquivo ;
     int y = 0;
     int quantidade ;
     int soma = 1;
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

            arquivo = fopen ("004.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
   
  }

    printf("\nDigite n termos: ");
    scanf("%d",&quantidade);
    fprintf ( arquivo, "Numero de termos:%d\n", quantidade );


if(quantidade == 1){
    
     fprintf ( arquivo, "1\n"  );
    
}
 
else{
  
    
    for(int y = quantidade; y > 0; y--)
    {
        
      soma =   pow(6,quantidade);
        
        fprintf ( arquivo, "1/%d\n", soma );
        
      quantidade--;  
    } 
     fprintf ( arquivo, "1"  );

    fclose ( arquivo );
    getchar();
    
}
    
}




void metodo5()
{
     FILE* arquivo ;
    int n, i;
    double x;
   
   
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

   arquivo = fopen ("005.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
  
  }

   printf("\nDigite um valor inteiro: ");
    scanf("%d", &n);

    printf("Digite um valor real: ");
    scanf("%lf", &x);
    
   
    
    

     for (i = 0; i < n; i++) {
         
         
         
        fprintf(arquivo, "%lf ", 1/pow(x, 2*i));
        
        
        
    }
    
    
    fclose ( arquivo );
    getchar();
  
    
    
   
}

void metodo6()
{
   
    int n;
    printf("Digite a quantidade de valores a serem somados: ");
    scanf("%d", &n);

    calculateAndSaveSums(n);



    
}


void metodo7 ()
{
     int n;

    printf("Digite a quantidade de termos a serem somados: ");
    scanf("%d", &n);

    calcularSoma(n);

}



void metodo8()
{
     void arquivofibonacci( int x);
   int quantidade = 0;
 
   printf("Digite o numero de vezes que deseja imprimir os termos pares de fibonacci\n");
   scanf("%i", &quantidade);
   arquivofibonacci( quantidade);
   printf("O arquivo foi criado\n");
    
    
}

void metodo9()
{
    
     FILE* arquivo ;
     int count = 0;
     int x;
     char palavra[101];
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

    arquivo = fopen ("RESULTADO09.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
   
  }

    printf("\n Digite as palavras que voce quer testar: ");
    getchar();
    fgets(palavra,101,stdin); //fgets para ler o espaco
    
     fprintf ( arquivo, "contagem da frase: \n" );
    
    while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
     
     if(islower(palavra[x]) )
     
     count++;
    
     ++x;//mudar a posicao das letras da string
      
   } 
     fprintf ( arquivo, "existem %d digitos minusculos nas palavras: %s", count, palavra );
    
    

    fclose ( arquivo );
    getchar();
   
    
}



void metodo10()
{
    
     FILE* arquivo ;
     int count = 0;
     int x;
     char palavra[101];
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

    arquivo = fopen ("RESULTADO10.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
  
  }

    printf("\n Digite as palavras que voce quer testar: ");
    getchar();
    fgets(palavra,101,stdin); //fgets para ler o espaco
    
     fprintf ( arquivo, "contagem da frase: \n" );
    
    while(palavra[x] != '\0')//ler ate o ultimo caracter
   {
     
     if(isdigit(palavra[x]) && (palavra[x] - '0') >= 3)
     
     count++;
    
     ++x;//mudar a posicao das letras da string
      
   } 
     fprintf ( arquivo, "existem %d digitos maiores ou iguais a 3 na frase: %s", count, palavra );
    
    

    fclose ( arquivo );
    getchar();
   
    
 
}





void metodo11()
{
     FILE* arquivo ;
     int i = 0;
     int quantidade ;
     int soma = 0;
    printf ( "EXEMPLO0701 - Method01 - v0.0" );

            arquivo = fopen ("011.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
   
  }

    printf("\nDigite o numero que voce quer obter os divisores: ");
    scanf("%d",&quantidade);
    fprintf (arquivo, "os divisores sao:\n");
    
    
 for (i = quantidade; i >= 1; i--) {
        if (quantidade % i == 0) {
            fprintf(arquivo, "%d\n", i);
        }
    }


    fclose ( arquivo );
    getchar();
    
    
}




void metodo12()
{
    
     int cont = contar_palavras_c();
    FILE* arquivo ;
    
     arquivo = fopen ("dados1.txt","w" );
   if(arquivo == NULL)
  {
   printf("Erro na abertura do arquivo!");
  
  }
    
     fprintf ( arquivo, "Foram digitadas %d palavras que começam com 'c' ou 'C'.\n", cont );
    
    fclose ( arquivo );
    

    
}