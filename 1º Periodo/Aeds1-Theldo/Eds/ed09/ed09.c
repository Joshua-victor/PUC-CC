#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>

void metodo0();
void metodo1();
void metodo3();
void metodo4();
void metodo5();
void metodo6();
void metodo7();
void metodo8();
void metodo9();
void metodo10();

int main()
{
   int x = 0;
   do
   {
      printf("0-Sair do programa\n");
      printf("1-Ler o numero de linhas, colunas e os termos de uma matriz e mostra-los na tela, salva-las em um arquivo e imprimir na tela informacoes do arquivo\n");
      printf("3-ler uma matriz e caso for quadrada imprimir sua diagonal principal\n");
      printf("4-ler uma matriz e caso for quadrada imprimir sua diagonal secundaria\n");
      printf("5-ler uma matriz e caso for quadrada imprimir os elementos abaixo da diagonal principal\n");
      printf("6-ler uma matriz e caso for quadrada imprimir os elementos acima da diagonal principal\n");
      printf("7-ler uma matriz e caso for quadrada imprimir os elementos abaixo da diagonal secundaria\n");
      printf("8-ler uma matriz e caso for quadrada imprimir os elementos acima da diagonal secundaria\n");
      printf("9-testar se não são todos zeros os valores abaixo da diagonal principal de uma matriz real quadrada\n");
      printf("10-testar se são zeros os valores acima da diagonal principal de uma matriz real quadrada\n");
    
      scanf("%i",&x);
      switch(x)
      {
         case 0:
            metodo0();
            break;
         case 1:
            metodo1();
            break;
         case 3:
            metodo3();
            break;
         case 4:
            metodo4();
            break;
         case 5:
            metodo5();
            break;
         case 6:
            metodo6();
            break;
         case 7:
            metodo7();
            break;
         case 8:
            metodo8();
            break;
         case 9:
            metodo9();
            break;
         case 10:
            metodo10();
            break;
            
            break;
         default:
            printf("Comando invalido, tente outro\n");
            x =1;
      }
   }while(x!=0);
   printf("Aperte enter para sair do programa\n");
   fflush( stdin);
   getchar();
   return (0);
}
void metodo0()
{
}
void metodo1()
{
   int colunas = 0;
   int linhas = 0;
   char nome[16];
   void mostrarmatriz(int x, int y, double m[x][y]);
   void arquivomatriz(int x, int y, double m[x][y], char c[]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   int continuar = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   printf("Digite 1 se quiser salvar a matriz em um arquivo\n");
   scanf("%i",&continuar);
   if(continuar == 1)
   {
      printf("Digite o nome do arquivo\n");
      scanf("%s", nome);
      arquivomatriz(linhas, colunas, matriz, nome);
   
   }
}
void mostrarmatriz(int x, int y, double m[x][y])
{
   printf("A matriz e:\n");
   for(int aux1 = 0; aux1 < x; aux1++)
   {
      for(int aux2 = 0; aux2< y; aux2++)
      {
         printf("%lf\t", m[aux1][aux2]);
      }
      printf("\n");
   }
}
void arquivomatriz(int x, int y, double m[x][y], char c[])
{
   FILE* arquivo = fopen(c, "wt");
   void mostrararquivo(char c[]);
   for(int aux1 = 0; aux1 < x; aux1++)
   {
      for(int aux2 = 0; aux2< y; aux2++)
      {
         fprintf(arquivo, "%lf\t", m[aux1][aux2]);
      }
      fprintf(arquivo,"\n");
   }
   fclose(arquivo);
   mostrararquivo(c);
}
void mostrararquivo(char c[])
{
   FILE* arquivo = fopen(c, "rt");
   char mostrar[101];
   fgets(mostrar,101, arquivo);
   while(!(feof(arquivo)))
   {
      printf("%s", mostrar);
      fgets(mostrar,101, arquivo);
   }
   fclose(arquivo);
}
void metodo3()
{

   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if( linhas == colunas)
   {
      printf("E uma matriz quadrada e sua diagonal principal e:\n");
      for(aux1 = 0; aux1 < linhas; aux1++)
      {
         printf("%lf", matriz[aux1][aux1]);
         printf("\n");
         for (aux2 = 0; aux2 <= aux1; aux2++)
         {
            printf("\t");
         } 
      }
      
   }
   else 
   {
      printf("Nao e uma matriz quadrada, entao nao existe diagonal principal\n");
   
   }
   printf("\n");
}

void metodo4()
{

   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if (linhas == 1 && colunas ==linhas)
   {
      printf("E uma matriz [1][1], e nao ha elementos abaixo da digonal secundaria\n");
   }
   else
   {
      if( linhas == colunas)
      {
         printf("E uma matriz quadrada e sua diagonal secundaria e:\n");
         aux2 = 0;
         for(aux1 = colunas-1; aux1 >= 0; aux1--)
         {
            printf("%lf", matriz[aux2][aux1]);
            printf("\n");
            aux2++;
         }
      
      }
      else 
      {
         printf("Nao e uma matriz quadrada, entao nao existe diagonal secundaria\n");
      
      }
      printf("\n");
   }
}

void metodo5()
{

   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if (linhas == 1 && colunas ==linhas)
   {
      printf("E uma matriz [1][1], e nao ha elementos abaixo da digonal principal\n");
   }
   else
   {
      if( linhas == colunas)
      {
         printf("E uma matriz quadrada e os elementos abaixo da diagonal principal sao:\n");
         for(aux1 = 1; aux1 < linhas; aux1++)
         {
            for (aux2 = 0; aux2 < aux1; aux2++)
            {
               printf("%lf ", matriz[aux1][aux2]);
            }
            printf("\n");
         }
      
      }
      else 
      {
         printf("Nao e uma matriz quadrada, entao nao existe diagonal principal\n");
      
      }
      printf("\n");
   }
}
void metodo6()
{
   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if (linhas == 1 && colunas ==linhas)
   {
      printf("E uma matriz [1][1], e nao ha elementos abaixo da digonal principal\n");
   }
   else
   {
      if( linhas == colunas)
      {
         printf("E uma matriz quadrada e os elementos acima da diagonal principal sao:\n");
         for(aux1 = 0; aux1 < linhas; aux1++)
         {
            for (aux2 = aux1+1; aux2 < colunas; aux2++)
            {
               printf("%lf ", matriz[aux1][aux2]);
            }
         }
      
      }
      else 
      {
         printf("Nao e uma matriz quadrada, entao nao existe diagonal principal\n");
      
      }
   }
   printf("\n");
}

void metodo7()
{
   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   int aux3 = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if (linhas == 1 && colunas ==linhas)
   {
      printf("E uma matriz [1][1], e nao ha elementos abaixo da digonal secundaria\n");
   }
   else
   {
      if( linhas == colunas)
      {
         printf("E uma matriz quadrada e os elementos abaixo da diagonal secundaria sao:\n");
         aux2=colunas-1;
         for(aux1 = 1; aux1 < linhas; aux1++)
         {
            aux3 = aux2 - 1;
            while(aux2<colunas)
            {
               printf("%lf ", matriz[aux1][aux2]);
               aux2++;
            }
            aux2 =aux3;
            
         }
      
      }
      else 
      {
         printf("Nao e uma matriz quadrada, entao nao existe diagonal secundaria\n");
      
      }
   }
   printf("\n");
}




void metodo8()
{
   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   int aux3 = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if (linhas == 1 && colunas ==linhas)
   {
      printf("E uma matriz [1][1], e nao ha elementos acima da digonal secundaria\n");
   }
   else
   {
      if( linhas == colunas)
      {
         printf("E uma matriz quadrada e os elementos acima da diagonal secundaria sao:\n");
         aux3=colunas-1;
         for(aux1 = 0; aux1 < linhas-1; aux1++)
         {
            for(aux2=0; aux2 < aux3; aux2++)
            {
               printf("%lf ", matriz[aux1][aux2]);
            }
            aux3--;
         }
      
      }
      else 
      {
         printf("Nao e uma matriz quadrada, entao nao existe diagonal secundaria\n");
      
      }
   }
   printf("\n");
}

void metodo9()
{

   
   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   int count = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if( linhas == colunas)
   {
      printf("E uma matriz quadrada e sua diagonal principal e:\n");
      
      
      for(aux1 = 0; aux1 < linhas; aux1++)
      {
          if( matriz [aux1][aux2] == 0){
              count++;
              
          }
         printf("%lf", matriz[aux1][aux1]);
         printf("\n");
         for (aux2 = 0; aux2 <= aux1; aux2++)
         {
            printf("\t");
         } 
      }
       
      
      
   }
   else 
   {
      printf("Nao e uma matriz quadrada, entao nao existe diagonal principal\n");
   
   }
    printf ("existem %d zeros na diagonal principal" , count);
   printf("\n");
}


void metodo10()
{

   int colunas = 0;
   int linhas = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   do
   {
      printf("Digite o numero de linhas da matriz\n");
      scanf("%i", &linhas);
      if(linhas <= 0)
      {
         printf("O numero de linhas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(linhas <= 0);
   do
   {
      printf("Digite o numero de colunas da matriz\n");
      scanf("%i", &colunas);
      if(colunas <= 0)
      {
         printf("O numero de colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(colunas <= 0);
   double matriz [linhas][colunas];
   int aux1 = 0;
   int aux2 = 0;
   int count = 0;
   for(aux1 = 0; aux1 < linhas; aux1++)
   {
      for(aux2 = 0; aux2< colunas; aux2++)
      {
         do
         {
            printf("Digite o termo [%i][%i] da matriz, sendo um valor positivo:\n",aux1 + 1, aux2 + 1);
            scanf("%lf", &matriz[aux1][aux2]);
            if(matriz[aux1][aux2]<=0)
            {
               printf("O valor digitado nao e positivo tente outro\n");
            }
         }while(matriz[aux1][aux2]<=0);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if (linhas == 1 && colunas ==linhas)
   {
      printf("E uma matriz [1][1], e nao ha elementos abaixo da digonal principal\n");
   }
   else
   {
      if( linhas == colunas)
      {
          if (matriz [aux1][aux2] == 0){
              
              count++;
          }
         printf("E uma matriz quadrada e os elementos acima da diagonal principal sao:\n");
         for(aux1 = 0; aux1 < linhas; aux1++)
         {
            for (aux2 = aux1+1; aux2 < colunas; aux2++)
            {
               printf("%lf ", matriz[aux1][aux2]);
            }
         }
      
      }
      else 
      {
         printf("Nao e uma matriz quadrada, entao nao existe diagonal principal\n");
      
      }
       printf ("existem %d zeros na diagonal principal" , count);
   }
   printf("\n");
}


