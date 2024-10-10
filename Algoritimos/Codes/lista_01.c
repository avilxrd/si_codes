#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

int exercicio_01(){
    float base, altura;
    float area, perimetro;
    scanf("%f,%f", &base, &altura);
    area = base * altura;
    perimetro = 2*base + 2*altura;
    printf("Area: %f / Perímetro: %f", area, perimetro);
}
int exercicio_02(){
    float raio;
    float area, circunferencia;
    scanf("%f", &raio);
    area = raio * raio * PI;
    circunferencia = 2 * raio * PI;
    printf("Raio: %f, Area: %f, Circunferencia: %f", raio, area, circunferencia);
}
int exercicio_03(){
    int cont_semana=0, cont_mes=0, cont_ano=0;
    int dias;
    scanf("%d", &dias);
    while(dias>=365){
        dias = dias - 365;
        cont_ano = cont_ano + 1;
    }
    while(dias>=30){
        dias = dias - 30;
        cont_mes = cont_mes + 1;
    }
    while(dias >=7){
        dias = dias - 7;
        cont_semana = cont_semana + 1;
    }
    printf("%d anos, %d meses, %d semanas e %d dias.", cont_ano, cont_mes, cont_semana, dias);
}
int exercicio_04(){
    int id, horas;
    float valor_hora;
    scanf("%d%d%f", &id, &horas, &valor_hora);
    printf("id: %d, salario: ", id, horas*valor_hora);
}
int exercicio_05(){
    int num, maior=0;
    int i;
    for(i=0; i<3; i++){
        scanf("%d", &num);
        if(num>maior){
            maior = num;
        }
    }
    printf("maior valor: %d", maior);
}
int exercicio_06(){
    float ponto_1[2], ponto_2[2];
    float distancia;
    scanf("%f %f", &ponto_1[0], &ponto_1[1]);
    scanf("%f %f", &ponto_2[0], &ponto_2[1]);
    distancia = sqrt(pow(ponto_2[1]-ponto_1[1], 2) + pow(ponto_2[0]-ponto_1[0], 2));
    printf("distancia: %.2f", distancia);
}
int exercicio_07(){
    //2, 5, 10, 20, 50, 100
    int valor;
    int cont_2=0, cont_5=0, cont_10=0, cont_20=0, cont_50=0, cont_100=0;
    scanf("%d", &valor);
    while(valor >= 100){
        valor = valor - 100;
        cont_100 ++;
    }
    while(valor >= 50){
        valor = valor - 50;
        cont_50 ++;
    }
    while(valor >= 20){
        valor = valor - 20;
        cont_20 ++;
    }
    while(valor >= 10){
        valor = valor - 10;
        cont_10 ++;
    }
    while(valor >= 5){
        valor = valor - 5;
        cont_5 ++;
    }
    while(valor >= 2){
        valor = valor - 2;
        cont_2 ++;
    }
    printf("%d notas de 100, %d notas de 50, %d notas de 20, %d notas de 10, %d notas de 5, %d notas de 2.", cont_100, cont_50, cont_20, cont_10, cont_5, cont_2);
}
exercicio_08(){
    int segundos, horas, minutos;
    
}

int main(){
    exercicio_07();
}