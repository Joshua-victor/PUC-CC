class Celula {
    public int elemento;
    public Celula prox;

    public Celula() { 
        this(0);
    }

    public Celula(int elemento) {
        this.elemento = elemento;
        this.prox = null;
    }
}

class Fila {

    private Celula primeiro, ultimo;

    public Fila() {
        primeiro = new Celula();
        ultimo = primeiro;
    }
    
    
    
    public void inserir(){
        
        ultimo.prox = new Celula();
        ultimo = ultimo.prox;
        
    }
    
    
    public void remover(){
       
      if(primeiro == ultimo){
          
          throw new Exception("erro, fila vazia");
      }  
          
      Celula tmp = primeiro;
      primeiro = primeiro.prox;
      tmp.prox = null;
      tmp = null;
   
    }
    
    public void mostrar{
        
        
     System.out.println("["); 
    
     for(Celula i = primeiro; i != ultimo; i = i.prox){
         
        System.out.printf(i.elemento + " "); 
         
     }
     
     System.out.println("]");    
      
    }
    
    public void MaiorElemento(){
        
     int maior = 0;
    
     for(Celula i = primeiro; i != null; i = i.prox){
         
        if(maior < i.elemento){
            
            maior = i.elemento;
            
        } 
    
     }
     
     System.out.printf("maior elemento é: " + maior); 
      
    }
    

}

public class FilaFlexivel {
    public static void main(String[] args) {
    
        try {
            Fila Fila = new Fila();
            Fila.inserir(4);
            Fila.inserir(5);
            Fila.inserir(2);
            Fila.inserir(6);
            Fila.inserir(8);
            Fila.mostrar();
          
            
  

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
       
        
    }
    
}
