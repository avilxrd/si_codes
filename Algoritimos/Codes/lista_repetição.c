#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int exercicio_01(){
    int cont = 0, num_recebido, maior;
    
    scanf("%d", &num_recebido);

    while (num_recebido != 0){
        if(num_recebido > maior){
            maior = num_recebido;
        }
        scanf("%d", &num_recebido);
    }
    printf("O maior numero digitado foi o %d. ", maior);
}

int main(){
    exercicio_01();
}