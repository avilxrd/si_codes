// l1-t2 Miguel Avila de Oliveira
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define RAINHA 'Q'
#define ESPACO_BRANCO ' '

void limpar_buffer(){
    while (getchar() != '\n');
}

// peguei esse codigo aqui -> https://www.geeksforgeeks.org/square-root-of-an-integer/
// faz a raiz inteira de um numero
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
// retorna o estado do tabuleiro (0: incompleto, 1: completo, 2: conflito)
int jogo_rainhas(int lado, char str[]){
    int i, rainhas=0;

    for (i=0; i<lado*lado; i++){
        if (str[i]==RAINHA) rainhas++;
    }

    if (!verifica_linha(lado, str) || !verifica_coluna(lado, str) || !verifica_diagonal(lado, str)) return 2; // 2 -> incorreto
    else {
        if (rainhas<lado) return 0; // 0 -> incompleto
        else return 1; // 1 -> completo
    }
}
// seta a cor da borda dependendo do status
void cor_borda(int cor){
    if (cor == 0) t_cor_fundo(255, 255, 0); // incompleto -> amarelo
    else if (cor == 1) t_cor_fundo(0, 255, 0); // correto -> verde
    else t_cor_fundo(255, 0, 0); // incorreto -> vermelho
}
// printa uma linha de espaços brancos com fundo da cor do estado do tabuleiro
void borda(int lado, int cor){
    int i;
    cor_borda(cor);
    for (i=0; i<lado+2; i++){
        printf(" %c ", ESPACO_BRANCO);
    }
}
// desenha o tabuleiro com a borda
void desenha_tabuleiro(int lado, char str[], int lin, int col, long start /*tempo inicial*/, bool inicio /*desenhar no inicio do terminal*/){
    int i, j;
    int posicao_destacada = (lin-1)*lado + (col-1);
    int cor = jogo_rainhas(lado, str);
    
    if (inicio == 1) t_lincol(1,1); // se o parametro inicio for true, o desenho será feito no inicio do terminal, caso contrario, onde houver espaço
    if (start!=0) printf("Tempo %ld \n", time(NULL)-start); // se start for 0, nao printar o tempo, caso contrario, sim
    // borda superior
    borda(lado, cor);
    for (i=0; i<lado; i++){
        t_cor_normal();
        printf("\n");
        for(j=0; j<lado; j++){
            // borda lateral
            if(j==0){
                cor_borda(cor);
                printf(" %c ", ESPACO_BRANCO);
            }

            int indice = i*lado + j;  
            if (indice == posicao_destacada){
                t_cor_letra(255, 255, 255);
                t_cor_fundo(190, 149, 196);
            } else if ((i+j)%2==0){
                t_cor_letra(255, 255, 255);
                t_cor_fundo(0, 0, 0);
            } else {
                t_cor_letra(0, 0, 0);
                t_cor_fundo(255, 255, 255);
            }
            if (str[indice] == RAINHA) printf(" # ");
            else printf(" %c ", ESPACO_BRANCO);
            
            // borda lateral
            if(j==lado-1){
                cor_borda(cor);
                printf(" %c ", ESPACO_BRANCO);
            }
        }
    }
    // borda inferior
    t_cor_normal();
    printf("\n");
    borda(lado, cor);
    t_cor_normal();
    printf("\n");
}
// atribui uma funcionalidade para cada tecla apertada
bool processa_entrada(int lado, char str[], int *ref_lin, int *ref_col){
    if (!t_tem_tecla()) return false;

    char option = t_tecla();
    switch(option){
        case 'X':
        case 'x': return true;
        
        case 'W':
        case 'w':
            //ref_lin igual a (se ref_lin for maior que 1) ref_lin-1 : senao igual a ref_lin+lado-1
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
// mensagem final dependendo de como o programa foi encerrado
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
// lógica principal do jogo
void main(){
    int i;
    int lado;
    printf("Qual o tamanho do tabuleiro? (ex. 4 => 4x4): ");
    scanf("%d", &lado);
    limpar_buffer();

    int tamanho = lado*lado;
    char str[tamanho];
    for (i=0; i<tamanho; i++){
        str[i] = ESPACO_BRANCO;
    }

    time_t start = time(NULL), end;
    int lin=1, col=1;
    int status;

    t_inicializa();
    while(true){
        
        if (jogo_rainhas(lado, str)==1){
            end = time(NULL);
            status = 1;
            break;
        } 
        
        if (processa_entrada(lado, str, &lin, &col)){
            end = time(NULL);
            status = 0;
            break;
        } else {
            t_limpa();
            desenha_tabuleiro(lado, str, lin, col, start, 1);
            t_atualiza();
        }
    }
    t_finaliza();
    t_limpa();
    t_lincol(1,1);
    mensagem_final(status, end-start);
    desenha_tabuleiro(lado, str, 0 /*linha*/, 0 /*coluna*/, 0/*start*/, 0/*inicio*/); //deixei com 0 pois nao precisa neste caso.
}