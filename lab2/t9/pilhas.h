#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

struct pilha
{
    // int max_elementos;
    int topo;
    char *elementos;
};
typedef struct pilha Pilha;

Pilha* cria_pilha(int max);

int pilha_vazia(Pilha *pilha);

// int pilha_cheia(Pilha *pilha);

int pop(Pilha *pilha);

Pilha* push(Pilha *pilha, const char valor);

void imprime_pilha(Pilha *pilha);
