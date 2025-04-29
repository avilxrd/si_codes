#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//  lista duplamente encadeada de inteiros
struct node{
    int          valor;
    struct node* prox;
    struct node* ant;
};
typedef struct node Node;

//  representacao de um numero com lista
struct numero{
    bool  negativo;
    Node* lista;
};
typedef struct numero Numero;

Numero* insere_final(Numero* numero, int valor_inserido);

//  le o input de uma string pelo usuario e 
//  transforma em uma lista encadeada
Numero* ler_numero(const char* string);

//  printa o numero
void imprime_numero(Numero* numero);
