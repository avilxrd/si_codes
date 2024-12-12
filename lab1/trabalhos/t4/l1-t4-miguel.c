// l1-t4 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MARGEM_ALTURA  50
#define MARGEM_LARGURA 350
#define LINHAS 12
#define COLUNAS 9

// defini várias mas provavelmente não vou usar todas.
cor_t branco      = {1, 1, 1, 1};
cor_t preto       = {0, 0, 0, 1};
cor_t amarelo     = {1, 1, 0, 1};

cor_t cinza       = {0.16, 0.17, 0.25, 1};
cor_t roxo        = {0.50, 0.07, 0.38, 1};
cor_t azul_claro  = {0.16, 0.84, 0.91, 1};
cor_t azul_escuro = {0.37, 0.53, 0.93, 1};
cor_t verde       = {0.33, 0.79, 0.26, 1};
cor_t laranja     = {1.00, 0.53, 0.24, 1};
cor_t vermelho    = {0.99, 0.30, 0.36, 1};
cor_t cinza_claro = {0.87, 0.89, 0.90, 1};

typedef struct{
    int i;
    int j;
}index_t;

typedef struct{
    int str[12][9];
    int recordes[10];
    int pontos;
    bool casa_selecionada;
    index_t selecionado;
    bool jaPega[LINHAS][COLUNAS];

    rato_t mouse;
    tamanho_t janela;
    tamanho_t tamanho_quad;
    // retangulos: o meu codigo cada vez que desenha algo, cria um retangulo novo, nao sei se isso deixa o jogo mt mais lento
    // ou não, mas na duvida (se der tempo) vou mudar para criar apenas 1 de cada e apenas desenhá-lo em posicoes diferentes
    // retangulo_t desistir;
    retangulo_t repovoar;
}jogo_t;

// ********** inicialização **********

//calcula o tamanho do "quadradinho" 
tamanho_t calcula_tamanho(tamanho_t janela){
    tamanho_t quad;
    quad.largura = (janela.largura - MARGEM_LARGURA)/9;
    quad.altura  = (janela.altura  - MARGEM_ALTURA)/12;
    return quad; 
}

// inicializa a matriz com numeros aleatorios
void inicializa_matriz(int str[12][9]){
    srand(time(NULL));
    //inicializa as casas vazias: 5 primeiras linhas
    for (int i=0; i<6; i++){
        for (int j=0; j<9; j++) str[i][j] = 0;
    }
    //inicializa as casas não vazias: 6ª a 12ª linhas.
    for (int i=6; i<12; i++){
        for (int j=0; j<9; j++) str[i][j] = 1 + rand()%9;
    }
}

// inicialização do jogo
void inicializaJaPega(jogo_t *pj) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            pj->jaPega[i][j] = false;  // Inicializa todas as posições como não "pegas"
        }
    }
}

void inicializa_jogo(jogo_t *pj){
    pj->janela = (tamanho_t){800, 600};
    pj->pontos = 0;
    pj->tamanho_quad = calcula_tamanho(pj->janela);
    pj->selecionado = (index_t){-1,-1};
}

// ********** funcoes para recordes **********

void ler_recordes(int recordes[10]){
    FILE *fp = fopen("recordes.txt", "r");

    if (fp == NULL){
        for (int i=0; i<10; i++) recordes[i] = 0;
        return;
    }

    for (int i=0; i<10; i++){
        if (fscanf(fp, "%d", &recordes[i]) != 1) recordes[i] = 0;
    }
    fclose(fp);
}

void salvar_recorde(int recordes[10]){
    FILE *fp = fopen("recordes.txt", "w");
    if (fp == NULL){
        printf("Erro!");
        return;
    }

    for (int i=0; i<10; i++){
        fprintf(fp, "%d\n", recordes[i]);
    }
    fclose(fp);
}

void atualizar_recorde(int recordes[10], int pontos){
    int i;
    for (i=0; i<10; i++){
        if (pontos > recordes[i]) break;
    }
    if (i == 10) return;
    for (int j=9; j>i; j--) recordes[j] = recordes[j-1];
    recordes[i] = pontos;
}

