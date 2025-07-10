import java.util.Scanner;

class Celula {

	public int elemento;
	public Celula prox;


	public Celula() {
		this(0);
	}

	public Celula(int elemento) {

		this.elemento = elemento;
		prox = null;

	}

}


class Lista {

	public Celula primeiro;
	public Celula ultimo;


	public Lista() {

		primeiro = new Celula();
		ultimo = primeiro;

	}


	void inserirFim(int x) {

		Celula tmp = new Celula(x);
		ultimo.prox = tmp;
		ultimo = tmp;
		tmp = null;

	}
	

	void mostrar(){
	    
	 for(Celula i = primeiro.prox; i != null; i = i.prox){
	     
	   System.out.print(i.elemento + " ");  
	     
	 }
	    
	   
	    
	    
	}


}





public class Beecrowd_1211
{
    public static int compararSequencia(Lista telefone1, Lista telefone2){
	    
	   Celula tmp1 = telefone1.primeiro.prox; 
	   Celula tmp2 = telefone2.primeiro.prox; 

	   int sequencia = 0; 
	   
	   
	   for(Celula i = telefone1.primeiro.prox; i != null; i = i.prox){
	       
	     if(tmp1.elemento != tmp2.elemento){
	         return sequencia;
	     }  
	     
	     if(tmp1.elemento == tmp2.elemento){
	         sequencia++;
	         tmp1 = tmp1.prox;
	         tmp2 = tmp2.prox;

	     }
	       
	       
	       
	   }
	  
	  return sequencia;  
	}
	
    
    
    
    
    
	public static void main(String[] args) {
		Scanner scanner = new Scanner (System.in);
		Lista telefone1 = new Lista();
		Lista telefone2  = new Lista();

		System.out.printf("digite a quantidade: ");
		int quantidade = scanner.nextInt();


		for(int i = 0; i < quantidade; i++) {
			System.out.printf("digite o telefone: ");
			int telefone = scanner.nextInt();

			String numero = Integer.toString(telefone);
			int[] vetor = new int[numero.length()];


			if(i == 0) {
				for(int j = 0; j < numero.length(); j++) {

					vetor[j] = numero.charAt(j) - '0';
					telefone1.inserirFim(vetor[j]);
				}
			}

				if(i == 1) {
					for(int j = 0; j < numero.length(); j++) {

						vetor[j] = numero.charAt(j) - '0';
						telefone2.inserirFim(vetor[j]);
					}

				}

    
		}
		
			
		int seq = compararSequencia(telefone1, telefone2);
		System.out.println(seq);
	
	
	}
}