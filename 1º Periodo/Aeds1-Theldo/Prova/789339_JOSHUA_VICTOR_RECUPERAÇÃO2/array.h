#include "array.h"

//funcoes
//1 
void ordenarDecrescente(int n, int array[]) {
    int trocou;
    do {
        trocou = 0;
        for (int i = 1; i < n; i++) {
            if (array[i - 1] < array[i]) {
                // Troca os elementos se eles não estiverem em ordem decrescente
                int temp = array[i - 1];
                array[i - 1] = array[i];
                array[i] = temp;
                trocou = 1;
            }
        }
    } while (trocou);
}
//2 
void arranjo_inverter(int n, int array[]) {
    int i, temp;
    for (i = 0; i < n/2; i++) {
        temp = array[i];
        array[i] = array[n - 1 - i];
        array[n - 1 - i] = temp;
    }
}
//3 
int arranjo_maiorDeTodos(int n, int array[]) {
    int maior = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > maior) {
            maior = array[i];
        }
    }
    return maior;
}

int arranjo_SegundoMaior(int n, int array[], int maior) {
    int segundoMaior = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] < maior && array[i] > segundoMaior) {
            segundoMaior = array[i];
        }
    }
    return segundoMaior;
}
//4 
void arranjo_filtrar(int n1, int arranjo1[], int n2, int arranjo2[], int arranjo3[]) {
    int contador = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (arranjo1[i] == arranjo2[j]) {
                // Verificar se o elemento já foi adicionado ao arranjo3
                int encontrado = 0;
                for (int k = 0; k < contador; k++) {
                    if (arranjo3[k] == arranjo1[i]) {
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    arranjo3[contador] = arranjo1[i];
                    contador++;
                }
                break;
            }
        }
    }
}
//5 
int arranjo_paraDecimal(int n, int arranjo[]) {
    int decimal = 0;
    int potencia = 1;

    for (int i = n - 1; i >= 0; i--) {
        decimal += arranjo[i] * potencia;
        potencia *= 2;
    }

    return decimal;
}
//
int hasPowerRows(int rows, int columns, int matrix[][columns]) {
    for (int i = 0; i < rows; i++) {
        int power = 1;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] != power) {
                return 0;  // Retorna 0 se a característica não for satisfeita
            }
            power *= (i + 1);  // Calcula a próxima potência
        }
    }
    return 1;  // Retorna 1 se a característica for satisfeita
}

// 
int hasPowerColumns(int rows, int columns, int matrix[][columns]) {
    for (int j = 0; j < columns; j++) {
        int power = 1;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] != power) {
                return 0;  // Retorna 0 se a característica não for satisfeita
            }
            power *= (j + 1);  // Calcula a próxima potência
        }
    }
    return 1;  // Retorna 1 se a característica for satisfeita
}
//
typedef struct {
    char nome[50];
    int codigo;
    double preco;
} Supermercado;

