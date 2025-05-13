#include "hash.h"

#define SPACE "          "

void loop_principal(Node **hash)
{
    while (1)
    {
        printf("\n(0) Sair%s(1) Mostrar Lista%s(2) Adicionar registro%s(3) Remover registro\n\n-> ", SPACE, SPACE, SPACE);
        int opcao, x=0;
        
        do {
            if (x != 0) printf("\nOpcao invalida, digite novamente.\n--> ");
            scanf("%d", &opcao);
        } while (opcao<0 && opcao>3);
        flush_in();
        
        switch (opcao)
        {
            case 0: 
                exit(1);
                break;
            case 1: 
                imprime_hash(hash);
                break;
            case 2: 
                adicionar_registro(hash);
                break;
            case 3: 
                remover_registro(hash);
                break;
            default:
        }
    }

}

int main()
{
    Node** tabela_hash = (Node**) malloc(9*sizeof(Node)); //tabela com os nós de uma lista
    for (int i = 0; i < 9; i++) 
    {
        tabela_hash[i] = NULL;
    }    

    FILE *file = fopen("cem", "r");
    tabela_hash = preenche_tabela(tabela_hash, file);

    system("cls || clear");
    loop_principal(tabela_hash);

    return 0;
}
