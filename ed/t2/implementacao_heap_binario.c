#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemento_fila
{
    char descricao_elemento[255];
    int prioridade;
};

typedef struct elemento_fila Elemento;

struct fila_prioridade
{
    int quantidade;
    Elemento *elementos_fila;
};

typedef struct fila_prioridade FilaPrio;

/*
* recebe como parametro a fila e a posicao do ultimo elemento inserido
* a funcao calcula a posicao do pai desse elemento e comeca a subir a heap
* verificando se existe alguma violacao
* esse processo e feito enquanto o valor do filho for maior que 0 e a prioridade
* do pai for maior que a do filho
* se ambas condicoes forem verdadeiras, troca pai e filho 
*/

void promove_elemento(FilaPrio *fila, int filho)
{
    Elemento temp;
    int pai = (filho - 1) / 2;
    while ((filho > 0) && (fila->elementos_fila[pai].prioridade))
    {
        temp = fila->elementos_fila[filho];
        fila->elementos_fila[filho] = fila->elementos_fila[pai];
        fila->elementos_fila[pai] = temp;

        filho = pai;
        pai   = (pai - 1) / 2;
    }
}

#define MAX 50

int insere_fila_prioridade(FilaPrio *fila, Elemento elemento)
{
    if (fila == NULL) return 0;
    if (fila->quantidade == MAX) return 0;
    strcpy(fila->elementos_fila[fila->quantidade].descricao_elemento, elemento.descricao_elemento);
    fila->elementos_fila[fila->quantidade].prioridade = elemento.prioridade;
    promove_elemento(fila, fila->quantidade);
    fila->quantidade++;
    return 1;
}

void rebaixa_elemento(FilaPrio *fila, int pai)
{
    Elemento temp;
    int filho = (2 * pai) + 1;
    while (filho < fila->quantidade)
    {
        if (filho < fila->quantidade-1)
        {
            if (fila->elementos_fila[filho].prioridade < fila->elementos_fila[filho+1].prioridade) filho++;
        } 
        if (fila->elementos_fila[pai].prioridade >= fila->elementos_fila[filho].prioridade) break;
        temp = fila->elementos_fila[pai];
        fila->elementos_fila[pai] = fila->elementos_fila[filho];
        fila->elementos_fila[filho] = temp;

        pai = filho;
        filho = (2 * pai) + 1;
    }
}

int remove_fila_prioridade(FilaPrio *fila)
{
    if (fila == NULL) return 0;
    if (fila->quantidade == 0) return 0;
    fila->quantidade--;
    fila->elementos_fila[0] = fila->elementos_fila[fila->quantidade];
    rebaixa_elemento(fila, 0);
    return 1;
}

int consulta_fila_prioridade(FilaPrio *fila, char *descricao)
{
    if (fila == NULL || fila->quantidade == 0) return 0;
    strcpy(descricao, fila->elementos_fila[0].descricao_elemento);
    return 1;
}

void imprime_heap(FilaPrio *fila)
{
    if (fila == NULL || fila->quantidade == 0)
    {
        printf("Heap vazia.\n");
        return;
    }

    int nivel = 0;
    int elementos_no_nivel = 1;
    int i = 0;

    while (i < fila->quantidade)
    {
        printf("Nível %d: ", nivel);
        for (int j = 0; j < elementos_no_nivel && i < fila->quantidade; j++, i++)
        {
            printf("[%s, %d] ", fila->elementos_fila[i].descricao_elemento, fila->elementos_fila[i].prioridade);
        }
        printf("\n");
        nivel++;
        elementos_no_nivel *= 2;
    }
}

int main()
{
    Elemento e1 = {"prio 1", 1};
    Elemento e2 = {"prio 2", 2};
    Elemento e3 = {"prio 3", 3};
    Elemento e4 = {"prio 4", 4};
    Elemento e5 = {"prio 5", 5};
    Elemento e6 = {"prio 6", 6};
    Elemento e7 = {"prio 7", 7};
    Elemento e8 = {"prio 8", 8};

    FilaPrio fila;
    fila.quantidade = 0;
    fila.elementos_fila = malloc(sizeof(Elemento) * MAX);

    insere_fila_prioridade(&fila, e1);
    insere_fila_prioridade(&fila, e2);
    insere_fila_prioridade(&fila, e3);
    insere_fila_prioridade(&fila, e4);
    insere_fila_prioridade(&fila, e5);
    insere_fila_prioridade(&fila, e6);
    insere_fila_prioridade(&fila, e7);
    insere_fila_prioridade(&fila, e8);

    imprime_heap(&fila);

}