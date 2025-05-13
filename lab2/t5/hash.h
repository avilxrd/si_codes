#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define BRANCO   "\u001b[37m"
#define VERMELHO "\u001b[31m"
#define VERDE    "\u001b[32m"
#define AMARELO  "\u001b[33m"

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

void flush_in();

Node* insere_lista(Node* lista, Pessoa* pessoa);

Node** preenche_tabela(Node** tabela_hash, FILE* file);

void imprime_hash(Node** tabela);

Pessoa* busca_cpf(Node** tabela_hash, const char* cpf);

Pessoa* busca_arquivo(Node** );

Pessoa* ler_registro();

int adicionar_registro(Node** hash);

int remover_registro(Node** hash);
