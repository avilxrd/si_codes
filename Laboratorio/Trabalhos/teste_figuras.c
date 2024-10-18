#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void linha(int tamanho, char caractere){    
    int i;
    for(i=0; i<tamanho; i++){
        printf("%c", caractere);
    }
} 

void figura_a(int tamanho, char caractere){
    int i;
    for (i=1; i<=tamanho; i++){
        linha(i, caractere);
        printf("\n");
    }
}

void figura_b(int tamanho, char caractere){
    int i;
    for (i=tamanho; i>0; i--){
        linha(i, caractere);
        printf("\n");
    }
}

void figura_c(int tamanho, char caractere){
    int espacos;
    int i;
    for (i=1; i<=tamanho; i++) {
        espacos = tamanho - i;
        linha(espacos, ' ');
        linha(i, caractere);
        printf("\n");
    }
}

void figura_d(int tamanho, char caractere){
    int espacos;
    int i;
    for (i=tamanho; i>=0; i--) {
        espacos = tamanho - i;
        linha(espacos, ' ');
        linha(i, caractere);
        printf("\n");
    }
}

void figura_e(int tamanho, char caractere){
    int espacos;
    int i, j=1;
    for (i=1; i<=tamanho; i++){
        espacos = tamanho - i; //espaços em cada lado da figura (total = espacos * 2)
        
        // linhas de teste de valor das variaveis
        // printf("%d\t", espacos);
        // printf("%d\t", j); 

        linha(espacos, ' ');
        linha(j, caractere);
        linha(espacos, ' ');
        printf("\n");
        j = j + 2;
    }
}

void figura_f(int tamanho, char caractere){
    int espacos, metade;
    int i, j=1;
    for (i=0; i<tamanho+2; i++){
        if (tamanho==0){
            break;
        } else if (tamanho == 1){
            printf("*\n");
            break;
        }
        if (i <= tamanho-1){
            espacos = tamanho - i;
        } else {
            espacos = espacos + 1;
        }
        // printf("esp: %d\t", espacos);
        // printf("j: %d\t", j);         
        // printf("i: %d\t", i);         

        linha(espacos, ' ');
        linha(j, caractere);
        linha(espacos, ' ');
        printf("\n");
        if (i < tamanho-1){
            j = j + 2;
        } else {
            j = j - 2;
        }
    }

}



int main(){
    int i;
    for (i=0; i<5; i++){
        printf("i = %d\n", i);
        figura_f(i, '*');
        printf("\n");
    }
}