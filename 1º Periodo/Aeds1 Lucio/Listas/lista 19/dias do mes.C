#include <stdio.h>
#include <stdlib.h>

int main()
{
    int meses[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int m;

    printf ("mes [1...12]");
    scanf("%i" , &m);



    printf("o mes %i tem  %i dias" , m, meses[m]);
    }
