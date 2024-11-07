#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// peguei esse codigo aqui -> https://www.geeksforgeeks.org/square-root-of-an-integer/
int floorSqrt(int x){
    // Base cases
    if (x == 0 || x == 1)
        return x;

    // Starting from 1, try all numbers until
    // i*i is greater than or equal to x.
    int i = 1, result = 1;
    while (result <= x) {
        i++;
        result = i * i;
    }
    return i - 1;
}

bool verifica_linha(int tamanho, char str[16]){
    int i, aux=0, cont=0;
    
    for (i=0; i<tamanho; i++){
        // conta as rainhas por linha
        if (str[i] == 'X') cont = cont + 1;
        
        // conta quantos quadrados foram verificados
        aux = aux + 1;
        // analisa as informações acima
        if (aux == 4){
            if (cont == 1) printf("Linha Ok!\n");
            else if (cont == 0) {
                printf("Nenhuma rainha na linha!\n");
                return false;
            }
            else if (cont > 1) {
                printf("Mais de uma rainha na linha!\n");
                return false;
            }
            aux = 0;
            cont = 0;
        }
    }
    return true;
}

bool verifica_coluna(int tamanho, char str[16]){
    int i, j, aux=0, cont=0, quant=0;

    // percorre o array em colunas
    for (i=0; i<4;i++){
        aux = i;
        for (j=0; j<4; j++){
            // printf("i:[%d], j:[%d], aux:[%d]\n", i, j, aux);

            // conta as rainhas por coluna
            if (str[aux] == 'X') cont = cont + 1;
            quant = quant + 1;

            // verifica os dados
            if (quant == 4){
                if (cont == 1) printf("Coluna Ok\n");
                else if (cont == 0){
                    printf("Nenhuma rainha na coluna\n");
                    return false;
                } else if (cont > 1){
                    printf("Mais de uma rainha na coluna\n");
                }
                cont = 0;
                quant = 0;
            }
            aux = aux + 4;
        }
    }
}

bool verifica_diagonal(int tamanho, char str[16]){

}

bool par(int tamanho){
    if (tamanho%2==0) return true;
    else return false ;
}

void desenha_tabuleiro(int tamanho, char str[16]){
    int i, cont=0, aux=0;

    for (i=0; i<tamanho; i++){
        
        if (i % floorSqrt(tamanho) == 0){
            t_cor_normal();
            printf("\n");
            if (par(tamanho)==true) aux = aux + 1;
        }


        if (aux%2 == 1) t_cor_fundo(255, 255, 255);
        else t_cor_fundo(0, 0, 0);

        printf("%c", str[i]);
        
        aux = aux + 1;
    }
    t_cor_normal();
    printf("\n\n");

}

void n_rainhas(int tamanho, char str[]){

    if(verifica_linha(tamanho, str) && verifica_coluna(tamanho, str)){ // && verifica_diagonal(tamanho, str)
        printf("Tabuleiro aceito! \n");
        desenha_tabuleiro(tamanho, str);
    } else {
        printf("Tabuleiro não aceito! \n");
        desenha_tabuleiro(tamanho, str);
    }

}

int main(){
    int i;
    char str[i];

    for (i=0; i<100; i++){
        if (rand()%2==0) str[i] = '.';
        else str[i] = 'Q';
    }

    for (i=0; i<5; i++){
        printf("tamanho: %dx%d\n", i, i);
        desenha_tabuleiro(i*i, str);
    }

}
