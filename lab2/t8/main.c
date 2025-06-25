#include "arvores.h"

/*
As árvores podem ser úteis como corretor ortográficos poderosos. 
Implemente um programa em duas partes:

A: montagem do dicionário. Inicialmente o programa lê uma lista de palavras em um arquivo, 
transforma as palavras para um código binário e as armazena em uma árvore;

B: busca de palavra. O programa recebe como entrada uma palavra, transforma a palavra para um código binário e busca a palavra no dicionário. 
O retorno é palavra encontrada ou palavra não encontrada.
*/

void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

int main()
{
    //1. criar o arquivo
    FILE *file = fopen("palavras", "r");
    if (!file)
    {
        printf("\nerro ao abrir o arquivo.\n");
        return -1;
    }

    //2. criar a arvore binaria
    Node *arvore = criar_node();
    arvore = arquivo_para_arvore(file);
    fclose(file);
    printf("\n");

    while(1)
    {
        printf("\n1. busca palavra\t2. encerra: ");
        int op;
        scanf("%d", &op);
        flush_in();
        if (op == 1)
        {
            printf("\npalavra: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            buscaPalavra(arvore, buffer);
        }
        else break;
    }
    printf("\nencerrando\n");
}