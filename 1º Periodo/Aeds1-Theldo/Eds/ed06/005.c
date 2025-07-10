#include <stdio.h>



//metodo 5

void mostrarC(int n, int cout, int soma )
{
    
    
  if(n>0 ){
      
      
      int num = 6 + cout ;
      
      printf ("%d " , num);
      n--;
      cout = cout + 6;
      soma = soma + num;
       if( n>0){
      printf("+ 6 = ");
  }
   else {
       printf(".");
   }
      mostrarC(n, cout, soma);
      
  
      
  }  
 
  
}
    

int main()
{
   
   int n = 0;
   
  printf("digite quantos termos voce deseja:");
  scanf("%d" , &n);
  mostrarC(n, 0, 0 );
   
   
   
}


