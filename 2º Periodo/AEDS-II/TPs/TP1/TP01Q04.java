import java.util.Random;
public class TP01Q04
{
	public static void main(String[] args) {


		String Palavra ;
		boolean isfim = false;
		do {
			Palavra = MyIO.readLine();
			Random gerador = new Random();
			gerador.setSeed(4);
			char letraAleatoria1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26)); // gerando a primeira letra
			char letraAleatoria2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26)); // gerando a segunda letra
			char[] frase = Palavra.toCharArray();
			int tamanho = Palavra.length();

			if (Palavra.equalsIgnoreCase("FIM")) { //equalsIgnoreCase serve para identificar se a palavra C) igual a FIM
				isfim = true;
				break;

			}

			for(int i = 0; i < tamanho; i++) {

				if(frase[i] == letraAleatoria1) {

					frase[i] = letraAleatoria2;
				}

			}

			for (char c : frase) {  // for para printar o vetor
				MyIO.print(c);

			}
			
			MyIO.println("");

		} while(isfim != true);
	}
}
