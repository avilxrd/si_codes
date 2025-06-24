// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct grafo
{
    int num_vertices;
    int num_arestas;
    int **matriz_adj;
};

typedef struct grafo Grafo;

static int** inicializa_matriz_adjacencia(int lin_col, int val)
{
    int **matriz = (int**) malloc(lin_col * sizeof(int*));
    for (int i=0; i<lin_col; i++)
    {
        matriz[i] = malloc(lin_col * sizeof(int*));
        for (int j=0; j<lin_col; j++) matriz[i][j] = val;
    }
    return matriz;
}

Grafo* inicializa_grafo(int vertices)
{
    Grafo *grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->num_vertices = vertices;
    grafo->num_arestas  = 0;
    grafo->matriz_adj   = inicializa_matriz_adjacencia(vertices, 0);
    return grafo;
}

#define vertice int

void inserir_arco_grafo(Grafo *grafo, vertice x, vertice y)
{
    x--;
    y--;

    if (grafo->matriz_adj[x][y] == 0)
    {
        grafo->matriz_adj[x][y] = 1;
        grafo->matriz_adj[y][x] = 1;
        grafo->num_arestas++;
    }
}

void remover_arco_grafo(Grafo *grafo, vertice x, vertice y)
{
    x--;
    y--;

    if (grafo->matriz_adj[x][y] == 1)
    {
        grafo->matriz_adj[x][y] = 0;
        grafo->matriz_adj[y][x] = 0;
        grafo->num_arestas--;
    }
}

void imprimir_grafo(Grafo *grafo)
{
    printf("\n");
    for (vertice i=0; i<grafo->num_vertices; i++)
    {
        printf("%d: ", i+1);
        for (vertice j=0; j<grafo->num_vertices; j++) if (grafo->matriz_adj[i][j] == 1) printf("%2d", j+1);
        printf("\n");
    }
    printf("\n");
}

void arquivo_para_grafo(Grafo *grafo, FILE *file)
{
    char linha[255];
    while (fgets(linha, sizeof(linha), file))
    {
        char filme[100], ator[100];
        strtok(filme, ",");
        strtok(ator,  ",");
        
    }
}

#define NUM_VERTICES 6
int main()
{
    FILE *file = fopen("filmes.csv", "r");
    Grafo *grafo = inicializa_grafo(NUM_VERTICES);
    static int visitados[NUM_VERTICES];

    inserir_arco_grafo(grafo, 1, 4);
    inserir_arco_grafo(grafo, 1, 5);
    inserir_arco_grafo(grafo, 2, 4);
    inserir_arco_grafo(grafo, 2, 6);
    inserir_arco_grafo(grafo, 3, 6);

    imprimir_grafo(grafo);

    return 0;
}
