
public class LAB01Q01
{
	public static void main(String[] args) {
	  
	  boolean isfim = false  ;
do{
	String palavra = MyIO.readLine();
	
	if(palavra.equalsIgnoreCase("FIM")){
	    isfim = true;
	    break;
	}
	
	
	char[] vet = palavra.toCharArray();
	int maiuscula = 0;
	
	    for(int i = 0; i < vet.length; i++){
	        
	       if(vet[i] >= 'A' && vet[i] <= 'Z'){
	           maiuscula++;
	       }

	    }
		
		 MyIO.println(maiuscula);
		
		
		
	}while(isfim != true);
	
	
}
}
