#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

struct aluno
{
    char nome[155];
    char cpf[20];
};

typedef struct aluno Aluno;

struct node
{
    Aluno* aluno;
    struct node* prox;
};

typedef struct node Node;

Node* insere_lista(Node* lista, Aluno* aluno);

Node** preenche_tabela(Node** tabela_hash, FILE* file);

void imprime_hash(Node** tabela);

Aluno* busca_cpf(Node** tabela_hash, const char* cpf);
