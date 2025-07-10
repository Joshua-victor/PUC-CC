#include <stdio.h>



//metodo 1

void mostrarC(int n)
{
    
    
  if(n>0 ){
      
      
      int num = 6 * n;
      printf("%d " , num);
      n--;
      mostrarC(n);
  }  
}
    

int main()
{
   
   int n = 0;
   
  printf("digite quantos termos voce deseja:");
  scanf("%d" , &n);
  mostrarC(n);
   
   
   
}
