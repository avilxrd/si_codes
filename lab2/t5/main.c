#include "hash.h"

void loop_principal(Node **hash, Node* lista)
{
    printf("%sobs: nao implementei a inserção e remoção na lista encadeada\napesar de ler o mesmo arquivo, a tabela hash e a lista sao diferentes\nna memoria do programa, ou seja, ao inserir na tabela hash, não é inserido na lista\n%s", AMARELO, BRANCO);
    while (1)
    {
        printf("\n%s========================================================================================================================%s\n", AMARELO, BRANCO);
        printf("\n[%s###############%s] (0) Sair\n", VERMELHO, BRANCO);
        printf("\n[%s  TABELA HASH  %s] (1) Mostrar Lista [t. hash ] (2) Busca Registro (3) Adicionar registro (4) Remover registro\n", VERDE, BRANCO);
        printf("\n[%sLISTA ENCADEADA%s] (5) Mostrar Lista [l. encad] (6) Busca Registro\n\n%s-->%s ", AMARELO, BRANCO, VERMELHO, BRANCO);
        int opcao, x=0;
        
        do {
            if (x != 0) printf("\nOpcao invalida, digite novamente.\n--> ");
            scanf("%d", &opcao);
        } while (opcao<0 && opcao>6);
        flush_in();
        char *cpf;
        switch (opcao)
        {
            case 0: 
                exit(1);
                break;
            case 1: 
                system("clear || cls");
                imprime_hash(hash);
                break;
            case 2:
                system("clear || cls");
                cpf = (char*) malloc(sizeof(char));
                printf("\nBuscar por CPF: ");
                scanf("%s", cpf);
                busca_cpf(hash, cpf);
                break;
            case 3: 
                system("clear || cls");
                adicionar_registro(hash);
                break;
            case 4: 
                system("clear || cls");
                remover_registro(hash);
                break;
            case 5:
                system("clear || cls");
                imprime_lista(lista);
                break;
            case 6: 
                system("clear || cls");
                cpf = (char*) malloc(sizeof(char));
                printf("\nBuscar por CPF: ");
                scanf("%s", cpf);
                busca_lista(lista, cpf);
                break;
        }

    }

}

int escolhe_arquivo()
{
    int opt=0, cont=0;
    do {
        system("clear || cls");
        if (cont != 0) printf("%sOpção inválida, escolha uma VÁLIDA\n\n%s", VERMELHO, BRANCO);
        printf("%sSelecione o arquivo desejado%s\n\n", AMARELO, BRANCO);
        printf("(1) 10      (2) 100      (3) 1000      (4) 10000");
        printf("\n\n%s--> %s", VERMELHO, BRANCO);
        scanf("%d", &opt);
        cont++;
    } while (opt<1 || opt>4);

    return opt;
}

int main()
{
    Node **tabela_hash = (Node**) malloc(9*sizeof(Node)); //tabela com os nós de uma lista
    Node *lista = (Node*) malloc (sizeof(Node));
    for (int i=0; i<10; i++) tabela_hash[i] = NULL;
    char arq[10];
    int opt = escolhe_arquivo();
    if (opt == 1) strcpy(arq, "10");
    if (opt == 2) strcpy(arq, "100");
    if (opt == 3) strcpy(arq, "1000");
    if (opt == 4) strcpy(arq, "10000");

    FILE *file1 = fopen(arq, "r");
    tabela_hash = preenche_tabela(tabela_hash, file1);
    fclose(file1);

    FILE *file2 = fopen(arq, "r");
    lista = arquivo_lista(lista, file2);
    fclose(file2);


    system("cls || clear");
    loop_principal(tabela_hash, lista);

    return 0;
}
