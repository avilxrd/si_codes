/*as funcoes nao manipulam pilhas de verdade, mas sim vetores,
porem o nome vai ser pilhas.c/pilhas.h para facilitar as coisas*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define CARTAS_BARALHO 52
#define NUM_FINAIS 4
#define NUM_PILHAS 7
#define MAX_CARTAS 13

typedef struct Carta{
    int naipe;
    int valor;
    bool visivel;
}Carta;

extern char lista_de_naipes[4][100];
extern Carta carta_vazia;   

// ======================================= //
// ======= funcoes gerais do jogo ======== //

//apaga tudo que esta no terminal
void limpaTela();

//muda a cor dos proximos caracteres
void mudaCor(int cor);

//troca duas cartas
void trocarCartas(Carta *a, Carta *b);

bool movimento_valido(Carta origem, Carta destino, bool finais);

// ======================================= //
// === funcoes relacionadas a "pilhas" === //

void mostraCartas(Carta pilha[], int tamanho);

bool pilhaVazia(Carta *pilha, int tamanho);

//distribui as cartas do baralhos em pilhas de acordo com a regra do paciencia
void distribuiCartas(Carta *baralho, Carta pilhas[7][13], int *tamanho_pilha);

//retorna quantas cartas uma pilha possui
int quantidadePilha(Carta pilha[], int tamanho);

//inicializa uma pilha de cartas com todas as cartas vazias
void inicializaPilhas(Carta pilha[], int tamanhoPilha);

//printa o layout das pilhas no jogo
void mostraPilhas(int quantidade, Carta pilhas[quantidade][13], bool mostrarZeros);

//retorna o indice da carta do topo diferente de 0 de uma pilha
int cartaTopo(Carta pilha[]);

//revela uma carta
void revelaCarta(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int pilha, int carta);

int quantasVisiveis(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int indexPilha);

int primeiraVisivel(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int indexPilha);

int ultimaVisivel(Carta pilha[], int tamanho);


// ======================================= //
// === funcoes relacionadas ao baralho === //

//preenche o baralho com todas as cartas possiveis
void preencheBaralho(Carta *baralho);

//embaralha o baralho
void embaralharBaralho(Carta *baralho);

// 
void removerBaralho(Carta *baralho, Carta removida);

void restitui_baralho(Carta baralho[], Carta deposito[]);

// ======================================= //
// === funcoes de manipulacao de cartas == //

int moveCartas(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int pilhaOrigem, int cartaMover, int pilhaDestino);

void compraCarta(Carta baralho[], Carta deposito[]);

int moveDeposito(Carta deposito[], Carta pilhaDestino[]);

void mostraDeposito(Carta deposito[], Carta baralho[]);

// ======================================= //
// ===== funcoes de selecao de cartas ==== //

int selecionarCarta(int pilhaOrigem, Carta pilhas[NUM_PILHAS][MAX_CARTAS]);

int selecionarDestino();

int pedeInstrucoes(Carta pilhas[NUM_PILHAS][MAX_CARTAS], Carta *baralho, Carta *descarte);