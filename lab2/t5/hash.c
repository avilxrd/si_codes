#include "hash.h"

Node* insere_lista(Node* lista, Pessoa* pessoa)
{
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->pessoa = pessoa;
    novo->prox = lista;
    lista = novo;
    return lista;
}

Node** preenche_tabela(Node** tabela_hash, FILE* file) {
    char linha[255];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';  // remove '\n'

        char* ult_espaco = strrchr(linha, ' ');
        if (ult_espaco == NULL || !isdigit(ult_espaco[1])) continue;

        Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));

        size_t len_nome = ult_espaco - linha;
        strncpy(pessoa->nome, linha, len_nome);
        pessoa->nome[len_nome] = '\0';

        strcpy(pessoa->cpf, ult_espaco + 1);

        int chave = pessoa->cpf[0] - '0';
        tabela_hash[chave] = insere_lista(tabela_hash[chave], pessoa);
    }

    return tabela_hash;
}

void imprime_hash(Node** tabela) 
{
    for (int i=0; i<10; i++) 
    {
        Node* temp = tabela[i];
        printf("\nLinha %d: \n\n", i);
        while (temp != NULL) 
        {
            printf("\tNOME: %s\tCPF: %s\n", temp->pessoa->nome, temp->pessoa->cpf);
            temp = temp->prox;
        }
        printf("\n");
    }
}

Pessoa* busca_cpf(Node** tabela_hash, const char* cpf) 
{

    int chave = cpf[0] - '0';
    Node* atual = tabela_hash[chave];

    clock_t inicio = clock();
    clock_t fim;

    if (cpf == NULL || strlen(cpf) == 0)
    {
        printf("\nPessoa nao encontrada.\n");
        return NULL;
    }

    while (atual != NULL) 
    {
        if (strcmp(atual->pessoa->cpf, cpf) == 0)
        {
            if (atual->pessoa!=NULL) printf("\nPessoa Encontrada\nNome: %s\tCpf: %s\n", atual->pessoa->nome, atual->pessoa->cpf);
            // for (volatile int i = 0; i < 1000000000; i++); // Só para gastar tempo
            fim = clock() - inicio;
            printf("\nTempo de execucao: %.12f\n", fim/CLOCKS_PER_SEC);
            return atual->pessoa;
        } 
        atual = atual->prox;
    }

    printf("\nPessoa nao encontrada.\n");
    return NULL;
}

