// l1-t3 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define RAINHA 'Q'
#define ESPACO_BRANCO ' '

// CORES
cor_t branco = {1, 1, 1, 1};
cor_t preto = {0, 0, 0, 1};
cor_t vermelho = {1, 0, 0, 1};

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

bool verifica_linha(int tamanho, char str[]){
    int lin, col, cont;
    int lado = floorSqrt(tamanho);

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

bool verifica_coluna(int tamanho, char str[]){
    int lin, col, cont;
    int lado = floorSqrt(tamanho);

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

bool verifica_diagonal(int tamanho, char str[]) {
    int lin, col, cont;
    int lado = floorSqrt(tamanho);

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

int jogo_rainhas(int tamanho, char str[]){
    int i, rainhas=0;
    int lado = floorSqrt(tamanho);

    for (i=0; i<tamanho; i++){
        if (str[i]==RAINHA) rainhas++;
    }

    if (!verifica_linha(tamanho, str) || !verifica_coluna(tamanho, str) || !verifica_diagonal(tamanho, str)) return 2; // 2 -> incorreto
    else {
        if (rainhas<lado) return 0; // 0 -> incompleto
        else return 1; // 1 -> completo
    }
}

// void cor_borda(int cor){
//     if (cor == 0) t_cor_fundo(255, 255, 0); // incompleto -> amarelo
//     else if (cor == 1) t_cor_fundo(0, 255, 0); // correto -> verde
//     else t_cor_fundo(255, 0, 0); // incorreto -> vermelho
// }

void borda(int lado, int cor){
    int i;
    // cor_borda(cor);
    for (i=0; i<lado+2; i++){
        printf(" %c ", ESPACO_BRANCO);
    }
}


void mensagem_final(int status, long tempo){
    switch(status){
        case 0:
            printf("\nPrograma encerrado com %ld segundos passados...\nÚltimo tabuleiro:\n\n", tempo);
            break;
        case 1:
            printf("\nParabéns!! Você venceu em %ld segundos...\nTabuleiro final:\n\n", tempo);
            break;
        default: printf("\nErro!\n\n");
    }
}

void desenha_tabuleiro(int lado, char str[], int lin, int col){

}

// especificações iniciais da janela
tamanho_t janela = {600, 800};

void main(){
    int i;
    int lado = 7;
    // scanf("%d", &lado);
    int tamanho = lado*lado;
    char str[tamanho];
    for (i=0; i<tamanho; i++){
        str[i] = ESPACO_BRANCO;
    }

    // inicializa o tamanho de uma posição do tabuleiro
    int altura, largura;
    int margin = 50;
    altura = (janela.altura - 3*margin) / lado;
    largura = (janela.largura - 4*margin) / lado;

    retangulo_t posicao;
    posicao.tamanho.altura = altura;
    posicao.tamanho.largura = largura;

    // inicializa o tamanho do tabuleiro
    retangulo_t tabuleiro;
    tabuleiro.tamanho.altura = lado * altura;
    tabuleiro.tamanho.largura = lado * largura;
    tabuleiro.inicio.x = janela.largura/2 - tabuleiro.tamanho.largura/2;    
    tabuleiro.inicio.y = janela.altura/2 - tabuleiro.tamanho.altura/2;    


    // fundo
    retangulo_t background;
    background.tamanho.altura = janela.altura;
    background.tamanho.largura = janela.largura;
    background.inicio.x = 1;
    background.inicio.y = 1;

    t_inicializa(janela, str);
    while(true){
        j_retangulo(background, 0, preto, vermelho);
        j_retangulo(tabuleiro, 3, preto, preto);
        
        // desenhando as posições no tabuleiro
        int i, j;
        posicao.inicio.x = tabuleiro.inicio.x;
        posicao.inicio.y = tabuleiro.inicio.y;

        for (i=0; i<lado; i++){
            for (j=0; j<lado; j++){
                if ((i+j)%2==0) j_retangulo(posicao, 1, preto, preto);
                else j_retangulo(posicao, 1, preto, branco);
                posicao.inicio.x += largura;
            }
            posicao.inicio.x = tabuleiro.inicio.x;
            posicao.inicio.y += altura;
        }
        j_atualiza();

        // if (jogo_rainhas(tamanho, str)==1){
        //     end = time(NULL);
        //     status = 1;
        //     break;
        // } 
        
        // if (processa_entrada(tamanho, str, &lin, &col)){
        //     end = time(NULL);
        //     status = 0;
        //     break;
        // } else {
        //     t_limpa();
        //     desenha_tabuleiro(tamanho, str, lin, col, start, 1);
        //     t_atualiza();
        // }
    }
    j_finaliza();
    // t_limpa();
    // mensagem_final(status, end-start);
    // desenha_tabuleiro(tamanho, str, 0, 0, 0, 0);
}