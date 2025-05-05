#include "listas.h"

Node* merge(Node* lista1, Node* lista2)
{
    Node *temp_1 = lista1, *temp_2 = lista2;
    Node *final = cria_lista(); 
    
    int cont=0;
    while (temp_1 != NULL && temp_2 != NULL)
    {
        printf("%d\n", cont);
        if (cont%2 == 0)
        {
            final = insere_final(final, temp_1->valor);
            temp_1 = temp_1->prox;
        }
        else
        {
            final = insere_final(final, temp_2->valor);
            temp_2 = temp_2->prox;
        }
        cont++;
    }

    while (temp_1 != NULL || temp_2 != NULL)
    {
        if (temp_1 != NULL)
        {
            final = insere_final(final, temp_1->valor);
            temp_1 = temp_1->prox;
        }
        else
        {
            final = insere_final(final, temp_2->valor);
            temp_2 = temp_2->prox;
        }                
    }
    return final;
}

int main()
{
    srand(time(NULL));
    Node* final = cria_lista();
    Node* lista1 = cria_lista();
    Node* lista2 = cria_lista();

    lista1 = preenche_lista(lista1, 10);
    imprime_lista(lista1);
    lista2 = preenche_lista(lista2, 10);
    imprime_lista(lista2);

    final = merge(lista1, lista2);
    imprime_lista(final);
    return 0;
}