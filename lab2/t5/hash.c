#include "hash.h"

void flush_in()
{
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

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
        printf("%sLinha %d: %s\n", AMARELO, i, BRANCO);
        while (temp != NULL) 
        {
            printf("\t%sNOME%s: %s\t%sCPF%s: %s\n", VERMELHO, BRANCO, temp->pessoa->nome, VERMELHO, BRANCO, temp->pessoa->cpf);
            temp = temp->prox;
        }
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
            fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\nTempo de execucao: %.6f segundos\n", tempo);
            return atual->pessoa;
        } 
        atual = atual->prox;
    }

    printf("\nPessoa nao encontrada.\n");
    return NULL;
}

Pessoa* ler_registro()
{
    Pessoa* pessoa = (Pessoa*) malloc (sizeof(Pessoa));
    char nome[155], cpf[15];

    printf("\nNome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    strcpy(pessoa->nome, nome);
    
    printf("\nCPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    strcpy(pessoa->cpf, cpf);

    return pessoa;
}

int adicionar_registro(Node** hash)
{
    printf("\n%sAdicionando novo registro:%s", AMARELO, BRANCO);
    Pessoa *pessoa = ler_registro();
    char* cpf = pessoa->cpf;
    int primeiro_digito = cpf[0] - '0';
    hash[primeiro_digito] = insere_lista(hash[primeiro_digito], pessoa);
    printf("\n%sRegistro Adicionado%s\n", VERDE, BRANCO);
    return 0;
}

int remover_registro(Node** hash)
{
    printf("\n%sRemovendo registro:%s", AMARELO, BRANCO);
    char cpf[15];
    printf("\nCPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    int primeiro_digito = cpf[0] - '0';
    
    Node *lista = hash[primeiro_digito];
    Node *ant = NULL;
    
    if (strcmp(lista->pessoa->cpf, cpf) == 0)
    {
        printf("\n%sPessoa removida:%s\nNOME: %s\tCPF: %s\n", AMARELO, BRANCO, hash[primeiro_digito]->pessoa->nome, hash[primeiro_digito]->pessoa->cpf);
        hash[primeiro_digito] = hash[primeiro_digito]->prox;
        printf("\n%sPessoa removida com sucesso%s\n", VERDE, BRANCO);
        return 1; //removeu
    }

    while (lista != NULL)
    {
        if (strcmp(lista->pessoa->cpf, cpf) == 0)
        {
            printf("\n%sPessoa removida:%s\nNOME: %s\tCPF: %s\n", AMARELO, BRANCO, lista->pessoa->nome, lista->pessoa->cpf);
            Node *lixo = lista;
            ant->prox = lista->prox;
            free(lixo);
            printf("\n%sPessoa removida com sucesso%s\n", VERDE, BRANCO);
            return 1; //removeu
        }
        ant   = lista;
        lista = lista->prox;
    }
    
    return 0; //nao removeu
}