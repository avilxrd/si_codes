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

int triangulo(){
    int i;
    int num;
    scanf("%d", &num);
    for (i=1; i<num+1; i++){
        linha(i, '*');
    }
}

int triangulo_contrario(){
    int i;
    int num;
    scanf("%d", &num);
    for (i=num; i>0; i--){
        linha(i, '*');
    }
}
//Funcoes para figuras

//9
void calendario(int dias, int primeiro_dia){
    int i;
    int dia=1, posicao = primeiro_dia;
    printf(" D  S  T  Q  Q  S  S\n");
    while(dia <= dias){
        for (i=0; i<posicao; i++){
            printf("   ");
        }
        while (posicao<7 && dia<=dias) {
            printf("%2d ", dia);
            dia++;
            posicao++;
        }
        printf("\n");
        posicao = 0;
    }

}

int main(){
    calendario(31, 5);
}
