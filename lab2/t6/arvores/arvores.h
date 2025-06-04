#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estudei arvores pelo livro do professor Andre Backes de estrutura de dados.

struct node
{
    char info[10];
    struct node *sae;
    struct node *sad;
};
typedef struct node Node;

Node* cria_arvore_binaria(void);

void libera_node(Node *node);

void libera_arvore_binaria(Node *raiz);

int esta_vazia_arvore_binaria(Node *raiz);

int total_no_arvore_binaria(Node *raiz);

int altura_arvore_binaria(Node *raiz);

void pre_ordem_arvore_binaria(Node *raiz);

void em_ordem_arvore_binaria(Node *raiz);

void pos_ordem_arvore_binaria(Node *raiz);

int insere_arvore_binaria(Node **raiz, char *valor);

void imprime_arvore(Node *raiz, int nivel);

int arvore_balanceada(Node *raiz);

int arvore_perfeitamente_balanceada(Node *raiz);

void verifica_balanceamento(Node *raiz);
