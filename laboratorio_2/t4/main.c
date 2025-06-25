#include "pilhas.h"

int jogada_possivel(Stack* origem, Stack* destino)
{
    if (origem->topo != -1 && (origem->item[origem->topo] < destino->item[destino->topo] || destino->topo == -1))
    {
        printf("Status: [Jogada %sVALIDA%s]\n\n", VERDE, BRANCO);
        return 1;
    }
    printf("Status: [Jogada %sINVALIDA%s]\n\n", VERMELHO, BRANCO);
    return 0;
}

int main()
{
    system("clear");
    
    int quantidade, jogadas=0;
    printf("\nQuantos elementos voce quer que tenha a pilha inicial? ");
    scanf("%d", &quantidade);

    Stack* pilhas[QUANT_PILHAS];
    for (int i=0; i<QUANT_PILHAS; i++)
    {
        pilhas[i] = cria_pilha(quantidade);
        if (i==0) for (int j=quantidade; j>0; j--) push(pilhas[i], j); //preenche a primeira
    } 
    
    mostra_pilhas(pilhas, quantidade);

    int acabou = 0;
    while (acabou == 0)
    {
        int origem, destino;
        printf("\n\nSelecione a pilha origem: ");
        scanf("%d", &origem);
        printf("\nSelecione a pilha destino: ");
        scanf("%d", &destino);
        destino--;
        origem --;
        
        system("clear || cls");
        if (jogada_possivel(pilhas[origem], pilhas[destino]) == 1)
        {
            push(pilhas[destino], pilhas[origem]->item[pilhas[origem]->topo]);
            pop(pilhas[origem]);
            jogadas++;
        }

        printf("Jogadas feitas: %d\n", jogadas);
        mostra_pilhas(pilhas, quantidade);
        acabou = fim(pilhas, QUANT_PILHAS);
    }


}
