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

//=============== Exercicios 03/10/2024 ===============//
int exercicio_01(){
  float num_1, num_2;
  scanf("%f", &num_1);  
  scanf("%f", &num_2);  

  if(num_1 > num_2){
    printf("%f", num_1);
  }else if(num_2 > num_1){
    printf("%f", num_2);
  }else{
    printf("Os numeros sao iguais");
  }
}

int exercicio_02(){
  float num_1, num_2;
  scanf("%f", &num_1);  
  scanf("%f", &num_2);  

  if(num_1 < num_2){
    printf("%f", num_1);
  }else if(num_2 < num_1){
    printf("%f", num_2);
  }else{
    printf("Os numeros sao iguais");
  }
}

int exercicio_03(){
  int num;
  if(num % 2 == 0){
    printf("O numero %d e par", num);
  }else{
    printf("O numero %d e impar", num);
  }
}

int exercicio_04(){
  float num_1, num_2, num_3;
  scanf("%f", &num_1);
  scanf("%f", &num_2);
  scanf("%f", &num_3);

  if(num_1 > num_2 && num_1 > num_3){
    printf("Maior: %f", num_1);
  }else if(num_2 > num_1 && num_2 > num_3){
    printf("Maior: %f", num_2);
  }else if(num_3 > num_1 && num_3 > num_2){
    printf("Maior: %f", num_3);
  }else{
    printf("Todos os numeros sao iguais");
  }
}

int exercicio_05(){
  float num_1, num_2, num_3;
  scanf("%f", &num_1);
  scanf("%f", &num_2);
  scanf("%f", &num_3);

  if((num_1 > num_2 && num_1 < num_3)||(num_1 < num_2 && num_1 > num_3)){
    printf("%f", num_1);
  }else if ((num_2 < num_1 && num_2 > num_3) || (num_2 > num_1 && num_2 < num_3)){
    printf("%f", num_2);
  }else if ((num_3 < num_1 && num_3 > num_2) || (num_3 > num_1 && num_3 < num_2)){
    printf("%f", num_3);
  }
}

int exercicio_06(){
  float nota_1, nota_2;
  float peso_1, peso_2;
  scanf("%f", &nota_1);
  scanf("%f", &nota_2);
  scanf("%f", &peso_1);
  scanf("%f", &peso_2);

  float media_pond = (((nota_1 * peso_1)+(nota_2 * peso_2))/(peso_1 + peso_2));
  if(media_pond >= 7){
    printf("Aluno aprovado com media %.2f", media_pond);
  }else{
    float nota_exame, media_final;
    scanf("%f", &nota_exame);
    media_final = (media_pond + nota_exame)/2;
    if(media_final >= 5){
      printf("Aluno aprovado com media %.2f", media_final);
    }else{
      printf("Aluno reprovado com media %.2f", media_final);
    }
  }
}

int exercicio_07(){
  float temperatura;
  scanf("%f", &temperatura);
  if(temperatura < 18){
    printf("Casaco.");
  }else{
    printf("Camiseta.");
  }
}

int exercicio_08(){
  float temperatura, vento;
  scanf("%f", &temperatura);
  scanf("%f", &vento);
  if(vento > 10 && temperatura < 20){
    printf("Casaco.");
  }else if(vento < 10 && temperatura < 18){
    printf("Casaco.");
  }else{
    printf("Camiseta.");
  }
}

int exercicio_09(){
  float temperatura, vento;
  int chuva = 0;

  scanf("%f", &temperatura);
  scanf("%f", &vento);
  scanf("%d", &chuva);

  if(chuva == 1 || temperatura > 35){
    printf("Levar guarda chuva.");
  }
  
  if(vento > 10 && temperatura < 20){
    printf("Casaco.");
  }else if(vento < 10 && temperatura < 18){
    printf("Casaco.");
  }else{
    printf("Camiseta.");
  }
}

float aliquota_ir(float base){
  float aliquota;
  if(base <= 2259.20){
    aliquota = 0;
  }else if(base >= 2259.21 && base <= 2826.65){
    aliquota = 0.075;
  }else if(base >= 2826.66 && base <= 3751.05){
    aliquota = 0.15;
  }else if(base >= 3751.06 && base <= 4664.68){
    aliquota = 0.225;
  }else{
    aliquota = 0.275;
  }
  return aliquota;
}
float parcela_ir(float base){
  float parcela;
  if(base <= 2259.20){
    parcela = 0;
  }else if(base >= 2259.21 && base <= 2826.65){
    parcela = 169.44;
  }else if(base >= 2826.66 && base <= 3751.05){
    parcela = 381.44;
  }else if(base >= 3751.06 && base <= 4664.68){
    parcela = 662.77;
  }else{
    parcela = 896.0;
  }
  return parcela;
}
float calculo_ir(){
  float base_ir;
  float aliquota, parcela;
  float ir;

  scanf("%f", &base_ir);
  aliquota = aliquota_ir(base_ir);
  parcela = parcela_ir(base_ir);

  ir = (base_ir * aliquota) - parcela;

  printf("Aliquota IR: %.2f\n", aliquota);
  printf("Parcela IR: %.2f\n", parcela);
  printf("Valor do IR: %.2f\n", ir);
  return ir;
}

int main(){
  calculo_ir();
}