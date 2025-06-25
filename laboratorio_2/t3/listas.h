#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//  lista duplamente encadeada de inteiros
struct node{
    int          valor; // valor armazenado
    struct node* prox;  // ponteiro para o proximo elemento
    struct node* ant;   // ponteiro para o elemento anterior
};
typedef struct node Node;

//  representacao de um numero com lista
struct numero{
    bool  negativo; // armazena apenas um boolean para representar
                    // se é negativo, ao invés de armazenar em cada nó.
    Node* lista;    // cabeça de uma lista encadeada, que armazena os
                    // valores de um "número".
};
typedef struct numero Numero;

// recebe um caractere e verifica se ele está dentro de um intervalo
// ASCII desejado
bool digito_valido(const char caractere);

//  le o input de uma string digitada pelo usuario e 
//  transforma em uma lista encadeada de inteiros
Numero* ler_numero(const char* string);

// recebe uma struct Numero e imprime todos os seus valores
void imprime_numero(Numero* numero);

// recebe um ponteiro de struct Numero e um int valor_inserido, e insere
// o valor_inserido no FINAL da lista encadeada (numero->lista)
Numero* insere_final(Numero* numero, int valor_inserido);

// recebe um ponteiro de struct Node e um int valor, e insere
// o valor no INÍCIO da lista encadeada
Node* insere_lista(Node* lista, int valor);

// recebe um ponteiro de struct Node, percorre até o final dessa lista
// e retorna o endereço do ultimo elemento
Node* final_lista(Node* lista);

// recebe um ponteiro de struct Numero e retorna a quantidade de algarismos
int conta_digitos(Numero* numero);

//  recebe dois numeros, compara eles e retorna um valor 
//  representando qual é o maior entre eles
//  (a>b): 1        (a<b): -1       (a==b): 0
int compara_numeros(Numero* numero1, Numero* numero2);

// recebe um ponteiro para struct Numero e remove os zeros à esquerda.
// Caso o resultado seja 0, deixa apenas um zero.
void remove_zeros(Numero* numero);

// recebe um ponteiro de struct Numero e retorna uma string equivalente ao
// numero armazenado na lista numero->lista
char* numero_string(Numero* numero);

// recebe um ponteiro para struct Numero, cria outro Numero e copia os elementos
// do Numero recebido para o novo. Retorna o novo Numero. 
Numero* clonar_numero(Numero* numero);

// recebe 3 ponteiros de struct Numero (numero1, numero2, resultado) e uma string referente
// à operação a ser realizada. Mostra na tela a conta de acordo com a operação selecionada
void imprime_operacao(Numero* numero1, Numero* numero2, Numero* resultado, const char* operacao);

// ==============================================
// ====== OPERACOES COM OS NUMEROS GRANDES ======
// ==============================================

// recebe 2 ponteiros para struct Numero (numero1 e numero2), realiza uma
// soma entre eles e retorna um ponteiro para struct Numero com o resultado.
Numero* soma_numeros(Numero* numero1, Numero* numero2);

// recebe 2 ponteiros para struct Numero (numero1 e numero2), realiza uma
// subtração absoluta entre eles, ou seja, não se preocupa com o sinal, 
// e retorna um ponteiro para struct Numero com o resultado.
Numero* subtrai_modulo(Numero* numero1, Numero* numero2);

// recebe 2 ponteiros para struct Numero (numero1 e numero2), realiza uma
// subtração entre eles e retorna um ponteiro para struct Numero com o resultado.
// Trata o sinal, pois utiliza o resultado da função subtrai_modulo();
Numero* subtrai_numeros(Numero* numero1, Numero* numero2);

// recebe 2 ponteiros para struct Numero (numero1 e numero2), realiza uma
// multiplicação entre eles e retorna um ponteiro para struct Numero com o resultado.
Numero* multiplica_numeros(Numero* numero1, Numero* numero2);

// recebe 2 ponteiros para struct Numero (numero1 e numero2), realiza uma
// divisão INTEIRA entre eles e retorna um ponteiro para struct Numero com o resultado.
Numero* divide_numeros(Numero* numero1, Numero* numero2);