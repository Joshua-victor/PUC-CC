import java.util.Scanner;
public class TP01Q11 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner (System.in);
		boolean isFim = false;
		do {
			String palavra = scanner.nextLine(); // LC* a entrada
			if (palavra.equalsIgnoreCase("FIM")) {
				isFim = true;
				break;
			}

			int maior = 0;
			int[] ultimoIndice = new int[256]; 
			for (int i = 0, j = 0; j < palavra.length(); j++) {
				i = Math.max(ultimoIndice[palavra.charAt(j)], i);
				maior = Math.max(maior, j - i + 1); 
				ultimoIndice[palavra.charAt(j)] = j + 1;
			}

			System.out.println(maior);


		} while (!isFim);
		scanner.close();
	}
}
