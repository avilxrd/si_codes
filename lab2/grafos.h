#include <stdio.h>
#include <stdlib.h>

struct grafo
{
    int ponderado;
    int num_vertices;
    int max_arestas;
    int **arestas;
    float **pesos;
    int *grau;
};

typedef struct grafo Grafo;

Grafo* cria_grafo(int num_vertices, int max_arestas, int ponderado);

void libera_grafo(Grafo *grafo);


