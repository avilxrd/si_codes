#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//estrutura da pilha
//como não vimos em ED ainda, vi aqui: https://dev.to/josethz00/data-structures-in-c-stack-55c7
typedef struct stack
{
    int max_elementos;      //numero maximo de elementos que a pilha comporta
    int topo;               //indice do último item a entrar na pilha
    int* item;              //ponteiro para um tipo de dados que armazenará todos os itens da pilha (nesse caso, um vetor de int)
}Stack;

//retorna um ponteiro para uma estutura Stack
Stack* cria_pilha(int max_elementos);

//mostra todos os elementos de uma pilha
void mostra_pilha(Stack* pilha);

//retorna se a pilha esta vazia
int vazia(Stack* pilha);

//retorna se a pilha esta cheia
int cheia(Stack* pilha);

//insere um elemento no topo da pilha
void push(Stack* pilha, int elemento);

//remove o elemento do topo de uma pilha
int pop(Stack* pilha);

//retorna o item do topo de uma pilha
int topo(Stack* pilha);

//destroi uma pilha
void destroy(Stack* pilha);