// ********** verificar a vizinhança **********

// verifica se A e B estão na mesma linha e em colunas diferentes
// e se não há casas ocupadas entre elas.
bool vizinhas_linha(jogo_t *pj, index_t a, index_t b){
    if (a.i != b.i || a.j == b.j) return false;
    int inicio = (a.j < b.j) ? a.j : b.j;
    int fim    = (a.j > b.j) ? a.j : b.j;
    
    for (int j=inicio+1; j<fim; j++) if (pj->str[a.i][j] != 0) return false; //há uma casa ocupada entre elas
    return true;
}

// verifica se A e B estão na mesma coluna e em linhas diferentes
// e se não há casas ocupadas entre elas.
bool vizinhas_coluna(jogo_t *pj, index_t a, index_t b){
    if (a.j != b.j || a.i == b.i) return false;
    int inicio = (a.i < b.i) ? a.i : b.i;
    int fim    = (a.i > b.i) ? a.i : b.i;

    for (int i = inicio + 1; i < fim; i++) if (pj->str[i][a.j] != 0) return false; //ha casa ocupada entre elas
    return true;
}

// verifica se A e B estão na mesma diagonal
// e se não há casas ocupadas entre elas.
bool vizinhas_diagonal(jogo_t *pj, index_t a, index_t b){
    // calcula a diferença absoluta entre as coordenadas de linha dx e coluna dy
    int dx = abs(a.i - b.i);
    int dy = abs(a.j - b.j);

    if (dx != dy) return false; // não estão na mesma diagonal

    int di = a.i < b.i ? 1 : -1;
    int dj = a.j < b.j ? 1 : -1;
    int i = a.i + di;
    int j = a.j + dj;

    while (i!=b.i && j!=b.j){
        if (pj->str[i][j] != 0) return false; // há alguma casa ocupada entre elas
        i += di;
        j += dj;
    }
    return true;
}

bool vizinhas_linha_seguinte(jogo_t *pj, index_t a, index_t b){
    if (b.i!=a.i+1) return false;

    int ultima_ocupada = -1;
    for (int j = 0; j < 9; j++) if (pj->str[a.i][j] != 0) ultima_ocupada = j;

    if (ultima_ocupada == -1 || b.j != 0 || pj->str[b.i][0] == 0) return false;
    return a.j == ultima_ocupada;
}

bool vizinhas_loop(jogo_t *pj, index_t a, index_t b){
    if (a.i != 11 || b.i != 0) return false;
    int ultima_ocupada = -1, primeira_ocupada = -1;

    for (int j = 0; j < 9; j++) if (pj->str[a.i][j] != 0) ultima_ocupada = j;

    for (int j = 0; j < 9; j++){
        if (pj->str[b.i][j] != 0){
            primeira_ocupada = j;
            break;
        }
    }
    return ultima_ocupada != -1 && primeira_ocupada != -1 && b.j == primeira_ocupada && a.j == ultima_ocupada;
}

// retorna se alguma das condições é válida
bool sao_vizinhas(jogo_t *pj, index_t a, index_t b){
    return vizinhas_linha          (pj, a, b) || 
           vizinhas_coluna         (pj, a, b) || 
           vizinhas_diagonal       (pj, a, b) ||
           vizinhas_linha_seguinte (pj, a, b) || 
           vizinhas_loop           (pj, a, b);
}

// ********** processamento do mouse **********

// verifica se o mouse esta dentro da posição passada
bool mouse_aqui(jogo_t *pj, int x, int y){
    pj->mouse = j_rato();
    if (pj->mouse.posicao.x>=x                              &&
        pj->mouse.posicao.x<=(x + pj->tamanho_quad.largura) && 
        pj->mouse.posicao.y>=y                              &&
        pj->mouse.posicao.y<=(y + pj->tamanho_quad.altura)
    ) return true;
    else return false;
}

