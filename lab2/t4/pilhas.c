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
    if (pilha->topo == -1)
    {
        printf("\n");
        for (int i=0; i<pilha->max_elementos; i++) printf ("\t|\n");
        printf("\n");
    }
    else
    {
        printf("\n");
        for (int i=0; i<pilha->max_elementos; i++)
        {
            if (i <= pilha->topo)
            {
                printf("\t");
                for (int j=0; j<pilha->item[i]; j++) printf("*");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf ("\t|\n");
                printf("\n");
            }

        } 
        printf("\n");

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
    free(pilha->item);                     //libera pilha1 região de memória onde estão os elementos
    free(pilha);                           //libera pilha1 região de memoria da pilha
    pilha = NULL;                          //arruma o ponteiro da pilha para NULL
}
