#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int matriz[4][4]= {{1,2,3,-4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    int i, j;
    int maior = 0;

    int soma = 0;




    for(i = 0 ; i < 4; i++)
    {

        for(j = 0 ; j< 4; j++)
        {

            if (j>i) soma = soma + matriz[i][j];       //soma todos os elementos acima da diagonal principal
            if (j>i && matriz[i][j] > 0 ) maior++;    //soma todos os numeros possitivos acima da diagonal principal


        }
    }

    printf("%i , %i ", soma,  maior);

    return 0;
}
