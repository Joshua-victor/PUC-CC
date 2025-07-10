#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matriz[3][3];
    int numLin = 3, numCol = 3;


    for(int i = 0 ; i < numLin; i++)
    {


        for(int j = 0 ; j < numCol; j++)
        {

            printf("digite o numero da matriz:");
            scanf("%i", &matriz[i][j]);

        }

    }


    for (int i = 0 ; i< numLin ; i++)
    {


        for (int j = 0; j < numCol ; j++)
        {


            printf("%i\t",  matriz[i][j]);





        }
        printf("\n");
    }


}
