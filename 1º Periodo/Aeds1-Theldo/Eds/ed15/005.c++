#include <iostream>
#include <cstring>
using namespace std;


char* str_chr(char* str, char c) {
    return strchr(str, c);
}

int main() {
    char str[] = "Hello, World!";
    char c = 'W';
    
    
    cout << " Digite a palavra ";
    cin >> str ; 
    
     cout << " Digite a letra";
    cin >> c ; 

    
    char* result = str_chr(str, c);
    
    if (result != NULL) {
        std::cout << "O caractere '" << c << "' foi encontrado na posição " << (result - str) << " da string." << std::endl;
    } else {
        std::cout << "O caractere '" << c << "' não foi encontrado na string." << std::endl;
    }
    
    return 0;
}
