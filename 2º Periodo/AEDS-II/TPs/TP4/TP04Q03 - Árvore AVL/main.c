#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

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


void removeEspaços(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

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
        while (*token == ' ')
            token++;
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

void removeAspas(char *str)
{
    char *src = str, *dst = str;
    while (*src)
    {
        if (src[0] == '"' && src[1] == '"')
        {
            src += 2;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
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
            if (*ptr == ',')
                ptr++;
        }
        removeEspaços(fields[i]);
        removeAspas(fields[i]);
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

    char tmpCast[500];
    strncpy(tmpCast, fields[4], 499);
    tmpCast[499] = '\0';
    split(tmpCast, s.cast, &s.castLength);

    copyOrNaN(s.country, fields[5]);
    copyOrNaN(s.date_added, fields[6]);
    s.release_year = atoi(fields[7]);
    copyOrNaN(s.rating, fields[8]);
    copyOrNaN(s.duration, fields[9]);

    char tmpListed[500];
    strncpy(tmpListed, fields[10], 499);
    tmpListed[499] = '\0';
    split(tmpListed, s.listed_in, &s.listedLength);

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

    if (!fgets(line, 1024, fp))
    {
        fclose(fp);
        return;
    }

    while (fgets(line, 1024, fp))
    {
        line[strcspn(line, "\r\n")] = 0;
        shows[showsLength++] = Ler(line);
        if (showsLength >= 5000)
            break;
    }

    fclose(fp);
}

typedef struct AVLNode
{
    Show *show;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

AVLNode *newNode(Show *show)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->show = show;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

long long comparacoes = 0;

int cmpTitles(const char *a, const char *b)
{
    return strcmp(a, b);
}

AVLNode *insertAVL(AVLNode *node, Show *show)
{
    if (node == NULL)
        return newNode(show);

    comparacoes++;
    int cmp = cmpTitles(show->title, node->show->title);

    if (cmp < 0)
        node->left = insertAVL(node->left, show);
    else if (cmp > 0)
        node->right = insertAVL(node->right, show);
    else
        return node; 

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && cmpTitles(show->title, node->left->show->title) < 0)
        return rightRotate(node);

    if (balance < -1 && cmpTitles(show->title, node->right->show->title) > 0)
        return leftRotate(node);

    if (balance > 1 && cmpTitles(show->title, node->left->show->title) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && cmpTitles(show->title, node->right->show->title) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool buscaAVL(AVLNode *node, const char *title, char *pathBuffer)
{
    if (node == NULL)
    {
        strcat(pathBuffer, " NAO");
        return false;
    }

    comparacoes++;
    int cmp = strcmp(title, node->show->title);
    if (cmp == 0)
    {
        strcat(pathBuffer, " SIM");
        return true;
    }
    else if (cmp < 0)
    {
        strcat(pathBuffer, " esq");
        return buscaAVL(node->left, title, pathBuffer);
    }
    else
    {
        strcat(pathBuffer, " dir");
        return buscaAVL(node->right, title, pathBuffer);
    }
}


int main()
{
    clock_t start = clock();

    readCSV();

    AVLNode *root = NULL;

    char input[100];

    while (true)
    {
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\r\n")] = 0;
        removeEspaços(input);
        if (strcmp(input, "FIM") == 0)
            break;

        Show *s = buscaId(input);
        if (s != NULL)
            root = insertAVL(root, s);
    }

    while (true)
    {
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\r\n")] = 0;
        removeEspaços(input);
        if (strcmp(input, "FIM") == 0)
            break;

        char path[1000] = "raiz";
        buscaAVL(root, input, path);
        printf("%s\n", path);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    FILE *logFile = fopen("789339_avl.txt", "w"); 
    if (logFile)
    {
        fprintf(logFile, "789339\t%.6f\t%lld\n", time_taken, comparacoes);
        fclose(logFile);
    }
    else
    {
        perror("Erro ao abrir arquivo de log");
    }

    return 0;
}
