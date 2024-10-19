//t1 l124b Miguel Avila de Oliveira
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//verifica se a entrada digitada é aceita ou não
bool verifica_opcao(char opcao_figura){
    if (opcao_figura >= 97 && opcao_figura <= 104 || opcao_figura == 122){
        return true;
    } else {
        printf("Valor inválido, digite outro valor: ");
        return false;
    }
}

bool verifica_char(char char_desenhado){
    if (char_desenhado >= 33 && char_desenhado <= 126){
        return true;
    } else {
        printf("Caractere inválido, digite outro : ");
        return false;
    }
}

bool verifica_inteiro(int tamanho_figura){
    if (tamanho_figura >=0){
        return true;
    } else {
        return false;
    }
}

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


//chama a funcao do figura correspondente
void imprime_figura(char opcao_figura, char char_desenhado, int tamanho_figura){
    printf("Imprimindo o figura %c, com o caractere %c e altura %d.\n", opcao_figura, char_desenhado, tamanho_figura);
    switch (opcao_figura){
        case 'a': figura_a(char_desenhado, tamanho_figura);
        break;
        default: printf("kkkk");
    }
    printf("Que legal! Vamos fazer outro. \n");

}


void desenha_figura(){
    printf("Olá usuário, me dê as instruções para o figura! \n");
    //declaração de variáveis
    int tamanho_figura;
    char opcao_figura, char_desenhado;
    //entrada de dados 
    do{
        //pede uma opção até que ela seja [a - h] ou z
        do{
            printf("Qual a figura? [a-h]: ");
            scanf(" %c", &opcao_figura);
        }while(verifica_opcao(opcao_figura)==false);

        //se opcao == z -> para o programa
        if (opcao_figura == 'z'){
            break;
        }
        
        //pede um char até que ele seja [! - ~] na tabela ascii
        do{
            printf("Qual o caractere base? [tabela ASCII] ");
            scanf(" %c", &char_desenhado);
        }while(verifica_char(char_desenhado)==false);
        //pede um int até ele ser maior que 0
        do{
            printf("Qual o tamanho da figura? ");
            scanf(" %d", &tamanho_figura);
        }while(verifica_inteiro(tamanho_figura)==false);

        imprime_figura(opcao_figura, char_desenhado, tamanho_figura);
    }while(true);
    printf("Fim do programa...\n");
}

int main(){
    desenha_figura();
}
