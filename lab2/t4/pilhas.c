#include "pilhas.h"

Stack* cria_pilha(int max_elementos)
{
    Stack* pilha = (Stack*)malloc(sizeof(Stack));
    pilha->max_elementos = max_elementos;
    pilha->topo          = -1;
    pilha->item          = (int*)malloc(max_elementos * sizeof(int)); 
    return pilha;
}

void mostra_pilha(Stack* pilha)
{
    if (vazia(pilha)) return;
    int quant_elementos = pilha->topo + 1;
    printf("\nImprimindo uma pilha:\n");
    for (int i=quant_elementos-1; i>=0; i--)
    {
        printf("\npilha[%d]:\t%d", i, pilha->item[i]);
        printf("\t"); 
        for (int x=0; x<pilha->item[i]; x++) printf("#");
    } 
}


int vazia(Stack* pilha)
{
    // printf("\nA pilha está vazia...\n");
    return (pilha->topo == -1);
}

int cheia(Stack* pilha)
{
    // printf("\nA pilha está cheia...\n");
    return (pilha->topo == pilha->max_elementos - 1);
}

void push(Stack* pilha, int elemento)
{
    if (cheia(pilha)) return;
    pilha->topo++;                         //incrementa o índice do elemento do topo
    pilha->item[pilha->topo] = elemento;   //adiciona o elemento ao array dos itens
}

int pop(Stack* pilha)
{
    if (vazia(pilha)) return 69;
    int x = pilha->item[pilha->topo];
    pilha->topo--;                         //decrementa o índice do elemento do topo
    return x;
}

int topo(Stack* pilha)
{
    if (vazia(pilha)) return 69;
    return pilha->item[pilha->topo];
}

void destroy(Stack* pilha)
{
    free(pilha->item);                     //libera a região de memória onde estão os elementos
    free(pilha);                           //libera a região de memoria da pilha
    pilha = NULL;                          //arruma o ponteiro da pilha para NULL
}
