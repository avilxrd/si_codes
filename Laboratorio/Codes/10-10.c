#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int teste_operador(char operador){
    while(operador!= '+' && operador != '-' && operador != '*' && operador != '/'){
        return 0;
    }
    return 1; 
}

int calculadora(){
    float num_1, num_2, resultado;
    char operador;
    do{
    scanf("%c", &operador);
    }
    while(teste_operador(operador)==0);
    scanf("%f%f", &num_1, &num_2);
    switch(operador){
        case '+': resultado=num_1+num_2;
        case '-': resultado= num_1-num_2;
        case '*': resultado=num_1*num_2;
        case '/': resultado = num_1/num_2;
    }
    printf("resultado: %.2f", resultado);

}

bool is_number(int num){
    if(num == 1 || num == 2 || num == 3 || num == 4 || num == 5
    || num == 6 || num == 7 || num == 8 || num == 9 || num == 0){
        return 1;
    }else{
        return 0;
    }
}

int lenum(){
    int valor=0;
    char num;

    while(true){
        if(!is_number(num)){
            break;
        }
        //usar o digito
        valor = valor * 10 + (num - '0');
    }
        printf("%d", valor);
        return valor;
}

int main(){
    lenum();
}