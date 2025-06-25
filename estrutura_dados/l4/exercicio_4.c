#include "listas.h"

Node* retira_anterior(Node* lista, int x)
{
    Node* temp = lista;
    Node* anterior;

    while (temp != NULL && temp->prox->valor != x)
    {
        anterior = temp;
        temp = temp->prox;
    }
    anterior->prox = temp->prox;
    return lista;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 30);
    imprime_lista(lista1);
    retira_anterior(lista1, 2);
    imprime_lista(lista1);
    return 0;
}