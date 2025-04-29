#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define VALOR_MAX 9   //numero maximo que pode ser atribuido na funcao  
                      //preenche matriz ao usar valores_aleatorios.
#define COR_VERDE    "\033[32m"
#define COR_AMARELO  "\033[33m"
#define COR_VERMELHO "\033[31m"
#define COR_BRANCO   "\033[37m"

//  estruturas dadas pela professora
struct node{
    int linha;          //lin do elemento
    int coluna;         //col do elemento
    int info;           //valor armazenado
    struct node* prox;  //ponteiro para o proximo node nao nulo
};
typedef struct node Node;

struct matriz{
    int linhas;     //numero de linhas
    int colunas;    //numero de colunas
    Node* primeiro; //ponteiro para o primeiro node da lista
};
typedef struct matriz Matriz;

//  1. criacao da matriz
Matriz* cria_matriz(int linhas, int colunas)
{
    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    matriz->linhas   = linhas;
    matriz->colunas  = colunas;
    matriz->primeiro = NULL;
    return matriz;
}

//  TODO: quero implementar uma funcao que insira ja o valor
//  em "ordem". Ex: tendo uma lista com apenas v1 {1,1}, ao adicionar
//  um v2 {2, 1}, automaticamente inserir DEPOIS de v1, pois se fosse
//  um vetor, o indice seria mais alto.
//  insere os valores no INCIO de uma lista
Node* insere_lista(Node* lista, int linha, int coluna, int valor_inserido)
{
    Node* novo_node = (Node*)malloc(sizeof(Node));
    novo_node->linha  = linha;
    novo_node->coluna = coluna;
    novo_node->info   = valor_inserido;

    if (lista == NULL || (linha < lista->linha || (linha == lista->linha && coluna < lista->coluna)))
    {
        novo_node->prox = lista;
        return novo_node;
    }

    //TODO: preciso percorrer a lista ate o lin/col
    Node* temp = lista;
    while (temp->prox != NULL && (temp->prox->linha < linha || (temp->prox->linha == linha && temp->prox->coluna < coluna))) temp = temp->prox;  

    novo_node->prox = temp->prox;
    temp->prox      = novo_node;
    return lista;
}

//  2. preenchimento da matriz
//  obs: flags utilizadas para facilitar o teste
//  indices_aleatorios: escolhe os indices onde inserir aleatoriamente
//  valores_aleatorios: escolhe os valores para inserir aleatoriamente

Node* busca_node(Node* lista, int linha, int coluna)
{
    Node* temp = lista;
    while (temp != NULL)
    {
        if (temp->linha == linha && temp->coluna == coluna) return temp;
        temp = temp->prox;
    }
    return NULL;
}

int preenche_matriz(Matriz* matriz, bool indices_aleatorios, bool valores_aleatorios)
{
    int lin, col, val;
    
    // flag: indices_aleatorios
    if (indices_aleatorios == true)
    {
        lin = rand() % matriz->linhas;
        col = rand() % matriz->colunas;
    }
    else
    {
        printf("\n(0-%d) [*][ ]: ", matriz->linhas-1);
        scanf("%d", &lin);
        printf("\nCOLUNA A INSERIR (0-%d): ", matriz->colunas-1);
        scanf("%d", &col);
    }
    
    // flag: valores_aleatorios
    if (valores_aleatorios == true)
    {
        val = (rand() % VALOR_MAX) + 1; // com parênteses para evitar erro de prioridade
    }
    else
    {
        printf("VALOR A INSERIR: ");
        scanf("%d", &val);
    }

    // verifica se já existe o elemento
    Node* existente = busca_node(matriz->primeiro, lin, col);
    if (existente != NULL)
    {
        // se já existir, substitui o valor
        existente->info = val;
        printf("Matriz %sAtualizada%s: [%d][%d] %s-->%s %d\n%s", COR_AMARELO, COR_BRANCO, lin, col, COR_VERMELHO, COR_BRANCO, val, COR_BRANCO);
    }
    else
    {
        // se não existir, insere novo node na lista
        matriz->primeiro = insere_lista(matriz->primeiro, lin, col, val);
        printf("Matriz %sPreenchida%s: [%d][%d] %s-->%s %d\n%s", COR_VERDE, COR_BRANCO, lin, col, COR_VERMELHO, COR_BRANCO, val, COR_BRANCO);
    }

    return 0;
}

