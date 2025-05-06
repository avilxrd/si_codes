#include "hash.h"

Node* insere_lista(Node* lista, Aluno* aluno)
{
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->aluno = aluno;
    novo->prox = lista;
    lista = novo;
    return lista;
}

Node** preenche_tabela(Node** tabela_hash, FILE* file)
{
    file = fopen("cem", "r");
    char linha[255];
    Aluno* aluno;

    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        //extrai os numeros de uma string
        char numeros[20] = "";
        int j=0, k=0;
        for (int i=0; i<strlen(linha); i++)
        {
            if (isdigit(linha[i]))
            {
                numeros[j] = linha[i];
                j++;
            }
            if (!isdigit(linha[i]))
            {
                aluno->nome[k] = linha[i];
                k++; 
            }
        }
        numeros[j] = '\0';
        aluno->matricula = numeros;

        int primeiro_num = numeros[0] - '0';

        tabela_hash[primeiro_num] = insere_lista(tabela_hash[primeiro_num], aluno);
    }

    return tabela_hash;
}

void imprime_hash(Node** tabela)
{

    for (int i=0; i<9; i++)
    {
        Node* temp = tabela[i];
        printf("linha %d: ", i);
        while (temp != NULL)
        {
            printf("[%s, %s] ", temp->aluno->nome, temp->aluno->matricula);
            temp = temp->prox;
        }
    }
}
