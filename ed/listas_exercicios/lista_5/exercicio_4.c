#include "listas.h"


int main()
{
    srand(time(NULL));
    Node* final = cria_lista();
    Node* lista1 = cria_lista();
    Node* lista2 = cria_lista();

    lista1 = preenche_lista(lista1, 10);
    imprime_lista(lista1);
    lista2 = preenche_lista(lista2, 10);
    imprime_lista(lista2);

    

    return 0;
}