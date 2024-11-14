// l1-t2 Miguel Avila de Oliveira
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define RAINHA 'Q'
#define ESPACO_BRANCO ' '

int sqrt(int x){
    if (x == 0 || x == 1)
        return x;
    int i = 1, result = 1;
    while (result <= x) {
        i++;
        result = i * i;
    }
    return i - 1;
}

bool verifica_linha(int tamanho, char str[tamanho]){
    int lin, col, cont;
    int lado = sqrt(tamanho);

    for (lin=1; lin<=lado; lin++){
        for (col=1; col<lado; col++){
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++; 
        }
        if (cont > 1) return false;
    }
}

bool verifica_coluna(int tamanho, char str[tamanho]){
    int lin, col, cont;
    int lado = sqrt(tamanho);

    for (col=1; col<=lado; col++){
        for (lin=1; lin<lado; lin++){
            int indice = (lin-1)*lado + (col-1);
            if (str[indice] == RAINHA) cont++; 
        }
        if (cont > 1) return false;
    }
}

bool verifica_diagonal(int tamanho, char str[tamanho]){
    int lin, col, cont;
    int lado = sqrt(tamanho);

    int indice = (lin-1)*lado + (col-1);
    
    for (lin=1; lin<lado; lin++){
        
        for (col=1; col<lado; col++){

        }
    }
}
