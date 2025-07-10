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


//-------------------------------------------------------------------
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
 


//-------------------------------------------------------------------
typedef struct Lista {
    Celula* primeiro;
    Celula* ultimo;
} Lista;


void start(Lista* lista) {
    Show *sentinela = (Show*) malloc(sizeof(Show));
    strcpy(sentinela->show_id, ""); // ou "NaN", se preferir
    sentinela->castLength = 0;
    sentinela->listedLength = 0;
    // você pode inicializar outros campos se quiser

    lista->primeiro = novaCelula(sentinela);
    lista->ultimo = lista->primeiro;
}



//-------------------------------------------------------------------


void inserirInicio(Show *x, Lista* lista) {
   Celula* tmp = novaCelula(x);
   tmp->prox = lista->primeiro->prox;
   lista->primeiro->prox = tmp;
   if (lista->primeiro == lista->ultimo) {                    
      lista->ultimo = tmp;
   }
   tmp = NULL;
}


void inserirFim(Show *x, Lista* lista) {
   lista->ultimo->prox = novaCelula(x);
   lista->ultimo = lista->ultimo->prox;
}


Show* removerInicio(Lista* lista) {
   if (lista->primeiro == lista->ultimo) {
      printf("erro remoção invalida!!!");
   }

    Celula* tmp = lista->primeiro->prox;
    Show* resp = tmp->elemento;
    lista->primeiro->prox = tmp->prox;
    if (tmp == lista->ultimo) lista->ultimo = lista->primeiro;
    free(tmp);
    return resp;

}


void removerFim(Lista* lista) {
   if (lista->primeiro == lista->ultimo) {
      printf("erro remoção invalida!!!");
   } 

   // Caminhar ate a penultima celula:
   Celula* i;
   for(i = lista->primeiro; i->prox != lista->ultimo; i = i->prox);

   Show *resp = lista->ultimo->elemento;
   lista->ultimo = i;
   free(lista->ultimo->prox);
   i = lista->ultimo->prox = NULL;

}

int tamanho(Lista* lista) {
   int tamanho = 0;
   Celula* i;
   for(i = lista->primeiro; i != lista->ultimo; i = i->prox, tamanho++);
   return tamanho;
}

//------------------------------------------------------------------------------------------------------------

Show* removerInicioParaInserirRemovidos(Lista* lista, Lista* removidos) {
   if (lista->primeiro == lista->ultimo) {
      printf("erro remoção invalida!!!");
   }

    Celula* tmp = lista->primeiro->prox;
    Show* resp = tmp->elemento;
    inserirFim(resp, removidos);
    lista->primeiro->prox = tmp->prox;
    if (tmp == lista->ultimo) lista->ultimo = lista->primeiro;
    free(tmp);
    return resp;

}


void removerFimParaInserirRemovidos(Lista* lista, Lista* removidos) {
   if (lista->primeiro == lista->ultimo) {
      printf("erro remoção invalida!!!");
   } 

   // Caminhar ate a penultima celula:
   Celula* i;
   for(i = lista->primeiro; i->prox != lista->ultimo; i = i->prox);

   Show *resp = lista->ultimo->elemento;
   inserirFim(resp, removidos);
   lista->ultimo = i;
   free(lista->ultimo->prox);
   i = lista->ultimo->prox = NULL;

}

Show* removerParaInserirRemovidos(Lista* lista , int pos, Lista* removidos) {

   int tam = tamanho(lista);
   Show *resp;
   if (lista->primeiro == lista->ultimo){
     printf("erro pos invalida!!!");
   } else if(pos < 0 || pos >= tam){
      printf("erro pos invalida!!!");
   } else if (pos == 0){
       removerInicioParaInserirRemovidos(lista, removidos);
   } else if (pos == tam - 1){
       removerFimParaInserirRemovidos(lista, removidos);
   } else {
      // Caminhar ate a posicao anterior a insercao
      Celula* i = lista->primeiro;
      int j;
      for(j = 0; j < pos; j++, i = i->prox);

      Celula* tmp = i->prox;
      resp = tmp->elemento;
      inserirFim(resp, removidos);
      i->prox = tmp->prox;
      tmp->prox = NULL;
      free(tmp);
      i = tmp = NULL;
   }
}


