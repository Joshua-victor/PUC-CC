
public void inserir( int elemento) {

	Tabela T1[], T3[];
	Lista ListaT1;
	Arvore ABT1, ABT3;

	int pos = h(elemento);


	if(T1[pos] == NULO) {

		T1[pos] = elemento;
	} else if {

	int posT2 = h(elemento);

		if(posT2 == 0) {

			int posT3 = h(elemento);
			if(T3[posT3] == NULO) {
				T3[posT3] = elemento;

			}

			posT3 = rehash(elemento);
			else if(posT3 == NULO) {

				T3[posT3] = elemento;


			} else if( T3[pos] != NULO) {

				ABT3.inserir(elemento)
			}


		} else if(posT2 == 1) {

			ListaT1.inserirfim(elemento);


		} else if(posT2 ==2) {

			ABT1.inserir(elemento)


		}



	}



}




