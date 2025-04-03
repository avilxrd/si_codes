#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "pilhas.h"

Carta pilhaEspadas[MAX_CARTAS]; 
Carta pilhaPaus[MAX_CARTAS]; 
Carta pilhaOuros[MAX_CARTAS];
Carta pilhaCopas[MAX_CARTAS];

// [4][13] finais       
void moveFinais(Carta pilha[], int cartaMover, Carta finais[4][13])
{
    int naipe = pilha[cartaMover].naipe;
    int topoFinal = cartaTopo(finais[naipe]);
    // if (topoFinal == -1) topoFinal++;

    printf("\ncartaMover: %d%s.\n", pilha[cartaMover].valor, lista_de_naipes[pilha[cartaMover].naipe]);
    printf("\ntopoFinal: %d%s.\n", finais[naipe][topoFinal].valor, lista_de_naipes[finais[naipe][topoFinal].naipe]);

    if (movimento_valido(pilha[cartaMover], finais[naipe][topoFinal], true)){
        finais[naipe][topoFinal+1] = pilha[cartaMover];
        pilha[cartaMover] = carta_vazia;
        for (int i=cartaMover; i<13; i++)
        {
            if (pilha[i].valor != 0) 
            {
                pilha[i].visivel = true;
                return;
            }
        }
        if (cartaMover-1 >= 0) 
        {
            pilha[cartaMover-1].visivel = true;
            return;
        }
    }
    else printf("\nNao pode mover para as pilha finais...\n");
}

void inicializaFinais(Carta pilhasFinais[4][13])
{
    for (int i=0; i<4; i++){
        for (int j=1; j<=13; j++){
            pilhasFinais[i][j-1].naipe = i;
            pilhasFinais[i][j-1].valor = 0;
            pilhasFinais[i][j-1].visivel = false;
        }
    }
}

void inicializaJogo(Carta baralho[CARTAS_BARALHO], Carta pilhas[NUM_PILHAS][MAX_CARTAS], int tamanho_pilha[NUM_PILHAS], Carta deposito[], Carta finais[4][13]){
    system("chcp 65001");
    for (int i=0; i<7; i++) inicializaPilhas(pilhas[i], 13);
    inicializaFinais(finais);
    inicializaPilhas(deposito, CARTAS_BARALHO);
    preencheBaralho(baralho);
    embaralharBaralho(baralho);
    distribuiCartas(baralho, pilhas, tamanho_pilha);
    // facilita(baralho, pilhas);
    // limpaTela();
}

void mostra_jogo(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int tamanho_pilha[NUM_PILHAS], Carta baralho[CARTAS_BARALHO], Carta deposito[], Carta finais[4][13]){
    limpaTela();
    for (int i=0; i<4; i++) printf("[%d%s] ", finais[i][quantidadePilha(finais[i], 13)-1].valor, lista_de_naipes[finais[i][0].naipe]);
    printf("\n\n");
    mostraPilhas(7, pilhas, false);
    printf("\n");
    // mostraDeposito(deposito, baralho);
}

