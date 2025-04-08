#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct node{
    int valor;
    struct node* prox;
    struct node* ant;
};

typedef struct node Node;

//retorna um ponteiro NULL
Node* cria_lista();

//insere um elemento em uma lista
//0: inicio  1: final
Node* insere_lista(Node* lista, int valor_inserido/*, int flag*/);

//mostra todos os elementos de uma lista
void mostra_lista(Node* lista);
