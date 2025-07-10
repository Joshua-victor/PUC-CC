#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define TAMANHO_MAX 7
#define DIGITO_INICIAL 3
#define DIGITO_FINAL 1
//funcoes



void q01(int a[], int n, int x, int y)
{
    if (x < y)
    {
        a[x] = a[x] + a[y];
        a[y] = a[x] - a[y];
        a[x] = a[x] - a[y];
        q01(a, n, x + 1, y - 1);
    }
}

//qual a saida esperada para:
int q02(char a[], int y, int x)
{
    y = y - 1;
    if (x <= y && a[x] == a[y])
        return (1 + q02(a, y, x ));
    else if (x < y)
        return (q02(a, y, x ));

}

//qual a saida esperada para:
void q03(int n, int a[][3])
{
    int x=0, y=0,z=0;
    while ( x < n )
    {
        y=x+1;
        while(y<n)
        {
            if (a[x][y] < a[y][x])
                a[x][y] = a[x][y] + a[y][x];
                y=y+1;
        }
        x=x+1;
    }
}

// qual a saida esperada para:
struct s {
    int a;
    double b;
    double c;
};

double q04(struct s x)
{
    int y = x.a;
    double z = 1.0;

    x.c = x.b;

    while (y > 0)
    {
        x.c = x.c * 10;
        z = z * 10;
        y = y - 1;
    }

    return ((int)x.c / z);
}

//dada o precedimento abaixo:
void q05(int *a, int *b, int *c)
{
    int d = *a, e = *b;
    if (d > e)
    {
        *a = e;
        *b = d;
    }
    
    d = *b;
    e = *c;
    if (d > e)
    {
        *b = e;
        *c = d;
    }
    
    d = *a;
    e = *b;
    if (d > e)
    {
        *a = e;
        *b = d;
    }
}

void q06(char *cadeia, int tamanhoTotal) {
    int tamanhoCadeia = strlen(cadeia);

    if (tamanhoCadeia >= tamanhoTotal) {
        // A cadeia já é maior ou igual ao tamanho total, não é necessário ajuste
        printf("%s\n", cadeia);
        return;
    }

    int espacosAntes = (tamanhoTotal - tamanhoCadeia) / 2;
    int espacosDepois = tamanhoTotal - tamanhoCadeia - espacosAntes;

    for (int i = 0; i < espacosAntes; i++) {
        printf("-");
    }
    printf("%s", cadeia);
    for (int i = 0; i < espacosDepois; i++) {
        printf("-");
    }
    printf("\n");
}

void q07(int linhas, int colunas, int matriz[][colunas], int *resultado) {
    int maiorColuna = colunas - 1; 
    int maiorValor = matriz[0][maiorColuna]; 
    int i, j;

   
    for (j = colunas - 2; j >= 0; j--) {
        int novoMaiorEncontrado = 0;
        for (i = 0; i < linhas; i++) {
            if (matriz[i][j] > maiorValor) {
                maiorColuna = j;
                maiorValor = matriz[i][j];
                novoMaiorEncontrado = 1;
            }
        }
       
        if (novoMaiorEncontrado) {
            j = colunas - 1;
        }
    }

   
    for (i = 0; i < linhas; i++) {
        resultado[i] = matriz[i][maiorColuna];
    }
}
void q08() {
    FILE *arquivoEntrada, *arquivoSaida;
    char linha[20];
    int resultados[TAMANHO_MAX] = {0};
    int quantidade = 0;

 
    arquivoEntrada = fopen("DADOS.TXT", "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL && quantidade < TAMANHO_MAX) {
        int valor = atoi(linha);
        if (valor >= 10000 && valor < 100000 && linha[0] == '3' && linha[4] == '1') {
            resultados[quantidade++] = valor;
        }
    }

   
    fclose(arquivoEntrada);

  
    arquivoSaida = fopen("RESULTADOS.TXT", "w");
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }


    for (int i = 0; i < TAMANHO_MAX; i++) {
        fprintf(arquivoSaida, "%5d\n", resultados[i]);
    }

    // Fecha o arquivo de saída
    fclose(arquivoSaida);
}


int main()
{
   printf("---->Ed<----");
   printf("\nJoshua Victor C. e Pereira\n");
   int x = 0;
   void atividade0 ();
   void atividade1 ();
   void atividade2 ();
   void atividade3 ();
   void atividade4 ();
   void atividade5 ();
   void atividade6 ();
   void atividade7 ();
   void atividade8 ();
   void atividade9 ();
   void atividade10 ();

   do
   {
      printf("0-Sair do programa\n");
      printf("1-  \n");
      printf("2-  \n");
      printf("3-  \n");
      printf("4-  \n");
      printf("5-  \n");
      printf("6-  \n");
      printf("7-  \n");
      printf("8-  \n");
    
 
      scanf("%i",&x);
      switch (x)
      {
         case 0:
            atividade0 ();
            break;
         case 1:
            atividade1 ();
            break;
         case 2:
            atividade2 ();
            break;
         case 3:
            atividade3 ();
            break;
         case 4:
            atividade4 ();
            break;
         case 5:
            atividade5 ();
            break;
         case 6:
            atividade6 ();
            break;
         case 7:
            atividade7 ();
            break;
         case 8:
            atividade8 ();
        
        
         default:
            printf("Valor diferente, tente outro\n");
            x=1;    
      }
   }while(x!=0);   
   fflush ( stdin );    
   getchar( );    
  // return (0);
}
void atividade0 ()
{
   
}
void atividade1 ()
{
    //qual a saida esperada para:
   int n = 7;
    int a[] = {2, 4, 6, 7, 5, 3, 1};
    q01(a, n, 0, n - 1);

    printf("Resultado: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    //Resultado : 1 3 5 7 6 4 2 
}
void atividade2 ()
{
   char a[] = "abacadabra";
    printf("%d\n", q02(a, strlen(a), 0));
    //resposta: 5 
}
void atividade3 ()
{
    int a[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int n = sizeof(a) / sizeof(a[0]);
    q03(3, a);

    printf("Resultado:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    //resposta: {1 6 10} {4 5 14}  { 7 8 9}
}
void atividade4 ()
{
      struct s x = {2, 0.12345};
    printf("%lf\n", q04(x));
    //Resposta: 0,120000
}
void atividade5 ()
{
    int x = 3, y = 1, z = 2;
    q05(&x, &y, &z);
    printf("%d %d %d\n", x, y, z);

    //Resposta: 1 2 3
}
void atividade6 ()
{

       char cadeia1[] = "maio";
    int n1 ;
    
    printf("quantidade de caracteres desejados:");
    scanf("%d" , &n1);
    
   
    
    q06 (cadeia1, n1);
   
}
void atividade7 ()
{

      int linhas = 4;
    int colunas = 5;
    int matriz[4][5] = {
        {11, 21, 31, 14, 15},
        {61, 71, 18, 19, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };
    int resultado[linhas];
    int i;

    q07(linhas, colunas, matriz, resultado);


    for (i = 0; i < linhas; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

}
void atividade8 ()
{
    escreverResultados();
}
