
public class LAB01Q02
{ 

public static int contarMaiusculas(char[] vet, int tamanho) {
        int maiuscula = 0;

        if (tamanho >= 0) { // Evita acessar índice inválido
            if (vet[tamanho] >= 'A' && vet[tamanho] <= 'Z') {
                maiuscula++;
            }
            maiuscula += contarMaiusculas(vet, tamanho - 1); // Soma ao resultado da recursão
        }

        return maiuscula;
    }

	public static void main(String[] args) {

		boolean isfim = false  ;
		do {
			String palavra = MyIO.readLine();

			if(palavra.equalsIgnoreCase("FIM")) {
				isfim = true;
				break;
			}


			char[] vet = palavra.toCharArray();
			int maiuscula = contarMaiusculas(vet, vet.length - 1) ;



			MyIO.println(maiuscula);



		} while(isfim != true);


	}
}
