 printf("notas da turma\n");
    
    int turma;
    bool erro;
    float nota;
    float media;
    float maiorNota = 0 ;
    float soma;
    
do{
      printf("digite quantos alunos tem");
      scanf("%i", &turma);
      erro = turma < 0;
      if (erro) puts("numero invalida!");
 }while (erro );
   
for (int x = 0 ; x < turma ; x++){
       
       
 do{
       printf("digite sua nota");
       scanf("%f" , &nota);
       soma = soma + nota;
       erro = nota < 0 ;
        
}while (erro);
       
      media = soma / turma; 
      
        if (nota > maiorNota) {
            
            maiorNota = nota;
            
        }
       
       
   }
  
      
 printf("a media da turma e: %f\n", media);
 printf("a maior nota da turma e: %f\n", maiorNota);
 
 
       

    