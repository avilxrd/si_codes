#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COD_ESTRUTURA 850

void limpa_buffer(void)
{
    int c=0;
    while((c = getchar()) != '\n' && c != EOF);
    return;
}

void remove_quebra_linha(char* str)
{
    size_t len = strlen(str);
    if(len>0 && str[len-1] == '\n') str[len-1] = '\0';
}


struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct data Data;

struct dados{
    char nome[100];
    char endereco[255];
    char cidade[255];
    char telefone[15];
    char id[20]; //cpf ou cnpj
};

typedef struct dados Dados;

struct item{
    float quantidade;
    char descricao[255];
    float valor_unit;
    float valor_total;
};

typedef struct item Item;

struct node_itens{
    Item item;
    struct node_itens* prox;
};

typedef struct node_itens Node_Itens;

struct nota{
    int cod_tipo;    
    char numero_nf[15];
    Data data;
    Dados dados_emissor;
    Dados dados_receptor;
    Node_Itens* itens;
};

typedef struct nota Nota;

Item preencher_item()
{
    Item item;
    printf("\nADICIONE UM NOVO ITEM: ");
    printf("\nQUANTIDADE: ");
    scanf("%f", &item.quantidade);
    printf("\nDESCRIÇÃO: ");
    limpa_buffer();
    fgets(item.descricao, sizeof(item.descricao), stdin);
    remove_quebra_linha(item.descricao);
    // scanf("%s", item.descricao);
    printf("\nVALOR UNITÁRIO: ");
    scanf("%f", &item.valor_unit);
    item.valor_total = item.valor_unit * item.quantidade;
    return item;
}

Node_Itens* adicionar_final(Node_Itens* itens, Item item)
{
    if (itens == NULL)
    {
        Node_Itens* novo_node = (Node_Itens*)malloc(sizeof(Node_Itens));
        novo_node->prox = NULL;
        novo_node->item = item;
        return novo_node;
    }
    else
    {
        Node_Itens* temp = itens;
        while (temp->prox != NULL) temp = temp->prox;
        Node_Itens* novo_node = (Node_Itens*)malloc(sizeof(Node_Itens));
        novo_node->prox = NULL;
        novo_node->item = item;
        temp->prox = novo_node;
        return itens;
    }
}

Dados gerar_dados(int flag)
{
    Dados novos_dados;
    if (flag == 0)
    {
        strcpy(novos_dados.nome,     "Emissor");
        strcpy(novos_dados.endereco, "Rua do Emissor");
        strcpy(novos_dados.cidade,   "Cidade Emissor");
        strcpy(novos_dados.telefone, "55998765432");
        strcpy(novos_dados.id,       "123456789-10");        
    }
    else
    {
        strcpy(novos_dados.nome,     "Receptor");
        strcpy(novos_dados.endereco, "Rua do Receptor");
        strcpy(novos_dados.cidade,   "Cidade Receptor");
        strcpy(novos_dados.telefone, "66932890213");
        strcpy(novos_dados.id,       "323890472-23");   
    }
    return novos_dados;
}

//printa todas as informações de uma estrutura nota
void mostra_nota(Nota* nota)
{
    system("cls || clear");
    printf("\n\nEDI SALVA NO ARQUIVO output.txt\n\n");

    Node_Itens* temp = nota->itens;

    printf("\n========================================================\n");
    printf("                  NOTA DE COMPRA/VENDA                  \n");
    printf("========================================================\n");
    printf("Tipo de Nota: %4d                                    \n", nota->cod_tipo);
    printf("Número NF: %-15s      Data: %02d/%02d/%04d     \n",
        nota->numero_nf, nota->data.dia, nota->data.mes, nota->data.ano);
    printf("--------------------------------------------------------\n");
    printf("                   EMISSOR                           \n");
    printf("Nome:     %-42s\n", nota->dados_emissor.nome);
    printf("Endereço: %-42s\n", nota->dados_emissor.endereco);
    printf("Cidade:   %-42s\n", nota->dados_emissor.cidade);
    printf("Telefone: %-15s   CPF/CNPJ: %-15s\n", 
        nota->dados_emissor.telefone, nota->dados_emissor.id);
    printf("--------------------------------------------------------\n");
    printf("                  RECEPTOR                           \n");
    printf("Nome:     %-42s\n", nota->dados_receptor.nome);
    printf("Endereço: %-42s\n", nota->dados_receptor.endereco);
    printf("Cidade:   %-42s\n", nota->dados_receptor.cidade);
    printf("Telefone: %-15s   CPF/CNPJ: %-15s\n", 
        nota->dados_receptor.telefone, nota->dados_receptor.id);
    printf("--------------------------------------------------------\n");
    printf("QTD  | DESCRIÇÃO                      | V.UNIT | V.TOTAL\n");
    printf("--------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-4.1f | %-30s | %-6.2f | %-7.2f \n",
            temp->item.quantidade,
            temp->item.descricao,
            temp->item.valor_unit,
            temp->item.valor_total);
        temp = temp->prox;
    }
    printf("========================================================\n");
}


