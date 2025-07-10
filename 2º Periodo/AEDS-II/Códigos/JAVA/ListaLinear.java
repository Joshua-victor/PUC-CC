import java.util.Scanner;


class Ponteiro {
	int n;
}

public class Main
{

	public static void inverter(int[] lista, Ponteiro quantidade, int tamanho) {
	    
	    
	    if( quantidade.n == 0){
	        System.out.println("Lista vazia!!");
	        return;
	    }
	    

		int[] inverso = new int[quantidade.n]; // cria uma nova lista para armazenar os elementos inversos
		int j = quantidade.n - 1;

		for(int i = 0; i < quantidade.n; i++) {


			inverso[i] = lista[j];
			j--;
		}

	        mostrar(inverso, quantidade); // chama a funão para mostrar a lista inversa

	}



	public static void pesquisar(int numero, int[] lista, Ponteiro quantidade) {

		boolean achou = false;
		for (int i = 0; i < quantidade.n; i++) { // percorre toda a lista 

			if(lista[i] == numero) {
				System.out.println("Numero encontrado na pos: " + i);
				i = quantidade.n;
				achou = true;
			}


		}
		if(achou != true) {
			System.out.println("Numero não encontrado!");

		}

	}



	public static void mostrar(int[] lista, Ponteiro quantidade) {

		System.out.print("[");
		for (int i = 0; i < quantidade.n; i++) { // for de 0 a quantidade.n (onde tem elementos)
			System.out.print(lista[i]);
			System.out.print(" ");
		}
		System.out.println("]");
	}

	public static void remover(int pos, int[] lista, Ponteiro quantidade, int tamanho) {


			if( pos < 0 || pos > quantidade.n) { // verifica se  tem espaço, se pos não e negativo, se pos não é maior que a lista
			System.out.println("Lista cheia ou pos invalida!");
			return;
		}

		quantidade.n--;     // diminui o quantidade.n, para tratar o elemento em questão como lixo

		for(int i = pos; i < quantidade.n; i++) {  // move os elementos do final ate a posição excluida


			lista[i] = lista[i+1];
		}




	}



	public static int removerFim(int[] lista, Ponteiro quantidade, int tamanho) {


			if(quantidade.n  == 0  ){
			System.out.println("Lista cheia ou pos inválida!");
			return 0;
		}

		int removido = lista[quantidade.n];
		quantidade.n--;


		return removido;


	}



	public static int removerInicio(int[] lista, Ponteiro quantidade, int tamanho) {


			if(quantidade.n  == 0  ) { // verifica se a lista não esta vazia
			System.out.println("Lista cheia ou pos inválida!");
			return 0 ;
		}

		int removido = lista[0];
		quantidade.n--;


		for(int i = 0; i < quantidade.n; i++) {


			lista[i] = lista[i+ 1];
		}

		return removido;


	}


	public static void inserir(int pos, int numero, int[] lista, Ponteiro quantidade, int tamanho) {

		try {
			if(quantidade.n  >= tamanho || pos < 0 || pos > quantidade.n) { // verifica se  tem espaço, se pos não e negativo, se pos não C) maior que a lista

			}
		} catch(ArrayIndexOutOfBoundsException e) {
			System.out.println("Lista cheia ou pos inválida!");
		}


		for(int i = quantidade.n; i > pos; i--) {


			lista[i] = lista[i-1];
		}

		lista[pos] = numero;
		quantidade.n++;


	}



	public static void inserirFim( int numero, int[] lista, Ponteiro quantidade, int tamanho) {


			if(quantidade.n  >= tamanho) {
			System.out.println("Lista cheia!");
			return;
		}

		lista[quantidade.n] = numero;
		quantidade.n++;
	}
	

	public static void inserirInicio(int numero, int[] lista, Ponteiro quantidade, int tamanho) {


			if(quantidade.n >= tamanho) {
			System.out.println("Lista cheia!");
			return;
		}

		for(int i = quantidade.n; i > 0; i--) {

			lista[i] = lista[i - 1];
		}

		lista[0] = numero;
		quantidade.n++;
	}


	public static void main(String[] args) {
		Scanner Scanner = new Scanner (System.in);
		boolean isfim = false;
		Ponteiro ponteiro = new Ponteiro();
		ponteiro.n = 0;
		int[] lista = new int[100];

		do {

			System.out.println("--------------------------------------------------------------------------");
			System.out.println("\nbem vindo aos exemplos de TAD, aqui temos algumas opções para treinar \ntemos as opções:\n a - inserir no inicio\n b - inserir no fim\n c - inserir em alguma posição\n d - remover no inicio\n e - remover no fim\n f - remover\n g - mostrar\n h - pesquisar\n i - Inverter elementos\n FIM - para sair do programa\n ");
			System.out.println("--------------------------------------------------------------------------");

			System.out.print("digite a escolha que deseja:");
			String escolha = Scanner.nextLine();


			int numero = 0;
			int pos = 0;

			if(escolha.equalsIgnoreCase("FIM")) {
				isfim = true;
				break;
			}


			switch (escolha) {


			case "a":
				System.out.print("Digite o numero desejado: ");
				numero = Scanner.nextInt();
				Scanner.nextLine();
				inserirInicio(numero, lista, ponteiro, lista.length);
				mostrar(lista, ponteiro);

				break;

			case "b":
				System.out.print("Digite o numero desejado: ");
				numero = Scanner.nextInt();
				Scanner.nextLine();
				inserirFim(numero, lista, ponteiro, lista.length);
				mostrar(lista, ponteiro);

				break;

			case "c":
				System.out.print("Digite o numero desejado: ");
				numero = Scanner.nextInt();
				Scanner.nextLine();
				System.out.print("Digite a posição desejada: ");
				pos = Scanner.nextInt();
				Scanner.nextLine();
				inserir(pos, numero, lista, ponteiro, lista.length);
				mostrar(lista, ponteiro);
				break;

			case "d":

				int removido = removerInicio(lista, ponteiro, lista.length);
				System.out.println("elemento removido: " + removido);
				mostrar(lista, ponteiro);
				break;


			case "e":
				removido = removerFim(lista, ponteiro, lista.length);
				mostrar(lista, ponteiro);
				break;


			case "f":

				System.out.print("Digite a posição desejada: ");
				pos = Scanner.nextInt();
				Scanner.nextLine();
				remover(pos, lista, ponteiro, lista.length);
				mostrar(lista, ponteiro);
				break;


			case "g":
				mostrar(lista, ponteiro);
				break;

			case "h":
				System.out.print("Digite a o numero desejado: ");
				numero = Scanner.nextInt();
				Scanner.nextLine();
				pesquisar(numero, lista, ponteiro);
				break;

			case "i":
				inverter(lista, ponteiro, lista.length);
				break;

			default:
				System.out.print("Invalido!");

			}


		} while(isfim != true);
		Scanner.close();
	}
}
