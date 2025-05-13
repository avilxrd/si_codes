#include "pilhas.h"

Stack* cria_pilha(int max_elementos)
{
    Stack* pilha = (Stack*)malloc(sizeof(Stack));
    pilha->max_elementos = max_elementos;
    pilha->topo          = -1;
    pilha->item          = (int*)malloc(max_elementos * sizeof(int)); 
    return pilha;
}
#define ESPACAMENTO_ENTRE_PILHAS "          "

void mostra_pilhas(Stack* pilhas[QUANT_PILHAS], int altura_maxima)
{
    int largura_max = altura_maxima * 2 - 1;
    char linha[256];

    // Cabeçalhos
    for (int p=0; p<QUANT_PILHAS; p++)
    {
        char titulo[16];
        sprintf(titulo, "Pilha %d", p + 1);
        int espacos = (largura_max - (int)strlen(titulo)) / 2;

        for (int i = 0; i < espacos; i++) printf(" ");
        printf("%s", titulo);
        for (int i = 0; i < largura_max - espacos - (int)strlen(titulo); i++) printf(" ");
        printf("       ");
    }
    printf("\n\n");

    // Corpo das pilhas
    for (int nivel = altura_maxima - 1; nivel >= 0; nivel--)
    {
        for (int p = 0; p < QUANT_PILHAS; p++)
        {
            memset(linha, ' ', largura_max);
            linha[largura_max] = '\0';

            if (pilhas[p]->topo >= nivel)
            {
                int valor = pilhas[p]->item[nivel];
                int largura = (valor * 2) - 1;
                int inicio = (largura_max - largura) / 2;
                for (int i = 0; i < largura; i++) linha[inicio + i] = '*';
            }
            else
            {
                int centro = largura_max / 2;
                linha[centro] = '|';
            }

            printf("%s", linha);
            printf(ESPACAMENTO_ENTRE_PILHAS);
        }
        printf("\n");
    }
    printf("\n");
}



int vazia(Stack* pilha)
{
    // printf("\nA pilha está vazia...\n");
    return (pilha->topo == -1);
}

int cheia(Stack* pilha)
{
    // printf("\nA pilha está cheia...\n");
    return (pilha->topo == pilha->max_elementos - 1);
}

void push(Stack* pilha, int elemento)
{
    if (cheia(pilha)) return;
    pilha->topo++;                         //incrementa o índice do elemento do topo
    pilha->item[pilha->topo] = elemento;   //adiciona o elemento ao array dos itens
}

int pop(Stack* pilha)
{
    if (vazia(pilha)) return -1;
    int x = pilha->item[pilha->topo];
    pilha->topo--;                         //decrementa o índice do elemento do topo
    return x;
}

int topo(Stack* pilha)
{
    if (vazia(pilha)) return 69;
    return pilha->item[pilha->topo];
}

void destroy(Stack* pilha)
{
    free(pilha->item);                     //libera pilha1 região de memória onde estão os elementos
    free(pilha);                           //libera pilha1 região de memoria da pilha
    pilha = NULL;                          //arruma o ponteiro da pilha para NULL
}

int fim(Stack** pilhas, int quant_pilhas)
{
    for (int i=0; i<quant_pilhas-1; i++) if (!vazia(pilhas[i]))
    {
        printf("\n\nalguma nao esta vazia\n\n");
        return 0;
    } 
    if (cheia(pilhas[quant_pilhas-1]))
    {
        printf("\n\na ultima esta cheia e todas as outras vazias\n\n");
        return 1;
    } 
    printf("\n\nnao devia chegar aqui\n\n");
    return 0;
}
