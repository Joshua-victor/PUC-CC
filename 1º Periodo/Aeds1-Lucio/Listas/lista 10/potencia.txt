#include <stdio.h>
#include <math.h>

int main()
{
    printf("potencia\n");
    
    int numero;
    int potencia;
    int rest = 1;
    
    printf("digite a base do numero:");
    scanf("%i" , &numero);
    
    printf("digite a potencia:");
    scanf("%i" , &potencia);

  
  for (int x = 0 ; x < potencia ; x++){
      
        rest *= numero; // rest = rest * numero
      
        if(potencia == 0) // Qualquer numero elevado a 0 é igual 1
        {
            rest = 1;
        }
      
      
  }
  
  printf("%i elevado a %i = %i" , numero , potencia , rest);
  
  
  
  
  
  
  
  
    return 0;
}
