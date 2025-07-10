import java.util.Scanner;

public class TP01Q20
{

	public static void Is(char[] vet, int tamanho, int i, boolean[] resp) {

		if(i == tamanho) {
			return;
		}
		if (vet[i] >= 'A' && vet[i] <= 'Z') { // C 	 uma letra
			if (vet[i] == 'A' || vet[i] == 'E' || vet[i] == 'I' || vet[i] == 'O' || vet[i] == 'U') {
				resp[1] = false; // Se tem vogal, nC#o pode ser sC3 consoante
			} else {
				resp[0] = false; // Se tem consoante, nC#o pode ser sC3 vogal
			}
			resp[2]= false; // Se tem letra, nC#o pode ser sC3 nC:mero
			resp[3] = false;
		} else if (vet[i] >= '0' && vet[i] <= '9') { // C	 um nC:mero
			resp[0] = false;
			resp[1] = false;
		}


		Is(vet, tamanho, i + 1, resp);


	}





	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		boolean efim = false;
		do {

			String palavra = scanner.nextLine().toUpperCase();

			if(palavra.equalsIgnoreCase("FIM")) {
				efim = true;
				break;
			}
			char[] vet = palavra.toCharArray();
			int tamanho = vet.length;
			boolean[] resp = {true, true, true, true}; // 1 - vogal, 2 - consoante, 3 - num, 4 - real

			/*	for(int i = 0 ; i < tamanho; i++) {

					if (vet[i] >= 'A' && vet[i] <= 'Z') { // C	 uma letra
						if (vet[i] == 'A' || vet[i] == 'E' || vet[i] == 'I' || vet[i] == 'O' || vet[i] == 'U') {
							econsoante = false; // Se tem vogal, nC#o pode ser sC3 consoante
						} else {
							evogal = false; // Se tem consoante, nC#o pode ser sC3 vogal
						}
						enumero= false; // Se tem letra, nC#o pode ser sC3 nC:mero
						ereal = false;
					} else if (vet[i] >= '0' && vet[i] <= '9') { // C	 um nC:mero
						evogal = false;
						econsoante = false;
					}
				}*/

			Is(vet, tamanho, 0, resp);


			System.out.print(resp[0] ? "SIM " : "NAO ");
			System.out.print(resp[1] ? "SIM " : "NAO ");
			System.out.print(resp[2] ? "SIM " : "NAO ");
			System.out.println(resp[3] ? "SIM" : "NAO");

		} while(efim !=true);

	}
}
