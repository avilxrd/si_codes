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
cor_t branco   = {1, 1, 1, 1};
cor_t preto    = {0, 0, 0, 1};
cor_t vermelho = {1, 0, 0, 1};
cor_t amarelo  = {1, 1, 0, 1};
cor_t verde    = {0, 1, 0, 1,};
cor_t cinza    = {0.168, 0.176, 0.258, 1};
cor_t roxo     = {0.5, 0.07, 0.388, 1};

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
    long tempo_final;
    int status;
    bool encerrado;
}jogo_t;

void inicializa_jogo(jogo_t *pj){
    pj->tempo_inicial = time(NULL);
    pj->tamanho_txt = 48;
    pj->cor_status = amarelo;
    pj->status = 0;
    pj->encerrado = 0;
    pj->mouse = j_rato();
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

    pj->rainha.raio = pj->posicao.tamanho.largura/5;
}

// FUNÇÕES DE PROCESSAMENTO DO JOGO
// verifica se há conflito nas linhas
bool verifica_linha(jogo_t *pj){
    int lin, col, cont;

    for (lin=1; lin<=pj->lado; lin++){
        cont = 0;
        for (col=1; col<=pj->lado; col++){
            int indice = (lin-1)*pj->lado + (col-1);
            if (pj->str[indice] == RAINHA) cont++;
        }
        if (cont > 1) return false;
    }
    return true;
}
// verifica se há conflito nas colunas
bool verifica_coluna(jogo_t *pj){
    int lin, col, cont;

    for (col=1; col<=pj->lado; col++){
        cont = 0;
        for (lin=1; lin<=pj->lado; lin++){
            int indice = (lin-1)*pj->lado + (col-1);
            if (pj->str[indice] == RAINHA) cont++;
        }
        if (cont > 1) return false;
    }
    return true;
}
// verifica se há conflito nas diagonais
bool verifica_diagonal(jogo_t *pj){
    int lin, col, cont;

    // esquerda -> direita
    int col_inicial;
    for (col_inicial=1; col_inicial<=pj->lado; col_inicial++){
        cont = 0;
        lin = 1;
        col = col_inicial;
        while (lin <= pj->lado && col <= pj->lado) {
            int indice = (lin-1)*pj->lado + (col-1);
            if (pj->str[indice] == RAINHA) cont++;
            lin++;
            col++;
        }
        if (cont>1) return false;
    }
    int lin_inicial;
    for (lin_inicial=2; lin_inicial<=pj->lado; lin_inicial++){
        cont = 0;
        lin = lin_inicial;
        col = 1;
        while (lin<=pj->lado && col<=pj->lado){
            int indice = (lin-1)*pj->lado + (col-1);
            if (pj->str[indice] == RAINHA) cont++;
            lin++;
            col++;
        }
        if (cont>1) return false;
    }

    // direita -> esquerda
    for (col_inicial=1; col_inicial<=pj->lado; col_inicial++){
        cont = 0;
        lin = 1;
        col = col_inicial;
        while (lin<=pj->lado && col>=1){
            int indice = (lin-1)*pj->lado + (col-1);
            if (pj->str[indice] == RAINHA) cont++;
            lin++;
            col--;
        }
        if (cont>1) return false;
    }
    for (lin_inicial=2; lin_inicial<=pj->lado; lin_inicial++){
        cont = 0;
        lin = lin_inicial;
        col = pj->lado;
        while (lin<=pj->lado && col>=1){
            int indice = (lin-1)*pj->lado + (col-1);
            if (pj->str[indice] == RAINHA) cont++;
            lin++;
            col--;
        }
        if (cont > 1) return false;
    }
    return true;
}

void jogo_rainhas(jogo_t *pj){
    int i, rainhas=0;
    int lado = floorSqrt(pj->tamanho);

    for (i=0; i<pj->tamanho; i++){
        if (pj->str[i]==RAINHA) rainhas++;
    }

    if (!verifica_linha(pj) || !verifica_coluna(pj) || !verifica_diagonal(pj)) pj->cor_status=vermelho;
    else {
        if (rainhas<lado) pj->cor_status=amarelo;
        else {
            pj->cor_status=verde;
            pj->encerrado=1;
        }
    }
}

