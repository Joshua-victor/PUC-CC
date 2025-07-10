import java.util.Scanner;
public class TP01Q09
{
	public static void main(String[] args) {
	    Scanner scanner = new Scanner (System.in);

		boolean isfim = false;
		do {

			String palavra1 = scanner.nextLine().toUpperCase(); // le a string e deixa ela maiuscula

			if(palavra1.equalsIgnoreCase("FIM")) { // função para verficar se palavra1 é igual a FIM
				isfim = true;
				break;
			}
			
			String[] partes = palavra1.split(" - "); // split serve como um separador de string, no caso ela separa cada vez que ve um " - "

			boolean resp = false;
			char[] vetor1 = partes[0].toCharArray();
			char[] vetor2 = partes[1].toCharArray();
			
	
			int tamanho = vetor1.length;


		 if (vetor1.length != vetor2.length) {
                System.out.println("\u004E\u00C3\u004F"); 
                continue; 
            }

			for(int i = 0; i < tamanho; i++) {

				for(int j = 0; j < tamanho; j++) {

					if(vetor1[j] == vetor2[i] ) {
						resp = true;
						j = tamanho;

					} else {
						resp = false;
					}
				}
			}

			if(resp == true) {
				System.out.println("SIM");
			} else if(resp == false) {
				System.out.println("\u004E\u00C3\u004F");
			}

		} while(isfim != true);
		scanner.close();

	}
}



