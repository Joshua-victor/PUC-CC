        #include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

void acrescentarPalavra (string *palavra ){

   palavra->erase(palavra->begin());
    
}


int main()
{
    string palavra;
    string letra;

     cout << "digite a palavra que voce quer: ";
     cin >> palavra;

   
    
    acrescentarPalavra( &palavra );
    
    cout << palavra;
    

    return 0;
}