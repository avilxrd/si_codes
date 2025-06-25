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
        int cont = 0;
        while (temp != NULL) 
        {
            printf("[%sTABELA HASH%s][%d][%d]\t%sNOME%s: %s\t%sCPF%s: %s\n", AMARELO, BRANCO, i, cont, VERMELHO, BRANCO, temp->pessoa->nome, VERMELHO, BRANCO, temp->pessoa->cpf);
            cont++;
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
        printf("\n%sPessoa nao encontrada.%s\n", VERMELHO, BRANCO);
        return NULL;
    }

    while (atual != NULL) 
    {
        if (strcmp(atual->pessoa->cpf, cpf) == 0)
        {
            if (atual->pessoa!=NULL) printf("\n%sPessoa Encontrada%s\nNome%s: %s\t%sCpf%s: %s\n", VERDE, VERMELHO, BRANCO, atual->pessoa->nome, VERMELHO, BRANCO, atual->pessoa->cpf);
            fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\nTempo de busca: %s%.6f%s segundos\n", AMARELO, tempo, BRANCO);
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

void imprime_lista(Node* lista)
{
    int cont = 0;
    Node *temp = lista;
    while (temp != NULL && temp->prox != NULL)
    {
        printf("[%sLISTA ENCADEADA%s][%d] %sNOME%s: %s\t\t%sCPF%s: %s\n", AMARELO, BRANCO, cont, VERMELHO, BRANCO, temp->pessoa->nome, VERMELHO, BRANCO, temp->pessoa->cpf);
        cont++;
        temp = temp->prox;
    }
}

Node* arquivo_lista(Node *lista, FILE *file)
{
    char linha[255];

    while (fgets(linha, sizeof(linha), file) != NULL) 
    {
        linha[strcspn(linha, "\n")] = '\0';

        char* ult_espaco = strrchr(linha, ' ');
        if (ult_espaco == NULL || !isdigit(ult_espaco[1])) continue;

        Pessoa *pessoa = (Pessoa*)malloc(sizeof(Pessoa));

        size_t len_nome = ult_espaco - linha;
        strncpy(pessoa->nome, linha, len_nome);
        pessoa->nome[len_nome] = '\0';

        strcpy(pessoa->cpf, ult_espaco + 1);

        lista = insere_lista(lista, pessoa);
    }
    return lista;
}

Pessoa* busca_lista(Node *lista, char *cpf)
{
    Node *temp = lista;
    clock_t inicio = clock(), fim;
    while (temp != NULL && temp->prox != NULL)
    {
        if (!strcmp(cpf, temp->pessoa->cpf))
        {
            fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\n%sPessoa encontrada%s\n%sNome%s: %s          %sCPF%s: %s\nTempo de busca: %s%.6f%s segundos!", VERDE, BRANCO, VERMELHO, BRANCO, temp->pessoa->nome, VERMELHO, BRANCO, temp->pessoa->cpf, AMARELO, tempo, BRANCO);
            return temp->pessoa;
        }
        temp = temp->prox;
    }

    printf("\nPessoa nao encontrada!");
    return NULL;
}
