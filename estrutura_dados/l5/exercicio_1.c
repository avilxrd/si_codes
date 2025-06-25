#include "listas.h"

Node* retira_valor(Node* lista, int valor)
{
    Node* temp = lista;
    Node* ant = NULL;

    while (temp != NULL)
    {
        if (temp->valor == valor)
        {
            temp = temp->prox;         
            ant->prox = temp;
        }
        else 
        {
            ant = temp;
            temp = temp->prox;
        }
    }
    return lista;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 10);
    imprime_lista(lista1);
    lista1 = retira_valor(lista1, 2);
    imprime_lista(lista1);
    return 0;
}