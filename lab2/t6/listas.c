#include "listas.h"

Node* cria_lista()
{
    return NULL;
}

Node* insere_inicio(Node *lista, int elemento)
{
    Node *novo = (Node*) malloc (sizeof(Node));
    novo->valor = elemento;
    novo->prox  = lista;
    lista = novo;
    return lista;
}

Node* preenche_lista(Node *lista, int quantidade)
{
    for (int i=0; i<quantidade; i++) lista = insere_inicio(lista, rand()%9);
    return lista;
}

void imprime_lista(Node *lista)
{
     Node *temp = lista;
     while (temp != NULL)
     {
         printf("%d ", temp->valor);
         temp = temp->prox;
     }
     printf("\n");
}