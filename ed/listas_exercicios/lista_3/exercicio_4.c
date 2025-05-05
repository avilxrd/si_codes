#include "listas.h"

Node* concatena(Node* lista1, Node* lista2)
{
    Node* temp = lista1;
    while (temp->prox != NULL) temp = temp->prox;
    temp->prox = lista2;
    return lista1;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* lista2 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 3);
    lista2 = preenche_lista(lista2, 3);
    imprime_lista(lista1);
    imprime_lista(lista2);
    concatenada = concatena(lista1, lista2);
    imprime_lista(concatenada);
    return 0;
}