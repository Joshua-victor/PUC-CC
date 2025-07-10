import java.util.Scanner;
public class TP01Q10
{
	public static void main(String[] args) {
	    Scanner scanner = new Scanner(System.in);
	    
	    boolean isfim = false;
	    do{
	    
	    String palavra = scanner.nextLine();
	    char[] vet = palavra.toCharArray();
	    int contagem = 1;
	    int tamanho = vet.length;
	    
	    if(palavra.equalsIgnoreCase("FIM")){ // Função para caso a palavra lida for igual a FIM
	        isfim = true;
	        break;
	    }
	    
	    for(int i = 0; i < tamanho; i++){
	        
	        if(vet[i] == ' '){
	            contagem++;
	        }
	    }
	     
	    System.out.print(contagem);
	    System.out.println(" ");
	    
	    
	    
	    }while(isfim != true);
	    scanner.close();
		
	}
}


