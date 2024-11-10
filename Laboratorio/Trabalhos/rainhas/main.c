#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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

bool verifica_linha(int tamanho, char str[tamanho]){
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

bool verifica_coluna(int tamanho, char str[tamanho]){
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

// Basicamente separei em quatro partes:
// Coluna 1 ↘   última coluna ↙
// Assim todas as diagonais são verificadas.
int verifica_diagonal(int tamanho, char str[tamanho]){
    int i, j;
    int quant_rainhas=0;
    int lado=floorSqrt(tamanho);

    int skip_baixo = floorSqrt(tamanho) + 1; //quantas linhas pular para checar a diagonal
    int skip_cima = floorSqrt(tamanho) - 1; //quantas linhas voltar para checar a diagonal
    
    // Coluna 1 -> 
    for (i=0; i<tamanho; i=i+4){ // muda a o item inicial da coluna
        quant_rainhas = 0;
        for (j=i; j<tamanho; j=j+skip_baixo){ // percorre a diagonal (direita baixo) do item inicial
            if (str[j]==RAINHA) quant_rainhas = quant_rainhas + 1;
        } 
        // printf("\n ⬊ [%d] quant_rainhas", quant_rainhas);
        // if (quant_rainhas <= 0) return 0;
        // else if (quant_rainhas>1) return 2;

        quant_rainhas = 0;
        for (j=i; j>=0; j=j-skip_cima){ // percorre a diagonal (direita cima) do item inicial
            if (str[j]==RAINHA) quant_rainhas = quant_rainhas + 1;
        }
        printf("\n ⬈ [%d] quant_rainhas", quant_rainhas);
        // if (quant_rainhas <= 0) return 0;
        // else return 2;
    }
    
    // Última Coluna
    int pos_inicial = floorSqrt(tamanho) - 1; // deixei com nomes diferentes apesar de ter o mesmo valor para facilitar a leitura
    skip_baixo = floorSqrt(tamanho) - 1;
    skip_cima = floorSqrt(tamanho) + 1;
    for (i=pos_inicial; i<tamanho; i++){ // muda o item da coluna
        for (j=i; j<tamanho; j=j+skip_baixo){
            if (str[j] == RAINHA) quant_rainhas = quant_rainhas + 1;
        }
        if (quant_rainhas <= 0) return 0;
        else if (quant_rainhas == 1) return 1;
        else return 2;

        quant_rainhas = 0;
        for (j=pos_inicial; j>=0; j=j-skip_cima){
            if (str[i] == RAINHA) quant_rainhas = quant_rainhas + 1;
        }
        if (quant_rainhas <= 0) return 0;
        else if (quant_rainhas == 1) return 1;
        else return 2;
    }
}

bool par(int tamanho){
    if (tamanho%2==0) return true;
    else return false ;
}

void desenha_tabuleiro(int tamanho, char str[tamanho]){
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

void limpar_buffer(){
    while (getchar() != '\n');
}
int main(){
    int lado;
    printf("Digite o tamanho do tabuleiro (exemplo: 4 => tabuleiro 4x4): ");
    scanf("%d", &lado);

    int tamanho=lado*lado; 
    char str[tamanho];

    printf("Como iniciar o tabuleiro?\n0: Tabuleiro Vazio\t1: Inserir Tabuleiro Inicial\t2: Tabuleiro Aleatório\nResposta: ");
    int option;
    scanf("%d", &option);
    limpar_buffer();
    if (option == 0){
        int i;
        for (i=0; i<tamanho; i++) {
            str[i] = ' ';
        }
    } else if (option == 1){
        int i;
        printf("Qualquer caractere diferente de %c e ' ' será ignorado...\n", RAINHA);
        for (i=0; i<tamanho; i++){
            do{
                scanf("%c", &str[i]);
            }while(str[i]!=' ' && str[i]!=RAINHA);
        }
    } else if (option == 2){
        srand(time(0));
        int i;
        for (i=0; i<tamanho; i++){
            if (rand()%2 == 0) str[i] = ' ';
            else str[i] = RAINHA;            
        }
    }
    
    printf("\nTabuleiro:");
    int i;
    for (i=0; i<tamanho; i++){
        if (i%floorSqrt(tamanho)==0) printf("\n");
        printf("%c", str[i]);
    }
    printf("\n");
}
