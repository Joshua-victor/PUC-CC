//bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int main()
{
   printf(" PROVA 01  ");
   int x = 0;
   void metodo0 ();
   void metodo1 ();
   void metodo2 ();
   void metodo3 ();
   void metodo4 ();
   void metodo5 ();
   void metodo6 ();
   void metodo7 ();
   void metodo8 ();
   do
   {
       printf("\n");
      printf("\n-----Digite 0 para sair do programa-----\n");
      printf("-----Prova01 - Questao 01----\n");
      printf("-----Prova01 - Questao 02----\n");
      printf("-----Prova01 - Questao 03----\n");
      printf("-----Prova01 - Questao 04----\n");
      printf("-----Prova01 - Questao 05----\n");
      printf("-----Prova01 - Questao 06----\n");
      printf("-----Prova01 - Questao 07----\n");
      printf("-----Prova01 - Questao 08----\n");
      printf("Digite o numero da questao: ");
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
         default:
            printf("Valor diferente, tente outro\n");
            x=1;    
      }
   }while(x!=0);   
   fflush ( stdin );     
   getchar( );  
   return (0);
}
//questao 06
int P_06(int base, int expoente){
    return pow(base, expoente);
}
void potencia (){
int base=0;
int expoente = base+1;
for (int i=0; i<10;i++){
    printf("\n valor procurado: %d^%d == %d^%d", base, expoente, expoente, base);
    if(pow(base,expoente)== pow(expoente, base)){

    
}
base++;
expoente ++;
        }
    }
    
//questao 7
bool p_07(const char *palavra) {
    int tamanho = strlen(palavra);
    if (tamanho == 0)
        return false;

    if (strcmp(palavra, "PARAR") == 0)
        return false;

    for (int i = 0; i < tamanho - 1; i++) {
        char letraAtual = palavra[i];
        char letraProxima = palavra[i + 1];

        if (letraAtual == 'p' || letraAtual == 'b') {
            if (i > 0 && palavra[i - 1] != 'm')
                return false;
        }
    }

    return true;
}

//questao 08
double fracoes(int n){
    double numerador = 1 ;
    double denominador =n;
    double soma=0;
    for (int i = 0; i < n; i++)
    {
        soma = soma+(numerador/denominador);
        numerador++;
        denominador--;
    }
    return soma;
}

void metodo0 ()
{
   // sair do programa
}
void metodo1 ()
{
    /*
    Questao 01:
    Qual das alternativas abaixo sra uma igualdade: 
    */
    
printf("\n(a) %d=%d",(4/(2+2)/4),(4/2+2/4)); 
printf("\n(b) %d=%d",((4/2)+(2/4)),(2-(4/2)+2*(2*2/4)));// Alternativa correta
printf("\n(c) %d=%d",((4+2)*2-4),(4+2*2-4)); 
printf("\n(d) %d=%d",((4+2/4)+(4-2)),((4/2)+(2+2*4)/(2+4))); 
}
   

void metodo2()
{
    /*
    Questao 02:
    Qual saida abaixo sera diferente das outras: 
    */
       bool a=(int) (M_PI * 1.0f) / 3;
       char b= (char) (((int) '2'-1 ) -48);
       double c= ( 4/3 + (int) (double) 3/5);
       int d= ( a < 4 ) && ( c <= 2%3 );

       // resultados
       printf ( "\n a = %d", a );      
       printf ( "\n b = %d", b );      
       printf ( "\n c = %lf", c );     
 
       // Alternativa correta
       printf ( "\n d = %d", d );       // 1

}

void metodo3()
{
    /*
    Questao 03:
    Qual a saida abaixo sera verdadeira: 
    */
       int a = 10;
       int b = 20;
       int c = 30;
       int d = 0;
       
    // resultados
       if      ( b>a && a>c || b>c && a>b ) {d = c;}
       else if ( a>b && c>b || b<c && a>b ) {d = b;}
       else if ( a<b && b>c || a<b && c>b ) {d = a;}
       printf ( "\nd = %d ", d ); 
       /*
       Alternativas: 
       a- d=0
       b- d=10   Alernativa correta
       c- d=20
       d- d=30
       */
      
}

void metodo4()
{
    /*
    Questao 04:
    Quais as saidas do codigo abaixo : 
    */  
    int x=0 , y= 0, n=5;
    y=n*(n+1)/2;
    for (x=2;x<=n; x=x+1)
   { y=y-x;
    printf("%d ",y);
   }
   
}
void metodo5()
{
   /*
    Questao 05:
    Qual a saida da funcao abaixo : 
    */
    int f1(int x, int y) {
      int z = 0;
    
        if (x < 0) {
            z = f1(-x, 1);
        } else {
            if (y <= 1) {
                z = f1(x, 2);
            } else if (x >= y / 2 && x % y == 0) {
                z = y + f1(x, y + 2);
            } else if (x >= y / 2) {
                z = f1(x, y + 2);
            }
        }
    
        return z;
    }

    printf("f1(18,1) = %d\n", f1(18, 1));
    
}
void metodo6(void)
{
    /*
    Questao 06:
    Definir uma funcao inteira para calcular
    o valor de um numero elevado a uma potencia
    tambem inteira.
    Em um metodo procurar e mostrar
    dois valores inteiros consecutivos
    (m e n), menores ou iguais a 10,
    para os quais valera a relacao abaxio,
    usando a funcao definida abaixo 
        m^n igual a n^m
    */
     potencia();
}
void metodo7()
{
    /*
    Questao 07:
    um corretor ortografico precisa implementar 
    uma verificacao para a seguinte regra da 
    lingua portuguesa:
    "antes de 'b' e 'p' devera vim 'm' e nao 'n' "

    ler palavras, uma de cada vez,
    a ultima palavra serar "PARAR", e 
    nao devera ser processada;
    dizer se cada palavra esta correta ou nao.

        ex:canpo,sombra...PARAR
    */
    char palavra[50];

    while (true) {
        printf("Digite uma palavra (ou 'PARAR' para sair): ");
        scanf("%s", palavra);

        if (p_07(palavra))
            printf("A palavra esta correta!\n");
        else
            printf("Atencao a palavra esta incorreta \n");

        if (strcmp(palavra, "PARAR") == 0)
            break;
    }
}
void metodo8()
{
    /*
    Questao 08:
    dados um valor inteiro positivo (n);
    e uma funcao real para calcular a soma
    1/n + 2/n-1 + ... n-1/2 + n/1
    ler tres valores inteiros diferentes entre si 
    e dizer qual deles possuira a menor soma,
    calculada pela funcao definida acima.
    */
     int a,b,c;
    printf("digite o primeiro numero: ");
    scanf("%d",&a);
    printf("digite o segundo numero: ");
    scanf("%d",&b);
    printf("digite o terceiro numero: ");
    scanf("%d",&c);
    double somaprimeiro= fracoes(a);
    double somasegundo= fracoes(b);
    double somaterceiro= fracoes(c);
if(a<b&&a<c){
  printf("o primeiro numero digitado possui a menor soma") ;
        } else if(b<a&&b<c)
    {
    printf(" o segundo numero digitado possui a menor soma");
            } else if(c<a&&c<b)
    {
    printf(" o terceiro numero digitado possui a menor soma");
    } else
{
    printf("ha somas iguais");
        }
}