//converte o clique de [x,y] -> index
index_t converte_clique(jogo_t *pj){
    tamanho_t quad_tam = calcula_tamanho(pj->janela);
    float x = (pj->janela.largura/2) - (9*quad_tam.largura)/2;
    float y = (pj->janela.altura/2)  - (12*quad_tam.altura)/2;

    int i, j;
    for (i=0; i<12; i++){
        for (j=0; j<9; j++){
            if (mouse_aqui(pj, x, y)) return (index_t){i,j};
            x += quad_tam.largura;
        }
        y += quad_tam.altura;
        x = (pj->janela.largura / 2) - (9 * quad_tam.largura) / 2;
    }
    return (index_t){-1, -1};
}

// verifica se uma linha está vazia
bool linha_vazia(int linha[9]){
    for (int j=0; j<9; j++) if (linha[j] != 0) return false;
    return true;
}

// apaga a linha e desloca as linhas acima para baixo
void atualizar_linhas(int str[12][9]){
    for (int i=0; i<11; i++){
        if (linha_vazia(str[i])){
            for (int j=i; j>0; j--) for (int k=0; k<9; k++) str[j][k] = str[j-1][k];
            for (int k=0; k<9; k++) str[0][k] = 0;
        }
    }
}

// ********** processamento **********

// seleção e desseleção
void selecionar_casa(jogo_t *pj, index_t indice){
    pj->casa_selecionada = true;
    pj->selecionado = indice;
}
void desmarcar_selecao(jogo_t *pj){
    pj->casa_selecionada = false;
}

// executa as ações quando uma combinação de numeros é válida
void realiza_combinacao(jogo_t *pj, index_t indice){
    printf("Vizinhas e iguais ou somadas = 10\n");
    pj->str[indice.i][indice.j] = 0;
    pj->str[pj->selecionado.i][pj->selecionado.j] = 0;
    pj->pontos += 9;
    desmarcar_selecao(pj);
    atualizar_linhas(pj->str);
}

// verifica se é válida a combinação
bool valida_combinacao(jogo_t *pj, index_t indice){
    int valor1 = pj->str[indice.i][indice.j];
    int valor2 = pj->str[pj->selecionado.i][pj->selecionado.j];
    return (valor1 + valor2 == 10 || valor1 == valor2);
}

// processa quando uma casa já foi selecionada
void processa_selecao_existente(jogo_t *pj, index_t indice){
    if (sao_vizinhas(pj, pj->selecionado, indice)){
        if (valida_combinacao(pj, indice)) realiza_combinacao(pj, indice);
        else {
            printf("Vizinhas mas diferentes e somadas não é 10\n");
            desmarcar_selecao(pj);
        }
    } else {
        printf("Não são vizinhas.\n");
        desmarcar_selecao(pj);
    }
}

// 
void processa_clique(jogo_t *pj, index_t indice){
    if (pj->str[indice.i][indice.j] != 0){
        if (pj->casa_selecionada) processa_selecao_existente(pj, indice);
        else selecionar_casa(pj, indice);
    }
}

void processa_mouse(jogo_t *pj){
    pj->mouse = j_rato();

    if (pj->mouse.clicado[0]){
        index_t indice = converte_clique(pj);
        if (indice.i >= 0 && indice.i < 12 && indice.j >= 0 && indice.j < 9) processa_clique(pj, indice);
    }
}

// ********** funções de desenho **********

// detecta a cor do fundo dos quadradinhos
cor_t detecta_cor(int num){
    if      (num==1 || num==9) return azul_escuro;
    else if (num==2 || num==8) return verde;
    else if (num==3 || num==7) return azul_claro;
    else if (num==4 || num==6) return laranja;
    else if (num==5)           return vermelho;
    else                       return cinza_claro;
}

// desenha um retangulo do tamanho da janela
void desenha_fundo(tamanho_t janela){
    retangulo_t fundo;
    fundo.inicio = (ponto_t){1,1};
    fundo.tamanho = (tamanho_t){janela.largura, janela.altura};
    j_retangulo(fundo, 0, preto, cinza);
}

