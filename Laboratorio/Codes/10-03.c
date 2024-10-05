#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//================= Aula 03/10/2024 =================//
bool diferenca(float gasolina, float etanol){
    float diferenca, media;
    media = (gasolina+etanol)/2;

    if(gasolina>etanol){
      diferenca = gasolina-etanol;
    }else if(gasolina<etanol){
      diferenca = etanol-gasolina;
    }else{
      return false;
    }

    if(diferenca>=media*0.05){
      printf("True");
      return true;
    }else{
      printf("False");
      return false;
    }

}

int gasolina_alcool(){
    float custo_gasolina, litro_gasolina, consumo_gasolina;
    float custo_etanol, litro_etanol, consumo_etanol;
    float distancia;

    //Gasolina
    printf("=============GASOLINA================\n");
    printf("Digite o valor do Litro da Gasolina: ");
    scanf("%f", &litro_gasolina);
    printf("Digite o consumo do carro com Gasolina (em Km/L): ");
    scanf("%f", &consumo_gasolina);
    //Etanol
    printf("\n==============ETANOL=================\n");
    printf("Digite o valor do Litro do Etanol: ");
    scanf("%f", &litro_etanol);
    printf("Digite o consumo do carro com Etanol (em Km/L): ");
    scanf("%f", &consumo_etanol);
    //Distancia
    printf("\n============DISTANCIA================\n");
    printf("Digite a distancia a ser percorrida: ");
    scanf("%f", &distancia);


    //Processamento
    custo_gasolina = (consumo_gasolina/distancia)*litro_gasolina;
    custo_etanol = (consumo_etanol/distancia)*litro_etanol;

    printf("Custo Gasolina: R$ %.2f\n", custo_gasolina);
    printf("Custo Etanol: R$ %.2f\n", custo_etanol);

    float media; 
    media = (litro_gasolina * litro_etanol)/2;
    
    if(diferenca(custo_gasolina, custo_etanol) == true){
      if(custo_gasolina>custo_etanol){
        printf("Gasolina é mais barato!");
      }else{
        printf("Etanol é mais barato!");
      }
    }else{
        printf("Tanto Faz!\n");
    }

}

int main(){
    gasolina_alcool();
}