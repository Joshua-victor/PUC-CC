area do circulo

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>



int main()
{
    
   printf("area do circulo\n");
   
   int area;
   int raio;
   int pi = 3.14;
   
   
   printf ("digite o raio do circulo");
   scanf("%i", &raio);
   area = pi  * pow (raio ,2);
   
   printf("a area do circulo e de  %i", area);
  
  
  
    

    return 0;
}
