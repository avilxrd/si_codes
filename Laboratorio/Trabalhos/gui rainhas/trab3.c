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

// CORES
cor_t branco = {1, 1, 1, 1};
cor_t preto = {0, 0, 0, 1};
cor_t vermelho = {1, 0, 0, 1};
cor_t amarelo = {1, 1, 0, 1};
cor_t verde = {0, 1, 0, 1,};
cor_t cinza = {0.168, 0.176, 0.258, 1};
cor_t roxo = {0.5, 0.07, 0.388, 1};

typedef struct{
    tamanho_t tamanho_janela;
    rato_t mouse;

    retangulo_t tabuleiro;
    retangulo_t posicao;
    retangulo_t desistir;

    int tamanho_txt;

    int lado;
    int tamanho;
    char *str;
    int lin;
    int col;

    // variaveis do jogo
    long tempo_inicial;
    long tempo_final;
    int status_saida;
}jogo_t;

void inicializa_jogo(jogo_t *pj){
    pj->tempo_inicial = time(NULL);
    pj->tamanho_txt = 14;
    pj->status_saida = 0;   
}

void tempo(jogo_t *pj){
    pj->tempo_final = time(NULL) - pj->tempo_inicial;
}


void processa_mouse(jogo_t *pj){
    pj->mouse = j_rato();
    if (pj->mouse.clicado[0]){

    }
}

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


// funções de desenho:
void tela_inicial(jogo_t *pj){
    retangulo_t tela;
    tela.tamanho = (tamanho_t){pj->tamanho_janela.altura, pj->tamanho_janela.largura};
    tela.inicio = (ponto_t){1,1};

    char txt[250];
    sprintf(txt, "Aperte enter para começar...");

}

void desenha_rainha(int altura_posicao, int largura_posicao, int y_inicio, int x_inicio){
    circulo_t rainha;
    rainha.raio = largura_posicao/5;
    rainha.centro.y = y_inicio + (altura_posicao/2);
    rainha.centro.x = x_inicio + (largura_posicao/2);
    j_circulo(rainha, 0, preto, vermelho);
}

void desenha_desistir(jogo_t *pj){
    char txt[100];
    sprintf(txt, "Desistir");

    int tamanho_txt = 24;
    ponto_t pos = {1,tamanho_txt};
    pj->desistir = j_texto_contorno(pos, tamanho_txt, txt);
    
    j_texto(pos, tamanho_txt, branco, txt);
}

void desenha_tempo(jogo_t *pj){
    int tamanho_txt = 14;
    ponto_t inicio_texto;
    inicio_texto.y = 10 + tamanho_txt; 
    inicio_texto.x = pj->tamanho_janela.largura/2 - 30;
    
    char txt[100];
    sprintf(txt, "Tempo: %ld s", time(NULL) - pj->tempo_inicial);
    j_texto(inicio_texto, tamanho_txt, branco, txt);

}

void desenha_tabuleiro(jogo_t *pj){

    // inicializa o tamanho de uma posição do tabuleiro
    int altura, largura;
    altura = (pj->tamanho_janela.altura - 3*MARGEM) / pj->lado;
    largura = (pj->tamanho_janela.largura - 4*MARGEM) / pj->lado;

    retangulo_t posicao;
    posicao.tamanho.altura = altura;
    posicao.tamanho.largura = largura;

    // inicializa o tamanho do tabuleiro
    retangulo_t tabuleiro;
    tabuleiro.tamanho.altura = ((pj->lado * altura)+LARGURA_BORDA);
    tabuleiro.tamanho.largura = ((pj->lado * largura)+LARGURA_BORDA);
    tabuleiro.inicio.x = pj->tamanho_janela.largura/2 - tabuleiro.tamanho.largura/2;    
    tabuleiro.inicio.y = pj->tamanho_janela.altura/2 - tabuleiro.tamanho.altura/2;    

    // fundo
    retangulo_t background;
    background.tamanho.altura = pj->tamanho_janela.altura;
    background.tamanho.largura = pj->tamanho_janela.largura;
    background.inicio.x = 1;
    background.inicio.y = 1;

    j_retangulo(background, 0, preto, cinza); //fundo
    cor_t cor = cor_status(pj->lado, pj->str); // cor da borda
    j_retangulo(tabuleiro, 3, preto, cor);

    // desenhando as posições no tabuleiro
    int i, j;
    posicao.inicio.x = tabuleiro.inicio.x + LARGURA_BORDA/2;
    posicao.inicio.y = tabuleiro.inicio.y + LARGURA_BORDA/2;

    int pos_destacada = (pj->lin-1)*pj->lado + (pj->col-1);

    for (i=1; i<=pj->lado; i++){
        for (j=1; j<=pj->lado; j++){
            int indice = (i-1)*pj->lado + (j-1);

            if (indice == pos_destacada) j_retangulo(posicao, 1, preto, roxo);
            else if ((i+j)%2==0) j_retangulo(posicao, 1, preto, preto);
            else j_retangulo(posicao, 1, preto, branco);
            
            if (pj->str[indice] == RAINHA) desenha_rainha(posicao.tamanho.altura, posicao.tamanho.largura, posicao.inicio.y, posicao.inicio.x);
            
            posicao.inicio.x += largura;
        }
        posicao.inicio.x = tabuleiro.inicio.x + LARGURA_BORDA/2;
        posicao.inicio.y += pj->posicao.tamanho.altura;
    }

}

void desenha_cursor(jogo_t *pj){
    circulo_t cursor = {pj->mouse.posicao, 5};
    j_circulo(cursor, 0, preto, vermelho);
}

void desenha_tela(jogo_t *pj){
    desenha_tabuleiro(pj);
    desenha_tempo(pj);
    desenha_desistir(pj);
    desenha_cursor(pj);
}

int main(){
    jogo_t jogo;

    jogo.tamanho_janela = (tamanho_t){800, 600};

    printf("Tamanho (ex. 4 => 4x4): ");
    scanf("%d", &jogo.lado);  
    jogo.tamanho = jogo.lado*jogo.lado;
    
    jogo.str = malloc(jogo.tamanho * sizeof(char));
    if (!jogo.str){
        printf("Erro ao alocar memoria para str!");
        return -1;
    }
    // inicializa str vazia
    for (int i=0; i<jogo.tamanho; i++){
        jogo.str[i] = ESPACO_BRANCO;
    }

    jogo.lin = 1;
    jogo.col = 1;


    t_inicializa(jogo.tamanho_janela, "Rainhas");
    inicializa_jogo(&jogo);
    while(jogo.status_saida==0){
        desenha_tela(&jogo);
        tempo(&jogo);
        processa_mouse(&jogo);

        j_atualiza();
    }
}