#include "hash.h"

Node* insere_lista(Node* lista, Aluno* aluno)
{
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->aluno = aluno;
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

        Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));

        // Copia o nome
        size_t len_nome = ult_espaco - linha;
        strncpy(aluno->nome, linha, len_nome);
        aluno->nome[len_nome] = '\0';

        // Copia a matrícula
        strcpy(aluno->cpf, ult_espaco + 1);

        int chave = aluno->cpf[0] - '0';
        tabela_hash[chave] = insere_lista(tabela_hash[chave], aluno);
    }

    return tabela_hash;
}

void imprime_hash(Node** tabela) {
    for (int i = 0; i < 10; i++) {
        Node* temp = tabela[i];
        printf("\nLinha %d: \n\n", i);
        while (temp != NULL) {
            printf("[%s | %s]  ", temp->aluno->nome, temp->aluno->cpf);
            temp = temp->prox;
        }
        printf("\n");
    }
}

Aluno* busca_cpf(Node** tabela_hash, const char* cpf) 
{
    clock_t inicio = clock();

    if (cpf == NULL || strlen(cpf) == 0) return NULL;

    int chave = cpf[0] - '0';
    Node* atual = tabela_hash[chave];

    while (atual != NULL) 
    {
        if (strcmp(atual->aluno->cpf, cpf) == 0)
        {
            if (atual->aluno==NULL) printf("\nAluno nao encontrado.\n");
            if (atual->aluno!=NULL) printf("\nAluno Encontrado\nNome: %s\tCpf: %s\n", atual->aluno->nome, atual->aluno->cpf);
            clock_t fim = clock();
            double tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\nTempo de execucao: %.6f\n", tempo_exec);
            return atual->aluno;
        } 
        atual = atual->prox;
    }
    return NULL;
}

