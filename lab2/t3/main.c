#include "listas.h"

int main()
{
    char string[1000];
    printf("\nDIGITE UM NUMERO\n");
    printf("‣ ");
    fgets(string, 1000, stdin);
    Numero* num = NULL;
    num = ler_numero(string);

    imprime_numero(num);
    return 0;
}