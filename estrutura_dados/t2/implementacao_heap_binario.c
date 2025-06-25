#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COR_VERDE    "\033[32m"
#define COR_AMARELO  "\033[33m"
#define COR_VERMELHO "\033[31m"
#define COR_BRANCO   "\033[37m"

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
    while ((filho > 0) && (fila->elementos_fila[filho].prioridade > fila->elementos_fila[pai].prioridade))
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

    for (int i = 0; i < fila->quantidade; i++)
    {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        printf("%sNó%s\t", COR_AMARELO, COR_BRANCO);
        printf("[ %s | %s%d%s ] ", fila->elementos_fila[i].descricao_elemento, COR_VERDE, fila->elementos_fila[i].prioridade, COR_BRANCO);

        if (esq < fila->quantidade)
            printf("%s➚%s Filho esquerda: [%s, %d] ", COR_VERMELHO, COR_BRANCO, fila->elementos_fila[esq].descricao_elemento, fila->elementos_fila[esq].prioridade);
        else printf("%s➚%s Filho esquerda: [%svazio%s] ", COR_VERMELHO, COR_BRANCO, COR_VERMELHO, COR_BRANCO);

        if (dir < fila->quantidade)
            printf("%s➘%s Filho direita: [%s, %d] ", COR_VERMELHO, COR_BRANCO, fila->elementos_fila[dir].descricao_elemento, fila->elementos_fila[dir].prioridade);
        else printf("%s➘%s Filho direita: [%svazio%s] ", COR_VERMELHO, COR_BRANCO, COR_VERMELHO, COR_BRANCO);

        printf("\n");
    }
}

void mostra_aviso()
{
    printf("\nobs: na nossa implementação, um Nó consiste em duas informações: \n");
    printf("\n%schar%s descricao[%s255%s]\t\t//string com a descrição do elemento", COR_AMARELO, COR_BRANCO, COR_VERMELHO, COR_BRANCO);
    printf("\n%sint%s  prioridade\t\t\t//int com a prioridade do elemento\n", COR_AMARELO, COR_BRANCO);
    printf("\n\npara facilitar, ao 'printar' um nó utilizaremos o seguinte formato: \n\n");
    printf("[ %sDescrição%s | %sPrioridade%s ] \n\n", COR_AMARELO, COR_BRANCO, COR_AMARELO, COR_BRANCO);
}

Elemento criar_elemento()
{
    Elemento elemento;
    printf("\n%sDigite a prioridade%s: ", COR_AMARELO, COR_BRANCO);
    scanf("%d", &elemento.prioridade);
    printf("\n%sDigite a descricao%s:  ", COR_AMARELO, COR_BRANCO);
    scanf("%s", &elemento.descricao_elemento);
    return elemento;
}

int main()
{
    FilaPrio *fila = (FilaPrio*) malloc(sizeof(FilaPrio));
    fila->quantidade = 0;
    fila->elementos_fila = (Elemento*)malloc(sizeof(Elemento) * MAX);

    while(1)
    {
        printf("\n%s0%s. Sair   %s1%s. Mostrar heap (nós)   %s2%s. Inserir elemento   %s3%s. Remover elemento   \n\n-> ", COR_AMARELO, COR_BRANCO, COR_AMARELO, COR_BRANCO, COR_AMARELO, COR_BRANCO, COR_AMARELO, COR_BRANCO);
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 0) break;
        else
        {
            if      (opcao == 1) imprime_heap(fila);
            else if (opcao == 2)
            {
                Elemento elemento = criar_elemento();
                insere_fila_prioridade(fila, elemento);
            }
            else if (opcao == 3) remove_fila_prioridade(fila);
            else break;
        }
    }
    printf("\nencerrando...\n");

}