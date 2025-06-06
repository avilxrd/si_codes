#include "pilhas.h"

// vai receber uma string com o cálculo a ser realizado em
// notação polonesa -> retorna o resultado da operação
int calculadora_polonesa(const char *not_polonesa)
{
    int i=0;
    Pilha *pilha = cria_pilha();
    while (not_polonesa[i] != '\n')
    {
        //1. le um caractere
        int c = not_polonesa[i];
        //2. é dígito? sim! adiciona na pilha
        if (isdigit(c))
        {
            pilha = push(pilha, (c -'0'));
            i++;
        }
        else if (c == ' ')
        {
            i++;
            continue;
        }
        //3. é dígito? nao! pega os dois ultimos valores da pilha
        //e realiza a operação com eles
        else 
        {
            int num_2 = pop(pilha);
            int num_1 = pop(pilha);
            //4. armazena o resultado da operação na pilha
            if      (c == '*') pilha = push(pilha, num_1*num_2);
            else if (c == '/') pilha = push(pilha, num_1/num_2);
            else if (c == '+') pilha = push(pilha, num_1+num_2);
            else if (c == '-') pilha = push(pilha, num_1-num_2);
            i++;
        }
    }
    return pilha->elementos[pilha->topo];
}

int main()
{
    // ex. de teste. res = 766
    // 2*(3+(4*(5+(6*(7+8)))))
    // 2 3 4 5 6 7 8 + * + * + *
    
    char str[255];
    printf("\ndigite em notacao polonesa: ");
    fgets(str, sizeof(str), stdin);
    // fgets()
    int res = calculadora_polonesa(str);
    printf("\nresultado: %d\n", res);
    return 0;
}
