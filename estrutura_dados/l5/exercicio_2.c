#include "listas.h"

Node* separa_lista(Node* lista, int n)
{
    Node* temp = lista;
    while (temp->valor != n) temp = temp->prox;

    Node* lista2 = temp->prox;
    temp->prox = NULL;
    return lista2;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 10);
    imprime_lista(lista1);
    Node* lista2 = separa_lista(lista1, 2);
    imprime_lista(lista2);
    return 0;
}