#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct node{
    int          valor;
    int          linha;
    int          coluna;
    struct node* prox;
};

typedef struct node Node;

struct matriz{
    int   ordem;
    Node* valores;
};
typedef struct matriz Matriz;

//  1. criar a matriz
Matriz* cria_matriz(int ordem)
{
    Matriz* matriz  = (Matriz*)malloc(sizeof(Matriz));
    matriz->ordem   = ordem;
    //talvez eu precise alocar a memoria para esse ponteiro
    matriz->valores = NULL;
    return matriz;
}

//  2. preenchimento da matriz
Node* inserir_lista(Node* lista, int valor_inserido, int lin, int col)
{
    Node* novo_node   = (Node*)malloc(sizeof(Node));
    novo_node->prox   = NULL;
    novo_node->valor  = valor_inserido;
    novo_node->linha  = lin;
    novo_node->coluna = col;

    //caso a lista esteja vazia
    if (lista == NULL) return novo_node;

    Node* temp = lista;
    while (temp->prox != NULL) temp=temp->prox;
    temp->prox = novo_node;
    return lista;

}

Matriz* preenche_matriz(Matriz* matriz, int ordem, bool random)
{
    Matriz* mat = matriz;

    mat->ordem = ordem;
    for (int i=0; i<ordem; i++)
    {
        for (int j=0; j<ordem; j++)
        {
            if (random == true) mat->valores = inserir_lista(mat->valores, rand()%9, i, j);
            else
            {
                int val;
                printf("\n[%d][%d]: ", i, j);
                scanf("%d", &val);
                mat->valores = inserir_lista(mat->valores, val, i, j);
            }
        }
    }
    return mat;
}

//  3. mostrar a matriz
void mostra_lista(Node* lista)
{
    Node* temp = lista;
    int cont = 0;
    while (temp!=NULL)
    {
        printf("%d ", temp->valor);
        temp = temp->prox;
        cont++;
    }
    printf("\nok\n");
}

bool busca_matriz(Node* matriz, int lin, int col)
{
    Node* temp = matriz;
    while (temp != NULL)
    {
        if (temp->linha == lin && temp->coluna == col) return true;
        temp = temp->prox;
    }
    return false;

}

void imprime_matriz(Matriz* matriz)
{
    Node* temp = matriz->valores;

    for (int i=0; i<matriz->ordem; i++)
    {
        for (int j=0; j<matriz->ordem; j++)
        {
            bool busca = busca_matriz(temp, i, j);
            if (busca == true)
            {
                printf("%d ", temp->valor);
                temp = temp->prox;
            }
            else printf("0 ");
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    Matriz* matriz = cria_matriz(5);
    matriz = preenche_matriz(matriz, 5, true);
    mostra_lista(matriz->valores);
    imprime_matriz(matriz);
}
