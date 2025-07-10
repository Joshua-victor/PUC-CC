//bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
//funcoes

//1
int exercicio01() {
    int n, x, soma;
    
    printf("Digite a quantidade de valores: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Digite um valor: ");
        scanf("%d", &x);
        
        soma = 0;
        for (int j = 1; j <= x; j++) {
            if (x % j == 0) {
                soma += j;
            }
        }
        
        printf("Soma dos divisores [%d]: %d\n",x, soma);
    }
    
    return n;
}

//2
void exercicio02() {
    int n;

    printf("Digite a quantidade de valores: ");
    scanf("%d", &n);

    int x[n];
    printf("Digite os valores:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    printf("Verificacao de numeros primos:\n");
    for (int i = 0; i < n; i++) {
        int num = x[i];
        int primo = 1;

        if (num <= 1) {
            primo = 0;
        } else {
            for (int j = 2; j * j <= num; j++) {
                if (num % j == 0) {
                    primo = 0;
                    break;
                }
            }
        }

        if (primo) {
            printf("Valor %d e primo.\n", num);
        } else {
            printf("Valor %d nao e primo.\n", num);
        }
    }
}


//3 
int OperadorLogico(char c) {
    return (c == '&' || c == '|' || c == '!');
}

int OperadorAritmetico(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int OperadorRelacional(char c) {
    return (c == '>' || c == '<' || c == '=');
}

int Separador(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '.' || c == ',' || c == ';' || c == ':' || c == '_');
}


void exercicio03() {
    char cadeia[100];
    printf("Digite uma cadeia de caracteres: ");
    scanf("%99[^\n]", cadeia);

    printf("Classificacao :\n");
    for (int i = 0; cadeia[i] != '\0'; i++) {
        char c = cadeia[i];

        if (OperadorLogico(c)) {
            printf("%c: Operador Logico\n", c);
        } else if (OperadorAritmetico(c)) {
            printf("%c: Operador Aritmetico\n", c);
        } else if (OperadorRelacional(c)) {
            printf("%c: Operador Relacional\n", c);
        } else if (Separador(c)) {
            printf("%c: Separador\n", c);
        } else {
            printf("%c: Outro simbolo\n", c);
        }
    }
}


//4



int operadorLogico(char c) {
    return (c == '&' || c == '|' || c == '!');
}


int operadorAritmetico(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}


int operadorRelacional(char c) {
    return (c == '>' || c == '<' || c == '=');
}


int separador(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '.' || c == ',' || c == ';' || c == ':' || c == '_');
}



void exercicio04() {
    char cadeia[100];
    printf("Digite uma cadeia de caracteres: ");
    scanf("%99[^\n]", cadeia);

    int maiusculas = 0;
    int minusculas = 0;
    int digitos = 0;
    int operadores = 0;
    int separadores = 0;

    for (int i = 0; cadeia[i] != '\0'; i++) {
        char c = cadeia[i];

        if (c >= 'A' && c <= 'Z') {
            maiusculas++;
        } else if (c >= 'a' && c <= 'z') {
            minusculas++;
        } else if (c >= '0' && c <= '9') {
            digitos++;
        } else if (operadorLogico(c) || operadorAritmetico(c) || operadorRelacional(c)) {
            operadores++;
        } else if (separador(c)) {
            separadores++;
        }
    }

    printf("Resultados dos testes:\n");
    printf("Letras maiusculas: %d\n", maiusculas);
    printf("Letras minusculas: %d\n", minusculas);
    printf("Digitos: %d\n", digitos);
    printf("Operadores: %d\n", operadores);
    printf("Separadores: %d\n", separadores);
}






//5
double encontrarMaior(double a, double b, double c) {
    double maior = a;

    if (b > maior)
        maior = b;
    if (c > maior)
        maior = c;

    return maior;
}


