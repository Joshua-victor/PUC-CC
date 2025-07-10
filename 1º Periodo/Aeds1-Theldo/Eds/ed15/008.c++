#include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

void acrescentarPalavra (string *um , string dois, int decisao){
 
 
  int tamanho = um->length();

if (decisao == 2){
 um->insert(tamanho, dois);
}

else {
    
     um->insert( 0 , dois);
    
}



}


int main()
{
    string um;
    string dois;
    int decisao = 0;

     cout << "digite a primeira string que voce quer: ";
     cin >> um;

     cout << "digite a segunda string que voce quer: ";
     cin >> dois;
     
     cout << " voce quer a segunda string na frente ou atras [1 = frente , 2 = atras]";
     cin >> decisao;
    
    
    acrescentarPalavra( &um , dois , decisao);
    
    cout << um;
    

    return 0;
}