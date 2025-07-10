#include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

void acrescentarPalavra (string  *palavra , char letra){

  palavra->push_back(letra);
    
}


int main()
{
    string palavra;
    char letra;

     cout << "digite a palavra que voce quer: ";
     cin >> palavra;



    cout << "digite a letra que voce quer: ";
    cin >> letra;
    
    
    acrescentarPalavra(&palavra , letra);
    
    cout << palavra;
    

    return 0;
}