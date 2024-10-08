#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ========== Aula 08/10 ==========

bool tres_iguais(float l1, float l2, float l3){
    if(a != b) return false;
    if(a != c) return false;
    return true;
}

bool dois_iguais(float l1, float l2, float l3){
    if (a == b) return true;
    if (a == c) return true;
    if (b == c) return true;
    return false;
}

int main(){
    float l1, l2, l3;

    scanf("%f", &l1);
    scanf("%f", &l2);
    scanf("%f", &l3);

    if(tres_iguais(l1, l2, l3)){
        printf("Equilatero");
    }else if(dois_iguais(l1, l2, l3)){
        printf("Isoceles");
    }else{
        printf("Escaleno");
    }
}