#include <stdio.h>



//metodo 1

void mostrarC(int n ,int m)
{
    
    
  if(n>0 ){
      
      
      int num = 6 * m;
      printf("%d " , num);
      n--;
      m++;
      
      mostrarC(n , m);
  }  
}
    

int main()
{
   
   int n = 0;
   
  printf("digite quantos termos voce deseja:");
  scanf("%d" , &n);
  mostrarC(n, 0);
   
   
   
}


// obs: Theldo, não consegui fazer o programa começar com no número "1" ao invés do "0"


