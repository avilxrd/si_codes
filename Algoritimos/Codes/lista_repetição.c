#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int exercicio_01(){
    int cont = 0, num_recebido, maior;
    
    printf("Digite um número: \n");
    scanf("%d", &num_recebido);

    while (num_recebido != 0){
        if(num_recebido > maior){
            maior = num_recebido;
        }
        printf("Digite um número: \n");
        scanf("%d", &num_recebido);
    }
    printf("O maior numero digitado foi o %d. \n", maior);
}

int exercicio_02(){
    float nota = 0, soma_notas = 0, media;
    int i;

    for(i=0; i<2; i++){
        do{
            if(nota<0 || nota > 10){
                printf("Nota inválida.");
            }
            printf("Digite uma nota: ");
            scanf("%f", &nota);
        }while(nota<0 || nota > 10);
        soma_notas = soma_notas + nota;
    }
    media = soma_notas / i;
    printf("Média final: %.2f\n", media);
}

int exercicio_03(){
    int x, y;

    do{
        printf("Digite um valor para x: ");
        scanf("%d", &x);
        printf("Digite um valor para y: ");
        scanf("%d", &y);
        printf("Par digitado: (%d, %d) ", x, y);

        if (x < y){
            printf("-> Crescente.\n");
        } else if(x > y){
            printf("-> Decrescente.\n");
        }
    }
    while(x != y);

    printf("Encerrando...\n");
}

int exercicio_04(){
    int x, y, soma = 0;
    int i;

    printf("Digite o intervalo [x y]: ");
    scanf("%d%d", &x, &y); 

    for(i=x; i<y+1; i++){
        soma = soma + i;
    }
    printf("Soma: %d\n", soma);
}

int exercicio_05(){
    int i, num;
    scanf("%d", &num);
    
    for (i=1; i<num; i++){//para considerar o proprio numero -> i<num+1
        if(num%i == 0){
            printf("%d é divisor.\n", i);
        }
    }
}

int exercicio_06(){
    int num;
    int i, contador = 0;    

    scanf("%d", &num);

    if (num == 0){
        printf("Não sei se 0 é primo ");
    } else if (num == 1){
        printf("É primo.\n");
    } else {
        for (i=1; i<num+1; i++){
            if(num%i == 0){
                contador = contador + 1;
            }
        }
        if (contador == 2){
            printf("É primo.\n");
        } else {
            printf("Não é primo.\n");
        }
    }
}

int exercicio_07(){
    int num, i, soma_divisores = 0;
    scanf("%d", &num);
    for (i=1; i<num; i++){
        if(num%i == 0){
            soma_divisores = soma_divisores + i;
        }
    }

    if (soma_divisores == num){
        printf("O número %d é perfeito.\n", num);
    } else {
        printf("O número %d não é perfeito.\n", num);
    }
}

int exercicio_08(){
    int num, i;
    int a=0, b=1, c;
    scanf("%d", &num);
    
    printf("Sequencia de Fibonacci [%d].\n", num);
    if(num <= 0){
        printf("...\n");
    } else if (num == 1){
        printf("%d\n", a);
    } else if (num == 2){
        printf("%d\n", a);
        printf("%d\n", b);
    } else {
        printf("%d\n", a);
        printf("%d\n", b);
        for (i=0; i<num-2; i++){
            c = a + b;
            printf("%d\n", c);
            a = b;
            b = c;
        }
    }
}

int exercicio_09(){
    //nao consegui fazer ainda
}

int exercicio_10(){
    int i, indice;
    scanf("%d", &indice);
    printf("Feliz nat");
    for (i=0;i<indice; i++){
        printf("a");
    }
    printf("l!\n");
}


int main(){
    exercicio_10();
}