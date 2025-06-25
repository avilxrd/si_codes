#include "listas.h"

int quantidade_nodes(Node* lista)
{
    Node* temp = lista;
    int cont=0;
    while (temp != NULL)
    {
        cont++;
        temp = temp->prox;
    }
    printf("\n%d nodes tem a lista.\n", cont);
    return cont;
}

int main()
{
    srand(time(NULL));
    Node* lista = cria_lista();
    lista = preenche_lista(lista, 3);
    imprime_lista(lista);
    quantidade_nodes(lista);
}