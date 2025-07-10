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

class Pilha {

    public Celula topo;

    public Pilha() {
        topo = null;
    }

    public void inserir(int x) {
        Celula tmp = new Celula(x);
        tmp.prox = topo;
        topo = tmp;
        tmp = null;
    }

    public int remover() throws Exception {
        if (topo == null) {
            throw new Exception("erro");
        }

        int removido = topo.elemento;
        Celula tmp = topo;
        topo = topo.prox;
        tmp.prox = null;
        tmp = null;

        return removido;
    }

    public void mostrar() {
        System.out.print("[");
        for (Celula i = topo; i != null; i = i.prox) {
            System.out.print(i.elemento + " ");
        }
        System.out.print("]");
        System.out.println(" ");
    }
    
      public void SomaElementos() {
        
        int soma = 0;
        for (Celula i = topo; i != null; i = i.prox) {
            
            soma += i.elemento;
            
        }
        
        System.out.println("soma dos elementos é:" + soma);
    }
    
    public void MaiorElemento(){
        int maior = 0;
        for (Celula i = topo; i != null; i = i.prox) {
            
            if(i.elemento > maior){
                
            maior = i.elemento;
            }
            
        }
        
        System.out.println("o maior elemento é:" + maior);
    }
    
       public void MostrarInverso(){
        
        int[] vetor = new int[6];
        int count = 0;
        
        for (Celula i = topo; i != null; i = i.prox) {
            
           vetor[count] = i.elemento;
           count++;
            
        }
        
        System.out.print("[");
        for (int i = 4; i >= 0; i--) {
            
           System.out.print(vetor[i] + " ");
            
        }
        System.out.print("]");

        
   
    }
    
  
   
}

public class PilhaFlexivel {
    public static void main(String[] args) {
    
        try {
            Pilha pilha = new Pilha();
            pilha.inserir(4);
            pilha.inserir(5);
            pilha.inserir(2);
            pilha.inserir(6);
            pilha.inserir(8);
            pilha.mostrar();
            pilha.SomaElementos();
            pilha.MaiorElemento();
            pilha.MostrarInverso();
            
  

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
       
        
    }
    
}
