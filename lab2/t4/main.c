#include "pilhas.h"

int jogada_possivel(Stack* origem, Stack* destino)
{
    if (origem->item[origem->topo] < destino->item[destino->topo] || destino->topo == -1)
    {
        printf("\nJOGADA VALIDA\n");
        return 1;
    }
    printf("\nJOGADA INVALIDA\n");
    return 0;
}

int main()
{
    system("clear");
    
    int quantidade;
    printf("\nQuantos elementos voce quer que tenha a pilha inicial? ");
    scanf("%d", &quantidade);

    Stack* pilhas[3];
    for (int i=0; i<3; i++)
    {
        pilhas[i] = cria_pilha(quantidade);
        if (i==0) for (int j=quantidade; j>0; j--) push(pilhas[i], j); //preenche a primeira
    } 
    
    for (int i=0; i<3; i++) mostra_pilha(pilhas[i]);

    int acabou = 0;
    while (acabou == 0)
    {
        int origem, destino;
        printf("\n\nSelecione a pilha origem: ");
        scanf("%d", &origem);
        printf("\nSelecione a pilha destino: ");
        printf("\n--> ");
        scanf("%d", &destino);
        destino--;
        origem --;
        
        system("clear");
        if (jogada_possivel(pilhas[origem], pilhas[destino]) == 1)
        {
            push(pilhas[destino], pilhas[origem]->item[pilhas[origem]->topo]);
            pop(pilhas[origem]);
        }

        for (int i=0; i<3; i++) mostra_pilha(pilhas[i]);

    }


}
