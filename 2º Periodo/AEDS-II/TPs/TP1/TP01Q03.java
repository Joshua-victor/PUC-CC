public class TP01Q03
{
	public static void main(String[] args) {

		boolean resp = true; // bool para a condiC'C#o de parada
		String palavra;
		do { 

			palavra  = MyIO.readLine(); //lendo a string digitada pelo usuC!rio
			char[] caracteres = palavra.toCharArray(); //transformando em vetor

			if (palavra.equalsIgnoreCase("FIM")) { //equalsIgnoreCase serve para identificar se a palavra C) igual a FIM
				break;
			}

			int tamanho = caracteres.length;  //descobrindo o tamanho do vetor

			for(int i = 0; i < tamanho; i++) {

				caracteres[i] = (char) (caracteres[i] + 3); //trocando a letra pela 3 posterior

			}

			for (char c : caracteres) {  // for para printar o vetor
				MyIO.print(c);
			}

			MyIO.println(" ");


		} while(resp == true);

	}
}
