import java.util.Scanner;

class Celula {

	public String pokemon;
	public Celula prox;



	public Celula() {

		this(" ");



	}


	public Celula(String pokemon) {

		this.pokemon = pokemon;
		this.prox = null;




	}


}

class Lista {

	public Celula primeiro;
	public Celula ultimo;




	public Lista() {


		this.primeiro = new Celula(" ");
		this.ultimo = primeiro;



	}


	public void inserirFim(String x) {

		boolean repetido = false;

		for(Celula i = primeiro.prox; i != null; i = i.prox) {

			if(x.equals(i.pokemon)) {
				repetido = true;
			}

		}

		if(repetido != true) {

			ultimo.prox = new Celula(x);
			ultimo = ultimo.prox;


		}


	}


	public void mostrar() {

        int pokemons = 151;
        int quantidade = 0;
		for(Celula i = primeiro.prox; i != null; i = i.prox) {


			quantidade++;

		}


        pokemons -= quantidade;
        System.out.print("faltam " + pokemons );



	}


}

public class Main
{
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		Lista lista = new Lista();

		int quantidade = scanner.nextInt();
		scanner.nextLine();

		String pokemon;

		for(int i = 0; i <= quantidade; i++) {


			pokemon = scanner.nextLine();

			lista.inserirFim(pokemon);

		}


		lista.mostrar();


	}
}
