#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct diagonal
{
    int ordem;
    int* vetor;
};

typedef struct diagonal Diagonal;

Diagonal cria_matriz()
{
    Diagonal matriz_diagonal;
    printf("Digite o tamanho da Matriz Diagonal a ser armazenada: ");
    scanf("%d", &matriz_diagonal.ordem);

    //alocando o vetor
    matriz_diagonal.vetor = (int*)malloc(matriz_diagonal.ordem * sizeof(int));

    return matriz_diagonal;
}

//   preenche o vetor de valores da struct Diagonal
//0: usuario insere os elementos da matriz
//1: elementos gerados aleatoriamente
//   retorna apenas o vetor

int* preenche_matriz(Diagonal* matriz, int aleatorio)
{
    if (aleatorio != 0)
    {
        srand(time(NULL));
        for (int i=0; i<matriz->ordem; i++) matriz->vetor[i] = rand()%9 + 1;
    }
    else
    {
        printf("\n");
        for (int i=0; i<matriz->ordem; i++)
        {
            printf("Digite o valor do elemento da diagonal [%d][%d]: ", i, i);
            scanf("%d", &matriz->vetor[i]);
        }
    }
    return matriz->vetor;
}

//printa todos os elementos de uma matriz
void mostra_matriz(Diagonal* matriz)
{
    printf("\n");
    for (int i=0; i<matriz->ordem; i++)
    {
        for (int j=0; j<i; j++) printf("0  ");
        printf("\033[33m%d\033[37m  ", matriz->vetor[i]); // \033[ -> muda a cor do caractere | 33m = amarelo | 37m = branco
        for (int j=i; j<matriz->ordem-1; j++) printf("0  ");
        printf("\n");
    }
}

int consulta_matriz(int* vetor,int pos)
{
    printf("\nElemento na posicao [%d][%d]: %d", pos, pos, vetor[pos]);
    return vetor[pos];
}

int main()
{
    Diagonal matriz_diagonal = cria_matriz();

    matriz_diagonal.vetor = preenche_matriz(&matriz_diagonal, 1); //0: digitar numeros | 1: aleatorios
    mostra_matriz(&matriz_diagonal);
    for (int i=0; i<matriz_diagonal.ordem; i++)
    {
        consulta_matriz(matriz_diagonal.vetor, i);
    }
    printf("\n");
    return 0;
}


