#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "cores.h"

#define MAX_VALUE 2 //valores maximos que estou gerando para
                    //preencher aleatoriamente a matriz.

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
    Node* temp = lista;
    Node* anterior = NULL;

    // Verificar se já existe um nó com mesma linha e coluna
    while (temp != NULL)
    {
        if (temp->linha == lin && temp->coluna == col)
        {
            temp->valor = valor_inserido; // substitui valor existente
            return lista;
        }
        anterior = temp;
        temp = temp->prox;
    }

    // Se não encontrou, cria um novo nó e adiciona ao final
    Node* novo_node   = (Node*)malloc(sizeof(Node));
    novo_node->valor  = valor_inserido;
    novo_node->linha  = lin;
    novo_node->coluna = col;
    novo_node->prox   = NULL;

    if (lista == NULL) return novo_node;

    anterior->prox = novo_node;
    return lista;
}


Matriz* preenche_matriz(Matriz* matriz, int ordem, bool random)
{
    Matriz* mat = matriz;

    mat->ordem = ordem;
    if (random == true)
    {
        for (int i=0; i<ordem; i++)
        {
            for (int j=0; j<ordem; j++)
            {
                int rand_int = rand()%MAX_VALUE;
                if (rand_int != 0) mat->valores = inserir_lista(mat->valores, rand_int, i, j);
            }
        }
    }
    else if (random == false)
    {
        int acabou=0;
        do
        {
            printf("Adicionando numeros na matriz\n");
            int lin, col, val;
            
            do{
                printf("\nLinha (0 a %d): ", ordem-1);
                scanf("%d", &lin);
            } while (lin < 0 || lin >= ordem);
            
            do{
                printf("\nColuna: (0 a %d): ", ordem-1);
                scanf("%d", &col);
            } while (col < 0 || col >= ordem);
            printf("\nValor para adicionar em [%d][%d]: ", lin, col);
            scanf("%d", &val);
            mat->valores = inserir_lista(mat->valores, val, lin, col);
            printf("\n0. Adicionar outro valor        1. Parar de adicionar:  ");
            scanf("%d", &acabou);
        } while (acabou == 0);
    }
    return mat;
}

//  3. mostrar a matriz
void mostra_lista(Node* lista)
{
    Node* temp = lista;
    int cont=0;
    printf("Mostrando os valores armazenados na memoria (struct node* valores): \n\n");
    while (temp!=NULL)
    {
        printf("%d ", temp->valor);
        temp = temp->prox;
        cont++;
    }
    printf("\n\nA matriz e de 5x5 --> 25 numeros.\n\nTemos %d numeros armazenados na lista.\n\n", cont);
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
    printf("\nMostrando a Matriz (os ZEROS nao estao guardados na memoria): \n\n");

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

int verifica_identidade(Matriz* matriz)
{
    int ordem = matriz->ordem;

    for (int i=0; i<ordem; i++)
    {
        for (int j=0; j<ordem; j++)
        {
            bool existe = busca_matriz(matriz->valores, i, j);

            if (i == j)
            {
                if (!existe)
                {
                    printf("\nRegra quebrada na diagonal [%d][%d]\n", i, j);
                    return i;
                }
                else
                {
                    Node* temp = matriz->valores;
                    while (temp != NULL)
                    {
                        if (temp->linha == i && temp->coluna == j && temp->valor != 1)
                        {
                            printf("\nRegra quebrada na diagonal [%d][%d]\n", i, j);
                            return i;
                        }
                        temp = temp->prox;
                    }
                }
            }
            else
            {
                if (existe)
                {
                    Node* temp = matriz->valores;
                    while (temp != NULL)
                    {
                        if (temp->linha == i && temp->coluna == j && temp->valor != 0)
                        {
                            printf("\nRegra quebrada fora da diagonal [%d][%d]\n", i, j);
                            return i;
                        }
                        temp = temp->prox;
                    }
                }
            }
        }
    }

    return 0;
}


int main()
{
    srand(time(NULL));
    int tamanho;
    printf("\nTamanho desejado da matriz: ");
    scanf("%d", &tamanho);
    Matriz* matriz = cria_matriz(tamanho);
    matriz = preenche_matriz(matriz, tamanho, false);
    mostra_lista(matriz->valores);
    imprime_matriz(matriz);
    printf("\nOBS: A FUNCAO RETORNA O INDICE DO PRIMEIRO lin/col QUE QUEBRA A REGRA\n\n");
    int identidade = verifica_identidade(matriz);
    if (identidade == -1) printf("\nIdentidade\n");
    else printf("\nNao Identidade\n");
}