void exercicio05() {
    int n;
    printf("Digite a quantidade de valores: ");
    scanf("%d", &n);

    double x[n];
    printf("Digite os valores:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    double somaMenor = 0.0;
    int countMenor = 0;

    double somaMeio = 0.0;
    int countMeio = 0;

    double somaMaior = 0.0;
    int countMaior = 0;

    for (int i = 0; i < n; i++) {
        double valor = x[i];

        if (valor < -32.25) {
            somaMenor += valor;
            countMenor++;
        } else if (valor >= -32.25 && valor <= 63.75) {
            somaMeio += valor;
            countMeio++;
        } else if (valor > 63.75) {
            somaMaior += valor;
            countMaior++;
        }
    }

    double mediaMenor = (countMenor != 0) ? somaMenor / countMenor : 0.0;
    double mediaMeio = (countMeio != 0) ? somaMeio / countMeio : 0.0;
    double mediaMaior = (countMaior != 0) ? somaMaior / countMaior : 0.0;

    printf("Média dos valores menores que -32.25: %.2lf\n", mediaMenor);
    printf("Média dos valores entre -32.25 e 63.75: %.2lf\n", mediaMeio);
    printf("Média dos valores maiores que 63.75: %.2lf\n", mediaMaior);

    double maiorMedia = encontrarMaior(mediaMenor, mediaMeio, mediaMaior);
    printf("Maior média de todas: %.2lf\n", maiorMedia);
}

//6 

// Função para verificar se um valor está no intervalo aberto (a, b)
int estaNoIntervalo(int valor, int a, int b) {
    return (valor > a && valor < b);
}

// Função para calcular a soma dos cubos dos inversos (1/x^3) dos ímpares
double calcularSomaCubosInversosImpares(int a, int b) {
    int valor;
    double soma = 0.0;

    printf("Digite os valores (digite -1 para parar):\n");
    while (1) {
        scanf("%d", &valor);
        if (valor == -1)
            break;

        if (estaNoIntervalo(valor, a, b) && valor % 2 != 0) {
            if (valor != 0)
                soma += 1.0 / (valor * valor * valor);
        }
    }

    return soma;
}

// Procedimento para realizar os testes
void exercicio06() {
    int a, b;
    printf("Digite os valores de a e b: ");
    scanf("%d %d", &a, &b);

    double somaCubosInversosImpares = calcularSomaCubosInversosImpares(a, b);

    printf("A soma dos cubos dos inversos dos ímpares no intervalo (%d, %d) é: %.2lf\n", a, b, somaCubosInversosImpares);
}


//7
 
 // Função para verificar se um valor está dentro do intervalo aberto (a, b)
int DentroDoIntervalo(double valor, double a, double b) {
    return (valor > a && valor < b);
}

// Procedimento para realizar os testes
void exercicio07() {
    double a, b;
    printf("Digite os valores de a e b: ");
    scanf("%lf %lf", &a, &b);

    double valor;
    int countDentro = 0;
    int countFora = 0;
    int countAcima = 0;
    int countAbaixo = 0;

    printf("Digite os valores (digite 0 para parar):\n");
    while (1) {
        scanf("%lf", &valor);
        if (valor == 0)
            break;

        if (DentroDoIntervalo(valor, a, b)) {
            countDentro++;
        } else {
            countFora++;
            if (valor > b)
                countAcima++;
            else if (valor < a)
                countAbaixo++;
        }
    }

    double percentAcima = (countFora != 0) ? (countAcima / (double)countFora) * 100.0 : 0.0;
    double percentAbaixo = (countFora != 0) ? (countAbaixo / (double)countFora) * 100.0 : 0.0;

    printf("Quantidade de valores dentro do intervalo: %d\n", countDentro);
    printf("Quantidade de valores fora do intervalo: %d\n", countFora);
    printf("Porcentagem de valores acima do intervalo: %.2lf%%\n", percentAcima);
    printf("Porcentagem de valores abaixo do intervalo: %.2lf%%\n", percentAbaixo);
}

//8
int OrdemDecrescente(float x, float y, float z) {
    return (x > y && y > z);
}


void exercicio08() {
    float x, y, z;

    printf("Digite o valor de x: ");
    scanf("%f", &x);

    printf("Digite o valor de y: ");
    scanf("%f", &y);

    printf("Digite o valor de z: ");
    scanf("%f", &z);

    if (OrdemDecrescente(x, y, z)) {
        printf("Os valores estao em ordem crescente.\n");
    } else if (OrdemDecrescente(x, y, z)) {
        printf("Os valores estao em ordem decrescente.\n");
    } else {
        float menor, maior;

        // Encontrar o menor valor
        menor = x;
        if (y < menor) menor = y;
        if (z < menor) menor = z;

        // Encontrar o maior valor
        maior = x;
        if (y > maior) maior = y;
        if (z > maior) maior = z;

        printf("Os valores nao estao em ordem. Menor valor: %.2f, Maior valor: %.2f\n", menor, maior);
    }
}

//9 

int ordemCrescente(char x, char y, char z) {
    return x < y && y < z;
}

int ordemDecrescente(char x, char y, char z) {
    return x > y && y > z;
}

void testeOrdemAlfabetica() {
    char x, y, z;
    printf("Digite o primeiro caractere: ");
    scanf(" %c", &x);
    printf("Digite o segundo caractere: ");
    scanf(" %c", &y);
    printf("Digite o terceiro caractere: ");
    scanf(" %c", &z);

    if (ordemCrescente(x, y, z)) {
        printf("Os caracteres estão em ordem crescente.\n");
    } else if (ordemDecrescente(x, y, z)) {
        printf("Os caracteres estão em ordem decrescente.\n");
    } else {
        printf("Os caracteres não estão em ordem crescente nem decrescente.\n");
    }
}


//10 

int comparar(char* a, char* b, char* c) {
    if (strcmp(a, b) > 0 && strcmp(b, c) > 0) {
        return -1; // ordem decrescente
    } else if (strcmp(a, b) < 0 && strcmp(b, c) < 0) {
        return 1; // ordem crescente
    } else {
        return 0; // nenhuma das ordens
    }
}

void exercicio10() {
    char x[100], y[100], z[100];
    printf("Digite as tres cadeias de caracteres:\n");
    scanf("%s %s %s", x, y, z);

    int resultado = comparar(x, y, z);

    if (resultado == -1) {
        printf("As cadeias estao em ordem decrescente.\n");
    } else if (resultado == 1) {
        printf("As cadeias estao em ordem crescente.\n");
    } else {
        char menor[100], maior[100];
        if (strcmp(x, y) < 0 && strcmp(x, z) < 0) {
            strcpy(menor, x);
        } else if (strcmp(y, z) < 0) {
            strcpy(menor, y);
        } else {
            strcpy(menor, z);
        }
        if (strcmp(x, y) > 0 && strcmp(x, z) > 0) {
            strcpy(maior, x);
        } else if (strcmp(y, z) > 0) {
            strcpy(maior, y);
        } else {
            strcpy(maior, z);
        }
        printf("As cadeias nao estao em ordem. A menor e %s e a maior e %s.\n", menor, maior);
    }
}


int main()
{
   printf(" Recuperacao 01 ");

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
   void metodo9 ();
   void metodo10 ();
   do
   {
       printf("\n");
      printf("\n-----Digite 0 para sair do programa-----\n");
      printf("----- Questao 01----\n");
      printf("----- Questao 02----\n");
      printf("----- Questao 03----\n");
      printf("----- Questao 04----\n");
      printf("----- Questao 05----\n");
      printf("----- Questao 06----\n");
      printf("----- Questao 07----\n");
      printf("----- Questao 08----\n");
      printf("----- Questao 09----\n");
      printf("----- Questao 10----\n");
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
        case 9:
            metodo9 ();
            break;
        case 10:
            metodo10 ();
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


void metodo0 ()
{
  
}
void metodo1 ()
{
   

 exercicio01();

}


void metodo2 ()
{
    
    
 exercicio02();

}
void metodo3 ()
{
   

    exercicio03();
    
}
void metodo4 ()
{
    
   

exercicio04();
    
}
void metodo5 ()
{
   
  
    
   exercicio05(); 
    
    
}
void metodo6 ()
{
    
    
    exercicio06(); 
    
}
void metodo7 ()
{
    
   


    exercicio07();
    
    
}
void metodo8 ()
{
      exercicio08();
    
    
}
void metodo9 ()
{
 
 testeOrdemAlfabetica();
    
     
    
}
void metodo10 ()
{
       exercicio10();
    
}