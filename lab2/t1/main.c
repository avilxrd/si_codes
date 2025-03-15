#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct
{     
    int naipe;
    int valor;
}Carta;

// char lista_de_naipes[4][100] = {"♠", "♣", "♥", "♦"};
char lista_de_naipes[4][100] = {"♤", "♧", "♡", "♢"};

void mostra_baralho(Carta *baralho)
{
    printf("mostrando o baralho...\n");
    int contador=0;
    for (int i=0; i<4; i++)
    {
        printf("\n");
        for (int j=0; j<13; j++)
        {
            printf("%d%s\t", baralho[contador].valor, lista_de_naipes[baralho[contador].naipe]);
            contador++;
        }
    }
}

void preenche_baralho(Carta *baralho)
{
    int contador=0;

    printf("preenchendo o baralho...\n");
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<13; j++)
        {
            baralho[contador].naipe = i;
            baralho[contador].valor = j;
            contador++;
        }
    }
    printf("baralho preenchido!\n");
}

void trocar_cartas(Carta *a, Carta *b) //swap
{
    Carta temp;
    temp = *a;
    *a = *b;
    *b = temp;
}   

/*
percorre todas as cartas, trocando elas com outra de um índice aleatório
*/
void embaralhar_baralho(Carta *baralho)
{
    printf("embaralhando o baralho...\n");
    srand(time(NULL));
    for (int i=0; i<52; i++)
    {
        int random = rand()%(52);
        trocar_cartas(&baralho[i], &baralho[random]);
    }
    printf("baralho embaralhado.\n");
}

void teste_de_baralho(Carta *baralho)
{    
    preenche_baralho(baralho);
    mostra_baralho(baralho);
    printf("\n\n\n");
    embaralhar_baralho(baralho);
    mostra_baralho(baralho);
    printf("\n\n\n");
}

int main()
{
    Carta baralho[52];
    teste_de_baralho(baralho);
    return 0;
}

