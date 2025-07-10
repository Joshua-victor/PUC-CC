#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool leMatriz( int  matrizA[3][3],  int  numCol, int numLin );
int main()
{
    int matrizA[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int numCol = 3, numLin = 3;
 leMatriz(  matrizA[3][3],   numCol,  numLin );
    
     
}

bool leMatriz( int  matrizA[3][3],  int  numCol, int numLin )
{
    int i, j;
    bool vdd = true;
    int soma1 = 0 ,soma2 = 0 ;

    for(i=0 ; i< numLin ; i++)
    {
        for(j = 0 ; j< numCol ; j++)
        {

        if (i == 0 ) soma1  = matrizA[i][j] +soma1 ;
            if (i == 2) soma2 = matrizA[i][j] + soma2;
               if ( soma1 != soma2) vdd = false;

        }
    }


return vdd;
}
