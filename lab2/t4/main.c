#include "pilhas.h"

void teste_pilhas()
{
    printf("Criando uma pilha de no máximo 3 elementos\n\n");
    Stack* pilha1 = cria_pilha(3);
    mostra_pilha(pilha1);
    printf("Inserindo 5 valores aleatórios na pilha\n\n");
    srand(time(NULL));
    for (int i=0; i<5; i++)
    {
        int valor_inserido = rand()%9;
        if (cheia(pilha1)) printf("Não tem espaço para o valor %d na pilha\n", valor_inserido);
        else printf("Inserindo o valor %d na pilha...\n", valor_inserido);
        push(pilha1, valor_inserido);
    }
    printf("\nValores inseridos com sucesso...\n");
    mostra_pilha(pilha1);
    printf("\n\n");

}

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
    teste_pilhas();
    
    //pilhas ok!, preciso agora fazer a lógica do jogo
    int quantidade;
    printf("\nQuantos elementos voce quer que tenha a pilha inicial? ");
    scanf("%d", &quantidade);

    Stack* pilhas[3];
    for (int i=0; i<3; i++)
    {
        pilhas[i] = cria_pilha(quantidade);
        if (i==0) for (int j=quantidade; j>0; j--) push(pilhas[i], j); //preenche a primeira
    } 
    mostra_pilha(pilhas[0]);

    int acabou = 0;
    
    while (acabou == 0)
    {
        printf("\nSelecione a pilha origem: ");
        printf("\n--> ");
        int origem, destino;
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
        for (int p=0; p<3; p++)
        {
            mostra_pilha(pilhas[p]);
        }
        //estou passando o indice, se quiser passar o numero
                                                         //da pilha preciso incrementar origem e destino

    }


}