// Função para calcular o preço médio de um produto
double calcularPrecoMedio(int n, Supermercado supermercados[]) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += supermercados[i].preco;
    }
    return soma / n;
}
int main()
{
   printf("---->Ed<----");
   printf("\nAutora: Celia Regina Perdigao\n");
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
      printf("1- colocá-los em ordem decrescente \n");
      printf("2- gravar o arranjo invertido  \n");
      printf("3- achar o maior valor que não ultrapasse o segundo parâmetro \n");
      printf("4- filtrar e mostrar os elementos comuns aos dois arranjos, sem repetições \n");
      printf("5- convertê-los para decimal mediante o uso de uma função \n");
      printf("6- montar, mostrar e gravar no arquivo uma matriz com a característica abaixo (tridiagonal crescente) \n");
      printf("7- montar, mostrar e gravar no arquivo MATRIZ2.TXT uma matriz com a característica abaixo (tridiagonal decrescente). \n");
      printf("8- definir uma função lógica para verificar se a matriz lida apresenta a característica abaixo (potências por linha) \n");
      printf("9-  definir uma função lógica para verificar etestar se a matriz lida apresenta a característica abaixo (potências por coluna) \n");
      printf("10- SUPERMECADO/ nomee codigo, preco medio...  \n");
 
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
         case 9:
            atividade9 ();
            break;
         case 10:
            atividade10 ();
            break;
         
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
   // Ler o arranjo do arquivo DADOS1.TXT
    int n = readArraySize("DADOS1.TXT");
    int array[n];
    freadIntArray("DADOS1.TXT", n, array);

    // Verificar se o arranjo está em ordem decrescente
    bool estaDecrescente = true;
    for (int i = 1; i < n; i++) {
        if (array[i - 1] < array[i]) {
            estaDecrescente = false;
            break;
        }
    }

    if (!estaDecrescente) {
        // Ordenar o arranjo em ordem decrescente
        ordenarDecrescente(n, array);

        // Escrever o arranjo ordenado no arquivo DECRESCENTE.TXT
        fprintIntArray("DECRESCENTE.TXT", n, array);
        printf("Arranjo ordenado em ordem decrescente e gravado em DECRESCENTE.TXT.\n");
    } else {
        printf("O arranjo já está em ordem decrescente.\n");
    }

   
}
void atividade2 ()
{
 
   // Ler o arranjo do arquivo "DECRESCENTE.TXT"
    char* arquivoEntrada = "DECRESCENTE.TXT";
    int n = readArraySize(arquivoEntrada);
    int arranjo[n];
    freadIntArray(arquivoEntrada, n, arranjo);

    // Inverter a ordem dos elementos do arranjo
    arranjo_inverter(n, arranjo);

    // Gravar o arranjo invertido no arquivo "INVERTIDOS.TXT"
    char* arquivoSaida = "INVERTIDOS.TXT";
    fprintIntArray(arquivoSaida, n, arranjo);

    printf("Arranjo invertido gravado em \"%s\"\n", arquivoSaida);

  
}
void atividade3 ()
{
   
   // Ler o arranjo do arquivo "DADOS1.TXT"
    char* arquivoEntrada = "DADOS1.TXT";
    int n = readArraySize(arquivoEntrada);
    int arranjo[n];
    freadIntArray(arquivoEntrada, n, arranjo);

    // Encontrar o maior valor do arranjo
    int maiorValor = arranjo_maiorDeTodos(n, arranjo);

    // Encontrar o segundo maior valor do arranjo
    int segundoMaiorValor = arranjo_SegundoMaior(n, arranjo, maiorValor);

    // Exibir o segundo maior valor
    printf("Segundo maior valor: %d\n", segundoMaiorValor);
 

}
void atividade4 ()
{

// Ler o arranjo do arquivo "DADOS1.TXT"
    char* arquivoEntrada1 = "DADOS1.TXT";
    int n1 = readArraySize(arquivoEntrada1);
    int arranjo1[n1];
    freadIntArray(arquivoEntrada1, n1, arranjo1);

    // Ler o arranjo do arquivo "DADOS2.TXT"
    char* arquivoEntrada2 = "DADOS2.TXT";
    int n2 = readArraySize(arquivoEntrada2);
    int arranjo2[n2];
    freadIntArray(arquivoEntrada2, n2, arranjo2);

    // Filtrar os elementos comuns aos dois arranjos
    int arranjo3[n1 + n2]; // O tamanho máximo possível é a soma dos tamanhos dos arranjos
    arranjo_filtrar(n1, arranjo1, n2, arranjo2, arranjo3);

    // Gravar o resultado no arquivo "FILTRADOS.TXT"
    char* arquivoSaida = "FILTRADOS.TXT";
    fprintIntArray(arquivoSaida, n1 + n2, arranjo3);

    printf("Elementos filtrados gravados em \"%s\"\n", arquivoSaida);

}
void atividade5 ()
{
 // Ler as cadeias de caracteres do arquivo "BINARIOS1.TXT"
    char* arquivoEntrada = "BINARIOS1.TXT";
    FILE* arquivo = fopen(arquivoEntrada, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo \"%s\"\n", arquivoEntrada);
        return 1;
    }

    char linha[STR_SIZE];
    int arranjo[STR_SIZE];
    int contador = 0;

    while (fgets(linha, STR_SIZE, arquivo) != NULL) {
        int valor = atoi(linha);

        if (valor == 0 || valor == 1) {
            arranjo[contador] = valor;
            contador++;
        }
    }

    fclose(arquivo);

    // Converter o arranjo para decimal
    int decimal = arranjo_paraDecimal(contador, arranjo);

    printf("Decimal: %d\n", decimal);

}
void atividade6 ()
{
       const char* nomeArquivoEntrada = "MATRIZ1.TXT";
    const char* nomeArquivoSaida = "MATRIZ2.TXT";
    int tamanho;

    // Ler dados do arquivo MATRIZ1.TXT
    int linhas = freadMatrixRows(nomeArquivoEntrada);
    int colunas = freadMatrixColumns(nomeArquivoEntrada);
    int matriz[linhas][colunas];
    freadIntMatrix(nomeArquivoEntrada, linhas, colunas, matriz);

    // Solicitar ao usuário o tamanho da matriz quadrada
    printf("Informe o tamanho da matriz quadrada: ");
    scanf("%d", &tamanho);

    // Criar uma matriz tridiagonal com valores crescentes
    int tridiagonal[tamanho][tamanho];
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i == j) {
                tridiagonal[i][j] = matriz[i][j];
            } else if (i == j - 1 || i == j + 1) {
                tridiagonal[i][j] = matriz[i][j];
            } else {
                tridiagonal[i][j] = 0;
            }
        }
    }

    // Exibir a matriz tridiagonal
    printf("Matriz Tridiagonal:\n");
    printIntMatrix(tamanho, tamanho, tridiagonal);

    // Gravar a matriz tridiagonal no arquivo MATRIZ2.TXT
    fprintIntMatrix(nomeArquivoSaida, tamanho, tamanho, tridiagonal);

    printf("Matriz tridiagonal foi gravada no arquivo %s\n", nomeArquivoSaida);

}
void atividade7 ()
{
   const char* inputFileName = "MATRIZ1.TXT";
    const char* outputFileName = "MATRIZ2.TXT";
    int size;

    // Ler dados do arquivo MATRIZ1.TXT
    int rows = freadMatrixRows(inputFileName);
    int columns = freadMatrixColumns(inputFileName);
    int matrix[rows][columns];
    freadIntMatrix(inputFileName, rows, columns, matrix);

    // Solicitar ao usuário o tamanho da matriz quadrada
    printf("Informe o tamanho da matriz quadrada: ");
    scanf("%d", &size);

    // Criar e preencher a matriz tridiagonal decrescente
    int tridiagonal[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j || i == j - 1 || i == j + 1) {
                tridiagonal[i][j] = matrix[i][j];
            } else {
                tridiagonal[i][j] = 0;
            }
        }
    }

    // Exibir a matriz tridiagonal
    printf("Matriz Tridiagonal:\n");
    printIntMatrix(size, size, tridiagonal);

    // Gravar a matriz tridiagonal no arquivo MATRIZ2.TXT
    fprintIntMatrix(outputFileName, size, size, tridiagonal);

    printf("Matriz tridiagonal foi gravada no arquivo %s\n", outputFileName);

}
void atividade8 ()
{
   const char* inputFileName = "MATRIZ3.TXT";

    // Ler a matriz do arquivo MATRIZ3.TXT
    int rows = freadMatrixRows(inputFileName);
    int columns = freadMatrixColumns(inputFileName);
    int matrix[rows][columns];
    freadIntMatrix(inputFileName, rows, columns, matrix);

    // Verificar se a matriz tem a característica de potências por linha
    int hasPower = hasPowerRows(rows, columns, matrix);

    // Exibir resultado
    if (hasPower) {
        printf("A matriz tem a caracteristica de potencias por linha.\n");
    } else {
        printf("A matriz nao tem a caracteristica de potencias por linha.\n");
    }

}
void atividade9 ()
{
   const char* inputFileName = "MATRIZ4.TXT";

    // Ler a matriz do arquivo MATRIZ4.TXT
    int rows = freadMatrixRows(inputFileName);
    int columns = freadMatrixColumns(inputFileName);
    int matrix[rows][columns];
    freadIntMatrix(inputFileName, rows, columns, matrix);

    // Verificar se a matriz tem a característica de potências por coluna
    int hasPower = hasPowerColumns(rows, columns, matrix);

    // Exibir resultado
    if (hasPower) {
        printf("A matriz tem a caracteristica de potencias por coluna.\n");
    } else {
        printf("A matriz nao tem a caracteristica de potencias por coluna.\n");
    }

}
void atividade10 ()
{
   const char* inputFileName = "DADOS3.TXT";

    // Abrir o arquivo para leitura
    FILE* arquivo = fopen(inputFileName, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler o número de supermercados
    int n;
    fscanf(arquivo, "%d", &n);

    // Verificar se o número de supermercados é válido
    if (n <= 0) {
        printf("Número inválido de supermercados.\n");
        fclose(arquivo);
        return 1;
    }

    // Alocar memória para o vetor de supermercados
    Supermercado* supermercados = (Supermercado*)malloc(n * sizeof(Supermercado));
    if (supermercados == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return 1;
    }

    // Ler os dados de cada supermercado
    for (int i = 0; i < n; i++) {
        fscanf(arquivo, "%s %d %lf", supermercados[i].nome, &supermercados[i].codigo, &supermercados[i].preco);
    }

    // Calcular o preço médio
    double precoMedio = calcularPrecoMedio(n, supermercados);

    // Exibir supermercados com preços inferiores à média
    int contador = 0;
    printf("Supermercados com preços inferiores à média:\n");
    for (int i = 0; i < n; i++) {
        if (supermercados[i].preco < precoMedio) {
            printf("Supermercado: %s (Código: %d)\n", supermercados[i].nome, supermercados[i].codigo);
            contador++;
        }
    }

    // Verificar se foram encontrados pelo menos dois supermercados com preços inferiores à média
    if (contador < 2) {
        printf("Não foram encontrados pelo menos dois supermercados com preços inferiores à média.\n");
    }

    // Liberar memória e fechar o arquivo
    free(supermercados);
    fclose(arquivo);
}