#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "cores.h"

#define VALOR_MAX 9   //numero maximo que pode ser atribuido na funcao  
                      //preenche matriz ao usar valores_aleatorios.

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
        int contl=0, contc=0;
        do{
            if (contl != 0) printf("%sValor fora de intervalo, escolha outro: \n%s", COR_VERMELHO, COR_BRANCO);
            printf("\nLinha para inserir (0-%d): ", matriz->linhas-1);
            scanf("%d", &lin);
            contl++;
        } while (lin < 0 || lin >= matriz->linhas);
        do{
            if (contc != 0) printf("%sValor fora de intervalo, escolha outro: \n%s", COR_VERMELHO, COR_BRANCO);
            printf("Coluna para inserir (0-%d): ", matriz->colunas-1);
            scanf("%d", &col);
            contc++;
        } while (col < 0 || col >= matriz->colunas);
    }
    
    // flag: valores_aleatorios
    if (valores_aleatorios == true)
    {
        val = (rand() % VALOR_MAX) + 1; // com parênteses para evitar erro de prioridade
    }
    else
    {
        printf("Valor inserido: ");
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

    printf("%s\nOBSERVACAO: CASO TENTE ADICIONAR UM VALOR EM UM INDICE QUE JA POSSUA UM VALOR\n", COR_VERMELHO);
    printf("O VALOR ANTERIOR SERA REMOVIDO DA LISTA, ADICIONANDO O NOVO VALOR POR CIMA.\n");
    printf("POR CONTA DISSO, AS VEZES AO PEDIR PARA ADICIONAR X VALORES NA LISTA\n");
    printf("ALEATORIAMENTE, PODE SER QUE ADICIONE MENOS, POIS UM SOBRESCREVERA O OUTRO\n%s", COR_BRANCO);

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
        printf("%s\n", COR_BRANCO);
    }
}

// somatorio de uma linha
int somatorio_linha(Matriz* matriz, int linha)
{
    Node* temp = matriz->primeiro;
    int soma=0;
    while (temp != NULL)
    {
        if (temp->linha == linha) soma += temp->info;
        temp = temp->prox;
    } 
    return soma;
}

int percentual_nao_nulo(Matriz* matriz)
{
    float total = matriz->colunas * matriz->colunas;
    float quant = 0;
    Node* temp = matriz->primeiro;
    while (temp != NULL)
    {
        quant++;
        temp = temp->prox;
    }
    printf("\n%.0f valores nao nulos de %.0f valores possiveis.\n", quant, total);
    float resultado = (100*quant)/total;
    printf("\n%.1f%% de nao nulos.\n", resultado);
    return resultado;
}

int main()
{
    system("clear || cls");
    srand(time(NULL));
    Matriz* matriz; 

    int opcao;
    bool indices, valores;
    
    do
    {
        printf("\nPARA FACILITAR O TESTE EU ADICIONEI UMA OPCAO DE INSERIR INDICES E VALORES ALEATORIOS\n\n");
        printf("%s0%s DEMONSTRACAO RAPIDA\n",                                                                       COR_AMARELO, COR_BRANCO);
        printf("%s1%s VALORES ALEATORIOS & INDICES ALEATORIOS (PREENCHE A MATRIZ ALEATORIAMENTE)\n",                COR_AMARELO, COR_BRANCO);
        printf("%s2%s VALORES ALEATORIOS                      (ESCOLHER OS INDICES, MAS VALORES SAO ALEATORIOS)\n", COR_AMARELO, COR_BRANCO);
        printf("%s3%s INDICES ALEATORIOS                      (ESCOLHER APENAS OS VALORES A SEREM INSERIDOS)\n",  COR_AMARELO, COR_BRANCO);
        printf("%s4%s MATRIZ MANUAL                           (PREENCHE MANUALMENTE A MATRIZ)\n\n",  COR_AMARELO, COR_BRANCO);
        printf("%s---> %s", COR_VERMELHO, COR_BRANCO);
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 4);
    
    if (opcao == 0)
    {
        printf("\n%sCriando matriz 5x5%s\n\n", COR_AMARELO, COR_BRANCO);
        matriz = cria_matriz(5, 5);
        printf("%sInserindo 10 valores aleatorios em indices aleatorios%s\n\n", COR_AMARELO, COR_BRANCO);
        for (int i=0; i<10; i++) preenche_matriz(matriz, 1, 1);
        printf("\n%sImprimindo a Matriz\n\n", COR_AMARELO);
        imprime_matriz(matriz);
        printf("\n%sEncerrando%s\n", COR_VERMELHO, COR_BRANCO);
        return 0;
    }
    else
    {
        int lin, col, quant;
        printf("\n%sQuantidade de Linhas:  \n%s---> %s", COR_AMARELO, COR_VERMELHO, COR_BRANCO);
        scanf("%d", &lin);
        printf("%sQuantidade de Colunas: \n%s---> %s",   COR_AMARELO, COR_VERMELHO, COR_BRANCO);
        scanf("%d", &col);
        printf("%sQuantidade de valores a ser inserido: \n%s---> %s",   COR_AMARELO, COR_VERMELHO, COR_BRANCO);
        scanf("%d", &quant);

        system("clear||cls");
        printf("\n%sCriando matriz %d x %d\n%s", COR_AMARELO, lin, col, COR_BRANCO);
        matriz = cria_matriz(lin, col);
    
        printf("%sPreenchendo Matriz%s\n\n", COR_AMARELO, COR_BRANCO);
             if (opcao == 1) for(int i=0; i<quant; i++) preenche_matriz(matriz, 1, 1);
        else if (opcao == 2) for(int i=0; i<quant; i++) preenche_matriz(matriz, 0, 1);
        else if (opcao == 3) for(int i=0; i<quant; i++) preenche_matriz(matriz, 1, 0);
        else if (opcao == 4) for(int i=0; i<quant; i++) preenche_matriz(matriz, 0, 0);
        imprime_matriz(matriz);
        float nao_nulos = percentual_nao_nulo(matriz);
        int lin_soma;
        while (1)
        {
            printf("\nDigite uma linha para ver o somatorio: ");
            scanf("%d", &lin_soma);
            if (lin_soma < 0 || lin_soma >= matriz->linhas) printf("\nValor Fora do intervalo aceito\n");
            else printf("\nSomatorio da linha %d %s--> %d%s\n", lin_soma, COR_VERMELHO, somatorio_linha(matriz, lin_soma), COR_BRANCO);
        
            int acabou;
            do{
                printf("\n0. Ver somatorio de outra linha        1. Encerrar\n%s--> %s", COR_VERMELHO, COR_BRANCO);
                scanf("%d", &acabou);
            } while (acabou!=0 && acabou!=1);
        
            if (acabou == 1) break;
        }
    }
    return 0;
}