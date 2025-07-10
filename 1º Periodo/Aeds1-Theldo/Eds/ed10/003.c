#include <stdio.h>




int leiturArquivos (FILE *arquivo , FILE *arquivo1){
    
 
}






int main ()
{
  int primeiro, segundo;

  printf ("digite a quantidade do primeiro arranjo:");
  scanf ("%d", &primeiro);

  printf ("digite a quantidade do segundo arranjo:");
  scanf ("%d", &segundo);

  int arranjo1[primeiro];
  int arranjo2[segundo];


  for (int i = 0; i < primeiro; i++)
    {

      printf ("digite o %d digito do arranjo 1: ", i);
      scanf ("%d", &arranjo1[i]);


    }
    
    printf("\n");
    getchar();

  for (int i = 0; i < segundo; i++)
    {

      printf ("digite o %d digito do arranjo 2: ", i);
      scanf ("%d", &arranjo2[i]);


}

  FILE *arquivo1;
    arquivo1 = fopen("Dados1.txt", "w");  
    
    if (arquivo1 == NULL) {
        printf("Erro ao abrir o arquivo!");
      
    }
    
    fprintf(arquivo1, "Números do arranjo: ");
    for (int i = 0; i < primeiro; i++) {
        fprintf(arquivo1, "\n %d ", arranjo1[i]);
    }
    
    fclose(arquivo1);  // Fecha o arquivo
    printf("Resposta gravada no arquivo 'dados1.txt'.\n"); 
    
    
    FILE *arquivo;
    arquivo = fopen("Dados2.txt", "w");  
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
      
    }
    
    fprintf(arquivo, "Números do arranjo: ");
    for (int i = 0; i < segundo; i++) {
        fprintf(arquivo, "\n %d ", arranjo2[i]);
    }
    
    fclose(arquivo);  // Fecha o arquivo
    printf("Resposta gravada no arquivo 'dados2.txt'.\n"); 
    
    
    arquivo = fopen("Dados1.txt", "r");
    arquivo1 = fopen("Dados2.txt", "r");


      leiturArquivos(arquivo1, arquivo);

    fclose(arquivo);
    fclose(arquivo1);











    return 0;
    
}


