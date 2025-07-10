import java.util.Scanner;

public class TP01Q12
{
	public static void main(String[] args) {
		Scanner scanner = new Scanner (System.in);
	


		boolean isfim = false;
		do {

			String palavra = scanner.nextLine();
			//String palavra = MyIO.readLine();
			char [] senha = palavra.toCharArray();
			int tamanho = senha.length;
			boolean maiuscula = false;
			boolean minuscula = false;
			boolean especial = false;
			boolean numero = false;
			int i = 0;

			if(palavra.equalsIgnoreCase("FIM")) { // função para ver se a palavra digitada é FIM
				isfim = true;
				break;
			}

			if(tamanho < 8) {
				i = tamanho;
			}


			for( i = 0 ;  i < tamanho; i++) {

				if(Character.isUpperCase(senha[i])) { // isupper verifica se o vetor e Maiusculo

					maiuscula = true;
					

				} else if(Character.isLowerCase(senha[i])) { // islower verifica se o vetor C) minusculo

					minuscula = true;
				

				} else if(!Character.isLetterOrDigit(senha[i])) { // ispunct verifica se o vetor C) especial

					especial = true;
					

				} else if(Character.isDigit(senha[i])) { // isdigit verifica se o vetor C) numero

					numero = true;
					
				}

			}


			if(maiuscula && minuscula && especial && numero && tamanho >= 8) {
				System.out.println("SIM");
			} else {
				 System.out.println("NAO"); // digitando não pela tabela unicode
			}

		} while(isfim != true);
		scanner.close();

	}
}


