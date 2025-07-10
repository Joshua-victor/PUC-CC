#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
        printf("[NaN]");
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
    printf("]");
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

int mesParaNumero(char *mes) {
    if (strcmp(mes, "January") == 0) return 1;
    if (strcmp(mes, "February") == 0) return 2;
    if (strcmp(mes, "March") == 0) return 3;
    if (strcmp(mes, "April") == 0) return 4;
    if (strcmp(mes, "May") == 0) return 5;
    if (strcmp(mes, "June") == 0) return 6;
    if (strcmp(mes, "July") == 0) return 7;
    if (strcmp(mes, "August") == 0) return 8;
    if (strcmp(mes, "September") == 0) return 9;
    if (strcmp(mes, "October") == 0) return 10;
    if (strcmp(mes, "November") == 0) return 11;
    if (strcmp(mes, "December") == 0) return 12;
    return 0;
}

void normalizarData(char *dataOriginal, char *dataNormalizada) {
    char mes[20];
    int dia, ano;
    sscanf(dataOriginal, "%s %d, %d", mes, &dia, &ano);
    int mesNum = mesParaNumero(mes);
    sprintf(dataNormalizada, "%04d-%02d-%02d", ano, mesNum, dia);
}




void bubble(char datas[][100], char Titulos[][100], char Ids[][100], int num) {
    char tempData[100];
    char tempTitulo[100];
    char tempId[100];

    for (int i = num - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            int cmpData = strcmp(datas[j], datas[j + 1]);

            if (cmpData > 0 || (cmpData == 0 && strcmp(Titulos[j], Titulos[j + 1]) > 0)) {
                // Troca datas
                strcpy(tempData, datas[j]);
                strcpy(datas[j], datas[j + 1]);
                strcpy(datas[j + 1], tempData);

                // Troca títulos
                strcpy(tempTitulo, Titulos[j]);
                strcpy(Titulos[j], Titulos[j + 1]);
                strcpy(Titulos[j + 1], tempTitulo);

                // Troca IDs
                strcpy(tempId, Ids[j]);
                strcpy(Ids[j], Ids[j + 1]);
                strcpy(Ids[j + 1], tempId);
            }
        }
    }
}




int main()
{
    readCSV();

    char input[100];
    char Ids[5000][100];
    char Titulos[5000][100];
    char datas[5000][100];
    int numTitulos = 0;
    int numdatas = 0;

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\r\n")] = 0;
    removeEspacos(input);

    while (strcmp(input, "FIM") != 0) {
        Show *s = buscaId(input);
        if (s != NULL) {
            strcpy(Ids[numTitulos], s->show_id);
            strcpy(Titulos[numTitulos], s->title);
            char dataConvertida[100];
            normalizarData(s->date_added, dataConvertida);
            strcpy(datas[numdatas], dataConvertida);

            
            numTitulos++;
            numdatas++;
        } else {
            printf("não encontrado\n");
        }

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\r\n")] = 0;
        removeEspacos(input);
    }
    
    

    
    
    bubble(datas, Titulos, Ids, numdatas);
   

    for (int i = 0; i < numTitulos; i++) {
        Show *s = buscaId(Ids[i]);
        if (s != NULL) {
            mostrar(s);
        }
    }
    
    
        

        
        
        
    
    

    return 0;
}