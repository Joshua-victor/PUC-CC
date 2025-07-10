#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main()
{
    printf("perfil da turma\n");
    
    
    int turma;
    bool erro;
    char genero;
    int idade;
    int menorIdade = 90;
    int maiorIdade = 0;
    float prctM = 0;
    float prctF = 0;
    float percentualM = 0;
    float percentualF = 0;
    
    printf("digite o tamanho da turma:");
    scanf(" %i", &turma);
    
    
    for(int x = 0 ; x < turma ; x++){
        
        
        do{
        printf("qual seu genero:");
        scanf(" %c" , &genero);
        genero = toupper (genero);
        erro = genero != 'M' && genero !='F';
        if (erro) puts("genero invalido");
        }while(erro);
       
      do{
        printf("qual sua idade:");
        scanf(" %i" , &idade);
        erro = idade < 0 && idade > 90;
        if (erro) puts("idade invalida");
        }while(erro);
       
        if (genero == 'F') prctF++;
        else prctM++;
       
       
       
      if (idade > maiorIdade){
          
          maiorIdade = idade;
      }
         else if ( idade < menorIdade){
             
             menorIdade = idade;
         }
       
       
       percentualM = (prctM/100)*genero;
      percentualF = (prctF/100)*genero;
     
     
    }
    
   
   
   printf(" o percentual masculino e:%f \n" , percentualM);
   printf(" o percentual feminino e:%f \n" , percentualF);
   printf(" a pessoa mais velha tem: %i anos  \n" , maiorIdade);
   printf(" a pessoa mais nova tem: %i anos  \n" , menorIdade);
  

    

    return 0;
}
    