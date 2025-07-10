#include <stdio.h>



//metodo 6

void mostrarC(int n, int cout, int soma )
{
    
    
  if(n>0 ){
      
      
      int num = 6 + cout ;
      
      printf ("1/%d " , num);
     
      cout = cout + 6;
      soma = soma + num;
       if( n>0){
      printf("+ 6 = " , n);
       n--;
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