int escreve_arquivo(Nota* nota)
{
    FILE* file;
    file = fopen("output.txt", "w"); //abrindo o arquivo em modo de escrita
    
    //#1
    fprintf(file, "ST*%d*%d\n", COD_ESTRUTURA, nota->cod_tipo); 
    //#2
    fprintf(file, "BG*%s*%d%d%d\n", nota->numero_nf, nota->data.dia, nota->data.mes, nota->data.ano); 
    //#3
    fprintf(file, "N1*%s*%s*%s*%s*%s\n", nota->dados_emissor.nome, nota->dados_emissor.endereco, nota->dados_emissor.cidade, nota->dados_emissor.telefone, nota->dados_emissor.id);
    //#4
    fprintf(file, "N2*%s*%s*%s*%s*%s\n", nota->dados_receptor.nome, nota->dados_receptor.endereco, nota->dados_receptor.cidade, nota->dados_receptor.telefone, nota->dados_receptor.id);
    //#5
    int i=1;
    float soma_itens=0, soma_precos=0;
    Node_Itens* temp = nota->itens;
    while (temp != NULL)
    {
        fprintf(file, "PO%d*%d*%s*%.2f*%.2f\n", i, (int)temp->item.quantidade, temp->item.descricao, temp->item.valor_unit,
        temp->item.valor_total);
        soma_itens  += temp->item.quantidade;
        soma_precos += temp->item.valor_total;
        temp = temp->prox;
        i++;
    }
    //#6
    fprintf(file, "CTT*%d*%.2f\n", (int)soma_itens, soma_precos);
    //#7
    fprintf(file, "SE*%s", nota->numero_nf);

    fclose(file);
}

//implementar um gerador de arquivos em formato EDI (notas de venda)
int main()
{
    Nota nota; //criei a variavel do tipo nota

    printf("GERADOR DE NOTAS DE VENDA\n");
    printf("\nSELECIONE QUAL O TIPO DE NOTA\n");

    int selecao=0;
    while (selecao < 1 || selecao > 2)
    {
        printf("1: NOTA DE VENDA\n2: NOTA DE COMPRA\n--> ");
        scanf("%d", &selecao);
	if (selecao < 1 || selecao > 2) printf("\nOPÇÃO INVÁLIDA, TENTE NOVAMENTE\n");
    }
    if (selecao == 1)      nota.cod_tipo = 5400;
    else if (selecao == 2) nota.cod_tipo = 5700;
 
    //#2 NUMERO DA NF / DATA
    printf("DIGITE O NUMERO DA NF: ");
    scanf("%s", nota.numero_nf); //pegando o numero em string    

    printf("\nDIGITE O DIA: ");
    scanf("%d", &nota.data.dia);
    printf("\nDIGITE O MÊS: ");
    scanf("%d", &nota.data.mes);
    printf("\nDIGITE O ANO: ");
    scanf("%d", &nota.data.ano);

    //#3 & #4
    nota.dados_emissor  = gerar_dados(0);
    nota.dados_receptor = gerar_dados(1);

    //#5 -->
    int option;
    nota.itens = NULL;
    do{
        Item item = preencher_item();
        nota.itens = adicionar_final(nota.itens, item);
        printf("\n\n0: TODOS OS ITENS JÁ FORAM ADICIONADOS\tQUALQUER CHAR: ADICIONAR OUTRO ITEM\n");
        scanf("%d", &option);
    }
    while(option != 0);

    //escreve as informacoes da nota no arquivo de saída
    escreve_arquivo(&nota);
    //mostra as informações armazenadas
    mostra_nota(&nota);
    return 0;
}