// desenha um circulo na posição do cursor
void desenha_cursor(rato_t mouse){
    circulo_t pos;
    pos.centro = mouse.posicao;
    pos.raio = 3;
    j_circulo(pos, 1, preto, branco);
}

// desenha cada quadradinho com o seu conteúdo [vazio ou numero]
void desenha_quad(jogo_t *pj){
    retangulo_t quad;
    quad.tamanho = calcula_tamanho(pj->janela);
    quad.inicio.x  = (pj->janela.largura/2) - (9*quad.tamanho.largura)/2;
    quad.inicio.y  = (pj->janela.altura/2)  - (12*quad.tamanho.altura)/2;

    for (int i=0; i<12; i++){
        for (int j=0; j<9; j++){
            cor_t cor       = detecta_cor(pj->str[i][j]);
            cor_t cor_txt   = branco;

            if (pj->casa_selecionada && pj->selecionado.i == i && pj->selecionado.j == j) {
                cor       = branco;
                cor_txt   = vermelho;
            }

            j_retangulo(quad, 2, branco, cor);
            
            char num[100];
            sprintf(num, "%d", pj->str[i][j]);
            ponto_t pos = (ponto_t){quad.inicio.x + quad.tamanho.largura/2, quad.inicio.y + quad.tamanho.altura/2};
            retangulo_t txt = j_texto_contorno(pos, 24, num); // cria um retangulo invisivel para descobrir a largura do txt e alinhar
            
            pos.x = (quad.inicio.x + quad.tamanho.largura/2) - txt.tamanho.largura/2;
            pos.y = (quad.inicio.y + quad.tamanho.altura/2)  + txt.tamanho.altura/2;
            if (pj->str[i][j]!=0) j_texto(pos, 24, cor_txt, num);

            quad.inicio.x += quad.tamanho.largura;
        }
        quad.inicio.x  = (pj->janela.largura/2) - (9*quad.tamanho.largura)/2;
        quad.inicio.y += quad.tamanho.altura; 
    }
}

// arredonda as bordas de um retangulo
void arredonda(retangulo_t ret){
    circulo_t borda;
    
    if (ret.tamanho.largura > ret.tamanho.altura){
        borda.raio = ret.tamanho.altura/2;
        borda.centro = (ponto_t){ret.inicio.x, ret.inicio.y + (ret.tamanho.altura)/2};
        j_circulo(borda, 0, branco, branco);
        borda.centro = (ponto_t){ret.inicio.x + ret.tamanho.largura, ret.inicio.y + (ret.tamanho.altura)/2};
        j_circulo(borda, 0, branco, branco);
    } else {
        borda.raio = ret.tamanho.largura/2;
        borda.centro = (ponto_t){ret.inicio.x + (ret.tamanho.largura)/2, ret.inicio.y};
        j_circulo(borda, 0, branco, branco);
        borda.centro = (ponto_t){ret.inicio.x + (ret.tamanho.largura)/2, ret.inicio.y + ret.tamanho.altura};
        j_circulo(borda, 0, branco, branco);
    }
}

// desenha o botão de repovoamento
void desenha_repovoar(tamanho_t janela, retangulo_t repovoa){
    ponto_t final = {janela.largura, janela.altura};

    circulo_t add;
    add.raio = 25;
    add.centro = (ponto_t){final.x - MARGEM_LARGURA/4, final.y - MARGEM_ALTURA};
    j_circulo(add, 1, branco, vermelho);

    retangulo_t cross_x;
    cross_x.tamanho = (tamanho_t){(add.raio),6};
    cross_x.inicio  = (ponto_t){add.centro.x - (add.raio)/2, add.centro.y - (cross_x.tamanho.altura)/2};
    j_retangulo(cross_x, 0, preto, branco);
    arredonda(cross_x);

    retangulo_t cross_y;
    cross_y.tamanho = (tamanho_t){6,(add.raio)};
    cross_y.inicio  = (ponto_t){add.centro.x - (cross_y.tamanho.largura)/2, add.centro.y - (add.raio)/2};
    j_retangulo(cross_y, 0, preto, branco);
    arredonda(cross_y);

    // "hitbox" do botao circular (no caso é um retangulo)
    repovoa.inicio  = (ponto_t){add.centro.x - add.raio, add.centro.y - add.raio};
    repovoa.tamanho = (tamanho_t){add.raio*2, add.raio*2};
    // j_retangulo(repovoa, 0, preto, azul_claro); 
}

