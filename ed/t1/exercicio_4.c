#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cores.h"

struct matriz
{
    int x;
    int y; 
    int z; 
    int*** valores;
};
typedef struct matriz Matriz;

// 1. Alocação da matriz
int*** aloca_matriz(Matriz* matriz)
{
    matriz->valores = (int***)malloc(matriz->x * sizeof(int**));
    for (int i=0; i<matriz->x; i++)
    {
        matriz->valores[i] = (int**)malloc(matriz->y * sizeof(int*));
        for (int j = 0; j < matriz->y; j++) matriz->valores[i][j] = (int*)malloc(matriz->z * sizeof(int));
    }
    return matriz->valores;
}

// 2. Criação da matriz
Matriz* cria_matriz(int x, int y, int z)
{
    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    matriz->x = x;
    matriz->y = y;
    matriz->z = z;

    matriz->valores = aloca_matriz(matriz);
    return matriz;
}

// 3. Preenchimento dos valores aleatórios
void preenche_matriz(Matriz* matriz)
{
    for (int i=0; i<matriz->x; i++) for (int j=0; j<matriz->y; j++) for (int k=0; k<matriz->z; k++) matriz->valores[i][j][k] = rand()%9;
}

// 4. Impressão das camadas (z = profundidade)
void imprime_matriz(Matriz* matriz)
{
    for (int k=0; k<matriz->z; k++)
    {
        printf("\n%sCamada %d%s\n\t", COR_AMARELO, k, COR_BRANCO);

        for (int j=0; j<matriz->y; j++)
        {
            printf("%s%2d ", COR_AMARELO, j);
        }
        printf("%s\n\n", COR_BRANCO);

        for (int i=0; i<matriz->x; i++)
        {
            printf("%s%d\t%s", COR_AMARELO, i, COR_BRANCO);
            for (int j = 0; j < matriz->y; j++) printf("%2d ", matriz->valores[i][j][k]);
            printf("\n");
        }
    }
}


int main() 
{
    system("clear || cls");
    printf("NOVAMENTE, PARA TESTE ESTOU GERANDO OS VALORES ALEATORIAMENTE. OS NUMEROS SAO\n");
    printf("DE (1, 9) PARA FICAREM BEM ALINHADOS NO PRINTF E FACILITAR A VISUALIZACAO\n");
    srand(time(NULL));
    int x, y, z;
    printf("\nQuantidade de Linhas da Matriz  (x): ");
    scanf("%d", &x);
    printf("\nQuantidade de Colunas da Matriz (y): ");
    scanf("%d", &y);
    printf("\nProfundidade da Matriz          (z): ");
    scanf("%d", &z);
    Matriz* matriz = cria_matriz(x, y, z);
    preenche_matriz(matriz);
    imprime_matriz(matriz);

    return 0;
}