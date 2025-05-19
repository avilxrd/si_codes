#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int valor;
    struct node *prox;
};

typedef struct node Node;

Node* cria_lista()
{
    return NULL;
}

Node* insere_inicio(Node *lista, int elemento)
{
    Node *novo = (Node*) malloc (sizeof(Node));
    novo->valor = elemento;
    novo->prox  = lista;
    lista = novo;
    return lista;
}

Node* preenche_lista(Node *lista, int quantidade)
{
    srand(time(NULL));
    for (int i=0; i<quantidade; i++) lista = insere_inicio(lista, rand()%9);
    return lista;
}

void imprime_lista(Node *lista)
{
     Node *temp = lista;
     while (temp != NULL)
     {
         printf("%d ", temp->valor);
         temp = temp->prox;
     }
     printf("\n");
}

Node* inverte_lista(Node *lista)
{
    Node *temp = lista;
    Node *ant = NULL, *prox = NULL; 
    
    while (temp != NULL)
    {
        prox = temp->prox;
        temp->prox = ant;
        ant = temp;
        temp = prox;
    }
    return ant;
}

int main()
{
    Node *lista = cria_lista();
    lista = preenche_lista(lista, 5);
    imprime_lista(lista);
    Node *lista_invertida;
    lista_invertida = inverte_lista(lista);
    imprime_lista(lista_invertida);
}
