#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define BRANCO   "\e[0;37m"
#define VERMELHO "\e[0;31m"
#define VERDE    "\e[0;32m"
#define AMARELO  "\e[0;33m"

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

Node** preenche_tabela(Node** tabela_hash, FILE* file);

void imprime_hash(Node** tabela);

Pessoa* busca_cpf(Node** tabela_hash, const char* cpf);

Pessoa* ler_registro();

int adicionar_registro(Node** hash);

int remover_registro(Node** hash);

Node* insere_lista(Node* lista, Pessoa* pessoa);

void imprime_lista(Node* lista);

Node* arquivo_lista(Node *lista, FILE *file);

Pessoa* busca_lista(Node *lista, char *cpf);
