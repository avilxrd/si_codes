#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "pilhas.h"

char lista_de_naipes[4][100] = {"♠", "♣", "♥", "♦"};
Carta carta_vazia = {0, 0, false};

// ======================================= //
// ======= funcoes gerais do jogo ======== //

void limpaTela(){
    system("cls || clear");
}

void mudaCor(int cor){
    printf("\033[%dm", cor);
}

void trocarCartas(Carta *a, Carta *b){
    Carta temp = *a;
    *a = *b;
    *b = temp;
}

bool movimento_valido(Carta origem, Carta destino, bool finais){
    if (finais == true){
        if (origem.valor == destino.valor+1){
            printf("\ntrue\n");
            return true;
        }
        else {
            printf("\nfalse\n");
            return false;
        }
    }
    else{
        if (origem.valor == 13 && destino.valor == 0){
            printf("\ntrue\n");
            return true;
        }  
        if (origem.valor == destino.valor-1){
            if (origem.naipe == 0 || origem.naipe == 1) if (destino.naipe == 2 || destino.naipe == 3){
                printf("\ntrue\n");
                return true;
            } 
            if (origem.naipe == 2 || origem.naipe == 3) if (destino.naipe == 0 || destino.naipe == 1){
                printf("\ntrue\n");
                return true;
            } 
        }
    }
    
    printf("\nfalse\n");
    return false;
}

// ======================================= //
// === funcoes relacionadas a "pilhas" === //

void mostraCartas(Carta pilha[], int tamanho)
{
    for (int i=0; i<tamanho; i++) printf("%d%s   ", pilha[i].valor, lista_de_naipes[pilha[i].naipe]);
}

bool pilhaVazia(Carta *pilha, int tamanho)
{
    for (int i=0; i<tamanho; i++) if (pilha[i].valor != 0) return false;
    return true;
}

void distribuiCartas(Carta *baralho, Carta pilhas[7][13], int *tamanho_pilha){
    int somador = 0;

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 13; j++){
            if(j <= i){
                pilhas[i][j] = baralho[somador];
                removerBaralho(baralho, pilhas[i][j]);
                if(i == j){
                    pilhas[i][j].visivel = true;
                }
                somador++;
            }else {
                pilhas[i][j].valor = 0;
                pilhas[i][j].naipe = 0;
                pilhas[i][j].visivel = true;
            }
        }
        tamanho_pilha[i] = i + 1;
    }
}

int quantidadePilha(Carta *pilha, int tamanho){
    int contador=0;
    for(int i=0; i<tamanho; i++) if(pilha[i].valor != 0) contador++;
    return contador;
}

void inicializaPilhas(Carta pilha[], int tamanhoPilha)
{
        for (int i=0; i<tamanhoPilha; i++){
        pilha[i] = carta_vazia;
    } 
}

void mostraPilhas(int quantidade, Carta pilhas[quantidade][13], bool mostrarZeros)
{
    for(int i=0; i<quantidade; i++)
    {
        printf("Pilha %d: ", i+1);
        for(int j=0; j<MAX_CARTAS; j++)
        {            
            if(pilhas[i][j].valor != 0 || mostrarZeros==true)
            {
                if(pilhas[i][j].visivel || mostrarZeros==true)
                {
                    if (pilhas[i][j].naipe == 2 || pilhas[i][j].naipe == 3) printf("\033[1;31m%d%s \033[0m", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
                    else printf("%d%s ", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
                }
                else printf("[] ");
            }
        }
        printf("\n");
    }
}

//pilha vazia: -1
int cartaTopo(Carta pilha[])
{
    int contador=-1;
    while(pilha[contador+1].valor != 0) contador++;
    return contador;
}

void revelaCarta(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int pilha, int carta)
{
    pilhas[pilha][carta].visivel = true;
}

int quantasVisiveis(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int indexPilha){
    int quantas_visiveis=0;

    for (int i=0; i<MAX_CARTAS; i++){
        if (pilhas[indexPilha][i].visivel == true && pilhas[indexPilha][i].valor != 0) quantas_visiveis++; 
    }

    return quantas_visiveis;
}

int primeiraVisivel(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int indexPilha){
    for (int i=0; i<MAX_CARTAS; i++) if (pilhas[indexPilha][i].visivel == true) return i;
    return -1;
}

int ultimaVisivel(Carta pilha[], int tamanho){
    for (int i=tamanho-1; i>=0; i--) if (pilha[i].visivel == true) return i;
    return -1;
}


// ======================================= //
// === funcoes relacionadas ao baralho === //

void preencheBaralho(Carta *baralho){
    inicializaPilhas(baralho, CARTAS_BARALHO);
    int contador=0;
    for (int i=0; i<4; i++){
        for (int j=1; j<=13; j++){
            baralho[contador].naipe = i;
            baralho[contador].valor = j;
            contador++;
        }
    }
}

void embaralharBaralho(Carta *baralho){
    srand(time(NULL));
    for(int i=0; i<52; i++){
        int random = rand() % 52;
        trocarCartas(&baralho[i], &baralho[random]);
    }
}

void removerBaralho(Carta *baralho, Carta removida){
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor == removida.valor && baralho[i].naipe == removida.naipe){
            baralho[i].valor = 0;
            baralho[i].naipe = 0;
            baralho[i].visivel = false;
            break;
        }
    }
}

