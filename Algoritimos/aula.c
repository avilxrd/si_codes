#include <stdio.h>

//Exercicio 3
void operacoes(){
    float num1, num2;

    printf("Digite um numero: ");
    scanf("%f", &num1);
    printf("Digite outro numero: ");
    scanf("%f", &num2);

    printf("\nSoma: %.2f\n", num1+num2);
    printf("Subtracao: %.2f\n", num1-num2);
    printf("Multiplicacao: %.2f\n", num1*num2);
    printf("Divisao: %.2f\n\n", num1/num2);
}

int main(){
    operacoes();
}