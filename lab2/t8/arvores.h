#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct node{
    int fim_palavra;        // NULL para nós intermediários
    struct node *sae;       // 0
    struct node *sad;       // 1
};
typedef struct node Node;

Node* criar_node();

void insere_binario(Node *raiz, bool bit);

Node* insere_caractere(Node *raiz, char caractere);

void insere_palavra(Node *raiz, const char *palavra);

Node* arquivo_para_arvore(FILE *file);

bool buscaPalavra(Node* raiz, const char* palavra);
