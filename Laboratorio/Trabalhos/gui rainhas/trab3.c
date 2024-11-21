// l1-t3 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// especificações iniciais da janela
#define ALTURA 600
#define LARGURA 800
// constantes usadas no codigo
#define RAINHA 'Q'
#define ESPACO_BRANCO ' '
#define LARGURA_BORDA 15
#define MARGEM 50

// typedef struct {
//     tamanho_t TAMANHO_JANELA;
// }jogo;

// CORES
cor_t branco = {1, 1, 1, 1};
cor_t preto = {0, 0, 0, 1};
cor_t vermelho = {1, 0, 0, 1};
cor_t amarelo = {1, 1, 0, 1};
cor_t verde = {0, 1, 0, 1,};
cor_t cinza = {0.168, 0.176, 0.258, 1};
cor_t roxo = {0.5, 0.07, 0.388, 1};

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

cor_t cor_status(int lado, char str[]){
    int i, quant_rainhas=0;
    
    for (i=0; i<lado*lado; i++){
        if (str[i] == RAINHA) quant_rainhas++; 
    }

    if (!verifica_linha(lado, str) || !verifica_coluna(lado, str) || !verifica_diagonal(lado, str)) return vermelho;
    else if (quant_rainhas<lado) return amarelo;
    else return verde;
}

tamanho_t janela = {ALTURA, LARGURA};

void desenha_rainha(int altura_posicao, int largura_posicao, int y_inicio, int x_inicio){
    circulo_t rainha;
    rainha.raio = largura_posicao/5;
    rainha.centro.y = y_inicio + (altura_posicao/2);
    rainha.centro.x = x_inicio + (largura_posicao/2);
    j_circulo(rainha, 0, preto, vermelho);
}

void desenha_desistir(){
    int tamanho_txt = 16;
    
    ponto_t inicio_txt;
    inicio_txt.y = 10 + tamanho_txt; 
    inicio_txt.x = 1; 
    j_texto(inicio_txt, tamanho_txt, branco, "DESISTIR");

}

void desenha_tempo(time_t start){
    int tamanho_txt = 14;
    ponto_t inicio_texto;
    inicio_texto.y = 10 + tamanho_txt; 
    inicio_texto.x = janela.largura/2 - 30;

    long tempo_atual = time(NULL) - start; 
    char txt[100];
    sprintf(txt, "Tempo: %ld s", tempo_atual);
    j_texto(inicio_texto, tamanho_txt, branco, txt);

}

void desenha_tabuleiro(int lado, char str[], int lin, int col){

    // inicializa o tamanho de uma posição do tabuleiro
    int altura, largura;
    altura = (janela.altura - 3*MARGEM) / lado;
    largura = (janela.largura - 4*MARGEM) / lado;
    retangulo_t posicao;
    posicao.tamanho.altura = altura;
    posicao.tamanho.largura = largura;

    // inicializa o tamanho do tabuleiro
    retangulo_t tabuleiro;
    tabuleiro.tamanho.altura = ((lado * altura)+LARGURA_BORDA);
    tabuleiro.tamanho.largura = ((lado * largura)+LARGURA_BORDA);
    tabuleiro.inicio.x = janela.largura/2 - tabuleiro.tamanho.largura/2;    
    tabuleiro.inicio.y = janela.altura/2 - tabuleiro.tamanho.altura/2;    

    // fundo
    retangulo_t background;
    background.tamanho.altura = janela.altura;
    background.tamanho.largura = janela.largura;
    background.inicio.x = 1;
    background.inicio.y = 1;

    j_retangulo(background, 0, preto, cinza); //fundo
    cor_t cor = cor_status(lado, str); // cor da borda
    j_retangulo(tabuleiro, 3, preto, cor);

    // desenhando as posições no tabuleiro
    int i, j;
    posicao.inicio.x = tabuleiro.inicio.x + LARGURA_BORDA/2;
    posicao.inicio.y = tabuleiro.inicio.y + LARGURA_BORDA/2;

    int pos_destacada = (lin-1)*lado + (col-1);
    for (i=1; i<=lado; i++){
        for (j=1; j<=lado; j++){
            int indice = (i-1)*lado + (j-1);

            if (indice == pos_destacada) j_retangulo(posicao, 1, preto, roxo);
            else if ((i+j)%2==0) j_retangulo(posicao, 1, preto, preto);
            else j_retangulo(posicao, 1, preto, branco);
            
            if (str[indice] == RAINHA) desenha_rainha(posicao.tamanho.altura, posicao.tamanho.largura, posicao.inicio.y, posicao.inicio.x);
            
            posicao.inicio.x += largura;
        }
        posicao.inicio.x = tabuleiro.inicio.x + LARGURA_BORDA/2;
        posicao.inicio.y += altura;
    }

}

bool processa_entrada(int lado, char str[], int *ref_lin, int *ref_col){
    if (!j_tem_tecla()) return false;

    char option = j_tecla();
    switch(option){
        case 'X':
        case 'x': return true;
        
        case 'W':
        case 'w':
            *ref_lin = (*ref_lin>1) ? *ref_lin-1 : *ref_lin+lado-1;
            return false;
        case 'S':
        case 's':
            *ref_lin = (*ref_lin<lado) ? *ref_lin+1 : *ref_lin-lado+1;
            return false;
        case 'A':
        case 'a': 
            *ref_col = (*ref_col>1) ? *ref_col-1 : *ref_col+lado-1;
            return false;
        case 'D':
        case 'd':
            *ref_col = (*ref_col<lado) ? *ref_col+1 : *ref_col-lado+1;
            return false;
        case '\n':
        case ESPACO_BRANCO:
            int indice = (*ref_lin-1)*lado + (*ref_col-1);  // indice relaciona linha e coluna com o indice da string do tabuleiro
            if (str[indice] == RAINHA) str[indice] = ESPACO_BRANCO;
            else if (str[indice] == ESPACO_BRANCO) str[indice] = RAINHA; 
            return false;
        default: return false;
    }
}

int main(){
    int i;
    int lado = 10;
    int tamanho = lado*lado;
    char str[tamanho];
    for (i=0; i<tamanho; i++){
        str[i] = ESPACO_BRANCO;
    }

    int lin=1, col=1;

    time_t start = time(NULL);
    t_inicializa(janela, str);
    while(true){
        processa_entrada(lado, str, &lin, &col);
        desenha_tabuleiro(lado, str, lin, col);
        desenha_tempo(start);
        desenha_desistir();
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
