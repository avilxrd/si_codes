// l1-t4 Miguel Avila de Oliveira
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// ********** constantes globais **********
#define MARGEM_ALTURA  50
#define MARGEM_LARGURA 350
#define LINHAS 12
#define COLUNAS 9

cor_t branco      = {1, 1, 1, 1};
cor_t preto       = {0, 0, 0, 1};
cor_t cinza       = {0.16, 0.17, 0.25, 1};
cor_t azul_claro  = {0.16, 0.84, 0.91, 1};
cor_t azul_escuro = {0.37, 0.53, 0.93, 1};
cor_t verde       = {0.33, 0.79, 0.26, 1};
cor_t laranja     = {1.00, 0.53, 0.24, 1};
cor_t vermelho    = {0.99, 0.30, 0.36, 1};
cor_t cinza_claro = {0.87, 0.89, 0.90, 1};

// estrutura indice
typedef struct{
    int i;
    int j;
}index_t;

// estrutura do jogo
typedef struct{
    rato_t mouse;
    tamanho_t janela;
    int tabuleiro[LINHAS][COLUNAS]; 
    int linhas_vazias[LINHAS];
    int recordes[10];
    int pontos;
    int status; // -2: perdeu | -1: desistiu | 0: rodando | 1: ganhou
    int restantes; // quantas peças faltam a serem retiradas
    bool jogadas_disponiveis;

    bool casa_selecionada;
    index_t selecionado;

    tamanho_t tamanho_quad;
    // retangulos e circulos para nao criar um novo dentro do loop
    circulo_t cursor;
    retangulo_t quad;
    retangulo_t fundo;
    retangulo_t half;
    retangulo_t repovoar; 
    retangulo_t status_final;
}jogo_t;

// ********** inicialização **********

// calcula o tamanho do "quadradinho" 
tamanho_t calcula_tamanho(tamanho_t janela){
    tamanho_t quad;
    quad.largura = (janela.largura - MARGEM_LARGURA)/COLUNAS;
    quad.altura  = (janela.altura  - MARGEM_ALTURA)/LINHAS;
    return quad; 
}

// calcula quantas casas há diferentes de 0
int inicializa_restantes(int tabuleiro[LINHAS][COLUNAS]){
    int restantes = 0;
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++) if (tabuleiro[i][j]!=0) restantes++;
    } 
    return restantes;
}

// inicializa a matriz com numeros aleatorios
void inicializa_matriz(int tabuleiro[LINHAS][COLUNAS]){
    srand(time(NULL));
    // inicializa as casas vazias: 5 primeiras linhas
    for (int i=0; i<LINHAS/2; i++){
        for (int j=0; j<COLUNAS; j++) tabuleiro[i][j] = 0;
    }
    // inicializa as casas não vazias: 6ª a 12ª linhas
    for (int i=6; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++) tabuleiro[i][j] = 1 + rand()%9;
    }
}

// define os estados iniciais das variaveis de jogo
void inicializa_jogo(jogo_t *pj){
    pj->janela       = (tamanho_t){800, 600};
    pj->pontos       = 0;
    pj->status       = 0; // jogo rodando
    pj->selecionado  = (index_t){-1,-1};
    pj->tamanho_quad = calcula_tamanho(pj->janela);
    pj->restantes    = inicializa_restantes(pj->tabuleiro);
}

// ********** funcoes para recordes **********

// le os recordes de um arquibo recordes.txt e adiciona num array
void ler_recordes(int recordes[10]){
    FILE *fp = fopen("recordes.txt", "r");

    // se der erro ao abrir o arquivo, inicializa o array com 0 (todas as posições).
    if (fp == NULL){
        for (int i=0; i<10; i++) recordes[i] = 0;
        return;
    }
    // se conseguir ler, adiciona no array os recordes enquanto existirem
    for (int i=0; i<10; i++){
        if (fscanf(fp, "%d", &recordes[i]) != 1) recordes[i] = 0;
    }
    fclose(fp);
}

