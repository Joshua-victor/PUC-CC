#include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

void acrescentarPalavra (string *palavra , string letra){

 palavra->insert(1, letra);
    
}


int main()
{
    string palavra;
    string letra;

     cout << "digite a palavra que voce quer: ";
     cin >> palavra;

     cout << "digite a letra que voce quer: ";
     cin >> letra;
    
    
    acrescentarPalavra( &palavra , letra);
    
    cout << palavra;
    

    return 0;
}