//  OBS: se a funcao de inserir esta inserindo na ordem
 
//  3. impressao da matriz
bool existe_lincol(Matriz* matriz, int lin, int col)
{
    Node* temp = matriz->primeiro;
    while (temp != NULL)
    {
        //posso adicionar verificacao para ver se ja passou do ponto
        //e encerra a funcao antes de percorrer toda a lista
        if (temp->linha > lin || (temp->linha == lin && temp->coluna > col)) return false; 
        if (temp->linha == lin && temp->coluna == col) return true;
    }
    return false;
}

void imprime_matriz(Matriz* matriz)
{
    Node* temp = matriz->primeiro;


    printf("\n%s\t", COR_BRANCO);
    for (int x=0; x<matriz->colunas; x++) printf("%s%d ", COR_AMARELO, x);
    printf("\n\n");
    for (int i=0; i<matriz->linhas; i++)
    {
        printf("%s%d%s\t", COR_AMARELO, i, COR_BRANCO);
        for (int j=0; j<matriz->colunas; j++)
        {
            if (temp != NULL && temp->linha == i && temp->coluna == j)
            {
                printf("%s%d ", COR_VERMELHO, temp->info);
                temp=temp->prox;
            }
            else printf("%s0 ", COR_BRANCO);
        }
        printf("\n");
    }
}


int main()
{
    system("clear || cls");
    srand(time(NULL));
    Matriz* matriz; 

    int opcao;
    bool indices, valores;
    
    printf("\nPARA FACILITAR O TESTE EU ADICIONEI UMA OPCAO DE INSERIR INDICES E VALORES ALEATORIOS\n\n");
    printf("%s0%s DEMONSTRACAO RAPIDA\n",                                                                       COR_AMARELO, COR_BRANCO);
    printf("%s1%s VALORES ALEATORIOS & INDICES ALEATORIOS (PREENCHE A MATRIZ ALEATORIAMENTE)\n",                COR_AMARELO, COR_BRANCO);
    printf("%s2%s VALORES ALEATORIOS                      (ESCOLHER OS INDICES, MAS VALORES SAO ALEATORIOS)\n", COR_AMARELO, COR_BRANCO);
    printf("%s3%s INDICES ALEATORIOS                      (ESCOLHER APENAS OS VALORES A SEREM INSERIDOS)\n\n",  COR_AMARELO, COR_BRANCO);
    printf("%s---> %s", COR_VERMELHO, COR_BRANCO);
    scanf("%d", &opcao);
    
    if (opcao == 0)
    {
        printf("\n%sCriando matriz 5x5%s\n\n", COR_AMARELO, COR_BRANCO);
        matriz = cria_matriz(7, 7);
        printf("%sInserindo 10 valores aleatorios em indices aleatorios%s\n\n", COR_AMARELO, COR_BRANCO);
        for (int i=0; i<10; i++) preenche_matriz(matriz, 1, 1);
        printf("\n%sImprimindo a Matriz\n\n", COR_AMARELO);
        imprime_matriz(matriz);
        printf("\n%sEncerrando%s\n", COR_VERMELHO, COR_BRANCO);
        return 0;
    }
    else
    {
        int lin, col;
        printf("\n%sQuantidade de Linhas:  \n%s---> %s", COR_AMARELO, COR_VERMELHO, COR_BRANCO);
        scanf("%d", &lin);
        printf("\n%sQuantidade de Colunas: \n%s---> %s", COR_AMARELO, COR_VERMELHO, COR_BRANCO);
        scanf("%d", &col);
        system("clear||cls");
        printf("\n%sCriando matriz %d x %d\n%s", COR_AMARELO, lin, col, COR_BRANCO);
        matriz = cria_matriz(lin, col);
    
        printf("%sPreenchendo Matriz%s\n\n", COR_AMARELO, COR_BRANCO);
             if (opcao == 1) preenche_matriz(matriz, 1, 1);
        else if (opcao == 2) preenche_matriz(matriz, 0, 1);
        else if (opcao == 3) preenche_matriz(matriz, 1, 0);
        imprime_matriz(matriz);
    }


}