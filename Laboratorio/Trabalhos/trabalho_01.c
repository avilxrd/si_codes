//t1 l124b Miguel Avila de Oliveira
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <signal.h>


//funções auxiliares
//limpa o buffer, para evitar erros ao usuario digitar duplicado
void limpar_buffer(){
    while (getchar() != '\n');
}

//verifica se a entrada digitada é aceita ou não (a-h ou z)
bool verifica_opcao(char opcao_figura){
    if (opcao_figura >= 97 && opcao_figura <= 104 || opcao_figura == 122){
        limpar_buffer();
        return true;
    } else {
        limpar_buffer();
        printf("Por favor, digite um caractere entre 'a' e 'h'. (z para sair) ");
        printf("\n");
        return false;
    }
}

//verifica se a entrada digitada é aceita ou não (char ascii)
bool verifica_char(char char_desenhado){
    if (char_desenhado >= 33 && char_desenhado <= 126){
        limpar_buffer();
        return true;
    } else {
        limpar_buffer();
        printf("Digite um caractere ASCII. \n");
        return false;
    }
}


//imprimir n caracteres c
void linha(int tamanho, char caractere){    
    int i;
    for(i=0; i<tamanho; i++){
        printf("%c", caractere);
    }
}
//imprime com espaços antes e depois do char
void imprimir_padrao(int tamanho, char caractere, int espacos_esquerda, int espacos_direita) {
    linha(espacos_esquerda, ' ');
    linha(tamanho, caractere);
    linha(espacos_direita, ' ');
    // printf("\n");
}

void imprimir_melhorado(int quant_esquerda, char esquerda_c, int tamanho, char tamanho_c, int quant_meio, char meio_c, int tamanho2, char tamanho2_c, int quant_direita, char direita_c){
    linha(quant_esquerda, esquerda_c);
    linha(tamanho, tamanho_c);
    linha(quant_meio, meio_c);
    linha(tamanho2, tamanho2_c);
    linha(quant_direita, direita_c);
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
void figura_h(int tamanho, char caractere){
    int i, j=1, k=0;
    int quant_chars = 2*tamanho + 1;
    int aux;
    linha(quant_chars, caractere);
    printf("\n");
    for (i=0; i<tamanho; i++){
        if(i==0) j = 0;
        else if(i==1) j = 1;
        else j = j + 2;
        imprimir_melhorado(tamanho-i, caractere, 1, ' ', j, caractere, k, ' ', tamanho-i, caractere);
        printf("\n");
        if(k!=1) k=k+1;
        aux = tamanho - i;
    }
    aux = aux + 1;
    for (i=0; i<tamanho-1; i++){
        j = j-2;
        if(i==tamanho-2) k=k-1;
        imprimir_melhorado(aux+i, caractere, 1, ' ', j, caractere, k, ' ', aux+i, caractere);
        printf("\n");
    }
    linha(quant_chars, caractere);
    printf("\n");
}

//chama a funcao do figura correspondente
void imprime_figura(char opcao_figura, char char_desenhado, int tamanho_figura){
    printf("\nImprimindo o figura %c, com o caractere %c e altura %d.\n\n", opcao_figura, char_desenhado, tamanho_figura);
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
        case 'h': figura_h(tamanho_figura, char_desenhado);
        break;
        default: printf("Nao deveria chegar aqui...");
    }
    printf("\nVamos fazer outro:  \n\n");
}
//lógica principal do programa
int main(){
    int tamanho_figura;
    char opcao_figura, char_desenhado;

    printf("Olá usuário, me dê as instruções para a figura! \n\n");

    //entrada de dados 
    do{
        //pede uma opção até que ela seja [a - h] ou z
        do{
            printf("Qual a figura? [a-h, ou z]: ");
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

        //pede um int até ele ser um inteiro maior que 0
        do{
            printf("Qual o tamanho da figura? ");
            if (scanf("%d", &tamanho_figura)!=1){
                printf("Tamanho inválido...");
                limpar_buffer();
                continue; //só usei para corrigir o bug
            } else if (tamanho_figura < 0){
                printf("Tamanho negativo...");
            } else {
                limpar_buffer();
                break;
            }
        }while(true);

        //chama a função da figura escolhida
        imprime_figura(opcao_figura, char_desenhado, tamanho_figura);

    }while(true);

    printf("\nFim do programa...\n");
}