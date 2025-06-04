#include "listas.h"

Node* inverte_lista(Node *lista)
{
    Node *temp = lista;
    Node *ant = NULL, *prox = NULL; 
    
    while (temp != NULL)
    {
        prox = temp->prox;
        temp->prox = ant;
        ant = temp;
        temp = prox;
    }
    return ant;
}

int main()
{
    Node *lista = cria_lista();
    lista = preenche_lista(lista, 5);
    imprime_lista(lista);
    Node *lista_invertida;
    lista_invertida = inverte_lista(lista);
    imprime_lista(lista_invertida);
}
