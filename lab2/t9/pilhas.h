#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

typedef struct pilha {
    int topo;
    int capacidade;
    int *elementos;
} Pilha;

Pilha* cria_pilha();

int pilha_vazia(Pilha *pilha);

int pop(Pilha *pilha);

Pilha* push(Pilha *pilha, int valor);

void imprime_pilha(Pilha *pilha);

void libera_pilha(Pilha *pilha);
