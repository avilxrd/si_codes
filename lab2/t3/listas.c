#include "listas.h"

//retorna um ponteiro NULL
Node* cria_lista()
{
    return NULL;
}

//insere um elemento no inicio de uma lista
Node* insere_lista(Node* lista, int valor)
{
  Node* novo = (Node*)malloc(sizeof(Node));
  novo->valor = valor;
  novo->prox = lista;
  novo->ant = NULL;
  if (lista != NULL) lista->ant = novo;
  return novo;
}

void mostra_lista(Node* lista)
{
    Node* novo;
    printf("\n--> ");
    for (novo=lista; novo!=NULL; novo=novo->prox) printf("%d ", novo->valor);
    printf("\n");
}
