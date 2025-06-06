#include "pilhas.h"

#define CAPACIDADE_INICIAL 10

Pilha* cria_pilha()
{
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    if (!pilha) 
    {
        printf("erro ao alocar a pilha\n");
        exit(1);
    }

    pilha->topo = -1;
    pilha->capacidade = CAPACIDADE_INICIAL;
    pilha->elementos = (int*) malloc(pilha->capacidade * sizeof(int));

    if (!pilha->elementos) 
    {
        printf("erro ao alocar elementos da pilha\n");
        exit(1);
    }

    return pilha;
}

int pilha_vazia(Pilha *pilha)
{
    return pilha->topo == -1;
}

int pop(Pilha *pilha)
{
    if (pilha_vazia(pilha)) 
    {
        printf("Pilha vazia!\n");
        exit(1);
    }
    return pilha->elementos[pilha->topo--];
}

Pilha* push(Pilha *pilha, const int valor)
{
    // realoca a pilha quando necessario
    if (pilha->topo + 1 >= pilha->capacidade) 
    {
        pilha->capacidade *= 2;
        pilha->elementos = realloc(pilha->elementos, pilha->capacidade * sizeof(int));
        if (!pilha->elementos) 
        {
            printf("erro ao realocar elementos da pilha\n");
            exit(1);
        }
    }

    pilha->elementos[++pilha->topo] = valor;
    return pilha;
}

void imprime_pilha(Pilha *pilha)
{
    if (pilha_vazia(pilha)) 
    {
        printf("pilha vazia\n");
        return;
    }

    for (int i=pilha->topo; i>=0; i--) printf("[%d] %d\n", i, pilha->elementos[i]);   
}

void libera_pilha(Pilha *pilha)
{
    if (pilha) 
    {
        free(pilha->elementos);
        free(pilha);
    }
}
