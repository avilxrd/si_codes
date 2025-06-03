#include "pilhas.h"

Pilha* cria_pilha(int max)
{
    Pilha *pilha;
    pilha->max_elementos = max;
    pilha->topo = -1;
    pilha->elementos = (int*) malloc (max * sizeof(int));
    return pilha;
}

int pilha_vazia(Pilha *pilha)
{
    if (pilha->topo == -1)
    {
        printf("\nPilha vazia!\n");
        return 1;
    }
    return 0;
}

int pilha_cheia(Pilha *pilha)
{
    if (pilha->topo == pilha->max_elementos -1)
    {
        printf("\nPilha cheia!\n");
        return 1;
    }
    return 0;
}

int pop(Pilha *pilha)
{
    if (pilha_vazia(pilha) == 1)
    {
        printf("\nNão foi feito o pop()\n");
        return 0;
    }
    int remov = pilha->elementos[pilha->topo]; 
    pilha->elementos[pilha->topo] = 0;
    pilha->topo--;
    return remov;
}

Pilha* push(Pilha *pilha)
{
    if (pilha_cheia(pilha) == 1)
    {
        printf("\nNão foi feito o push()\n");
        return pilha;
    }

    
}
