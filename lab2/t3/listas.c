#include "listas.h"

bool digito_valido(const char caractere)
{
    if (caractere >= 48 && caractere <= 57) return true;
    else return false;
}

Numero* insere_final(Numero* numero, int valor_inserido)
{
    Node* lista = numero->lista;
    //caso a lista esteja vazia
    if (lista == NULL)
    {
        Node* novo_node = (Node*)malloc(sizeof(Node));
        novo_node->ant  = NULL;
        novo_node->prox = NULL;
        novo_node->valor = valor_inserido;
        numero->lista = novo_node;
    }
    else
    {
        Node* temp = lista;
        while (temp->prox != NULL) temp = temp->prox;
        Node* novo_node = (Node*)malloc(sizeof(Node));
        novo_node->prox = NULL;
        novo_node->ant  = temp;
        novo_node->valor = valor_inserido;
        temp->prox = novo_node;
        numero->lista = lista;
    }
    return numero;
}

Numero* ler_numero(const char* string)
{
    Numero* numero = (Numero*)malloc(sizeof(Numero));
    numero->negativo = false;
    numero->lista    = NULL;

    int i=0;
    if (string[0] == '-')
    {
        numero->negativo = true;
        i++;
    }

    for (i; string[i] != '\0'; i++)
    {
        if (digito_valido(string[i]) == true)
        {
            int digito = string[i] - '0';
            numero = insere_final(numero, digito);
        }
    }
    return numero;
}

void imprime_numero(Numero* numero)
{
    Numero* temp = numero;
    printf("\nNUMERO DIGITADO\n");
    printf("‣ ");
    if (numero->negativo == true) printf("-");
    while (temp->lista != NULL)
    {
        printf("%d", temp->lista->valor);
        temp->lista = temp->lista->prox;
    }
    printf("\n");
}
