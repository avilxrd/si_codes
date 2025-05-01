#include "listas.h"

bool digito_valido(const char caractere)
{
    if (caractere >= 48 && caractere <= 57) return true;
    else return false;
}

Numero* ler_numero(const char* string)
{
    Numero* numero = (Numero*)malloc(sizeof(Numero));
    numero->negativo = false;
    numero->lista    = NULL;

    int i=0;
    if (string[0] == '-')
    {
        numero->negativo = true;
        i++;
    }

    for (i; string[i] != '\0'; i++)
    {
        if (digito_valido(string[i]) == true)
        {
            int digito = string[i] - '0';
            numero = insere_final(numero, digito);
        }
    }
    return numero;
}

void imprime_numero(Numero* numero)
{
    if (numero->negativo) printf("-");

    int total_digitos = 0;
    Node* temp = numero->lista;
    while (temp != NULL)
    {
        total_digitos++;
        temp = temp->prox;
    }

    temp = numero->lista;
    int i = 0;
    printf("\nNumero: ");
    while (temp != NULL)
    {
        printf("%d", temp->valor);
        i++;
        if ((total_digitos - i)%3 == 0 && (total_digitos - i) > 0) printf(".");
        temp = temp->prox;
    }

    printf("\n");
}

Numero* insere_final(Numero* numero, int valor_inserido)
{
    Node* lista = numero->lista;
    //caso a lista esteja vazia
    if (lista == NULL)
    {
        Node* novo_node = (Node*)malloc(sizeof(Node));
        novo_node->ant  = NULL;
        novo_node->prox = NULL;
        novo_node->valor = valor_inserido;
        numero->lista = novo_node;
    }
    else
    {
        Node* temp = lista;
        while (temp->prox != NULL) temp = temp->prox;
        Node* novo_node = (Node*)malloc(sizeof(Node));
        novo_node->prox = NULL;
        novo_node->ant  = temp;
        novo_node->valor = valor_inserido;
        temp->prox = novo_node;
        numero->lista = lista;
    }
    return numero;
}

Node* insere_lista(Node* lista, int valor)
{  
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox = lista;
    novo->ant = NULL;
    if (lista != NULL) lista->ant = novo;
    return novo;
}

Node* final_lista(Node* lista)
{
    if (lista == NULL) return NULL;
    Node* temp = lista;
    while (temp->prox != NULL) temp = temp->prox;
    return temp;
}

//  recebe uma struct Numero e retorna a quantidade
//  de algarismos que o numero possui
int conta_digitos(Numero* numero)
{
    Node* temp = numero->lista;
    int quantidade=0;
    while (temp != NULL)
    {
        quantidade++;
        temp = temp->prox;
    }
    return quantidade;
}

int compara_numeros(Numero* numero1, Numero* numero2)
{
    if (conta_digitos(numero1) > conta_digitos(numero2)) return  1;
    if (conta_digitos(numero1) < conta_digitos(numero2)) return -1;

    Node* num1 = numero1->lista;
    Node* num2 = numero2->lista;
    
    while (num1 != NULL && num2 != NULL) //mesma quantidade de algarismos
    {
        if (num1->valor > num2->valor) return  1;
        if (num1->valor < num2->valor) return -1;
        num1 = num1->prox;
        num2 = num2->prox;
    }
    return 0;
}

//  remove os zeros a esquerda do numero
void remove_zeros(Numero* numero)
{
    Node* num = numero->lista;
    while (num != NULL && num->valor == 0 && num->prox != NULL)
    {
        Node* lixo = num;
        num        = num->prox;
        num->ant   = NULL;
        free(lixo);
    }
    numero->lista = num;
}

// Função auxiliar para converter um Numero em string
char* numero_string(Numero* numero)
{
    int digitos = conta_digitos(numero);
    int pontos = (digitos - 1) / 3;
    int tamanho = digitos + pontos + (numero->negativo ? 1 : 0);

    char* str = (char*)malloc((tamanho + 1) * sizeof(char));
    str[tamanho] = '\0';

    Node* atual = numero->lista;
    int i=0;

    if (numero->negativo) str[i++] = '-';
    
    int restante = digitos;
    while (atual != NULL)
    {
        str[i++] = atual->valor + '0';
        restante--;
        if (restante > 0 && restante % 3 == 0) str[i++] = '.';
        atual = atual->prox;
    }
    return str;
}

Numero* clonar_numero(Numero* numero)
{
    Numero* novo_numero = (Numero*)malloc(sizeof(Numero));
    novo_numero->negativo = numero->negativo;
    novo_numero->lista = NULL;

    Node* temp = numero->lista;
    while (temp != NULL)
    {
        novo_numero = insere_final(novo_numero, temp->valor);
        temp = temp->prox;
    }

    return novo_numero;
}

void imprime_operacao(Numero* numero1, Numero* numero2, Numero* resultado, const char* operacao)
{
    char operador;

    if      (strcmp(operacao, "soma") == 0) operador = '+';
    else if (strcmp(operacao, "subtracao") == 0) operador = '-';
    else if (strcmp(operacao, "multiplicacao") == 0) operador = 'x';
    else if (strcmp(operacao, "divisao") == 0) operador = '/';
    else {
        printf("Operação inválida!\n");
        return;
    }

    printf("\n%s\n\n", operacao);

    char* str1 = numero_string(numero1);
    char* str2 = numero_string(numero2);
    char* str3 = numero_string(resultado);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len3 = strlen(str3);
    int maxlen = len1;
    if (len2 + 1 > maxlen) maxlen = len2 + 1;
    if (len3 > maxlen) maxlen = len3;

    printf("%*s\n", maxlen, str1);
    printf("%c%*s\n", operador, maxlen - 1, str2);
    for (int i = 0; i < maxlen; i++) printf("-");
    printf("\n");
    printf("%*s\n", maxlen, str3);

    free(str1); free(str2); free(str3);
}

