#include "listas.h"

Node* cria_lista()
{
    return NULL;
}

Node* insere_lista(Node* lista, int valor)
{
    Node* novo = (Node*) malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox = lista;
    return novo; 
}

Node* preenche_lista(Node* lista, int quantidade)
{
    for (int i=0; i<quantidade; i++) lista = insere_lista(lista, rand()%9);
    return lista;
}

void imprime_lista(Node* lista)
{
    Node* novo = lista;
    printf("lista: ");
    while(novo != NULL)
    {
        printf("%d ", novo->valor);
        novo = novo->prox;
    }
    printf("\n\n");
}

Node* insere_final(Node* lista, int valor) {
    Node* novo = malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox = NULL;

    if (lista == NULL) {
        return novo;
    } else {
        Node* temp = lista;
        while (temp->prox != NULL)
            temp = temp->prox;
        temp->prox = novo;
        return lista;
    }
}