void restitui_baralho(Carta baralho[], Carta deposito[]){
    int i=0;
    while(deposito[i].valor != 0){
        baralho[i] = deposito[i];
        deposito[i].valor = 0;
        i++;
    }
}

// ======================================= //
// === funcoes de manipulacao de cartas == //

int moveCartas(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int pilhaOrigem, int cartaMover, int pilhaDestino)
{
    int topoDestino = cartaTopo(pilhas[pilhaDestino]);
    if (movimento_valido(pilhas[pilhaOrigem][cartaMover], pilhas[pilhaDestino][topoDestino], false))
    {
        printf("movendo %d%s para pilha %d.\n", pilhas[pilhaOrigem][cartaMover].valor, lista_de_naipes[pilhas[pilhaOrigem][cartaMover].naipe], pilhaDestino);
        pilhas[pilhaDestino][topoDestino+1] = pilhas[pilhaOrigem][cartaMover];
        pilhas[pilhaOrigem][cartaMover].valor = 0; 
        pilhas[pilhaOrigem][cartaMover].naipe = 0; 
        pilhas[pilhaOrigem][cartaMover].visivel = false;
        printf("ok.\n");
        return 0;
    }
    printf("movimento invalido.\n");
    return -1;
}

void compraCarta(Carta baralho[], Carta deposito[])
{   
    for (int i=0; i<CARTAS_BARALHO; i++){
        if (baralho[i].valor != 0){
            int topoDeposito = cartaTopo(deposito);
            //adiciona no deposito
            deposito[topoDeposito+1] = baralho[i];
            deposito[topoDeposito+1].visivel = true;
            //remove do baralho
            baralho[i].valor = 0;
            baralho[i].visivel = false;
            //deixa a anterior invisivel
            if (topoDeposito>0) deposito[topoDeposito].visivel = false;
            break;
        }
    }
}

int moveDeposito(Carta deposito[], Carta pilhaDestino[])
{
    int topoDeposito = cartaTopo(deposito);
    int topoDestino = cartaTopo(pilhaDestino);

    if (movimento_valido(deposito[topoDeposito], pilhaDestino[topoDestino], false)){
        printf("movendo %d%s do deposito para destino [%d%s]...\n\n", deposito[cartaTopo(deposito)].valor, lista_de_naipes[deposito[cartaTopo(deposito)].naipe],
        pilhaDestino->valor, lista_de_naipes[pilhaDestino->naipe]);

        pilhaDestino[topoDestino+1] = deposito[topoDeposito];
        deposito[topoDeposito] = carta_vazia;
        bool conseguiu=false;
        for (int i=topoDeposito; i<52; i++){
            if (deposito[i].valor!=0){
                deposito[i].visivel = true;
                conseguiu = true;
            }
        }
        if (conseguiu == false) deposito[topoDeposito-1].visivel = true;
    }
    else {
        printf("movendo %d%s do deposito para destino [%d%s]...\n\n", deposito[cartaTopo(deposito)].valor, lista_de_naipes[deposito[cartaTopo(deposito)].naipe],
                                                                                                     pilhaDestino->valor, lista_de_naipes[pilhaDestino->naipe]);
        printf("Jogada invalida.\n");
        return 1;
    }
    return 0;
}

