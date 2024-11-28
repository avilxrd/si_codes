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
    rato_t mouse;
    tamanho_t tamanho_janela;
    cor_t cor_status;

    retangulo_t background;
    retangulo_t tabuleiro;
    retangulo_t posicao;
    retangulo_t desistir;
    circulo_t rainha;
    circulo_t cursor;

    int index;
    int lin;
    int col;
    int lado;
    int tamanho;
    char *str;
    int tamanho_txt;
    long tempo_inicial;
    int status;
}jogo_t;

void inicializa_jogo(jogo_t *pj){
    pj->tempo_inicial = time(NULL);
    pj->tamanho_txt = 48;
    pj->cor_status = amarelo;
    pj->status = 0;
}

void inicia_tabuleiro(jogo_t *pj){
    float altura  = (pj->tamanho_janela.altura - 3*MARGEM)  / pj->lado;
    float largura = (pj->tamanho_janela.largura - 4*MARGEM) / pj->lado;
    pj->posicao.tamanho = (tamanho_t){largura, altura};
    
    // tabuleiro
    pj->tabuleiro.tamanho.altura  = ((pj->lado * altura)+LARGURA_BORDA); 
    pj->tabuleiro.tamanho.largura = ((pj->lado * largura)+LARGURA_BORDA); 
    pj->tabuleiro.inicio.x = pj->tamanho_janela.largura/2 - pj->tabuleiro.tamanho.largura/2;    
    pj->tabuleiro.inicio.y = pj->tamanho_janela.altura/2 -  pj->tabuleiro.tamanho.altura/2;

    // background
    pj->background.inicio = (ponto_t){1,1};
    pj->background.tamanho.altura = pj->tamanho_janela.altura;
    pj->background.tamanho.largura = pj->tamanho_janela.largura;
}

// FUNÇÕES DE DESENHO
void desenha_janela(jogo_t *pj){
    j_retangulo(pj->background, 0, preto, cinza); //fundo
    j_retangulo(pj->tabuleiro, 3, preto, pj->cor_status); //tabuleiro
}
void desenha_gui(jogo_t *pj){
    char tempo[100];
    sprintf(tempo, "%ld", time(NULL) - pj->tempo_inicial);
    j_texto((ponto_t){pj->tamanho_janela.largura/2, pj->tamanho_txt}, pj->tamanho_txt, branco, tempo);
    char desistir[100];
    sprintf(desistir, "Desistir");
    ponto_t posicao_desistir = (ponto_t){1, pj->tamanho_txt};
    pj->desistir = j_texto_contorno(posicao_desistir, pj->tamanho_txt, desistir);    
    j_texto(posicao_desistir, pj->tamanho_txt, branco, desistir);   
}
void desenha_rainha(jogo_t *pj){
    pj->rainha.raio = pj->posicao.tamanho.largura/5;
    pj->rainha.centro.y = pj->posicao.inicio.y + (pj->posicao.tamanho.altura/2);
    pj->rainha.centro.x = pj->posicao.inicio.x + (pj->posicao.tamanho.altura/2);
    j_circulo(pj->rainha, 0, preto, vermelho);
}
void desenha_posicoes(jogo_t *pj){
    pj->posicao.inicio.y = pj->tabuleiro.inicio.y + LARGURA_BORDA/2;
    pj->posicao.inicio.x = pj->tabuleiro.inicio.x + LARGURA_BORDA/2;

    for (int i=1; i<=pj->lado; i++){
        
        for (int j=1; j<=pj->lado; j++){
            pj->index = (pj->lin)*pj->lado + pj->col;

            if ((i+j)%2==0) j_retangulo(pj->posicao, 1, preto, preto);
            else j_retangulo(pj->posicao, 1, preto, branco);
            
            if (pj->str[pj->index]==RAINHA) desenha_rainha(pj);
            pj->posicao.inicio.x += pj->posicao.tamanho.largura;
        }
        pj->posicao.inicio.x =  pj->tabuleiro.inicio.x + LARGURA_BORDA/2;
        pj->posicao.inicio.y += pj->posicao.tamanho.altura;
    }
}
void desenha_cursor(jogo_t *pj){
    pj->cursor = (circulo_t){pj->mouse.posicao, 5};
    j_circulo(pj->cursor, 0, preto, vermelho);
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
    inicia_tabuleiro(&jogo);
    while(jogo.status==0){
        desenha_janela(&jogo);
        desenha_gui(&jogo);
        desenha_posicoes(&jogo);
        processa_mouse(&jogo);
        desenha_cursor(&jogo);
        j_atualiza();
    }
    
}