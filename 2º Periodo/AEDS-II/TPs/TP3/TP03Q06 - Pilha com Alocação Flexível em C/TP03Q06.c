#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//-------------------------------------------------------------------

typedef struct Show
{
    char show_id[100];
    char type[100];
    char title[100];
    char director[100];
    char cast[50][100];
    int castLength;
    char country[100];
    char date_added[100];
    int release_year;
    char rating[100];
    char duration[100];
    char listed_in[50][100];
    int listedLength;
} Show;

Show shows[5000];
int showsLength = 0;

// Funções auxiliares
void removeEspacos(char *str)
{
    char *end;
    while (isspace((unsigned char)*str)) str++;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

void copyOrNaN(char *dest, const char *src)
{
    strncpy(dest, (strlen(src) > 0 ? src : "NaN"), 100);
    dest[99] = '\0';
}

void split(char *src, char dest[50][100], int *count)
{
    *count = 0;
    if (strlen(src) == 0)
    {
        strcpy(dest[(*count)++], "NaN");
        return;
    }

    char *token = strtok(src, ",");
    while (token != NULL && *count < 50)
    {
        while (*token == ' ') token++;
        strncpy(dest[*count], token, 100);
        dest[*count][99] = '\0';
        (*count)++;
        token = strtok(NULL, ",");
    }

    if (*count == 0)
    {
        strcpy(dest[(*count)++], "NaN");
    }
}

int compareStrings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void ordena(char list[50][100], int length)
{
    if (length == 1 && strcmp(list[0], "NaN") == 0)
    {
        printf("[NaN");
        return;
    }

    char *tempPtrs[50];
    for (int i = 0; i < length; i++)
        tempPtrs[i] = list[i];

    qsort(tempPtrs, length, sizeof(char *), compareStrings);

    printf("[");
    for (int i = 0; i < length; i++)
    {
        printf("%s", tempPtrs[i]);
        if (i < length - 1)
            printf(", ");
    }
   
}

void mostrar(Show *s)
{
    printf("=> %s ## %s ## %s ## %s ## ",
           *s->show_id ? s->show_id : "NaN",
           *s->title ? s->title : "NaN",
           *s->type ? s->type : "NaN",
           *s->director ? s->director : "NaN");

    ordena(s->cast, s->castLength);

    printf(" ## %s ## %s ## %d ## %s ## %s ## ",
           *s->country ? s->country : "NaN",
           *s->date_added ? s->date_added : "NaN",
           s->release_year,
           *s->rating ? s->rating : "NaN",
           *s->duration ? s->duration : "NaN");

    ordena(s->listed_in, s->listedLength);
    printf(" ##\n");
}

int linhaCSV(char *line, char fields[20][100])
{
    int i = 0;
    char *ptr = line;
    while (*ptr && i < 20)
    {
        if (*ptr == '"')
        {
            ptr++;
            char *start = ptr;
            while (*ptr && !(ptr[0] == '"' && (ptr[1] == ',' || ptr[1] == '\0' || ptr[1] == '\n')))
                ptr++;
            int len = ptr - start;
            strncpy(fields[i], start, len);
            fields[i][len] = '\0';
            ptr += (*ptr == '"') ? 2 : 1;
        }
        else
        {
            char *start = ptr;
            while (*ptr && *ptr != ',')
                ptr++;
            int len = ptr - start;
            strncpy(fields[i], start, len);
            fields[i][len] = '\0';
            if (*ptr == ',') ptr++;
        }
        removeEspacos(fields[i]);
        i++;
    }
    return i;
}

Show Ler(char *line)
{
    Show s;
    char fields[20][100];
    linhaCSV(line, fields);

    copyOrNaN(s.show_id, fields[0]);
    copyOrNaN(s.type, fields[1]);
    copyOrNaN(s.title, fields[2]);
    copyOrNaN(s.director, fields[3]);
    split(fields[4], s.cast, &s.castLength);
    copyOrNaN(s.country, fields[5]);
    copyOrNaN(s.date_added, fields[6]);
    s.release_year = atoi(fields[7]);
    copyOrNaN(s.rating, fields[8]);
    copyOrNaN(s.duration, fields[9]);
    split(fields[10], s.listed_in, &s.listedLength);

    return s;
}

Show *buscaId(char *id)
{
    for (int i = 0; i < showsLength; i++)
    {
        if (strcmp(shows[i].show_id, id) == 0)
        {
            return &shows[i];
        }
    }
    return NULL;
}

void readCSV()
{
    FILE *fp = fopen("/tmp/disneyplus.csv", "r");
    if (!fp)
    {
        perror("Erro");
        exit(1);
    }

    char line[1024];
    fgets(line, 1024, fp); // Pula cabeçalho

    while (fgets(line, 1024, fp))
    {
        line[strcspn(line, "\r\n")] = 0;
        shows[showsLength++] = Ler(line);
        if (showsLength >= 5000)
            break;
    }

    fclose(fp);
}


//****************************************** Celula e pilha ***********************************************************************************


typedef struct Celula {
	struct Show* elemento;        // Elemento inserido na celula.
	struct Celula* prox; // Aponta a celula prox.
} Celula;

Celula* novaCelula(Show *elemento) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->elemento = elemento; // agora ambos são ponteiros
    nova->prox = NULL;
    return nova;
}
 

