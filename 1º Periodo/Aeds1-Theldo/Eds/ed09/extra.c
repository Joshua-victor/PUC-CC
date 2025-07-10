#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void metodo10();
void metodo11();
void metodo12();
int main()
{
  
   int x = 0;
   do
   {
 
      printf("10-ler colunas e linhas de uma matriz e escreve-la em um arquivo\n");
      printf("11-ler colunas e linhas de uma matriz e escreve-la em um arquivo(tranposta do 10)\n");
      scanf("%i",&x);
      switch(x)
      {

         
         case 10:
            metodo11();
            break;
         case 11:
            metodo12();
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



void metodo10()
{

   int colunas = 0;
   int linhas = 0;
   bool resp = 0;
   void mostrarmatriz(int x, int y, double m[x][y]);
   bool teste2( int x , int y,double m[x][y]);
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
       
         printf("Digite o termo [%i][%i] da matriz\n",aux1 + 1, aux2 + 1);
         scanf("%lf", &matriz[aux1][aux2]);
      }
   }
   mostrarmatriz(linhas, colunas, matriz);
   if( linhas == colunas)
   {
      resp = teste2(linhas, colunas, matriz);
      if (resp == 0)
      {
         printf("A matriz e triangular superior\n");
      
      }
      else
      {
         printf("A matriz nao e triangular superior\n");
      }
      
   }
   else 
   {
      printf("Nao e uma matriz quadrada, entao nao existe diagonal principal\n");
   
   }
   printf("\n");
}
bool teste2( int x , int y, double m[x][y])
{
   bool resposta = 0;
   int aux1= 1;
   int aux2 = 0;
   while ((aux2 < x) && (resposta == 0))
   {
      while( (aux1 < y) && (resposta == 0))
      {
         
         resposta = (m[aux2][aux1] != 0);
         aux1++;
      }
      aux2++;
      aux1 = aux2+1;
   }

   return resposta;
}

int** retornmatriz(int x)
{
   int aux1 = 0;
   int aux2 = 0;
   int num =x *x;
   int** matriz = NULL;
   matriz = (int**)malloc(x*sizeof(int*));
   for(int i = 0; i <x; i++)
   {
      matriz[i] = (int*)malloc(x*sizeof(int));
   }
   for(aux1 = 0; aux1 < x; aux1++)
   {
      for(aux2 = 0; aux2 < x; aux2++)
      {
         matriz[aux2][aux1] = num;
         num--;
      }
   }
   return matriz;
}
void arquivoe2(int LeC, int** m)
{
   FILE* arquivo = fopen("matrizq2.txt", "wt");
   for(int aux1 = 0; aux1 < LeC; aux1++)
   {
      for(int aux2 = 0; aux2 < LeC; aux2++)
      {
       
         fprintf(arquivo,"%i\t", m [aux1][aux2]);
      
      }
      fprintf(arquivo,"\n");
   }

   fclose(arquivo);
}
void metodo11()
{
   int LeC = 0;
   void arquivoe2(int LeC, int** m);
   int** retornmatriz(int x);
   do
   {
      printf("Digite o numero de linhas e colunas da matriz\n");
      scanf("%i", &LeC);
      if(LeC <= 0)
      {
         printf("O numero de linhas e colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(LeC <= 0); 
   int aux1 = 0;
   int aux2 = 0;
   int** matriz = retornmatriz(LeC);
   for(aux1 = 0; aux1 < LeC; aux1++)
   {
      for(aux2 = 0; aux2 < LeC; aux2++)
      {
       
         printf("%i\t", matriz [aux1][aux2]);
      
      }
      printf("\n");
   }
   arquivoe2( LeC, matriz);
}  
int** retornmatriz1(int x)
{
   int aux1 = 0;
   int aux2 = 0;
   int num =x *x;
   int** matriz = NULL;
   matriz = (int**)malloc(x*sizeof(int*));
   for(int i = 0; i <x; i++)
   {
      matriz[i] = (int*)malloc(x*sizeof(int));
   }
   for(aux1 = 0; aux1 < x; aux1++)
   {
      for(aux2 = 0; aux2 < x; aux2++)
      {
         matriz[aux1][aux2] = num;
         num--;
      }
   }
   return matriz;
}
void arquivoe1(int LeC, int** m)
{
   FILE* arquivo = fopen("matrizq1.txt", "wt");
   for(int aux1 = 0; aux1 < LeC; aux1++)
   {
      for(int aux2 = 0; aux2 < LeC; aux2++)
      {
       
         fprintf(arquivo,"%i\t", m [aux1][aux2]);
      
      }
      fprintf(arquivo,"\n");
   }

   fclose(arquivo);
}
void metodo12()
{
   int LeC = 0;
   void arquivoe2(int LeC, int** m);
   int** retornmatriz1(int x);
   do
   {
      printf("Digite o numero de linhas e colunas da matriz\n");
      scanf("%i", &LeC);
      if(LeC <= 0)
      {
         printf("O numero de linhas e colunas e invalido, tente um valor nao nulo, positivo\n");
      }
   }while(LeC <= 0); 
   int aux1 = 0;
   int aux2 = 0;
   int** matriz = retornmatriz1(LeC);
   for(aux1 = 0; aux1 < LeC; aux1++)
   {
      for(aux2 = 0; aux2 < LeC; aux2++)
      {
       
         printf("%i\t", matriz [aux1][aux2]);
      
      }
      printf("\n");
   }
   arquivoe2( LeC, matriz);
}  