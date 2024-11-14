// l1-t2 Miguel Avila de Oliveira
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define RAINHA 'Q'
#define ESPACO_BRANCO ' '

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

// PARTE 1 DO TRABALHO -> VERIFICAÇÃO DAS N RAINHAS
bool verifica_linha(int tamanho, char str[tamanho]){
    int i, aux=0, cont=0;
    int lado = floorSqrt(tamanho);

    for (i=0; i<tamanho; i++){
        // conta as rainhas por linha
        if (str[i] == RAINHA) cont = cont + 1;
        
        // conta quantos quadrados foram verificados
        aux = aux + 1;
        // analisa as informações acima
        if (aux == lado){
            if (cont > 1){
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
    int lado = floorSqrt(tamanho);

    // percorre o array em colunas
    for (i=0; i<lado;i++){
        aux = i;
        for (j=0; j<lado; j++){

            // conta as rainhas por coluna
            if (str[aux] == RAINHA) cont = cont + 1;
            quant++;

            // verifica os dados
            if (quant == lado){
                if (cont > 1){
                    printf("Mais de uma rainha na coluna\n");
                    return false;
                }
                cont = 0;
                quant = 0;
            }
            aux = aux + lado;
        }
    }
    return true;
}

    // Basicamente separei em quatro partes:
    // Coluna 1 ↘   última coluna ↙
    // Assim todas as diagonais são verificadas.
bool verifica_diagonal(int tamanho, char str[tamanho]){
    int i, j;
    int quant_rainhas;
    int lado=floorSqrt(tamanho);

    // Coluna 1 -> 
    for (i=0; i<tamanho; i+=lado){ // muda a o item inicial da coluna
        // col 1 ⬊
        quant_rainhas = 0;
        for (j=i; j<tamanho; j+=lado+1){ // percorre a diagonal (direita baixo) do item inicial
            if (str[j]==RAINHA) quant_rainhas++;
        } 
        if (quant_rainhas > 1){
            printf("DIREITA BAIXO: %d Rainhas\n", quant_rainhas);
            return false;
        } 

        // col 1 ⬈
        quant_rainhas = 0;
        for (j=i; j>=0; j-=lado-1){ // percorre a diagonal (direita cima) do item inicial
            if (str[j]==RAINHA) quant_rainhas++;
        }
        if (quant_rainhas > 1){
            printf("DIREITA CIMA: %d Rainhas\n", quant_rainhas);
            return false;
        }
    }
    
    // Última Coluna
    for (i=lado-1; i<tamanho; i+=lado){ // muda o item da coluna
        
        quant_rainhas = 0;
        for (j=i; j+lado<tamanho; j+=lado-1){
            if (str[j] == RAINHA) quant_rainhas++;
        }
        if (quant_rainhas > 1){
            printf("ESQUERDA BAIXO: %d Rainhas\n", quant_rainhas);
            return false;
        } 

        quant_rainhas = 0;
        for (j=lado-1; j>=0; j-=lado+1){
            if (str[i] == RAINHA) quant_rainhas++;
        }
        if (quant_rainhas > 1){
            printf("ESQUERDA CIMA: %d Rainhas\n", quant_rainhas);
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
            // printf("Tabuleiro Correto e Completo\n");
            return 2;
        } else {
            // printf("Tabuleiro Correto mas Incompleto\n");
            return 0;
        }
    } else {
        // printf("Tabuleiro Incorreto!\n");
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
        } else if (((i/lado)+(i/lado+i))%2 == 0){
            t_cor_fundo(255, 255, 255);
            t_cor_letra(0, 0, 0);
        } else {
            t_cor_fundo(0, 0, 0);
            t_cor_letra(255, 255, 255);
        }  
        printf("%c", str[i]);

    }
    t_cor_normal();
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
    t_limpa();
    while(true){
        t_lincol(1,1);
        if(n_rainhas(tamanho, str)==2) break;
        
        if (processa_entrada(tamanho, str, &lin, &col)){
            printf("Programa Encerrado.");
            break;
        } else {
            t_limpa();
            desenha_tabuleiro(tamanho, str, lin, col);
            t_atualiza();
        }
    }
    t_limpa();
    t_cor_normal();
    t_finaliza();

    // 
    // FINALIZAÇÃO
    time_t diff = time(NULL) - start;
    t_limpa();
    if (n_rainhas(tamanho, str) == 2){
        printf("\nParabéns, você conseguiu em %ld segundos!!\nVeja seu tabuleiro vencedor: \n", diff);
        desenha_tabuleiro(tamanho, str, lin, col);
        printf("\n\n");
    } 
    else{
        printf ("\nO jogador desistiu com %ld segundos passados...\nEste era seu tabuleiro:\n", diff);
        desenha_tabuleiro(tamanho, str, lin, col);
        printf("\n\n");
    } 
}