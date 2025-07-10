import java.util.Scanner;


class Celula {


	public int figurinhasRaras;
	public int qntFigurinhas;
	public Celula prox;



	public Celula() {
		this(0, 0 );
	}

	public Celula(int figurinhasRaras, int qntFigurinhas) {


		this.figurinhasRaras = figurinhasRaras;
		this.qntFigurinhas = qntFigurinhas;
		this.prox = null;





	}


}


class Lista {


	public Celula primeiro;
	public Celula ultimo;



	public Lista() {

		primeiro = new Celula( 0, 0);
		ultimo = primeiro;



	}


	void inserirFim( int x, int y) {

		ultimo.prox = new Celula( x, y);
		ultimo = ultimo.prox;


	}



	public void mostrar() {


		for(Celula i = primeiro.prox; i != null; i = i.prox) {


			System.out.print(i.qntFigurinhas + " ");

		}







	}


	void quntRaras( Lista lista1, int raras) {


		for(Celula i = primeiro.prox; i != null; i = i.prox) {



			for(Celula j = lista1.primeiro.prox; j != null; j = j.prox) {



                    if(i.figurinhasRaras == j.qntFigurinhas){
                        raras--;
                    }





			}


		}

            System.out.print(raras);


	}




}




	public class Main
	{
		public static void main(String[] args) {
			Scanner sc = new Scanner (System.in);
			Lista lista = new Lista();
			Lista lista1 = new Lista();


			int figurinhasAlbum = sc.nextInt();
			int qntfigurinhasRaras = sc.nextInt();
			int qntFigurinhas = sc.nextInt();

			int figurinhasRaras;
			int totalFigurinhas;

			for(int i = 0; i < qntfigurinhasRaras; i++) {


				figurinhasRaras = sc.nextInt();
				lista.inserirFim(figurinhasRaras, 0 );


			}


			for(int i = 0; i < qntFigurinhas; i++) {


				totalFigurinhas = sc.nextInt();
				lista1.inserirFim(0, totalFigurinhas );


			}


            lista.quntRaras(lista1, qntfigurinhasRaras);



		}
	}
