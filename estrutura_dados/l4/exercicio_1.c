#include "listas.h"


Node* inverte_sinal(Node* lista)
{
    Node* temp = lista;
    while (temp != NULL)
    {
        temp->valor = temp->valor * (-1);
        temp = temp->prox;
    }
    return lista;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 3);
    imprime_lista(lista1);
    lista1 = inverte_sinal(lista1);
    imprime_lista(lista1);
    return 0;
}