#include <stdio.h>



//metodo 1

void mostrarC(int n, int count)
{
    
    
  if(n>0){
      
      int num = 6+(count*2);
      printf("%d " , num);
      
      
      count++;
      n--;
      mostrarC(n,count);
  }  
}
    

int main()
{
   
   int n = 0;
   
  printf("digite quantos termos voce deseja:");
  scanf("%d" , &n);
  mostrarC(n,0);
   
   
   
}
