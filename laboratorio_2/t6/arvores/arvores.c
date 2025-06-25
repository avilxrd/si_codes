#include "arvores.h"

Node* cria_arvore_binaria(void)
{
    return NULL;
}

void libera_node(Node *node)
{
    if (node == NULL) return;
    libera_node(node->sae);
    libera_node(node->sad);
    free(node);
    node = NULL;
}

void libera_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return;
    libera_node(raiz);
}

int esta_vazia_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return 1;
    return 0;
}

int total_no_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return 0;
    int total_esq = total_no_arvore_binaria(raiz->sae);
    int total_dir = total_no_arvore_binaria(raiz->sad);
    return (total_esq + total_dir + 1);
}

int altura_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return 0;
    int alt_esq = altura_arvore_binaria(raiz->sae);
    int alt_dir = altura_arvore_binaria(raiz->sad);
    if (alt_esq > alt_dir) return (alt_esq + 1);
    else return (alt_dir + 1);
}

void pre_ordem_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return;
    printf("%s\n", raiz->info);
    pre_ordem_arvore_binaria(raiz->sae);
    pre_ordem_arvore_binaria(raiz->sad);
}

void em_ordem_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return;
    em_ordem_arvore_binaria(raiz->sae);
    printf("%s\n", raiz->info);
    em_ordem_arvore_binaria(raiz->sad);
}

void pos_ordem_arvore_binaria(Node *raiz)
{
    if (raiz == NULL) return;
    pos_ordem_arvore_binaria(raiz->sae);
    pos_ordem_arvore_binaria(raiz->sad);
    printf("%s\n", raiz->info);
}

int insere_arvore_binaria(Node **raiz, char *valor)
{
    if (*raiz == NULL)
    {
        Node *novo = (Node*) malloc(sizeof(Node));
        if (novo == NULL) return 0;
        strcpy(novo->info, valor);
        novo->sad  = NULL;
        novo->sae  = NULL;
        *raiz = novo;
        return 1;
    }
    else
    {
        Node *atual = *raiz;
        Node *anterior = NULL;
        while(atual != NULL) 
        {
            anterior = atual;
            if (strcmp(valor, atual->info) == 0) return 0;
            if (strcmp(valor, atual->info) > 0) atual = atual->sad;
            else atual = atual->sae;
        } 
        Node *novo = (Node*) malloc(sizeof(Node));
        if (novo == NULL) return 0;
        strcpy(novo->info, valor);
        novo->sad  = NULL;
        novo->sae  = NULL;
        if (strcmp(valor, anterior->info) > 0) anterior->sad = novo;
        else anterior->sae = novo;
    }
    return 1;
}

void imprime_arvore(Node *raiz, int nivel)
{
    if (raiz == NULL) return;

    imprime_arvore(raiz->sad, nivel + 1);

    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%s\n", raiz->info); 

    imprime_arvore(raiz->sae, nivel + 1); 
}

int arvore_balanceada(Node *raiz)
{
    if (raiz == NULL) return 1;
    int alt_esquerda = altura_arvore_binaria(raiz->sae);
    int alt_direita  = altura_arvore_binaria(raiz->sad);
    if (abs (alt_esquerda - alt_direita) > 1) return 0;
    return arvore_balanceada(raiz->sae) && arvore_balanceada(raiz->sad);
}

int arvore_perfeitamente_balanceada(Node *raiz)
{
    if (raiz == NULL) return 1;
    int alt_esquerda = altura_arvore_binaria(raiz->sae);
    int alt_direita  = altura_arvore_binaria(raiz->sad);
    if (alt_esquerda != alt_direita) return 0;
    return arvore_perfeitamente_balanceada(raiz->sae) && arvore_perfeitamente_balanceada(raiz->sad);
}

void verifica_balanceamento(Node *raiz)
{
    if (arvore_balanceada(raiz)) 
    {
        if (arvore_perfeitamente_balanceada(raiz)) printf("A árvore é perfeitamente balanceada.\n");
        else printf("A árvore é balanceada.\n");
    } 
    else printf("A árvore NÃO é balanceada.\n");
}
