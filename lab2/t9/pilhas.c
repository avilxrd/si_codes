#include "pilhas.h"

Pilha* cria_pilha(int max)
{
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->topo = -1;
    pilha->elementos = (char*) malloc (max * sizeof(char));
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

// int pilha_cheia(Pilha *pilha)
// {
//     if (pilha->topo == pilha->max_elementos -1)
//     {
//         printf("\nPilha cheia!\n");
//         return 1;
//     }
//     return 0;
// }

int pop(Pilha *pilha)
{
    if (pilha_vazia(pilha) == 1)
    {
        printf("\nNão foi feito o pop()\n");
        return 0;
    }
    pilha->elementos[pilha->topo] = '0';
    pilha->topo--;
}

Pilha* push(Pilha *pilha, const char valor)
{
    // if (pilha_cheia(pilha) == 1)
    // {
    //     printf("\nNão foi feito o push()\n");
    //     return pilha;
    // }
    pilha->topo++;
    pilha->elementos[pilha->topo] = valor;

    return pilha;
}

void imprime_pilha(Pilha *pilha)
{
    if (pilha_vazia(pilha) == 1) return;
    for (int i=pilha->topo; i>=0; i--) printf("\n[%d] %c", i, pilha->elementos[i]);
}
