#include "listas.h"

//retorna um ponteiro NULL
Node* cria_lista()
{
    return NULL;
}

//insere um elemento no inicio de uma lista
//0: insere no inicio da lista
//1: insere no final  da lista
Node* insere_lista(Node* lista, int valor)
{  
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox = lista;
    novo->ant = NULL;
    if (lista != NULL) lista->ant = novo;
    return novo;
}

Node* insere_final(Node* lista, int valor_inserido)
{
    //caso a lista esteja vazia
    if (lista == NULL)
    {
        Node* novo_node = (Node*)malloc(sizeof(Node));
        novo_node->ant  = NULL;
        novo_node->prox = NULL;
        novo_node->valor = valor_inserido;
        return novo_node;
    }
    else
    {
        Node* temp = lista;
        while (temp->prox != NULL) temp = temp->prox;
        Node* novo_node = (Node*)malloc(sizeof(Node));
        novo_node->prox = NULL;
        novo_node->ant  = temp;
        novo_node->valor = valor_inserido;
        temp->prox = novo_node;
        return lista;
    }

}

Node* final_lista(Node* lista)
{
    if (lista == NULL) return lista;
    else
    {
        while (lista->prox != NULL) lista = lista->prox;
        return lista;
    }
}

void mostra_lista(Node* lista)
{
    Node* novo;
    printf("\n--> ");
    for (novo=lista; novo!=NULL; novo=novo->prox) printf("%d ", novo->valor);
    printf("\n");
}