// gravar os recordes do array para o arquivo
void salvar_recorde(int recordes[10]){
    FILE *fp = fopen("recordes.txt", "w");
    if (fp == NULL){
        printf("Erro!");
        return;
    }
    // adiciona cada recorde salvo no array em um arquivo recordes.txt
    for (int i=0; i<10; i++){
        fprintf(fp, "%d\n", recordes[i]);
    }
    fclose(fp);
}

// atualiza o array com a pontuação atual, já em ordem crescente
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

// verifica se A e B sao vizinhas de linha
bool vizinhas_linha(int tabuleiro[LINHAS][COLUNAS], index_t clique_1, index_t clique_2){
    if (clique_1.i != clique_2.i || clique_1.j == clique_2.j) return false;
    // ve qual dos cliques vem "antes", para checar a linha
    int inicio = (clique_1.j < clique_2.j) ? clique_1.j : clique_2.j;
    int fim    = (clique_1.j > clique_2.j) ? clique_1.j : clique_2.j;
    
    for (int j=inicio+1; j<fim; j++){
        if (tabuleiro[clique_1.i][j] != 0) return false; //há uma casa ocupada entre elas
    } 
    return true;
}

// verifica se A e B sao vizinhas de coluna
bool vizinhas_coluna(int tabuleiro[LINHAS][COLUNAS], index_t clique_1, index_t clique_2){
    if (clique_1.j != clique_2.j || clique_1.i == clique_2.i) return false;

    int inicio = (clique_1.i < clique_2.i) ? clique_1.i : clique_2.i;
    int fim    = (clique_1.i > clique_2.i) ? clique_1.i : clique_2.i;

    for (int i = inicio + 1; i < fim; i++){
        if (tabuleiro[i][clique_1.j] != 0) return false; //ha casa ocupada entre elas
    } 
    return true;
}

// verifica se A e B sao vizinhas de diagonal
bool vizinhas_diagonal(int tabuleiro[LINHAS][COLUNAS], index_t clique_1, index_t clique_2){
    // calcula a diferença absoluta entre as coordenadas de linha dx e coluna dy
    int dx = abs(clique_1.i - clique_2.i);
    int dy = abs(clique_1.j - clique_2.j);
    if (dx != dy) return false;

    int di = clique_1.i < clique_2.i ? 1 : -1;
    int dj = clique_1.j < clique_2.j ? 1 : -1;
    int i = clique_1.i + di;
    int j = clique_1.j + dj;

    while (i!=clique_2.i && j!=clique_2.j){
        if (tabuleiro[i][j] != 0) return false; // há alguma casa ocupada entre elas
        i += di;
        j += dj;
    }
    return true;
}

// verifica se A e B sao vizinhas mas em linhas diferentes sem nenhuma casa ocupada entre elas
bool vizinhas_linha_seguinte(int tabuleiro[LINHAS][COLUNAS], index_t clique_1, index_t clique_2){
    if (clique_1.i > clique_2.i){
        index_t temp = clique_1;
        clique_1 = clique_2;
        clique_2 = temp;
    }

    if (clique_1.i + 1 != clique_2.i) return false;

    for (int j = 0; j < COLUNAS; j++){
        if (tabuleiro[clique_1.i+1][j] != 0) return false; // casa ocupada entre as duas linhas
    }

    return tabuleiro[clique_1.i][clique_1.j] != 0 && 
           tabuleiro[clique_2.i][clique_2.j] != 0 && 
           clique_1.j == clique_2.j;
}

// verifica se a primeira é vizinha da ultima
bool vizinhas_loop(jogo_t *pj, index_t clique_1, index_t clique_2){
    index_t ultima = clique_1.i == LINHAS - 1 ? clique_1 : clique_2;
    index_t primeira = clique_1.i == 0 ? clique_1 : clique_2;

    if (ultima.i != LINHAS-1 || primeira.i != 0) return false;

    int ultima_ocupada = -1, primeira_ocupada = -1;

    for (int j=0; j<COLUNAS; j++){
        if (pj->tabuleiro[ultima.i][j] != 0) ultima_ocupada = j;
        if (pj->tabuleiro[primeira.i][j] != 0 && primeira_ocupada == -1) primeira_ocupada=j;
    }

    return ultima_ocupada != -1 && primeira_ocupada != -1 &&
           ultima.j == ultima_ocupada && primeira.j == primeira_ocupada;
}

