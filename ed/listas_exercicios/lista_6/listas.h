#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int valor;
    struct node* prox;
    struct node* ant;
};
typedef struct node Node;

Node* cria_lista()
{
    return NULL;
}

void imprime_lista(Node* lista)
{
    Node* temp = lista;
    while (temp != NULL)
    {
        printf("%d ", temp->valor);
        temp->ant = temp;
        temp = temp->prox;
    }
}