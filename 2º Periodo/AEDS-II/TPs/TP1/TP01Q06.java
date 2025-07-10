import java.util.Scanner;

public class TP01Q06
{
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
			boolean evogal = true;
			boolean econsoante = true;
			boolean enumero = true;
			boolean ereal = true;

			for(int i = 0 ; i < tamanho; i++) {

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
			}


			if(evogal) {
				System.out.print("SIM ");
			} else {
				System.out.print("NAO ");
			}
			if(econsoante) {
				System.out.print("SIM ");
			} else {
				System.out.print("NAO ");
			}
			if(enumero) {
				System.out.print("SIM ");
			} else {
				System.out.print("NAO ");
			}
			if(ereal) {
				System.out.println("SIM");
			} else {
				System.out.println("NAO");
			}

		} while(efim !=true);

	}
}
