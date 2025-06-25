#include "pilhas.h"

// vai receber uma string com o cálculo a ser realizado em
// notação polonesa -> retorna o resultado da operação
int calculadora_polonesa(const char *not_polonesa)
{
    Pilha *pilha = cria_pilha();
    char *copia = strdup(not_polonesa);
    char *token = strtok(copia, " \t\n");
    int i=0;
    while (token != NULL)
    {
        char *end;
        long val = strtol(token, &end, 10);

        //2. é dígito? sim! adiciona na pilha
        if (*end == '\0') pilha = push(pilha, (int)val);
        else if (strlen(token) == 1)
        {
            int num_2 = pop(pilha);
            int num_1 = pop(pilha);
            switch(token[0])
            {
                case '+': pilha = push(pilha, num_1+num_2); break;
                case '-': pilha = push(pilha, num_1-num_2); break;
                case '*': pilha = push(pilha, num_1*num_2); break;
                case '/': pilha = push(pilha, num_1/num_2); break;
                default: 
                    printf("[%c] operador desconhecido\n", token[0]);
                    libera_pilha(pilha);
                    free(copia);
                    exit(1);
            }
        }
        else
        {
            fprintf(stderr, "Entrada inválida: %s\n", token);
            libera_pilha(pilha);
            free(copia);
            exit(1);
        }
        token = strtok(NULL, " \t\n");
    }
    int resultado = pop(pilha);
    libera_pilha(pilha);
    free(copia);
    return resultado;
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