void mostraDeposito(Carta deposito[], Carta baralho[])
{
    printf("\nDeposito: ");

    int topoDeposito = cartaTopo(deposito);
    
    if (topoDeposito >= 0 && deposito[topoDeposito].visivel==true){
        if (deposito[topoDeposito].naipe == 2 || deposito[topoDeposito].naipe == 3) printf("[\033[1;31m%d%s\033[0m]\n", deposito[topoDeposito].valor, lista_de_naipes[deposito[topoDeposito].naipe]);
        else printf("[%d%s]\n", deposito[topoDeposito].valor, lista_de_naipes[deposito[topoDeposito].naipe]);
    } 
    else printf("[ ]\n");
    int contagem = quantidadePilha(baralho, CARTAS_BARALHO);
    printf("\n%d cartas restantes no baralho...\n", contagem);
    if (contagem == 0) printf("\nRestitua o baralho...\n");
}

// ======================================= //
// ===== funcoes de selecao de cartas ==== //

int selecionarCarta(int pilhaOrigem, Carta pilhas[NUM_PILHAS][MAX_CARTAS]){
    int quant_visiveis = quantasVisiveis(pilhas, pilhaOrigem);
    int primeira_visivel = primeiraVisivel(pilhas, pilhaOrigem);
    int indexCartaMover;

    if (quant_visiveis == 0){
        printf("Pilha Vazia");
        return -1;
    } else if (quant_visiveis == 1){
        printf("Retornando a unica carta.\n");
        return primeira_visivel;
    } 
    
    printf("Qual carta você quer mover? \n\n");

    for (int i=primeira_visivel; i<primeira_visivel+quant_visiveis; i++){
        printf("(%d) %d de %s ", i, pilhas[pilhaOrigem][i].valor, lista_de_naipes[pilhas[pilhaOrigem][i].naipe]);
    }

    do{
        scanf("%d", &indexCartaMover);
    } while (indexCartaMover < primeira_visivel || indexCartaMover > primeira_visivel + (quant_visiveis-1));

    printf("Retornando: %d", indexCartaMover);
    return indexCartaMover;
}

int selecionarDestino(){
    int pilhaDestino;
    printf("(1-7) Escolha a pilha de destino | (8) Adicionar na pilha final: ");
    scanf("%d", &pilhaDestino);
    return pilhaDestino-1;
}

int pedeInstrucoes(Carta pilhas[NUM_PILHAS][MAX_CARTAS], Carta *baralho, Carta *descarte){
    int instrucao;
    do{
        printf("\n(1-7) - Selecionar pilha | ");
        
        /*verifica se o baralho nao estiver vazio*/
        bool baralho_vazio=true;
        for (int i=0; i<CARTAS_BARALHO; i++){
            if (baralho[i].valor != 0){
                baralho_vazio = false;
                break;
            }
        }
        if (baralho_vazio == false) printf("(8) - Comprar do deposito | ");
        
        /*se houver uma carta disponivel para compra*/
        bool deposito_vazio=true;
        for (int i=0; i<CARTAS_BARALHO; i++){
            if (descarte[i].valor != 0 && descarte[i].visivel == true){
                deposito_vazio = false;
                break;
            }
        }
        if(deposito_vazio == false) printf("(9) - Mover carta do descarte | ");
        if(quantidadePilha(baralho, CARTAS_BARALHO) == 0) printf("(10) - Restituir baralho | ");
        
        printf("(0) - Sair ");
        scanf("%d", &instrucao);
        printf("\n");

        if(instrucao >= 1 && instrucao <= 7) printf("Pilha %d selecionada\n\n", instrucao);
        else if(instrucao ==  8) printf("Carta comprada\n\n");
        else if(instrucao ==  9) printf("Pilha de descarte selecionada\n\n");
        else if(instrucao == 10) printf("Restituindo o baralho\n\n");
        else if(instrucao !=  0) printf("Digite uma instrução valida\n\n");
    }
    while(!(instrucao >= 0 && instrucao <= 10));
    return instrucao;
}
