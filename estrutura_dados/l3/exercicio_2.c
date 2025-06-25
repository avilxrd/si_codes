#include "listas.h"

int maiores(Node* lista, int n)
{
    Node* temp = lista;
    int cont=0;
    while (temp != NULL)
    {
        if (temp->valor > n) cont++;
        temp = temp->prox;
    }
    printf("\nA lista possui %d valores maiores que %d.\n", cont, n);
    return cont;
}

int main()
{
    srand(time(NULL));
    Node* lista = cria_lista();
    lista = preenche_lista(lista, 3);
    imprime_lista(lista);
    maiores(lista, 5);
}