int verificaInstrucao(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int instrucao, Carta baralho[], Carta deposito[], int tamanho_pilha[], Carta finais[4][13]) {
    int pilha_origem, pilha_destino;

    if (instrucao >= 1 && instrucao <= 7) {
        pilha_origem = instrucao - 1;
        int carta_mover = selecionarCarta(pilha_origem, pilhas);
        if (carta_mover == -1) return -1; // Pilha vazia

        if (pilhas[pilha_origem][carta_mover].naipe == 0 || pilhas[pilha_origem][carta_mover].naipe == 1){
            printf("\033[33m\nA carta selecionada foi: \033[0m%d de %s\n\n", 
                   pilhas[pilha_origem][carta_mover].valor, 
                   lista_de_naipes[pilhas[pilha_origem][carta_mover].naipe]);
        }
        else{
            printf("\033[33m\nA carta selecionada foi: \033[31m%d de %s\033[0m\n\n", 
                pilhas[pilha_origem][carta_mover].valor, 
                lista_de_naipes[pilhas[pilha_origem][carta_mover].naipe]);
        }

        int conectadas = 0;
        for (int i = carta_mover + 1; i < MAX_CARTAS; i++) {
            if (pilhas[pilha_origem][i].valor != 0) conectadas++;
        }
        // printf("%d conectadas.\n\n", conectadas);

        do {
            pilha_destino = selecionarDestino();
        } while (pilha_destino < 0 || pilha_destino > 7);

        printf("pilha destino: %d\n", pilha_destino);

        if (pilha_destino >= 0 && pilha_destino <= 6) {
            int topo_destino = cartaTopo(pilhas[pilha_destino]);
            printf("topo: %d\n", topo_destino);

            if (movimento_valido(pilhas[pilha_origem][carta_mover], pilhas[pilha_destino][topo_destino], false) && topo_destino+conectadas < 13) {
                for (int i = carta_mover; i <= carta_mover + conectadas; i++) {
                    printf("i: %d\n", i);
                    moveCartas(pilhas, pilha_origem, i, pilha_destino);
                }
                pilhas[pilha_origem][carta_mover - 1].visivel = true;
            }
        } else if (pilha_destino == 7){
            int topoOrigem = ultimaCarta(pilhas[pilha_origem]);
            printf("\ntopo: %d%s\tmover: %d%s", pilhas[pilha_origem][topoOrigem].valor, lista_de_naipes[pilhas[pilha_origem][topoOrigem].naipe],
                                                pilhas[pilha_origem][carta_mover].valor, lista_de_naipes[pilhas[pilha_origem][carta_mover].naipe]);
            if (pilhas[pilha_origem][topoOrigem].naipe == pilhas[pilha_origem][carta_mover].naipe && pilhas[pilha_origem][topoOrigem].valor == pilhas[pilha_origem][carta_mover].valor)
            {
                moveFinais(pilhas[pilha_origem], carta_mover, finais);
            }
            else printf("\nNao pode mover essa carta.\n");
        }
    }

    else if (instrucao == 8) {
        compraCarta(baralho, deposito);
    } 
    
    else if (instrucao == 9){

        int topo_deposito = cartaTopo(deposito);
        if (deposito[topo_deposito].valor != 0 && deposito[topo_deposito].visivel){
            do {
                pilha_destino = selecionarDestino();
            } while (pilha_destino < 0 || pilha_destino > 7);
            
            if (pilha_destino >= 0 && pilha_destino <= 6){
                moveDeposito(deposito, pilhas[pilha_destino]);
            }
            if (pilha_destino == 7){
                moveFinais(deposito, topo_deposito, finais);
            }          
            deposito[topo_deposito].visivel = true;
        }
    } 
    else if (instrucao == 10) {
        restitui_baralho(baralho, deposito);
    }
    
    return 0;
}

int verificaFim(Carta finais[4][13])
{
    for (int i=0; i<4; i++) if (quantidadePilha(finais[i], 13) != 13) return 1;
    return 0;
}

int main(){
    Carta baralho[CARTAS_BARALHO];
    Carta deposito[CARTAS_BARALHO];
    Carta pilhas[NUM_PILHAS][MAX_CARTAS];
    Carta pilhasFinais[NUM_FINAIS][MAX_CARTAS];
    int tamanho_pilha[7];

    inicializaJogo(baralho, pilhas, tamanho_pilha, deposito, pilhasFinais);
    
    int instrucao;
    do{
        mostra_jogo(pilhas, tamanho_pilha, baralho, deposito, pilhasFinais);
        instrucao = pedeInstrucoes(pilhas, baralho, deposito);
        verificaInstrucao(pilhas, instrucao, baralho, deposito, tamanho_pilha, pilhasFinais);
    }while(instrucao != 0 || verificaFim(pilhasFinais) != 0);

    return 0;
}