void mensagem_final(jogo_t *pj){
    retangulo_t tela_final;
    tela_final.inicio = (ponto_t){1,1};
    tela_final.tamanho = pj->tamanho_janela;
    char txt[150], txt2[150];

    switch(pj->status){
        case -1:
            j_retangulo(tela_final, 0, preto, cinza);

            sprintf(txt, "Desistiu em %ld segundos.", pj->tempo_final);
            j_texto((ponto_t){pj->tamanho_janela.largura/2 - 150, pj->tamanho_janela.altura/2 - 24}, 24, vermelho, txt);
            sprintf(txt2, "Clique no mouse para encerrar...");
            j_texto((ponto_t){pj->tamanho_janela.largura/2 - 200, pj->tamanho_janela.altura/2 + 24}, 24, vermelho, txt2);
            break;
        case 0:
           j_retangulo(tela_final, 0, preto, cinza);

            sprintf(txt, "Parabéns! %ld segundos.", pj->tempo_final);
            j_texto((ponto_t){pj->tamanho_janela.largura/2 - 150, pj->tamanho_janela.altura/2 - 24}, 24, verde, txt);
            sprintf(txt2, "Clique no mouse para encerrar...");
            j_texto((ponto_t){pj->tamanho_janela.largura/2 - 200, pj->tamanho_janela.altura/2 + 24}, 24, verde, txt2);
            break;
        default: printf("\nErro!\n\n");
    }
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
    pj->rainha.centro.y = pj->posicao.inicio.y + (pj->posicao.tamanho.altura/2);
    pj->rainha.centro.x = pj->posicao.inicio.x + (pj->posicao.tamanho.largura/2);
    j_circulo(pj->rainha, 0, preto, vermelho);
}
void desenha_posicoes(jogo_t *pj){
    pj->posicao.inicio.y = pj->tabuleiro.inicio.y + LARGURA_BORDA/2;
    pj->posicao.inicio.x = pj->tabuleiro.inicio.x + LARGURA_BORDA/2;

    for (int i=1; i<=pj->lado; i++){
        for (int j=1; j<=pj->lado; j++){
            int index = (i-1)*pj->lado + j-1;

            if ((i+j)%2==0) j_retangulo(pj->posicao, 1, preto, preto);
            else j_retangulo(pj->posicao, 1, preto, branco);

            if (pj->str[index]==RAINHA) desenha_rainha(pj);
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


int indice_tabuleiro(jogo_t *pj){
    if (pj->mouse.posicao.x < pj->tabuleiro.inicio.x ||
        pj->mouse.posicao.x >= pj->tabuleiro.inicio.x + pj->tabuleiro.tamanho.largura ||
        pj->mouse.posicao.y < pj->tabuleiro.inicio.y ||
        pj->mouse.posicao.y >= pj->tabuleiro.inicio.y + pj->tabuleiro.tamanho.altura) return -1;

    int coluna = ((pj->mouse.posicao.x - pj->tabuleiro.inicio.x) / pj->posicao.tamanho.largura);
    int linha = ((pj->mouse.posicao.y - pj->tabuleiro.inicio.y) / pj->posicao.tamanho.altura);

    // printf("Clique detectado em linha: %d, coluna: %d\n", linha+1, coluna+1);

    // printf("Indice: [%d] \n", (linha)*pj->lado + (coluna));
    return linha*pj->lado + coluna;
}
bool desistiu(jogo_t *pj){
    if (pj->mouse.posicao.x >= pj->desistir.inicio.x &&
        pj->mouse.posicao.x <= pj->desistir.inicio.x + pj->desistir.inicio.x + pj->desistir.tamanho.largura &&
        pj->mouse.posicao.y >= pj->desistir.inicio.y &&
        pj->mouse.posicao.y <= pj->desistir.inicio.y + pj->desistir.inicio.x + pj->desistir.tamanho.altura) return 1;
        else return 0;
}
void processa_mouse(jogo_t *pj){
    pj->mouse = j_rato();
    desenha_cursor(pj);

    if (pj->mouse.clicado[0]){
        if (desistiu(pj)){
            pj->status    = -1;
            pj->encerrado =  1;
        }
        else {
            int index = indice_tabuleiro(pj);
            if (index != -1) {
                pj->str[index] = (pj->str[index] == ESPACO_BRANCO) ? RAINHA : ESPACO_BRANCO;
           }
        }
    }
}

int main(int argc, char *argv[]){
    jogo_t jogo;
    jogo.tamanho_janela = (tamanho_t){800, 600};
    
    if (argc==1){
        printf("\nnenhum argumento passado, tamanho default: 4\n\n");
        jogo.lado = 4;
    } else if (argc==2){
        if (atoi(argv[1]) > 0) jogo.lado= atoi(argv[1]); //converte str para int
        else{
            // caso passe um valor negativo, pede outro
            printf("O tamanho deve ser um número inteiro.\n");
            printf("Digite um valor correto: ");
            scanf("%d", &jogo.lado);    
            // return 1;
        }
    }
    
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

    while(jogo.encerrado!=1){
        // printf("String: [");
        // for (int i=0; i<jogo.tamanho; i++) printf("%c", jogo.str[i]);
        // printf("]\n");
        jogo_rainhas(&jogo);
        desenha_janela(&jogo);
        desenha_gui(&jogo);
        desenha_posicoes(&jogo);
        processa_mouse(&jogo);
        j_atualiza();
    }

    jogo.tempo_final = time(NULL) - jogo.tempo_inicial;
    while (true) {
        mensagem_final(&jogo);
        jogo.mouse = j_rato();
        if (jogo.mouse.clicado[0]) break;
        j_atualiza();
    }
    free(jogo.str);
    j_finaliza();
    return 0;
}
