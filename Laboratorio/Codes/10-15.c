#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int aleatorio(int num1, int num2){
    return num1 + rand() % (num2 - num1 + 1);
}

char le_resposta(){
    char resposta;

    do{
        printf("0: Sim | 1: Menor | 2: Maior \n");
        scanf(" %c", &resposta);    
    }while(resposta < '0' || resposta > '2');
    
    return resposta;
}

int advinha(){
    int menor = 1, maior = 100;
    srand(time(0));

    printf("Press enter to start: ");
    getchar();

    while(true){
        int chute;
        chute = aleatorio(menor, maior);

        printf("O numero é %d?\n", chute);
        char resposta = le_resposta();
        
        if(resposta == '1'){
            maior = chute - 1;
        }else if (resposta == '2'){
            menor = chute + 1;
        }else if(resposta == '0'){
            break;
        }else{
            printf("caractere invalido!\n");
        }

        if(menor>maior){
            printf("Não vale mentir!\n");
            break;
        }
    }
    printf("Resposta certa!");
}

void linha(int n, char c){    
    for(int i=0; i<n; i++){
        printf("%c", c);
    }
    printf("\n");
} 

int altura(int num){
    int i;
    for (i=0; i<num; i++){
        linha(i, "*");
    }
}

int main(){
    altura(4);
}