// l1-t4 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//CONSTANTES
#define MARGEM 50

// CORES
cor_t branco   = {1, 1, 1, 1};
cor_t preto    = {0, 0, 0, 1};
cor_t vermelho = {1, 0, 0, 1};
cor_t amarelo  = {1, 1, 0, 1};
cor_t verde    = {0, 1, 0, 1,};
cor_t cinza    = {0.168, 0.176, 0.258, 1};
cor_t roxo     = {0.5, 0.07, 0.388, 1};

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
    for (int j=0; j<9; j++) str[i][j] = 1 + rand()%10;
  }
}

void inicializa_jogo(jogo_t *pj){
  pj->janela = (tamanho_t){800, 600};
  inicializa_matriz(pj->str);
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
  tabuleiro.tamanho = (tamanho_t) {12*50, 9*50};
  tabuleiro.inicio  = (ponto_t)   {pj->janela.largura/2 - tabuleiro.tamanho.largura/2, pj->janela.altura/2 - tabuleiro.tamanho.altura/2};
  j_retangulo(tabuleiro, 0, preto, verde);
}

void desenha_cursor(rato_t mouse){
  circulo_t pos;
  pos.centro = mouse.posicao;
  pos.raio = 5;
  j_circulo(pos, 0, preto, roxo);
}


void desenha_tela(){

}

int main()  {
  jogo_t jogo;

  inicializa_jogo(&jogo);
  t_inicializa(jogo.janela, "Numbers");
  while(true){
    rato_t mouse = j_rato();
    desenha_fundo(&jogo);
    desenha_tabuleiro(&jogo);
    desenha_cursor(mouse);
    j_atualiza();
  }
}
