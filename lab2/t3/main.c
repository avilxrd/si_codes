#include "listas.h"

Node* soma_listas(Node* lista1, Node* lista2) {
    Node* resultado = NULL;
    Node* a = lista1;
    Node* b = lista2;

    a = final_lista(a);
    b = final_lista(b);

    int carry=0;
    while (a != NULL && b != NULL)
    {
        int res = a->valor + b->valor;
        if (res > 10)
        {
            printf("\ncarry: %d\tres: %d", carry, res);
        }

        resultado = insere_lista(resultado, res);
        a = a->ant;
        b = b->ant;
    }
    if (a != NULL)
    {
        while (a != NULL)
        {
            resultado = insere_lista(resultado, a->valor);
            a = a->ant;
        }
    }
    else if (b != NULL)
    {
        while (b != NULL)
        {
            resultado = insere_lista(resultado, b->valor);
            b = b->ant;
        }
    }

    return resultado;
}

int main()
{
    Node* num1 = NULL;
    Node* num2 = NULL;
    srand(time(NULL));
    for (int i=0; i<3; i++) num1 = insere_lista(num1, rand()%9);
    for (int i=0; i<3; i++) num2 = insere_lista(num2, rand()%9);
    mostra_lista(num1);
    mostra_lista(num2);

    Node* resultado = soma_listas(num1, num2);
    mostra_lista(resultado);

    return 0;
}


