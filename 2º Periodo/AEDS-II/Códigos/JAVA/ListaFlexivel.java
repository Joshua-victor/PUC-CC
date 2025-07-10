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

class Lista {

    private Celula primeiro, ultimo;

    public Lista() {
        primeiro = new Celula();
        ultimo = primeiro;
    }
    
    
    
    public void inserirFim(){
        
        ultimo.prox = new Celula();
        ultimo = ultimo.prox;
        
    }
    
    public void inserirInicio(int x){
        
      Celula Tmp = new Celula(x);
      tmp.prox = primeiro.prox;
      primeiro.prox = tmp;
       
       if(primeiro == ultimo){
           ultimo = tmp;
       } 
       
       tmp = null;
        
    }
    
    public void inserir(int x, int pos){
        
      if(pos < 0 || pos > tamanho){
          throw new Exception("erro");
      }  
        
       if(pos == 0){
           inserirInicio(x);
       }else if(pos == tamanho){
           inserirFim(x);
       }
        
       Celula i = primeiro;
       for(int j = 0; j != pos; j++, i = i.prox);
       
       
        Celula tmp = new Celula(x);
        tmp.prox = i.prox;
        i.prox = tmp;
        tmp = null;       
     
    }
    

      public void removerInicio(){
       
      if(primeiro == ultimo){
          
          throw new Exception("erro, Lista vazia");
      }  
          
      Celula tmp = primeiro;
      primeiro = primeiro.prox;
      tmp.prox = null;
      tmp = null;
   
    }
    
    public void removerFim(){
        
     if(primeiro == ultimo){
         throw new Exception("erro lista vazia");
     } 
     
        
    Celula i = new Celula();    
        
    for(i = primeiro; i != ultimo; i = i.prox);
        
    int elemento = ultimo.elemento;   
        
    ultimo = tmp;
    tmp = tmp.prox = null;
    
    
    System.out.println(elemento);
        
    }
   
    public void remover(int pos){
        
        if(pos < 0 || pos > tamanho || primeiro == ultimo){
            throw new Exception("erro");
        }
        
        if(pos == primeiro){
            removerInicio();
        }else if(pos == tamanho){
            removerFim();
        }
        
        
        Celula i =primeiro;
        for(int j = 0; j != pos; j++ i = i.prox);
        
        Celula tmp = i.prox;
        i.prox = tmp.prox;
        tmp.prox = null;
        i = tmp = null 
        
        
        
        
        
        
        
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

public class ListaFlexivel {
    public static void main(String[] args) {
    
        try {
            Lista Lista = new Lista();
            Lista.inserir(4);
            Lista.inserir(5);
            Lista.inserir(2);
            Lista.inserir(6);
            Lista.inserir(8);
            Lista.mostrar();
          
            
  

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
       
        
    }
    
}
