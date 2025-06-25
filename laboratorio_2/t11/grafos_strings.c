#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int id;
    struct No* prox;
} No;

typedef struct {
    char* nome;
    int tipo; 
    No* adj;  
} Vertice;

typedef struct {
    Vertice* lista;
    int tamanho;
    int capacidade;
} Grafo;

void inicializar_grafo(Grafo* grafo) 
{
    grafo->tamanho = 0;
    grafo->capacidade = 10;
    grafo->lista = malloc(grafo->capacidade * sizeof(Vertice));
}

int obter_ou_adicionar_vertice(Grafo* grafo, char* nome, int tipo) 
{
    for (int i=0; i<grafo->tamanho; i++) 
    {
        if (strcmp(grafo->lista[i].nome, nome) == 0) return i;
    }

    if (grafo->tamanho == grafo->capacidade) {
        grafo->capacidade *= 2;
        grafo->lista = realloc(grafo->lista, grafo->capacidade * sizeof(Vertice));
    }

    grafo->lista[grafo->tamanho].nome = strdup(nome);
    grafo->lista[grafo->tamanho].tipo = tipo;
    grafo->lista[grafo->tamanho].adj  = NULL;
    return grafo->tamanho++;
}

void adicionar_aresta(Grafo *grafo, int a, int b) 
{
    No* novoA = malloc(sizeof(No));
    novoA->id = b;
    novoA->prox = grafo->lista[a].adj;
    grafo->lista[a].adj = novoA;

    No* novoB = malloc(sizeof(No));
    novoB->id = a;
    novoB->prox = grafo->lista[b].adj;
    grafo->lista[b].adj = novoB;
}

void liberar_grafo(Grafo *grafo) 
{
    for (int i = 0; i < grafo->tamanho; i++) 
    {
        free(grafo->lista[i].nome);
        No* atual = grafo->lista[i].adj;
        while (atual) 
        {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(grafo->lista);
}

void buscar_filmes_do_ator(Grafo *grafo, char* nome) 
{
    int encontrado = 0;

    for (int i = 0; i < grafo->tamanho; i++) {
        if (strcmp(grafo->lista[i].nome, nome) == 0 && grafo->lista[i].tipo == 1) {
            encontrado = 1;
            printf("\nFilmes com %s:\n", grafo->lista[i].nome);
            No* p = grafo->lista[i].adj;
            int tem_filmes = 0;
            while (p) 
            {
                printf("  - %s\n", grafo->lista[p->id].nome);
                tem_filmes = 1;
                p = p->prox;
            }
            if (!tem_filmes) printf("  (Nenhum filme encontrado)\n");
            break;
        }
    }
    if (!encontrado) printf("\nAtor \"%s\" não encontrado no grafo.\n", nome);
}

void menu(Grafo *grafo) 
{
    int opcao;
    char buffer[256];

    do 
    {
        printf("\n1. buscar ator\t\t0. sair");
        char linha_opcao[16];
        printf("\n= ");
        fgets(linha_opcao, sizeof(linha_opcao), stdin);
        sscanf(linha_opcao, "%d", &opcao);

        switch (opcao) 
        {
            case 1:
                printf("\nNome do ator: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                buscar_filmes_do_ator(grafo, buffer);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

int main() 
{
    FILE* arq = fopen("entrada.csv", "r");
    if (!arq) 
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Grafo *grafo = (Grafo*) malloc(sizeof(grafo));
    inicializar_grafo(grafo);

    char linha[512];
    while (fgets(linha, sizeof(linha), arq)) 
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        char* filme = strtok(linha, ",");
        char* ator =  strtok(NULL, ",");

        if (!filme || !ator) continue;

        while (*filme == ' ') filme++;
        while (*ator == ' ') ator++;

        int id_filme = obter_ou_adicionar_vertice(grafo, filme, 0);
        int id_ator  = obter_ou_adicionar_vertice(grafo, ator, 1);

        adicionar_aresta(grafo, id_filme, id_ator);
    }

    fclose(arq);

    menu(grafo);
    liberar_grafo(grafo);
    return 0;
}