//------------------------------------------------------------------------------------------------------------




void inserir(int pos, Show *x, Lista* lista){

   int tam = tamanho( lista);

   if(pos < 0 || pos > tam){
      printf("erro pos invalida!!!");
   } else if (pos == 0){
      inserirInicio(x, lista);
   } else if (pos == tam){
      inserirFim(x, lista);
   } else {
      // Caminhar ate a posicao anterior a insercao
      int j;
      Celula* i = lista->primeiro;
      for(j = 0; j < pos; j++, i = i->prox);

      Celula* tmp = novaCelula(x);
      tmp->prox = i->prox;
      i->prox = tmp;
      tmp = i = NULL;
   }
}



Show* remover(Lista* lista , int pos) {

   int tam = tamanho(lista);

   if (lista->primeiro == lista->ultimo){
     printf("erro pos invalida!!!");
   } else if(pos < 0 || pos >= tam){
      printf("erro pos invalida!!!");
   } else if (pos == 0){
       removerInicio(lista);
   } else if (pos == tam - 1){
       removerFim(lista);
   } else {
      // Caminhar ate a posicao anterior a insercao
      Celula* i = lista->primeiro;
      int j;
      for(j = 0; j < pos; j++, i = i->prox);

      Celula* tmp = i->prox;
      i->prox = tmp->prox;
      tmp->prox = NULL;
      free(tmp);
      i = tmp = NULL;
   }
}

void imprimir(Lista *lista) {
    Celula *i;
    for (i = lista->primeiro->prox; i != NULL; i = i->prox) {
        Show *s = i->elemento;
        printf("=> %s ## %s ## %s ## %s ## ",
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
    }
}


void imprimirremovidos(Lista *lista) {
    Celula *i;
    for (i = lista->primeiro->prox; i != NULL; i = i->prox) {
        Show *s = i->elemento;
        printf("(R) %s\n",*s->title ? s->title : "NaN");
    }
}




//------------------------------------------------------------------------------------------

int main()
{
    readCSV();
    Lista removidos;
    start(&removidos);
    Lista lista;
    start(&lista);

    char input[100];
    char Ids[5000][100];
    char Titulos[5000][100];
    int numTitulos = 0;

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\r\n")] = 0;
    removeEspacos(input);

    while (strcmp(input, "FIM") != 0) {
        Show *s = buscaId(input);
        if (s != NULL) {
            strcpy(Ids[numTitulos], s->show_id);
            strcpy(Titulos[numTitulos], s->title);
            inserirFim(s, &lista);
            numTitulos++;
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

        if (strncmp(linha, "II", 2) == 0) {
            char id[20];
            sscanf(linha, "II %s", id);
             Show *s = buscaId(id);
             inserirInicio(s, &lista);
            
        } else if (strncmp(linha, "IF", 2) == 0) {
            char id[20];
            sscanf(linha, "IF %s", id);
             Show *s = buscaId(id);
             inserirFim(s, &lista);
            
            
        } else if (strncmp(linha, "I*", 2) == 0) {
            int pos;
            char id[20];
            sscanf(linha, "I* %d %s", &pos, id);
            Show *s = buscaId(id);
            if (s != NULL) {
                strcpy(Ids[numTitulos], s->show_id);
                strcpy(Titulos[numTitulos], s->title);
                inserir(pos, s, &lista);
            }
            
        } else if (strcmp(linha, "RI") == 0) {
            removerInicioParaInserirRemovidos(&lista, &removidos);
            
        } else if (strcmp(linha, "RF") == 0) {
            removerFimParaInserirRemovidos(&lista, &removidos);
            
        } else if (strncmp(linha, "R*", 2) == 0) {
            int pos;
            sscanf(linha, "R* %d", &pos);
            removerParaInserirRemovidos(&lista, pos, &removidos);
            
        } else {
            printf("Comando inválido: %s\n", linha);
        }
    }
    
    
    imprimirremovidos(&removidos);
    imprimir(&lista);

    return 0;
}