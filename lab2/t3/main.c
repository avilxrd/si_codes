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

        resultado = insere_lista(resultado, res, false);
        a = a->ant;
        b = b->ant;
    }
    if (a != NULL)
    {
        while (a != NULL)
        {
            resultado = insere_lista(resultado, a->valor, false);
            a = a->ant;
        }
    }
    else if (b != NULL)
    {
        while (b != NULL)
        {
            resultado = insere_lista(resultado, b->valor, false);
            b = b->ant;
        }
    }
    if (carry == 1) resultado = insere_lista(resultado, carry, false);

    return resultado;
}

Node* subtrai_listas(Node* lista1, Node* lista2)
{
    Node* resultado = NULL;
    bool negativo=false;

    Node* a = lista1;
    Node* b = lista2;

    while (lista1!=NULL && lista2!=NULL)
    {
        if (lista1->valor < lista2->valor)
        {
            Node* temp;
            temp = a;
            a = b;
            b = temp;
            negativo=true;
            break;
        }
        else if (lista1->valor == lista2->valor)
        {
            lista1 = lista1->prox;
            lista2 = lista2->prox;
        }
        else break;

    }
    
    //se o resultado for negativo quebra
    // if (a->valor <= b->valor)
    // {
    //     printf("\nEncerrando pois nao trato negativos ainda...\n");
    //     return 0;
    // }

    a = final_lista(a);
    b = final_lista(b);
    

    int carry=0;
    while (a != NULL && b != NULL)
    {
        if (a->valor >= b->valor) resultado = insere_lista(resultado, a->valor - b->valor, negativo);
        else
        {
            a->ant->valor -= 1;
            a->valor += 10;
            resultado = insere_lista(resultado, a->valor - b->valor, negativo);  
        }
        a = a->ant;
        b = b->ant;
    }

    if (a != NULL)
    {
        while (a != NULL)
        {
            resultado = insere_lista(resultado, a->valor, negativo);
            a = a->ant;
        }
    }
    else if (b != NULL)
    {
        while (b != NULL)
        {
            resultado = insere_lista(resultado, b->valor, negativo);
            b = b->ant;
        }
    }
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
    for (int i=0; i<3; i++) num1 = insere_lista(num1, rand()%9, false);
    for (int i=0; i<3; i++) num2 = insere_lista(num2, rand()%9, false);

    //mostrando os numeros
    printf("\nNumero 1: \n");
    mostra_lista(num1);
    printf("\nNumero 2: \n");
    mostra_lista(num2);

    //somando um numero com o outro
    // printf("\nSoma das listas: \n");
    // Node* resultado = soma_listas(num1, num2);
    // mostra_lista(resultado);

    //subtraindo um numero com o outro
    printf("\nSubtração das listas: \n");
    Node* resultado = subtrai_listas(num1, num2);
    mostra_lista(resultado);


    //multiplicando por 2 (para testar, mas pode ser qualquer int (a principio)).
    // printf("\nMultiplicando por 2: \n");
    // mostra_lista(num1);
    // printf("x 2\n");
    // printf("___\n");
    // resultado = multiplica_lista(num1, 2);
    // mostra_lista(resultado);


    return 0;
}


