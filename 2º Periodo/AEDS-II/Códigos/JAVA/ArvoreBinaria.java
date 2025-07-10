class No { // classe responsavel pelo elemento e ponteiros de esquerda e direita da arvora

	int elemento;
	No esq;
	No dir;


	No(int elemento) { // construtor setando para null
		this(elemento, null, null);
	}

	No(int elemento, No esq, No dir) {

		this.elemento = elemento;
		this.dir = dir;
		this.esq = esq;

	}



}

class arvore {

	private No raiz;

	public arvore() {
		raiz = null;
	}

	void inserir(int x) {
		raiz = inserir(x, raiz); // o nC3 raiz recebe o elemento para inserir na arvore
	}

	No inserir(int x, No i) { // aqui criamos uma copia de x e de raiz

		if( i == null) { //  se a arvore estiver vazia inserimos na raiz
			i = new No(x);
		} else if(x > i.elemento) { // se o elemento C) maior vai para a direita

			i.dir = inserir(x, i.dir); // chama recursivamente a partir do nC3 a direita

		} else if(x < i.elemento) { // se o elemento C) menor vai para a esquerda

			i.esq = inserir(x, i.esq); // chama recursivamente a partir do nC3 a esquerda

		} else {

			System.out.print("ERRO!!");

		}

		return i;
	}



	boolean pesquisar(int x) {
		return pesquisar( x, raiz);
	}

	boolean pesquisar (int x, No i ) {

		boolean resp = false;

		if( i == null) { //  se a arvore estiver vazia inserimos na raiz
			resp = false;
		} else if(x == i.elemento) { // se o elemento C) maior vai para a direita

			resp = true; // chama recursivamente a partir do nC3 a direita

		} else if(x < i.elemento) { // se o elemento C) menor vai para a esquerda

			resp = pesquisar(x, i.esq); // chama recursivamente a partir do nC3 a esquerda

		} else if(x > i.elemento) { // se o elemento C) menor vai para a direita

			resp = pesquisar(x, i.dir); // chama recursivamente a partir do nC3 a direita

		}
		return resp;

	}

	void CaminharCentral() {
		CaminharCentral(raiz);
	}

	void CaminharCentral (No i) { // mostra os elementos em ordem crescente

		if( i != null) {

			CaminharCentral(i.esq);
			System.out.printf(i.elemento + " ");
			CaminharCentral(i.dir);

		}

	}


	void CaminharPosOrdem() {
		CaminharPosOrdem(raiz);
	}

	void CaminharPosOrdem (No i) {

		if( i != null) {

			CaminharCentral(i.esq);
			CaminharCentral(i.dir);
			System.out.printf(i.elemento + " ");


		}

	}


	void CaminharPreOrdem() {
		CaminharPreOrdem(raiz);
	}

	void CaminharPreOrdem (No i) { // mostra os filhos depois o pai

		if( i != null) {

			System.out.printf(i.elemento + " ");
			CaminharCentral(i.esq);
			CaminharCentral(i.dir);


		}

	}


int getMaior(){
    int maior = -1;
    
    if(raiz != null){
        No i;
        for( i = raiz; i.dir != null; i = i.dir);
        maior = i.elemento;
    
    }

    return maior;
}

int getMenor(){
   int menor = 10000;
    
    if(raiz != null){
        No i;
        for( i = raiz; i.esq != null; i = i.esq);
        menor = i.elemento;
    
    }

    return menor;
}


void remover(int x){
    
    raiz = remover(x, raiz);
}

No remover(int x, No i ){
    
 if( i == null){
     System.out.print("Erro ao remover");
 }else if ( i.elemento < x){
     
     i.dir = remover(x, i.dir);

 }else if ( i.elemento > x){
     
     i.esq = remover(x, i.esq);

 }else if (i.dir == null){
     i = i.esq;
 }else if (i.esq == null){
     i = i.dir;
 }else {
     i.esq = maiorEsq(i, i.esq);
 }
    
    return i;

    
}

No maiorEsq( No i, No j){
        
    if (j.dir == null){
        
        i.elemento = j.elemento;
        j = j.esq;
    } else{
        
        j.dir = maiorEsq(i, j.dir);
    }
        
    return j;
        
}







}


public class ArvoreBinaria
{
	public static void main(String[] args) {

		arvore arvoreBinaria = new arvore();

		arvoreBinaria.inserir(5);
		arvoreBinaria.inserir(8);
		arvoreBinaria.inserir(2);
		arvoreBinaria.inserir(3);
		arvoreBinaria.inserir(7);
		arvoreBinaria.inserir(9);
		arvoreBinaria.inserir(0);
		arvoreBinaria.inserir(1);
		arvoreBinaria.CaminharCentral();
		System.out.println(" ");
		arvoreBinaria.CaminharPreOrdem();
		System.out.println(" ");
		arvoreBinaria.CaminharPosOrdem();
		System.out.println(" ");



	}
}