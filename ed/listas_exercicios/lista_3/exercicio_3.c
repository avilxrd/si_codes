#include "listas.h"

Node* ultimo_node(Node* lista)
{
    Node* temp = lista;
    while (temp->prox != NULL) temp = temp->prox;
    return temp;
}

int main()
{
    srand(time(NULL));
    Node* lista = cria_lista();
    lista = preenche_lista(lista, 3);
    imprime_lista(lista);
    lista = ultimo_node(lista);
    imprime_lista(lista);
}