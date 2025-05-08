#include "hash.h"

int main()
{
    Node** tabela_hash = (Node**) malloc(9*sizeof(Node)); //tabela com os nós de uma lista
    for (int i = 0; i < 9; i++) 
    {
        tabela_hash[i] = NULL;
    }    

    FILE *file = fopen("dezmil", "r");
    tabela_hash = preenche_tabela(tabela_hash, file);
    imprime_hash(tabela_hash);
    
    char cpf[20];
    printf("\nDigite um CPF para buscar pessoa: ");
    scanf("%s", cpf);
    busca_cpf(tabela_hash, cpf);

    return 0;
}
