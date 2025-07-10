

#include <iostream>

using namespace std;

void transformar_minuscula(char palavra[10]){
    
    
    
    for (int i = 0; i < 10 ; ++i) {
        palavra[i] = std::towlower(palavra[i]);
    }
    
   
    
}



int main()
{
    
    char palavra[10];
    
    cout<<"digite a palavra: ";
    cin >> palavra ; 
    
    transformar_minuscula(palavra);
    
    cout << "a palavra agora e:" << palavra ; 

    return 0;
}