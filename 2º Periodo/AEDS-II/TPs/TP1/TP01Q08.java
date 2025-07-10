import java.util.Scanner;
public class TP01Q08
{
	public static void main(String[] args) {
	     Scanner scanner = new Scanner(System.in);

		boolean isfim = false;
		
		do {
            String numeros = scanner.nextLine();
            
			if(numeros.equalsIgnoreCase("FIM")) { // condição de parada
				isfim = true;
				break;
			}

			char[] vet = numeros.toCharArray();
			int tamanho = numeros.length();
			int soma = 0;


			for(int i = 0; i < tamanho; i++) {

				soma += vet[i] - '0' ; // sem o - '0' o codigo soma os valores pela tabela ASCII

			}

			 System.out.print(soma);
			 System.out.println(" ");

		} while(!isfim);
		scanner.close();

	}
}
