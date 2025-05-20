#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int valor;
    struct node *sad;
    struct node *sae;
} Node;

typedef struct {
    Node *raiz;
} Arvore;

Node* cria_arvore() {
    return NULL;
}

int arvore_vazia(Node *raiz) {
    return raiz == NULL;
}

void imprime_arvore(Node *raiz) {
    printf("< ");
    if (!arvore_vazia(raiz)) {
        printf("%d ", raiz->valor);
        imprime_arvore(raiz->sae);
        imprime_arvore(raiz->sad);
    }
    printf(" >");
}

Node* cria_node(int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->sad = NULL;
    novo->sae = NULL;
    novo->valor = valor;
    return novo;
}

void inserir(Node** raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = cria_node(valor);
        return;
    }

    if (valor < (*raiz)->valor)
        inserir(&((*raiz)->sae), valor);
    else
        inserir(&((*raiz)->sad), valor);
}

// recebe uma string e retorna um array de inteiros 
// com cada posição do vetor representando o código
// ascii do caractere correspondente
int* str_ascii(char *string)
{
    int len = strlen(string);
    int *str_ascii = (int*)malloc(len*sizeof(int));

    for (int i=0; i<len; i++) str_ascii[i] = (int)string[i];
    return str_ascii;
}

int* ascii_bin(int *ascii)
{
    
}

int main() {
    Arvore *arvore = (Arvore*)malloc(sizeof(Arvore));
    arvore->raiz = cria_arvore();

    inserir(&arvore->raiz, 0);
    inserir(&arvore->raiz, 1);
    inserir(&arvore->raiz, 1);
    imprime_arvore(arvore->raiz);

    return 0;
}
