// l1-t2 Miguel Avila de Oliveira
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define RAINHA 'Q'
#define ESPACO_BRANCO ' '

// 
// FUNÇÕES UTEIS
// 

// reutilizei do outro trabalho
void limpar_buffer(){
    while (getchar() != '\n');
}
// peguei esse codigo aqui -> https://www.geeksforgeeks.org/square-root-of-an-integer/
int floorSqrt(int x){
    // Base cases
    if (x == 0 || x == 1)
        return x;

    // Starting from 1, try all numbers until
    // i*i is greater than or equal to x.
    int i = 1, result = 1;
    while (result <= x) {
        i++;
        result = i * i;
    }
    return i - 1;
}
// apenas verifica se um numero é par
bool par(int tamanho){
    if (tamanho%2==0) return true;
    else return false ;
}

// 
// PARTE 1 DO TRABALHO -> VERIFICAÇÃO DAS N RAINHAS
// 
bool verifica_linha(int tamanho, char str[tamanho]){
    int i, aux=0, cont=0;
    
    for (i=0; i<tamanho; i++){
        // conta as rainhas por linha
        if (str[i] == RAINHA) cont = cont + 1;
        
        // conta quantos quadrados foram verificados
        aux = aux + 1;
        // analisa as informações acima
        if (aux == 4){
            if (cont == 0){
                // printf("Nenhuma Rainha na Linha\n");
                // return false;
            }
            else if (cont > 1){
                printf("Mais de uma Rainha na Linha\n");
                return false;
            }
            aux = 0;
            cont = 0;
        }
    }
    return true;
}

bool verifica_coluna(int tamanho, char str[tamanho]){
    int i, j, aux=0, cont=0, quant=0;

    // percorre o array em colunas
    for (i=0; i<4;i++){
        aux = i;
        for (j=0; j<4; j++){
            // printf("i:[%d], j:[%d], aux:[%d]\n", i, j, aux);

            // conta as rainhas por coluna
            if (str[aux] == RAINHA) cont = cont + 1;
            quant = quant + 1;

            // verifica os dados
            if (quant == 4){
                if (cont == 0){
                    // printf("Nenhuma rainha na coluna\n");
                    // return false;
                } else if (cont > 1){
                    printf("Mais de uma rainha na coluna\n");
                    return false;
                }
                cont = 0;
                quant = 0;
            }
            aux = aux + 4;
        }
    }
    return true;
}

bool verifica_diagonal(int tamanho, char str[tamanho]){
    // Basicamente separei em quatro partes:
    // Coluna 1 ↘   última coluna ↙
    // Assim todas as diagonais são verificadas.
    int i, j;
    int quant_rainhas=0;
    int lado=floorSqrt(tamanho);

    int skip_baixo = floorSqrt(tamanho) + 1; //quantas linhas pular para checar a diagonal
    int skip_cima = floorSqrt(tamanho) - 1; //quantas linhas voltar para checar a diagonal
    
    // Coluna 1 -> 
    for (i=0; i<tamanho; i=i+4){ // muda a o item inicial da coluna
        quant_rainhas = 0;
        for (j=i; j<tamanho; j=j+skip_baixo){ // percorre a diagonal (direita baixo) do item inicial
            if (str[j]==RAINHA) quant_rainhas = quant_rainhas + 1;
        } 
        if (quant_rainhas > 1){
            printf("\n ⬊ [%d] quant_rainhas", quant_rainhas);
            return false;
        } 

        quant_rainhas = 0;
        for (j=i; j>=0; j=j-skip_cima){ // percorre a diagonal (direita cima) do item inicial
            if (str[j]==RAINHA) quant_rainhas = quant_rainhas + 1;
        }
        if (quant_rainhas > 1) {
            printf("\n ⬈ [%d] quant_rainhas", quant_rainhas);
            return false;
        }
    }
    
    // Última Coluna
    int pos_inicial = floorSqrt(tamanho) - 1; // deixei com nomes diferentes apesar de ter o mesmo valor para facilitar a leitura
    skip_baixo = floorSqrt(tamanho) - 1;
    skip_cima = floorSqrt(tamanho) + 1;

    for (i=pos_inicial; i<tamanho; i+=floorSqrt(tamanho)){ // muda o item da coluna
        
        TODO: // preciso garantir que não está passando do limite do laço


        for (j=i; j<tamanho; j=j+skip_baixo){
            if (str[j] == RAINHA) quant_rainhas++;
        }
        if (quant_rainhas > 1){
            printf("\n ↖ [%d] quant_rainhas", quant_rainhas);
            return false;
        } 

        quant_rainhas = 0;
        for (j=pos_inicial; j>=0; j=j-skip_cima){
            if (str[i] == RAINHA) quant_rainhas++;
        }
        if (quant_rainhas > 1){
            printf("\n ↙ [%d] quant_rainhas", quant_rainhas);
            return false;
        }
    }

    return true;
}

int n_rainhas(int tamanho, char str[]){
    int i, rainhas=0, lado = floorSqrt(tamanho);

    // conta as rainhas na string
    for (i=0; i<tamanho; i++){
        if (str[i]==RAINHA) rainhas++; 
    }

    if(verifica_linha(tamanho, str) && verifica_coluna(tamanho, str) && verifica_diagonal(tamanho, str)){ 
        if (rainhas == lado){
            printf("Tabuleiro Correto e Completo\n");
            return 2;
        } else {
            printf("Tabuleiro Correto mas Incompleto\n");
            return 0;
        }
    } else {
        printf("Tabuleiro Incorreto!\n");
        return 1;
    }
}
// 
// PARTE 2 DO TRABALHO -> DESENHO DO TABULEIRO
// 