typedef struct Pilha {
    Celula* topo;
    
} Pilha;


void start(Pilha* pilha) {
    Show *sentinela = (Show*) malloc(sizeof(Show));
    strcpy(sentinela->show_id, "NaN"); 
    sentinela->castLength = 0;
    sentinela->listedLength = 0;

    pilha->topo = NULL;
    
}


//******************************************** Celula e pilha ***********************************************************************************

void inserirFim(Show *x, Pilha* pilha) {
 
   Celula* tmp = novaCelula(x);
   tmp->prox = pilha->topo;
   pilha->topo = tmp;
   tmp = NULL;
   
}

void removerFim(Pilha* pilha) {
   if (pilha->topo == NULL) {
      printf("erro remoção invalida!!!");
   } 
   
   Show *resp = pilha->topo->elemento;
   Celula* tmp = pilha->topo;
   pilha->topo = pilha->topo->prox;
   tmp->prox = NULL;
   free(tmp);
   tmp = NULL;
   
}

int tamanho(Pilha* pilha) {
   int tamanho = 0;
   Celula* i;
   for(i = pilha->topo; i != NULL; i = i->prox, tamanho++);
   return tamanho;
}

//------------------------------------------------------------------------------------------------------------

void removerFimParaInserirRemovidos(Pilha* pilha, Pilha* removidos) {
    if (pilha->topo == NULL) {
      printf("erro remoção invalida!!!");
   } 

   Show *resp = pilha->topo->elemento;
   inserirFim(resp, removidos);
   Celula* tmp = pilha->topo;
   pilha->topo = pilha->topo->prox;
   tmp->prox = NULL;
   free(tmp);
   tmp = NULL;
   

}
//------------------------------------------------------------------------------------------------------------



void imprimir(Pilha *pilha, int quant) {
    Celula *i;
    for (i = pilha->topo; i != NULL; i = i->prox) {
        Show *s = i->elemento;
        printf("[%d] => %s ## %s ## %s ## %s ## ", quant,
               *s->show_id ? s->show_id : "NaN",
               *s->title ? s->title : "NaN",
               *s->type ? s->type : "NaN",
               *s->director ? s->director : "NaN");

       ordena(s->cast, s->castLength);
        

        printf("] ## %s ## %s ## %d ## %s ## %s ## ",
               *s->country ? s->country : "NaN",
               *s->date_added ? s->date_added : "NaN",
               s->release_year,
               *s->rating ? s->rating : "NaN",
               *s->duration ? s->duration : "NaN");

        ordena(s->listed_in, s->listedLength);
        printf("] ##\n");
        quant--;
    }
}


void imprimirremovidos(Pilha *pilha) {
    Celula *i = pilha->topo;
    int tamanho = 0;

    // Conta os elementos
    while (i != NULL) {
        tamanho++;
        i = i->prox;
    }

    // Cria vetor para armazenar os ponteiros
    Celula **vetor = (Celula **) malloc(tamanho * sizeof(Celula *));
    i = pilha->topo;
    for (int j = 0; j < tamanho; j++) {
        vetor[j] = i;
        i = i->prox;
    }

    // Imprime do fim para o início
    for (int j = tamanho - 1; j >= 0; j--) {
        Show *s = vetor[j]->elemento;
        printf("(R) %s\n", *s->title ? s->title : "NaN");
    }

    free(vetor);
}





//------------------------------------------------------------------------------------------

int main()
{
    readCSV();
    Pilha removidos;
    start(&removidos);
    Pilha pilha;
    start(&pilha);

    char input[100];
    char Ids[5000][100];
    char Titulos[5000][100];
    int numTitulos = 0;
    int quant = 0;

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\r\n")] = 0;
    removeEspacos(input);

    while (strcmp(input, "FIM") != 0) {
        Show *s = buscaId(input);
        if (s != NULL) {
            strcpy(Ids[numTitulos], s->show_id);
            strcpy(Titulos[numTitulos], s->title);
            inserirFim(s, &pilha);
            numTitulos++;
            quant++;
        } else {
            printf("não encontrado\n");
        }

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\r\n")] = 0;
        removeEspacos(input);
    }

    
    int n;
    scanf("%d", &n);
    getchar(); // consumir o '\n'

    char linha[100];

    for (int i = 0; i < n; i++) {
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = 0; // remover o '\n'

         if (strncmp(linha, "I", 1) == 0) { // comparação para verificar se vai inserir
            char id[20];
            sscanf(linha, "I %s", id);
             Show *s = buscaId(id);
             inserirFim(s, &pilha);
            
        }  else if (strcmp(linha, "R") == 0) {// comparação para verificar se vai remover
            removerFimParaInserirRemovidos(&pilha, &removidos);
            
            
        }  else {
            printf("Comando inválido: %s\n", linha);
        }
    }
    
    
    imprimirremovidos(&removidos);
    imprimir(&pilha, quant- 2);

    return 0;
}