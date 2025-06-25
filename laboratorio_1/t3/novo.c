// l1-t3 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// constantes usadas no codigo
#define RAINHA 'Q'
#define ESPACO_BRANCO ' '
#define LARGURA_BORDA 15
#define MARGEM 50
#define TAMANHO_TXT 24

// CORES
cor_t branco   = {1, 1, 1, 1};
cor_t preto    = {0, 0, 0, 1};
cor_t vermelho = {1, 0, 0, 1};
cor_t amarelo  = {1, 1, 0, 1};
cor_t verde    = {0, 1, 0, 1,};
cor_t cinza    = {0.168, 0.176, 0.258, 1};
cor_t roxo     = {0.5, 0.07, 0.388, 1};

// limpa o buffer
void limpar_buffer(){
    while (getchar() != '\n');
}

// peguei esse codigo aqui -> https://www.geeksforgeeks.org/square-root-of-an-integer/
int floorSqrt(int x){
    if (x == 0 || x == 1)
        return x;
    int i = 1, result = 1;
    while (result <= x) {
        i++;
        result = i * i;
    }
    return i - 1;
}

typedef struct{
    long tempo_inicial;
}jogo_t;

void inicia_jogo(){

}

// ********** ANALISE DE TABULEIRO **********

// verifica se há conflito nas linhas
bool verifica_linha(int lado, char str[]){
    int lin, col, cont;

    for (lin=1; lin<=lado; lin++){
        cont = 0;
        for (col=1; col<=lado; col++){
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++; 
        }
        if (cont > 1) return false;
    }
    return true;
}

// verifica se há conflito nas colunas
bool verifica_coluna(int lado, char str[]){
    int lin, col, cont;

    for (col=1; col<=lado; col++){
        cont = 0;
        for (lin=1; lin<=lado; lin++){
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++; 
        }
        if (cont > 1) return false;
    }
    return true;
}

// verifica se há conflito nas diagonais
bool verifica_diagonal(int lado, char str[]) {
    int lin, col, cont;

    // esquerda -> direita
    int col_inicial;
    for (col_inicial=1; col_inicial<=lado; col_inicial++){ 
        cont = 0;
        lin = 1;
        col = col_inicial;
        while (lin <= lado && col <= lado) { 
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col++;
        }
        if (cont>1) return false; 
    }
    int lin_inicial;
    for (lin_inicial=2; lin_inicial<=lado; lin_inicial++){ 
        cont = 0;
        lin = lin_inicial;
        col = 1;
        while (lin<=lado && col<=lado){ 
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col++;
        }
        if (cont>1) return false; 
    }

    // direita -> esquerda
    for (col_inicial=1; col_inicial<=lado; col_inicial++){
        cont = 0;
        lin = 1;
        col = col_inicial;
        while (lin<=lado && col>=1){ 
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col--;
        }
        if (cont>1) return false; 
    }
    for (lin_inicial=2; lin_inicial<=lado; lin_inicial++){
        cont = 0;
        lin = lin_inicial;
        col = lado;
        while (lin<=lado && col>=1){ 
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col--;
        }
        if (cont > 1) return false; 
    }
    return true;
}

// retorna o estado do tabuleiro (0: incompleto, 1: completo, 2: conflito)
int jogo_rainhas(int lado, char str[]){
    int i, rainhas=0;
    for (i=0; i<lado*lado; i++){
        if (str[i]==RAINHA) rainhas++;
    }
    if (!verifica_linha(lado, str) || !verifica_coluna(lado, str) || !verifica_diagonal(lado, str)) return 2; // 2 -> incorreto
    else {
        if (rainhas<lado) return 0; // 0 -> incompleto
        else return 1; // 1 -> completo
    }
}

// ********** DESENHOS **********

// seta a cor da borda dependendo do status
cor_t cor_borda(int cor){
    if (cor == 0) return amarelo;    // incompleto -> amarelo
    else if (cor == 1) return verde; // correto    -> verde
    else return vermelho;            // incorreto  -> vermelho
}

// desenha um quadrado cinza para ser o fundo
void desenha_fundo(tamanho_t janela){
    retangulo_t fundo;
    fundo.inicio = (ponto_t){1,1};
    fundo.tamanho = janela;
    j_retangulo(fundo, 0, preto, cinza);
}

// desenha um quadrado escrito desistir
void desenha_desistir(){
    char txt[100];
    sprintf(txt, "Desistir");

    ponto_t posicao_desistir = (ponto_t){1, TAMANHO_TXT};
    retangulo_t desistir;
    desistir = j_texto_contorno(posicao_desistir, TAMANHO_TXT, txt);
    j_texto(posicao_desistir, TAMANHO_TXT, branco, txt);
}

// desenha o tempo decorrido até então
void desenha_tempo(long tempo_inicial, tamanho_t janela){
    char tempo[100];
    sprintf(tempo, "%d", time(NULL) - tempo_inicial);
    ponto_t pos = (ponto_t){janela.largura/2, TAMANHO_TXT};
    j_texto(pos, TAMANHO_TXT, branco, tempo);
}

// desenha toda a interface
void desenha_interface(tamanho_t janela, long tempo_inicial){
    desenha_fundo(janela);
    desenha_desistir();
    desenha_tempo(tempo_inicial, janela);
}

void desenha_borda(){
    retangulo_t tabuleiro;
    tabuleiro.inicio  = (ponto_t){4*MARGEM, 3*MARGEM};
    tabuleiro.tamanho = 
}

void desenha_posicoes(){
    
}

void desenha_tabuleiro(){
    desenha_borda();
    desenha_posicoes();
}