#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tabela[26];

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

char* string_binario(char *string)
{
    int len = strlen(string);
    char *resultado = (char*) malloc (255*sizeof(char));
    int controlador=0;

    for (int i=0; i<len; i++)
    {
        char c = string[i];
        int val_c = (int)c;
        
        for (int j=0; j<26; j++)
        {
            // printf("\nVal_c = %d\nc = %c (%d)\n", val_c, c, (int)c);
            if (val_c == tabela[j])
            {
                printf("j+1 = %d, controlador = %d\n", j+1, controlador);
                resultado[controlador] = j+1;
                controlador++;
                break;
            } 
        }
    }
    for (int i=0; i<len; i++) printf("%d", resultado[i]);
    // printf("%s", resultado);
    return resultado;
}

void teste_string()
{
    char buffer[255];
    int size = sizeof(buffer);
    printf("Digite a string: ");
    // fgets(buffer, size,stdin);
    scanf("%s", buffer);
    char *res = (char*) malloc (255*sizeof(char));

    res = string_binario(buffer);
    printf("\nBinario: %s ", res);
}

int main() 
{
    Arvore *arvore = (Arvore*)malloc(sizeof(Arvore));
    arvore->raiz = cria_arvore();

    int j=97;
    for (int i=0; i<26; i++)
    {
        tabela[i] = j;
        j++;
    }

    // inserir(&arvore->raiz, 0);
    // inserir(&arvore->raiz, 1);
    // inserir(&arvore->raiz, 1);
    // imprime_arvore(arvore->raiz);
    teste_string();

    return 0;
}
