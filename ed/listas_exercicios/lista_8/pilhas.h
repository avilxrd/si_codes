#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct pilha
{
    int max_elementos;
    int topo;
    int* valores;
};
typedef struct pilha Pilha;

struct fila
{
    int max_elementos;
    int index_fim;
    int* valores;
};
typedef struct fila Fila;

Pilha* cria_pilha(int max_elementos)
{
    //importante verificar se conseguiu alocar
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->max_elementos = max_elementos;
    pilha->topo = -1; //vazia
    pilha->valores = (int*) malloc(max_elementos* sizeof(int));
    return pilha;
}

Fila* cria_fila(int );