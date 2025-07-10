public class Quicksort
{

	public static void quicksort(int esq, int dir, int[] vet) {

		int i = esq; //( primeira posição)
		int j = dir; //( ultima posição)
		int pivo = vet[(esq + dir)/2]; // elemento do meio do vetor

		while(i <= j) {

			while(vet[i] < pivo) // enquanto o elemento i for menor que o pivo 
				i++; // pula um elemento
			while(vet[j] > pivo) // enquanto o elemento j e maior que o pivo
				j--; //decrementa um elemeto

			if( i <= j) { // se i maior igual a j, faz a troca dos elementos
				swap(i, j, vet); // faz a troca dos elementos
				i++; // incrementa um i
				j--; // decrementa um j
			}
		}

		if(esq < j) // esq vale 0 e j vale a metate do vetor
			quicksort(esq, j, vet); // ordena recursivamnete o vetor de esq (0) ate j

		if(i < dir) // i vale a metade do vetor e dir (vet - 1);
			quicksort(i, dir, vet); // ordena recursivamnete o vetor de esq (0) ate j

	}

	public static void swap(int i, int j, int[] vet) {

		int temp = vet[i];
		vet[i] = vet[j];
		vet[j] = temp;

	}

	public static void mostrar(int[] vet) {

		System.out.print("[");
		for(int t = 0; t < vet.length; t++) {

			System.out.print(vet[t]);
			System.out.print(" ");

		}
		System.out.print("]");
	}

	public static void main(String[] args) {

		int[] vet = {0,1,5,15,16,9,10,4,3,30,5,20,48,71,82}; // declara o vetor 
		int esq = 0; // esq pega o valor do primeiro indice do vetor
		int dir = vet.length - 1; // dir pega o valor do ultimo indice do vetor


		quicksort(esq, dir, vet); // chama o quicksort
		mostrar(vet); // mostra o vetor ordenado


	}

}







