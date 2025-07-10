import java.util.Scanner;

public class Main
{

    public static void removerPos(int[] repetidos, int tamanho, int pos){

        if(pos > tamanho || pos < 0){
            return;
        }

        for(int i = tamanho; i < pos; i--){
            repetidos[i] = repetidos[ i - 1];
        }
            
    }


	public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
        boolean isfim = false;
    do{
        int n =  scanner.nextInt();
        int m = scanner.nextInt();

            if(n == 0 && m==0){
                isfim= true;
                break;
            }


          int[] numeros = new int[n * m + 1];  // criamos o vetor ( poderia ser uma matriz porem fui pensar no final) e alocaremos todos os jogadores aqui
          int[] repetidos = new int[n * m]; // criamos outro vetor para alocar todos os repetidos


        for(int i = 0; i < n * m; i++ ){ // aqui vamos ler todos os elementospara armazenar 

            numeros[i] = scanner.nextInt();
        }
                int k =0;

                int l = 0;
                int g = 0;

            for( l = 0; l < n* m - 1; l++){ // aqui ordenamos e  vemos qual e repetido ou não para melhor manipulação
                int menor = l;
                for( g= l + 1; m < n * g; g++){

                    if(numeros[menor] == numeros[g]){
                        menor = g;
                    }
                    
                    repetidos[l] = numeros[g];

                }
            }

            for(int i = 0; i < n * m; i++){
                System.out.println(numeros[i]);
            }

            // inserção porem com igualdade

        
            /*
             aqui eu removeria os elementos de menos aprição deixando os maiores ou iguais a eles

             chamando um removerPos(repetidos, n*m, pos);


             */

            for(int i = 0; i < repetidos.length; i++){
              System.err.println(repetidos[i]);
            }


    }while(isfim != true);
          scanner.close();
	
}
 
}


/*
 * A entrada contém diversos casos de teste. Jogadores são identificados por inteiros de 1 a 10000.
 *  A primeira linha de um caso de teste contém dois inteiros N e M, indicando, respectivamente, 
 * o número de rankings disponíveis (2 ≤ N ≤ 500) e o número de jogadores em cada ranking (2 ≤ M ≤ 500).
 *  Cada uma das próximas N linhas contém a descrição de um ranking semanal. Cada descrição é composta por 
 * uma sequência de M inteiros, separados por um espaço em branco, identificando os jogadores que apareceram 
 * naquele ranking semanal. Você pode assumir que:

em cada caso de teste há exatamente um melhor jogador e ao menos um segundo melhor jogador,
cada ranking semanal consiste de M jogadores distintos.
O final da entrada é indicado por N = M = 0.

Saída
Para cada caso de teste da entrada seu programa deve produzir uma linha de saída, contendo o identificador do jogador
 que é o segundo melhor, em número de aparições nos rankings. Se há um empate para segundo lugar, imprima os identificadores
  de todos os segundo colocados, em ordem crescente. Cada identificador produzido deve ser seguido por um espaço em branco.
 */