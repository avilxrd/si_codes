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

int main()
{
    system("clear");
    teste_pilhas();
}
