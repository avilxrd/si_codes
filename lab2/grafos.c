#include "grafos.h"
  
Grafo* cria_grafo(int num_vertices, int max_arestas, int ponderado)
{
    Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));

    if (grafo != NULL)
    {
        grafo->num_vertices = num_vertices;
        grafo->max_arestas  = max_arestas;
        grafo->ponderado    = (ponderado != 0) ? 1 : 0;
        grafo->grau         = (int*)calloc(num_vertices, sizeof(int));

        grafo->arestas      = (int**)malloc(num_vertices*sizeof(int));
        for (int i=0; i<num_vertices; i++) grafo->arestas[i] = (int*)malloc(max_arestas*sizeof(int));
        if (grafo->ponderado)
        {
            grafo->pesos = (float**)malloc(num_vertices*sizeof(float*));
            for (int i=0; i<num_vertices; i++) grafo->pesos[i] = (float*)malloc(max_arestas*sizeof(float));
        }
    }
    return grafo;
}

void libera_grafo(Grafo *grafo)
{
    if (grafo != NULL)
    {
        for (int i=0; i<grafo->num_vertices; i++) free(grafo->arestas[i]);
        free(grafo->arestas);

        if (grafo->ponderado)
        {
            for (int i=0; i<grafo->num_vertices; i++) free(grafo->pesos[i]);
            free(grafo->pesos);
        }
        free(grafo->grau);
        free(grafo);
    }
}

int insere_aresta(Grafo *grafo, int origem, int destino, int digrafo, float peso)
{
    if (grafo == NULL) return 0;
    if (origem <0 || origem  >= grafo->num_vertices) return 0;
    if (destino<0 || destino >= grafo->num_vertices) return 0;
    if (grafo->grau[origem] == grafo->)

}