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

void imprime_desenho(char opcao_desenho){
    switch (opcao_desenho){
        case 'a': desenho_a();
        break;
        case 'b': desenho_b();
        break;
        case 'c': desenho_c();
        break;
        case 'd': desenho_d();
        break;
        case 'e': desenho_e();
        break;
        case 'f': desenho_f();
        break;
        case 'g': desenho_g();
        break;
        case 'h': desenho_h();
        break;
    }
}

//desenhos
void figura_a(){
    
}

void desenha_figura(){
    printf("Olá usuário, qual desenho você gostaria de fazer?\n");
    printf("a | b | c | d | e | f | g | h \n");
    //declaração de variáveis
    int tamanho_desenho;
    char opcao_figura, char_desenhado;
    //entrada de dados 
    do{
        //pede uma opção até que ela seja [a - h] ou z
        do{
            scanf("%c", &opcao_figura);
        }while(verifica_opcao()==false);
        //se opcao == z -> para o programa
        if (opcao_figura == 'z'){
            break;
        }
        //pede um char até que ele seja [! - ~] na tabela ascii
        do{
            scanf("%c", &char_desenhado);
        }while(verifica_char()==false);
        //pede um int até ele ser maior que 0
        do{
            scanf("%d", &tamanho_desenho);
        }while(verifica_inteiro()==false);

    }while(true);
    printf("Fim do programa...\n");
}

int main(){
    desenha_figura();
}
