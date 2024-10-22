#include <stdio.h>
#include <stdlib.h>



int main(){
    float numeros[15];
    int contador, i;
    float acumular=0, media;

    for (i=0; i<15; i++){
        scanf("%f", &numeros[i]);
        if (numeros[i] == 0){
            break; 
        } else {
            acumular = acumular + numeros[i];
        }
    }
    contador = i;
    media = acumular/i;
    printf("media: %.3f\n", media);
    
    for (i=0; i<contador; i++){
        if(numeros[i]<media){
            printf("Menor que a media: %f, [%d]\n", numeros[i], i);
        }
    }

}