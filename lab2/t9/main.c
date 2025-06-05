#include "pilhas.h"

// vai receber uma string com o cálculo a ser realizado em
// notação polonesa -> retorna o resultado da operação
int calculadora_polonesa(const char **not_polonesa)
{
    int i=0;
    while (not_polonesa[i] != '\n')
    {
        Pilha *pilha = cria_pilha(100);
        //1. le um caractere
        char c = not_polonesa[i];
        //2. é dígito? sim! adiciona na pilha
        if (isdigit(c)) pilha = push(pilha, c);
        else if (c == ' ') continue;
        //3. é dígito? nao! pega os dois ultimos valores da pilha
        else 
        {
            if ()
        }
    }
    //e realiza a operação com eles
    //4. armazena o resultado da operação na pilha
    //4. string[i] == \n? sim! encerra a funcao e 
    //retorna o resultado
    //5. string[i] == \n? nao! repete para o proximo

}



int main()
{
    Pilha *pilha = cria_pilha(5);

    pilha = push(pilha, 'a');
    pilha = push(pilha, 'h');
    pilha = push(pilha, 'a');
    pilha = push(pilha, 'g');
    pilha = push(pilha, 'b');
    pilha = push(pilha, 'p');
    pilha = push(pilha, 'n');
    imprime_pilha(pilha);
    printf("\n\n");
}
