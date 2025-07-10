import java.util.Scanner;

class posicoes {

	int primeiro;
	int ultimo;
}

public class listaCircular
{

	public static void inserir(int numero, int[] FilaCircular, posicoes pos, int tamanho) {


		if(((pos.ultimo + 1) % tamanho) == pos.primeiro) {
			System.out.println("ERRO LISTA CHEIA!!");
			return;
		}

		FilaCircular[pos.ultimo] = numero;

		pos.ultimo = (pos.ultimo + 1) % tamanho;

	}


	public static void remover(int[] FilaCircular, posicoes pos, int tamanho) {


		if(pos.ultimo == pos.primeiro) {
			System.out.println("ERRO LISTA VAZIA!!");
			return;
		}

		pos.primeiro = (pos.primeiro + 1) % tamanho;

	}

	public static void main(String[] args) {
		Scanner Scanner = new Scanner (System.in);

		posicoes Posicoes = new posicoes();
		Posicoes.primeiro = 0;
		Posicoes.ultimo = 0;
		int tamanho = 5;
		int[] FilaCircular = new int[tamanho + 1];
		boolean isfim = false;

		do {

			System.out.printf(" ----------------------\n");
			System.out.printf("    fila circular\n a-Adicionar elemento\n b-Remover elemento\n c-Mostrar elementos\n");
			System.out.printf(" ----------------------\n");

			System.out.printf("digite a sua escolha: ");
			String escolha = Scanner.nextLine();

			if(escolha.equalsIgnoreCase("FIM")) {
				isfim = true;
				break;
			}


			switch (escolha) {

			case "a":

				int numero = 0;
				System.out.printf("digite o numero: ");
				numero = Scanner.nextInt();
				Scanner.nextLine();
				inserir(numero, FilaCircular, Posicoes, FilaCircular.length);

				break;

			case "b":
				remover(FilaCircular, Posicoes, FilaCircular.length);
				break;

			case "c":
				System.out.print("[");
				for (int i = Posicoes.primeiro; i < Posicoes.ultimo; i++) {
					System.out.print(FilaCircular[i]);
					System.out.print(" ");
				}
				System.out.println("]");
				break;

			}

		} while(isfim != true);

	}
}