// ==============================================
// ====== OPERACOES COM OS NUMEROS GRANDES ======
// ==============================================

//  recebe dois ponteiros para struct Numero (numero1 e numero2)
//  e retorna um ponteiro para struct Numero com o resultado
//  da soma entre esses dois "Numeros"
Numero* soma_numeros(Numero* numero1, Numero* numero2)
{
    Numero *resultado = (Numero*)malloc(sizeof(Numero));
    resultado->negativo = false;
    resultado->lista    = NULL;

    Node* num1 = final_lista(numero1->lista);    
    Node* num2 = final_lista(numero2->lista);    
    
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry > 0)
    {
        int val1 = (num1 != NULL) ? num1->valor : 0;
        int val2 = (num2 != NULL) ? num2->valor : 0;

        int soma = val1 + val2 + carry;
        carry = soma / 10;
        int digito = soma % 10;

        resultado->lista = insere_lista(resultado->lista, digito);

        if (num1 != NULL) num1 = num1->ant;
        if (num2 != NULL) num2 = num2->ant;
    }

    return resultado;
}

//  2. subtracao de dois numeros
//  separado em duas funcoes, uma que faz a subtracao absoluta
//  de um numero pelo outro (modulo) e outra que trata os sinais

//  recebe dois ponteiros para struct Numero (numero1 e numero2)
//  e retorna um ponteiro para struct Numero com o resultado
//  da subtracao entre esses dois numeros
Numero* subtrai_modulo(Numero* numero1, Numero* numero2)
{
    Numero* resultado = (Numero*)malloc(sizeof(Numero));
    resultado->lista    = NULL;
    resultado->negativo = false;

    Node* num1 = final_lista(numero1->lista);
    Node* num2 = final_lista(numero2->lista);

    int carry=0;
    while (num1 != NULL)
    {
        int val1 = (num1 != NULL) ? num1->valor : 0;
        int val2 = (num2 != NULL) ? num2->valor : 0;
        val1 -= carry;

        if (val1 < val2)
        {
            val1 += 10;
            carry =  1;
        }
        else carry = 0;

        int sub = val1 - val2;
        resultado->lista = insere_lista(resultado->lista, sub);
        num1 = num1->ant;
        if (num2 != NULL) num2 = num2->ant;
    }

    remove_zeros(resultado);
    return resultado;
}


Numero* subtrai_numeros(Numero* numero1, Numero* numero2)
{
    Numero* resultado;
    
    if (numero1->negativo != numero2->negativo)
    {
        Numero* temp2 = (Numero*)malloc(sizeof(Numero));
        temp2->negativo = !numero2->negativo;
        temp2->lista = numero2->lista;
        resultado = soma_numeros(numero1, temp2);
        resultado->negativo = numero1->negativo;
        return resultado;
    }
    
    int comparacao = compara_numeros(numero1, numero2);
    if (comparacao == 0) //numeros iguais, resultado = 0;
    {
        resultado = (Numero*)malloc(sizeof(Numero));
        resultado->negativo = false;
        resultado->lista = insere_lista(NULL, 0);
    }
    
    else if (comparacao == 1) //numero1 > numero2
    {
        resultado = subtrai_modulo(numero1, numero2);
        resultado->negativo = numero1->negativo;
    }
    else if (comparacao == -1) //numero1 < numero2
    {
        resultado = subtrai_modulo(numero2, numero1);
        resultado->negativo = !numero1->negativo;
    }
    return resultado;
}

//  recebe dois ponteiros para struct Numero (numero1 e numero2)
//  e retorna um ponteiro para struct Numero com o resultado
//  de multiplicacao entre esses dois numeros
Numero* multiplica_numeros(Numero* numero1, Numero* numero2)
{
    Numero* resultado   = (Numero*)malloc(sizeof(Numero));
    resultado->lista    = NULL;
    resultado->negativo = numero1->negativo ^ numero2->negativo; 

    Node* num2 = final_lista(numero2->lista);
    int ordem = 0;

    while (num2 != NULL)
    {
        Numero* temp   = (Numero*)malloc(sizeof(Numero));
        temp->lista    = NULL;
        temp->negativo = false;

        for (int i=0; i<ordem; i++) temp->lista = insere_lista(temp->lista, 0);

        Node* num1 = final_lista(numero1->lista);
        int carry = 0;

        while (num1 != NULL)
        {
            int prod = num1->valor * num2->valor + carry;
            carry = prod / 10;
            int digito = prod % 10;
            temp->lista = insere_lista(temp->lista, digito);
            num1 = num1->ant;
        }

        if (carry > 0) temp->lista = insere_lista(temp->lista, carry);

        resultado = soma_numeros(resultado, temp);
        ordem++;
        num2 = num2->ant;
    }

    return resultado;
}

Numero* divide_numeros(Numero* numero1, Numero* numero2)
{
    if (compara_numeros(numero2, ler_numero("0")) == 0) 
    {
        printf("\nDivisão por zero.\n");
        return NULL;
    }

    Numero* quociente = ler_numero("0");
    Numero* um        = ler_numero("1");
    Numero* resto     = clonar_numero(numero1);

    while (compara_numeros(resto, numero2) >= 0) {
        Numero* novo_resto = subtrai_numeros(resto, numero2);
        free(resto);
        resto = novo_resto;

        Numero* novo_quociente = soma_numeros(quociente, um);
        free(quociente);
        quociente = novo_quociente;
    }

    free(resto);
    free(um);
    return quociente;
}
