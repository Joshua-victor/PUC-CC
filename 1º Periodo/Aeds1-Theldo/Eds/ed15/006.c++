#include <iostream>
#include <cstring>

void separarPorDelimitador(char* cadeia, char delimitador) {
    char* ptr = cadeia;
    
    while (*ptr != '\0' && *ptr != delimitador) {
        std::cout << *ptr;
        ptr++;
    }
    
    std::cout << std::endl;
}

int main() {
    char cadeia[] = "Hello, World!";
    char delimitador = ',';
    
    separarPorDelimitador(cadeia, delimitador);
    
    return 0;
}
