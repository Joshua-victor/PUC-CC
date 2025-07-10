#include <iostream>
#include <string>
using namespace std;

void comparacao(string *um, string *dois) {
    int tamanho = um->length();
    int tamanho1 = dois->length();

    if (tamanho > tamanho1) {
        cout << "A primeira string é maior que a segunda.";
    } else if (tamanho < tamanho1) {
        cout << "A segunda string é maior que a primeira.";
    } else {
        cout << "As strings são iguais.";
    }
}

int main() {
    string um, dois;

    cout << "Digite a primeira string: ";
    cin >> um;

    cout << "Digite a segunda string: ";
    cin >> dois;

    comparacao(&um, &dois);

    return 0;
}
