#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool verifica_linha(int tamanho, char str[16]){
    int i, cont=0;
    
    for (i=1; i<tamanho+1; i++){

        if (str[i] == 'X'){
            cont = cont + 1;
        }
        if (i%4==0){
            if (cont == 0){
                printf("Nenhuma Rainha na linha.\n");
                return false;
            } else if (cont > 1){
                printf("Mais de uma Rainha na linha.\n");
                return false;
            } else if (cont == 1){
                printf("Ok.\n");
                break;
            }
            cont = 0;
        }
    }
    return true;
}

bool verifica_coluna(int tamanho, char str[16]){
    int i, j, cont=0;

    for (i=0; i<4; i++){
        j = i;
        for (j; j<4; j+4){
            if(str[j] == 'X') cont = cont + 1;
        }

        if (cont == 0){
            printf("Nenhuma Rainha na coluna.\n");
            return false;
        } else if (cont > 1){
            printf("Mais de uma Rainha na coluna.\n");
            return false;
        } else if (cont == 1){
            printf("Ok\n");
        }
    }
    return true;
}

int main(){
    int tamanho = 17;
    char str[17] = ".X.....XX.....X.";

    verifica_linha(tamanho, str);
    // verifica_coluna(tamanho, str);

}
