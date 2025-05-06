#include "hash.h"

int main()
{
    Node** tabela_hash = (Node**) malloc(9*sizeof(Node)); //tabela com os nós de uma lista
    FILE *file;

    tabela_hash = preenche_tabela(tabela_hash, file);
    imprime_hash(tabela_hash);

}
