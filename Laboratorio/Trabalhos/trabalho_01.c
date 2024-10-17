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

bool verifica_inteiro(int tamanho_desenho){
    if (tamanho_desenho >=0){
        return true;
    } else {
        return false;
    }
}

//desenhos
void linha(int n, char c){    
    for(int i=0; i<n; i++){
        printf("%c", c);
    }
    printf("\n");
} 

void figura_a(char char_desenhado, int tamanho_desenho){
    int i;
    for (i=1; i<tamanho_desenho+1; i++){
        linha(i, char_desenhado);
    }
}

void imprime_desenho(char opcao_desenho, char char_desenhado, int tamanho_desenho){
    switch (opcao_desenho){
        case 'a': figura_a(char_desenhado, tamanho_desenho);
        break;
        default: printf("kkkk");
    }
}


void desenha_figura(){
    printf("Olá usuário, qual desenho você gostaria de fazer? [a-h] \n");
    //declaração de variáveis
    int tamanho_desenho;
    char opcao_figura, char_desenhado;
    //entrada de dados 
    do{
        //pede uma opção até que ela seja [a - h] ou z
        do{
            printf("Digite opcao_figura: ");
            scanf(" %c", &opcao_figura);
        }while(verifica_opcao(opcao_figura)==false);

        //se opcao == z -> para o programa
        if (opcao_figura == 'z'){
            break;
        }
        
        //pede um char até que ele seja [! - ~] na tabela ascii
        do{
            printf("Digite char_desenhado: ");
            scanf(" %c", &char_desenhado);
        }while(verifica_char(char_desenhado)==false);
        //pede um int até ele ser maior que 0
        do{
            printf("Digite tamanho_desenho:  ");
            scanf("%d", &tamanho_desenho);
        }while(verifica_inteiro(tamanho_desenho)==false);

        imprime_desenho(opcao_figura, char_desenhado, tamanho_desenho);
    }while(true);
    printf("Fim do programa...\n");
}

int main(){
    desenha_figura();
}
