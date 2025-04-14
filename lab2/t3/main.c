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
        int res = carry + a->valor + b->valor;

        if (res >= 10)
        {
            res -= 10;
            carry = 1;
        }
        else 
        {
            carry=0;
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
    if (carry == 1) resultado = insere_lista(resultado, carry);

    return resultado;
}

Node* multiplica_lista(Node* lista1, int valor)
{
    Node* resultado = lista1;

    for (int i=1; i<valor; i++)
    {
        resultado = soma_listas(resultado, lista1);
    }

    return resultado;
}

int main()
{
    srand(time(NULL));
    Node* num1 = NULL;
    Node* num2 = NULL;

    //preenchendo as listas
    for (int i=0; i<100; i++) num1 = insere_lista(num1, rand()%9);
    for (int i=0; i<100; i++) num2 = insere_lista(num2, rand()%9);

    //mostrando os numeros
    printf("\nNumero 1: \n");
    mostra_lista(num1);
    printf("\nNumero 2: \n");
    mostra_lista(num2);

    //somando um numero com o outro
    printf("\nSoma das listas: \n");
    Node* resultado = soma_listas(num1, num2);
    mostra_lista(resultado);

    //multiplicando por 2 (para testar, mas pode ser qualquer int (a principio)).
    printf("\nMultiplicando por 2: \n");
    mostra_lista(num1);
    printf("x 2\n");
    printf("___\n");
    resultado = multiplica_lista(num1, 2);
    mostra_lista(resultado);


    return 0;
}


