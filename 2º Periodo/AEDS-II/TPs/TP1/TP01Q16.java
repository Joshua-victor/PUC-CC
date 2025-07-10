public class TP01Q16 {


	public static boolean epalindromo(int tamanho, char[] palindromo,char[] vetor, int i) {
	    
		if (i >= tamanho / 2) {
			return true;
		}

		if(palindromo[i] == vetor[i]) {
			return epalindromo(tamanho, palindromo, vetor, i + 1);

		} else {

			return false;
		}

	}

	public static void main(String[] args) {


		boolean isfim = false;

		do {
			String palavra = MyIO.readLine();
			boolean resp = false;
			char[] vetor = palavra.toCharArray();
			char[] palindromo = new char[vetor.length];

			if (palavra.equalsIgnoreCase("FIM")) {
				isfim = true;
			}


			for (int i = 0; i < vetor.length; i++) {
				palindromo[i] = vetor[vetor.length - 1 - i];
			}

			int tamanho = vetor.length;
			resp = epalindromo(tamanho, palindromo, vetor, 0);

			if(resp == true && isfim != true) {
				MyIO.println("SIM");
			} else if (resp == false && isfim != true) {
				MyIO.println("NAO");
			}

		} while(!isfim);

	}
}











