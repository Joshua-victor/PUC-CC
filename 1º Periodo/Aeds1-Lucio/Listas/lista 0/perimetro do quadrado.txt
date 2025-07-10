#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>



int main()
{
    
   printf("perimetro de um quadrado\n");
   
   int perimetro;
   int lado;
   
   
   
   printf ("digite o lado do quadrado");
   scanf("%i", &lado);
   perimetro = lado * 4;
   
   printf("o perimetro do quadrado e de %i", perimetro);
  
  
  
    

    return 0;
}
