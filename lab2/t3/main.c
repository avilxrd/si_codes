#include "listas.h"

Node* soma_listas(Node* lista1, Node* lista2) {
    Node* resultado = NULL;
    Node* a = lista1;
    Node* b = lista2;
    int cont=0;
    int arr[100];
    while (a != NULL && b != NULL) {
        arr[cont] = 
        // resultado = insere_lista(resultado, a->valor + b->valor);
        cont++;
        a = a->prox;
        b = b->prox;
    }

    return resultado;
}

int main()
{
    Node* num1 = NULL;
    Node* num2 = NULL;
    srand(time(NULL));
    for (int i=0; i<5; i++) num1 = insere_lista(num1, rand()%4);
    for (int i=0; i<5; i++) num2 = insere_lista(num2, rand()%4);
    mostra_lista(num1);
    mostra_lista(num2);

    Node* resultado = soma_listas(num1, num2);
    mostra_lista(resultado);

    return 0;
}


