
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(){

int arranjo[10] ;
int zero = 0 ;

for(int x = 0 ; x < 10  ; x++)
{

    printf("digite um numero:");
    scanf("%i" , &arranjo[x]);

if (arranjo[x] == 0) zero++;


}

printf("total de zeros no arranjo e: %i" , zero);




return 0 ;
}
