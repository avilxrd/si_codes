#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

struct pessoa
{
    char nome[155];
    char cpf[20];
};

typedef struct pessoa Pessoa;

struct node
{
    Pessoa* pessoa;
    struct node* prox;
};

typedef struct node Node;

Node* insere_lista(Node* lista, Pessoa* pessoa);

Node** preenche_tabela(Node** tabela_hash, FILE* file);

void imprime_hash(Node** tabela);

Pessoa* busca_cpf(Node** tabela_hash, const char* cpf);

Pessoa* busca_arquivo(Node** );
