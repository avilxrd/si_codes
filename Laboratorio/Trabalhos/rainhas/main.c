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

bool verifica_linha(int tamanho, char str[]){
    int lin, col, cont;
    int lado = floorSqrt(tamanho);

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

bool verifica_coluna(int tamanho, char str[]){
    int lin, col, cont;
    int lado = floorSqrt(tamanho);

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

// bool verifica_diagonal(int tamanho, char str[]){
//     int lin, col, i, cont;
//     int lado = floorSqrt(tamanho);
    
//     for (i=1; i<=lado; i++){
//         cont = 0;
//         for (lin=1, col=i; lin<=lado && col<=lado; lin++, col++){
//             int indice = (lin-1)*lado + (col-1);
//             if (str[indice] == RAINHA) cont++;
//         }
//         if (cont > 1) return false; 
//     }

//     for (i=2; i<=lado; i++){
//         cont = 0;
//         for (lin=i, col=1; lin<=lado && col<=lado; lin++, col++){
//             int indice = (lin-1)*lado + (col-1);
//             if (str[indice] == RAINHA) cont++;
//         }
//         if (cont > 1) return false; 
//     }
    
//     // <-
//     for (i=1; i<=lado; i++){
//         cont = 0;
//         for (lin=1, col=i; lin>=1 && col<=lado; lin--, col++){
//             int indice = (lin-1)*lado + (col-1);
//             if (str[indice] == RAINHA) cont++;
//         }
//         if (cont > 1) return false; 
//     }

//     for (i=2; i<=lado; i++){
//         cont = 0;
//         for (lin=lado, col=i; lin>=1 && col<=lado; lin--, col++){
//             int indice = (lin-1)*lado + (col-1);
//             if (str[indice] == RAINHA) cont++;
//         }
//         if (cont > 1) return false; 
//     }
//     return true;
// }

bool verifica_diagonal(int tamanho, char str[]) {
    int lin, col, cont;
    int lado = floorSqrt(tamanho);

    // Diagonais principais (esquerda para direita, do topo esquerdo ao canto inferior direito)
    for (int start_col = 1; start_col <= lado; start_col++) { 
        cont = 0;
        lin = 1;
        col = start_col;

        while (lin <= lado && col <= lado) { 
            int indice = (lin - 1) * lado + (col - 1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col++;
        }

        if (cont > 1) return false; 
    }

    for (int start_row = 2; start_row <= lado; start_row++) { 
        cont = 0;
        lin = start_row;
        col = 1;

        while (lin <= lado && col <= lado) { 
            int indice = (lin - 1) * lado + (col - 1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col++;
        }

        if (cont > 1) return false; 
    }

    // Diagonais secundárias (direita para esquerda, do topo direito ao canto inferior esquerdo)
    for (int start_col = 1; start_col <= lado; start_col++) {
        cont = 0;
        lin = 1;
        col = start_col;

        while (lin <= lado && col >= 1) { 
            int indice = (lin - 1) * lado + (col - 1);
            if (str[indice] == RAINHA) cont++;
            lin++;
            col--;
        }

        if (cont > 1) return false; 
    }

    for (int start_row = 2; start_row <= lado; start_row++) {
        cont = 0;
        lin = start_row;
        col = lado;

        while (lin <= lado && col >= 1) { 
            int indice = (lin - 1) * lado + (col - 1);
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

void cor_borda(int cor){
    if (cor == 0) t_cor_fundo(255, 255, 0); // incompleto -> amarelo
    else if (cor == 1) t_cor_fundo(0, 255, 0); // correto -> verde
    else t_cor_fundo(255, 0, 0); // incorreto -> vermelho
}

void borda(int lado, int cor){
    int i;
    cor_borda(cor);
    for (i=0; i<lado+4; i++){
        printf("%c", ESPACO_BRANCO);
    }
}

void desenha_tabuleiro(int tamanho, char str[], int lin, int col, long start, bool inicio){
    int i, j;
    int lado = floorSqrt(tamanho);
    int posicao_destacada = (lin-1)*lado + (col-1);
    int cor = jogo_rainhas(tamanho, str);
    
    if (inicio == 1) t_lincol(1,1);
    if (start!=0) printf("Tempo %ld \n", time(NULL)-start);
    // borda superior
    borda(lado, cor);

    for (i=0; i<lado; i++){
        t_cor_normal();
        printf("\n");
        for(j=0; j<lado; j++){
            // borda lateral
            if(j==0){
                cor_borda(cor);
                printf("%c%c", ESPACO_BRANCO, ESPACO_BRANCO);
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
            printf("%c", str[indice]);
            // borda lateral
            if(j==lado-1){
                cor_borda(cor);
                printf("%c%c", ESPACO_BRANCO, ESPACO_BRANCO);
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

bool processa_entrada(int tamanho, char str[], int *ref_lin, int *ref_col){
    int lado = floorSqrt(tamanho);
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

void end_status(int status, long tempo){
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

    time_t start = time(NULL);
    int lin=1, col=1;
    int status;

    t_inicializa();
    while(true){
        
        if (jogo_rainhas(tamanho, str)==1){
            status = 1;
            break;
        } 
        
        if (processa_entrada(tamanho, str, &lin, &col)){
            status = 0;
            break;
        } else {
            t_limpa();
            desenha_tabuleiro(tamanho, str, lin, col, start, 1);
            t_atualiza();
        }
    }
    t_finaliza();
    t_limpa();
    t_lincol(1,1);
    end_status(status, time(NULL)-start);
    desenha_tabuleiro(tamanho, str, 0, 0, 0, 0);
}