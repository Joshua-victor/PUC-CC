#include <stdio.h>

void recursive_procedure(char str[], int index)
{
    if (str[index] == '\0') {
       
        return;
    }

    printf("%c ", str[index]);
    recursive_procedure(str, index+1);
}

int main()
{
    char str[100];
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", str);
    recursive_procedure(str, 0);
    return 0;
}