void desenha_tabuleiro(int tamanho, char str[tamanho], int lin, int col){
    int i;
    int lado = floorSqrt(tamanho);
    int indice = (lin-1)*lado + (col-1); // relaciona linha e coluna com o indice da posição (ex. linha 1, coluna 2 = indice 1 da string).

    int cor = n_rainhas(tamanho, str);
    
    for (i=0; i<tamanho; i++){
        
        if (i%lado == 0){
            if (cor == 0) t_cor_fundo(255, 255, 0);
            else if (cor == 1) t_cor_fundo(255, 0, 0);
            else if (cor == 2) t_cor_fundo(0, 255, 0);
            printf("\n");
            printf("\t");
        }

        if (i==indice){
            t_cor_fundo(157, 78, 221);
            t_cor_letra(255, 255, 255);
        } else if ((i/lado+i)%2 == 0){
            t_cor_fundo(255, 255, 255);
            t_cor_letra(0, 0, 0);
        } else {
            t_cor_fundo(0, 0, 0);
            t_cor_letra(255, 255, 255);
        }  

        printf("%c", str[i]);
    }

    t_cor_normal();
    printf("\n\n");
}

// 
// PARTE 3 DO TRABALHO -> PROCESSAMENTO DA ENTRADA
// 

bool processa_entrada(int tamanho, char str[tamanho], int *ref_lin, int *ref_col){
    int lado = floorSqrt(tamanho);
    char tecla;

    if (!t_tem_tecla()) return false;
    else tecla = t_tecla();
    
    switch(tecla){
        case 'x': return true;

        // ao movimentar o cursor, fiz com que ao 'exceder' o numero da linha/coluna o cursor vá para
        // o início/fim da mesma.
        
        // *ref_lin = (*ref_lin>0) ? *ref_lin-1 : lado-1;
        case 'w': 
            if (*ref_lin>1) *ref_lin -= 1;
            else *ref_lin += lado-1;
            return false;
        case 's': 
            if (*ref_lin<lado) *ref_lin += 1;
            else *ref_lin -= lado-1; 
            return false;
        case 'a':
            if (*ref_col>1) *ref_col -= 1;
            else *ref_col += lado-1; 
            return false;
        case 'd': 
            if (*ref_col<lado) *ref_col += 1;
            else *ref_col -= lado-1;
            return false;

        //altera na posição (rainha -> ESPACO_BRANCO -> rainha)
        case '\n':
        case ESPACO_BRANCO:
            int indice = (*ref_lin-1)*lado + (*ref_col-1);  // indice relaciona linha e coluna com o indice da string do tabuleiro
            if (str[indice] == RAINHA) str[indice] = ESPACO_BRANCO;
            else if (str[indice] == ESPACO_BRANCO) str[indice] = RAINHA; 
            return false;

        default: return false;
    }
}

// 
// PARTE 4 DO TRABALHO -> PROGRAMA PRINCIPAL
// 

int main(){
    // ENTRADA DE DADOS DO PROGRAMA

    // pede pro usuario o tamanho do tabuleiro
    int lado;
    printf("Digite o tamanho do tabuleiro (exemplo: 4 => tabuleiro 4x4): ");
    scanf("%d", &lado);

    int tamanho=lado*lado; 
    char str[tamanho];

    // inicialização do tabuleiro (nao pedia no trabalho, mas me facilitou para testar)
    printf("Como iniciar o tabuleiro?\n0: Tabuleiro Vazio\t1: Inserir Tabuleiro Inicial\t2: Tabuleiro Aleatório\nResposta: ");
    int option;
    scanf("%d", &option);
    limpar_buffer();
    if (option == 0){
        int i;
        for (i=0; i<tamanho; i++) {
            str[i] = ESPACO_BRANCO;
        }
    } else if (option == 1){
        int i;
        printf("Qualquer caractere diferente de %c e ' ' será ignorado...\n", RAINHA);
        for (i=0; i<tamanho; i++){
            do{
                scanf("%c", &str[i]);
            }while(str[i]!=ESPACO_BRANCO && str[i]!=RAINHA);
        }
    } else if (option == 2){
        srand(time(0));
        int i;
        for (i=0; i<tamanho; i++){
            if (rand()%2 == 0) str[i] = ESPACO_BRANCO;
            else str[i] = RAINHA;            
        }
    }


    // 
    // PARTE DO PROGRAMA QUE REPETE
    // 

    time_t start = time(NULL); 
    int lin=1, col=1;

    t_inicializa();
    while(true){
        if(n_rainhas(tamanho, str)==2) break;
        t_limpa();
        if (processa_entrada(tamanho, str, &lin, &col)){
            printf("Programa Encerrado.");
            t_limpa();
            break;
        }
        else {
            desenha_tabuleiro(tamanho, str, lin, col);
            t_atualiza();
        }
    }
    t_finaliza();

    // 
    // FINALIZAÇÃO
    time_t diff = time(NULL) - start;
    t_limpa();
    if (n_rainhas(tamanho, str) == 2){
        printf("\nParabéns, você conseguiu em %d segundos!!\nVeja seu tabuleiro vencedor: \n", diff);
        desenha_tabuleiro(tamanho, str, lin, col);
    } 
    else{
        printf ("\nO jogador desistiu com %.2f segundos passados...\nEste era seu tabuleiro:\n\n");
        desenha_tabuleiro(tamanho, str, lin, col);
    } 
}