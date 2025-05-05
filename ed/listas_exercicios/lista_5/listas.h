#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int valor;
    struct node* prox;
};
typedef struct node Node;

Node* cria_lista();

Node* insere_lista(Node* lista, int valor);

Node* preenche_lista(Node* lista, int quantidade);

void imprime_lista(Node* lista);

Node* insere_final(Node* lista, int valor);