// retorna se alguma das condições é válida
bool sao_vizinhas(jogo_t *pj, index_t clique_1, index_t clique_2){
    return vizinhas_linha          (pj->tabuleiro, clique_1, clique_2) || 
           vizinhas_coluna         (pj->tabuleiro, clique_1, clique_2) || 
           vizinhas_diagonal       (pj->tabuleiro, clique_1, clique_2) ||
           vizinhas_linha_seguinte (pj->tabuleiro, clique_1, clique_2) || 
           vizinhas_loop           (pj, clique_1, clique_2);
}

// ********** processamento do mouse **********

// verifica se o mouse esta dentro da posição passada
// obs: funciona apenas para o caso do converte_clique()
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
    for (int i=0; i<9; i++){
        if (linha[i] != 0) return false;  
    } 
    return true;
}

// atualiza o array de vazias
void atualiza_vazias(jogo_t *pj){
    for (int i=0; i<LINHAS; i++){
        pj->linhas_vazias[i] = linha_vazia(pj->tabuleiro[i]) ? 1 : 0; // 1 para vazia, 0 para ocupada
    }
}

// apaga a linha e desloca as linhas acima para baixo
void atualizar_linhas(jogo_t *pj, int vazias_antes[LINHAS]){
    for (int i=0; i<LINHAS; i++){
        if (!vazias_antes[i] && linha_vazia(pj->tabuleiro[i])){   // verifica se a linha era vazia -> cheia
            // desloca as linhas de cima para baixo
            for (int j=i; j>0; j--){
                for (int k=0; k<COLUNAS; k++){
                    pj->tabuleiro[j][k] = pj->tabuleiro[j-1][k];
                }
            }

            // zera a linha superior
            for (int k=0; k<COLUNAS; k++){
                pj->tabuleiro[0][k] = 0;
            }
            pj->pontos += 109; // incremento de quando uma linha é esvaziada
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
    pj->tabuleiro[indice.i][indice.j] = 0;
    pj->tabuleiro[pj->selecionado.i][pj->selecionado.j] = 0;
    pj->pontos += 9;
    pj->restantes -= 2;
    desmarcar_selecao(pj);
    atualizar_linhas(pj, pj->linhas_vazias);
}

// verifica se é válida a combinação
bool valida_combinacao(jogo_t *pj, index_t indice){
    int valor1 = pj->tabuleiro[indice.i][indice.j];
    int valor2 = pj->tabuleiro[pj->selecionado.i][pj->selecionado.j];
    return (valor1 + valor2 == 10 || valor1 == valor2);
}

// processa quando uma casa já foi selecionada
void processa_selecao(jogo_t *pj, index_t indice){
    if (sao_vizinhas(pj, pj->selecionado, indice)){
        if (valida_combinacao(pj, indice)) realiza_combinacao(pj, indice);
        else {
            // printf("Vizinhas mas diferentes e somadas não é 10\n");
            desmarcar_selecao(pj);
        }
    } else {
        // printf("Não são vizinhas.\n");
        desmarcar_selecao(pj);
    }
}

void processa_clique(jogo_t *pj, index_t indice){
    if (pj->tabuleiro[indice.i][indice.j] != 0){
        if (pj->casa_selecionada) processa_selecao(pj, indice);
        else selecionar_casa(pj, indice);
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
void desenha_fundo(tamanho_t janela, retangulo_t fundo){
    fundo.inicio = (ponto_t){1,1};
    fundo.tamanho = (tamanho_t){janela.largura, janela.altura};
    j_retangulo(fundo, 0, preto, cinza);
}

// desenha um circulo na posição do cursor
void desenha_cursor(rato_t mouse, circulo_t cursor){
    cursor.centro = mouse.posicao;
    cursor.raio = 3;
    j_circulo(cursor, 1, preto, branco);
}

// desenha cada quadradinho com o seu conteúdo [vazio ou numero]
void desenha_quad(jogo_t *pj){
    pj->quad.tamanho = calcula_tamanho(pj->janela);
    pj->quad.inicio.x  = (pj->janela.largura/2) - (9*pj->quad.tamanho.largura)/2;
    pj->quad.inicio.y  = (pj->janela.altura/2)  - (12*pj->quad.tamanho.altura)/2;

    for (int i=0; i<12; i++){
        for (int j=0; j<9; j++){
            cor_t cor       = detecta_cor(pj->tabuleiro[i][j]);
            cor_t cor_txt   = branco;

            if (pj->casa_selecionada && pj->selecionado.i == i && pj->selecionado.j == j) {
                cor       = branco;
                cor_txt   = vermelho;
            }

            j_retangulo(pj->quad, 2, branco, cor);
            
            char num[100];
            sprintf(num, "%d", pj->tabuleiro[i][j]);
            ponto_t pos = (ponto_t){pj->quad.inicio.x + pj->quad.tamanho.largura/2, pj->quad.inicio.y + pj->quad.tamanho.altura/2};
            retangulo_t txt = j_texto_contorno(pos, 24, num); // cria um retangulo invisivel para descobrir a largura do txt e alinhar
            
            pos.x = (pj->quad.inicio.x + pj->quad.tamanho.largura/2) - txt.tamanho.largura/2;
            pos.y = (pj->quad.inicio.y + pj->quad.tamanho.altura/2)  + txt.tamanho.altura/2;
            if (pj->tabuleiro[i][j]!=0) j_texto(pos, 24, cor_txt, num);

            pj->quad.inicio.x += pj->quad.tamanho.largura;
        }
        pj->quad.inicio.x  = (pj->janela.largura/2) - (9*pj->quad.tamanho.largura)/2;
        pj->quad.inicio.y += pj->quad.tamanho.altura; 
    }
}

// arredonda as bordas de um retangulo
void arredonda(retangulo_t ret, bool jogadas_disp){
    circulo_t borda;
    cor_t cor;

    if (jogadas_disp == false) cor = vermelho;
    else cor = branco;

    if (ret.tamanho.largura > ret.tamanho.altura){
        
        borda.raio = ret.tamanho.altura/2;
        borda.centro = (ponto_t){ret.inicio.x, ret.inicio.y + (ret.tamanho.altura)/2};
        j_circulo(borda, 0, branco, cor);
        borda.centro = (ponto_t){ret.inicio.x + ret.tamanho.largura, ret.inicio.y + (ret.tamanho.altura)/2};
        j_circulo(borda, 0, branco, cor);
    } else {
        borda.raio = ret.tamanho.largura/2;
        borda.centro = (ponto_t){ret.inicio.x + (ret.tamanho.largura)/2, ret.inicio.y};
        j_circulo(borda, 0, branco, cor);
        borda.centro = (ponto_t){ret.inicio.x + (ret.tamanho.largura)/2, ret.inicio.y + ret.tamanho.altura};
        j_circulo(borda, 0, branco, cor);
    }
}

// desenha o botão de repovoamento
void desenha_repovoar(jogo_t *pj){
    ponto_t final = {pj->janela.largura, pj->janela.altura};
    cor_t cor_ret, cor_borda, cor_fundo;
    if (pj->jogadas_disponiveis == false){
        cor_ret = vermelho;
        cor_fundo = branco;
        cor_borda = vermelho;
    } else {
        cor_ret = branco;
        cor_fundo = vermelho;
        cor_borda = branco;
    }
    circulo_t add;
    add.raio = 25;
    add.centro = (ponto_t){final.x - MARGEM_LARGURA/4, final.y - MARGEM_ALTURA};
    j_circulo(add, 1, cor_borda, cor_fundo); 

    retangulo_t cross_x;
    cross_x.tamanho = (tamanho_t){(add.raio),6};
    cross_x.inicio  = (ponto_t){add.centro.x - (add.raio)/2, add.centro.y - (cross_x.tamanho.altura)/2};
    j_retangulo(cross_x, 0, preto, cor_ret);
    arredonda(cross_x, pj->jogadas_disponiveis);

    retangulo_t cross_y;
    cross_y.tamanho = (tamanho_t){6,(add.raio)};
    cross_y.inicio  = (ponto_t){add.centro.x - (cross_y.tamanho.largura)/2, add.centro.y - (add.raio)/2};
    j_retangulo(cross_y, 0, preto, cor_ret);
    arredonda(cross_y, pj->jogadas_disponiveis);

    // "hitbox" do botao circular (no caso é um retangulo)
    pj->repovoar.inicio  = (ponto_t){add.centro.x - add.raio, add.centro.y - add.raio};
    pj->repovoar.tamanho = (tamanho_t){add.raio*2, add.raio*2};
}

// desenha a pontuação atual do jogador
void desenha_pontos(int pontos){
    char txt[100];
    sprintf(txt, "%d", pontos);
    ponto_t pos = (ponto_t){10, 30};
    j_texto(pos, 24, branco, txt);
}

// desenha a interface completa
void desenha_interface(jogo_t *pj){
    // esc para desistir txt
    char txt[100];
    sprintf(txt, "ESC para desistir");
    retangulo_t alinhar = j_texto_contorno((ponto_t){1,1}, 20, txt);
    ponto_t pos = (ponto_t){pj->janela.largura/2 - alinhar.tamanho.largura/2, alinhar.tamanho.altura};
 
    desenha_fundo(pj->janela, pj->fundo);
    desenha_pontos(pj->pontos);
    desenha_repovoar(pj);
    j_texto(pos, 20, vermelho, txt);
}

// ve se a pontuação é maior que o ultimo recorde
bool pontuacao_entra(int pontos, int recordes[10]){
    if (pontos >= recordes[9]) return true;
    return false;
}

void desenha_mensagem_final(jogo_t *pj){
    char txt[100];
    ponto_t pos = {1,40};
    if (pj->status == -1){
        sprintf(txt, "Desistiu");
        j_texto(pos, 40, vermelho, txt);
    } else if (pj->status == -2){
        sprintf(txt, "Perdeu");
        j_texto(pos, 40, vermelho, txt);
    } else if (pj->status == 1){
        sprintf(txt, "Parabéns! %d pts", pj->pontos);
        j_texto(pos, 40, verde, txt);       
        pos.y += 50;
        if (pontuacao_entra(pj->pontos, pj->recordes) == true){
            sprintf(txt, "Sua pontuação entra nos recordes!");
            j_texto(pos, 40, verde, txt);  
        } else {
            sprintf(txt, "Sua pontuação não entra nos recordes!");
            j_texto(pos, 40, vermelho, txt);  
        }
    }
}

void desenha_tela_final(jogo_t *pj){
    desenha_fundo(pj->janela, pj->fundo);
    char txt[100];
    ponto_t pos;

    // metade da esquerda
    pj->half.inicio  = (ponto_t){1,1};
    pj->half.tamanho = (tamanho_t){pj->janela.largura/2, pj->janela.altura};
    j_retangulo(pj->half, 0, preto, cinza);
    sprintf(txt, "Ver Recordes ");
    retangulo_t contorno = j_texto_contorno((ponto_t){1,1}, 40, txt);
    pos = (ponto_t){pj->half.tamanho.largura/2 - contorno.tamanho.largura/2, pj->half.tamanho.altura/2 + 40};
    j_texto(pos, 40, branco, txt);

    // metade da direita
    pj->half.inicio  = (ponto_t){pj->janela.largura/2,1};
    pj->half.tamanho = (tamanho_t){pj->janela.largura/2, pj->janela.altura};
    j_retangulo(pj->half, 0, preto, branco);
    sprintf(txt, "Sair ");
    contorno = j_texto_contorno((ponto_t){1,1}, 40, txt);
    pos = (ponto_t){pj->half.inicio.x + pj->half.tamanho.largura/2 - contorno.tamanho.largura/2, pj->half.tamanho.altura/2 + 40};
    j_texto(pos, 40, cinza, txt);
}

int processa_tela_final(rato_t mouse, tamanho_t janela){
    if (mouse.clicado[0]){
        if (mouse.posicao.x >= 1 && 
            mouse.posicao.x <= janela.largura/2 && 
            mouse.posicao.y >= 1 
            && mouse.posicao.y <= janela.altura){
                printf("0 esquerda\n");
                return 0; // esquerda
            } 
        else if (mouse.posicao.x > janela.largura/2 &&
            mouse.posicao.x <= janela.largura  &&
            mouse.posicao.y >= 1 && 
            mouse.posicao.y <= janela.altura){
            printf("1 direita\n");
            return 1; // direita
            }
    }
    return -1; 
}

// tela com os recordes dos jogadores
void desenha_recordes(jogo_t *pj){
    desenha_fundo(pj->janela, pj->fundo);
    ponto_t pos_inicial = (ponto_t){1, 40};
    char txt[100];
    for (int i=0; i<10; i++){
        sprintf(txt, "%d: %d pontos.", i+1, pj->recordes[i]);
        j_texto(pos_inicial, 20, branco, txt);
        pos_inicial.y += 30;
    }
    sprintf(txt, "Clique para voltar.");
    pos_inicial.y = pj->janela.altura - 40;
    j_texto(pos_inicial, 40, vermelho, txt);
}

void processa_mouse(jogo_t *pj){
    if (pj->mouse.clicado[0]){
        index_t indice = converte_clique(pj);
        if (indice.i>=0 && indice.i<LINHAS && indice.j>=0 && indice.j<COLUNAS) processa_clique(pj, indice);
    }
}

// ********** passando arquivo **********

// modifiquei a funcao para ler os . mas converter para 0, pois meu tabuleiro é de int
bool verifica_args(int nl, int nc, int tab[nl][nc], int argc, char *argv[]){
    if (argc != 2) return false;
    char *nome = argv[1];
    FILE *arq = fopen(nome, "r");
    if (arq == NULL) return false;
    bool consegui_ler = true;
    for (int l = 0; l < nl; l++){
        for (int c = 0; c < nc; c++){
            char val;
            if (fscanf(arq, " %c", &val) == 1){
                if (val == '.') tab[l][c] = 0; 
                else if (val >= '1' && val<='9')tab[l][c] = val - '0'; 
                else {
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

// ********** repovoa **********
void repovoar(jogo_t *pj){

    int ocupadas[LINHAS * COLUNAS], livres[LINHAS * COLUNAS];   
    int ocupadas_cont = 0, livres_cont = 0;
    int primeiro_encontrado = 0;

    // procura o primeiro número diferente de 0 e as casas livres antes dele
    for (int lin=0; lin<LINHAS && !primeiro_encontrado; lin++){
        for (int col=0; col<COLUNAS && !primeiro_encontrado; col++){
            if (pj->tabuleiro[lin][col] != 0){
                primeiro_encontrado = 1; 
                break;
            }
            livres[livres_cont++] = lin * COLUNAS + col;
        }
    }

    if (livres_cont < pj->restantes){
        printf("nao ha espaço\n");
        return;
    }

    for (int lin=0; lin<LINHAS; lin++){
        for (int col=0; col<COLUNAS; col++){
            if (pj->tabuleiro[lin][col] != 0) ocupadas[ocupadas_cont++] = pj->tabuleiro[lin][col];
        }
    }

    for (int i = 0; i < ocupadas_cont; i++){
        int idx_livre = livres[livres_cont-1-i];
        int lin = idx_livre / COLUNAS;
        int col = idx_livre % COLUNAS;
        pj->tabuleiro[lin][col] = ocupadas[ocupadas_cont-1-i];
    }
    pj->restantes = pj->restantes * 2; // atualiza o numero de casas ocupadas
}

// retorna true se o clique foi feito na area do botao repovoar
bool clique_repovoar(jogo_t *pj){
    if (pj->mouse.clicado[0]){
        if (pj->mouse.posicao.x >= pj->repovoar.inicio.x                                &&
            pj->mouse.posicao.x <= pj->repovoar.inicio.x + pj->repovoar.tamanho.largura &&
            pj->mouse.posicao.y >= pj->repovoar.inicio.y                                &&
            pj->mouse.posicao.y <= pj->repovoar.inicio.y + pj->repovoar.tamanho.altura){
                printf("repovoa\n");
                return true;
        } else return false;
    }
    return false;
}

// ********** modularizando a main **********

// verifica se o jogo acabou
bool jogo_acabou(jogo_t *pj){
    if (pj->restantes == 0){
        pj->status = 1;
        return true;
    } else if (j_tecla() == 27){
        pj->status = -1;
        return true;
    } else if (pj->status == -2){
        printf("perdeu\n");
        return true;
    }
    return false;
}

// funções de inicialização
void inicializar_sistema(jogo_t *jogo, int argc, char *argv[]){
    if (!verifica_args(12, 9, jogo->tabuleiro, argc, argv)){
        inicializa_matriz(jogo->tabuleiro);
    }
    inicializa_jogo(jogo);
    ler_recordes(jogo->recordes);
    t_inicializa(jogo->janela, "Numbers");
}


void jogadas_disponiveis(jogo_t *pj){
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++){
            if (pj->tabuleiro[i][j] == 0) continue; // casas vazias

            for (int k=0; k<LINHAS; k++){
                for (int l=0; l<COLUNAS; l++){
                    if ((i==k && j==l) || pj->tabuleiro[k][l] == 0) continue; // mesma casa ou vazia

                    int num1 = pj->tabuleiro[i][j];
                    int num2 = pj->tabuleiro[k][l];

                    if ((num1==num2 || num1+num2 == 10)){
                        index_t clique_1 = {i, j};
                        index_t clique_2 = {k, l};

                        if (sao_vizinhas(pj, clique_1, clique_2)){
                            // printf("ha jogadas disponiveis\n");
                            pj->jogadas_disponiveis = true;
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("nao ha jogadas, repovoe\n");
    pj->jogadas_disponiveis = false;
    return;
}


// loop principal do jogo
void executar_jogo(jogo_t *jogo){
    while (!jogo_acabou(jogo)){
        atualiza_vazias(jogo);
        jogadas_disponiveis(jogo);
        jogo->mouse = j_rato();
        if (clique_repovoar(jogo)) repovoar(jogo);
        desenha_interface(jogo);
        desenha_quad(jogo);
        desenha_cursor(jogo->mouse, jogo->cursor);
        processa_mouse(jogo);
        j_atualiza();
    }
    // só salva o recorde se o jogador ganhou
    if (jogo->status == 1){
        atualizar_recorde(jogo->recordes, jogo->pontos);
        salvar_recorde(jogo->recordes);
    }
}

// loop que fica mostrando os recordes
void exibir_recordes(jogo_t *jogo){
    while (true){
        jogo->mouse = j_rato();
        desenha_recordes(jogo);
        j_atualiza();
        if (jogo->mouse.clicado[0]){
            break;
        }
    }
}

// loop da tela final
void finalizar_jogo(jogo_t *jogo){
    while (true){
        jogo->mouse = j_rato();
        desenha_tela_final(jogo);
        desenha_mensagem_final(jogo);
        desenha_cursor(jogo->mouse, jogo->cursor);
        j_atualiza();

        int retorno = processa_tela_final(jogo->mouse, jogo->janela);
        if (retorno == 1){
            break;
        } else if (retorno == 0){
            exibir_recordes(jogo);
        }
    }

    j_finaliza();
}

int main(int argc, char *argv[]){
    jogo_t jogo;

    inicializar_sistema(&jogo, argc, argv); // funções de inicialização
    atualiza_vazias(&jogo);// inicializa o array das casas vazias
    executar_jogo(&jogo);  // loop principal do jogo
    finalizar_jogo(&jogo); // loop da tela final

    return 0;
}