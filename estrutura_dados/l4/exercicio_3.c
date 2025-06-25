#include "listas.h"

float media(Node* lista)
{
    Node* temp = lista;
    float acumulador=0, contador=0;
    while (temp!=NULL)
    {
        acumulador += temp->valor;
        contador++;
        temp = temp->prox;
    }
    float media = acumulador/contador;
    printf("\nA media dos valores e %.1f\n", media);
    return media;
}

int main()
{
    srand(time(NULL));
    Node* lista1 = cria_lista();
    Node* concatenada = cria_lista();
    lista1 = preenche_lista(lista1, 3);
    imprime_lista(lista1);
    media(lista1);
    return 0;
}