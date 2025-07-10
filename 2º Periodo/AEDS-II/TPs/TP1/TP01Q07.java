public class TP01Q07 {

	public static void main(String[] args) {
		String Palavra;
		boolean isfim = false;
		do { 
		    
			Palavra = MyIO.readLine(); // leitura da palavra
			char[] vet = Palavra.toCharArray(); // transformando em vetor
			char[] transversa = new char[vet.length];
			int tamanho = vet.length - 1; // posiC'C#o da ultima letra do vetor

			if(Palavra.equalsIgnoreCase("FIM")) {
				isfim = true;
				break;
			}

			for(int i = 0; i < vet.length; i++) {

				transversa[tamanho] = vet[i];
				tamanho--;
			}

			for (char c : transversa) {  // for para printar o vetor
				MyIO.print(c);

			}
			MyIO.println("");

		} while(isfim != true);
	}
}
