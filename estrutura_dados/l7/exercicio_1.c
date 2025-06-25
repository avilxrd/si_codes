#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int matricula;
    char nome[50];
    struct node* prox;
};
typedef struct node Node;

void imprime_lista(Node* lista)
{
    Node* temp = lista;
    while (temp != NULL)
    {
        printf("\nMatricula: %d\tNome: %s\n", temp->matricula, temp->nome);
        temp = temp->prox;
    }
}

Node* insere_lista()
{

}