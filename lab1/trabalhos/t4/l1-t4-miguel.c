// l1-t4 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//CONSTANTES
#define MARGEM_ALTURA  50
#define MARGEM_LARGURA 350

// CORES
cor_t branco      = {1, 1, 1, 1};
cor_t preto       = {0, 0, 0, 1};
cor_t amarelo     = {1, 1, 0, 1};
cor_t cinza       = {0.168, 0.176, 0.258, 1};
cor_t roxo        = {0.5, 0.07, 0.388, 1};

cor_t azul_claro  = {0.16, 0.84, 0.91, 1};
cor_t azul_escuro = {0.37, 0.53, 0.93, 1};
cor_t verde       = {0.33, 0.79, 0.26, 1};
cor_t laranja     = {1.00, 0.53, 0.24, 1};
cor_t vermelho    = {0.99, 0.30, 0.36, 1};
cor_t cinza_claro = {0.87, 0.89, 0.90, 1};

typedef struct{
    int str[12][9];
    tamanho_t janela;
}jogo_t;

void inicializa_matriz(int str[12][9]){
    srand(time(NULL));
    //inicializa as casas vazias: 5 primeiras linhas
    for (int i=0; i<5; i++){
    for (int j=0; j<9; j++) str[i][j] = 0;
    }
    //inicializa as casas não vazias: 6ª a 12ª linhas.
    for (int i=5; i<12; i++){
    for (int j=0; j<9; j++) str[i][j] = 1 + rand()%9;
    }
}

void inicializa_jogo(jogo_t *pj){
    pj->janela = (tamanho_t){800, 600};
    inicializa_matriz(pj->str);
}
//calcula o tamanho do "quadradinho" 
tamanho_t calcula_tamanho(tamanho_t janela){
    tamanho_t quad;
    quad.largura = (janela.largura - MARGEM_LARGURA)/9;
    quad.altura  = (janela.altura  - MARGEM_ALTURA)/12;
    return quad; 
}

// FUNÇÕES DE DESENHO
void desenha_fundo(jogo_t *pj){
    retangulo_t fundo;
    fundo.inicio = (ponto_t){1,1};
    fundo.tamanho = (tamanho_t){pj->janela.largura, pj->janela.altura};
    j_retangulo(fundo, 0, preto, cinza);
}

void desenha_tabuleiro(jogo_t *pj){
    retangulo_t tabuleiro;
    // tabuleiro.tamanho = (tamanho_t) {12*50, 9*50};
    tamanho_t tam = calcula_tamanho(pj->janela);
    tabuleiro.tamanho.altura  = 12*tam.altura;
    tabuleiro.tamanho.largura = 9*tam.altura;

    tabuleiro.inicio  = (ponto_t){pj->janela.largura/2 - tabuleiro.tamanho.largura/2, pj->janela.altura/2 - tabuleiro.tamanho.altura/2};
    j_retangulo(tabuleiro, 0, preto, verde);
}

void desenha_cursor(rato_t mouse){
    circulo_t pos;
    pos.centro = mouse.posicao;
    pos.raio = 3;
    j_circulo(pos, 1, preto, branco);
}

cor_t detecta_cor(int num){
    if      (num==1 || num==9) return azul_escuro;
    else if (num==2 || num==8) return verde;
    else if (num==3 || num==7) return azul_claro;
    else if (num==4 || num==6) return laranja;
    else if (num==5)           return vermelho;
    else                       return cinza_claro;
}

void desenha_quad(jogo_t *pj){
    retangulo_t quad;
    quad.tamanho = calcula_tamanho(pj->janela);
    quad.inicio.x  = (pj->janela.largura/2) - (9*quad.tamanho.largura)/2;
    quad.inicio.y  = (pj->janela.altura/2)  - (12*quad.tamanho.altura)/2;

    for (int i=0; i<12; i++){
        for (int j=0; j<9; j++){
            cor_t cor = detecta_cor(pj->str[i][j]);
            j_retangulo(quad, 2, branco, cor);
            
            char num[100];
            sprintf(num, "%d", pj->str[i][j]);
            ponto_t pos = (ponto_t){quad.inicio.x + quad.tamanho.largura/2, quad.inicio.y + quad.tamanho.altura/2};
            retangulo_t txt = j_texto_contorno(pos, 24, num); //cria um retangulo invisivel para descobrir a largura do txt e alinhar
            
            pos.x = (quad.inicio.x + quad.tamanho.largura/2) - txt.tamanho.largura/2;
            pos.y = (quad.inicio.y + quad.tamanho.altura/2)  + txt.tamanho.altura/2;
            if (pj->str[i][j]!=0) j_texto(pos, 24, branco, num);

            quad.inicio.x += quad.tamanho.largura;
        }
        quad.inicio.x  = (pj->janela.largura/2) - (9*quad.tamanho.largura)/2;
        quad.inicio.y += quad.tamanho.altura; 
    }
}

void desenha_add(tamanho_t janela){
    ponto_t final = {janela.largura, janela.altura};

    circulo_t add;
    add.raio = 25;
    add.centro = (ponto_t){final.x - MARGEM_LARGURA/4, final.y - MARGEM_ALTURA};
    j_circulo(add, 1, branco, vermelho);

    retangulo_t cross_x;
    cross_x.tamanho = (tamanho_t){(add.raio),6};
    cross_x.inicio  = (ponto_t){add.centro.x - (add.raio)/2, add.centro.y - (cross_x.tamanho.altura)/2};
    j_retangulo(cross_x, 0, preto, branco);
    
    circulo_t arredondar;
    arredondar.raio = cross_x.tamanho.altura/2;
    arredondar.centro = (ponto_t){cross_x.inicio.x, cross_x.inicio.y + (cross_x.tamanho.altura)/2};
    j_circulo(arredondar, 0, branco, branco);
    arredondar.centro = (ponto_t){cross_x.inicio.x + cross_x.tamanho.largura, cross_x.inicio.y + (cross_x.tamanho.altura)/2};
    j_circulo(arredondar, 0, branco, branco);

    retangulo_t cross_y;
    cross_y.tamanho = (tamanho_t){6,(add.raio)};
    cross_y.inicio  = (ponto_t){add.centro.x - (cross_y.tamanho.largura)/2, add.centro.y - (add.raio)/2};
    j_retangulo(cross_y, 0, preto, branco);
    arredondar.centro = (ponto_t){cross_y.inicio.x + (cross_y.tamanho.largura)/2, cross_y.inicio.y};
    j_circulo(arredondar, 0, branco, branco);
    arredondar.centro = (ponto_t){cross_y.inicio.x + (cross_y.tamanho.largura)/2, cross_y.inicio.y + cross_y.tamanho.altura};
    j_circulo(arredondar, 0, branco, branco);

}

int main()  {
    jogo_t jogo;

    inicializa_jogo(&jogo);
    t_inicializa(jogo.janela, "Numbers");
    while(true){
    rato_t mouse = j_rato();
    desenha_fundo(&jogo);
    // desenha_tabuleiro(&jogo);
    desenha_quad(&jogo);
    desenha_add(jogo.janela);
    desenha_cursor(mouse);
    j_atualiza();
    }   
}
