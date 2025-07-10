votaçao da turma

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>



int main()
{
    
   printf ("0 – Sair do Programa\n"); 
  printf ("1 – Chapa 1\n"); 
  printf("2 – Chapa 2\n");
  printf("3 – Voto em branco/nulo\n"); 
  
  int voto;
  bool erro;
  int turma;
  int chapa1 = 0;
  int chapa2 = 0;
  int nulo = 0;
  char decisao;
  
  
  do{
  printf("quantos alunos tem?");
  scanf(" %i", &turma);
  erro = turma <= 0 ;
  if (erro) puts("numero invalido!");
  
  
  for (int x = 0; x < turma ; x++){
  do{
  printf("qual o seu voto?");
  scanf(" %i", &voto);
  erro = (!(voto >= 0 && voto <= 3 ));
  if(erro) puts("voto invalido");
  }while (erro);
  
   if(voto == 1) chapa1++;
    else if (voto == 2) chapa2++;
      else if (voto == 3) nulo++;
  
  } 
  
 
      if (chapa1 > chapa2){ 
      printf ("a chapa 1 ganhou com %i votos\n" , chapa1);
      printf ("chapa 2 com %i votos\n" , chapa2 );
     
     
      }
      
      else if (chapa2 > chapa1){
       printf ("a chapa 1 ganhou com %i votos\n" , chapa1);
      printf ("chapa 2 com %i votos\n" , chapa2 );
      
          
          
      }
      
      else if (chapa2 = chapa1){
       printf ("a votaçao deu em empate com %i votos, espero voces no 2 turno!" , chapa1);
     
          
          
      }
      
     printf( "votos nulos/brancos %i\n" , nulo);
     
  
  }while (decisao != 0 );
  
  
  
  
  
  
    

    return 0;
}
