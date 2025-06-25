#include "arvores.h"

Node* criar_node()
{
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->sae = NULL;
    novo->sad = NULL;
    novo->fim_palavra = false;
    return novo;
}

void insere_binario(Node *raiz, bool bit)
{
    if (bit == 0)
    {
        if (raiz->sae == NULL) raiz->sae = criar_node();
    } 
    else 
    {
        if (raiz->sad == NULL) raiz->sad = criar_node();
    }
}

Node* insere_caractere(Node *raiz, char caractere)
{
    for (int i = 7; i >= 0; i--)
    {
        int bit = (caractere >> i) & 1;
        insere_binario(raiz, bit);
        raiz = (bit == 0) ? raiz->sae : raiz->sad;
    }
    return raiz;
}

void insere_palavra(Node *raiz, const char *palavra)
{
    Node *atual = raiz;
    int len = strlen(palavra);
    for (int i = 0; i < len; i++)
    {
        char caractere = tolower(palavra[i]);
        atual = insere_caractere(atual, caractere);
    }
    atual->fim_palavra = true;
}


Node* arquivo_para_arvore(FILE *file)
{
    Node *raiz = criar_node();
    char buffer[255];

    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        insere_palavra(raiz, buffer);
    }
    return raiz;
}

bool buscaPalavra(Node* raiz, const char* palavra){
    int len = strlen(palavra);
    if(len == 0) return false;
    
    for(int i = 0; i < len; i++){
        char c = tolower(palavra[i]);
        
        for(int j = 7; j >= 0; j--){
            int bit = (c >> j) & 1;
            if(bit == 0){
                if(raiz->sae == NULL)
                {
                    printf("\nnao achou\n");
                    return false;
                } 
                raiz = raiz->sae;
            }
            else{
                if(raiz->sad == NULL)
                {
                    printf("\nnao achou\n");
                    return false;
                } 
                raiz = raiz->sad;
            }
        }
    }
    if (raiz->fim_palavra) {
        printf("\nachou\n");
        return true;
    } else {
        printf("\nnao achou\n");
        return false;
    }
}

