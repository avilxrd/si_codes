//t1 l124b Miguel Avila de Oliveira
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//verifica se a entrada digitada é aceita ou não (a-h ou z)
bool verifica_opcao(char opcao_figura){
    if (opcao_figura >= 97 && opcao_figura <= 104 || opcao_figura == 122){
        return true;
    } else {
        printf("(z para sair) Digite um caractere entre [a - h]: ");
        return false;
    }
}

//verifica se a entrada digitada é aceita ou não (char ascii)
bool verifica_char(char char_desenhado){
    if (char_desenhado >= 33 && char_desenhado <= 126){
        return true;
    } else {
        printf("Digite um caractere ASCII: ");
        return false;
    }
}

//verifica se a entrada digitada é aceita ou não (tamanho positivo)
bool verifica_inteiro(int tamanho_figura){
    if (tamanho_figura >=0){
        return true;
    } else {
        printf("Digite um inteiro positivo: ");
        return false;
    }
}

//funções auxiliares
//imprimir n caracteres c
void linha(int tamanho, char caractere){    
    int i;
    for(i=0; i<tamanho; i++){
        printf("%c", caractere);
    }
}
//imprimir n espacos brancos
void imprimir_espacos(int quantidade){
    int i;
    for (i=0; i<quantidade; i++){
        printf(" ");
    }
}
//imprime com espaços antes e depois do char
void imprimir_padrao(int tamanho, char caractere, int espacos_esquerda, int espacos_direita) {
    imprimir_espacos(espacos_esquerda);
    linha(tamanho, caractere);
    imprimir_espacos(espacos_direita);
    // printf("\n");
}

//logica especifica de cada figura
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
    int i;
    for (i=1; i<=tamanho; i++){
        imprimir_padrao(i, caractere, tamanho-i, 0);
        printf("\n");
    }
}
void figura_d(int tamanho, char caractere){
    int i;
    for (i=tamanho; i>0; i--){
        imprimir_padrao(i, caractere, tamanho-i, 0);
        printf("\n");
    }
}
void figura_e(int tamanho, char caractere){
    int i, j=1;
    for (i=1; i<=tamanho; i++){
        imprimir_padrao(j, caractere, tamanho-i, tamanho-i);
        printf("\n");
        j = j + 2;
    }
}
void figura_f(int tamanho, char caractere){
    figura_e(tamanho, caractere);
    int i, j=1;

    for (i=tamanho-1; i>0; i--){
        imprimir_padrao(2*i-1, caractere, j, j);
        printf("\n");
        j = j + 1;
    }
}
void figura_g(int tamanho, char caractere){
    int i, j=0, espacos_centrais=0;

    for (i=1; i<=tamanho; i++){
        imprimir_padrao(1, caractere, tamanho-i, espacos_centrais);
        if (i!=1) imprimir_padrao(1, caractere, 0, 0);
        printf("\n");
        espacos_centrais = (2*j) + 1;
        j = j + 1;
    }
    j = j-3;
    for (i=i-2; i>=1; i--){
        espacos_centrais = (2*j) + 1;
        j = j - 1;
        imprimir_padrao(1, caractere, tamanho-i, espacos_centrais);
        if (i!=1) imprimir_padrao(1, caractere, 0, 0);
        printf("\n");
    }
}


//chama a funcao do figura correspondente
void imprime_figura(char opcao_figura, char char_desenhado, int tamanho_figura){
    printf("Imprimindo o figura %c, com o caractere %c e altura %d.\n", opcao_figura, char_desenhado, tamanho_figura);
    switch (opcao_figura){
        case 'a': figura_a(tamanho_figura, char_desenhado);
        break;
        case 'b': figura_b(tamanho_figura, char_desenhado);
        break;
        case 'c': figura_c(tamanho_figura, char_desenhado);
        break;
        case 'd': figura_d(tamanho_figura, char_desenhado);
        break;
        case 'e': figura_e(tamanho_figura, char_desenhado);
        break;
        case 'f': figura_f(tamanho_figura, char_desenhado);
        break;
        case 'g': figura_g(tamanho_figura, char_desenhado);
        break;
        // case 'h': figura_h(tamanho_figura, char_desenhado);
        // break;
        default: printf("Nao deveria chegar aqui...");
    }
    printf("Que legal! Vamos fazer outro. \n");
}

//lógica principal do programa
int main(){
    int tamanho_figura;
    char opcao_figura, char_desenhado;

    printf("Olá usuário, me dê as instruções para a figura! \n");

    //entrada de dados 
    do{
        //pede uma opção até que ela seja [a - h] ou z
        do{
            printf("(z para sair) Qual a figura? [a-h]: ");
            scanf(" %c", &opcao_figura);
        }while(verifica_opcao(opcao_figura)==false);

        //se opcao == z -> para o programa
        if (opcao_figura == 'z'){
            break;
        }
        
        //pede um char até que ele seja [! - ~] na tabela ASCII
        do{
            printf("Qual o caractere base? [tabela ASCII] ");
            scanf(" %c", &char_desenhado);
        }while(verifica_char(char_desenhado)==false);

        //pede um int até ele ser maior que 0
        do{
            printf("Qual o tamanho da figura? ");
            scanf(" %d", &tamanho_figura);
        }while(verifica_inteiro(tamanho_figura)==false);

        //chama a função da figura escolhida
        imprime_figura(opcao_figura, char_desenhado, tamanho_figura);

    }while(true);

    printf("\nFim do programa...\n");
}