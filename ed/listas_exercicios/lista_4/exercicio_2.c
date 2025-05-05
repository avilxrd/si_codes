#include "listas.h"

Node* insere_final(Node* lista, int valor)
{
    Node* temp = lista;
    while (temp->prox != NULL) temp = temp->prox;
    Node* novo = (Node*) malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox  = NULL;
    temp->prox = novo;
    return lista;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 3);
    imprime_lista(lista1);
    insere_final(lista1, 1);
    insere_final(lista1, 2);
    insere_final(lista1, 3);
    imprime_lista(lista1);
    return 0;
}