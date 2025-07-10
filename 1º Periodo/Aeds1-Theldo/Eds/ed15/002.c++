#include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

void acrescentarPalavra (string *palavra){

 palavra->pop_back();
    
}


int main()
{
    string palavra;
    char letra;

     cout << "digite a palavra que voce quer: ";
     cin >> palavra;

    
    
    acrescentarPalavra( &palavra);
    
    cout << palavra;
    

    return 0;
}