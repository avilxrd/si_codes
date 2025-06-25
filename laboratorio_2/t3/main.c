#include "listas.h"

int main()
{
    char numero1[1000], numero2[1000];
    Numero *num1, *num2;
    Numero *soma, *subtracao, *multiplicacao, *divisao;

    printf("\nDigite um numero: ");
    fgets(numero1, 1000, stdin);
    printf("\nDigite um numero: ");
    fgets(numero2, 1000, stdin);
    numero1[strcspn(numero1, "\n")] = '\0'; //remover a quebra de linha do fgets()
    numero2[strcspn(numero2, "\n")] = '\0'; // ==

    num1 = ler_numero(numero1);
    num2 = ler_numero(numero2);
    
    soma          = soma_numeros     (num1, num2);
    subtracao     = subtrai_numeros  (num1, num2);
    multiplicacao = multiplica_numeros(num1, num2);
    divisao       = divide_numeros   (num1, num2);

    imprime_operacao(num1, num2, soma, "soma");
    imprime_operacao(num1, num2, subtracao, "subtracao");
    imprime_operacao(num1, num2, multiplicacao, "multiplicacao");
    imprime_operacao(num1, num2, divisao, "divisao");
    printf("\n\nA DIVISAO E INTEIRA, MAS POSSO REFAZER COM PONTO FLUTUANTE CASO NECESSARIO\n\n");
    return 0;
}