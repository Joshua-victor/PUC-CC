#include <stdio.h>

int main()
{
    
    float dinheiro = 0.0;
    scanf("%f" , &dinheiro);

    int cem = 0;
    int cinquenta = 0; 
    int vinte = 0;
    int dez = 0;
    int cinco = 0;
    int dois = 0;
    int umreal = 0;
    int cinquentaCentavos = 0;
    int vintecincoCentavos = 0;
    int dezcentavos = 0;
    int cincocentavos = 0;
    int umcentavo = 0;
    float aux = 0.0;
    
      
        
            while(aux + 100.00 <= dinheiro){
                cem++;
                aux += 100.00;
            }


            while(aux + 50.00 <= dinheiro){
                  cinquenta++;
                aux += 50.00;
            }

            while(aux + 20.00 <= dinheiro){
                  vinte++;
                aux += 20.00;
            }

              while(aux + 10.00 <= dinheiro){
                  vinte++;
                aux += 20.00;
            }

               while(aux + 05.00 <= dinheiro){
                  cinco++;
                aux += 05.00;
            }

              while(aux + 2.00 <= dinheiro){
                dois++;
                aux += 2.00;
            }


            while(aux + 1.00 <= dinheiro){
                  umreal++;
                aux += 1.00;
            }

            while(aux + 0.50 <= dinheiro){
                  cinquentaCentavos++;
                aux += 0.50;
            }

               while(aux + 0.25 <= dinheiro){
                  vintecincoCentavos++;
                aux += 0.25;
            }



              while(aux + 0.10 <= dinheiro){
                  dezcentavos++;
                aux += 0.10;
            }

             while(aux + 0.05 <= dinheiro){
                  cincocentavos++;
                aux += 0.05;
            }

               while(aux + 0.01 <= dinheiro){
                  umcentavo++;
                aux += 0.01;
            }
            



        printf("NOTAS:\n");
        printf("%d nota(s) de R$ 100.00\n" , cem);
        printf("%d nota(s) de R$ 50.00\n" , cinquenta);
        printf("%d nota(s) de R$ 20.00\n" , vinte);
        printf("%d nota(s) de R$ 10.00\n" , dez);
        printf("%d nota(s) de R$ 5.00\n" , cinco);
        printf("%d nota(s) de R$ 2.00\n" , dois);
        printf("MOEDAS:\n");
        printf("%d moeda(s) de R$ 1.00 \n" , umreal);
        printf("%d moeda(s) de R$ 0.50\n" , cinquentaCentavos);
        printf("%d moeda(s) de R$ 0.25\n" , vintecincoCentavos);
        printf("%d moeda(s) de R$ 0.10\n" , dezcentavos);
        printf("%d moeda(s) de R$ 0.05\n" , cincocentavos);
        printf("%d moeda(s) de R$ 0.01\n" , umcentavo);

        
        







    return 0;
}
