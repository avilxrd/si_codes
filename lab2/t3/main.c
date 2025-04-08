#include "listas.h"

Node* soma_listas(Node* lista1, Node* lista2)
{
    Node* resultado = (Node*)malloc(9*sizeof(Node));
    Node* a=lista1; 
    Node* b=lista2;
    for (a, b; a->prox!=NULL && b->prox!=NULL; a=a->prox, b=b->prox)
    {
        
    }
}

int main()
{
    Node* num1 = NULL;
    Node* num2 = NULL;
    srand(time(NULL));
    for (int i=0; i<5; i++) num1 = insere_lista(num1, rand()%9);
    for (int i=0; i<5; i++) num2 = insere_lista(num2, rand()%9);
    mostra_lista(num1);
    mostra_lista(num2);

    return 0;
}
