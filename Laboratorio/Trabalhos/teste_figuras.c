#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void linha(int tamanho, char caractere){    
    int i;
    for(i=0; i<tamanho; i++){
        printf("%c", caractere);
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
    figura_e(tamanho, caractere);
    int espacos=1;
    int i, j=tamanho;

    for (i=tamanho-1; i>=0; i--){
        if (i != tamanho-1){
            j = (i*2) + 1; 
            linha(espacos, ' ');
            linha(j, caractere);
            linha(espacos, ' ');
            printf("\n");
            espacos = espacos + 1;
        }
    }
}


// 
void figura_g(int tamanho, char caractere){
    int i, j=0, a=0;

    for (i=1; i<=tamanho; i++){
        linha(tamanho-i, ' ');
        printf("%c", caractere);
        linha(a, ' ');
        if (i != 1){
            printf("%c", caractere);
        }
        a = j*2 + 1;
        j = j + 1;
        printf("\n");
    }
    
    j = j - 2;
    for (i=tamanho-1; i>=1; i--){
        j = j - 1;
        a = j*2 + 1;
        linha(tamanho-i, ' ');
        printf("%c", caractere);
        linha(a, ' ');
        if (i != 1){
            printf("%c", caractere);
        }
        printf("\n");
    }
}


int main(){
    // int i;
    // for (i=0; i<=10; i++){
    //     printf("tamanho = %d\n", i);
    //     figura_g(i, '*');
    //     printf("\n");
    // }
    figura_g(30, '*');

}