// desenha a pontuação atual do jogador
void desenha_pontos(int pontos){
    char txt[100];
    sprintf(txt, "%d", pontos);
    ponto_t pos = (ponto_t){10, 30};
    j_texto(pos, 24, branco, txt);
}

// desenha a interface completa
void desenha_interface(tamanho_t janela, int pontos, retangulo_t repovoar){
    desenha_fundo(janela);
    desenha_pontos(pontos);
    desenha_repovoar(janela, repovoar);
}

// ********** repovoamento **********
bool clique_repovoa(retangulo_t repovoa){
    rato_t mouse = j_rato();
    if (mouse.posicao.x >= repovoa.inicio.x &&
        mouse.posicao.x <= repovoa.inicio.x + repovoa.tamanho.largura &&
        mouse.posicao.y >= repovoa.inicio.y &&
        mouse.posicao.y <= repovoa.inicio.y + repovoa.tamanho.altura) return true;
    return false;
}

int pegaUltimo(jogo_t *pj){
  int carregador = 0;
  for(int i = LINHAS - 1; i >= 0; i--){
    for(int j = COLUNAS - 1; j >= 0; j--){
      if((pj->str[i][j] != 0) && (pj->jaPega[i][j] == false)){
        pj->jaPega[i][j] = true;
        carregador = pj->str[i][j];
        return carregador;
      }
    }
  }
  return carregador;
}

void repovoaTabuleiro(jogo_t *pj){
  for(int i = LINHAS - 1; i >= 0; i--){
    for(int j = COLUNAS - 1; j >= 0; j--){
      if(pj->str[i][j] == 0){
        pj->str[i][j] = pegaUltimo(pj);
        pj->jaPega[i][j] = true;
      }
    }
  }
}

// ********** passando arquivo **********

// modifiquei a funcao para ler os . mas converter para 0, pois meu tabuleiro é de int
bool verifica_args(int nl, int nc, int tab[nl][nc], int argc, char *argv[])
{
    if (argc != 2) return false;
    char *nome = argv[1];
    FILE *arq = fopen(nome, "r");
    if (arq == NULL) return false;

    bool consegui_ler = true;
    for (int l = 0; l < nl; l++){
        for (int c = 0; c < nc; c++){
            char val;
            if (fscanf(arq, " %c", &val) == 1){
                if (val == '.') {
                    tab[l][c] = 0; 
                } else if (val >= '1' && val<='9'){
                    tab[l][c] = val - '0'; 
                } else {
                    consegui_ler = false;
                    break;
                }
            } else {
                consegui_ler = false;
                break;
            }
        }
        if (!consegui_ler) break;
    }
    fclose(arq);
    return consegui_ler;
}

// ********** lógica principal **********
int main(int argc, char *argv[]){
    jogo_t jogo;

    if (!verifica_args(12, 9, jogo.str, argc, argv)){
        inicializa_matriz(jogo.str);
    }

    inicializa_jogo(&jogo);
    ler_recordes(jogo.recordes);

    t_inicializa(jogo.janela, "Numbers");
    while(true){
        if (j_tecla() == 27) break; // 27 == ESC na tabela ASCII.
        desenha_interface(jogo.janela, jogo.pontos, jogo.repovoar);
        desenha_quad(&jogo);
        desenha_cursor(jogo.mouse);
        processa_mouse(&jogo);
        j_atualiza();
    }   
    atualizar_recorde(jogo.recordes, jogo.pontos);
    salvar_recorde(jogo.recordes);

    j_finaliza();
    return 0;
}
