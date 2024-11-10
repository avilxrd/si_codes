#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RAINHA 'Q'

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
        if (str[i] == RAINHA) cont = cont + 1;
        
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
            if (str[aux] == RAINHA) cont = cont + 1;
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

void checa_rainhas(int quant_rainhas){
    if (quant_rainhas == 0){
            printf("Nenhuma Rainha!");
            return false;
        } else if (quant_rainhas > 1){
            printf("Mais de uma Rainha!");
            return false;
        }  else if (quant_rainhas == 1){
            printf("Ok!");
            quant_rainhas = 0;
        }
}
// Basicamente separei em quatro partes:
// Coluna 1 ↘   Linha 1 ↘   Linha 1 ↙   Coluna última ↙
// Assim todas as diagonais são verificadas.
bool verifica_diagonal(int tamanho, char str[16]){
    int i, j, quant_rainhas=0;
    int skip = floorSqrt(tamanho) + 1; //quantas linhas pular para checar a diagonal

    // Coluna 1 ↘
    // Primeiro laço muda a o item inicial da coluna
    for (i=0; i<tamanho; i=i+4){
        // Segundo laço percorre a diagonal (direita baixo) do item inicial
        for (j=i; j<tamanho; j=j+skip){
            if (str[j]==RAINHA) quant_rainhas = quant_rainhas + 1;
        }   
    }
    // Linha 1 ↘
    for (i=0; i<tamanho; i++){
        for (j=i; j<tamanho; j=j+skip){
            if (str[j]==RAINHA) quant_rainhas = quant_rainhas + 1;
        }
    }

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
    } else {
        printf("Tabuleiro não aceito! \n");
    }

}

int main(){
    char str[16] = "...Q.Q..Q.....Q.";

    // GERA UMA STRING ALEATORIA COM ('.' OU 'Q')
    // for (i=0; i<100; i++){
    //     if (rand()%2==0) str[i] = '.';
    //     else str[i] = RAINHA;
    // }

    // CHAMA 5 TABULEIROS COM TAMANHOS 1 - 5
    // for (i=0; i<5; i++){
    //     printf("tamanho: %dx%d\n", i, i);
    //     desenha_tabuleiro(i*i, str);
    // }

    verifica_diagonal(16, str);

}
