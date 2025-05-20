#include "listas.h"


void remove_repetidos(Node *lista) {
    Node *temp = lista;

    while (temp != NULL) 
    {
        Node *anterior = temp;
        Node *temp_prox = temp->prox;

        while (temp_prox != NULL) 
        {
            if (temp_prox->valor == temp->valor) 
            {
                anterior->prox = temp_prox->prox;
                free(temp_prox);
                temp_prox = anterior->prox;
            } 
            else 
            {
                anterior = temp_prox;
                temp_prox = temp_prox->prox;
            }
        }

        temp = temp->prox;
    }
}

// compara duas listas, e remove os elementos repetidos
// no caso, se repete nas duas listas remove a ocorrencia na segunda
// se repete na mesma lista, apenas remove
Node* intersec_lista(Node *lista1, Node *lista2)
{
    Node *lista3 = NULL;
    
    while (lista1)
    {
        lista3 = insere_inicio(lista3, lista1->valor);
        lista1 = lista1->prox;
    }
    while (lista2)
    {
        lista3 = insere_inicio(lista3, lista2->valor);
        lista2 = lista2->prox;
    }
    return lista3;
}

int main()
{
    srand(time(NULL));

    Node *lista1 = cria_lista();
    Node *lista2 = cria_lista();
    Node *lista3 = cria_lista();

    printf("obs: a ordem esta invertida pois estou inserindo no inicio da lista.\n\n");
    //lista 1
    lista1 = preenche_lista(lista1, 5);
    printf("lista 1                    : ");
    imprime_lista(lista1);
    remove_repetidos(lista1);
    printf("lista 1 (sem repeticao)    : ");
    imprime_lista(lista1);

    //lista 2
    lista2 = preenche_lista(lista2, 5);
    printf("lista 2                    : ");
    imprime_lista(lista2);
    remove_repetidos(lista2);
    printf("lista 2 (sem repeticao)    : ");
    imprime_lista(lista2);

    //lista 3
    lista3 = intersec_lista(lista1, lista2);
    printf("interseccao                : ");
    imprime_lista(lista3);

    remove_repetidos(lista3);
    printf("interseccao (sem repeticao): ");
    imprime_lista(lista3);
}
